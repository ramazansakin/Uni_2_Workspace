 
 /* System programming HW #4 
  * 08104402 sonuna ekle
  * Mustafa Çoker
  * */
 
 #include <stdio.h>
 #include <pthread.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <sys/stat.h>
 #define MAX_PATH 256
 
 void *countFileRow( void *arg );
 int getFileColumnNumber( int fildes );
 void createTemp_fromTargetLocation(int fildes, int file1columnNumber );
 void addFile( int fildes );
 void *createTempFromFile2( void * arg );
 void *updateFile2( void * arg );
 void copyFile(char* sourcePath, char* targetPath);
 
 /* global file path variable */
 char *file1Path;
 char *file2path;
 
 int main(int argc, char* args[] )
 {
	if( argc < 2 || argc > 3 )
	{
		fprintf(stderr, "USAGE : %s file1 file2\n", args[0] );
		return 1;
	}
	
	if( argc == 2 )
	{
		fclose(fopen("file2", "w") );
		copyFile(args[1], "file2");
	}
	
	file1Path = malloc( sizeof( char ) * MAX_PATH );
	file2path = malloc( sizeof( char ) * MAX_PATH );
	
	file1Path = args[1];
	file2path = args[2];
	
	int fildes = open(file1Path, O_RDWR );
	int file1ColumnNumber = getFileColumnNumber( fildes );
	close( fildes );
	
	/*** thread in diğer file ı okudugu yer ***/
	pthread_t tid;
	void *file2ColumnNumber = malloc(sizeof(int) ); 
	
	pthread_create(&tid, NULL, countFileRow, file2ColumnNumber );
	
	pthread_join(tid, &file2ColumnNumber );
	/*** ***/
	
	//fprintf(stderr, "file2 %d \t file1  %d\n", *( (int *)file2ColumnNumber ), file1ColumnNumber );
	
	if( *( (int *)file2ColumnNumber ) > file1ColumnNumber )
	{
		pthread_t tid3;
		pthread_create(&tid3, NULL, createTempFromFile2, &file1ColumnNumber );
		pthread_join(tid3, NULL );
		
		fildes = open(file1Path, O_RDWR );
		addFile( fildes );
	}
	else
	{
		pthread_t tid2;
		fildes = open(file1Path, O_RDWR );
		createTemp_fromTargetLocation(fildes, *( (int *)file2ColumnNumber ) );
		char *path = file2path;
		
		pthread_create(&tid2, NULL, updateFile2, path );
		pthread_join(tid2, NULL );
	}
	
	remove( "temp" );
	
	return 0;
 }/********************** end of main function ************************/ 
 
 void *createTempFromFile2( void * arg )
 {
	int fildes = open(file2path, O_RDWR );
	
	createTemp_fromTargetLocation(fildes, *( (int *) arg ) );
	
	return NULL;
 }
 
 void *updateFile2( void * arg )
 {
	int fildes = open(arg, O_RDWR );
	addFile( fildes );
	
	return NULL;
 }/***************** end of UpdateFile ********************************/
 
 void addFile( int fildes )
 {
	int tempFileFildes = open("temp", O_RDWR );
	int readVal=0;
	char readed;
	
	do
	{
		readVal = read(fildes, &readed, sizeof( char ) );
	}while( readVal != 0 );
	
	do
	{
		readVal = read( tempFileFildes, &readed, sizeof( char ) );
		
		if( readVal != 0 )
			write( fildes, &readed, sizeof( char ) );
		
	}while( readVal != 0 );
	
	
	return;
 }/************ end of addFile ****************************************/
 
 void createTemp_fromTargetLocation(int fildes, int file1columnNumber )
 {
	fclose(fopen("temp", "w"));
	
	int fildesTemp = open("temp", O_RDWR );
	int readedColumnNumber =0;
	int readedVal = 0;
	char readed;
	
	do
	{
		readedVal = read(fildes, &readed, sizeof( char ));
		if( readedVal != 0 )
		{
			if( readedColumnNumber >= file1columnNumber )
				write(fildesTemp, &readed, sizeof( char ) );
			else if( readed == '\n')
				++readedColumnNumber;
		}
		
	}while( readedVal != 0);
	
	
 }/*************** end of createTemp_fromTargetLocation **************/ 
 
 void *countFileRow( void *arg )
 {
	int fileLen=0;
	int fildes = open(file2path, O_RDWR );
	
	fileLen = getFileColumnNumber( fildes );
	
	/****/
	*( (int *) arg ) = fileLen;
	
	return arg;
 }/******************** end of countFileRow function ******************/
 
 int getFileColumnNumber( int fildes )
 {
	int columnNumber=0;
	int readVal;
	char readed;
	
	do
	{
		readVal = read(fildes, &readed, sizeof( char ) );
		
		if(readVal != 0 && readed == '\n' )
			++columnNumber;
	}
	while( readVal != 0 );
	
	return columnNumber;
 }/************ end of getFileColumnNumber function *******************/
 
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

