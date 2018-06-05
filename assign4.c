#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMVALS 100000
#define MAXVAL	5000
//#define NUMVALS 100
//#define MAXVAL  10

typedef struct input_data_struct_type {
    int val;
    struct input_data_struct_type *next;
}input_data_type;

input_data_type *head = NULL,*tail = NULL;


void *generate() {
    
    input_data_type *tofill;
    int insertcount = 0,newcount;
    int count = 0;

    while (count < NUMVALS) {
/*	if((count %1000) == 1) {
		printf("count = %d\n",count);
	}*/
	tofill = (input_data_type *)malloc(sizeof(input_data_type));
	tofill->val = rand() % MAXVAL;

	tofill->next=NULL;
	if (head == NULL) {
	    head = tofill;
	}
	else {
	    tail->next = tofill;
	}
	tail = tofill;
	count++;
    }
}

void *fcfs()
{
  input_data_type *x;
  int count = 0;
  int trackCon;
  int trackTrav;
  int curr, next;
  int i, j;
  //establish head, and keep track of travels
  x=head;
  trackCon=x->val;
  while(x->next != NULL){
      curr=x->val;
      next=x->next->val;
      trackTrav=abs(next-curr);
      // printf("TrackTrav= %d\n",trackTrav);
      trackCon=trackCon+trackTrav;
      x=x->next;
  }
  //print total number of travels
  printf("Total Tracks Traveled for FCFS = %d\n",trackCon);
  return 0;
}

void *scan()
{
  input_data_type *x;
  x=head;
  int i,j,n;
  int trackCon=0;
  int disk[100000];
  int dhead;
  int temp,max;
  int loc;
  int count;
  //scanning an array would be much easier. Sort numbers in terms of travel distance
  for(i=0;i<NUMVALS;i++){
    disk[i]=x->val;
    x=x->next;
  }
  n=NUMVALS;
  disk[n]=dhead;
  n=n+1;
  //sorts numbers, and count the amount of travels made
  for(i=0;i<n;i++){
    for(j=i;j<n;j++){
      if(disk[i]>disk[j]){
	temp=disk[i];
	disk[i]=disk[j];
	disk[j]=temp;
	count+=1;
	if(count%5==0){
	  trackCon=trackCon+(5000-disk[j]);
	}
      }
    }
  }
  max=disk[n];
  for(i=0;i<n;i++){
    if(dhead==disk[i]){
      loc=i;
      break;
    }
  }


  // printf("%d\n",count);
  //print test
  /* for(i=loc;i>0;i--){
    printf("%d -->",disk[i]);
  }
  printf("0 -->");
  for(i=loc+1;i<n;i++){
    printf("%d-->",disk[i]);
    }*/

  //print total number of travels
  trackCon=trackCon+dhead+max;
  printf("Total Track Travels for SCAN = %d\n",trackCon);
  return 0;
  
  

}


int displaynums()
{
    input_data_type *x;
    int count = 0;

    x = head;
    while(x) {
	printf("%d\n",x->val);
	++count;
	x = x->next;
    }
    printf("\ncount = %d\n\n",count);
    return(count);
}

main(argc,argv)
int argc;
char *argv[]; {
    
    pthread_t generate_thread;
    pthread_t fcfs_thread;
    pthread_t scan_thread;

    srand( (int)time(NULL) );

    if(pthread_create(&generate_thread,NULL,generate,NULL) != 0) {
	perror("Generate numbers thread create");
    }
    if(pthread_join(generate_thread,NULL) != 0) { 
	perror("Generate thread join");
    }

    if(pthread_create(&fcfs_thread,NULL,fcfs,NULL) != 0) {
	perror("FCFS thread create");
    }
    if(pthread_join(fcfs_thread,NULL) != 0) { 
	perror("FCFS thread join");
    }
    if(pthread_create(&scan_thread,NULL,scan,NULL) != 0) {
	perror("SCAN thread create");
    }
    if(pthread_join(scan_thread,NULL) != 0) { 
	perror("SCAN thread join");
    }

    // displaynums();


}
