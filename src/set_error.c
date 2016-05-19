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
set error - set the first field to a speci
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "uthash.h"
#include "util.h"


#define MAXFIELDS 1000
int fields[MAXFIELDS];
int ifields[MAXFIELDS];
int ifields_count=0;

int fieldcount=0;

char *fpos[10000];

char buf[20000];
char obuf[20000];
int reverse_matching=0;
char bufcpy[20000];
FILE *yesf;
FILE *nof;

int main (int argc, char *argv[]) {
int i;

for (i=1;i<argc;i++) {
  if (strncmp(argv[i],"-n",2)==0) {
    reverse_matching=1;
    continue;
    }
  int w=0;
    w=atoi(argv[i]);
    ifields[ifields_count++]=w;
  }
if (reverse_matching) {
  yesf=stderr;nof=stdout;
  }
else {
  yesf=stdout;nof=stderr;
  }

while(gets(buf) != NULL) {
  strcpy(bufcpy,buf);
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

  int flag=1; /* If we process or not */
  if (ifields_count) {
    for (i=0;i<ifields_count;i++) {
      if (fpos[ifields[i]-1][0] == '\0') { /* if we are empty at this field */
        flag=0; /* we aint loadin this one */
	break;
	}
      }
    }    
  if (flag) {
    fprintf(yesf,"%s\n",bufcpy);
    }
  else {
    fprintf(nof,"%s\n",bufcpy);
    }
  }
return(0);
}



