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

Derived from make_phone_numbers

This makes UK phone numbers

This makes phone numbers
Reads from l007 and tries to add

A residential phone - if there was a phone,  or 50% of the time.

A cell phone - 92% of the time


1. read the numbers_per_street.txt to ge the number of people who have a residential phone on that street
2. Read the acs.txt  - to get possible phone area codes

for each person
  if residential is needed:
  if phone is not known, pick the prefix based on streed - if you can - if not, give up.
  loop
    Pick a phone number -
    until you find one that is not the same as the real phone numberm and
       you find a number that is unique.  ( try for a real phone number 3 times )
  flag the phone as unique.
  
  if cell is needed:
  pick any prefix. randomized cell phone prefix.
  loop
   pick
     until you find one that is not the same and unique - real try 2 times
     end looop

  print out the new persons phone number.
    

note - all 5555 0079 and 9970 numbers are out of the loop

*/

#include <ctype.h>
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


int flipac[] = {101,1543,0,0};




unsigned char actual_numbers[1250000000];
unsigned char all_numbers[1250000000];



int number_used(unsigned char *numbers,long long pnum) {
unsigned char t;



/* find the flag */
t = numbers[pnum>>3] & (f[pnum&7]);
t = !t;
t = !t;
return (t);
}

int flippant(int a) {
int i=0;
while (flipac[i]) {
  if (flipac[i]==a) 
    return flipac[i+1];
  i += 2;
  }
return a;
}


void set_number_used(unsigned char *numbers,long long pnum,
  int value)
{
unsigned char t;


/* convert to a long 64 bit number*/

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



int number_to_uk_phone(long long phone,char *ac,char *rest) {
char buf[2000];
sprintf(buf,"%qd",phone);
buf[10]='\0'; /* clip 11 digit numbers */
int size;
if (
   (strncmp(buf,"13873",5)==0)||
   (strncmp(buf,"15242",5)==0)||
   (strncmp(buf,"15394",5)==0)||
   (strncmp(buf,"15395",5)==0)||
   (strncmp(buf,"15396",5)==0)||
   (strncmp(buf,"16973",5)==0)||
   (strncmp(buf,"16974",5)==0)||
   (strncmp(buf,"16977",5)==0)||
   (strncmp(buf,"17683",5)==0)||
   (strncmp(buf,"17684",5)==0)||
   (strncmp(buf,"17687",5)==0)||
   (strncmp(buf,"19467",5)==0)) {
  size=5;
  }
else if (
         ((buf[0]=='1')&&
          (buf[1]=='1')&&
          isdigit(buf[2])) ||
         ((buf[0]=='1')&&
          (buf[2]=='1')&&
          isdigit(buf[1])) ) {
  size = 3;
  }
else if (
  (buf[0]=='1')&&
  isdigit(buf[1])&&
  isdigit(buf[2])&&
  isdigit(buf[3])) {
  size=4;
  }
else if ( 
  (buf[0]=='2') &&
  isdigit(buf[1]) ) {
  size=2;
  }
else if (strncmp(buf,"7624",4)==0) {
  /* isle of mann */
  size=4;
  }
else if ((strncmp(buf,"70",2)==0)||
         (strncmp(buf,"76",2)==0)) {
  /* pagers */
  size=2;
  }
else if ((buf[0]=='7') &&
         isdigit(buf[1]) &&
         isdigit(buf[2]) &&
         isdigit(buf[3]) ) { 
  /* mobile*/
  size=4;
  }
else if ((buf[0] == '3') &&
         isdigit(buf[1])&&
         isdigit(buf[2])) {
  /* non geo */
  size=3;
  }
else if ((strncmp(buf,"500",3)==0) ||
         (strncmp(buf,"800",3)==0) ||
         (strncmp(buf,"808",3)==0)) {
  /* freephone */
  size=3;
  }
else if ((buf[0]=='5')&&
         isdigit(buf[1])) {
  size=2;
  }
else if ((buf[0]=='8') &&
  isdigit(buf[1])&&
  isdigit(buf[2])) {
    size = 3;
  }
else if ((buf[0]=='9') &&
  isdigit(buf[1])&&
  isdigit(buf[2])) {
    size = 3;
  }
else {
  size=0;
  }
strncpy(ac,buf,size);
ac[size]='\0';
strcpy(rest,buf+size);
return size;
}


int *area_codes[1000000]; /* actually only need 1 tenth that amount */
int area_code_lengths[1000000];
int area_code_bad[1000000];



void mark(int ac,int rest) {
if ((ac>=7400)&&(ac<=7999)&&(ac != 7624)) {
  mark(9999,ac);
  ac=9998; /* cellular */
  }
int len = area_code_lengths[ac];
if (!len) {
  area_codes[ac] = calloc(1,sizeof(int)*1024);
  }
else if (len==1024) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*10240);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*1024);
  free(old);
  }
else if (len==10240) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*102400);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*10240);
  free(old);
  }
else if (len==102400) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*1024000);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*102400);
  free(old);
  }
else if (len==1024000) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*10240000);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*1024000);
  free(old);
  }
else if (len==10240000) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*102400000);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*10240000);
  free(old);
  }
else if (len==102400000) {
  int *old = area_codes[ac];
  area_codes[ac] = malloc(sizeof(int)*1024000000);
  memcpy((void *)area_codes[ac],(void *)old,sizeof(int)*102400000);
  free(old);
  }
else if (len==1024000000) {
  fprintf(stderr,"too big on area code %d\n",ac);
  exit(-1);
  }
area_codes[ac][len] = rest;
area_code_lengths[ac]=len+1;  

/* make the numbers have clar points */
{
  long long l;
  char buf[1000];
  sprintf(buf,"%d%d",ac,rest);
  buf[10]='\0';
  l = atol(buf);
  set_number_used(all_numbers,l,0);
  }
}



  
int init_numbers(unsigned char *numbers) {
memset(actual_numbers,0,1250000000);
memset(numbers,255,1250000000);
memset(area_code_lengths,0,1000000*sizeof(int));
memset(area_code_bad,0,1000000*sizeof(int));
{ 
  FILE *xf;
  xf=fopen("phone_numbers.txt","r"); 
  if (!xf) {
    fprintf(stderr,"cannot open phone numbers.txt\n");
    exit(-1);
    }
  char buf[20000];
  while (fgets(buf,19999,xf)) {
    char ac[20000];
    char rest[20000];
    char tog[20000];
    field(buf,ac,0);
    field(buf,rest,2);
    sprintf(tog,"%s%s",ac,rest);
    long long num;
    num=atoll(tog);
    if ((num>0)&&(num<10000000000)) {
      set_number_used(actual_numbers,num,1);
      set_number_used(numbers,num,0);
      }
    }
  fclose(xf);
  }


{
  FILE *xf; 
  xf = fopen("fulllist.txt","r");
  if (!xf) {
    fprintf(stderr,"cannot open fulllist.txt\n");
    exit(-1);
    }
  char buf[20000];   
  while (fgets(buf,19999,xf)) {
    char fromc[10000];
    char toc[10000];
    long long from;
    long long to;
    field(buf,fromc,0);
    field(buf,toc,1);
    from = atol(fromc);
    to = atol(toc);
    long long i;
    for (i=from;i<to;i++) {
      set_number_used(numbers,i,0);
      }
    }
  fclose(xf);
  
  }
  
  
  
{
  long long i,range;
  range=0;
  for (i=100000000;i<10000000000;i++) {
    if (number_used(actual_numbers,i)) {
      long long j,k;
      for (j=i+1;j<10000000000;j++) {
        if (!number_used(actual_numbers,j)) {
	  for (k=j+1;k<j+1000;k++) {
	    if (number_used(actual_numbers,k)) {
	      j=k;
	      break;
	      }
	    }
	  if (j!=k) {
	    if (i<1000000000) {
	      if (i==j-1) j=i+60; else  while (j%1000) j++;
	      }
	    else if (i<7000000000) {
	      if (i==j-1) j=i+60; else  while (j%1000) j++;
	      }
	    else {
	      if (i==j-1) j=i+80000;
	      while (j%1000) j++;
	      }
	    {
	      for (k=i;k<j;k++) {
	        set_number_used(actual_numbers,k,0);
	        }
	      char ac1[100];
	      char rest1[100];
	      char ac2[100];
	      char rest2[100];
	      int ac1x;
	      int ac2x;
	      int rest1x;
	      int rest2x;
	      number_to_uk_phone(i,ac1,rest1);
	      number_to_uk_phone(j-1,ac2,rest2);
	      ac1x = atoi(ac1);
	      ac2x = atoi(ac2);
	      rest1x = atoi(rest1);
	      rest2x = atoi(rest2);
	      
	      /* mark it on the list for the ac */
	      while (ac1x<ac2x) {
	        int len = strlen(rest1);
		int max;
		max=-1;
		if (len==1) max=9;
		if (len==2) max=99;
		if (len==3) max=999;
		if (len==4) max=9999;
		if (len==5) max=99999;
		if (len==6) max=999999;
		if (len==7) max=9999999;
		if (len==8) max=99999999;
		for (rest1x=rest1x;rest1x<max;rest1x++) {
		  mark(ac1x,rest1x);
		  }
		rest1x=1;
		ac1x++;
		}
	      while (rest1x<=rest2x) {
	        mark(ac1x,rest1x);
		rest1x++;
		}
	      
	      range += j-i;
	      }
	    i=j;
	    break;
	    }
	  } /* if blank */
	} /* while spanning */
      } /* if found one on */
    } /* for each row */
  } /* block to find the useful numbers to search for */

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



int count=0;

while (gets(buf)) { /* the zipcode */
  int f;
  int size;
  int size2;
  int pos;
  char area_code[100];
  char rest_phone[100];
  char new_rest_phone[100];
  char full_phone[100];
  char ac1[100];
  char rest1[100];
  char ac2[100];
  char rest2[100];
  char fname[20000];
  char lname[20000];
  
  int randomac=0;    
  
  count++;
  if (count%100000==0) {
    fprintf(stderr,".");
    }
  
  if (strncmp(buf,"warning",7)==0) continue;
  if (strncmp(buf,"|||||||",7)==0) continue;
  
  field(buf,area_code,16);
  field(buf,rest_phone,18);
  field(buf,zip,15);
  {char rest[200000];
  field(buf,rest,1);
  }
  field(buf,fname,32); /* new first name */
  field(buf,lname,33); /* new last name */
  long long actual_number=-1;
  int flag=0;
  // flag will be if residental is needed
  if ((*area_code)&&(area_code[0]>= '1')&&(area_code[0]<'2')) { /* if we have a match */
    flag=1;
    char c[2000];
    sprintf(c,"%s%s",area_code,rest_phone);
    long long num;
    num = atol(c);
    number_to_uk_phone(num,area_code,rest_phone);
    
    
    }
  else if ((*area_code)|| ((random()>>2) % 100 <30)) { /* if we should try to add a residential number */
    flag=1;
again:    
    sprintf(searchline,"%s|",zip);
    search(acs_per_zip,searchline,line);
    size=fieldi(line,1);
    int pos;
    pos =((random()>>2) % size) +1;
    sprintf(searchline,"%s|%010d|",zip,pos);
    search(acs_by_zip,searchline,line);
    field(line,area_code,2);
    long long num;
    char c[2000];
    num =  atol(area_code);
    num = flippant(num);
    number_to_uk_phone(num,area_code,c);
    
    }
  if (flag) { /* we have a ac and prefix for the main line that is good to go */
    int acx;
    int tries=0;
    int ok=0;
    acx = atoi(area_code);
    int len;
    len = area_code_lengths[acx];
    if (len==-1) continue;
    do {
      ok=1;
      int lastnum;
      int id;
      
      long long full_phonex;
      if (!len) {
        if ((acx == 1395)||
	    (acx == 1495)||
	    (acx == 1676)||
	    (acx == 1900)||
	    (acx == 1903)||
	    (acx == 1909)||
	    (acx == 1926)||
	    (acx == 1929)||
	    (acx == 1931)||
	    (acx == 1934)||
	    (acx == 1935)||
	    (acx == 1937)||
	    (acx == 1938)||
	    (acx == 1939)||
	    (acx == 1943)||
	    (acx == 1945)||
	    (acx == 1946)||
	    (acx == 1948)||
	    (acx == 1949)||
	    (acx == 1955)||
	    (acx == 1963)||
	    (acx == 1968)||
	    (acx == 1969)||
	    (acx == 1970)||
	    (acx == 1974)||
	    (acx == 1978)||
	    (acx == 1981)||
	    (acx == 1982)||
	    (acx == 1983)||
	    (acx == 1984)||
	    (acx == 1986)||
	    (acx == 1994)||
	    (acx == 1995)
	      )
	    {}
	else {
          fprintf(stderr,"AC %d no %s pos %s\n",acx,line,searchline);
	  }
	int tries;
	tries=0;
	
	do {
	  ok=1;
	  char ax[20];
	  strcpy(ax,area_code);
	  char *ex = ax + strlen(ax);
	  int digits=10-strlen(ax);
	  
	  int i;
	  {
	    char *z;
	    z=ex;
	    for (i=0;i<digits;i++) {
	      *z++ = '0' + ((random()>>2)%10);
	      }
	    *z = '\0';
	    
	    full_phonex = atol(ax);
	    if (number_used(all_numbers,full_phonex)) ok=0;
            else if (strcmp(new_rest_phone,rest_phone)==0) ok=0;
	    else if (phone_match_with_name(full_phonex,fname,lname)) {
//	      fprintf(stderr,"N");
	      ok=0;
	      }
            if (!ok) tries++;
	    else {
	      strcpy(new_rest_phone,ex);
	      strcpy(full_phone,ax);
	      }
	    
	    }
	  
	  } while ((!ok) && (tries<=1000));
	  
        if (!ok) {
	  fprintf(stderr,"cannot find for ac %s\n",area_code);
	  area_code_bad[acx]++;
	  if (area_code_bad[acx] >=10000) {
  	    area_code_lengths[acx]=-1;
  	    goto forgetit;
	    }
	  goto again;
	  }

	}
      else {
        id = (random()>>2)%len;
      
        sprintf(new_rest_phone,"%04d",area_codes[acx][id]);
        sprintf(full_phone,"%d%d",acx,area_codes[acx][id]);
        full_phonex = atol(full_phone);
      
        // her we can check if the number is used, try to use real numbers first
        if ((tries<50)&& (!number_used(actual_numbers,full_phonex))) {
	  ok=0; 
	  }
        else if (number_used(all_numbers,full_phonex)) ok=0;
        else if (strcmp(new_rest_phone,rest_phone)==0) ok=0;
        else if (phone_match_with_name(full_phonex,fname,lname)) {
//	  fprintf(stderr,"N");
	  ok=0;
	  }
        if (!ok) tries++;
        if (ok) {
          area_codes[acx][id] = area_codes[acx][len-1]; 
  	  area_code_lengths[acx]--;
	  }
	}
	
      if (ok) {
        set_number_used(all_numbers,full_phonex,1);
	}
      } while ((!ok) && (tries<=100));
    if (!ok) flag=0;
    }
  if (flag) { /* if we finally got a phone number */
    strcpy(ac1,area_code);
    strcpy(rest1,new_rest_phone);
    }
  else {
    ac1[0] = '\0';
    rest1[0] = '\0';
    }

  /* Cell phone */
  flag=0;  
  if ((ac1[0]==0)||(             ((random()>>2) % 100 )  <90)) { /* 82% have cell phones, but everyone without
       a land line gets a cell phone  so we fudged it up to 90 %*/
    flag=1;  
    
    int lastnum;
    int len;
    len = area_code_lengths[9999];
    int id;
    int acx;
      
    if (!len) {
      fprintf(stderr,"error cellular AC 9999 (or 9998) no records\n");
	exit(-1);
	}
      
    id = (random()>>2)%len;

    acx =area_codes[9999][id];
    lastnum = area_codes[9998][id];
    sprintf(new_rest_phone,"%04d",lastnum);
      
    sprintf(ac2,"%d",acx);
    strcpy(rest2,new_rest_phone);
    
    area_codes[9999][id] = area_codes[9999][len-1];
    area_codes[9998][id] = area_codes[9998][len-1];
    area_code_lengths[9999]--;
    area_code_lengths[9998]--;
    } /* if we are lucky enough to own a cell phone */
  else {
    ac2[0]='\0';
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
    fprintf(stderr,"%s|%s|%s|%s|%s|%s|||||\n",ac1,"",rest1,ac2,"",rest2);  
    fprintf(stderr,"Bad phone!\n");
    goto again;
    exit(-1);
    }
  printf("%s|%s|%s|%s|%s|%s|||||\n",ac1,"",rest1,ac2,"",rest2);  
forgetit:
  ac1[0]='\0'; /* filler */  
  }  
return(0);
}




