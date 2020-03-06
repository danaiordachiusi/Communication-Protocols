#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv) {
  msg r,t;
  int res;
  init(HOST,PORT);

  
  printf("[RECEIVER] Starting.\n");

  // Primeste denumirea fisierului
  if (recv_message(&r) < 0) {
    perror("Receive message");
    return -1;
  }
  memset(t.payload, 0, sizeof(t.payload));
  t.len = strlen(t.payload) + 1;
  send_message(&t);

  int dest = open("recv_fileX", O_WRONLY |O_TRUNC | O_CREAT, 0644);
  if (dest < 0) {
    perror("Can't open output file");
  }

  // Primeste lungimea fisierului
  if (recv_message(&r)<0) {
    perror("Receive message");
    return -1;
  }

  int size;
  memcpy(&size, r.payload, sizeof(int));

  memset(t.payload, 0, 1400);
  send_message(&t);
  int COUNT = size/1400 + 1;
  int i;
  for (i = 0; i < COUNT; i++) {
    /* wait for message */
    res = recv_message(&r);
    if (res < 0) {
      perror("[RECEIVER] Receive error. Exiting.\n");
      return -1;
    }
    //scriem in fisier
    write(dest,r.payload,r.len);
    
    /* send ACK */
    res = send_message(&t);
    if (res < 0) {
      perror("[RECEIVER] Send ACK error. Exiting.\n");
      return -1;
    }
  }

  return 0;
}
