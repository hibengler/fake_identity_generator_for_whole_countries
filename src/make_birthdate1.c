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

This takes l008.txt and adds the following:
birth date code - date converted to a numberic value


Here is how we do it - fow now.
1. Figure out the birthdate - use the age grouping if possible,
2. If a wife, married - send to stderr
3. If a husband, or single, send to stdout.

The next phase will adjust the ages based on marriage.


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


#define START_DATE "15-May-2013"

struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;

int id=1500000001;




struct searcher *mall_wife_husband;








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
  

mall_wife_husband = new_searcher("all_wife_husband.txt",1,populate,locked);



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
char age_group[20000];
char id[20000];
while (gets(buf)) {
  int sample;
  int target;
  int f;
  int start_date;
  int size;
  int pos;
  field(buf,age_group,21);
  int day;
  

     
  /* figure out the age */
  start_date = date_to_code(START_DATE);
  if (strcmp(age_group,"18 To 24")==0) {
    start_date = start_date - 18*(365+365+365+366)/4;
    int range = (25-18)*(365+365+365+366)/4;
    day =  start_date - (random()>>2)  % range;
    }
  else if (strcmp(age_group,"25 To 34")==0) {
    start_date = start_date - 25*(365+365+365+366)/4;
    int range = (35-25)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;
    }
  else if (strcmp(age_group,"35 To 44")==0) {
    start_date = start_date - 35*(365+365+365+366)/4;
    int range = (45-35)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;
    }
  else if (strcmp(age_group,"45 To 54")==0) {
    start_date = start_date - 45*(365+365+365+366)/4;
    int range = (45-35)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;
    }
  else if (strcmp(age_group,"55 To 64")==0) {
    start_date = start_date - 55*(365+365+365+366)/4;
    int range = (65-55)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;
    }
  else if (strcmp(age_group,"65 And Older")==0) {
    start_date = start_date - 65*(365+365+365+366)/4;
    int range = (83-65)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;
    }
  else { /* Unknown */  
    start_date = start_date - 18*(365+365+365+366)/4;
    int range = (83-18)*(365+365+365+366)/4;      
    day =  start_date - (random()>>2)  % range;      
    }
 
  field(buf,id,1);
  sprintf(searchline,"%s|",id);
  if (!search(mall_wife_husband,searchline,line)) {
    fprintf(stdout,"%s|%d\n",id,day);
    }
  else {
    char husband[20000];
    field(line,husband,1);
    fprintf(stderr,"%s|%s|%d\n",id,husband,day);
    }
  }
return(0);
}


