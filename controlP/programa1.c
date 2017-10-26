#include <stdio.h> //signal
#include <unistd.h>//signal
#include <stdlib.h>//signal
#include <signal.h>//signal

#include <fcntl.h> //leer
#include <sys/stat.h>//leer

#include <sys/types.h> //pipe

void sighandler(int);

int main () {
   signal(SIGINT, sighandler);

    //esperando la señal
   while(1) {
      printf("esperando...\n");
      sleep(1); 
   }
   return(0);   
}   

void sighandler(int signum) {
   //para leer un archivo
   int fd;
   char * mytxt = "/home/maria/Escritorio/OS works/ucsp.txt"; // lee un archivo de mi compu
   char buf[7];
   fd = open(mytxt, O_RDONLY);
   read(fd, buf, 7);
   printf("Encontrado: %s\n", buf);
   close(fd);
   //para escribir en el pipe named
   int fd2;
   char * myfifo = "/tmp/myfifo";
   mkfifo(myfifo, 0666);
   fd2 = open(myfifo, O_WRONLY);
   write(fd2, buf, sizeof(buf));
   close(fd2);
   unlink(myfifo);
}
