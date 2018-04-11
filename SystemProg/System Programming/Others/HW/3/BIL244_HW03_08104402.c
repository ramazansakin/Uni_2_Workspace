
 /* 08104402
  * Mustafa ÇOKER
  * Systems Programming 
  * HW #03
  * localSyncFk
  * */
 
 #include <dirent.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <errno.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <fcntl.h>
 #include <time.h>
 #define BUFSIZE 250
 #define MAX_PATH 255
 #define NAME 100 // dosya ya da klasor isimleri icin
 
 void copyDir( char *sourcePath, char *targetPath );
 // klasorleri kopyalıyo
 
 void getAllIndex( char *path, int fildes );
 // verilen path içindeki herseyin path ını alıp pipe e yazıyo
 
 int getIndexNumber( char *path );
 // verilen path de ki tum dosya ve klasorleri sayıp donduruyo
 
 void copyFile(char* sourcePath, char* targetPath);
 int compareByDate( struct stat buf1, struct stat buf2 );
 int compareBySize( struct stat buf1, struct stat buf2 );
 int isDirectory(char *path);
 
 int main(int argc, char* argv[] )
 {
	if( argc < 3 )
	{
		fprintf(stderr, "invalid usage!\n");
		fprintf(stderr, "the usage is %s -d/s dir1 dir2 ...\n", argv[0]);
		return 1;
	}
	
	if( argv[1][1] != 's' && argv[1][1] != 'd')
	{
		fprintf(stderr, "usage error\n");
		return 1;
	}
	
	// eger sadece bi tane dir verildiyse buraya giriyo ve newDir adında
	// bi klasor yapıp oraya kopyalıyo
	
	if( argc == 3 )
	{
		char *cwd = malloc( sizeof( char ) * MAX_PATH );
		char *targetPath = malloc( sizeof ( char ) * MAX_PATH );
		
		getcwd( cwd, MAX_PATH );
		sprintf(targetPath, "%s/%s", cwd, "newDir" );
		
		mkdir(targetPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
		copyDir(argv[2], targetPath );
	}
	
	char *sourcePath = malloc( sizeof( char ) * MAX_PATH );
	char *targetPath = malloc( sizeof( char ) * MAX_PATH );
	
	int i=0;
	targetPath = argv[2];
	
	
	pid_t childPid;
	
	int fd[2];
	
	if( pipe(fd) == -1 )
	{
		perror("Failed to create the pipe\n");
		return 1;
	}
	
	
	childPid = fork();
	
	if( childPid == -1 )
	{
		perror("failed to fork\n");
		return 1;
	}
	
	// bu dongu de ilk dir e tum diğer dir lerin içeriğini topluyo
	for(i=3; i<argc; i++ )
	{
		if( childPid == 0 )
		{
			/* ikinci klasorden itibaren tum klasorlerin içindeki herşeyin 
			 * path ini pipe a gönderiyo
			 * */
			sourcePath = argv[i];
			int numberOfElement=0; // toplam dosya ve klasor sayısı
			int lengthOfSourceDir = strlen( sourcePath );
			
			numberOfElement = getIndexNumber( sourcePath );
			
			write(fd[1], &numberOfElement, sizeof( int ) );
			// element(yani tüm dosya ve klasor) sayisi pipe a gitti
			
			write(fd[1], &lengthOfSourceDir, sizeof( int ) );
			// klasorun path uzunlugu pipe a gitti
			
			getAllIndex( sourcePath, fd[1]);
			// tum indexler pipe a gidiyo
			
			i = argc; // child dongü den cıkıp olsun bu esitlik yapıldı
		}
		else
		{
			wait(NULL);
			
			int numberOfElement = 0;
			int lengthOfPath = 0;
			int lengthOfSourceDir = 0;
			struct stat statbuf;
			struct stat statbuf2;
			int k=0;
			
			char *path = malloc( sizeof( char ) *  MAX_PATH );
			char *tempPath = malloc( sizeof( char ) * MAX_PATH );
			
			read(fd[0], &numberOfElement, sizeof( int ) );
			// child dan gelen toplam eleman sayısını pipe den okuyo
			
			read(fd[0], &lengthOfSourceDir, sizeof( int ) );
			//kaynak dosyanın path uzunlugunu okuyo
			
			for(k=0; k<numberOfElement; k++ )
			{
				
				read(fd[0], &lengthOfPath, sizeof( int ) );
				read(fd[0], path, sizeof( char ) * lengthOfPath );
				
				path[ lengthOfPath ] = '\0';
				sprintf(tempPath, "%s%s", targetPath, path + lengthOfSourceDir);
				
				if( isDirectory(path) != 0 )
				{
					if( stat(tempPath, &statbuf) == -1)
						mkdir(tempPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
				}
				else
				{
					if( stat(path, &statbuf2) == -1 )
						perror("Failed to get file status");
					
					if( stat(tempPath, &statbuf) == -1)
					{
						/* kaynak klasordeki file hedef mevcut değilse 
						 * hedef adrese file create ediyoruz
						 * */
						FILE* ptr = fopen(tempPath, "w");
						
						if( ptr == NULL )
							fprintf(stderr, "error %s\n", tempPath );
						else
							fclose( ptr );
						copyFile(path, tempPath);
					}
					else
					{
						switch ( argv[1][1] )
						{
							case 's':
								if( compareBySize(statbuf2, statbuf) )
									copyFile(path, tempPath);
								break;
							
							case 'd':
								if( compareByDate(statbuf2, statbuf) )
									copyFile(path, tempPath);
								break;
							default:
								fprintf(stderr, "only 's' & 'd' char\n");
						}
					}
					
				}
			}
			
			if( i < argc-1 )
			{
				childPid = fork();
				// her klasor için ayrı proses olusturduk teker teker 
				// tum klasorleri gezdik
				
				if( childPid == -1 )
				{
					perror("failed to fork\n");
					return 1;
				}
			}
			
		}
	
	}
	
	// tekrar parent proses devreye giriyo. bi once ki dongu de tum 
	// klasorlerin içinde ki file ve dir leri ilk dir de toplamıstık
	// simdi ilk dir i tum diğer dir lere kopyalıyoruz
	
	if( childPid != 0 )
	{
		childPid = fork();
	
		if( childPid == -1 )
		{
			perror("failed to fork\n");
			return 1;
		}
		
		
		for(i=3; i<argc; i++ )
		{
			if( childPid == 0 )
			{
				sourcePath = argv[2];
				int numberOfElement=0;
				int lengthOfSourceDir = strlen( sourcePath );
				
				numberOfElement = getIndexNumber( sourcePath );
				
				write(fd[1], &numberOfElement, sizeof( int ) );
				// element(yani tüm dosya ve klasor) sayisi pipe a gitti
				
				write(fd[1], &lengthOfSourceDir, sizeof( int ) );
				// klasorun path uzunlugu pipe a gitti
				
				getAllIndex( sourcePath, fd[1]);
				// tum indexler pipe a gidiyo
				
				i = argc;
			}
			else
			{
				wait(NULL);
				
				targetPath = argv[i];
				int numberOfElement = 0;
				int lengthOfPath = 0;
				int lengthOfSourceDir = 0;
				struct stat statbuf;
				struct stat statbuf2;
				int k=0;
				targetPath = argv[i];
				char *path = malloc( sizeof( char ) *  MAX_PATH );
				char *tempPath = malloc( sizeof( char ) * MAX_PATH );
				read(fd[0], &numberOfElement, sizeof( int ) );
				read(fd[0], &lengthOfSourceDir, sizeof( int ) );
				
				for(k=0; k<numberOfElement; k++ )
				{
					
					read(fd[0], &lengthOfPath, sizeof( int ) );
					read(fd[0], path, sizeof( char ) * lengthOfPath );
					
					path[ lengthOfPath ] = '\0';
					sprintf(tempPath, "%s%s", targetPath, path + lengthOfSourceDir);
					
					if( isDirectory(path) != 0 )
					{
						if( stat(tempPath, &statbuf) == -1)
							mkdir(tempPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
					}
					else
					{
						if( stat(path, &statbuf2) == -1 )
							perror("Failed to get file status");
						
						if( stat(tempPath, &statbuf) == -1)
						{
							/* kaynak klasordeki file hedef mevcut değilse 
							 * hedef adrese file create ediyoruz
							 * */
							FILE* ptr = fopen(tempPath, "w");
							
							if( ptr == NULL )
								fprintf(stderr, "%s\n", tempPath );
							else
								fclose( ptr );
							copyFile(path, tempPath);
						}
						else
						{
							switch ( argv[1][1] )
							{
								case 's':
									if( compareBySize(statbuf2, statbuf) )
										copyFile(path, tempPath);
									break;
								
								case 'd':
									if( compareByDate(statbuf2, statbuf) )
										copyFile(path, tempPath);
									break;
								default:
									fprintf(stderr, "only 's' & 'd' char\n");
							}
						}
						
					}
				}
				
				if( i < argc-1 )
				{
					childPid = fork();
					
					if( childPid == -1 )
					{
						perror("failed to fork\n");
						return 1;
					}
				}
				
			}
		
		}
		
	}
	
	return 0;
 }/***********************  END OF  MAIN  *****************************/
 
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
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 )
		{
			sprintf( newSource, "%s/%s", sourcePath, direntp->d_name );
			sprintf( newTarget, "%s/%s", targetPath, direntp->d_name);
			
			if( isDirectory( newSource ) != 0 )
			{
				mkdir(newTarget, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
				fprintf(stderr, "dirrrr--->%s\n", newSource );
				copyDir( newSource, newTarget );
			}
			else
			{
				//fprintf(stderr, "file---->%s\n", newSource );
				copyFile(newSource, newTarget);
			}
		}
		
		
	}while( direntp != NULL );
	
	return;
 }/***********************  END OF  copyDir ***************************/
 
 void getAllIndex( char *path, int fildes )
 {
	DIR* dir;
	struct dirent *direntp;
	char *tempPath = malloc( sizeof( char ) * MAX_PATH );
	
	dir = opendir( path );
	
	do
	{
		int lenghtOfPath = 0;

		direntp = readdir( dir );
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 )
		{
			sprintf(tempPath, "%s/%s", path, direntp->d_name );
			
			lenghtOfPath = strlen( tempPath );
			
			
			write(fildes, &lenghtOfPath, sizeof( int ) );
			write(fildes, tempPath, sizeof( char )* lenghtOfPath );
			
			//fprintf(stderr, "%d %s\n", lenghtOfPath, tempPath);
			
			if( isDirectory( tempPath ) != 0 )
				getAllIndex( tempPath, fildes);
		}
	}
	while( direntp != NULL );
	
	return;
 }/***********************  END OF  getAllIndex ***********************/
 
 
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
		
		if( direntp != NULL && strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 )
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
 
 int isDirectory(char *path)
 {
	struct stat statbuf;

	if (stat(path, &statbuf) == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
 }/************************* end of isDirectory  **********************/
