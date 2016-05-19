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

This makes phone numbers
Reads from l007 and tries to add

A residential phone - if there was a phone,  or 30% of the time.

A cell phone - 70% of the time


1. read the numbers_per_street.txt to ge the number of people who have a residential phone on that street
2. Read the street_phone_prefix.txt  - to get possible phone prefixes

for each person
  if residential is needed:
  if phone is not known, pick the prefix based on streed - if you can - if not, give up.
  loop
    Pick a phone number -
    until you find one that is not the same as the real phone numberm and
       you find a number that is unique.  ( try for a real phone number 3 times )
  flag the phone as unique.
  
  if cell is needed:
  pick the prefix based on zipcode -> areacode. randomized cell phone prefix.
  loop
   pick
     until you find one that is not the same and unique - real try 2 times
     end looop

  print out the new persons phone number.
    

note - all 5555 0079 and 9970 numbers are out of the loop

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
#include "uthash.h"
#include "phone_common.h"

struct value_struct {
int id;
char *value;
UT_hash_handle hh;
};

int populate=0;
int locked=0;




FILE *newhousefd;
FILE *newhousefd2;
struct searcher *numbers_per_street = NULL;
struct searcher *phone_prefix_by_street = NULL;
struct searcher *prefixes_for_ac = NULL;
struct searcher *prefixes_of_ac = NULL;
struct searcher *acs_per_zip = NULL;
struct searcher *acs_by_zip = NULL;







unsigned char all_numbers[1250000000];

int init_numbers(unsigned char *numbers) {
memset(numbers,0,1250000000);
}


int number_used(unsigned char *numbers,char * area_code,char *prefix, char * rest) {
unsigned char t;


/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
ac = atoi(area_code);
pf = atoi(prefix);
r = atoi(rest);
pnum  = ((long long)(ac)) * 10000000 + ((long long)pf) * 10000 + ((long long)r);

/* find the flag */
t = numbers[pnum>>3] & (f[pnum&7]);
t = !t;
t = !t;
return (t);
}


void set_number_used(unsigned char *numbers,char * area_code,char *prefix, char * rest,
  int value)
{
unsigned char t;


/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
ac = atoi(area_code);
pf = atoi(prefix);
r = atoi(rest);
pnum  = ((long long)(ac)) * 10000000 + ((long long)pf) * 10000 + ((long long)r);

/* find the flag */
t = numbers[pnum>>3];
if (value) {
  t = t | f[pnum&7];
  }
else {
  t = t & nf[pnum&7]; 
  }
numbers[pnum>>3]=t;
}





int init(int argc, char *argv[]) {
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
  
numbers_per_street = new_searcher("numbers_per_street.txt",7,populate,locked);
phone_prefix_by_street = new_searcher("phone_prefix_by_street.txt",8,populate,locked);

prefixes_for_ac = new_searcher("prefixes_for_ac.txt",1,populate,locked);
prefixes_of_ac = new_searcher("prefixes_of_ac.txt",2,populate,locked);
acs_per_zip = new_searcher("acs_per_zip.txt",1,populate,locked);
acs_by_zip = new_searcher("acs_by_zip.txt",2,populate,locked);

init_phone_name_filters(argc,argv);


init_numbers(all_numbers);

return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
struct value_struct *values;
struct value_struct *values2;
struct value_struct *c;
values = NULL;
char buf[20000];
char phase1[20000];
char zip[20000];
char searchline[20000];
char line[20000];
char address[20000];
char previous_zip[20000];
char lastline[20000];
char lastline2[20000];
char listed_gender[10];
lastline[0]='\0';
lastline2[0]='\0';
previous_zip[0]='\0';






while (gets(buf)) { /* the zipcode */
  int f;
  int size;
  int size2;
  int pos;
  char area_code[100];
  char prefix[100];
  char rest_phone[100];
  char new_rest_phone[100];
  char ac1[100];
  char prefix1[100];
  char rest1[100];
  char ac2[100];
  char prefix2[100];
  char rest2[100];
  char fname[20000];
  char lname[20000];
  
  int randomac=0;    
  
  if (strncmp(buf,"warning",7)==0) continue;
  if (strncmp(buf,"|||||||",7)==0) continue;
  field(buf,area_code,16);
  field(buf,prefix,17);
  field(buf,rest_phone,18);
  field(buf,zip,15);
  field(buf,fname,32); /* new first name */
  field(buf,lname,33); /* new last name */
  
  {char rest[200000];
  field(buf,rest,1);
  }
  long long actual_number=-1;
  int flag=0;
  // flag will be if residental is needed
  if ((*area_code == 0)) { /* if we have no area code*/
    fprintf(stderr,"error no area code%s\n",buf);
    exit(-1);
    }  
  if ((*area_code)&&(*prefix)) { /* if we have a match */
    flag=1;
    
    int ac,pf,rest;
    rest=0;ac=0;pf=0;
    ac=fieldi(buf,16);
    pf=fieldi(buf,17);
    rest=fieldi(buf,18);
    if (rest != 0) {
      actual_number = ((long long)(ac)) * 10000000 + ((long long)pf) * 10000 + ((long long)rest);
      }
    }
  else if ((random()>>2) % 100 <30) { /* if we should try to add a residential number */
    flag=1;
      
    char a[1000];
    char b[1000];
    char c[1000];
    char d[1000];
    char e[1000];
    char f[1000];
    field(buf,a,15);
    field(buf,b,8);
    field(buf,c,29);
    field(buf,d,9);
    field(buf,e,10);
    field(buf,f,30);
    sprintf(searchline,"%s|%s|%s|%s|%s|%s|%s|",a,b,c,d,e,f,area_code);
    // get a prefix based on the city/zip
    if (search(numbers_per_street,searchline,line)) {
      size = fieldi(line,7);
      if (size) {pos=(random()>>2) % size + 1;} 
         else {fprintf(stderr,"wtf street %s\n",searchline); flag=0;}
      }
    else {
      flag=0;
      }
    if (flag) {
      sprintf(searchline,"%s|%s|%s|%s|%s|%s|%s|%010d|",a,b,c,d,e,f,area_code,pos);
      search(phone_prefix_by_street,searchline,line);
      field(line,prefix,8); 
      }
    }
  
  
  if (flag) { /* we have a ac and prefix for the main line that is good to go */
    int tries=0;
    int ok=0;
    do {
      ok=1;
      int lastnum;
      lastnum = (random()>>2) % 10000;
      sprintf(new_rest_phone,"%04d",lastnum);
      
      if ((lastnum == 5555) || (lastnum == 79) || (lastnum == 9970)) ok=0;
      else if (number_used(all_numbers,area_code,prefix,new_rest_phone)) ok=0;
      else if (strcmp(new_rest_phone,rest_phone)==0) ok=0;
      else {
        char full_phonetx[20000];
	long long full_phonex;
	sprintf(full_phonetx,"%s%s%s",area_code,prefix,new_rest_phone);
	full_phonex = atol(full_phonetx);
        if (phone_match_with_name(full_phonex,fname,lname)) ok=0;
	}
      if (!ok) tries++;
      } while ((!ok) && (tries<=100));
    if (!ok) flag=0;
    }
  if (flag) { /* if we finally got a phone number */
    strcpy(ac1,area_code);
    strcpy(prefix1,prefix);
    strcpy(rest1,new_rest_phone);
    set_number_used(all_numbers,area_code,prefix,new_rest_phone,1);
    }
  else {
    ac1[0] = '\0';
    prefix1[0] = '\0';
    rest1[0] = '\0';
    }

  /* Cell phone */
  flag=0;  
  if ((ac1[0]==0)||(             ((random()>>2) % 100 )  <70)) { /* 82% have cell phones, but everyone without
       a land line gets a cell phone  so we fudged it down to 70 %*/
    flag=1;  
    
    int tries=0;
    do {
      sprintf(searchline,"%s|",area_code);
      if (search(prefixes_for_ac,searchline,line)) {
        size=fieldi(line,1);
        }
      else size=0;
      /* sometimes the ac is bogus, so we look up an ac for prefix */
      if (!size) {
        /* find a different area code to use for the given zip code */
        sprintf(searchline,"%s|",zip);
        search(acs_per_zip,searchline,line);
	size=fieldi(line,1);
	
        int pos;
        pos =(random()>>2) % size +1;
        sprintf(searchline,"%s|%010d|",zip,pos);
	search(acs_by_zip,searchline,line);
	field(line,area_code,2);
	size=0;	
	tries++;
        }
      } while ((!size) && (tries <=1000));
   
    if (size) {
      int tries=0;
      int ok=0;
      do {
        int pos;
        pos =(random()>>2) % size +1;
        sprintf(searchline,"%s|%010d|",area_code,pos);
        search(prefixes_of_ac,searchline,line);
        field(line,prefix,2);
    
        int lastnum;
        ok=1;
        lastnum = (random()>>2) % 10000;
        sprintf(new_rest_phone,"%04d",lastnum);
      
        if ((lastnum == 5555) || (lastnum == 79) || (lastnum == 9970)) ok=0;
        else if (number_used(all_numbers,area_code,prefix,new_rest_phone)) ok=0;
        else {
          char full_phonetx[20000];
  	  long long full_phonex;
	  sprintf(full_phonetx,"%s%s%s",area_code,prefix,new_rest_phone);
	  full_phonex = atol(full_phonetx);
          if (phone_match_with_name(full_phonex,fname,lname)) ok=0;
	  }
        if (!ok) tries++;
        } while ((!ok) && (tries<=1000));
      if (!ok) flag=0;
      }
    else { flag = 0; }
    
    if (flag) {
      strcpy(ac2,area_code);
      strcpy(prefix2,prefix);
      strcpy(rest2,new_rest_phone);
      set_number_used(all_numbers,area_code,prefix,new_rest_phone,1);
      }
    else {
      /* pick a random area code and stuff */
      int ok=0;
      int tries=0;
      randomac=1;
      do {
        do {
          int aci;
          aci = ((random()>>2) % 1000);
          sprintf(area_code,"%d",aci);
          sprintf(searchline,"%s|",area_code);
          if (search(prefixes_for_ac,searchline,line)) {
            size=fieldi(line,1);
            }
          else size=0;      
          } while (!size);

        int pos;
        pos =(random()>>2) % size +1;
        sprintf(searchline,"%s|%010d|",area_code,pos);
        search(prefixes_of_ac,searchline,line);
        field(line,prefix,2);
    
        int lastnum;
        ok=1;
        lastnum = (random()>>2) % 10000;
        sprintf(new_rest_phone,"%04d",lastnum);
      
        if ((lastnum == 5555) || (lastnum == 79) || (lastnum == 9970)) ok=0;
        else if (number_used(all_numbers,area_code,prefix,new_rest_phone)) ok=0;
        else {
          char full_phonetx[20000];
  	  long long full_phonex;
	  sprintf(full_phonetx,"%s%s%s",area_code,prefix,new_rest_phone);
	  full_phonex = atol(full_phonetx);
          if (phone_match_with_name(full_phonex,fname,lname)) ok=0;
	  }
        if (!ok) tries++;
        } while ((!ok) && (tries<=1000));
    
      if (!ok) {
        fprintf(stderr,"FAILED could not even find a random phone number random area code!\n");
        exit(-1);
        }
      strcpy(ac2,area_code);
      strcpy(prefix2,prefix);
      strcpy(rest2,new_rest_phone);
      set_number_used(all_numbers,area_code,prefix,new_rest_phone,1);
      } /* if we could not find a number the normal way and had to choose wild randoms */
    } /* if we are lucky enough to own a cell phone */
  else {
    ac2[0]='\0';
    prefix2[0]='\0';
    rest2[0]='\0';
    }
  fieldspan(buf,phase1,0,38,0);
  printf("%s",phase1);
  int i=0;
  char *t=phase1;
  while (*t) {
     if (*t == '|') i++;
     t++;
     }
  while (i<=38) {printf("|"); i++;}
  if ((ac1[0] =='\0')&&(ac2[0]=='\0'))  {
    fprintf(stderr,"%s\n",buf);
    fprintf(stderr,"%s|%s|%s|%s|%s|%s|||||\n",ac1,prefix1,rest1,ac2,prefix2,rest2);  
    fprintf(stderr,"Bad phone!\n");
    exit(-1);
    }
  printf("%s|%s|%s|%s|%s|%s|||||\n",ac1,prefix1,rest1,ac2,prefix2,rest2);  
  if (randomac) { /* print this out so we can test how manmy we are getting random ac errors for */
    fprintf(stderr,"%s|%s|%s|%s|%s|%s|||||\n",ac1,prefix1,rest1,ac2,prefix2,rest2);
    }
  }  
return(0);
}




