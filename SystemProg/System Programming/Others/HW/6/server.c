
 /* server.c file 
  * Mustafa Çoker
  * 08104402
  * Chatting project
  * HW # 6
  * */
 
 #include <stdio.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <signal.h>
 #include <stdlib.h>
 #include <sys/shm.h>
 #include <pthread.h>
 #include <string.h>
 #include <ctype.h> // for isdigit func.
 
 #define PERM (S_IRUSR | S_IWUSR)
 #define MAX_CHAT 256
 #define MAX_CLIENT 50
 #define FIFO_PERMS  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
 
 // global variables 
 static volatile sig_atomic_t istemciler[ MAX_CLIENT ];
 static volatile sig_atomic_t istemciSayisi = 0;
 static volatile int sharedMemId[ MAX_CLIENT ];
 int fifoID =0;
 
 // function prototypes
 void cleanTempFile();
 void *createSharedMem( void *parameter ); // thread function
 void *receivedMessageHandler( void *parameter ); // thread function 
 void *messageSender( void *parameter ); // thread function
 
 static void registerClient( int signo )
 {
	pid_t clientPid;
	int fildes = open("registerFile", O_RDWR );
	
	if( fildes == -1 )
	{
		perror("Failed to opening the register file\n");
		exit( 1 );
	}
	
	read(fildes, &clientPid, sizeof(pid_t));
	
	/*** create a shared mem for message with different thread ***/
	pthread_t tid;
	
	pthread_create(&tid, NULL, createSharedMem, &clientPid );
	pthread_join(tid, NULL );
	
	/*** end creating shared mem ***/
	
	fprintf(stderr, "%ld registered yet\n", (long)clientPid );
	fclose( fopen( "registerFile", "w" ));
	
	return;
 }/************* end of registerClient function ***********************/
 
 // handler of SIGINT signal
 static void terminator( int signo )
 {
	int i=0;
	for(i=0; i<istemciSayisi; i++ )
		kill( istemciler[ i ], SIGUSR1 );
	
	printf("terminated all clients\n");
	
	cleanTempFile();
	
	exit( 1 );	 
 }/***************** end of terminator function ***********************/
 
 static void unRegisterClient( int signo )
 {
	int fildes = open("unRegisterFile", O_RDWR );
	
	pid_t targetPid;
	read(fildes, &targetPid, sizeof( pid_t ) );
	
	int i=0;
	int targetFound = 0;
	
	for(i=0; i<istemciSayisi; i++ )
	{
		if( targetFound )
		{
			istemciler[ i-1 ] = istemciler[ i ];
			sharedMemId[ i -1 ] = sharedMemId[ i ];
		}
		else
		{
			if( istemciler[i] == targetPid )
			{
				targetFound = 1;
			}	
		}
	}
	
	--istemciSayisi;
	
	fprintf(stderr, "%ld unRegistered yet\n", (long)targetPid);
	
	return;
 }/************ end of unRegisterClient function **********************/
 
 static void messageReceiver( int signo )
 {
	pid_t messageSender; 
	pthread_t tid;
	
	read(fifoID, &messageSender, sizeof(pid_t));
	
	pthread_create(&tid, NULL, receivedMessageHandler, &messageSender );
	pthread_join(tid, NULL);
	
	return;
 }/************ end of receiveMessage function ************************/
 
 int main()
 {
	
	fclose( fopen("registerFile", "w") );
	fclose( fopen( "sunucuPidFile", "w"));
	
	int fildes = open("sunucuPidFile", O_RDWR );
	pid_t mypid = getpid();
	
	write(fildes, &mypid, sizeof( pid_t ));
	
	if( mkfifo("messageQueueFifo", FIFO_PERMS ) == -1  )
		perror("Failed to creating messageFifo\n");
	
	fifoID = open("messageQueueFifo", O_RDWR | O_SYNC );
	
	if( mkfifo("sharedMemIdFifo", FIFO_PERMS ) == -1 )
		perror("Failed the sharedMemIdFifo\n");
	
	/*** SIGNAL HANDLERS ***/
	
	struct sigaction act1;
	
	act1.sa_handler = registerClient;            
    act1.sa_flags = 0;
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGUSR1, &act1, NULL) == -1)) {
        perror("Failed to set SIGUSER1 handler");
        return 1;
    }
    
    struct sigaction act2;
    
    act2.sa_handler = terminator; // terminate the server
    act2.sa_flags = 0;
    if( (sigemptyset(&act2.sa_mask) == -1 ) ||
			(sigaction(SIGINT, &act2, NULL) == -1) )
    {
		perror("Failed to set SIGINT handler\n");
		return 1;
	}
    
    struct sigaction act3;
    
    act3.sa_handler = unRegisterClient;
    act3.sa_flags = 0;
    if( (sigemptyset(&act3.sa_mask) == -1 ) ||
			(sigaction(SIGUSR2, &act3, NULL) == -1) )
    {
		perror("Failed to set unRegister signal handler\n");
		return 1;
	}
    
    
    struct sigaction act4;
    
    act4.sa_handler = messageReceiver;
    act4.sa_flags = 0;
    if( (sigemptyset(&act4.sa_mask) == -1 ) ||
			(sigaction(SIGABRT, &act4, NULL) == -1) )
    {
		perror("Failed to set unRegister signal handler\n");
		return 1;
	}
    
	/*** END OF SIGNAL HANDLERS ***/
	
	
	
	/*** CHATTING ***/
	char message[256];
	pthread_t tid;
	
	while( 1 )
	{
		gets( message );
		
		pthread_create(&tid, NULL, messageSender, message );
		pthread_join(tid, NULL );
	}
	/*** END OF CHATTINGS ***/
	
	return 0;
 } // end of main
 
 void cleanTempFile()
 {
	remove( "registerFile" );
	remove( "unRegisterFile" );
	remove( "sunucuPidFile" );
	remove( "sharedMemDesFile" );
	
	if( unlink("messageQueueFifo") == -1 )
		perror("Failed to unlink messageFifo\n");
	
	if( unlink( "sharedMemIdFifo" ) == -1 )
		perror("Failed to unlink fifo\n");
	
	return; 
 }/*************** end of cleanTempFile function  *********************/
 
 void *createSharedMem( void *parameter )
 {
	pid_t newClientPid = *( ( pid_t *)parameter);
	
	istemciler[ istemciSayisi ] = newClientPid;
	
	if ((sharedMemId[ istemciSayisi ] = shmget(IPC_PRIVATE, sizeof( char ) * MAX_CHAT, PERM)) == -1)
	{
		perror("Failed to create shared memory segment");
		return NULL;
    }
    
	int id = open("sharedMemIdFifo", O_RDWR | O_SYNC );
	
	int shMemId = sharedMemId[ istemciSayisi ];
	
	write(id, &shMemId, sizeof( int ) );
	
	++istemciSayisi;
	
	return NULL;
 }/*************** end of createSharedMem function  *******************/
 
 void *receivedMessageHandler( void *parameter )
 {
	pid_t messageSender = *((pid_t *)parameter );
	char *sharedMemPtr = NULL, *message = malloc(sizeof( char ) * MAX_CHAT );
	int targetNumber=0;
	int senderIndex =0, i=0;
	
	for(i=0; i<istemciSayisi; i++ )
		if( istemciler[ i ] == messageSender )
		{
			senderIndex = i;
			break;
		}
	
	sharedMemPtr = ( (char *) shmat(sharedMemId[ senderIndex ], NULL, 0));
	targetNumber = atoi( sharedMemPtr );
	
	int digitNumber = 0;
	while( isdigit( *(sharedMemPtr + digitNumber) ) )
		++digitNumber;
	
	if( digitNumber == 0 )
	{
		fprintf(stderr, "invalid targetNumber from %ld\n", (long)messageSender );
		return NULL;
	}
	
	strcpy(message, sharedMemPtr + digitNumber);
	
	fprintf(stderr, "sender index %d message %s\n", targetNumber, message );
	
	return NULL;
 }/************* end of receivedMessageHandler function ***************/
 
 void *messageSender( void *parameter )
 {
	char *message = (char *) parameter;
	
	fprintf(stderr, "server mess ->%s\n", message );
	
	
	return NULL;
 }
