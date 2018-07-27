#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char *argv[]){
  int arrlen = 0, i = 0;
	FILE *fp;

  char ch;
  char * arr= malloc(sizeof(char) * 512);
  char * bitSize = argv[2];

  fp = fopen(argv[1],"r");
  while((ch = fgetc(fp)) != EOF){
    arr[arrlen]= ch;
    arrlen++;
  }

  if(bitSize[0] == '8'){
      unsigned int checksum = 0;

      for(i=0;i<=strlen(arr);i++){
        if(i==80||i==160||i==240||i==320||i==400||i==480)
          printf("\n");
        printf("%c", arr[i]);
        checksum = checksum + arr[i];
      }

      checksum = checksum % 256;
      printf("%s bit checksum is %x for all %d chars", bitSize, checksum, arrlen);

  }else if (bitSize[0] == '1' && bitSize[1] == '6'){
       //16 bit checksum
      uint16_t checksum = 0;

      //Pad with X
      if(strlen(arr) % 2 != 0){
        arr[arrlen] = 'X';
        arrlen++;
      }

      for(i=0;i<arrlen;i=i+2){
        if(i==80||i==160||i==240||i==320||i==400||i==480)
          printf("\n");
        printf("%c%c",arr[i], arr[i+1]);
        checksum += (arr[i] << 8) + arr[i+1];
      }

      printf("\nThe %s bit checksum is %x for all %d chars",bitSize, checksum, arrlen);

  }else if (bitSize[0] == '3' && bitSize[1] == '2'){

      uint32_t checksum = 0;

      while(arrlen % 4 != 0){ //Pad with X
          arr[arrlen] = 'X';
          arrlen++;
      }

      for(i=0;i<arrlen;i=i+4){
        if(i==80||i==160||i==240||i==320||i==400||i==480)
          printf("\n");
        checksum += (arr[i] << 24) + (arr[i+1] << 16) + (arr[i+2] << 8) + (arr[i+3]);
        printf("%c%c%c%c", arr[i], arr[i+1], arr[i+2], arr[i+3]);
      }

      printf("\nThe %s bit checksum is %x for all %d chars", bitSize, checksum, arrlen);
  }else{
      printf("Bad input ...");
  }

  printf("\n");
  fclose(fp);
  return 0;
}
