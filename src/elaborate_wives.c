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
V1.3 - Nov 5 - for some reason the code to make names now makes 2 letter gender and this was not writtent o handle that
As you know,  the first letter is the new gender, and the second is the original
so if the second exists,  handle it
V1.2 does ac
V1.1
Usage:
elaborate_wives wives.txt person_by_house.txt  >unnamed_wives.txt 2>justgirls.txt

Elaborate wives - We have a file with a list of addresses that get a female,  possibly a wife.
And we have a list of households sorted by addres.

So we read through the wives - and for each potential wife, we read through the household
and see if there is a husband to match.  If so, we give the wife the home, age range, etc.
If not, we make the wife a regular female person and drop them into the stderr bucket.
The regular persons - will be combined with the additional regular persons that are added in order 
to give us a fuller population.

But wives are handled differently, as we know the last name is safe on the street, we can 
later name them only changing the first name, which will ne more efficient.

The full population gets names generated differntly.

Reads from person_by_house.txt which has  zip address STANDARD005
and reads from wives.txt which has zip address newid

Oututs to stdout STANDARD004-ish
Outputs to stderr ZIP|address|gender|id


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

char *fname_wife;
char *fname_person;
FILE *fm;
FILE *fd;
fname_wife=argv[1];
fname_person=argv[2];
fm = fopen(fname_wife,"r");
if (!fm) {fprintf(stderr,"error fname %s not there\n",fname_wife);
  exit(-1);
  }
fd = fopen(fname_person,"r");
if (!fd) {fprintf(stderr,"error fname %s not there\n",fname_person);
  exit(-1);
  }
  
char prev_wife_addr[20000];
char person[20000];
prev_wife_addr[0]='\0';
person[0]='\0';

while (fgets(buf,19999,fm)) {
  char wife_addr[20000];
  /* clip off the \n */
  {int y;
  y = strlen(buf);
  if ((y) && (buf[y-1] == '\n')) buf[y-1] = '\0';
  }
  int fields;
  int length;
  int id;
  int oldid;
  fieldspan(buf,wife_addr,0,1,1);
  id = fieldi(buf,2);
  /* did we already add a wife here? */
  if (strcmp(wife_addr,prev_wife_addr)==0) {
    fprintf(stderr,"%sF|%d\n",wife_addr,id);
    continue;
    }
  strcpy(prev_wife_addr,wife_addr);
  length = strlen(wife_addr);
  char husband[20000];
  char person_addr[2000];
  int eligable_bachelor=1; /* eligible if there are no other women */
  husband[0]='\0';
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
	
    int cmp=strcmp(wife_addr,person_addr);
    if (cmp==0 ) {
      char gender[20000];
      field(person,gender,2+ 25); 
      if (gender[1]) { /* this is stupid because the gender will always be MM or FF at this stage. used to be M or F but I changed make_name_from_name so we put this in */
        gender[0]=gender[1];
	gender[1]='\0';
	}
      if (gender[0]=='M') { /* possible husband */
        strcpy(husband,person);
	}
      else { /* another woman. */
        eligable_bachelor=0;
	}
      person[0]='\0'; /* show that we used this record */
      }
    else if (cmp>0) {
      /* some people do not get wives, skip em */
      person[0]='\0'; /* show that we used this record */
      continue; 
      }
    else {
      /* this address is different. Save it for later */
      break;
      }
    } while (1);
  if (husband[0]=='\0') { /* we did not find a husband */
    eligable_bachelor=0;
    }
  if (eligable_bachelor) {
    /* we need to build the woman's line up - everything the same as the husband but the gender.*/
    char phase1[20000];
    char phase2[20000];
    char phase3[20000];
    char lname[20000];
    oldid = fieldi(husband,3);
    fieldspan(husband,phase1,2+2,2+16,1);  /* skip error + id, lname to zip, skip phone number prefix and rest, but take area code */
    fieldspan(husband,phase2,2+19,2+24,1); /* after phone to just before gender */
    fieldspan(husband,phase3,2+26,2+30,1); /* after gender to second street direction, */
    field(husband,lname,2+33); /* new last name */
    printf("|%d|%s||%sFM|%s%d||%s|||||||\n",id,phase1,phase2,phase3,oldid
            ,lname);
    }
  else {
    fprintf(stderr,"%sFM|%d\n",wife_addr,id);
    }
  } /* while get line from main file */
fclose(fm);
fclose(fd);
return(0);
}



