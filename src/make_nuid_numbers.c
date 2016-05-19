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
derived from make_ssn_numbers.c 3/22/2013

This takes l008.txt and adds the following:
null for birth state
birth date
birth date code - date converted to a numberic value
nuid_part_1  - 2 character prefix
nuid_part_2 - unique (within prefix) id number 6 digits starting with 1
nuid_part_3 - A,B,C,D randomly chosen
nuid - everything combined



So for each record:
 4. repeat:
	a. randomly find a number in the given year
	b. reject if used already
	until done
	


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





struct searcher *mstate_area;
struct searcher *mstate_area_count;

char codes[400][10];

unsigned int *all_nuid_numbers;
unsigned int *nuids_by_years[3000];
unsigned int year_lengths[3000];

int init_numbers() {
all_nuid_numbers = malloc(sizeof(unsigned int)*300000000);
{
  FILE *xf;
  unsigned int counter = 0;
  unsigned int prevyr=-1;
  xf=fopen("nuid_range_per_year.txt","r");
  if (!xf) {
    fprintf(stderr,"cannot open phone numbers.txt\n");
    exit(-1);
    }
  char buf[20000];  
  while (fgets(buf,19999,xf)) {
    unsigned int yr;
    unsigned int pos;
    char code[20000];
    unsigned int from;
    unsigned int to;
    yr = fieldi(buf,0);
    pos = fieldi(buf,1);
    field(buf,code,2);
    from = fieldi(buf,3);
    to = fieldi(buf,4);

    /* redundant - but fast eenough - get the code name */
    strcpy(codes[pos],code);
    
    if (prevyr != yr) {
      nuids_by_years[yr] = all_nuid_numbers + counter;
      year_lengths[yr]=0;
      prevyr=yr;
      }
    unsigned int i;
//    fprintf(stderr,"year %d from %d to %d\n",yr,from,to);
    for (i=from;i<=to;i++) {
      all_nuid_numbers[counter++] = pos*1000000 + i;
      year_lengths[yr]++;
      }
    }
  fclose(xf);
  } /* block to get all possible nuid numbers distributed by year */  
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
init_numbers();
return 0;
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
int failed;
failed=0;

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
  code_to_date(day,date);
  
  field(buf,birth_state,49);

  int nuid_part_1;
  int nuid_part_2;
  int nuid_part_3;
  char  nuidx[100];
  int tries=0;
  int variance;
  int ok=1;
  {
    /* determine nuid to search */
    int mm,dd,yy;
    
    date_to_mdy(date,&mm,&dd,&yy);
    
    int len;
    len = year_lengths[yy];
    if (len<=0) {
      fprintf(stderr,"%d out\n",yy,date);
      failed= -1;
      continue; /* error condition but we need to go throught hte whole file to adjust the distribution correctly */
      }
    int x;
    x = (random()>>1)%len;
    nuid_part_1 = nuids_by_years[yy][x] / 1000000;
    nuid_part_2 = nuids_by_years[yy][x] % 1000000;
    nuid_part_3 = (random()>>2)%4;
    sprintf(nuidx,"%s%6.6d%c",codes[nuid_part_1],nuid_part_2,'A' + nuid_part_3);
    
    nuids_by_years[yy][x] = nuids_by_years[yy][len-1];
    year_lengths[yy]--;
    }
  
  
  /* alright we got an nuid for now */
  /* get rid of sort code */
  char *b2;
  b2=buf;
  while ((*b2)&&(*b2 != '|')) b2++;
  printf("%s|%s|%6.6d|%c|%s\n",
      b2,codes[nuid_part_1],nuid_part_2,'A'+nuid_part_3,nuidx);
  }
return(failed);
}



