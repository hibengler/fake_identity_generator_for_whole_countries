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
This makes, but does not name wives.
Wives are females who are attached to an address with a male member.
They might be not wives, dependng on the makeup of the family unit.
That will be determined later. First, we need to know their address.

Simple output:
1	0	zipcode
2	1	address
3	2	id number

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
#include "uthash.h"
#include "bsearch.h"


struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;

int id=1400000001;




struct searcher *mhouse;
struct searcher *mzip;



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
  

mhouse = new_searcher("mhouse.txt",3,populate,locked);
mzip = new_searcher("mzip.txt",1,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
struct value_struct *values;
struct value_struct *c;
values = NULL;
char buf[20000];
char phase1[20000];
char zip[20000];
char searchline[20000];
char line[20000];
char address[20000];
char listed_gender[10];
while (gets(buf)) {
  int sample;
  int target;
  int f;
  int size;
  int pos;
  if (strncmp(buf,"warning",7)==0) continue;
  if (strncmp(buf,"|||||||",7)==0) continue;
  get2counts(phase1,buf,&sample,&target,&f);
  field(buf,listed_gender,0);
  field(buf,zip,1);
  for (c=values; c!= NULL; c=values) {
    HASH_DELETE(hh,values,c);
    free(c);
    }      

  if (listed_gender[0]=='F') { /* if we are a wife */
    sprintf(searchline,"%s|",zip);
    if (!search(mzip,searchline,line)) continue; /* skip f there are no men eligable - so we loose a couple
        of women, big deal */
    size = fieldi(line,1);
    int i=0;
    while (i <target-sample) {
      if (i>=size-4) break;
      do {
        if (size) {pos=(random()>>2) % size+1;} else {pos=0;}
        sprintf(searchline,"%s|%010d|",zip,pos);
        search(mhouse,searchline,line);
        field(line,address,2);
	/* quit if we are overloaded */
        /* see if it already exists */
	HASH_FIND_STR(values,address,c);
	if (!c) {
	  break;
	  }
        } while (1);
      int l=strlen(address);
      c = malloc(sizeof(struct value_struct) + (l+1) * sizeof(char));
      if (!c) {
        fprintf(stderr,"Out of memory! darn!\n");
        exit(-1);
        }
      c->value = (char *)(c+1);
      strcpy(c->value,address);
      HASH_ADD_KEYPTR(hh,values,c->value,l,c);
      printf("%s|%s|%d\n",zip,address,id);
      id++;
      i++;
      }
    }
  }
return(0);
}


