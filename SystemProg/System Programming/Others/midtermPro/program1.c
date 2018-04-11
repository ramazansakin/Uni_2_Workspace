/* 08104402 Mustafa Coker
 * midterm
 * System Programming
 * program1.c
 * */

/* bu program yarısmanın organizasyonunu yapıyo */

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

#define FIFO_PERMS  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#ifdef PATH_MAX
#undef PATH_MAX
#endif
#define PATH_MAX 250

static volatile sig_atomic_t competitor[20];
static volatile sig_atomic_t competitorOfNumber = 0;
static volatile sig_atomic_t finishedComp = 0;
static volatile sig_atomic_t maxCompetitor = 0;

void writePid();
void createRegisterFile();
void createUnRegisterFile();
void createRandomMatrixFile();
void copyFile(char* sourcePath, char* targetPath);

/* ===== signals handlers ====== */

static void registeProgram2( int signo )
{
	if( competitorOfNumber >= maxCompetitor )
	{
		fprintf(stderr, "no more competitor can register\n");
		return;
	}
	
	int fildes = open("registerFile", O_RDWR );
	FILE *logFilePtr = fopen("logFilePro1.txt", "a");// log a eklemek icin
	
	if( logFilePtr == NULL )
	{
		fprintf(stderr, "log file error\n" );
		exit( 1 );
	}
	
	if( fildes  == -1 )
		perror("register file not opened");
	
	pid_t temp;
	if ( read(fildes, &temp, sizeof( pid_t ) ) == -1 )
		perror("reading error");
	
	competitor[ competitorOfNumber ] = temp;
	++competitorOfNumber;
	fprintf(stderr, "%ld has registered yet\n", (long) temp );
	
	fprintf(logFilePtr, "%d. competitor is %ld\n", competitorOfNumber, (long) temp );
	fclose( logFilePtr );
	
	if( close( fildes ) == -1 )
		perror( "register file not closed");
		
	fclose( fopen("registerFile", "wb") );
	
	if( competitorOfNumber >= 3 )
		raise( SIGUSR1 );
	
	return;
}// end of registerProgram2 handler

static void terminateAllProgram(int signo )
{
	int i=0;
	
	for(i=0; i<competitorOfNumber; i++ )
	{
		if( kill(competitor[ i ], SIGUSR1 ) == -1 )
			perror("failed");
	}
	
	if (unlink("myfifo") == -1)
	   perror("Failed to remove myfifo");
	
	remove("program1Pid");
	remove("registerFile");
	remove("unRegisterFile");
	
	FILE *logFilePtr = fopen("logFilePro1.txt", "a");
	fprintf(logFilePtr, "someone send me kill signal\n");
	fclose( logFilePtr );
	
	exit( 1 );
}// end of terminate all program handler

void unRegisterPro2()
{
	int fildes = open("unRegisterFile", O_RDWR );
	
	if( fildes == -1 )
	{
		perror("failed to opening unRegisterFile\n");
		exit( 1 );
	}
	
	pid_t killedProgram2;
	
	if( read(fildes, &killedProgram2, sizeof( pid_t ) ) == -1 )
		perror("failed unRegister\n");
	else	
		fprintf(stderr, "*** unregistering %ld\n\n", (long)killedProgram2 );
	
	int i=0;
	int controlNum=1;
	
	for(i=0; i<competitorOfNumber; i++ )
	{
		if( controlNum )
		{
			if( competitor[i] == killedProgram2 )
				controlNum = 0;
		}
		else
			competitor[i-1] = competitor[i];
	}
	--competitorOfNumber;
	
	for(i=0; i<competitorOfNumber; i++ )
		fprintf(stderr, "%d %ld\n", i, (long)competitor[i] );
	
	return;
}// end of unRegisterPro2 handler
/**************               HANDLER FINISHED HERE         ***********/

int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		fprintf(stderr, "usage : %s numberOfCalc maxCompetitor\n", argv[0] );
		return 1;
	}
	
	FILE* fPtr1 = fopen("MatrixFile1", "w");
	FILE* fPtr2 = fopen("MatrixFile2", "w");
	
	fclose( fPtr1 );
	fclose( fPtr2 );
	
	maxCompetitor = atoi( argv[ 2 ] );
	int numberOfCalc = atoi( argv[ 1 ] );
	
	fprintf(stderr, "%ld\n", (long)getpid() );
	
	// logfile a baslangıc anı yazıldı
	FILE *logFilePtr = fopen("logFilePro1.txt", "w");
	
	time_t tcurrent;

	tcurrent = time(NULL);
	fprintf(logFilePtr, "organizator Pid %ld\n", (long)getpid() );
	fprintf(logFilePtr, "program start time is %s\n", ctime(&tcurrent));
	fclose( logFilePtr );
	
	if (mkfifo("myfifo", FIFO_PERMS) == -1)
		perror("Failed to create myfifo");
		
	int fd = open("myfifo", O_RDWR | O_SYNC );
	
	if( fd == -1 )
	{
		perror( "failed fifo \n");
		return 1;
	}
	
	createRandomMatrixFile();
	
	/* ### */
	int signum = SIGUSR1; // for waiting minimum competitor
	int signo;
	sigset_t sigset;
	
	if( sigemptyset(&sigset) == -1 ||
		sigaddset(&sigset, signum ) == -1 || 
		sigprocmask(SIG_BLOCK, &sigset, NULL ) == -1 )
		perror("Failed to block signals before sigwait");
	
	// register signal ini handle eden sigaction
	struct sigaction act1;
	
	act1.sa_handler = registeProgram2;            
    act1.sa_flags = 0;
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGUSR2, &act1, NULL) == -1)) {
        perror("Failed to set SIGUSER handler");
        return 1;
    }
    
    // ctrl + c signalini handle eden sigaction
    struct sigaction act2;
    
    act2.sa_handler = terminateAllProgram;
    act2.sa_flags = 0;
    if ((sigemptyset(&act2.sa_mask) == -1) ||
          (sigaction(SIGINT, &act2, NULL) == -1)) {
        perror("Failed to set SIGINT handler");
        return 1;
    }
	
	// program2 inin kill olmasıyla gelen signal in handle eden sigaction
	struct sigaction act3;
	
	act3.sa_handler = unRegisterPro2;
	act3.sa_flags = 0;
	
	if ((sigemptyset(&act3.sa_mask) == -1) ||
          (sigaction(SIGABRT, &act3, NULL) == -1)) {
        perror("Failed to set SIGABRT handler");
        return 1;
    }
    /* ### */
    
	/******************************************************************/
	
	createRegisterFile();
	createUnRegisterFile();
	writePid();
	
	while( competitorOfNumber < 3 )
	{
		if( sigwait(&sigset, &signo) == -1 )
			perror("Failed to wait using sigwait");
	}
	
	int i=0, j=0;
	
	logFilePtr = fopen("logFilePro1.txt", "a");

	tcurrent = time(NULL);
	fprintf(logFilePtr, "calculation start time is %s\n", ctime(&tcurrent));
	fclose( logFilePtr );
	
	for(j=0; j < numberOfCalc; j++ )
	{
		while( competitorOfNumber < 3 )
		{
			if( sigwait(&sigset, &signo) == -1 )
				perror("Failed to wait using sigwait");
		}
		
		for(i=0; i<competitorOfNumber; i++ )
		{
			if( kill(competitor[ i ], SIGUSR2 ) == -1 )
				perror("failed");
		}
		
		int lastRegisteredComp = competitorOfNumber;
		while( finishedComp < lastRegisteredComp )
		{
			pid_t temp = 0;
			
			if( ( read(fd, &temp, sizeof( pid_t ) ) ) == -1 )
				perror("reading error\n");
			
			++finishedComp;
		}
		
		fprintf(stderr, "%d. yarıs bitti\n", j+1);
		
		finishedComp = 0;
	}
	
	/******************************************************************/
	
	for(i=0; i<competitorOfNumber; i++ )
		fprintf(stderr, "%ld\n", (long)competitor[ i ] );
	
	fprintf(stderr, "terminating All program...!\n");
	
	// program1 biterken tüm yarısmacılara ctrl c signali gönderip
	// terminate ettiriyo
	for(i=0; i<competitorOfNumber; i++ )
	{
		if( kill(competitor[ i ], SIGUSR1 ) == -1 )
			perror("failed");
	}
	
	if (unlink("myfifo") == -1)
	   perror("Failed to remove myfifo");
	
	remove("program1Pid");
	remove("registerFile");
	remove("unRegisterFile");
	
	logFilePtr = fopen("logFilePro1.txt", "a+");

	tcurrent = time(NULL);
	fprintf(logFilePtr, "program finish time is %s\n", ctime(&tcurrent));
	fclose( logFilePtr );
	
	return 0;
}/* ================================================================= */

void writePid()
{
	fclose( fopen("program1Pid", "wb") );

	pid_t mypid = getpid();
	int fildes = open("program1Pid", O_RDWR );
	write(fildes, &mypid, sizeof(pid_t) );

	close( fildes );
	
	return;
}/*************************** end of writePid function ****************/

void createRegisterFile()
{
	fclose( fopen("registerFile", "wb") );
	
	return;
}/********************** end of createRegisterFile ********************/

void createUnRegisterFile()
{
	fclose(fopen("unRegisterFile", "wb") );
	
	return;
}/******************** end of unRegisterFile **************************/

void createRandomMatrixFile()
{
	char mycwd[ PATH_MAX ];
	char pooldirPath[ PATH_MAX ];
	char matrix1[ PATH_MAX ];
	char matrix2[ PATH_MAX ];
	char source[ PATH_MAX ];
	struct dirent* direntDirector;
	DIR* poolDir;
	int i=0;
	
	if (getcwd(mycwd, PATH_MAX) == NULL) {
        perror("Failed to get current working directory");
        return;
    }
    sprintf(pooldirPath, "%s/pool", mycwd );
    sprintf(matrix1, "%s/MatrixFile1", mycwd );
    sprintf(matrix2, "%s/MatrixFile2", mycwd );
    
    int randomNumber=0;
    srand( time(NULL) );
    
    randomNumber = rand() % 10;
    randomNumber++;
    poolDir = opendir( pooldirPath );
	
	if(poolDir == NULL )
	{
		fprintf(stderr, "havuz bulunamadı\n");
		exit( 1 );
	}
	
    for(i=0; i<randomNumber; i++ )
    {
		direntDirector = readdir( poolDir );
	}
	rewinddir( poolDir );
	
	while( strcmp(direntDirector->d_name, ".") == 0 || strcmp(direntDirector->d_name, "..") == 0 )
	{
		randomNumber = rand() % 10;
		randomNumber++;
		for(i=0; i<randomNumber; i++ )
		{
			direntDirector = readdir( poolDir );
		}
		rewinddir( poolDir );
	}
	rewinddir( poolDir );
	
	sprintf(source, "%s/%s", pooldirPath, direntDirector->d_name );
	fprintf(stderr, "%s\n", source );
	copyFile( source, matrix1 );
	
	randomNumber = rand() % 10;
    randomNumber++;
	
	for(i=0; i<randomNumber; i++ )
    {
		direntDirector = readdir( poolDir );
	}
	rewinddir( poolDir );
	
	while( strcmp(direntDirector->d_name, ".") == 0 || strcmp(direntDirector->d_name, "..") == 0 )
	{
		randomNumber = rand() % 10;
		randomNumber++;
		for(i=0; i<randomNumber; i++ )
		{
			direntDirector = readdir( poolDir );
		}
		rewinddir( poolDir );
	}
	rewinddir( poolDir );
	
	sprintf(source, "%s/%s", pooldirPath, direntDirector->d_name );
	fprintf(stderr, "%s\n", source );
	copyFile(source, matrix2 );
	
	closedir( poolDir );
	
	return;
}

void copyFile(char* sourcePath, char* targetPath)
 {
	// bayt bayt kopyaladım
	
	fprintf(stderr, "item copying\n");
	fclose( fopen(targetPath, "w") );
	pid_t targetFile, sourceFile; // for read write
	char *buf = malloc( sizeof( char ) );
	int readVal=0;
	
	targetFile = open(targetPath, O_RDWR );
	sourceFile = open(sourcePath, O_RDWR );
	
	do
	{
		readVal = read(sourceFile, buf, sizeof( char ) );
		if( readVal != 0 )
			write(targetFile, buf, sizeof( char ) );
		
	}while( readVal != 0 );
	
	fprintf(stderr, "copied\n");
 }/******************* END OF copyFile FUNCTION ***********************/
