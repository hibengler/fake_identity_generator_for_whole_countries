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

Derived from make_gender_from_first_name.c

The UK name data is terrible,  some records are
last_name first_name (m)

and some are

first_name m last_name

So we parse them both,  then look at the data based on name to see which one seems correct.
???
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





struct searcher *lname_only;
struct searcher *fname_only;

int weight(struct searcher *searcher,char *name)
{
char searchline[20000];
char line[20000];
sprintf(searchline,"%s|",name);
if (search(searcher,searchline,line)) {
  int pos;
  int size=fieldi(line,1);
  if (!size) size=1;
  return size;
  }
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
  

fname_only = new_searcher("../common/us_fname_only.txt",1,populate,locked);
lname_only = new_searcher("../common/us_lname.txt",1,populate,locked);
return 0;
}


int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char out[20000];
char fname[20000];
char lname[20000];
char minit[20000];
char mname[20000];
char suffix[20000];
char altfname[20000];
char altlname[20000];
char altminit[20000];
char altmname[20000];
char altsuffix[20000];

char phase1[20000];
char phase2[20000];
char phase3[20000];
char gen[20000];


char listed_gender[10];
char preferred_gender[10];
while (gets(buf)) {
  field(buf,lname,2);
  field(buf,fname,3);
  field(buf,minit,4);
  field(buf,mname,5);
  field(buf,suffix,19);
  
  field(buf,altlname,33);
  field(buf,altfname,32);
  field(buf,altminit,34);
  field(buf,altmname,35);
  field(buf,altsuffix,36);
  
  if ((altlname[0]) && (altfname[0])) {
    if ( (strcmp(altlname,lname)!=0) ||
        (strcmp(altfname,fname)!=0)) {
      if (strlen(fname) >2) {
        int f,l,altf,altl;
	f = weight(fname_only,fname);
	l = weight(lname_only,lname);
	altf = weight(fname_only,altfname);
	altl = weight(lname_only,altlname);
//	fprintf(stderr,"%s %s reg %d,%d = %d   %s %s alt %d,%d = %d\n",fname,lname,f,l,f*l,altfname,altlname,altf,altl,altf*altl);
	if (f*l < altf*altl) {
	  strcpy(lname,altlname);
	  strcpy(fname,altfname);
	  strcpy(minit,altminit);
	  strcpy(mname,altmname);
	  strcpy(suffix,altsuffix);
//	  fprintf(stderr,".");
	  }
	}
      }
    }
  fieldspan(buf,phase1,0,1,1);
  fieldspan(buf,phase2,6,18,1);
  fieldspan(buf,phase3,20,30,1);
  printf("%s%s|%s|%s|%s|%s%s|%s\n",phase1,lname,fname,minit,mname,phase2,suffix,phase3);
  }
return(0);
}


