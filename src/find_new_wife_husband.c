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
This is derived from marry_people,  but it aint marrying anybody



Thes reads from new_address_lname_gender_oldid_newid.txt that has teh following format:
1	0	zip
2	1	full address
3	2	old id
4	3	new id


And this also reads wife_husband that has the following format:
1	0	wife_id
2	1	husband_id


From this,  we compute the following - for the same address:
1	0	new_wife_id
2	1	new_husband_id


This is then used by marry_people,  in order to give the proper surnames to the 
wives.

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





struct searcher *wife_husband; // old wife_husband before we expanded to fake addresses






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
  

wife_husband = new_searcher("wife_husband.txt",1,populate,locked);
return 0;
}



static void gather_spouses(char **people,int num_people,char *address);

int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char searchline[20000];
char line[20000];
char id[20000];
char idm[20000];
#define MAX_PEOPLE 10000
char *people[MAX_PEOPLE];

/* allow up to MAX_PEOPLE (200) people to be stored for one address */
int i;
for (i=0;i<MAX_PEOPLE;i++) {
  people[i]=malloc(sizeof(char)*20000);
  people[i][0]='\0';
  }

int people_on_address;
char last_address[20000];

/*set up our mechanism to keep track of all people in our little world */
people_on_address=0;
last_address[0]='\0';

while (gets(buf)) {
  char address[20000];
  fieldspan(buf,address,0,1,0);
  
  if (strcmp(address,last_address) != 0) {
    gather_spouses(people,people_on_address,last_address);
    people_on_address=0;
    strcpy(last_address,address);
    }
  fieldspan(buf,line,2,3,0);
  strcpy(people[people_on_address],line);
  people_on_address++;
  }
if (last_address[0]) {
  gather_spouses(people,people_on_address,last_address);
  }
exit(0);
}
  
  
  
  
static void gather_spouses(char **people,int num_people,char *address) {
int i,j;
for (i=0;i<num_people;i++) {
  char *possible_wife = people[i];
  char id[20000];
  char searchline[20000];
  char line[20000];
  field(possible_wife,id,0);
  sprintf(searchline,"%s|",id);
  if (search(wife_husband,searchline,line)) { /* if we are a wife */
     char newid[20000];
     char idm[20000];
     int hubby_found=0;
     field(possible_wife,newid,1);
     field(line,idm,1); /* get the husbands oldid */
     for (j=0;j<num_people;j++) {
       if (j==i) continue;
       char *possible_husband = people[j];
       char checkid[20000];
       field(possible_husband,checkid,0);
       if (strcmp(checkid,idm) ==0) {
         char newmid[20000];
	 field(possible_husband,newmid,1);
         fprintf(stdout,"%s|%s\n",newid,newmid);
	 hubby_found=1;
	 break; /* yes if we have multiple spouses assigned with the same id - this breaks
	            but we don't do that, OK?  and if we did, we would loose a small percentage
		    of marriages.  Big deal.  The world would be better off.
		    I mean marriage and the pursiut of happiness are at odds alot
		    but we get children, which is cool.  Society changes as it needs to
		    but too slowly for my taste. Anyways... */
		/* yes - I had a chocolate bar this morning */
	 }
      } /* for each person - looking for the hubby */
    if (!hubby_found) {
      fprintf(stderr,"Cannot find husband|%s|%s|%s\n",
         address,possible_wife,idm); /* should show the address infoirmation too - oh well */
      }
    } /* if we are a wife */
  } /* for looking for wives */
}


