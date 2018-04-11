//Libraries
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <netdb.h>
#include <time.h>

//Macro Variables
#define  PORT_NUM1       1326
#define  PORT_NUM2       1327
#define MATRIX_SIZE      40
#define  HOST_NAME_LEN   255
#define  LOG_FILE        "MatrixMultiplierMaodule.log"
#define  BUFFSIZE        5
#define  BILLION         1000000000L
#define  MILLION         1000000L

typedef struct client{
	int      fdes;
	double   Mat[MATRIX_SIZE][MATRIX_SIZE];
	double   LMat[MATRIX_SIZE][MATRIX_SIZE];
	double   UMat[MATRIX_SIZE][MATRIX_SIZE];
	double   invLMat[MATRIX_SIZE][MATRIX_SIZE];
	double   invUMat[MATRIX_SIZE][MATRIX_SIZE];
	double   multInvLU[MATRIX_SIZE][MATRIX_SIZE];
	double   deter;
	int      isInver;
	int      dimens;
}info_t;

static int numberOFClient = 0;	// to hold number of client
static volatile sig_atomic_t i_doneFlag = 0;
static int intrToClients = 0;
static int count = 0;

static  pthread_mutex_t  smutex =  PTHREAD_MUTEX_INITIALIZER;
static  sem_t            semitems;
static  sem_t            semslots;
static  int  in  = 0;
static  int  out = 0;
int buffSize;
info_t *threads;
int threadNumber;
int queueSize;
int trace;
FILE* logFile;


int establish( unsigned short portNum ); //Establish Connection
void matrixMultiplier( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], double mat3[][MATRIX_SIZE], int dim );
void matrix_print( double matrix[MATRIX_SIZE][MATRIX_SIZE], int dimen );
void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim );
void matrix_print( double matrix[MATRIX_SIZE][MATRIX_SIZE], int dimen );
void* signalThread( void* temp );
struct timespec timeDiffNanosec( struct timespec start, struct timespec end );

void* threadBOSS( void* fd );
void* serveToBOSS( void* arg );


int main(int argc, char const *argv[])
{

	int serverFd, new_fd[10]; // socket descriptor 
	pthread_t tidSig,  *tids, tidBoss;
	sigset_t set;
	time_t t_start;
	info_t threadInfo; 
	int retVal, i ;
	struct timespec startTime, endTime, diffTime;

	// USAGE  CHECKING  *********
	if( argc != 4 ){
		fprintf(stderr,"USAGE : %s #Threads  QueueSize  Trace\n", argv[0] );
		fprintf(stderr, "Sample Usage : 50  20  1\n", argv[0] );
		return 0;
	}


	
	threadNumber = atoi(argv[1] );
	queueSize = atoi( argv[2] );
	buffSize = threadNumber*50;
	trace = atoi(argv[3]);

	/***  semaphores initializing *****************/
	if( sem_init( &semitems, 0, 0  ) ){
		perror("semitem init ");
		return 0;
	}
	if( sem_init( &semslots, 0, buffSize ) ){
		perror("semslot init : ");
		sem_destroy(&semitems);
		return 0;
	}

	/* blocking the signal of SIGINt( Ctrl-C signal ) for catching the signal from a spesific thread */
    sigemptyset(&set);
    sigaddset(&set, SIGINT  );
    // Block signal SIGUSR1 in this thread
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create( &tidSig, NULL, signalThread, NULL );


    // LOG_FILE  for Verifier
    t_start = time(NULL);
    logFile = fopen(LOG_FILE, "w");
	fprintf(logFile, "Matrix Multiplier Module was started to work at %s\n" , ctime(&t_start) );
	if( trace == 1 )
	fprintf(stderr, "Matrix Multiplier Module was started to work at %s\n" , ctime(&t_start) );

	//Get Connection
    if((serverFd = establish( PORT_NUM1 )) < 0){
        perror("Establish");
        return 0 ;
    }

	/**************************************************************/
	/**        GeT Thread  NUMBER FROM  TERMINAL                  */

	
	if ((tids = (pthread_t *)calloc(threadNumber*30, sizeof(pthread_t))) == NULL) {
      perror("Failed to allocate space for thread IDs");
      return 1;
    }

    if ((threads = (info_t *)calloc(threadNumber*30, sizeof(info_t))) == NULL) {
      perror("Failed to allocate space for threads");
      return 1;
    }

    for( i=0; i< threadNumber; ++i )
    	pthread_create( tids+i, NULL, serveToBOSS, (void*)&threads[i] );


	while( !intrToClients ){

		new_fd[numberOFClient] = accept(serverFd, NULL, NULL);
		
		if( intrToClients )
        	break;
		
		clock_gettime( CLOCK_REALTIME , &startTime );
		t_start=time(NULL);
		if( trace == 1 )
			fprintf(stderr, "%d.Client connected  at  %s\n",numberOFClient+1, ctime(&t_start) );
		fprintf( logFile, "%d.Client connected  at  %s\n",numberOFClient+1, ctime(&t_start) );

		pthread_create( &tidBoss, NULL, threadBOSS, &new_fd[numberOFClient] );
		++numberOFClient;
	}

	clock_gettime( CLOCK_REALTIME, &endTime );
    diffTime = timeDiffNanosec( startTime, endTime );

    fprintf(stderr, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   ); 
    fprintf(logFile, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   ); 



	close(serverFd);
	free(tids);
	free(threads);
	return 0;
}


void* threadBOSS( void* fd ){

	int *fileDes = (int*)fd;
	int error, returnVal,  i;
	pthread_detach(pthread_self());
	int dim;
	info_t tempI ;

	while( 1 ){

		while( (( error = sem_wait(&semslots) ) == -1 ) && (errno == EINTR ) );
		if( error ){
			break;
		}

		if ((returnVal = read( *fileDes , &dim , sizeof(int) )) < 0 )
			perror("returnVal " );
		
		if( returnVal <= 0 ){
			break;
		}

		if( error = pthread_mutex_lock( &smutex ) ){
			break;
		}

		for( i=0; i<dim; ++i  )
			read( *fileDes, tempI.invLMat[i] , dim*sizeof(double));

		for( i=0; i<dim; ++i )
			read( *fileDes, tempI.invUMat[i] , dim*sizeof(double));

		tempI.dimens = dim;
		tempI.fdes = *fileDes;
		threads[in] = tempI;
		in = ( in + 1 )%buffSize;
		
		if( error = pthread_mutex_unlock(&smutex) ){
			break;
		}

		if( sem_post( &semitems) == -1 ){
			break;
		}
		
	}

	close(*fileDes);
	pthread_exit(NULL);
}


void* serveToBOSS( void* arg ){

	int returnVal, error, i;
	pthread_detach(pthread_self());

	while( !intrToClients ){

		while( (( error = sem_wait(&semitems) ) == -1 ) && (errno == EINTR ) );
		if( error )
			return NULL;

		if( error = pthread_mutex_lock( &smutex ) )
			return NULL;

		matrixMultiplier( threads[out].invUMat, threads[out].invLMat, threads[out].multInvLU, threads[out].dimens );
		
		fprintf(logFile, "###------------  Inverse Of LU ------------###\n" );		
		if( trace == 1 ){
			fprintf(stderr, "###------------  Inverse Of LU ------------###\n" );
			matrix_print( threads[out].multInvLU, threads[out].dimens );
			fprintf(stderr, "###----------------------------------------###\n" );
		}
		fprintf(logFile, "###----------------------------------------###\n" );

		fprintf(logFile, "###------------  Inverse Of U Matrix ------------###\n" );		
		if( trace == 1 ){
			fprintf(stderr, "###------------  Inverse Of U Matrix ------------###\n" );
			matrix_print( threads[out].invUMat, threads[out].dimens );
			fprintf(stderr, "###----------------------------------------###\n" );
		}
		fprintf(logFile, "###----------------------------------------###\n" );


		for( i=0; i < threads[out].dimens ; ++i )
			write( threads[out].fdes, threads[out].multInvLU[i] ,  threads[out].dimens*sizeof(double) );

		out = ( out + 1 )%buffSize;

		if( error = pthread_mutex_unlock(&smutex) )
			return NULL;
		if( sem_post( &semslots) == -1 )
			return NULL;

	}

	pthread_exit( NULL );
}

// print matrix
void matrix_print( double matrix[MATRIX_SIZE][MATRIX_SIZE], int dimen ) {
	int i, j;

	if( trace == 1 ){
		for( i = 0; i < dimen; ++i  ){
			for( j=0; j < dimen; ++j ){
				fprintf(stderr,"%-9.3f", matrix[i][j]);
			}
			fprintf(stderr,"\n");
		}
	}
	for( i = 0; i < dimen; ++i  ){
		for( j=0; j < dimen; ++j ){
			fprintf(logFile,"%-9.3f", matrix[i][j]);
		}
		fprintf(logFile,"\n");
	}

}


/**
  Signal catcher Thread for catch the SIGINT signal( CTRL-C signal )
  @param temp : holds nothing( unrequired data )
*/
void* signalThread( void* temp ){

   sigset_t set;
   int sig;

   sigemptyset(&set);
   sigaddset(&set, SIGINT);
   pthread_detach(pthread_self());
   // Block signal SIGINT in this thread
   pthread_sigmask(SIG_BLOCK, &set, NULL);
   
   sigwait( &set, &sig);
   intrToClients=1;
   fprintf(stderr, "Ctrl-C has come...\n" );
   fprintf(logFile, "Ctrl-C has come...\n" );

   pthread_exit(NULL);
}


void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim ){

	int i, j;
	for(i = 0; i < dim; ++i) {
		for( j = 0; j < dim; ++j) {
			mat1[i][j] = mat2[i][j];
		}
	}
}


/* Multiplies two matrix and holds the result matrix */
void matrixMultiplier( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], double mat3[][MATRIX_SIZE], int dim ){

  int i, j, k;

  for(i=0;i<dim;i++){
	for(j=0;j<dim;j++){
		mat3[i][j]=0;
		for(k=0;k<dim;k++){
			mat3[i][j]+=mat1[i][k]*mat2[k][j];
		}
	}
  }

}


//Establish Connection
int establish(unsigned short portNum){

    int socketfd;
    struct sockaddr_in sa;

    //Build Socket
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    	perror("socket in establish ");
        return(-1);
    }

    memset(&sa, 0, sizeof(struct sockaddr_in)); //Clear our address
    sa.sin_family= AF_INET; //Our host address
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port= htons(portNum); //Our port number

    //Bind address to socket
    if (bind(socketfd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0){
        close(socketfd);
        perror("bind in establish ");
        return(-1); 
    }
    
    listen(socketfd, 5); //Max num of cliets in the queue
    
    return socketfd;
}

struct timespec timeDiffNanosec( struct timespec start, struct timespec end ){
	
	struct timespec result;

	if(end.tv_sec == start.tv_sec){
		result.tv_sec = 0;
		result.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	else{
		result.tv_sec = end.tv_sec - start.tv_sec - 1;
		result.tv_nsec = BILLION - start.tv_nsec + end.tv_nsec;
		if(result.tv_nsec > BILLION){
			++(result.tv_sec);
			result.tv_nsec -= BILLION;
		}
	}

	return result;
}



