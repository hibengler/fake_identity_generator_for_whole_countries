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
Separated from make_ssn_numbers - so that we can do  this faster


This takes l008.txt and adds the following:
birth state - merged from birthdates.txt
birth date
birth date code - date converted to a numberic value


Here is how we do it - fow now.
Birthdates are figured out and are in a file birthdates.txt

So for each record:
  set brith state to birth date- for now.
  set birth date
  expand out birth date


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


#define START_DATE "15-MAY-2013"

struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;
int ukmode=0; /* set to 1 for uk mode - uk does not ahve state migration info, so we skip that logic */
int id=1500000001;




struct searcher *mbirthdates;
struct searcher *mstate_migration_count;
struct searcher *mstate_migration;


int ssn_length[100000];
unsigned char ssn_numbers[125000000];

int init_numbers(unsigned char *numbers) {
memset(numbers,0,125000000);
int i;
for (i=0;i<100000;i++) {
  ssn_length[i]=10000;
  }
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
  else if (strcmp(argv[i],"-u")==0) {
    ukmode=1;
    }
  else {
    srandom(atoi(argv[i]));
    }
  }
  

mbirthdates = new_searcher("birthdates.txt",1,populate,locked);
if (!ukmode) {
  mstate_migration_count = new_searcher("state_migration_count.txt",1,populate,locked);
  mstate_migration = new_searcher("state_migration.txt",3,populate,locked);
  }
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
  char resident_state[20000];
  char birth_state[20000];
  set_number_of_fields(buf,49);
  field(buf,id,1);

  /* find the birth date */
  sprintf(searchline,"%s|",id);
  if (!search(mbirthdates,searchline,line)) {
     fprintf(stderr,"error cannot find date for %s\n",buf);
     exit(-1);
     }
     
  day = fieldi(line,1);

  code_to_date(day,date);
  field(buf,resident_state,14);

  
  if (!ukmode) {
    sprintf(searchline,"%s|",resident_state);
    search(mstate_migration_count,searchline,line);
    int state_size = fieldi(line,1);

    int variance=365;  
    int dy = day - variance + (random()>>2) % (variance*2+1);

    
    /* determine birth state */
    
    int state_index = ((random() >>2) % state_size) + 1; 
    sprintf(searchline,"%s|%010d|",resident_state,state_index);
    search(mstate_migration,searchline,line);  

    field(line,birth_state,2);
    
    sprintf(searchline,"%s|",birth_state);
    }

  /* come up with a frivilous state code to provide random order */  
  char *bufa;   
  bufa=buf;
  while ((*bufa)&&(*bufa != '|')) bufa++;
  int bdcode=day; /* birthdate code */
  bdcode = bdcode + 200 - ((random()>>2) % 400);
  bdcode = bdcode * 100 +  ((random()>>2) % 100); /* add some more randomness
                                                    so we don't end up always going
                                                    in the order of the id if
                                                     the date cod eis the same */
  printf("%s%010d%s|%s|%s|%d\n",birth_state,bdcode,bufa,birth_state,date,day);
  }
return(0);
}



