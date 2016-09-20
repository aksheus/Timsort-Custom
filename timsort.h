#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#define MIN_RUN_SIZE 7
#define STACK_SIZE 66        //using a fixed size stack
typedef struct{
 int* index;
 int length;
 }run;  //object for 'runs' in an array to be sorted
 typedef struct{
   int *storage;   //stores the current 'runs' in the stack
   run runs[STACK_SIZE];
   int stack_height; //index of the first unwritten element of the stack
   int *partitioned_up_to;
   //keeps track of how far partitions are made if anything < partitioned upto it's on the stack 
   // and everythin >= partitoned is not yet on the stack if when partitioned upto ==length
   // it means that we haveput everything onto the stack
   int *array;
   int length;
}sort_state_struct;


typedef sort_state_struct* sort_state;
void int_timsort(int [],int  );
void insertion_sort(int [],int );
void swap(int * , int *);
void merge(int [],int [],int ,int [],int ,int []);
int next_partition(sort_state );
int should_collapse(sort_state );
void merge_collapse(sort_state );

void reverse(int array[],int length){        //if runs are in decreasing order helper fucntion to reverse the runs in place 
    int *start=array;
	int *end=array+length-1;
	while(start<end){
	      int x=*start;
		  *start=*end;
		  *end=x;
		  start++;
		  end--;
    }
}

void boost_run_length(sort_state state,run* run){
//while selecting parition get minrun length  array send minruns to insertion sort
 int length=state->length-(run->index-state->array);
 if(length> MIN_RUN_SIZE) 

length=MIN_RUN_SIZE;
    insertion_sort(run->index,length);
    run->length=length;
}	

int next_partition(sort_state state){
    //determine next run
	if(state->partitioned_up_to >= (state->array + state->length)) return 0; //wev reached the end no more runs
	
	int * start_index=state->partitioned_up_to;
	//to find increasing run from start_index
	int* next_start_index=start_index+1;
	if(next_start_index <  (state->array+state->length)){  //#recheck to see if next start index dosen't exceed the array limits
	   if(*next_start_index < *start_index) //well have a decreasin run
	    {
		  while(next_start_index< (state->array+state->length)){
		    if(*next_start_index < *(next_start_index-1))
			   next_start_index++;
			else
			  break;
		  }
		  
		  reverse(start_index,next_start_index-start_index); //reverse the decrasin //run
	     }

else{
		 //well have an increasin run as wanted
		 while(next_start_index < (state->array+state->length)){
		      if(*next_start_index >= *(next_start_index -1))
			     next_start_index++;
			  else
			    break;
			}
		}
	}
	
	//we need to push  [start_index ,next_start_index ) which is an increasing run onto //the stack
	run run_to_add;
	run_to_add.index=start_index;
	run_to_add.length=(next_start_index-start_index);
	
	if(run_to_add.length< MIN_RUN_SIZE)
	   boost_run_length(state,&run_to_add);
	
	state->partitioned_up_to=start_index+run_to_add.length;
	state->runs[state->stack_height]=run_to_add;
	state->stack_height++;
	
	return 1;


}

int should_collapse(sort_state state){ //#check wether merge condition satisfies 
    if(state->stack_height<=2) return 0;
	int h=state->stack_height-1;
	int top_length=state->runs[h].length;
	int next_length=state->runs[h-1].length;
	
	return (2*top_length) > next_length;
}
void merge_collapse(sort_state state){  //collapse the top two on the stack if merge condition satisfied then called
     run first=state->runs[state->stack_height-2];
	 run second=state->runs[state->stack_height-1];
	 
	 merge(first.index,first.index,first.length,second.index,second.length,state->storage);
	 
	 state->stack_height--;
	 first.length+=second.length;
	 state->runs[state->stack_height-1]=first;
}
void merge(int target[],int p1[],int l1,int p2[],int l2,int storage[] ){   //standard merge in merge sort
     int *merge_to=storage;
     int i1,i2;
	 

           i1=i2=0;
	 
	 int *next_merge_element=merge_to;
	 // iterate over both the arrays writing the least element at the current position 
	   // to merge_to ,when both are equal left is preffered for stability 
	 while(i1<l1 && i2<l2){
	  if(p1[i1]<=p2[i2]){
	    *next_merge_element=p1[i1];
		i1++;
	  }
	  else{
	  *next_merge_element=p2[i2];
	  i2++;
	  }
	    next_merge_element++;
	}
	 //copy the leftover elements 
	 memcpy(next_merge_element,p1+i1,sizeof(int)*(l1-i1));
	 memcpy(next_merge_element,p2+i2,sizeof(int)*(l2-i2));
	 
	 //#copy to target array
	 memcpy(target,merge_to,sizeof(int)*(l1+l2));
}
void swap(int *first,int* second){
  int temp=*first;
  *first=*second;

  *second=temp;
}
void insertion_sort(int *minrun,int length){        //#2 #REMEM#SEETHIS#SHIT#IMP
   if(length<=1) return;
   int i;
   for(i=1;i<length;i++){
      int x=minrun[i];
	  int j=i-1;
	  while((x<minrun[j]) && (j>=0)){
	    minrun[j+1]=minrun[j];
		j--;
	 }
	 minrun[j+1]=x;
  } 
}
void int_timsort(int array[],int size){
     sort_state_struct state;
	 state.storage=(int *)malloc(sizeof(int)*size);  //#1
	 state.stack_height=0;
	 state.partitioned_up_to=array;
	 state.array=array;
	 state.length=size;
	 while(next_partition(&state)){              //while there are runs and element to be pushed is not greater than twice the top then collapse em
	   while(should_collapse(&state))
	         merge_collapse(&state);

 }
	 while (state.stack_height > 1) merge_collapse(&state);  //collapse everything on the stack to get sorted array
	 free(state.storage);
}
