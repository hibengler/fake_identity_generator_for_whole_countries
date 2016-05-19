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
Usage:
Like elaborate_wives - excepting that this just gets a list of eligable bachelor addresses
Which is good to give a girl a place to marry.


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

char *fname_person;
  
char person[20000];
char husband[20000];
char prev_person_addr[20000];
prev_person_addr[0]='\0';
person[0]='\0';
char person_addr[20000];
husband[0]='\0';
int eligable_bachelor=1; /* eligible if there are no other women */
while (gets(person)) {
  fieldspan(person,person_addr,0,1,1);
	
  int cmp=strcmp(prev_person_addr,person_addr);
  strcpy(prev_person_addr,person_addr);
  if (cmp!=0 ) {
    if (husband[0]=='\0') { /* we did not find a husband */
      eligable_bachelor=0;
      }
    if (eligable_bachelor) {
      /* we need to build the woman's line up - everything the same as the husband but the gender.*/
      printf("%s\n",husband);
      }
    eligable_bachelor=1; /* eligible if there are no other women */
    husband[0]='\0';
    }
        
  char gender[20000];
  field(person,gender,2);
      
  if (gender[0]=='M') { /* possible husband */
    strcpy(husband,person);
    }
  else { /* another woman. */
    eligable_bachelor=0;
    }
  person[0]='\0'; /* show that we used this record */
  } /* while get line from main file */
      if (husband[0]=='\0') { /* we did not find a husband */
        eligable_bachelor=0;
        }
      if (eligable_bachelor) {
        /* we need to build the woman's line up - everything the same as the husband but the gender.*/
        printf("%s\n",husband);
        }

return(0);
}



