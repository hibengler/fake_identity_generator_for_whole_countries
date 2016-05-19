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
marry_people2 is a variabt of marry_people that is made for hf... 
when we are adding streets and stuff
We read from new_wife_husband instead of wife_husband and new_last_name instead of last_name

and there are minor differences beyond that
ID
This marries people based on an assumption that they were married
The assumption is that they have the same last name, are male and female,
and live in the same house.




Turns out this is pretty complex to do.  We know the original 
husbands and wives, 
and can use that to find the new husbands and wives.
That is done in other parts.  So we use new_wife_husband.txt to 
identify the new wives
to new husbands and change the surname, and maiden name accordingly.



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





struct searcher *wife_husband;
struct searcher *new_last_name;






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
  

wife_husband = new_searcher("new_wife_husband.txt",1,populate,locked);
new_last_name = new_searcher("new_last_name.txt",1,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char searchline[20000];
char line[20000];
char phase1[20000];
char phase2[20000];
char new_lname[20000];
char id[20000];
char idm[20000];
char gender[20000];
char lname[20000];
while (gets(buf)) {
  fieldspan(buf,phase1,0,32,1);
  fieldspan(buf,phase2,34,37,0);
  field(buf,lname,33);
  field(buf,gender,25);
  gender[1]='\0'; /* clip the gender changers */  
  field(buf,id,1); /* new id */
  if (strcmp(gender,"F")==0) {
    /* see if we are a wife */
     sprintf(searchline,"%s|",id);
    if (search(wife_husband,searchline,line)) { /* if we are a wife */
      field(line,idm,1); /* find the husband's last name */
      sprintf(searchline,"%s|",idm);
      if (search(new_last_name,searchline,line)) {
        field(line,new_lname,1);
	fprintf(stderr,"%s%s|%s|%s\n",phase1,new_lname,phase2,lname); 
	           /* split out the females - the men are done */
	continue;
	}	
      }
    }
  printf("%s%s|%s|\n",phase1,lname,phase2);
  }
return(0);
}


