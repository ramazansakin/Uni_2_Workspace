
 /* client.c file 
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
 #include <string.h>
 
 #define FIFO_PERMS  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
 
 /* global variables */
 pid_t sunucuPid;
 int sharedMemID;
 
 static void selfTerminate( int signo )
 {
	fclose( fopen("unRegisterFile", "w") ); 
	int fildes = open( "unRegisterFile", O_RDWR );
	
	pid_t mypid = getpid();
	 
	write(fildes, &mypid, sizeof( pid_t )); 
	
	if( kill(sunucuPid, SIGUSR2 ) == -1 )
		perror("Failed to sending unRegister signal\n");
	exit( 1 );
	return;
 }
 
 static void terminatedByServer(int signo )
 {
	fprintf(stderr, "%ld killed me\n", (long)sunucuPid );
	exit( 1 );
 }
 
 
 int main()
 {
	/*** Registering step ***/
	int registerFileDes = open("registerFile", O_RDWR );
	pid_t mypid = getpid();
	write(registerFileDes, &mypid, sizeof( pid_t ) );
	close( registerFileDes );
	
	int sunucuFileDes = open("sunucuPidFile", O_RDWR );
	
	read(sunucuFileDes, &sunucuPid, sizeof( pid_t ));
	close( sunucuFileDes );
	
	if( kill(sunucuPid, SIGUSR1 ) == -1 )
		perror("Failed to sending register signal\n");
	
	int id = open("sharedMemIdFifo", O_RDWR | O_SYNC );
	
	read(id, &sharedMemID, sizeof( int ) );
	
	char* shared;
		
	if ((shared = (char *)shmat(sharedMemID, NULL, 0)) == (void *)-1)
		perror("Failed to attach shared memory segment");
	
	/*** end of Registering step ***/
	
	/*** SIGNAL HANDLERS ***/
	
	struct sigaction act1;
	
	act1.sa_handler = selfTerminate;            
    act1.sa_flags = 0;
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGINT, &act1, NULL) == -1)) {
        perror("Failed to set SIGUSER1 handler");
        return 1;
    }
	
	struct sigaction act2;
	
	act2.sa_handler = terminatedByServer;            
    act2.sa_flags = 0;
    if ((sigemptyset(&act2.sa_mask) == -1) ||
          (sigaction(SIGUSR1, &act2, NULL) == -1)) {
        perror("Failed to set SIGUSR1 handler");
        return 1;
    }
	
	/*** end of SIGNAL HANDLERS ***/
	
	int fifoId = open("messageQueueFifo", O_RDWR | O_SYNC );
	
	char message[256];
	
	while( 1 )
	{
		fprintf(stderr, "FORMAT: clientNumber message");
		gets( message );
		strcpy(shared, message );
		
		write(fifoId, &mypid, sizeof( pid_t ) );
		
		if (kill(sunucuPid, SIGABRT ) == -1)
			perror("Failed to send the SIGUSR1 signal");

	}
	return 0;
 }// end of main
 
 
