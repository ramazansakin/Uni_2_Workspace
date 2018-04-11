 
 
 /* Mustafa ÇOKER
  *   08104402
  * localsync odev #2
  * */
 

 #include <dirent.h>
 #include <stdio.h>
 #include <errno.h>
 #include <unistd.h>
 #include <stdlib.h> // for malloc
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <fcntl.h>
 #include <time.h>
 #include <string.h> // for strcmp

 #define MAX_PATH 255

 
 void copyFile(char* sourcePath, char* targetPath);
 void localsync(char *sourcePath, char *targetPath, char cmpType );
 int isDirectory(char *path);
 int compareBySize( struct stat buf1, struct stat buf2);
 int compareByDate( struct stat buf1, struct stat buf2 );
  
 int main( int argc, char *argv[] )
 {
	if( argc != 4 )
	{
		fprintf(stderr, "usage error\n");
		return 1;
	}
	
	// hedef klasorleri degistirip iki kez fonksiyonu cagırdım
	localsync(argv[2], argv[3], argv[1][1]);
	localsync(argv[3], argv[2], argv[1][1]);
	
	return 0;
 }/******************* END OF main FUNCTION ***************************/
 
 // cmpType = type of compare( size or date )( for size s & for date d )  
 void localsync(char *sourcePath, char *targetPath, char cmpType )
 {
	DIR *dirA, *dirB;
	dirA = opendir( sourcePath );
	dirB = opendir( targetPath );
	
	if( dirA == NULL || dirB == NULL )
	{
		fprintf(stderr, "ERROR opening directory\n");
		return;
	}
	
	struct dirent *direntp;
	struct stat statbuf;
	struct stat statbuf2;
	
	do
	{
		direntp = readdir( dirA );
		char *tempPath = malloc( MAX_PATH );
		char *tempPath2 = malloc( MAX_PATH );
		
		if( direntp != NULL )
		{
			// klasorde bulunan oge nin path ini olusturdum
			sprintf(tempPath, "%s/%s", sourcePath, direntp->d_name );
			
			/* ayni ogeyi diger klasore gore adresledim
			 * bolece status aldıgımızda bu oge diğer klasorde yoksa -1 
			 * dondurecek bizde bu ogeyi hedef adresde create edecez
			 * */
			sprintf(tempPath2, "%s/%s", targetPath, direntp->d_name );
			
			if( isDirectory(tempPath) != 0 )
			{
				// pointer lara carparsa atlayacak
				 
				if( strcmp(direntp->d_name, ".") != 0 && 
					strcmp(direntp->d_name, "..") != 0)
				{
					/* eger -1 gelirse bu klasor hedef klasorde yok
					 * biz de klasor create ediyoruz
					 * */
					if( stat(tempPath2, &statbuf2) == -1)
						mkdir(tempPath2, 
							  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
						
					/* yeni yaptıgımız klasor un icini kaynak klasor deki
					 * elemanlarla doldurmak icin recursive olarak ayni
					 * fonksiyonu tekrar cagırıyoruz
					 * */
					localsync(tempPath, tempPath2, cmpType );
				}
			}
			else
			{
				/* bu else file lar icin calısıo yukarıda ki if klasorler
				 * icin di
				 * */
				if(stat(tempPath, &statbuf) == -1 )
					perror("Failed to get file status");
				
				else if( strcmp(direntp->d_name, ".") != 0 && 
						 strcmp(direntp->d_name, "..") != 0)
				{
				
					if( stat(tempPath2, &statbuf2) == -1)
					{
						/* kaynak klasordeki file hedef mevcut değilse 
						 * hedef adrese file create ediyoruz
						 * */
						fclose( fopen(tempPath2, "w") );
						copyFile(tempPath, tempPath2);
					}
					else
					{
						/* file her iki klasorde varsa istenen modda 
						 * check edip gerekirse kopyalıyoruz
						 * */
						switch (cmpType)
						{
							case 's':
								if( compareBySize(statbuf2, statbuf) )
									copyFile(tempPath2, tempPath);
								else if( compareBySize(statbuf, statbuf2) )
									copyFile(tempPath, tempPath2);
								break;
							
							case 'd':
								if( compareByDate(statbuf2, statbuf) )
									copyFile(tempPath2, tempPath);
								else if( compareByDate(statbuf, statbuf2) )
									copyFile(tempPath, tempPath2);
								break;
							default:
								fprintf(stderr, "only 's' & 'd' char\n");
						}
					}
				}
			}
		}
		
	}while( direntp != NULL );
	
	if( closedir( dirA ) == -1 || closedir( dirB ) == -1 )
	{
		fprintf(stderr, "ERROR closing directory\n");
		return;
	}
 }/******************* END OF localsync FUNCTION **********************/
 
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
 }/******************* END OF isDirectory FUNCTION ********************/
