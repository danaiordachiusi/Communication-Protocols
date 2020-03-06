#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;

  //Calcularea ferestrei
  
  int w = (atoi(argv[2]) * atoi(argv[3]) * 1000)/(sizeof(msg) * 8);

  //Trimiterea informatiilor despre fisier

  int fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    perror("Could not open file");
    return -1;
  }
  struct stat file_data;
  fstat(fd,&file_data);
  int size = file_data.st_size;  //dimensiune fisier

  int COUNT = size/1400 + 1;

  //Trimiterea numelui fisierului
  sprintf(t.payload, "%s", argv[1]);
  t.len = strlen(t.payload)+1;
  send_message(&t);

  if (recv_message(&t) < 0) {
    perror("receive error");
    return -1;
  }

  //Trimiterea lungimii fisierului
  memset(t.payload,0,sizeof(t.payload));
  memcpy(t.payload, &size, sizeof(int));
  send_message(&t);
  if (recv_message(&t) < 0) {
    perror("receive error");
  }

  int i = 0;
  int unknown = 0; //pachete pt care n am primit raspuns
  printf("Count = %d\n", COUNT);
  while(i < COUNT || unknown > 0 ) {

    while(w > 0 && i < COUNT) {
    
      /* fill msg */
      memset(&t.payload, 0, sizeof(t.payload));
      int readF = read(fd,t.payload,sizeof(t.payload));
      t.len = readF;  //nr de octeti cititi din fisier
          /* send msg */
      int res = send_message(&t);
      if (res < 0) {
        perror("[SENDER] Send error. Exiting.\n");
        return -1;
      }
      w--;
      i++;
      unknown++;
  }
    int res = recv_message(&t);
    if (res < 0 ) {
      perror("[SENDER] Recieve error. Exiting.\n");
      return -1;
    } else {
      w++;
      unknown--;
    }
   
  }
  close(fd);
  return 0;
}
