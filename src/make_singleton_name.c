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
/* This shuffles up the singletons.
V1.3 - placed the singleton stuff int he common area
V1.2 made it so that the first name has to be filled in, same with last anems, made the middle initial extruded properly
V1.1 original
ID
Yes, individuals with unique names, are going to have dopplegangers that also have unique names.
But they will be different in EVERY way.

This reads formthe main name program the people who dont easily get converted into other names.
Everything is being done at once -first,last, middle init, middle name, and suffix
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


int populate=0;
int locked=0;





struct searcher *gender_count;
struct searcher *last_name;
struct searcher *first_name;
struct searcher *middle_initial;
struct searcher *middle_initial_fake;
struct searcher *middle_name;
struct searcher *name_suffix;





int find_new_names_via_singleton(char *fname, char *lname, 
   char *listed_gender,
   char *special_gender,
   char *minit,
   char *mname,
   char *suffix,
   char *new_fname,
   char *new_lname,
   char *new_minit,
   char *new_mname,
   char *new_suffix
   )
{
char searchline[20000];
char line[20000];
char a[20000];
char b[20000];
char c[20000];
char d[20000];
int size;
int fsize;
int lsize;

/* find the total numner of rows for each gender */
sprintf(searchline,"%s|",listed_gender);
search(gender_count,searchline,line);
size = fieldi(line,1);
if (size==0) {
  fprintf(stderr,"problem with gender %s on %s\n",listed_gender,line);
  }
  
do {
#define r {pos =(random()>>2) % size+1;\
  sprintf(searchline,"%s|%010d|",listed_gender,pos);}
#define s(a,b) {search(a,searchline,line); field(line,b,2);}
  int pos;
  
  r;
  s(last_name,new_lname);
  r;
  s(first_name,new_fname);
  r;
  s(middle_initial,new_minit);
  if (new_minit[0]) { /* if we have initials */
    new_minit[1]='\0';
    sprintf(searchline,"%s|%s|",listed_gender,new_minit);
    search(middle_initial_fake,searchline,line);
    /* find a middle name to go with them thare initials */
    int msize = fieldi(line,2);
    if (msize<=1) {
      pos=0;
      }
    else {
      pos = (random()>>2) % msize+1;
      }
    sprintf(searchline,"%s|%s|%010d|",listed_gender,new_minit,pos);
    search(middle_name,searchline,line);
    field(line,new_mname,3);
    }
  else new_mname[0]='\0';
  
  r;
  s(name_suffix,new_suffix);
  
  } while ((strcmp(fname,new_fname)==0)||
           (strcmp(lname,new_lname)==0)||
	   (minit[0] && strcmp(minit,new_minit)==0)||
           (mname[0] && strcmp(mname,new_mname)==0)||
           (suffix[0] && strcmp(suffix,new_suffix)==0)||
	   (new_fname[0]=='\0') ||
	   (new_lname[0]=='\0') ||
	   ((new_minit[0]!='\0')&&new_mname[0]=='\0'));
return 1;
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
  

gender_count = new_searcher("../common/singleton_gender.txt",1,populate,locked);
last_name = new_searcher("../common/singleton_lname.txt",2,populate,locked);
first_name = new_searcher("../common/singleton_fname.txt",2,populate,locked);
middle_initial = new_searcher("../common/singleton_minit.txt",2,populate,locked);
middle_initial_fake = new_searcher("../common/minit_fake.txt",2,populate,locked);
middle_name = new_searcher("../common/singleton_mname.txt",3,populate,locked);
name_suffix = new_searcher("../common/singleton_suffix.txt",2,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char oldid[20000];
char phase1[20000];
char new_fname[20000];
char new_lname[20000];
char new_minit[20000];
char new_mname[20000];
char new_suffix[20000];
char fname[20000];
char mname[20000];
char minit[20000];
char suffix[20000];

char lname[20000];
char listed_gender[10];
char special_gender[10];
while (gets(buf)) {
  if (strncmp(buf,"warning",7)==0) continue;
  if (strncmp(buf,"|||||||",7)==0) continue;
  fieldspan(buf,phase1,0,30,0);
  field(buf,oldid,31);
  field(buf,lname,2);
  field(buf,fname,3);
  field(buf,minit,4);
  field(buf,mname,5);
  field(buf,suffix,19);
  field(buf,listed_gender,25);
  if (listed_gender[0]=='\0') continue;
  if (listed_gender[1]!='\0') {
    special_gender[0] = listed_gender[1];
    special_gender[1] = '\0';
    listed_gender[1] = '\0';
    }
  else {
    special_gender[0] = listed_gender[0];
    special_gender[1] = '\0';
    }
  find_new_names_via_singleton(fname,lname,listed_gender,special_gender,
        minit,mname,suffix,
        new_fname,new_lname,new_minit,new_mname,new_suffix);
    printf("%s|%s|%s|%s|%s|%s|%s|1|\n",phase1,oldid,new_fname,new_lname,new_minit,new_mname,new_suffix);
  }
return(0);
}


