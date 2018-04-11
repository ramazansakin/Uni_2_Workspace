
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
	
 #define PORTNUM 50000
 #define MAXHOSTNAME 5000
 #define MAX_CHAT 256
 
 /*** function prototypes ***/
 int callSocket(char *hostname, unsigned short portnum);
 void *getMessage( void *parameter );
 void terminator( int signo );
 /*** end of function prototypes ***/
 
 /*** Global variables declarations ***/
 int istemci;
 int sunucu;
 /*** end of Global variables declarations ***/


//////////////////////////// ##################### ///////////////////// 
 int main(int argc, char* argv[] )
 {
	if( argc != 2 )
	{
		fprintf(stderr, "USAGE: %s server_ip\n", argv[0] );
		exit( 1 );
	}
	
	if ( ( sunucu = callSocket(argv[1], (unsigned)(PORTNUM) ) ) < 0) 
	{ 	
		perror("accept");
		exit( 1 );
	}
	
	fprintf(stderr, "%s\n%s\n", 
	"sohbet programına hosgeldiniz mesaj formatı bu sekilde",
	"clientId (ikiTırnak)message(ikiTırnak)");
	
	// ctrl+c signal handler 
	struct sigaction act1;
	
	act1.sa_handler = terminator;        
    act1.sa_flags = 0;
    
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGINT, &act1, NULL) == -1)) {
        perror("Failed to set SIGINT handler");
        return 1;
    }
    
	pthread_t tid;
	pthread_create(&tid, NULL, getMessage, NULL);
	
	char *chat = malloc( sizeof( char )*MAX_CHAT );
	
	while( 1 )
	{
		gets( chat );
		if( strcmp(chat, "i am killed") == 0 )
		{
			fprintf(stderr, "WARNING: bu mesajı bu sekilde gonderemezsiniz\n");
			continue;
		}
		write( sunucu, chat, sizeof( char ) * MAX_CHAT );
	}
	
	return 0;
 }
//////////////////////////// ##################### /////////////////////
 
 int callSocket(char *hostname, unsigned short portnum)
 {
	struct sockaddr_in sa;
	struct hostent *hp;
	int s;
	
	if ((hp= gethostbyname(hostname)) == NULL)
	{ /* do we know the host's */
		errno= ECONNREFUSED; /* address? */
		return -1; /* no */
	} /* if gethostname */
	
	memset(&sa, 0 ,sizeof(sa));
	memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length ); /* set address */
	
	sa.sin_family= hp->h_addrtype;
	sa.sin_port= htons((u_short)portnum);
	
	if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) /* get socket */
		return -1;
	
	if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0)
	{ /* connect */
		close( s );
		return -1;
	} /* if connect */
	
	int id;
	read(s, &id, sizeof(int));
	fprintf(stderr, "my id %d\n", id);
	return s;
 }/****************** end of callSocket function **********************/ 
 
 void *getMessage( void *parameter )
 {
	char *message = malloc( sizeof( char ) * MAX_CHAT );
	
	while( 1 )
	{
		read(sunucu, message, sizeof( char ) * MAX_CHAT );
		if( strcmp(message, "kill") == 0 )
		{
			char *killMessage = "i am killed";
			write(sunucu, killMessage, sizeof(char) * 12 );
			
			fprintf(stderr, "killed by server\n");
			exit( 1 );
		}
		fprintf(stderr, "%s", message );
	}
	
	return NULL;
 }/********************** end of getMessage function ******************/
 
 void terminator( int signo )
 {
	fprintf(stderr, "i am killed by user\n"); 
	char *killMessage = "i am killed";
	write(sunucu, killMessage, sizeof(char) * 12 );
	exit( 0 );
 }
