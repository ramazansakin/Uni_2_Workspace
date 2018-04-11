//Libraries

// MY  IP ADDr = 192.168.43.6

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
#include <netdb.h>
#include <time.h>
#include <semaphore.h>
#include <math.h>

//Macro Variables
#define  PORT_NUM1       1326
#define  PORT_NUM2       1327
#define  HOST_NAME_LEN   255
#define  LOG_FILE        "VerifierModule.log"
#define  MATRIX_SIZE     40
#define  BILLION         1000000000L
#define  MILLION         1000000L


typedef struct client{
	int     fdes;
	double  Mat[MATRIX_SIZE][MATRIX_SIZE];
	double  LMat[MATRIX_SIZE][MATRIX_SIZE];
	double  UMat[MATRIX_SIZE][MATRIX_SIZE];
	double  invLMat[MATRIX_SIZE][MATRIX_SIZE];
	double  invUMat[MATRIX_SIZE][MATRIX_SIZE];
	double  multInvLU[MATRIX_SIZE][MATRIX_SIZE];
	double  deter;
	int     isInver;
	int     dimens;
}info_t;


static int numberOFClient = 0;	// to hold number of client
static int intrToClients = 0;
static int invertinleNum = 0;
static int unInvertibleNum = 0;

info_t *threads;
static pthread_mutex_t  smutex =  PTHREAD_MUTEX_INITIALIZER;
static sem_t            semitems;
static sem_t            semslots;
static int  in  = 0;
static int  out = 0;
int buffSize;
int threadNumber;
int socketMAtMultFd;
int queueSize ;
char IP_MMM[20];
FILE* logFile;
int trace;
static int unInvIndex ;


//void* verifyMatResult( void* arg );
void* signalThread( void* temp );
int buildConnection( unsigned short portnum);
int establish(unsigned short portNum);
void matrix_print( double matrix[MATRIX_SIZE][MATRIX_SIZE], int dimen );
void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim );
int isIdentityMatrix( double mat[MATRIX_SIZE][MATRIX_SIZE], int size );
struct timespec timeDiffNanosec( struct timespec start, struct timespec end );
double compute_determinant(double matrix[][MATRIX_SIZE], int sizeOfMat );

void* threadBOSS( void* fd );
void* serveToBOSS( void* arg );


int main( int argc, char const *argv[] ){

	int socketFd, new_fd[10];
	time_t t_start;	
	sigset_t set;	
	pthread_t tidSig, *tids, tidBoss;
	int count = 0, i;
	struct timespec startTime, endTime, diffTime;

  //  USAGE  CHECKING
  if( argc != 5 ){
     fprintf(stderr, "USAGE : %s  #Threads  Queue Size  IP1 Trace\n", argv[0] ); 
     fprintf(stderr, "Sample USAGE : %s  50   20  127.0.0.1  1\n", argv[0] );
     return 0;
  }

    clock_gettime( CLOCK_REALTIME , &startTime );
    /* blocking the signal of SIGINt( Ctrl-C signal ) for catching the signal from a spesific thread */
    sigemptyset(&set);
    sigaddset(&set, SIGINT  );
    // Block signal SIGUSR1 in this thread
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create( &tidSig, NULL, signalThread, NULL );


  	t_start = time(NULL);
  	logFile = fopen(LOG_FILE, "w");
  	fprintf(logFile, "Verifier was started to work at %s\n",ctime(&t_start) );
    fprintf(stderr, "Verifier was started to work at %s\n",ctime(&t_start) );

  	/************************************************/
  	threadNumber = atoi(argv[1]); // GET FROM  ARG LINE THREAD NUMBER
    buffSize = threadNumber*50;
    queueSize =  atoi( argv[2] );
    sprintf( IP_MMM, "%s", argv[3] );
    trace = atoi( argv[4]);

    /***  semaphores initializing *****************/
    threadNumber=300;
    if( sem_init( &semitems, 0, 0  ) ){
      perror("semitems init ");
      return 0;
    }
    
    if( sem_init( &semslots, 0, buffSize ) ){
      perror("semslots init : ");
      sem_destroy(&semitems);
      return 0;
    }

    /*    Threads  Id allocations acc to  ID number                          */
  	if ((tids = (pthread_t *)calloc(threadNumber, sizeof(pthread_t))) == NULL) {
        perror("Failed to allocate space for thread IDs");
        return 1;
    }

    /*   Buffer allocation for threads according to thread number  */
    if ((threads = (info_t *)calloc(threadNumber, sizeof(info_t))) == NULL) {
      perror("Failed to allocate space for threads");
      return 1;
    }

  	//Get Connection
    if((socketFd = establish(PORT_NUM2)) < 0){
        perror("Establish");
        return 0 ;
    }

    socketMAtMultFd = buildConnection( PORT_NUM1 );

    for( i=0; i< threadNumber; ++i ){
     if ( pthread_create( tids+i, NULL, serveToBOSS, (void*)&threads[i] ) == -1 )
     	perror("thread : ");
    }


    while( !intrToClients ){

      new_fd[count] = accept(socketFd, NULL, NULL);
      clock_gettime( CLOCK_REALTIME, &endTime );

      if( intrToClients )
        break;

      fprintf(stderr, "%d.Client connected...\n", numberOFClient );
      pthread_create( &tidBoss, NULL, threadBOSS, &new_fd[count] );

    	++count;
    	++numberOFClient;
    }

    clock_gettime( CLOCK_REALTIME, &endTime );
    diffTime = timeDiffNanosec( startTime, endTime );

    if( trace == 1 ){
	    fprintf(stderr, "Number of all marices is %d\n", invertinleNum+unInvertibleNum );
	    fprintf(stderr, "Number of invertible marices is %d\n", invertinleNum );
	    fprintf(stderr, "Number of uninvertible matrices is %d\n", unInvertibleNum );
	}
	fprintf(logFile , "Number of all marices is %d\n", invertinleNum+unInvertibleNum );
	fprintf(logFile , "Number of invertible marices is %d\n", invertinleNum );
	fprintf(logFile , "Number of uninvertible matrices is %d\n", unInvertibleNum );

    fprintf(stderr, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   ); 
    fprintf(logFile, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   ); 
  

	  close(socketFd);
	  free(threads);
	  free(tids);

	return 0;
}

void* threadBOSS( void* fd ){

  int *fileDes = (int*)fd;
  int error, returnVal,  i;
  pthread_detach( pthread_self() );
  int dim;
  int check;

  while( 1 ){

    while( (( error = sem_wait(&semslots) ) == -1 ) && (errno == EINTR ) );
    if( error )
      return NULL;

    returnVal = read( *fileDes , &dim , sizeof(int) );
    for( i=0; i<threadNumber ; ++i )
      threads[i].dimens = dim;

    if( returnVal <= 0 )
      return NULL;


    if( error = pthread_mutex_lock( &smutex ) )
      return NULL;


    for( i=0; i<dim; ++i )
      read( *fileDes, threads[in].multInvLU[i] , dim*sizeof(double));
    

    for( i=0; i<dim; ++i  )
      read( *fileDes, threads[in].Mat[i] , dim*sizeof(double));

    if(  threads[in].multInvLU[0][0] != threads[in].multInvLU[0][0]     ){
        fprintf(stderr, " ---------------------------    %f\n",threads[in].multInvLU[0][0] );
        sleep(1);
        unInvIndex = in;
     }

    in = ( in + 1 )%buffSize;
    
    if( error = pthread_mutex_unlock(&smutex) )
      return NULL;
    if( sem_post( &semitems) == -1 )
      return NULL;
    
  }

  close(*fileDes);
  pthread_exit(NULL);
}

void* serveToBOSS( void* arg ){


  int retVal, error;
  pthread_detach(pthread_self());
  int check, i;
  info_t temp;

  while( !intrToClients ){

    while( (( error = sem_wait(&semitems ) ) == -1 ) && (errno == EINTR ) );
    if( error )
      return NULL;

    if( error = pthread_mutex_lock( &smutex ) )
      return NULL;

    write( socketMAtMultFd , &threads[out].dimens, sizeof(int) );


    for( i=0; i < threads[out].dimens ; ++i )
      retVal= write( socketMAtMultFd , threads[out].Mat[i] , sizeof(double)*threads[out].dimens );

    for( i=0; i < threads[out].dimens ; ++i )
      retVal= write( socketMAtMultFd , threads[out].multInvLU[i] , sizeof(double)*threads[out].dimens );
    
    /* read from multiplier */
    for( i=0; i < threads[out].dimens ; ++i )
      read( socketMAtMultFd , temp.Mat[i] , sizeof(double)*threads[out].dimens );



    check = isIdentityMatrix( temp.Mat , threads[out].dimens );

    fprintf(logFile, "###---- Result of Multiplication A and A' -----------###\n" );
    if( trace == 1 ){
      fprintf(stderr, "###---- Result of Multiplication A and A' -----------###\n" );
      matrix_print( temp.Mat, threads[out].dimens );
      fprintf(stderr, "###--------------------------------------------------###\n" );
    }
    fprintf(logFile, "###--------------------------------------------------###\n" );


    if( check == 1 ){
      if( trace == 1 )
          fprintf(stderr, "The Matrix is invertible!!\n" );
      fprintf(logFile, "The Matrix is invertible!!\n" ); 
      ++invertinleNum;
    }else{
      if( trace == 1 ){
          fprintf(stderr, "The Matrix is not invertible!!\n" );
          fprintf(stderr, "#################### uninvertible  A Matrix   #####################\n" );    
      }

      fprintf(logFile,    "################## uninvertible  A Matrix   #######################\n" );
      matrix_print( threads[unInvIndex].Mat, threads[out].dimens );
      fprintf(logFile,    "###################################################################\n" );
      
      if( trace == 1 )
          fprintf(stderr, "###################################################################\n" );  

      fprintf(logFile, "The Matrix is not invertible!!\n" );
        ++unInvertibleNum;
    }

    out = ( out + 1 )%buffSize;

    if( error = pthread_mutex_unlock(&smutex) )
      return NULL;
    if( sem_post( &semslots ) == -1 )
      return NULL;

  }


  pthread_exit( NULL );
}

double compute_determinant( double matrix[][MATRIX_SIZE], int sizeOfMat ) {

  double sumOfDeterminant = 0;  // to avoid from garbagge values, result of Determinant
    int i, j;
    int size, colN;
  double subMats[MATRIX_SIZE][MATRIX_SIZE]; /* minors of the matrix */
  
  if( sizeOfMat <= 0 ){ //MATRIX_SIZE <= 0
    printf("Matrix dimension can not be 0 or neagative!\n");
    exit(0);
  }else if( sizeOfMat == 1 )    //MATRIX_SIZE == 1
    return matrix[0][0];
    else if (sizeOfMat == 2)    //MATRIX_SIZE == 2
        sumOfDeterminant = matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    else{
        sumOfDeterminant = 0; //sum of all minors 2x2 matrixes
        
      for (size = 0 ; size < sizeOfMat ; size++){ // creates sub matrix and calculate determinant all of them 
        /* Create sub matrixes and adds them all to sumOfDeterminant */
          for (i = 1 ; i < sizeOfMat ; i++){
            colN = 0;
            for (j = 0; j < sizeOfMat; j++){
                
                if (j != size){ // if the value matrix[i][j] is not the same col, takes it to subMatrix  
                    subMats[i-1][colN] = matrix[i][j];
                    colN++;   // increase the col number
                  }
          }
            }

            // calculate the determinant the matrix and call the function again until to be minor matrixes
            // and add them all to sumOfDeterminant
          sumOfDeterminant += pow(-1.0, size)*matrix[0][size]*compute_determinant( subMats, sizeOfMat-1); 
          }
    }
  // return sum of all results  
  return sumOfDeterminant;
}

int isIdentityMatrix( double mat[MATRIX_SIZE][MATRIX_SIZE], int size ){
  int i,j;
  double sum=0;

  for(i=0 ; i < size; ++i)
    for(j=0 ; j < size; ++j){
      sum += mat[i][j];
    }

    if(sum <= (size + 0.000001) && sum >= (size - 0.000001))
      return 1;
  
  return 0;
}


void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim ){

  int i, j;
  for(i = 0; i < dim; ++i) {
    for( j = 0; j < dim; ++j) {
      mat1[i][j] = mat2[i][j];
    }
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

//Build connection and connect to servers
int buildConnection( unsigned short portnum){

   struct sockaddr_in sa;
   int s; //Socket descriptor

   if ((s = socket( AF_INET , SOCK_STREAM,0)) < 0){ //et socket
       perror("Error in socket buildCon :");
       return -1;
   }
    
   memset(&sa, 0 ,sizeof(sa) );

   sa.sin_family= AF_INET;
   sa.sin_addr.s_addr = inet_addr(IP_MMM); // ARG IP NUMBER
   sa.sin_port= htons((u_short)portnum);
   

   if (connect(s , (struct sockaddr *)&sa , sizeof(sa) ) < 0 ){
       perror("Errorn in connect in buildConnection");
       close( s );
       return -1;
   }

   return s; //Send the descriptor of socket
}

//Establish Connection
int establish(unsigned short portNum)
{
    char myHost[HOST_NAME_LEN];
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

