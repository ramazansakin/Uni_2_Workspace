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
#include <netdb.h>
#include <time.h>
#include <math.h>
#include <semaphore.h>

//Macro Variables
#define  PORT_NUM1       1326
#define  PORT_NUM2       1327
#define MATRIX_SIZE      40
#define  HOST_NAME_LEN   255
#define  LOG_FILE        "Module1.log"
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


static int intrToClients = 0;
int threadNumber;
static int uninvertMatNum = 0;
static pthread_mutex_t smutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t smutex2 = PTHREAD_MUTEX_INITIALIZER;
char myHostName[HOST_NAME_LEN];
int verifierFd;
int multiplierFd;
int numberOfMatrices;
int queueSize;
int trace;
char IPnumMMM[20];
char IPnumVM[20];
FILE* logFile;


// functions
void matrix_print( double matrix[][MATRIX_SIZE], int dimen );
void* matrix_create( void* threadInfo  );
void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim );
void* getMatInverse( void* threadInfo );
double multiplyTwoLines(int iLIndex, int iUIndex, int iMatrixSize, double dLMatrix[][MATRIX_SIZE],
								 								    double dUMatrix[][MATRIX_SIZE]);
void* LUDecomposition( void* threadInfo );
void* signalThread( void* temp );
struct timespec timeDiffNanosec( struct timespec start, struct timespec end );

int buildConnection( unsigned short portnum);
void* sendDatas( void* infos );



// main function
int main(int argc, char *argv[]){

	double matrix[MATRIX_SIZE][MATRIX_SIZE];
	double temp[MATRIX_SIZE][MATRIX_SIZE];
	int row, column;
	sigset_t set;
	pthread_t tidSig, *tids;
	time_t t_start;
	int i , error, returnVal;
	info_t *threads;
	struct timespec startTime, endTime, diffTime;
	int thNum;

	// USAGE  CHECKING
	if( argc != 8 ){
		fprintf(stderr, "USAGE : %s  #Matrix  MatrixSize  QueueSize  #Thread  Trace  IP_MMM  IP_VM\n",argv[0] );
		fprintf(stderr, "Sample USAGE : ./MatCalcMod 10   8   10   100   1   127.0.0.1   192.168.43.6\n" );
		return 0;
	}

	clock_gettime( CLOCK_REALTIME , &startTime );
	numberOfMatrices = atoi( argv[1] );
	row = atoi( argv[2] ); 
	sprintf( IPnumMMM, "%s",argv[6] );
	sprintf( IPnumVM, "%s", argv[7] );
	threadNumber = atoi( argv[4] ); // get it from arg line
	trace = atoi( argv[5]  );
	queueSize = atoi( argv[3] );
	

	t_start = time(NULL);
	logFile = fopen(LOG_FILE, "w");
	fprintf(logFile, "Matrix generator-LU decomposer-inverser module was started to work at %s\n",ctime(&t_start) );
	fprintf(stderr, "Matrix generator-LU decomposer-inverser module was started to work at %s\n",ctime(&t_start) );

	/* blocking the signal of SIGINt( Ctrl-C signal ) for catching the signal from a spesific thread */
    sigemptyset(&set);
    sigaddset(&set, SIGINT  );
    // Block signal SIGUSR1 in this thread
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create( &tidSig, NULL, signalThread, NULL );

	srand( time(NULL) );
	thNum=numberOfMatrices;
	column = row;

	if ((tids = (pthread_t *)calloc(thNum, sizeof(pthread_t))) == NULL) {
      perror("Failed to allocate space for thread IDs");
      return 1;
    }

    if ((threads = (info_t *)calloc(thNum, sizeof(info_t))) == NULL) {
      perror("Failed to allocate space for threads");
      return 1;
    }	

    /*******************************************************************************/
    /*			RANDOM  MATRIX  GENERATOR  THREADS                                 */
    /*******************************************************************************/
    
	for(i = 0; i < thNum; i++){      /* create numthreads computethreads */  
	  threads[i].dimens = row;
      if (error =  pthread_create( tids+i, NULL, matrix_create, (void*)&threads[i] )) { 
         fprintf(stderr, "Failed to start thread %d: %s\n", i,
                 strerror(error));
         return 1;
       }
    }

    for (i = 0; i < thNum ; i++)    /* wait for computethreads to be done */
      if (error = pthread_join(tids[i], (void**)&(threads[i]) )) {
         fprintf(stderr, "Failed to join threads %d: %s\n", i, strerror(error));
         return 1;
      }

    /*******************************************************************************/
    /*			LU  DECOMPOSITION CALCULATOR  THREADS                              */
    /*******************************************************************************/
      
    for(i = 0; i < thNum; i++){      /* create numthreads computethreads */  
      if (error =  pthread_create( tids+i, NULL, LUDecomposition, (void*)&threads[i] )) { 
         fprintf(stderr, "Failed to start thread %d: %s\n", i,
                 strerror(error));
         return 1;
       }
    }

    for (i = 0; i < thNum ; i++)    /* wait for computethreads to be done */
      if (error = pthread_join(tids[i], (void**)&(threads[i]) )) {
         fprintf(stderr, "Failed to join threads %d: %s\n", i, strerror(error));
         return 1;
      }  

	/*******************************************************************************/
    /*			           INVERSE  TAKER  THREADS                                 */
    /*******************************************************************************/

    for(i = 0; i < thNum; i++){      /* create numthreads computethreads */  
        if (error =  pthread_create( tids+i, NULL, getMatInverse, (void*)&threads[i] )) { 
          fprintf(stderr, "Failed to start thread %d: %s\n", i,
                 strerror(error));
          return 1;
	    }
    }

    for (i = 0; i < thNum ; i++)    /* wait for computethreads to be done */
      if (error = pthread_join(tids[i], (void**)&(threads[i]) )) {
         fprintf(stderr, "Failed to join threads %d: %s\n", i, strerror(error));
         return 1;
      }

    //sprintf( myHostName , "%s","127.0.0.1" );	//my IP number  = 192.168.43.6

    if ( ( multiplierFd = buildConnection(  PORT_NUM1 ) ) < 0 )// to connect to multiplier  module
    	fprintf(stderr, "Connection is not established for randGenerator\n" );

    if ( ( verifierFd = buildConnection(  PORT_NUM2 ) ) < 0 )// to connect to multiplier  module
    	fprintf(stderr, "Connection is not established for randGenerator\n" );


    for(i = 0; i < thNum; i++){      /* create numthreads computethreads */  

        threads[i].fdes = multiplierFd;
        if (error =  pthread_create( tids+i, NULL, sendDatas, (void*)&threads[i] )) { 
          fprintf(stderr, "Failed to start thread %d: %s\n", i,
                 strerror(error));
          return 1;
	    }
    }      

    for (i = 0; i < thNum ; i++)    /* wait for computethreads to be done */
      if (error = pthread_join(tids[i], (void**)&(threads[i]) )) {
         fprintf(stderr, "Failed to join threads %d: %s\n", i, strerror(error));
         return 1;
      }

	clock_gettime( CLOCK_REALTIME, &endTime );
    diffTime = timeDiffNanosec( startTime, endTime );

    fprintf(stderr, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   ); 
    fprintf(logFile, "Elapsed time  :  %ld seconds %ld nanosecons\n", diffTime.tv_sec, diffTime.tv_nsec   );       
      
    close( multiplierFd );
    close( verifierFd );
    free(threads);
   	free(tids);

	return 0;
}


void* sendDatas( void* infos ){

	info_t *threadInfo = (info_t*)infos;
	int retVal, error, i;
	int matrisNum = 0;

	if (error = pthread_mutex_lock(&smutex2)){
		perror("mutex lock ");
		return NULL;
	}

	fprintf(logFile, "###--------------------------------------###\n" );
	fprintf(logFile, "Thread ID = %u\n",(unsigned int)pthread_self() );
	fprintf(logFile, "###------------  A Matrix  --------------###\n" );
	if( trace == 1 ){
		fprintf(stderr, "###--------------------------------------###\n" );
		fprintf(stderr, "Thread ID = %u\n",(unsigned int)pthread_self() );
		fprintf(stderr, "###------------  A Matrix  --------------###\n" );
		matrix_print( threadInfo->Mat, threadInfo->dimens );
		fprintf(stderr, "###--------------------------------------###\n" );
	}
	fprintf(logFile, "###--------------------------------------###\n" );

	++matrisNum;
	if( matrisNum > numberOfMatrices )
		pthread_exit( (void*)threadInfo );

	retVal = write( threadInfo->fdes, &(threadInfo->dimens) , sizeof(int) );

	/* write to multiplier */
	for( i=0; i < threadInfo->dimens ; ++i ){
		if ((retVal = write( threadInfo->fdes , threadInfo->invLMat[i] , sizeof(double)*threadInfo->dimens )) < 0){
			perror("write");
		}
	}

	for( i=0; i < threadInfo->dimens ; ++i ){
		if ((retVal = write( threadInfo->fdes , threadInfo->invUMat[i] , sizeof(double)*threadInfo->dimens ) ) < 0){
			perror("write");
		}
	}

	/* read from multiplier */
	for( i=0; i < threadInfo->dimens ; ++i )	
		if ((retVal = read( threadInfo->fdes , threadInfo->multInvLU[i] , threadInfo->dimens*sizeof(double) )) <0 )
			perror( "read = ...");

	fprintf(logFile, "###-----------  inverse of LU   -----------###\n" );	
	if( trace == 1 ){
		fprintf(stderr, "###-----------  inverse of LU   -----------###\n" );	
		matrix_print( threadInfo->multInvLU , threadInfo->dimens );		
		fprintf(stderr, "###----------------------------------------###\n" );
	}
	fprintf(stderr, "###----------------------------------------###\n" );


	retVal = write( verifierFd, &threadInfo->dimens, sizeof(int) );
	
	/* write to very */
	for( i=0; i < threadInfo->dimens ; ++i )
		write( verifierFd, threadInfo->multInvLU[i] ,  threadInfo->dimens*sizeof(double) );

	for( i=0; i < threadInfo->dimens ; ++i )
		write( verifierFd, threadInfo->Mat[i] ,  threadInfo->dimens*sizeof(double) );		

	if(error = pthread_mutex_unlock(&smutex2)){
		perror("unlock the mutex ");
		return NULL;
	}

	pthread_exit( (void*)threadInfo );
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
   if( PORT_NUM1 == portnum ){
   	  sa.sin_addr.s_addr = inet_addr(IPnumMMM); // ARG IP NUMBER
   	  if( trace ){
   	  	fprintf(stderr, "The Module  was connected to MatrixMultiplier Module\n" );
   	  }
   	  fprintf(logFile, "The Module  was connected to MatrixMultiplier Module\n" );
   }else{
   	  sa.sin_addr.s_addr = inet_addr(IPnumVM);
   	  if( trace ){
   	  	fprintf(stderr, "The Module  was connected to MatrixVerifier Module\n" );
   	  }
   	  fprintf(logFile, "The Module  was connected to MatrixVerifier Module\n" );
   }

   sa.sin_port= htons((u_short)portnum);
   
   if (connect(s , (struct sockaddr *)&sa , sizeof(sa) ) < 0 ){
       perror("Errorn in connect in buildConnection");
       close( s );
       return -1;
   }

   return s; //Send the descriptor of socket
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

// create matrix
void* matrix_create( void* threadInfo  ) {

	int i, j, error;
	info_t *threadInf = (info_t* )threadInfo;

	if (error = pthread_mutex_lock(&smutex)){
		perror("mutex lock ");
		exit(1);
	}

	for(i = 0; i < threadInf->dimens; ++i) {
		for( j = 0; j < threadInf->dimens; ++j) {
			threadInf->Mat[i][j] = fabs( (rand()%25+5)/(rand()%4+1) );
		}
	}
	if(error = pthread_mutex_unlock(&smutex)){
		perror("unlock the mutex ");
		exit(1);
	}

	pthread_exit( (void*)threadInf );
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

/* copy a matrix content to another matrix */
void arr2Dcpy( double mat1[][MATRIX_SIZE], double mat2[][MATRIX_SIZE], int dim ){

	int i, j;
	for(i = 0; i < dim; ++i) {
		for( j = 0; j < dim; ++j) {
			mat1[i][j] = mat2[i][j];
		}
	}
}

/* Gets the matrices' inverse of L and U  */
void* getMatInverse( void* threadInfo ){

	int i, j, k, t;
	double a, ratio;
	int  size, error;
	double inv[MATRIX_SIZE][MATRIX_SIZE];
	double MatCopy[MATRIX_SIZE][MATRIX_SIZE];
	info_t *thread = (info_t*)threadInfo;
	
	if (error = pthread_mutex_lock(&smutex)){
		perror("mutex lock ");
		exit(1);
	}

	for( t=0; t<2 ; ++t ){

	if( t == 0 )
		arr2Dcpy( inv, thread->LMat, thread->dimens );
	else
		arr2Dcpy( inv, thread->UMat, thread->dimens );		

	    for(i = 0; i < thread->dimens; i++){
	        for(j = thread->dimens; j < 2*thread->dimens; j++){
	            if(i==(j-thread->dimens))
	                inv[i][j] = 1.0;
	            else
	                inv[i][j] = 0.0;
	        }
	    }

	    for(i = 0; i < thread->dimens; i++){
	        for(j = 0; j < thread->dimens; j++){
	            if(i!=j){
	                ratio = inv[j][i]/inv[i][i];
	                for(k = 0; k < 2*(thread->dimens); k++){
	                    inv[j][k] -= ratio * inv[i][k];
	                }
	            }
	        }
	    }

	    for(i = 0; i < thread->dimens; i++){
	        a = inv[i][i];
	        for(j = 0; j < 2*(thread->dimens); j++){
	            inv[i][j] /= a;
	        }
	    }

	    k=0;
	    for(i = 0; i < thread->dimens; i++){
	        for(j = thread->dimens; j < 2*(thread->dimens); j++){
				inv[i][k] = inv[i][j];
	        	++k;
	        }
	        k=0;
	    }


		if( t == 0 )
			arr2Dcpy( thread->invLMat, inv , thread->dimens );
		else
			arr2Dcpy( thread->invUMat, inv, thread->dimens );

	}

	if(error = pthread_mutex_unlock(&smutex)){
		perror("unlock the mutex ");
		exit(1);
	}

    pthread_exit((void*)thread);
}

/* this function to calculate product of given index lines */
double multiplyTwoLines(int iLIndex, int iUIndex, int iMatrixSize,
								double dLMatrix[][MATRIX_SIZE],
								double dUMatrix[][MATRIX_SIZE]){
	int iI=0;			
	double dSum=0.0;	/* sum of line product */
	
	for(iI=0; iI<iMatrixSize; iI++)
		dSum += dLMatrix[iLIndex][iI]*dUMatrix[iI][iUIndex];
	/* return sum */
	return dSum;
}


/* The function calculates L nad U Matrices for LU decompositon */
void* LUDecomposition( void* threadInfo ){
	
	int iRow=0,		/* holds row number */
		iColumn=0, error;	/* holds column number */
	info_t  *thread = (info_t*)threadInfo;

	if (error = pthread_mutex_lock(&smutex)){
		perror("mutex lock ");
		exit(1);
	}

	for(iRow=0; iRow < thread->dimens ; iRow++){
		for(iColumn=0; iColumn < thread->dimens ; iColumn++){
			/* if column number is bigger than row number */
			if(iRow < iColumn){
				/* LMatrix[iRow][iColumn]  must be 0 */
				thread->LMat[iRow][iColumn] = 0.0;
				/* calculate U matrix */
				thread->UMat[iRow][iColumn] = 
					(thread->Mat[iRow][iColumn] - multiplyTwoLines(iRow,iColumn, thread->dimens ,
										 thread->LMat ,thread->UMat ) )/thread->LMat[iRow][iRow];
			}else{
				/* if column number is equal row number */
				if(iRow == iColumn){
					/* LMatrix[iRow][iColumn] must be 1*/
					thread->LMat[iRow][iColumn] = 1.0;
					/* calculate U matrix */
					thread->UMat[iRow][iColumn] = 	
						( thread->Mat[iRow][iColumn] - multiplyTwoLines(iRow,iColumn, thread->dimens ,
										thread->LMat ,thread->UMat ) )/ thread->LMat[iRow][iRow];
				/* if row number is bigger than column number */
				}else{
					/* UMatrix[iRow][iColumn] must be 0 */
					thread->UMat[iRow][iColumn] = 0.0;
					/* calculate L matrix */
					thread->LMat[iRow][iColumn] = 	
						( thread->Mat[iRow][iColumn] - multiplyTwoLines(iRow, iColumn, thread->dimens ,
										thread->LMat ,thread->UMat ) )/ thread->UMat[iColumn][iColumn];
				}
			}
		}
	}
	if(error = pthread_mutex_unlock(&smutex)){
		perror("unlock the mutex ");
		exit(1);
	}

	pthread_exit( (void*)thread );
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

