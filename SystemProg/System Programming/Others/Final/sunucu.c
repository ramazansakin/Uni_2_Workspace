
 #include <errno.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <sys/wait.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <pthread.h>
 #include <ctype.h>
 #include <time.h>
 
 // Constants
 #define PORTNUM 50000
 #define MAXHOSTNAME 5000
 #define MAX_CHAT 256
 
 /*** function prototypes ***/
 int establish (unsigned short portnum);
 int getConnection( int s );
 void messageOrganizator( char *message, int istemciDes );
 void terminator( int signo );
 void *connecting( void *parameter );
 void *getMessage( void *parameter );
 /*** end of function prototypes ***/
 
 struct istemci{
	int des; 
	int id;  // index in array 
 };
 
 struct offlineMessage{
	int target;
	char message[ MAX_CHAT ];
 };
 
 /*** Global variables declarations ***/
 int sunucu;
 int maxClient;
 struct istemci* istemciler;
 int istemciSayisi = 0;
 int offlineMessNum=0;
 struct offlineMessage offMess[100];
 int firstClientDes=0;
 /*** end of Global variables declarations ***/
 
////////////// ######################################## ////////////////
 
 int main(int argc, char* argv[] )
 {
	if( argc != 2 )
	{
		fprintf(stderr, "USAGE: %s max_istemci(digit)\n", argv[0]);
		exit( 1 );
	} 
	
	int i=0;
	for(i=0; i<strlen( argv[1] ); i++ )
		if( isdigit( argv[1][i] ) == 0 )
		{
			fprintf(stderr, "USAGE: %s max_istemci(digit)\n", argv[0]);
			exit( 1 );
		}
		
	
	maxClient = atoi( argv[1] );
	istemciler = malloc( sizeof(struct istemci) * maxClient );
	
	if( (sunucu= establish(PORTNUM) ) < 0)
	{ /* plug in the phone */
		perror("establish");
		exit(1);
	}
	// established successfully
	
	fprintf(stderr, "%s%s%s%s%s%s%s", "sohbet progamına hosgeldiniz\n", 
	"oturumu sunucu olarak actınız",
	"bu durumda sohbeti sadece yönetme hakkınız olacaktır\n",
	"yani size hiç mesaj gonderilemeyek ama siz gönderebilirsiniz\n",
	"siz istemcilere kill mesajı göndererek sohbetten atabilirsiniz\n",
	"kill mesajı asagıda ki örnekteki gibi gonderilebilecek\n",
	"1 kill\n" );
	
	
	// ctrl+c signal handler
	struct sigaction act1;
	
	act1.sa_handler = terminator;        
    act1.sa_flags = 0;
    
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGINT, &act1, NULL) == -1)) {
        perror("Failed to set SIGINT handler");
        return 1;
    }
	
	// sunucu istemci bekliyo bu iplikle
	pthread_t tid1;
	pthread_create(&tid1, NULL, connecting, NULL);
	
	/************ sohbet in basladıgı kısım ***************************/
	
	char *chat = malloc( sizeof( char ) * MAX_CHAT );
	while( 1 )
	{
		gets( chat );
		messageOrganizator( chat, 0 );
	}
	
	close( sunucu );
	return 0;
 }
 
////////////// ######################################## ////////////////
 
 void *connecting( void *parameter )
 {
	while( istemciSayisi <= maxClient )
	{
		if ((istemciler[ istemciSayisi ].des = getConnection( sunucu )) < 0)
		{
			if (errno == EINTR)
				continue;
			perror("accept");
			exit(1);
		}
		
		istemciler[ istemciSayisi ].id = istemciSayisi+1;
		
		pthread_t tid;
		pthread_create(&tid, NULL, getMessage, &( istemciler[ istemciSayisi ]) );
		
		++istemciSayisi;
	}
	
	return NULL;
 }/**************** end of connecting function ************************/
 
 int getConnection( int s )
 {
	int t; /* socket of connection */
	if ( (t = accept(s, NULL, NULL ) ) < 0)
		return(-1);
	
	if(istemciSayisi == 0)
		firstClientDes = t;
	
	++istemciSayisi;
	write(t, &istemciSayisi, sizeof(int));
	--istemciSayisi;
	
	int i=0;
	for(i=0; i<offlineMessNum; i++ )
		if( offMess[i].target == istemciSayisi+1 )
			write(t, offMess[i].message, sizeof(char) * MAX_CHAT );
	
	printf("Connection established : %d\n",t);
	
	return t;
 }/************ end of getConnection function *************************/
 
 int establish ( unsigned short portnum )
 {
	char myname[MAXHOSTNAME];
	int s;
	
	struct sockaddr_in sa;
	struct hostent *hp;
	
	memset(&sa, 0, sizeof(struct sockaddr_in)); /* clear our address */
	
	gethostname(myname, MAXHOSTNAME); /* who are we? */
	
	hp= gethostbyname(myname); /* get our address info */
	
	if (hp == NULL) /* we don't exist !? */
		return(-1);
	
	sa.sin_family= hp->h_addrtype; /* this is our host address */
	sa.sin_port= htons(portnum); /* this is our port number */
	
	if ((s= socket(AF_INET, SOCK_STREAM, 0)) < 0) /* create socket */
		return(-1);
	
	if (bind(s, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0)
	{
		close(s);
		return(-1); /* bind address to socket */
	}
	
	listen(s, 2); /* max # of queued connects */
	
	return s;
 }/****************************** end of establish function ***********/
 
 void *getMessage( void *parameter )
 {
	struct istemci ilgiliIstemci = *( (struct istemci *) parameter);
	
	char *chat = malloc( sizeof( char ) * MAX_CHAT );
	
	while( 1 )
	{
		read(ilgiliIstemci.des, chat, sizeof( char ) * MAX_CHAT );
		
		if( strcmp(chat, "i am killed") == 0 )
		{
			fprintf(stderr, "%d cevrimdışı oldu\n", ilgiliIstemci.id);
			
			int i=0;
			for( i=0; i<istemciSayisi; i++ )
			{
				if( istemciler[i].des == ilgiliIstemci.des )
				{
					istemciler[i].des =0;
					istemciler[i].id =0;
					return NULL;
				}
			}
		}
		messageOrganizator( chat, ilgiliIstemci.des );
		
	}
	
	return NULL;
 }
 
 void messageOrganizator( char *message, int istemciDes )
 {
	char messageFormat[] = "dikkat mesaj formatı hatalı once istemci tanımlayıcı sayısını girin ardından da iki tırnak icinde mesajınızı girin\n";
	
	char warm[] = "sunucu ya bu sekilde mesaj gonderemezsin\n";
	int target = atoi( message ), startMessage=0;
	char *temp = NULL;
	char *sendMessage = malloc( sizeof(char)*MAX_CHAT );
	
	if( target < 0 )
	{
		char *warm = "server: indeks numarası negetif olamaz\n"; 
		write(istemciDes, warm, sizeof(char)*MAX_CHAT );
		return;
	}
	
	while( isdigit( message[ startMessage ] ) )
		++startMessage;
	
	
	if( message[ startMessage ] != ' ' ||
		message[ startMessage+1 ] != '"' ||
		message[ strlen(message)-1] != '"' )
	
	{
		temp = message + startMessage + 1;
		temp[4] = '\0';
		
		if( strcmp(temp, "kill") == 0 )
		{
			if( target > istemciSayisi )
			{
				char *warn = "server: bu istemci henuz sohbete katılmamıs katılmadan olduremezsiniz\n";
				write(istemciDes, warn, sizeof(char)*MAX_CHAT);
				return;
			}
			
			else if( istemciler[ target-1 ].des == 0 )
			{
				char *warn = "server: bu istemci zaten terminate edilmiş durumda\n";
				write(istemciDes, warn, sizeof(char)*MAX_CHAT);
				return;
			}
			
			write(istemciler[ target-1 ].des, temp, sizeof( char ) * 5);
		}
		else
			write(istemciDes, messageFormat, sizeof( char ) * MAX_CHAT );
		
		return;
	}
	
	
	message[ strlen( message )-1 ] = '\n'; // son da ki " işaretini için
	temp = message + startMessage + 2;
	time_t curr = time(NULL);
	
	if( istemciDes == 0 )
		sprintf(sendMessage, "\nSUNUCU-->%s ~%s", ctime( &curr ), temp );
	else
		sprintf(sendMessage, "\nistemmci%d-->%s ~%s", istemciDes-firstClientDes+1,
				ctime( &curr ), temp );
	
	if( target == 0 )
	{
		write(istemciDes, warm, sizeof( char ) * MAX_CHAT );
		return;
	}
	else
	{
		
		if( target > maxClient )
		{
			char *bilgi = "server: bu kadar cok istemci kabul edilmeyecek dolayısıyla bu istemci hiç varolmayacak\n";
			write(istemciDes, bilgi, sizeof(char) * MAX_CHAT );
			return;
		}
		if( target > istemciSayisi )
		{
			char *bilgi = "server: mesajınız off line olarak tanımlandı istemci online oldugunda iletilecek\n";
			write(istemciDes, bilgi, sizeof(char) * MAX_CHAT );
			
			struct offlineMessage temp;
			temp.target = target;
			strcpy(temp.message, sendMessage);
			
			offMess[ offlineMessNum ] = temp;
			offlineMessNum++;
			
			return;
		}
		else if( istemciler[ target-1 ].des == 0 )
		{
			char *bilgi = "server: mesajınızı artık hedef istemciye iletemem cunku terminate edilmis\n";
			write(istemciDes, bilgi, sizeof(char)* MAX_CHAT );
				return;
		}
		
		write( istemciler[ target-1 ].des, sendMessage, sizeof(char)* MAX_CHAT );
	}
	
	return;
 }
 
 void terminator( int signo )
 {
	int i=0;
	char killMessage[] = "kill";
	
	for(i=0; i<istemciSayisi; i++ )
		if( istemciler[ i ].des != 0 )
			write(istemciler[ i ].des, killMessage, sizeof( char ) * 5);
	
	close( sunucu );
	
	fprintf(stderr, "terminated all Clients\n");
	exit( 1 );
 }

