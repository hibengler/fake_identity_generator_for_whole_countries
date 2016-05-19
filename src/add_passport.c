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
Add passport - for 25% of the records, add a passport field


The passport field has the following:

P<USAMARCUS SR<<JOHN<MICHAEL<<<<<.....




Adding the foillowint:
passport id
passport number
passport expdate
passport extra code
passport code1
passport code2
reserverd
reserved
gender (truncated)


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "soundex.h"
#include "util.h"
#include <time.h>





unsigned char passport_numbers[125000000];

int init_numbers(unsigned char *numbers) {
memset(numbers,0,125000000);
}

static unsigned char f[8] = {1,2,4,8,16,32,64,128};
static unsigned char nf[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


int number_used(unsigned char *numbers,int code) {
unsigned char t;

/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
pnum = code;

/* find the flag */
t = numbers[pnum>>3] & (f[pnum&7]);
t = !t;
t = !t;
return t;
}






void set_number_used(unsigned char *numbers,int code,
  int value)
{
unsigned char t;


/* convert to a long 64 bit number*/
long long pnum;
int ac;
int pf;
int r;
pnum  = code;

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



char *nameit(char *out,char *in) {
char *r=out;
while (*out) out++;
char ch;
while (ch= *(in++)) {
  if ((ch>='a')&&(ch<='z'))
    ch = ch- 'a' + 'A';
  else if ((ch >='A')&&(ch<='Z'))
    ch=ch;
  else if ((ch >='0')&&(ch<='9'))
    ch=ch;
  else
    ch='<';
  *(out++) = ch;
  }
*out = '\0';
return r;
}


int check_digit(char *x) {
int check=0;
int m=7;
char ch;
while (ch= *(x++)) {
  int cd;
  if ((ch>='a')&&(ch<='z'))
    cd = ch- 'a' + 'A' + 10;
  else if ((ch >='A')&&(ch<='Z'))
    cd = ch - 'A' + 10;
  else if ((ch >='0')&&(ch<='9'))
    cd= ch - '0';
  else
    cd = 0;
  check += cd*m;
  if (m==7) m=3;
  else if (m==3) m=1;
  else m=7;
  }
check = check % 10;
return check;
}





int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
    }
init_numbers(passport_numbers);
set_number_used(passport_numbers,0,1);
set_number_used(passport_numbers,999999999,1);
return 0;
}



int main(int argc, char *argv[]) {
init(argc,argv);
char z[20000];

  
    
time_t now;
struct tm *d;
char li[13];
time(&now);
d = localtime(&now);
strftime(li,20,"%d-%b-%Y",d);
int date_code = date_to_code(li);    
        
while (gets(z)) {
  char gender[20000]; /* compute the truncated gender no matter what */
  field(z,gender,25);
  
  if (((random() >>2) % 100) <=22) { /* 22 percent amercians have a paasport */
    int passportnum;
    do {
      passportnum = random() % 1000000000;
      } while (number_used(passport_numbers,passportnum));
    set_number_used(passport_numbers,passportnum,1);
  
    char passport_number[20];
    sprintf(passport_number,"%09d",passportnum);
  
    char name[10000];
    int i;
    char fname[20000];
  
    char lname[20000];
    char mname[20000];
    char suffix[20000];
  
    field(z,lname,33);
    field(z,fname,32);
    field(z,mname,35); /* shoot - we need to make up middle names */

  
      
    upper(fname,fname);
    upper(lname,lname);
    upper(mname,mname);
    upper(suffix,suffix);
    name[0]='\0';
    nameit(name,lname);
    if (suffix[0]) {
      strcat(name,"<");
      nameit(name,suffix);
      }
    strcat(name,"<<");
    nameit(name,fname);
    if (mname[0]) {
      strcat(name,"<");
      nameit(name,mname);
      }
  
    /* set to 39 characters */
    int l=strlen(name);
    if (l>39) {
      name[39]='\0';
      }
    else {
      while (l<39) {
        name[l++]='<';
        }
      name[l]='\0';
      }
  
    char codel1[20000];
    sprintf(codel1,"P<USA%s",name);
  
  
  
  
    char codel2[20000];
   
    char bd[20000];
    field(z,bd,50);
    int month,day,year;
  
    date_to_mdy(bd,&month,&day,&year);
    sprintf(bd,"%02d%02d%02d",(year%100),month,day);
  
  
  
  
    int curcode = date_code + 60 + (random()>>2) % (3650 - 60);
    char temp[20000];
    char edate[20000];
    char expdate[20000];
    code_to_date(curcode,edate);
  
    date_to_mdy(edate,&month,&day,&year);
  
  
    sprintf(expdate,"%02d%02d%02d",(year%100),month,day);
  
  
    char extra[20000];
    char extra1[20000];
    sprintf(extra,"%d",(int)((random()>>2) % 10)); /* note - mine is a < */
    strcpy(extra1,extra);
    strcat(extra,"<<<<<<<<<<<<<");
  
  
  
    sprintf(temp,"%s%d%s%d%s%d%s%d",
                passport_number,check_digit(passport_number),
		 bd,check_digit(bd),expdate,check_digit(expdate),
		           extra,check_digit(extra));

    sprintf(codel2,"%s%dUSA%s%d%c%s%d%s%d%d",
          passport_number,check_digit(passport_number),
	  bd,check_digit(bd),gender[0],expdate,check_digit(expdate),
	  extra,check_digit(extra),check_digit(temp));
  
    printf("%s|%s|%s|%s|%s|%s|||%c\n"
     ,z,passport_number,edate,extra1,codel1,codel2,gender[0]);
     
    }
  else {
    printf("%s||||||||%c\n",z,gender[0]);
    }
  }
exit(0);
}
