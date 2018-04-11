
/* H W # 5
 * localSyncTh.c file
 * Mustafa Çoker
 * 08104402
 * */

 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <dirent.h>
 #include <string.h>

 
 #ifdef MAX_PATH
 #undef MAX_PATH
 #define MAX_PATH 250
 #else
 #define MAX_PATH 250
 #endif
 
 struct thread_paramaters {
	char *path;
	int fildes;
 };
 
 typedef struct thread_paramaters t_param;
 typedef t_param* t_paramPtr;

 /*** functions prototypes ***/
 void *getAllIndex( void* parameter );
 // verilen path içindeki herseyin path ını alıp pipe e yazıyo
 
 int getIndexNumber( char *path );
 // verilen path de ki tum dosya ve klasorleri sayıp donduruyo
 
 void *writeIndexNumberToPipe( void* parameter );  
 // dir lerin toplam index sayılarını pipe a yazıyo
 
 void copyDir( char *sourcePath, char *targetPath );
 // klasorleri kopyalıyo
 
 void copyFile(char* sourcePath, char* targetPath);
 // dosyaları kopyalanyan fonksiyon
  
 int isDirectory(char *path);
 // return zero the path isn't directory or return 
 
 int compareBySize( struct stat buf1, struct stat buf2 );
 // compare two path by size
 
 int compareByDate( struct stat buf1, struct stat buf2 );
 // compare two path by date
 
 void *syncTh( void *param );
 // ikinci adımda ki sync de cagrılıyo 
 /*** ***/
 
 /* global variable */
 char compareType;
 
 
 int main(int argc, char* args[] )
 {
	if( argc < 2 )
	{
		fprintf(stderr, "USAGE : %s -s/-d path1 path2 ... \n", args[0] );
		exit( 1 );
	}
	
	if( args[1][1] != 's' && args[1][1] != 'd' && args[1][0] != '-' )
	{
		fprintf(stderr, "USAGE : %s -s/-d path1 path2 ... \n", args[0] );
		exit( 1 );
	}
	
	if( argc == 3 )
	{
		char *sourceDirName = malloc( sizeof (char ) * MAX_PATH );
		char *sourcePath = malloc( sizeof (char ) * MAX_PATH );
		sourcePath = args[2];
		int sourceDirLength = strlen( sourcePath ); 
		
		while( sourcePath[ sourceDirLength ] != '/' && sourceDirLength > 0 )
			--sourceDirLength;
		
		sourceDirName = sourcePath + sourceDirLength + 1;
		
		if( sourceDirLength > 0 )
		{
			mkdir( sourceDirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
			copyDir(sourcePath, sourceDirName );
		}	
		else
		{
			fprintf(stderr, "zaten current directory de bu klasor mevcut\n");
			exit( 1 );
		}
		return 0;
	}
	
	compareType = args[1][1];
	
	int i=0;
	
	pthread_t tid, tid2;
	t_param parameters;
	
	char *sourcePath = malloc( sizeof(char)* MAX_PATH );
	char *targetPath = malloc( sizeof(char)* MAX_PATH );
	char *tempPath = malloc( sizeof(char)* MAX_PATH );
	
	sourcePath = args[2];
	
	int fd[2];
	if( pipe(fd) == -1 )
		perror("failed to create pipe\n");
	
	for(i=3; i<argc; i++ )
	{

		parameters.path = malloc( sizeof( int ) * MAX_PATH );
		parameters.fildes = fd[1];
		parameters.path = args[i];
		
		pthread_create(&tid, NULL, writeIndexNumberToPipe, &parameters );
		pthread_join(tid, NULL );
		
		pthread_create(&tid2, NULL, getAllIndex, &parameters );
		pthread_join(tid2, NULL );
		/****/
		
		int total = 0;
		int sourcePathLength;
		int lengthOfTargetPath=0;
		struct stat statbuf;
		struct stat statbuf2;
		
		read(fd[0], &total, sizeof( int ) );
		read(fd[0], &sourcePathLength, sizeof( int ) );
		
		/** main thread **/
		int j=0;
		for(j=0; j<total; j++ )
		{
			read(fd[0], &lengthOfTargetPath, sizeof( int ));
			read(fd[0], targetPath, sizeof(char ) * lengthOfTargetPath );
			
			targetPath[ lengthOfTargetPath ] = '\0';
			
			sprintf(tempPath, "%s%s", sourcePath, targetPath + sourcePathLength );
			
			if( isDirectory(targetPath) )
			{
				if( stat(tempPath, &statbuf) == -1)
					mkdir(tempPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
			}
			else
			{
				
				if( stat(targetPath, &statbuf) == -1 )
					perror("Failed to get file Statüs\n");
				
				if( stat(tempPath, &statbuf2) == -1 )
				{
					fclose( fopen(tempPath, "w" ) );
					copyFile(targetPath, tempPath );
				}
				else
				{
					switch ( compareType )
					{
						case 's':
							if( compareBySize(statbuf, statbuf2) )
								copyFile(targetPath, tempPath);
							break;
							
						case 'd':
							if( compareByDate(statbuf, statbuf2) )
								copyFile(targetPath, tempPath);
							break;
						default:
							fprintf(stderr, "USAGE ERROR only 's' & 'd' char\n");
					
					}	
				}
			}
			
		}
		
	}
	// yukarıda ki for la tüm klasorleri ilk klasörde topladık 
	
	sourcePath = args[2];
	
	int totalIndex = getIndexNumber( sourcePath );
	int lengthOfSourcePath = strlen( sourcePath );
	
	for(i=3; i<argc; i++ )
	{
		write(fd[1], &totalIndex, sizeof( int ) );
		write(fd[1], &lengthOfSourcePath, sizeof( int ) );
		
		parameters.path = sourcePath;
		parameters.fildes = fd[1];
		
		getAllIndex( &parameters );
		
		
		parameters.path = args[i];
		parameters.fildes = fd[0];
		pthread_create(&tid, NULL, syncTh, &parameters );
		pthread_join(tid, NULL );
		
		
	}
	// tüm klasörleri ilk klasorle sync ettik
	return 0;
 }/************************* END OF MAIN ******************************/
 
 void *syncTh( void *param )
 {
	char *path = malloc( sizeof(char) * MAX_PATH ); // target in param
	char *sourcePath = malloc( sizeof(char) * MAX_PATH );
	char *tempPath = malloc( sizeof(char) * MAX_PATH );
	
	int fildes = ( (t_paramPtr)param )->fildes;
	path = ( (t_paramPtr)param )->path;
	
	int totalIndex=0;
	int lengthOfSourcePath=0;
	int lengthOfNextPath=0;
	int i=0;
	
	struct stat statbuf;
	struct stat statbuf2;
	
	read(fildes, &totalIndex, sizeof( int ) );
	read(fildes, &lengthOfSourcePath, sizeof( int ) );
	
	for(i=0; i<totalIndex; i++ )
	{
		read(fildes, &lengthOfNextPath, sizeof( int ) );
		read(fildes, sourcePath, sizeof( char ) * lengthOfNextPath );
		sourcePath[ lengthOfNextPath ] = '\0';
		
		sprintf(tempPath, "%s%s", path, sourcePath + lengthOfSourcePath );
		
		if( isDirectory( sourcePath ) )
		{
			if( stat(tempPath, &statbuf) == -1)
				mkdir(tempPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
		}
		else
		{
			if( stat(sourcePath, &statbuf) == -1 )
				perror("Failed to get file Statüs\n");
				
			if( stat(tempPath, &statbuf2) == -1 )
			{
				fclose( fopen(tempPath, "w" ) );
				copyFile(sourcePath, tempPath );
			}
			else
			{
				switch ( compareType )
					{
						case 's':
							if( compareBySize(statbuf, statbuf2) )
								copyFile(sourcePath, tempPath);
							break;
							
						case 'd':
							if( compareByDate(statbuf, statbuf2) )
								copyFile(sourcePath, tempPath);
							break;
						default:
							fprintf(stderr, "USAGE ERROR only 's' & 'd' char\n");
					}
			}
		}
	}
	
	
	return NULL;
 }
 
 void *writeIndexNumberToPipe( void* parameter )
 {
	char *path = malloc( sizeof(char) * MAX_PATH );
	path = ((t_paramPtr)parameter)->path;
	int fildes = ((t_paramPtr)parameter)->fildes;
	
	int targetPathLength = strlen( path );
	int total = getIndexNumber( path );
	
	write(fildes, &total, sizeof(int) );
	write(fildes, &targetPathLength, sizeof(int) );
	
	return NULL;
 }
 
 void *getAllIndex( void* parameter )
 {
	char *path = ( (t_paramPtr)parameter )->path;
	int fildes = ( (t_paramPtr)parameter )->fildes;
	
	DIR* dir;
	struct dirent *direntp;
	char *tempPath = malloc( sizeof( char ) * MAX_PATH );
	
	dir = opendir( path );
	
	do
	{
		int lenghtOfPath = 0;

		direntp = readdir( dir );
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 
			&& strcmp(direntp->d_name, "..") != 0 )
		{
			sprintf(tempPath, "%s/%s", path, direntp->d_name );
			
			lenghtOfPath = strlen( tempPath );
			
			
			write(fildes, &lenghtOfPath, sizeof( int ) );
			write(fildes, tempPath, sizeof( char )* lenghtOfPath );
			
			if( isDirectory( tempPath ) != 0 )
			{
				void *param;
				t_param tempParam;
				tempParam.path = malloc( sizeof(char) * MAX_PATH );
				tempParam.path = tempPath;
				tempParam.fildes = fildes;
				param = &tempParam;
				getAllIndex( param );
			}
		}
	}
	while( direntp != NULL );
	
	return NULL;
 }/***********************  END OF  getAllIndex ***********************/
 
 int isDirectory(char *path)
 {
	struct stat statbuf;

	if (stat(path, &statbuf) == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
 }/************************* end of isDirectory  **********************/
 
 void copyDir( char *sourcePath, char *targetPath )
 {
	DIR* dir;
	struct dirent *direntp;
	char *newTarget = malloc( sizeof( char ) * MAX_PATH );
	char *newSource = malloc( sizeof( char ) * MAX_PATH );
	
	
	dir = opendir( sourcePath );
	
	do
	{
		direntp = readdir( dir );
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 
			&& strcmp(direntp->d_name, "..") != 0 )
		{
			sprintf( newSource, "%s/%s", sourcePath, direntp->d_name );
			sprintf( newTarget, "%s/%s", targetPath, direntp->d_name);
			
			if( isDirectory( newSource ) != 0 )
			{
				mkdir(newTarget, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
				copyDir( newSource, newTarget );
			}
			else
				copyFile(newSource, newTarget);
			
		}
		
		
	}while( direntp != NULL );
	
	return;
 }/***********************  END OF  copyDir ***************************/
 
 int getIndexNumber( char *path )
 {
	int total=0;
	
	struct dirent *direntp;
	char *tempPath = malloc( sizeof( char ) * MAX_PATH );
	
	DIR *dir;
	dir = opendir( path );// kotrol et
	
	do
	{
		direntp = readdir( dir );
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 
			&& strcmp(direntp->d_name, "..") != 0 )
		{
			sprintf( tempPath, "%s/%s", path, direntp->d_name );
			
			if( isDirectory( tempPath ) != 0 )
			{
				total = total + getIndexNumber( tempPath );
				++total;
			}
			else
				++total;
		}// end of if( dirent != NULL )
		
	}while( direntp != NULL );
	
	closedir( dir );// kontrol
	return total;
 }/************************* end of getIndexNumber  *******************/
 
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
 
 int compareBySize( struct stat buf1, struct stat buf2 )
 {
	if( buf1.st_size > buf2.st_size )
		return 1;
	else
		return 0;
	 
 }/******************* END OF compareBySize FUNCTION ******************/
 
 int compareByDate( struct stat buf1, struct stat buf2 )
 {
	if( buf1.st_mtime > buf2.st_mtime )
		return 1;
	else
		return 0;
 }/******************* END OF compareByDate  FUNCTION ******************/
