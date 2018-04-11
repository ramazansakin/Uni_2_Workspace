
 /* MUSTAFA ÇOKER 08104402 
  * sistem programlama odev 1 part 2
  * SIRASINA EKLE 
  */
  
 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 #include <sys/types.h>
 
 int main(int argc, char *argv[])
 {
	if( argc != 3 )
	{
		fprintf(stderr, "error exe format\n" );
		fprintf(stderr, "the usage: %s file1 file2 \n", argv[0] );
		return 1;
	} 
	
	pid_t childPid;
	
	FILE* tempFilePtr;// temp file sadece olusturmak icin kullandım
	
	
	/* iki tane temporary file tuttum
	 * fopen la acıp hemen kapattım aslında sadece olusturmak icin 
	 * fopen fclose kullandım open la olustururken permission flag lar 
	 * cok kalabalıktı onları kullanmamak ici bu sekilde olusturdum
	 */
	 
	tempFilePtr = fopen("temp.dat", "w");
	fclose( tempFilePtr );
	
	tempFilePtr = fopen("temp2.dat", "w");
	fclose( tempFilePtr );
	
	childPid = fork();
	
	if( childPid == 0 )
	{
		/* parent wait e carpınca buraya geliyo. 
		 * file1 temp e kopyalanmıstı zaten
		 * bu bölümde child process temp ile file2 yi karsılastırıp 
		 * file2 yi temp den gelen fazla char lar ile birlestirip temp2
		 * yazıyo sonra file yi silip temp2 yi tamamen file2 kopyalıyo
		 *  
		 */
		 
		pid_t file2, temp, temp2;
		int readVal1, readVal2;
		char *buffer = malloc( sizeof( char ) ),
			 *buffer2 = malloc(sizeof( char ));
		
		file2 = open(argv[2], O_RDWR );
		temp = open("temp.dat", O_RDWR );
		temp2 = open("temp2.dat", O_RDWR );
		
		readVal1 = read(file2, buffer, sizeof( char ) );
		readVal2 = read(temp, buffer2, sizeof( char ) );
		
		// file2 ve file1(temp) bos durumu kontrol etmek lazım bu asamada
		// eger ikisinden biri bossa digerini temp2 ye kopyalıyo 
		
		if(readVal2 == 0 )
		{
			while( readVal1 != 0 )
			{
				if( readVal1 != 0 )
					write(temp2, buffer, sizeof( char ) );
					
				readVal1 = read(file2, buffer, sizeof( char ) );
			}
		}
		
		else if(readVal1 == 0 )
		{
			while( readVal2 != 0 )
			{
				if( readVal2 != 0 )
					write(temp2, buffer2, sizeof( char ) );
					
				readVal2 = read(temp, buffer2, sizeof( char ) );
			}
		}
		else
		{
			while( readVal1 != 0 || readVal2 != 0 )
			{
				
				if( (*buffer) != '\n' && (*buffer2) != '\n' )
				{
					write(temp2, buffer, sizeof( char ) );
					
					readVal1 = read(file2, buffer, sizeof( char ) );
					readVal2 = read(temp, buffer2, sizeof( char ) );
				}
				
				else if( (*buffer) == '\n' && (*buffer2) != '\n' )
				{
					while( (*buffer2) != '\n' && readVal2 != 0 )
					{
						write(temp2, buffer2, sizeof( char ) );
						readVal2 = read(temp, buffer2, sizeof( char ) );
					}
				}
				
				else if( (*buffer2) == '\n' && (*buffer) != '\n' )
				{
					while( (*buffer) != '\n' && readVal1 != 0 )
					{
						write(temp2, buffer, sizeof( char ) );
						readVal1 = read( file2, buffer, sizeof( char ) );
					}
				}
				
				else if( ( *buffer )  == '\n' && (*buffer2) == '\n' )
				{
					write(temp2, buffer, sizeof( char ) );
					
					readVal1 = read(file2, buffer, sizeof( char ) );
					readVal2 = read(temp, buffer2, sizeof( char ) );
				}

			}// end of while	
		}
		 
		close( temp );
		close( file2 );
		close( temp2 );
		
		// file yi silmek icin actım kapattım
		tempFilePtr = fopen(argv[2], "w");
		fclose( tempFilePtr );
		
		file2 = open(argv[2], O_RDWR );
		temp2 = open("temp2.dat", O_RDWR );
		
		do
		{
			readVal1 = read(temp2, buffer, sizeof( char ) );
			
			if( readVal1 != 0 )
				write(file2, buffer, sizeof( char ) );
			
		}while( readVal1 != 0 );
		
	}
	else
	{
		// once bura calısıyo parent process in ilk asaması wait den 
		// once ki kısım
		
		// burada sadece file 1( argv[1] ) temp e kopyalandı
		
		pid_t file1Pid, tempFilePid;
		int readVal=0;
		char *buffer = malloc( sizeof( char ) );
		
		file1Pid = open(argv[1], O_RDWR );
		tempFilePid = open("temp.dat", O_RDWR );
		
		do
		{
			readVal = read(file1Pid, buffer, sizeof( char ) );
			
			if( readVal != 0 )
				write(tempFilePid, buffer, sizeof( char ) );
				
		}while( readVal != 0 );
		
	}	
	wait(NULL); // parent process bekletildi
	
	if( childPid == 0 )
	{
		; /* child code  ( nothing done ) */
	}
	else
	{
		// en son da bura calısıyo file in sonuna file2 den gelen fazla
		// karakterler yazılıyo
		int file1, temp, temp2;
		int readVal1, readVal2;
		char *buffer1 = malloc( sizeof( char ) ),
			 *buffer2 = malloc( sizeof( char ) );
		
		// temp file kullanacagım icin icini sildim
		tempFilePtr = fopen("temp.dat", "w");
		fclose( tempFilePtr );
	
		file1 = open( argv[1], O_RDWR );
		temp = open( "temp.dat", O_RDWR );
		temp2 = open( "temp2.dat", O_RDWR );
		
		readVal1 = read(file1, buffer1, sizeof( char ) );
		readVal2 = read(temp2, buffer2, sizeof( char ) );
		
		// tekrar file ları kontrol ettim bu iki if statement la
		if( readVal1 == 0 )
		{
			while( readVal2 != 0 )
			{
				write(temp, buffer2, sizeof( char ) );
				readVal2 = read(temp2, buffer2, sizeof( char ) );
			}
		}
		else if( readVal2 == 0 )
		{
			while( readVal1 != 0 )
			{
				write(temp, buffer1, sizeof( char ) );
				readVal1 = read(file1, buffer1, sizeof( char ) );
			}
		}
		else
		{
			while( readVal1 != 0 || readVal2 != 0 )
			{
				if( (*buffer1) != '\n' && (*buffer2) != '\n' )
				{
					write(temp, buffer1, sizeof( char ) );
					
					readVal1 = read(file1, buffer1, sizeof( char ) );
					readVal2 = read(temp2, buffer2, sizeof( char ) );
				}
				
				else if( (*buffer1) == '\n' && (*buffer2) != '\n' )
				{
					while( (*buffer2) != '\n' )
					{
						write(temp, buffer2, sizeof( char ) );
						readVal2 = read(temp2, buffer2, sizeof( char ) );
					}
				}
				
				else if( (*buffer2) == '\n' && (*buffer1) != '\n' )
				{
					while( (*buffer1) != '\n' )
					{
						write(temp, buffer1, sizeof( char ) );
						readVal1 = read(file1, buffer1, sizeof( char ) );
					}
				}
				
				else if( (*buffer1) == '\n' && (*buffer2) == '\n')
				{
					write(temp, buffer1, sizeof( char ) );
					
					readVal1 = read(file1, buffer1, sizeof( char ) );
					readVal2 = read(temp2, buffer2, sizeof( char ) );
				}
				
			}// end of while 	
		}
		
		close( file1 );
		close( temp2 );
		close( temp );
		
		// file1 i update etmek icin icini sildim
		tempFilePtr = fopen(argv[1], "w");
		fclose( tempFilePtr );
		
		temp = open("temp.dat", O_RDWR );
		file1 = open(argv[1], O_RDWR );
		
		do
		{
			readVal1 = read(temp, buffer1, sizeof( char ) );
			
			if( readVal1 != 0 )
				write(file1, buffer1, sizeof( char ) );
			
		}while( readVal1 != 0);
		
		
		// removing temporary file
		remove("temp.dat");
		remove("temp2.dat");
	} 
	return 0;
 }
