/*
Fake Identity Generator
Copyright (C) 2011-2016 Hibbard M. Engler (Bitcoin address 1ERDHsxtekdh5FAsxdb92PBFK7nnuwMkbp for gifts)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/* 
V1.5 = fixed a bug in the range check - instead of by begin/end date, it is by begin/end code
V1.4 - changed the algorighm to go by state, and then by code.
V1.3 - improved the algorithm
V1.2 - sped up by tapping the numbers around it
V1.1 - slowed down like noones business as ssn numbers were tapped out

This takes l008.txt and adds the following:
birth state
birth date
birth date code - date converted to a numberic value
ssn_part_1
ssn_part_2
ssn_part_3
ssn



So for each record:
 4. repeat:
	a. find a ssn number for the state
	b. randomize between the two interpolation points
	c. reject if dead
	d. reject if used already
	until not rejected
	


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "util.h"
#include "bsearch.h"
#include "uthash.h"


#define START_DATE "15-APR-2013"

struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;

int id=1500000001;




struct searcher *mstate_area;
struct searcher *mstate_area_count;


int ssn_min_code[1000];
int ssn_max_code[1000];
unsigned char ssn_numbers[125000000];

int init_numbers(unsigned char *numbers) {
memset(numbers,0,125000000);
}

static unsigned char f[8] = {1,2,4,8,16,32,64,128};
static unsigned char nf[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


int number_used(unsigned char *numbers,int code) {
unsigned char t;

/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
pnum = code;

/* find the flag */
t = numbers[pnum>>3] & (f[pnum&7]);
t = !t;
t = !t;
return t;
}






void set_number_used(unsigned char *numbers,int code,
  int value)
{
unsigned char t;


/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
pnum  = code;

/* find the flag */
t = numbers[pnum>>3];
if (value) {
  t = t | f[pnum&7];
  }
else {
  t = t & nf[pnum&7]; 
  }
numbers[pnum>>3]=t;
}







int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-p")==0) {
    populate=1;
    }
  else if (strcmp(argv[i],"-l")==0) {
    locked=1;
    }
  else {
    srandom(atoi(argv[i]));
    }
  }
  

mstate_area = new_searcher("state_area.txt",3,populate,locked);
mstate_area_count = new_searcher("state_area_count.txt",1,populate,locked);

/* eliminate the dead people's ssn numbers */
{
  init_numbers(ssn_numbers);
  int i;
  for (i=0;i<1000;i++) {
    ssn_min_code[i]=010101;
    ssn_max_code[i]=999997;
    }
  
  FILE *xf;
  char buf[20000];
  xf = fopen("ssdi_sample_cleaned.txt","r");
  while (fgets(buf,20000,xf)) {
    int a=fieldi(buf,0);
    set_number_used(ssn_numbers,a,1);
    }
  fclose(xf);
  
  
  
  /* find the min and max ranges based on the sample of dead people */
  {
    int preva=0;
    int prevnum;
    xf = fopen("by_code.txt","r");
    while (fgets(buf,20000,xf)) {
      int a=fieldi(buf,0);
      int num=fieldi(buf,1);

            
      if (a!= preva) { /* new main prefix */
        if (preva) {
	  int pn=prevnum+30000; /* fudgeit */
	  if (pn>=1000000) pn=999999;
	  ssn_max_code[preva]= pn;
	  }
	ssn_min_code[a] =num;
	}
      preva=a;
      prevnum=num;
      }
    if (preva) {
      int pn=prevnum+30000; /* fudgeit */
      if (pn>=1000000) pn=999999;
      ssn_max_code[preva]= pn;
      }					      
    fclose(xf);
    for (i=0;i<1000;i++) {
 //     fprintf(stderr,"eliminating SSN %d outside code %6d to %6d\n",i,ssn_min_code[i],ssn_max_code[i]);
      int j;
      for (j=0;j<ssn_min_code[i];j++) {
        int ssnbase = j;
        int ssn_part_2 = ssnbase / 10000;
        int ssn_part_3 = ssnbase % 10000;
        ssn_part_2 = code_to_base(ssn_part_2);
        int ssn = i * 1000000 + ssn_part_2 * 10000 + ssn_part_3;
        set_number_used(ssn_numbers,ssn,1);
	}
      for (j=ssn_max_code[i]+1;j<1000000;j++) {
        int ssnbase = j;
        int ssn_part_2 = ssnbase / 10000;
        int ssn_part_3 = ssnbase % 10000;
        ssn_part_2 = code_to_base(ssn_part_2);
        int ssn = i * 1000000 + ssn_part_2 * 10000 + ssn_part_3;
        set_number_used(ssn_numbers,ssn,1);
        }
      }
    } /* find min max rqanges */
  } /* eliminate dead people also */

return 0;
}


int code_base[] = {0,1,3,5,7,9,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
                  46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,
		  94,96,98,2,4,6,8,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,
		  45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,
		  93,95,97,99};

int code_to_base(int from) 
{
return code_base[from];
}




int main (int argc, char *argv[]) {
init(argc,argv);
struct value_struct *values;
struct value_struct *c;
values = NULL;
char buf[20000];
char searchline[20000];
char line[20000];
char id[20000];
while (gets(buf)) {
  int sample;
  int target;
  int f;
  int day;
  int pos;
  char date[20000];
  char birth_state[20000];
//  set_number_of_fields(buf,49);
  field(buf,id,1);
  
  
     
  day = fieldi(buf,51);
  field(buf,birth_state,49);

  int ssn_part_1;
  int ssn_part_2;
  int ssn_part_3;
  int ssn;
  int tries=0;
  int variance;
  int ok=1;
  do {
    tries++;
    if (tries>1000) {
      ok=0;
      break;
      }
    /* determine ssn to search */
    sprintf(searchline,"%s|",birth_state);
    search(mstate_area_count,searchline,line);  
    int size = fieldi(line,1);
    
      
    if (tries<100) {
      int index = ((random()>>2) % size) + 1;
      sprintf(searchline,"%s|%010d|",birth_state,index);
      search(mstate_area,searchline,line);
      ssn_part_1 = fieldi(line,2);
      }
    else {
      ssn_part_1 = 700 + (random()>>2) % 29; /* railroad */
      }  
    
 //   if (tries>50) {
 //     fprintf(stderr,"%s	%s	%d 	%d	left\n",id,birth_state,ssn_part_1, ssn_max_code[ssn_part_1]-ssn_min_code[ssn_part_1]);
 //     }
    ok=0;
    while (ssn_min_code[ssn_part_1] < ssn_max_code[ssn_part_1]) {
      int ssnbase;
      ssnbase = ssn_min_code[ssn_part_1];
      ssn_part_2 = ssnbase / 10000;
      ssn_part_3 = ssnbase % 10000;
      ssn_part_2 = code_to_base(ssn_part_2);
      ssn = ssn_part_1 * 1000000 + ssn_part_2 * 10000 + ssn_part_3;
      if (!(number_used(ssn_numbers,ssn))) {
        ssn_min_code[ssn_part_1]=ssnbase+1;
        ok=1;
        break;
        }
      else {
        ssn_min_code[ssn_part_1]=ssnbase+1;
        }   
      }
    
    } while (!ok);
  
  if (!ok) {
    fprintf(stderr,"ran out in state %s\n",birth_state);
    int i;
    for (i=0;i<1000;i++) {
      fprintf(stderr,"ssn prefix %d from %06d to %06d\n",i,ssn_min_code[i],ssn_max_code[i]);
      }
    fprintf(stderr,"ran out in state %s\n",birth_state);
    exit(-1);
    }
  set_number_used(ssn_numbers,ssn,1);
  
  /* alright we got an ssn for now */
  /* get rid of sort code */
  char *b2;
  b2=buf;
  while ((*b2)&&(*b2 != '|')) b2++;
  printf("%s|%03d|%02d|%04d|%03d-%02d-%04d\n",
      b2,ssn_part_1,ssn_part_2,ssn_part_3,
                       ssn_part_1,ssn_part_2,ssn_part_3);
  }
return(0);
}



