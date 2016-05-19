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
V1.3
V1.3 added -o
V1.2 Added -n to 
V1.1 Original
match.c is like field.c and it uses bsearch at the same time
Usage:
match <input 1 3 4 match.txt >match.out 2>nomatch.out
It has the same fields - except that the field is matched against a filter file
If the fields exist, then the original record goes to stdout
If the fields do not exist,  then the original goes to stderr
This is good to check names against other names.



options:

-p - preload all the file in memory.  Good if we have the memory. Like 100x good!
-l - lock in memory.  Good if we are pushing the limits of the machine.
-n - flip the order - make standard error contain the matches, and standard output contain
           the ok ones.  This is good when we are filtering against matches, and flowing from
	   one set of data to the next.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "util.h"
#include "bsearch.h"


#define MAXFIELDS 1000
int fields[MAXFIELDS];


int output_search_field_only; /* tricky - output the searched field instead*/
int fieldcount=0;

char *fpos[10000];

char buf[20000];
char obuf[20000];

int populate=0;
int locked=0;
int flip=0;
FILE *fmatch;
FILE *fnomatch;

struct searcher *filter_searcher;


int init (int argc, char *argv[]) {
int i;
char *fname;
for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-p")==0) {
    populate=1;
    }
  else if (strcmp(argv[i],"-l")==0) {
    locked=1;
    }
  else if (strcmp(argv[i],"-n")==0) {
    flip=1;
    }
  else if (strncmp(argv[i],"-o",2)==0) {
    output_search_field_only=atoi(argv[i]+2);
    }
  else if ((argv[i][0] >='0')&&(argv[i][0] <='9')) {
    int w;
    w=atoi(argv[i]);
    if (w != 0) {
      fields[fieldcount++] = w;
      }
    }
  else {
    fname = argv[i];
    }
  }
  

filter_searcher = new_searcher(fname,fieldcount,populate,locked);
if (flip) {
  fmatch = stderr;
  fnomatch = stdout;
  }
else {
  fmatch = stdout;
  fnomatch = stderr;
  }

return 0;
}



int main (int argc, char *argv[]) {
struct value_struct *values;
struct value_struct *c;
int all_in_memory_flag;
int sortflag=0;
char bufcopy[20000];
char line[20000];
values = NULL;
int i;
int markerfields=-1;
int memposition=1;
int memfiles = 0;

init(argc,argv);


while(gets(buf) != NULL) {
  strcpy(bufcopy,buf);
  /* split it out */
  int cols=0;
  char *q= buf;
  char *r = q;
  char *optr = obuf;
  while (*r) {
    while (*r &&(*r != '|')) r++;
    fpos[cols++] =q;
    if (*r) {
      *r = '\0';
      r++;
      }
    q=r;    
    }
    
  for (i=0;i<fieldcount;i++) {
    int pos = fields[i]-1;
    if (pos<cols) {
      char *iptr;
      for (iptr = fpos[pos];*iptr;iptr++) {
        *optr++ = *iptr;
	}
      }
    *optr++ = '|';
    }
  
  *optr='\0';

    /* see if it is in the file */
  if (search(filter_searcher,obuf,line)) {
    if (output_search_field_only) {
      field(line,bufcopy,output_search_field_only);
      }
    if (bufcopy[0]) /* print only if not blank */
      fprintf(fmatch,"%s\n",bufcopy);
    }
  else {
    if (!output_search_field_only)
      if (bufcopy[0]) /* print only if not blank */
        fprintf(fnomatch,"%s\n",bufcopy);
    }
  }

return(0);
}


