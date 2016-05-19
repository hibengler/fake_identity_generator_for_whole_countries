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
V1.4
V1.4 Jan 2012 - fixed minor bug. Changed first column of stderr to be the new full address
V1.3 Dec 2011 - made this use husband_wives and wife_husbands in order to determine new husband wife pairs before we rename everything
                This makes it cool

V1.2 - Jul 23 - made search handle multiple ocurrences
Usage:
variable of elaborate_wives - but for generic people.

Reads from households.txt:
1	0	zipcode
2	1	street direction
3	2	spanish street name
4	3	street name
5	4	street type
6	5	second street direction
7	6	from number
8	7	from sudivision type
9	8	from sub number
10	9	new number
11	10	new subdivision type
12	11	new subdivision number

stdin: l006.txt

Oututs to stdout STANDARD004-ish  with the gender as a double gender FM gets a female name from a male name
Outputs to stderr analysis for husband|wife

1	0	new full address
2	1	new city
3	2	new state
4	3	old id
5	4	gender
6	5	new id
7	6	old spouse id

Used to be
nes street number|new subdivision type|new subdivision number|new city|new state|oldid|gender|new_id|old_spouse_id
But that was not enough to differentiate so I changed to full street address

husband|wife pair - which is to be used later to make the husband_wife complete



*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "util.h"
#include "bsearch.h"
int id=1700000000;




int populate=0;
int locked=0;

struct searcher *mhousehold;
struct searcher *mhusband_wife;
struct searcher *mwife_husband;

char buf[20000];
char obuf[20000];



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
mhousehold = new_searcher("households.txt",9,populate,locked);
mhusband_wife = new_searcher("old_husband_wife.txt",1,populate,locked);
mwife_husband = new_searcher("old_wife_husband.txt",1,populate,locked);
return 0;
}

int main (int argc, char *argv[]) {
int i;
init(argc,argv);

char prev_pers_addr[20000];
char person[20000];
prev_pers_addr[0]='\0';
person[0]='\0';

while (gets(buf)) {
  char searchline[20000];
  char line[20000];
  char gender[20000];
  char zip[20000];
  char street_direction[20000];
  char spanish_name[20000];
  char street_name[20000];
  char street_type[20000];
  char second_street_direction[20000];
  char old_street_number[20000];
  char old_subdivision_type[20000];
  char old_subdivision_number[20000];
    char ac[20000];
    char prefix[20000];
  field(buf,zip,15);
  field(buf,street_direction,8);
  field(buf,spanish_name,29);
  field(buf,street_name,9);
  field(buf,street_type,10);
  field(buf,gender,25);
  gender[1]='\0'; /* clip the double part */
  field(buf,second_street_direction,30);
  field(buf,old_street_number,7);
  field(buf,old_subdivision_type,11);
  field(buf,old_subdivision_number,12);
  field(buf,ac,16);
  field(buf,prefix,17);
  int new_id;
  sprintf(searchline,"%s|%s|%s|%s|%s|%s|%s|%s|%s|",
       zip,street_direction,spanish_name,street_name,street_type,
       second_street_direction,old_street_number,
       old_subdivision_type,old_subdivision_number);
       
  unsigned long long nextline = 0;
  int f1=0;
  int f2=0;
  do {
    if (f1) f2=search_next(mhousehold,searchline,line,&nextline);
    else f2=search_first(mhousehold,searchline,line,&nextline);
    
    if (!f2) break;
    f1=1;
    /* we need to build the persons's line up - 
        everything the same as the mark*/
    
    /* but first set stderr with the line for debugging purposes */
//    fprintf(stderr,"%s\n",line);
    
    char new_street_number[20000];
    char new_subdivision_type[20000];
    char new_subdivision_number[20000];
    char new_city[20000];
    char new_state[20000];
    char phase1[20000];
    char phase2[20000];
    char phase3[20000];
    char  stage[20000];
    char full_address[20000];
    char *comma = "";
    int old_id;
    old_id = fieldi(buf,1);
       
    
    field(line,new_street_number,9);
    field(line,new_subdivision_type,10);
    field(line,new_subdivision_number,11);
    field(line,new_city,12);
    field(line,new_state,13);
    fieldspan(buf,phase1,2,5,1);  /* keep the name */
    

    new_id = id++;

    
    
    full_address[0]='\0';
    if (new_street_number[0]) {
      strcat(full_address,comma);
      strcat(full_address,new_street_number);
      comma=" ";
      }
    if (street_direction[0]) {
      strcat(full_address,comma);
      strcat(full_address,street_direction);
      comma=" ";
      }
    if (spanish_name[0]) {
      strcat(full_address,comma);
      strcat(full_address,spanish_name);
      comma=" ";
      }
    if (street_name[0]) {
      strcat(full_address,comma);
      strcat(full_address,street_name);
      comma=" ";
      }
    if (street_type[0]) {
      strcat(full_address,comma);
      strcat(full_address,street_type);
      comma=" ";
      }
    if (second_street_direction[0]) {
      strcat(full_address,comma);
      strcat(full_address,second_street_direction);
      comma=" ";
      }
    if (new_subdivision_type[0]) {
      strcat(full_address,comma);
      strcat(full_address,new_subdivision_type);
      comma=" ";
      }
    if (new_subdivision_number[0]) {
      strcat(full_address,comma);
      strcat(full_address,new_subdivision_number);
      comma=" ";
      }
    int oldid = fieldi(buf,1);
    fieldspan(buf,phase2,19,30,0);
    printf("|%d|%s%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s||%s|%d\n",new_id,phase1,full_address,
        new_street_number,street_direction,street_name,street_type,
	new_subdivision_type,new_subdivision_number,new_city,new_state,zip,
	ac,prefix,
	phase2,oldid);
   
   
    {
      char sl2[20000];
      char line[20000];
      sprintf(sl2,"%d|",old_id);
      if (search(mhusband_wife,sl2,line)) {
	int old_id2=fieldi(line,1);
	fprintf(stderr,"%s|%s|%s|%d|%s|%d|%d\n",full_address,
	           new_city,new_state,old_id,gender,new_id,old_id2);
	}
      else if (search(mwife_husband,sl2,line)) {
	int old_id2=fieldi(line,1);
	fprintf(stderr,"%s|%s|%s|%d|%s|%d|%d\n",full_address,
	           new_city,new_state,old_id,gender,new_id,old_id2);
	}
      /* only care if they are married */
      } /* block to search for new records */
	    

   
   
    } while (1); /* do while we match things */
  } /* while get line from main file */
return(0);
}



