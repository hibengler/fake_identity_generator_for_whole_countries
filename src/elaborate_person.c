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
V1.3 - Nov 5 - for some reason the code to make names now makes 2 letter gender and this was not writtent o handle that
As you know,  the first letter is the new gender, and the second is the original
so if the second exists,  handle it
V1.2 - Added area code
V1.1
Usage:
variabt of elaborate_wives - but gor generic people.

elaborate_person person.txt person_by_house.txt  >unnamed_person.txt 2>bad_person.txt

Elaborate person - We have a file with a list of addresses that get a new person, and their gender.
And we have a list of households sorted by address.

So we read through the people, 
 - and pick a person who loved at the address. First person is fine.  
 We then output the gender differently - instead if F we have FM 
 which means female name from male name
Which is used by the name generator in wife mode.

Reads from person_by_house.txt which has  zip address STANDARD005
and reads from person.txt which has zip address newid and Gender

Oututs to stdout STANDARD004-ish  with the gender as a double gender FM gets a female name from a male name
Outputs to stderr ZIP|address|id|gender|ac - but we don't use this error stuff anyways.


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

char *fname_pers;
char *fname_person;
FILE *fm;
FILE *fd;
fname_pers=argv[1];
fname_person=argv[2];
fm = fopen(fname_pers,"r");
if (!fm) {fprintf(stderr,"error fname %s not there\n",fname_pers);
  exit(-1);
  }
fd = fopen(fname_person,"r");
if (!fd) {fprintf(stderr,"error fname %s not there\n",fname_person);
  exit(-1);
  }
  
char prev_pers_addr[20000];
char person[20000];
prev_pers_addr[0]='\0';
person[0]='\0';

while (fgets(buf,19999,fm)) {
  char to_gender[20000];
  char pers_addr[20000];
  char ac[20000];
  int fields;
  int length;
  int id;
  fieldspan(buf,pers_addr,0,1,1);
  field(buf,to_gender,3);
  field(buf,ac,4);
  to_gender[1] = '\0'; /* get rid of new line */
  id = fieldi(buf,2);
  /* did we already add a pers here? */
  if (strcmp(pers_addr,prev_pers_addr)==0) {
    fprintf(stderr,"%s|%d|%s|%s\n",pers_addr,id,to_gender,ac);
    continue;
    }
  strcpy(prev_pers_addr,pers_addr);
  length = strlen(pers_addr);
  char person_addr[20000];
  char mark[20000];  
  mark[0]='\0';
  do {
    if (person[0]=='\0') {
      if (!(fgets(person,19999,fd))) {
        break;
        }
      }
        /* clip off the \n */
    {int y;
    y = strlen(person);
    if ((y) && (person[y-1] == '\n')) person[y-1] = '\0';
    }

    fieldspan(person,person_addr,0,1,1);
	
    int cmp=strcmp(pers_addr,person_addr);
    if (cmp==0 ) {
      char gender[20000];
      strcpy(mark,person);
      person[0]='\0'; /* show that we used this record */
      }
    else if (cmp>0) {
      person[0]='\0'; /* show that we used this record */
      continue; 
      }
    else {
      /* this address is different. Save it for later */
      break;
      }
    } while (1);
  if (mark[0]!='\0') { /* we did not find a mark */
    /* we need to build the woman's line up - everything the same as the mark but the gender.*/
    char phase1[20000];
    char phase2[20000];
    char phase3[20000];
    char lname[20000];
    char gender[20000];
    int oldid;
    fieldspan(mark,phase1,2+2,2+16,1);  /* skip error + id, lname to zip, skip some of phone number - but do have the area code */
    fieldspan(mark,phase2,2+19,2+24,1); /* after phone to just before gender */
    fieldspan(mark,phase3,2+26,2+30,1); /* after gender to second street direction, */
    field(mark,gender,2+ 25); 
    if (gender[1]) { /* this is stupid because the gender will always be MM or FF at this stage. used to be M or F but I changed make_name_from_name so we put this in */
      gender[0]=gender[1];
      gender[1]='\0';
      }
    field(mark,lname,2+33);
    oldid =fieldi(mark,2+1); // we will use the old last name here I think.
    printf("|%d|%s||%s%s%s|%s%d||%s||||||\n",id,phase1,phase2,
    to_gender,gender,phase3,oldid,lname);
    }
  else {
    fprintf(stderr,"%s|%d|%s\n",pers_addr,id,to_gender);
    }
  } /* while get line from main file */
fclose(fm);
fclose(fd);
return(0);
}



