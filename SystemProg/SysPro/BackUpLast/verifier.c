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


//Macro Variables
#define  PORT_NUM1       1094
#define  PORT_NUM2       1095
#define  HOST_NAME_LEN   255
#define  HOST_NAME       "myPrivateHost"	// to set the host name
#define  LOG_FILE        "VerifierModule.log"
#define  MATRIX_SIZE     40


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

//void* verifyMatResult( void* arg );
void* signalThread( void* temp );
int buildConnection( unsigned short portnum);
int establish(unsigned short portNum);
void matrix_print( double matrix[MATRIX_SIZE][MATRIX_SIZE], int dimen );
void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim );
int isIdentityMatrix( double mat[MATRIX_SIZE][MATRIX_SIZE], int size );

void* threadBOSS( void* fd );
void* serveToBOSS( void* arg );


int main( int argc, char const *argv[] ){

	int socketFd, new_fd[10];
	time_t t_start;	
	sigset_t set;	
	pthread_t tidSig, *tids, tidBoss;
	int count = 0, i;

	
  //  USAGE  CHECKING
  if( argc != 5 ){
     fprintf(stderr, "USAGE : %s  #Threads  Queue Size  IP1 Trace\n", argv[0] ); 
     fprintf(stderr, "Sample USAGE : %s  50   20  127.0.0.1  1\n", argv[0] );
     return 0;
  }


    /* blocking the signal of SIGINt( Ctrl-C signal ) for catching the signal from a spesific thread */
    sigemptyset(&set);
    sigaddset(&set, SIGINT  );
    // Block signal SIGUSR1 in this thread
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create( &tidSig, NULL, signalThread, NULL );


  	t_start = time(NULL);
  	logFile = fopen(LOG_FILE, "w");
  	fprintf(logFile, "Verifier was started to work at %s\n",ctime(&t_start) );

  	/************************************************/
  	threadNumber = atoi(argv[1]); // GET FROM  ARG LINE THREAD NUMBER
    buffSize = threadNumber;
    queueSize =  atoi( argv[2] );
    sprintf( IP_MMM, "%s", argv[3] );
    trace = atoi( argv[4]);

    /***  semaphores initializing *****************/
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

    for( i=0; i< threadNumber; ++i )
      pthread_create( tids+i, NULL, serveToBOSS, (void*)&threads[i] );


    while( !intrToClients ){

      new_fd[count] = accept(socketFd, NULL, NULL);
      fprintf(stderr, "Client connect fdes = %d\n", new_fd[count] );
      pthread_create( &tidBoss, NULL, threadBOSS, &new_fd[count] );

    	++count;
    	++numberOFClient;
    }


 
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

    fprintf(logFile, "###---- Result of Multiplication A and A'(Identity) -----------###\n" );
    if( trace == 1 ){
      fprintf(stderr, "###---- Result of Multiplication A and A'(Identity) -----------###\n" );
      matrix_print( temp.Mat, threads[out].dimens );
      fprintf(stderr, "###------------------------------------------------------------###\n" );
    }
    fprintf(logFile, "###-------------------------------------------------------------###\n" );


    if( check == 1 ){
      if( trace == 1 )
          fprintf(stderr, "The Matrix is invertible!!\n" );
      fprintf(logFile, "The Matrix is invertible!!\n" ); 
    }else{
      if( trace == 1 ){
          fprintf(stderr, "The Matrix is not invertible!!\n" );
          fprintf(stderr, "#################### uninvertible  A Matrix   #####################\n" );    
      }

      fprintf(logFile,    "################## uninvertible  A Matrix   #######################\n" );
      matrix_print( threads[out].Mat, threads[out].dimens );
      fprintf(logFile,    "###################################################################\n" );
      
      if( trace == 1 )
          fprintf(stderr, "###################################################################\n" );  

      fprintf(logFile, "The Matrix is not invertible!!\n" );
        
    }

    out = ( out + 1 )%buffSize;

    if( error = pthread_mutex_unlock(&smutex) )
      return NULL;
    if( sem_post( &semslots ) == -1 )
      return NULL;

  }


  pthread_exit( NULL );
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
   sa.sin_addr.s_addr = inet_addr("127.0.0.1"); // ARG IP NUMBER
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

