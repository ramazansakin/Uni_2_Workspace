 
 /* MUSTAFA ÇOKER 08104402
  * sistem programlama odev 1 part 1
  * sonuna ekle 
  * */
 
 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 
 int main( int argc, char *argv[] )
 {
	 if( argc != 3 )
	 {
		fprintf(stderr, "error file using. The usage: %s file1 file2\n", 
				 argv[0]);
		return 1;
	 }
	 
	 FILE* tempPtr;
   
   	 pid_t childPid;
	 
	 // open da ki permission flag ları kullanmamak icin bu sekilde 
	 // olusturdum
	 
	 tempPtr =  fopen("temp.dat", "w");
	 fclose( tempPtr );
	 
	 childPid = fork();
	 
	 if( childPid == 0 )
	 {
		// parent process wait e carpınca burası calısmaya baslıyo.
		// ikinci bolum burası
		
		pid_t file1Pid, tempFilePid;
		int readVal1=1, readVal2=1;
		char *buffer = malloc( sizeof( char ) );
		char *buffer2 = malloc( sizeof( char ) );
		
		
		file1Pid = open(argv[2], O_RDWR );
		tempFilePid = open("temp.dat", O_RDWR );
		
		do
		{
			if( readVal1 != 0 )
				readVal1 = read(file1Pid, buffer, sizeof( char ) );
			else
				write(file1Pid, buffer2, sizeof( char ) );
				
			if( readVal2 != 0 )
				readVal2 = read(tempFilePid, buffer2, sizeof( char ) );
			else
				write(tempFilePid, buffer, sizeof( char ) );
				
			
		}while( readVal1 != 0 || readVal2 != 0 );
		
		
		close( file1Pid );
		close( tempFilePid );
	 }
	 else
	 {
		// ilk burası calısıyo parent process wait e carpmadan once
		
		pid_t file1Pid, tempFilePid;
		int readVal=0;
		char *buffer = malloc( sizeof( char ) );
		
		file1Pid = open(argv[2], O_RDWR );
		tempFilePid = open("temp.dat", O_RDWR );
		
		do
		{
			readVal = read(file1Pid, buffer, sizeof( char ) );
			
			if( readVal != 0 )
				write(tempFilePid, buffer, sizeof( char ) );
			
		}while( readVal != 0  );
		
		close( tempFilePid );
		close( file1Pid );
		
	 }
	 wait(NULL);
	 
	 if( childPid == 0 )
		; /* child process code ( nothing done ) */
	 
	 else
	 {
		// parent process in son kısmı artık child öldü
		// temp file file1 ile file2 den gelen fazla karakterleri 
		// kontrol ediyo
		
		pid_t file2Pid, tempFilePid;
		int readVal1=1, readVal2=1;
		char *buf = malloc( sizeof( char ) );
		char *buf2 = malloc( sizeof( char ) );
		
		file2Pid = open(argv[1], O_RDWR );
		tempFilePid = open("temp.dat", O_RDWR );
		
		do{
			if( readVal1 != 0 )
				readVal1 = read(file2Pid, buf, sizeof( char ) );
			else
				write(file2Pid, buf2, sizeof( char ) );
			
			if( readVal2 != 0 )
				readVal2 = read(tempFilePid, buf2, sizeof( char ) );
			else
				write(tempFilePid, buf, sizeof( char ) );
			
		}while( readVal1 != 0 || readVal2 != 0 );
		
		close( file2Pid );
		close( tempFilePid );
		
		remove( "temp.dat" );
	 }
	 
	 return 0;
 } 
