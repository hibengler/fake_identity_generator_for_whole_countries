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
This reads from address_lname_gender in the following format:
Zipcode|address|lname|gender|ID


the idea is that if there is a husband and wife pair, they will be like the following:

94403|304 hillsdale blvd|Smith|F|23221
94403|304 hillsdale blvd|Smith|M|444342

Same last name in same address, male/female.  They are married.
Now, in real life, some of these are not married, and some married couples 
do not have the same last names.
But we don't care. It is close enough.


So we output to standard output the links for husband, and for wife.
Then we can Marry them easily.
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




int init (int argc, char *argv[]) {
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char address[20000];
char lname[20000];
char gender[20000];
char id[20000];
char prev_address[20000];
char prev_lname[20000];
char prev_gender[20000];
char prev_id[20000];

prev_address[0]='\0';
prev_lname[0]='\0';
prev_gender[0]='\0';
prev_id[0]='\0';

while (gets(buf)) {
  fieldspan(buf,address,0,1,1);
  field(buf,lname,2);
  field(buf,gender,3);  
  field(buf,id,4);
  if ((strcmp(address,prev_address)==0) &&
      (strcmp(lname,prev_lname)==0) &&
      (strcmp(gender,"M")==0) &&
      (strcmp(prev_gender,"F")==0)) {
    printf("%s|%s\n",id,prev_id);
    fprintf(stderr,"%s|%s\n",prev_id,id);
    }
  strcpy(prev_address,address);
  strcpy(prev_lname,lname);
  strcpy(prev_gender,gender);
  strcpy(prev_id,id);
  }
return(0);
}


