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
V1.1

We need to distribute the extra populace evenly and fairly amonst the population.
We are increaing male and female population, and making female population even with mail population
to do that, we need to distribute the population evenly-ish.
This does that job.  

This will also be used later for new house distribution.

input 1 will be

FIELDS|count|newcount

input 2 will be

FIELDS|morefields|count

output will be
FIELDS|morefields|count|newcount
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "util.h"



char buf[20000];
char obuf[20000];



int main (int argc, char *argv[]) {
int i;

char *fname_master;
char *fname_detail;
FILE *fm;
FILE *fd;
fname_master=argv[1];
fname_detail=argv[2];
fm = fopen(fname_master,"r");
if (!fm) {fprintf(stderr,"error fname %s not there\n",fname_master);
  exit(-1);
  }
fd = fopen(fname_detail,"r");
if (!fd) {fprintf(stderr,"error fname %s not there\n",fname_detail);
  exit(-1);
  }
char detail[20000];
detail[0]='\0';
while (fgets(buf,19999,fm)) {
  long long sample;
  long long target;
  int fields;
  int length;
  char head[20000];
  char tail[20000];
  { int s,t;
  get2counts(head,buf,&s,&t,&fields);
  sample=s;target=t;
  }
  length = strlen(head);
  long long chunk_target;
  long long chunk_sample;
  do {
    if (detail[0]=='\0') {
      if (!(fgets(detail,19999,fd))) {
        break;
        }
      }
    {int s;
    getcount(tail,detail,&s);
    chunk_sample=s;
    }
    strcat(tail,"|");
    if (strncmp(head,tail,length) ==0 ) {
      chunk_target = chunk_sample * target / sample;
      target -= chunk_target;
      sample -= chunk_sample;
      {
        int s = chunk_sample;
        int t = chunk_target;
        printf("%s%d|%d\n",tail,s,t);
        }
      detail[0]='\0';
      }
    else break;
    } while (1);
  } /* while get line from main file */
fclose(fm);
fclose(fd);
return(0);
}



