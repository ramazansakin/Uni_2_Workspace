/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : May 20th 2013
 * File       : readMe.txt
 *
 * Description: 
 *          Description of how to run part1 and part2 of homework3           
 *******************************************************************
 */



 #############################################################
 HW#3 PART 1 : 
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o systemhw3
 *  $ ./systemhw3 -3 test.txt    OR  $ ./systemhw3 test.txt
 *
 *********************************************************
 */

 Tanıtım :
   Programın çalışma metodu ve nasıl derleneceği yukarıda belirtilmiştir. Eğer kaç tane
 satırın basılacağı arguman olarak gelmişse istenilen text dosyası verilen sayı kadar 
 basar." ./systemhw3 -3 test.txt " gibi olmalıdır. Açılacak olan text dosyası programın 
 derlendiği directory içerisinde olmalıdır. Eğer kaç tane satırın basılacağı arguman 
 olarak gelmemişse program çalıştırıldıktan sonra "./systemhw3 test.txt" kullanıcıdan 
 "enter" veya "space" tuşuna basması beklenir. "enter" tuşu text dosyasının 1 satırını 
 "space" tuşu text dosyasının 4 satırını ekranda gösterir.




 #############################################################
 HW#3 PART 2 : 
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o system
 *  $ ./system fifo
 *
 *********************************************************
 */

 Önbilgi : Hocam 20 mayıs pazartesi öğleden sonra yanınıza gelip ödev 3'ün part2 bölümünde 
 yanlışlıkla fonksiyona kendi bilgisayarımın path'ini verdiğimi söylemiştim. 85. satırda "/home/sabri/Desktop"
 diye bir adres var. O adresi arama yapacağınız directory olarak değiştirirseniz program sağlıklı
 bir şekilde çalışacaktır.. Teşekkürler.


 Tanıtım :
    Programın çalışma metodu ve nasıl derleneceği yukarıda belirtilmiştir. HW3'ün part2 bölümü derlenirken
 "./system fifo" ilk arguman program ismi 2. arduman ise inşaa edilecek olan fifo (haberleşme) dosyasının
 ismini oluşturmaktadır. Programın 85. satırındaki path aranacak directory olarak değiştirlirse, program mevcut directory'deki bütün file ,directory ve subdirectory'lerin ismini ve sayısını ekranda gösterecektir.
 
 
 
 
 
