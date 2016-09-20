#include	<stdio.h>
#include	<string.h>
#include	<time.h>
#include	<stdlib.h>
#include "timsort.h"
int main(){
  int i,j,n;
 // a=3; b=4;
  //swap(&a,&b);
  int chk[9999];
  
  for(i=n=10000,j=0;(i>0)&&(j<10000);i--,j++){
       chk[j]=rand();
  }
 // printf("\n what's going on ? \n");  
 printf("%d \n",n); 
 for(i=0;i<10000 && printf(" %d ",chk[i]);i++);
  //int_timsort(chk,64);
  //printf("\n wtf this is pathetic \n");
 // for(i=0;i<64 && printf(" %d ",chk[i]);i++); 
 	return 0; }
