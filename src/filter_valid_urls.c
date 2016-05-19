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
/* filter_valid_urls - 
take the urls and determine if they are valid to be referred to
*/

#define DEPTH_SEARCH

#define RANGE_SIZE 30

#include <time.h>
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


struct searcher *main_file;



char *convert_slash_to_ctrla(char *p1x,char *line)
{
      char *x,*y;
      x=line,y=p1x;
      while (*x) {
        if (*x == '/') {
          *y++ = 001; x++;
  	  }
        else {
          *y++ = *x++;
  	  }
        }
      *y = '\0';
return p1x;
}



void get_pos(char *buf,long long *pos) {
char *z = buf;
while (*buf) {
  if (*buf=='|') z=buf+1;
  buf++;
  }
*pos = atoll(z);
}


int dirfield(char *x, char *y,int fieldnum)
{
int flag=0;
char *z=y;
while (fieldnum && *x) {
  if ((*x == '/')) fieldnum--;
  x++;
  }
while (*x && (*x != '/')) {
  char ch=*x;
  if (ch!='/') {
    *z++ = ch;
    }
  x++;
  }
*z='\0';
if (*x == '/') flag=1;
return flag;
}





void dir_remainder_to_pipe(char *x, char *file,int fieldnum)
{
int flag=0;
char *z =file;
while (fieldnum && *x) {
  if ((*x == '/')) {
    fieldnum--;
    }
  x++;
  }
while (*x) {
  char ch=*x;
  if (ch=='/') {
    *z++ = '|';
    }
  else if (ch==001) { /* ctrl a special */
    *z++ = '/';
    }
  else {
    *z++ = ch;
    }
  x++;
  }
*z='\0';
}

void add_from_range_url( char *obuf,char *url,int from_range, int to_range) {
      char gbuf[2000];
      char *t;
      char *o=gbuf;
      t=url;
      if (*t) *o++= *t++;
      while ((*t)&&(*t) != '/') {
        *o++ = *t++;
         }
      if (*t=='/') t++;
      if (from_range) {
        while ((*t)&&(*t) != '/') {
           t++;
	   }
        if (*t=='/') t++;
	}
      *o = '\0';
      if (to_range) {
        sprintf(obuf,"%s/_%d/%s",gbuf,to_range,t);
	}
      else {
        sprintf(obuf,"%s/%s",gbuf,t);
	}

}



int check_pic (int ip)
{
  char fname[100];
  sprintf(fname,"i/%u.png",ip);
  struct stat sts;
  if (((stat(fname,&sts))== -1)/*||(rand() % 100 ==0)*/) {
    char biggerbuf[1000];
    sprintf(biggerbuf,"touch i/%u.png",ip);
    system(biggerbuf);
    sprintf(biggerbuf,"modify_pic.sh %u",ip);
    system(biggerbuf);
    }

}

void remove_range_url_trail( char *obuf,char *url,int from_range,char *trail) {
      char gbuf[2000];
      char *t;
      char *o=gbuf;
      t=url;
      if (*t) *o++= *t++;
      while ((*t)&&(*t) != '/') {
        *o++ = *t++;
         }
      if (*t=='/') t++;
      if (from_range) {
        while ((*t)&&(*t) != '/') {
           t++;
	   }
        if (*t=='/') t++;
	}
      *o = '\0';
      sprintf(obuf,"%s/%s",gbuf,t);
int l=strlen(obuf);
while ((l)&&obuf[l-1] != '/') {
  l--;
  }
if (obuf[l]) {
  strcpy(trail,obuf+l);
  obuf[l]='\0';
  }
else {
  trail[0]='\0';
  }
}



char *format_ccard(char *buf,char *in) {
int x=0;
while (*in) {
  if ((x)&&(x % 4)==0) {
    *buf++ = '-';
    }
  *buf++ = *in++;
  x=x+1;
  }
*buf='\0';
return buf;
}

char *format_ccard_tease(char *buf,char *in) {
int l=strlen(in);
int tease_count=l-5;
int x=0;
while (*in) {
  if ((x)&&(x % 4)==0) {
    *buf++ = '-';
    }
  *buf = *in++;
  if (x&&(tease_count>0)) { /* hide the second digit but show the last four to tease them */
    *buf='X';
    tease_count--;
    }
  buf++;
  x=x+1;
  }
*buf='\0';
return buf;
}



char *format_phone(char *buf,char *area,char *prefix, char *suffix) {
if ((area) && (*area)) {
  sprintf(buf,"(%s)%s-%s",area,prefix,suffix);
  }
else
  buf[0]='\0';
return buf;
}



char *html_header(char *buf,char *cookie_names[],char *cookie_values[]) {
sprintf(buf,"");
return buf;
}



char *html_start_section_body( char *buf,char *url,int ip,char *title) {
if (title == NULL) title="Index";
sprintf(buf,"");
}

char *html_end_section_body( char *buf) {
sprintf(buf,"");
}

char *html_footer(char *buf) {
*buf='\0';
return buf;
}



char * error_404(char *b,int *pbuflength) {
sprintf(b,"404\n");
*pbuflength = strlen(b);
return b;
}


char * warning_304(char *b,int *pbuflength) { /* not modified - a hack for evercookie detection */
sprintf(b,"304");
*pbuflength = strlen(b);
return b;
}





char *follow_flag(int id,char *method) {
/* 
ssn   20
phn1  30
phn2  10
flm   15
lfm   10
cs    15
*/
unsigned int idx;
char *rel;
idx = id;
idx = idx % 100;
rel=" rel=\"nofollow\"";  /* usual case */
if (idx <20) {
  if (strcmp(method,"ssn")==0) rel=""; /* ssn */
  }
else {
  idx -= 20;
  if (idx < 30) {
    if ((strcmp(method,"phn1")==0)||(strcmp(method,"phn")==0)) rel=""; /* phone */
    }
  else {
    idx -= 30;
    if (idx < 10) {   /* phone 2 is cell phone,  less know to be real. */
      if ((strcmp(method,"phn2")==0)||(strcmp(method,"phn")==0)) rel=""; /* phone 2 */
      }
    else {
      idx -= 10;
      if (idx < 15) {   
        if (strcmp(method,"flm")==0) rel=""; /* flm */
	}
      else {
        idx -= 15;
	if (idx < 10) {
	  if (strcmp(method,"lfm")==0) rel=""; /* lfm */
	  }
	else {
	  idx -= 10;
	  /* if idx < 15 but we know it is */
	  if (strcmp(method,"cs")==0) rel=""; /* city state */
	  }
	}
      }
    }
  }
return rel;
}




char *follow_flag_consider_phone (int id,char *mode,
  char *ac1,char *prefix1, char *suffix1,
  char *ac2,char *prefix2, char *suffix2,
  char *url_part)
{
if ((strcmp(mode,"phn")==0)&&(suffix1[0])&&(suffix2[0])) {
  char b1[2000];
  char b2[2000];
  char test[2000];
  /* url part is something like  56/(440)315-1156/0 , hacky but true
     We clip off the start and end and make it (440)315-1156
     then we can compare apples and oranges and make sure we link to phn1 or phn2 accordingly
     That way every person will only be listed once */
  strcpy(test,url_part+3); /* skip dd/ */
  test[13]='\0'; /* clip off the /0 */
  sprintf(b1,"(%s)%s-%s",ac1,prefix1,suffix1);
  sprintf(b2,"(%s)%s-%s",ac2,prefix2,suffix2);
  if (strcmp(test,b1)==0) {
    mode="phn1";
    }
  else if (strcmp(test,b2)==0) {
    mode="phn2";
    }
  else {
    fprintf(stderr,"ERROR %s %s %s\n",test,b1,b2);
    }
  }
return follow_flag(id,mode);
}





void find_line_xcount(char *r,int fieldnum,char *line,char *xcount,struct searcher *base_searcher,
  struct sup_searcher *sup_searcher) {
char *x;
char *lx = line;
char *cx = xcount;
char *prev_left_off=NULL;
int f=0;
/* skip the first matched fields */
for (x=r;(*x)&&(f<fieldnum);x++)  { if (*x=='|') f++; }

/* print out the text and the count */
for (;*x;x++)  {
  if (*x=='|') {
    *lx++='/';
    prev_left_off=lx;
    *cx = '\0';
    cx = xcount;
    }
  else if (*x=='/') {
    *(cx++) = 001;
    *lx++ =001; /* ctrla */
    }
  else {
    *(cx++) = *x;
    *(lx++) = *x;
    }
  }
*cx = '\0';
*lx = '\0';
if (prev_left_off) { /* do we add or not add the last /?  This is problematic. hmmmm
                            I guess that if we are displaying a non base subset, we leave it off
			    but if we are a base subset, we leave it on
			    There was a bug here - where we were comparing
			   prev_left_off to r - we should have been comparing to line
                            */
  if ((sup_searcher)&&(sup_searcher->base != base_searcher)&&(prev_left_off != line)) {
    prev_left_off--; /* remove / */
    }
  *prev_left_off='\0';
  /*if completely empty, forget it */
  if (line[0]=='\0') {
    strcat(line,"/");
    }
  }
}




int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
  }


/*??? add DL? */
main_file = new_searcher("../out/n001.txt",11,0,0);
return 0;
}









int main() {
 (init(0,NULL));
char buf[20000];
int level;
while (gets(buf)) {
  level=0;
  char buf2[20000];
  char buf3[20000];
  field(buf,buf2,0);
  field(buf,buf3,1);
  long long curpos;
  curpos = atoll(buf2);
  if (curpos==99999999999999) {
    printf("%s\n",buf3);
    }
  else {
    char *url;
    char f1[2000];
    int offset=2;
    char *origurl;
    char buff[513];
    url=buf3;
    decode_url(buff,url,512);
    origurl=url;
    url=buff;
    int searching=dirfield(url,f1,1);
    int flag=0;
    {
      char *mode = f1;

      char ch;
      char *x = main_file->map + curpos;
      char *xb=x;
      while ((*x)&&(*x != '\n')) x++;



      /* split into an array of fields */
      char abuf[20000];
      strncpy(abuf,xb,x-xb);
      abuf[x-xb]='\0';



      char *f[1000];
      int cols=0;
      char *q=abuf;
      char *r1=q;
      while (*r1) {
        while (*r1 &&(*r1 != '|')) r1++;
        f[cols++] =q;
        if (*r1) {
          *r1 = '\0';
          r1++;
          }
        q=r1;
        }

      
      char p1[10000];
      char p2[10000];
      char rest2[2000];
      int id=atoi(f[10]);
      if (strcmp(mode,"phn")==0) {
        char *x;
	int count=5;
	x=url;
	while ((*x)&&count) {
	  if (*x =='/') count--;
	  x++;
	  }
	x -=3;
	strcpy(rest2,x);
	}
      else {
        strcpy(rest2,"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
	}
      char *follow=follow_flag_consider_phone(id,mode,f[39],f[40],f[41],f[25],f[26],f[27],rest2);
      if (follow[0]=='\0') {
        puts(buf);
	}
      }
    }
  }
return 0;
}
