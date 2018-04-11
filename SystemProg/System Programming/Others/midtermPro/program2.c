/* Mustafa Çoker
 * 08104402
 * midterm
 * program2.c file
 * */

/* bu program yarısmada yarısacak olan program*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#ifndef PATH_MAX
#define PATH_MAX 250
#endif

// global variables
pid_t program1Pid;

// function prototypes
void record();
void getMatrix( double array[SIZE][SIZE], int size );
void processMatrix( double array1[ SIZE ][ SIZE ], double array2[ SIZE ][ SIZE ], int size );

// signals handlers
void terminatePro( int signo )
{
	fprintf(stderr, "i am killed by %ld\n", (long)program1Pid );
	
	char logName[ PATH_MAX ];
	sprintf(logName, "logFileProgram_%ld", (long) getpid() );
	FILE* logFile = fopen(logName, "a" );
	time_t tcurrent;

	tcurrent = time(NULL);

	fprintf(logFile, "program terminate time is %s\n", ctime(&tcurrent));
	fprintf(logFile, "terminated by %ld\n", (long) program1Pid );
	fclose( logFile );
	
	exit( 1 );
	return; // compile error vermesin diye koydum ama zaten buraya hic inmiyo
}// end of terminatePro

void selfTerminate( int signo )
{
	int fildes = open("unRegisterFile", O_RDWR );
	if( fildes == -1 )
	{
		perror( "failed to unreg file opening ");
		exit( 1 );
	}
	
	// burada pid temp file a gidiyo
	pid_t mypid = getpid();
	if( write(fildes, &mypid, sizeof( pid_t ) ) == -1 )
	{
		perror("failed to ");
		exit( 1 );
	}
	
	if( kill(program1Pid, SIGABRT ) == -1 )
		perror("failed signal");
	
	char logName[ PATH_MAX ];
	sprintf(logName, "logFileProgram_%ld", (long) getpid() );
	FILE* logFile = fopen(logName, "a" );
	time_t tcurrent;

	tcurrent = time(NULL);

	fprintf(logFile, "program terminate time is %s\n", ctime(&tcurrent));
	fprintf(logFile, "terminated by %ld\n", (long) getpid() );
	fclose( logFile );
	
	exit( 1 );
}

/* ================================================================= */
int main()
{
	double Matrix1[SIZE][SIZE], Matrix2[SIZE][SIZE];
	int fildesFifo = open("myfifo", O_RDWR | O_SYNC );
	
	if( fildesFifo == -1 )
	{
		fprintf(stderr, "fifo acılamadı demek ki yarıs henüz baslamamıs");
		exit( 1 );
	}
	
	char logName[ PATH_MAX ];
	sprintf(logName, "logFileProgram_%ld", (long) getpid() );
	fprintf(stderr, "%s\n", logName );
	FILE* logFile = fopen(logName, "w" );
	
	time_t tcurrent;

	tcurrent = time(NULL);
	fprintf(logFile, "program start time is %s\n", ctime(&tcurrent));
	fclose( logFile );
	
	/* ### */
	int signum = SIGUSR2; // for waiting calc signal from program1
	int signo;
	sigset_t sigset;
	
	if( sigemptyset(&sigset) == -1 ||
		sigaddset(&sigset, signum ) == -1 || 
		sigprocmask(SIG_BLOCK, &sigset, NULL ) == -1 )
		perror("Failed to block signals before sigwait");
	
	struct sigaction act1;// sigusr1 ( pro1 den gelen kill signal i)
	
	act1.sa_handler = terminatePro;            
    act1.sa_flags = 0;
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGUSR1, &act1, NULL) == -1)) {
        perror("Failed to set SIGUSER handler");
        return 1;
    }
	
	struct sigaction act2;// sigint
	
	act2.sa_handler = selfTerminate;
	act2.sa_flags = 0;
	
	if ((sigemptyset(&act2.sa_mask) == -1) ||
          (sigaction(SIGINT, &act2, NULL) == -1)) {
        perror("Failed to set SIGINThandler");
        return 1;
    }
	/* ### */
	
	
	int fildes = open("program1Pid", O_RDWR );
	if( read(fildes, &program1Pid, sizeof(pid_t) ) == -1 )
		perror("no prog1\n");
	
	/******************************************************************/
	record();// registerFile a pid gitti
	// register signal i gitti
	if( kill(program1Pid, SIGUSR2 ) == -1 )
    {
	    perror("failed");
		exit( 1 );
	}
	
	fprintf(stderr, "program signal gonderdi\n");
	
	getMatrix(Matrix1, 10);
	getMatrix(Matrix2, 10);
	
	logFile = fopen(logName, "a" );
	fprintf(logFile, "first calc time is %s\n", ctime(&tcurrent));
	fclose( logFile );
	
	int calculationNumber = 0;
	while( 1 )
	{
		if( sigwait(&sigset, &signo) == -1 )
			perror("Failed to wait using sigwait");
		
		++calculationNumber;
		processMatrix(Matrix1, Matrix2, 10);
		fprintf(stderr, "%d hesaplema finish\n", calculationNumber );
		
		pid_t mypid = getpid();
		
		
		if( (write(fildesFifo, &mypid, sizeof(pid_t) ) ) == -1 )
			perror("fifo writing error\n");
		
	}
	
	
	/******************************************************************/
	int temp;
	scanf("%d", &temp );
	fprintf(stderr, "terminating...\n\n");
	
	logFile = fopen(logName, "a" );
	fprintf(logFile, "program finish time is %s\n", ctime(&tcurrent));
	fclose( logFile );
	
	return 0;
}/* ================================================================= */

void record()
{
	pid_t mypid = getpid();
	int fildes = open("registerFile", O_RDWR );
	
	if( write( fildes, &mypid, sizeof( mypid ) ) == -1 )
		perror("error write");
		
	close( fildes );
	return;
}/********************* end of record *********************************/

void getMatrix( double array[SIZE][SIZE], int size )
{
	FILE* fPtr = fopen("MatrixFile1", "r");
	
	if( fPtr == NULL )
	{
		fprintf(stderr, "matrixFile can not open\n");
		exit( 1 );
	}
	
	int i=0, j=0;
	
	for(i=0; i<size; i++ )
		for(j=0; j<size; j++ )
			fscanf(fPtr, "%lf", &( array[i][j] ) ); 
	
	fclose( fPtr );
	
	return;
}

void processMatrix( double array1[ SIZE ][ SIZE ], double array2[ SIZE ][ SIZE ], int size )
{
	double res[ SIZE ][ SIZE ];
	
	int i=0, j=0, k=0;
	
	for (i = 0; i<size ; i++ )
		for (j = 0; j<size ; j++ )
			for(k = 0; k<size; k++ )
				res[i][j] = array1[i][k] * array2[k][j] + res[i][j];

	
	return;
}
