#include <stdio.h>
#include "timsort.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PATH 260
#define FOR(i,a,b) for(i=a;i<b;i++)
/*                 ###### TIMSORT #######
                  provide full path to input text file
                  outputs sorted file to current directory of this program
                  USAGE : interface <full path>
                  DO NOT PROVIDE FILE EXTENSION
				  */
int main(int argc,char *argv[]){
   int N,i,count=0;  char extension[]={'.','t','x','t','\0'}; int* array;
   clock_t begin,end; double time_spent;
   FILE *fd=NULL;
   if(argc<2){
           printf("\n ######## TIMSORT ######### \n");
           printf("\n provide full path to input text file ");
           printf("\n outputs sorted file to current directory of this program \n");
           printf("\n USAGE : interface <full_path> ");
           printf("\n DO NOT PROVIDE FILE EXTENSION ");

exit(0); 
    }
    else if(argc > 2){ printf("\n TOO MANY arguments \n"); exit(0);
    }
    else{                        //#length check 
         if(strlen(argv[1])>MAX_PATH){ printf("\n INVALID PATH exceeds 260 characters on Windows 7 \n"); exit(0); } 
    }  
    char path[strlen(argv[1])+strlen(extension)+1];
    snprintf(path,sizeof(path),"%s%s",argv[1],extension);
    fd=fopen(path,"r");
    if(fd==NULL){
        printf("\n the path provided is invalid "); 
        printf("\n try again by providing proper path without file extension \n");
        exit(0);
    }
    fscanf(fd,"%d",&N);
    array=(int *)malloc(sizeof(int)*N);
    FOR(i,0,N){
        count=fscanf(fd,"%d",&array[i]);
        if(count!=1){
           printf("\n the input file does not have sufficient number of objects ");
           printf("\n as claimed to be ,sorting aborted \n");
           exit(0);
        }
    }

fclose(fd);
    begin=clock();
    int_timsort(array,N);
    end=clock();
    time_spent=(double)(end-begin);
    fd=fopen("output.txt","w+");
     if(fd==NULL){
            printf("\n failed to create output file \n");
            exit(0);
     }
    fprintf(fd,"\n %s  :  %15.6f \n","Time spent sorting : ",time_spent);
    FOR(i,0,N){ 
       fprintf(fd,"\n %d ",array[i]);
    }
    fclose(fd);
 /* scanf("%d",&N);
   int chk[N-1];
   for(i=0;i<N;i++){
     scanf("%d",&chk[i]);
   }
   
   printf("\n output in :   %15.6f\n",time_spent);  
   
   for(i=0;i<N && printf(" \n %d  \n",chk[i]);i++); */
   return 0;
 

}   
