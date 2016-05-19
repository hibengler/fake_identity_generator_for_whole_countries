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
/* V1.2 

V1.2 - we obscure the phone number to just be area code prefix 
we can get the original number from L003
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

int id=1000000001;



int keep=0; /* keep the phone number for gender assignment.  Used for UK */



struct searcher *fname_gender;
struct searcher *fname_only;

int random_gender_from_first_name(char *fname,char *line)
{
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|",fname);
if (search(fname_only,searchline,line)) {
  int pos;
  int size=fieldi(line,1);
  if (size)
    pos =(random()>>2) % size+1;
  else pos=0;  
  sprintf(searchline2,"%s|%010d|",fname,pos);
  search(fname_gender,searchline2,line);
  return size;
  }
else {
  strcpy(line,"a|000|F"); /*default to female */
  return(1);
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
  else if (strcmp(argv[i],"-k")==0) {
    keep=1;
    fprintf(stderr,"keep\n");
    }
  else {
    srandom(atoi(argv[i]));
    }
  }
  

fname_gender = new_searcher("fname_gender.txt",2,populate,locked);
fname_only = new_searcher("fname_only.txt",1,populate,locked);
return 0;
}


int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char out[20000];
char fname[20000];
char phase1[20000];
char phase2[20000];
char phase3[20000];
char gen[20000];

char lname[20000];
char listed_gender[10];
char preferred_gender[10];

while (gets(buf)) {
  field(buf,gen,25);
  if (strcmp(gen,"M")&&(strcmp(gen,"F"))) {
    if (keep) {
      field(buf,fname,3);
      fieldspan(buf,phase1,2,17,1);
      fieldspan(buf,phase2,18,24,1);
      fieldspan(buf,phase3,26,300,1);
      random_gender_from_first_name(fname,out);
      field(out,gen,2);
      printf("|%d|%s%s%s|%s\n",id,phase1,phase2,gen,phase3);
      }
    else {
      field(buf,fname,3);
      fieldspan(buf,phase1,2,17,1);
      fieldspan(buf,phase2,19,24,1);
      fieldspan(buf,phase3,26,300,1);
      random_gender_from_first_name(fname,out);
      field(out,gen,2);
      printf("|%d|%s|%s%s|%s\n",id,phase1,phase2,gen,phase3);
      }    
    }
  else {
    fieldspan(buf,phase1,2,300,1);
    printf("|%d|%s\n",id,phase1);
    }
  id++;
  }
return(0);
}


