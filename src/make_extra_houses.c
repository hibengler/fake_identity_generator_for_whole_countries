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
This makes households.  In order to do this, the following happens
V1.6 - bug with values2 not being initialized or cleaned up.
V1.5 - dealt with the adding
V1.4 - added ac phone prefix
V1.3 - Added a check to make sure the from houses are unique. Cuz otherwise we do not get out full constituents
later on.
V1.2 Added the second set of houses - the ones with extra blocks added to the end
We use these only if we need to, to make the addresses nicer. :)



1. Read the zipcode file to get the numebr of people to create additionally
2. Read in all the fake houses from the fake pool for the given zipcode.
3. While there are more people needed
4.   pick a random house
5.   Find the people in a random real house on that street
6.    Use these people as a sample for the new people on the new house, output them

But if we run out,  we will use houses from newhouse2.txt - which are less desireable because they are 
made by adding an extra 2 blocks to every street.


extra people - male and female.

input - zip_a.txt
1	0	zip code
2	1	current number of people
3	2	target number of people


This also reads the following files:
newhouse.txt - list of all new houses
newhouse2.txt - second list with street numbers that are bigger than the real city. used as a last resort.
newhouse_zipcount.txt - used to figure out the index fro newhouse - so we can choose a house ranomly
newhouse_zipcount2.txt - similar for newhouse2.txt
street.txt - a list of the streets with a count of people on the street
house_index.txt - used to pick an input/from house randomly


Output is a L004 format I believe.
1	0	zipcode
2	1	street direction
3	2	spanish street name
4	3	street name
5	4	street type
6	5	second street direction
7	6	from number
8	7	from sudivision type
9	8	from sub number
10	9	new number
11	10	new subdivision type
12	11	new subdivision number
13	12	City
14	13	State
15	14	oldid
This is meant to be fed into the evaluate_houses - that
will tahe this sorted list and mach against the real addresses - which will
allow us to make candidate people based on the "old houses" and the same number
of people will be in the "new" house.


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

struct value_struct {
int id;
char *value;
UT_hash_handle hh;
};






int populate=0;
int locked=0;




FILE *newhousefd;
FILE *newhousefd2;
struct searcher *mnewhouse = NULL;
struct searcher *mnewzip;
struct searcher *mnewhouse2 = NULL;
struct searcher *mnewzip2;
struct searcher *mstreet;
struct searcher *mhouse;

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
  
newhousefd = fopen("newhouse.txt","r");
newhousefd2 = fopen("newhouse2.txt","r");
mnewzip = new_searcher("newhouse_zipcount.txt",1,populate,locked);
mnewzip2 = new_searcher("newhouse_zipcount2.txt",1,populate,locked);
mstreet = new_searcher("street.txt",6,populate,locked);
mhouse = new_searcher("house_index.txt",7,populate,locked);
return 0;
}





struct searcher *new_searcher_zipcode(FILE *fd,char *zipcode,
    int searchfields,char *lastline,int locked) {
  struct searcher *s;
  s = malloc(sizeof(struct searcher));
  s->filename = "<//Unlisted//>";
    int flags;
    int i;
    char *map;  /* mmapped array of int's */
    char *mptr;
    size_t size;
    size=500000000; /* should be enough */
    s->map= map = malloc(size);
      if (!map) {
        fprintf(stderr,"Error memory\n");
	exit(-1);
	}
    s->searchfields=searchfields;
    
/* this fails sometimes    if (locked) {
      int x=mlock(map,size);
      if (x!= 0)
        {
	fprintf(stderr,"error locking\n");
	}
      }*/
    mptr = map;
    *map = '\0';
    while (1) {
      if (lastline[0] == '\0') {
        if (!fgets(lastline,20000,fd)) {
	  break;
	  }
	}
      int l=strlen(zipcode);
      int c=strncmp(zipcode,lastline,l);
      if (c<0) {
        break;
	}
      if (c==0) {
        l = strlen(lastline);
	strcat(mptr,lastline);
	mptr= mptr+l;
	}
      lastline[0]='\0';
      }
      s->size = mptr-map;
      return(s);
    }



int main (int argc, char *argv[]) {
init(argc,argv);
struct value_struct *values;
struct value_struct *values2 = NULL;
struct value_struct *c;
values = NULL;
char buf[20000];
char phase1[20000];
char zip[20000];
char searchline[20000];
char line[20000];
char address[20000];
char previous_zip[20000];
char lastline[20000];
char lastline2[20000];
char listed_gender[10];
lastline[0]='\0';
lastline2[0]='\0';
previous_zip[0]='\0';
while (gets(buf)) { /* the zipcode */
  int sample;
  int target;
  int f;
  int size;
  int size2;
  int pos;
  if (strncmp(buf,"warning",7)==0) continue;
  if (strncmp(buf,"|||||||",7)==0) continue;
  get2counts(phase1,buf,&sample,&target,&f);
  field(buf,zip,0);
  /* clear out the hash table */
  for (c=values; c!= NULL; c=values) {
    HASH_DELETE(hh,values,c);
    free(c);
    }
  /* clear out the other hash table */
  for (c=values2; c!= NULL; c=values2) {
    HASH_DELETE(hh,values2,c);
    free(c);
    }
  if (mnewhouse) {
    free(mnewhouse->map);
    free(mnewhouse);
    }
  mnewhouse =new_searcher_zipcode(newhousefd,zip,2,lastline,locked);
  if (mnewhouse2) {
    free(mnewhouse2->map);
    free(mnewhouse2);
    }
  mnewhouse2 =new_searcher_zipcode(newhousefd2,zip,2,lastline2,locked);
  sprintf(searchline,"%s|",zip);
  if (search(mnewzip,searchline,line)) {
    size = fieldi(line,1);
    }
  else size=0;
  if (search(mnewzip2,searchline,line)) {
    size2 = fieldi(line,1);
    }
  else size2=0;
  
  int houses_made=0;

  int i=0;
  while (i <target-sample) {
    int other_flag=0;
    
    if (houses_made+5 >size) {
      other_flag=1;
      }
    else {
      int t=1;
      do {
    
        if (size) {pos=(random()>>2) % size + 1;} else {pos=0;}
        sprintf(searchline,"%s|%010d|",zip,pos);
        search(mnewhouse,searchline,line);
        fieldspan(line,address,2,11,1);
        /* see if it already exists */
        HASH_FIND_STR(values,address,c);
        if (!c) {
	  break;
 	  }
        t++;
        } while (t<1000000);
      if (t==1000000) {
        fprintf(stderr,"E\nEEE %s %d s %d m %d\n",zip,target-sample,size,houses_made);
        other_flag=1;
        }
      }
   if (other_flag) {
      int t=1;
      if (houses_made+5 >size + size2) {
        break;
	}
      do {
    
        if (size2) {pos=(random()>>2) % size2 + 1;} else {pos=0;}
        sprintf(searchline,"%s|%010d|",zip,pos);
        search(mnewhouse2,searchline,line);
        fieldspan(line,address,2,11,1);
        /* see if it already exists */
        HASH_FIND_STR(values2,address,c);
        if (!c) {
	  break;
 	  }
        t++;
	
        } while (t<1000000);
      if (t==1000000) {
        fprintf(stderr,"E\nEEE2 %s %d s %d m %d\n",zip,target-sample,size,houses_made);
	break;
        }
//     fprintf(stderr,"%s %d %d\n",zip,target-sample,t);

      }    

    
    houses_made ++;
    int l=strlen(address);
    c = malloc(sizeof(struct value_struct) + (l+1) * sizeof(char));
    if (!c) {
      fprintf(stderr,"Out of memory! darn!\n");
      exit(-1);
      }
    c->value = (char *)(c+1);
    strcpy(c->value,address);
    if (other_flag) {
      HASH_ADD_KEYPTR(hh,values2,c->value,l,c);
      }
    else {
      HASH_ADD_KEYPTR(hh,values,c->value,l,c);
      }
    /* Actually we do much more here */
    /* We need to find a real address on the same street */
    {
      char p1[20000];
      char p2[20000];
      char p3[20000];
/*      char p4[20000];*/
      int size2;
      int pos2;
      fieldspan(line,p1,2,6,1);
      sprintf(searchline,"%s|%s",zip,p1);
      search(mstreet,searchline,line);
      size2 = fieldi(line,6);
      int t=1;

      if (size2) {pos2=(random()>>2) % size2 + 1;} else {pos2=0;}
      sprintf(searchline,"%s|%s%010d|",zip,p1,pos2);
      search(mhouse,searchline,line);
      fieldspan(line,p2,7,9,1);
      fieldspan(address,p3,5,9,1);
      /*fieldspan(line,p4,10,11,1);*/ /* ac and zipcode */
	

      /* output the old/new address to the world */
      int ll= fieldi(line,10);
      printf("%s|%s%s%s|%d\n",zip,p1,p2,p3,ll);
      i += ll;
/*     int y=ll-1;
       fprintf(stderr,"|");
      while (y) {
        fprintf(stderr,".");
        y--;
        }    
       */ 
      }
    } /* while we do not have items */
  fprintf(stderr,"%s h(%d=%d+%d) p(%d) -> h(%d) p(%d)\n",
     zip,size+size2,size,size2,target-sample,houses_made,i);
    
  } /* for each zipcode line from zip_a.txt */
return(0);
}

