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
from make_Dl.c 3/23/2013

Make dl
A very tough problem for a little number 
We need the state code and the dl as a full idnetification.



England, Scotland, and Wales - 16 characters long



    1-5: The first five characters of the surname (padded with 9s if less than 5 characters)
    6: The decade digit from the year of birth (e.g. for 1987 it would be 8)
    7-8: The month of birth (7th character incremented by 5 if driver is female i.e. 51-62 instead of 01-12)
    9-10: The date within the month of birth
    11: The year digit from the year of birth (e.g. for 1987 it would be 7)
    12-13: The first two initials of the first names, padded with a 9 if no middle name
    14: Arbitrary digit - usually 9, but decremented to differentiate drivers with the first 13 characters in common
    15-16: Two computer check digits.
    17-18: Appended, two digits representing the licence issue, which increases by 1 for each licence issued.

Northern ireland - 8 characters long 7 id and one check.

So, we need the data sorted by birthdate - but it already is becasuse the nuid step just prior sorted it that way.
Cool.  

UK is zip codes starting with BT

*/

#define CURRENT_YEAR 2013


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "soundex.h"
#include "uthash.h"
#include "util.h"


struct dl_struct {
char *value;
UT_hash_handle hh;
};



char z[20000];

char dl[20000];


  

struct dl_struct *license_used= NULL;



int license_in_use(char * state,char *code) {
struct dl_struct *c;
char thelicense[20000];
strcpy(thelicense,state);
strcat(thelicense,code);
HASH_FIND_STR(license_used,thelicense,c);
if (c) return(1);
return 0;
}


int use_license(char * state,char *code) {
struct dl_struct *c;
char thelicense[20000];
int l;
strcpy(thelicense,state);
strcat(thelicense,code);
l=strlen(thelicense);
c = (struct dl_struct *) malloc(sizeof(struct dl_struct) + (l+1) * sizeof(char));
if (!c) {
  fprintf(stderr,"error mallocing license %s\n",thelicense);
  exit(-1);
  }
c->value = (char *)(c+1);
strcpy(c->value,thelicense);
HASH_ADD_KEYPTR(hh,license_used,c->value,l,c);
if (c) return(1);
return 0;
}


int month_day_gender(
 int month,int day,
 char *gender,
 int female_add,
 int month_mult) {
int dateno;
dateno = (month-1) * month_mult + day;
if (gender[0]=='F') {
  dateno += female_add;
  }
return dateno;
}



char *generate_numbers(char *buf,int length) {
int i;
for (i=0;i<length;i++) {
  if (i || (length==1)) {
    *(buf++) = (random()>>2) % 10 + '0';
    }
  else {
    *(buf++) = (random()>>2) % 9 + '1';
    }
  }
*(buf++) = '\0';
}


/* note - this includes Z, but the original dl did not */
char *generate_letters(char *buf, int length) {
int i;
for (i=0;i<length;i++) {
  *(buf++) = (random()>>2) % 26 + 'A';
  }
*(buf++) = '\0';
}


char *generate_alphanum(char *buf,int length) {
int i;
for (i=0;i<length;i++) {
  int v;
  if (i || (length==1)) {
    v= (random()>>2) % 36;
    }
  else {
    v = (random()>>2) % 35 + 1;
    }
  if (v<10) {
    *(buf++) = v+'0';
    }
  else {
    *(buf++) = v-10+'A';
    }
  }
*(buf++) = '\0';
}















char ni_used[10000000];

int ni_counter=0100000;

void northern_ireland() {
int guess;
do {
  guess = ni_counter + (random()%20000 - 10000);
  if (guess>=10000000) {
    fprintf(stderr,"range too big! overflowed\n");
    exit(-1);
    }
  } while (ni_used[guess]);
ni_used[guess]=1;
ni_counter += 88; 

/* compute check digit */
int chk;
chk=1;
int eat;
eat = guess;
while (eat) {
  chk += (eat % 10);
  eat = eat / 10;
  }
int dlid;
dlid = guess*10 + (chk % 10);

sprintf(dl,"%8.8d",dlid);


}



void northern_ireland_init() {
int i;
for (i=0;i<10000000;i++) {
  ni_used[i]=0;
  }
}






void uk (char *z) {
char name1[10000];
char name2[10000];
char gender[10000];
field(z,name1,33);
upper(name2,name1);
int l;
l=strlen(name2);
while (l<5) {
  name2[l++]='9';
  }
name2[5]='\0';

/* make any non alpha into 9s */
{
  char *ch;
  ch  =name2;
  while (*ch) {
    if ((*ch < 'A')||(*ch >'Z')) {
      if ((*ch < '0')||(*ch >'9')) {
        *ch = '9'; /* handle the spaces and dashes */
        }
      }
    ch++;
    }
  }
char *bdsection = name2+5;
char bd[10000];
int month,day,year;
field(z,bd,50);
date_to_mdy(bd,&month,&day,&year);
field(z,gender,25);
gender[1]='\0';
if (gender[0]=='F') month = month + 50;
sprintf(bdsection,"%d%2.2d%2.2d%d",(year%100)/10,month,day,year%10);

/* first initials of first names */
char n1;
field(z,name1,32);
n1 = name1[0];
if (n1 == '\0') n1 = '9';
name2[11]=n1;

char n2;
field(z,name1,35);
n2 = name1[0];
if (n2 == '\0') n2 = '9';
name2[12]= n2;
name2[14]='\0';

name2[13]='9';
while (license_in_use("",name2)) {
  char c;
  c=name2[13];
  if (c=='0') {
    c='Z';
    }
  else if (c=='A') {
    fprintf(stderr,"FAILED license %s code %s too many\n",name2,z);
    exit(-1);
    }
  else {
    c--;
    }
  name2[13]=c;
  }

use_license("",name2);

generate_letters(name2+14,2);
  
  
int sequence;
  
sequence = (CURRENT_YEAR-(year+18));
if (sequence<0) sequence=0;
sequence = 1 + sequence/7 + ((random()>>2)%6)/4;
  
sprintf(name2+16," %2.2d",sequence);

strcpy(dl,name2);
}







int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
    }
  
northern_ireland_init();

return 0;
}



int main(int argc, char *argv[]) {
init(argc,argv);
char phase1[20000];

  
while (gets(z)) {
  char zipcode[20000];
  field(z,zipcode,15);
  if (strncmp(zipcode,"BT",2)==0) { /* if northern ireland */
    northern_ireland();
    }
  else {
    uk(z);
    }
  fieldspan(z,phase1,0,55,1);
  printf("%s|%s\n",phase1,dl);
  }
return(0);
}
