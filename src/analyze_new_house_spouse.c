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
ID
1.2
1.2 Jan 2012 - simplified the system to just have the new full address
Dec 29, 2011 - this is supposed to analyze the new house spouse from elaboratE_household
This is a new way of doing this,  so we have the husband/wife stuff all pretty much figured out - then the 
filters for hd adding spouses is all we have to do.

Usage:
variable of elaborate_wives - but for generic people.

Reads from households.txt:
1	0	new full address
2	1	new city
3	2	new state
4	3	old id
5	4	gender
6	5	new id
7	6	old spouse id

We assume that this is sorted - which means that the husband wife pair will be together.


So - what happens when we get one spouse and don't have the other - well, we don't print out the record.
Only when we see the other one do we print out both.
This makes it a simple state setup

stdout: husband|

Oututs to stdout STANDARD004-ish  with the gender as a double gender FM gets a female name from a male name
Outputs to stderr analysis for husband|wife
oldid|new number|new subdivision type|new subdivision number|new city|new state|new_id|old_spouse_id
husband|wife pair - which is to be used later to make the husband_wife complete



*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "util.h"





char buf[20000];
char pbuf[20000];
char obuf[20000];



int init (int argc, char *argv[]) {
return 0;
}

int main (int argc, char *argv[]) {
int i;
init(argc,argv);

int prev_old_id;
int prev_old_spouse_id;
int prev_new_id;
int count;
prev_old_spouse_id = 0;
prev_new_id = 0;
prev_old_id = 0;
count = 0;

while (gets(buf)) {
  int old_id,new_id,old_spouse_id;
  char gender[2000];
  old_id = fieldi(buf,3);
  field(buf,gender,4);
  new_id = fieldi(buf,5);
  old_spouse_id = fieldi(buf,6);
  if (prev_old_id) {
    if (old_spouse_id == prev_old_id) {
      if (old_id == prev_old_spouse_id) {
        if (strcmp(gender,"M")==0) {
          printf("%d|%d\n",new_id,prev_new_id);  
  	  fprintf(stderr,"%d|%d\n",prev_new_id,new_id);
	  prev_old_id = 0; /* so we don't join up to many times of two addresses are similar */
	  prev_new_id = 0;
	  prev_old_spouse_id = 0;
	  count=0;
  	  }
        else {
          printf("%d|%d\n",prev_new_id,new_id);
  	  fprintf(stderr,"%d|%d\n",new_id,prev_new_id);
	  prev_old_id = 0;
	  prev_new_id = 0;
	  prev_old_spouse_id = 0;
	  count=0;
          }
        }
      else {
        fprintf(stderr,"X|x|prev_spouse!=old|old %s    new %s\n",pbuf,buf);
        exit(-1);
        }
      }
    else if (old_id == prev_old_spouse_id) {
      fprintf(stderr,"X|x|spouse!= prev old|old %s    new %s\n",pbuf,buf);
      exit(-1);
      }
    }
  else if (count != 0) {
    fprintf(stderr,"X|x|missing match|old %s    new %s\n",pbuf,buf);
    exit(-1);
    }  
  prev_old_id = old_id;
  prev_new_id = new_id;
  prev_old_spouse_id = old_spouse_id;
  count++;
  strcpy(pbuf,buf);  
  } /* while get line from main file */
return(0);
}



