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
This code analyzes the web agent so we know if it s a crawler, user agent, etc.
It also appends new agents to a list - so that we can add to the list as we
go along.


Not fully implemented probabl;y from xlate or rtr or something
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
#include "rtr.h"



struct searcher *???;

struct super_searcher *id_ss;
struct super_searcher *city_state;
struct super_searcher *first_last_middle;
struct super_searcher *first_middle_last;
struct super_searcher *last_first_middle;
struct super_searcher *phone_area_code;
struct super_searcher *phone_prefix;
struct super_searcher *ssn;
struct super_searcher *state_city;
struct super_searcher *zip4_street;
struct super_searcher *zip_name;
struct super_searcher *zip_street;
struct super_searcher *everything;


/* 
base - main page
/lfm - last first middle - list the last names
/lfm/Engler - Engler main page
/lfm/Engler/_s1 - first set - list all 10
/lfm/Engler/Joe - all engler joes
/lfm/Engler/Joe//23123121
*/

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




void dir_remainder_to_pipe(char *x, char *y,int fieldnum)
{
int flag=0;
char *z =y;
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
  else {
    *z++ = ch;
    }
  x++;
  }
*z='\0';
}

void add_from_range_url( char *obuf,char *url,int from_range, int to_range) {      
      char gbuf[10000];
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




void remove_range_url_trail( char *obuf,char *url,int from_range) {      
      char gbuf[10000];
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
obuf[l]='\0';
      
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
if (*area) {
  sprintf(buf,"(%s)%s-%s",area,prefix,suffix);
  }
else 
  buf[0]='\0';
return buf;
}



char *html_header(char *buf,char *cookie_names[],char *cookie_values[]) {
sprintf(buf,"HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n\n"
);
return buf;
}

char *html_footer(char *buf) {
*buf='\0';
return buf;
}



char * error_404(char *b,int *pbuflength) {
sprintf(b,"HTTP/1.1 404 Not Found\n"
"Content-Type: text/html; charset=iso-8859-1\n\n"
"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n"
"<html><head>\n"
"<title>404 Not Found</title>\n"
"</head><body>\n"
"<h1>Not Found</h1>\n"
"<p>The requested URL was not found on this server.</p>\n"
"<hr>\n"
"</body></html>\n");
*pbuflength = strlen(b);
return b;
}


char * warning_304(char *b,int *pbuflength) { /* not modified - a hack for evercookie detection */
sprintf(b,"HTTP/1.1 304 Not Modified\n\n");
*pbuflength = strlen(b);
return b;
}


char * display_page(struct super_searcher *super_search,
    char *b, /* buffer to append stuff to */
    int searching, /* non zero if we are searching at a strange offset */
    char *url,
    int offset,int *buflength)
{
char f1[20000];
char f2[20000];
char f3[20000];
char search_field[20000];
char results[20000];
char xoffset[20000];
char *hack = NULL;
char *e=b;

unsigned long long nextline;
int found;
int from_range=0;
int weirdness=0; /* weirdness goes up if the url or something is a bit off */
if (searching) {
  dirfield(url,xoffset,offset+0);
  if (xoffset[0]=='_') {  /* range folder - ignore */
    from_range = atoi(xoffset+1);
    int original_from_range = from_range;
        
    /* clean up from_range for hackers */
    if (from_range<0) from_range = -(from_range);
    from_range = ((from_range+(RANGE_SIZE-1))/RANGE_SIZE)*RANGE_SIZE;
    if (!from_range) from_range +=RANGE_SIZE;
    if (from_range != original_from_range) {
      hack="Weird from range";
      }
    
    offset++;
    }
  }

dir_remainder_to_pipe(url,f1,offset+0); /* convert from abc/_RANGE_SIZE/sue/markus/y to sue|markus|y */

char base_url_clean[10000];
remove_range_url_trail(base_url_clean,url,from_range);

html_header(b,NULL,NULL);
e = b + strlen(b);

sprintf(search_field,"%s",f1);
int supindex;
int searchindex;
int fieldnum;
int letter_count;
struct searcher *base_searcher;
struct sup_searcher *sup_searcher;
found =super_search_first_range_over(super_search,search_field,results,&nextline,1,
  &supindex,&searchindex,&base_searcher,&sup_searcher,&fieldnum,&letter_count);
int l=strlen(search_field);


if (from_range) {
  int r = atoi(results);
  r = r + from_range;
  char uu[100];
  sprintf(uu,"%010d|",r);
  found =search_first_range_over(base_searcher,uu,results,&nextline,0);
  }   

  
  
int show_base_flag=0;
if (base_searcher == super_search->base) show_base_flag=1;

if (!show_base_flag) { /* we are above the base - show that */
  int count=0;
  int first_record=1;
  
  
  
  {
    /* skip one field in result */
    char *r=results;
    while ((*r)&&(*r!= '|')) r++;
    if (*r=='|') r++;

    found = !(strncmp(search_field,r,l)); /* filter it to make sure we match */
    }
  
  
  while (1) {
    long long curpos;
      
      
    /* skip one field in result */
    char *r=results;
    while ((*r)&&(*r!= '|')) r++;
    if (*r=='|') r++;
    
    

    found = !(strncmp(search_field,r,l)); /* filter it to make sure we match */
    if (!found) { /* cannot find a match  OK */
      if (first_record) { /* something is wrong, we should get at least one match */
        if (from_range) {  /* the from range should never be too high, unless they FABRICATED the URL */
	  hack="Dir From range too high";
	  }
	else {
	  hack="Dir Invalid Search"; /* Invalid search might be possible. But PROBABLY NOT!!!! */
	  }
        }
      break;
      }
      
    if (count>=RANGE_SIZE) break; /* went too far */
      
    if (first_record) {
      first_record=0;
      
      
	
      if (from_range) {/* have more to do - make a previous set section */
        char obuf[10000];
        char ubuf[10000];
        char gbuf[10000];
	
	sprintf(gbuf,"<html>\n <head>\n  <title>Index of %s range %d</title>\n </head>\n <body>\n"
	    "<h1>Index of %s range %d</h1></a>",url,from_range,url,from_range);
        strcat(e,gbuf);  
        e = e+ strlen(gbuf);	     
        add_from_range_url(obuf,url,from_range,from_range-RANGE_SIZE);
        sprintf(gbuf,"<a href=\"%s\">Previous set of records.</a><br><br>\n",
	    encode_url(ubuf,obuf,512));
        strcat(e,gbuf);  
        e = e+ strlen(gbuf);	     
        } /* if we have more to do */
      else {
        char gbuf[10000];
	sprintf(gbuf,"<html>\n <head>\n  <title>Index of %s</title>\n </head>\n <body>\n"
	    "<h1>Index of %s</h1></a>",url,url);
        strcat(e,gbuf);  
        e = e+ strlen(gbuf);	     
        }   
      
      } /* if this is the first time we got a record */	

     
    char gbuf[10000];
    char line[10000];
    char xcount[10000];
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
      else {
        *(cx++) = *x;
        *(lx++) = *x;
	}
      }
    *cx = '\0';
    *lx = '\0';
    if (prev_left_off) { /* do we add or not add the last /?  This is problematic. hmmmm 
                            I guess that if we are displaying a non base subset, we leave it off
			    but if we are a base subset, we leave it on*/
      if ((sup_searcher)&&(sup_searcher->base != base_searcher)&&(prev_left_off != r)) { 
        prev_left_off--; /* keep the / */
	}
      *prev_left_off='\0';
      }
    char p1[10000];
    char p2[10000];
    sprintf(gbuf,"<a href=\"%s%s\">%s (%s) records.</a><br>\n",
    encode_url(p1,base_url_clean,512),encode_url(p2,line,512),line,xcount);
    strcat(e,gbuf);
    e = e+ strlen(gbuf);
    found=search_next_range(base_searcher,search_field,results,&nextline);
    
    count++;
    if (!found) { /* quit early - we will trust this found */
      break;
      }
    } /* while displaying all the records */
  
  if (found) {/* have more to do */
    char obuf[10000];
    char gbuf[10000];
    char ubuf[10000];
    add_from_range_url(obuf,url,from_range,from_range+RANGE_SIZE);
    sprintf(gbuf,"<br><a href=\"%s\">Next set of records.</a><br>\n",
        encode_url(ubuf,obuf,512));
    strcat(e,gbuf);  
    e = e+   strlen(gbuf);	     
    } /* if we have more to do */
  
  *e='\0';
  
//  sprintf(e,"<address>Apache/2.2.16 (Unix) Server at soandsuch.com Port 80</Address></body></html>");
//  e = e + strlen(e);
  
  html_footer(e);    
  e = e + strlen(e);
  
  } /* index */
else { /* show the details */
  char *rest;
  /* OK, it would be great to drill right into the detail - but
         then we would not have the final url searchable by google - and we want google to see everything
	 so here we check to see if we are found - before we really check,
	 we should be found.
	 And then we see what is left.  If nothing is left, then we have the full URL layed out, 
	 we can print it out differently.
	 Good idea - turn off the passport information. show just the ccards on the table.
	    Have birthdate, birthd state, and maiden name on final detail!
	    fucking evil!
	 */
    /* skip one field in result- that would be the index count */
  char *r=results;
  while ((*r)&&(*r!= '|')) r++;
  if (*r=='|') r++;
  found = !(strncmp(search_field,r,l)); /* filter it to make sure we match */
  if (found) {
    rest = r+l;
    if (*rest=='|') rest++; /* skip the first vertical bar here */
    char *done_check;
    done_check=rest;
    /* see if we have a | in the file */
    if (index(rest,'|')) {
      /* here we are printing out a table of records that match the search criteria */
      html_header(b,NULL,NULL);
      e = b + strlen(b);
/*??? indent 4 vvv */
  int first_record=1;
  int count=0;
  while (1) {
    long long curpos;

    /* skip one field in result */
    char *r=results;
    while ((*r)&&(*r!= '|')) r++;
    if (*r=='|') r++;
      
    found = !(strncmp(search_field,r,l)); /* filter it to make sure we match */
      
    if (!found) { /* something is wrong here */
      if (first_record) { /* something is wrong, we should get at least one match */
        if (from_range) {  /* the from range should never be too high, unless they FABRICATED the URL */
	  hack="File From range too high";
	  }
	else {
	  hack="File Invalid Search"; /* Invalid search might be possible. But PROBABLY NOT!!!! */
	  }
        }
      break;
      }
      
    if (count>=RANGE_SIZE) break;
 
    if (first_record) {
      first_record=0;	
      if (from_range) {/* have more to do */
        char obuf[10000];
        char gbuf[10000];
	char ubuf[10000];
        add_from_range_url(obuf,url,from_range,from_range-RANGE_SIZE);
        sprintf(gbuf,"<a href=\"%s\">Previous set of records.</a><br><br>\n",
	   encode_url(ubuf,obuf,512));
        strcat(e,gbuf);  
        e = e+   strlen(e);	     
        } /* if we have a previous set */
	
      /* OK print out the table header */
      char gbuf[10000];
      sprintf(gbuf,"<table border=1><tr><th>Rec</th><th>Name</th>"
	"<th>Sex</th><th>Address</th><th>Phone</th>"
	"<th>SSN</th><th>Drivers License</th><th>Credit Cards</th>"
	"<th>Passport</th><th>Birth Date</th>"
	"</tr>\n");
      strcat(e,gbuf);
      e = e+   strlen(e);
		   
      } /* if this is the first time we got a record */	
    /* get the exacting value */
    char rest[10000];
    strcpy(rest,r+l);
    /* pull a line from the main file, thanks to the cursor position */
    get_pos(results,&curpos);
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
      
    char gbuf[20000]	;
    char phone1[1000];
    char phone2[1000];
    format_phone(phone1, f[25],f[26],f[27]);
    format_phone(phone2,f[39],f[40],f[41]);
    char cc1[1000];
    char cc2[1000];
    char cc3[1000];
    format_ccard_tease(cc1,f[51]);
    format_ccard_tease(cc2,f[54]);
    format_ccard_tease(cc3,f[57]);
    char buf1[10000];
    char buf2[10000];
    char buf3[10000];
    char buf4[10000];
    char buf5[10000];
    char buf6[10000];
    char buf7[10000];
    char buf8[10000];
    char buf9[10000];
    char buf10[10000];
    char buf11[10000];
    char buf12[10000];
    char buf13[10000];
    char buf14[10000];
    char buf15[10000];
    char buf16[10000];
    char buf17[10000];
    char buf18[10000];
    char buf19[10000];
    char buf20[10000];
    char buf21[10000];
    char buf22[10000];
    char buf23[10000];
    char buf24[10000];
    char buf25[10000];
    char buf26[10000];
    char buf27[10000];
    char buf28[10000];
    char buf29[10000];
    char buf30[10000];
    char buf31[10000];
    char rest2[10000];
    char rest2_url[10000];
    char rest2_html[10000];
    {
      char *x = rest;
      char *z = rest2;
      char *lastspot;
      lastspot=z;
      while (*x) {
        if ((*x) == '|') {
          *z = '/';
	  lastspot=z;
	  }
        else *z = *x;
        x++;
        z++;
        } /* while converting | to / */
      *lastspot = '\0'; /* clip of the very last field - that should be the position field */
      } /* block to make rest2 from dfhjdfs|dfsdfsdf|34672 to  dfhjdfs/dfsdfsdf */
    

    /* put together the phone information */
    if (phone1[0]) {
      if (phone2[0]) {
        sprintf(buf11,"%s<br>%s"
        ,encode_html(buf2,phone1,9999)
        ,encode_html(buf3,phone2,9999));
        }
      else {
        sprintf(buf11,"%s"
        ,encode_html(buf2,phone1,9999));
        }
      }
    else {
      if (phone2[0]) {
        sprintf(buf11,"%s"
        ,encode_html(buf2,phone2,9999));
        }
      else buf11[0]='\0';
      }

    /* consolidate the credit cards numbers */
    {
       
      if (cc1[0]) {
        if (cc2[0]) {
          if (cc3[0]) {
            sprintf(buf12,"<font size=1>%s<br>%s<br>%s</font>",
             cc1,cc2,cc3);
            }
          else {
             sprintf(buf12,"<font size=1>%s<br>%s</font>",
               cc1,cc2);
             } 
          }
        else {
          sprintf(buf12,"<font size=1>%s</font>",
               cc1);
          }
        }
      else {
        buf12[0]='\0';
        }
      } /* consolidate ccard block */             
      


    sprintf(gbuf,"<tr><td><a href=\"%s%s\">%s</a></td><td>%s, %s %s</td>"
	"<td>%s</td>"
         "<td>%s<br>%s, %s<br>%s</td>" /* address */
	"<td>%s</td>" /* phones */
	"<td>%s</td><td><center><i>%s</i></center>%s</td><td>%s</td>"
	"<td>%s</td>"
	"<td>%s</td></tr>\n",
         encode_url(buf31,base_url_clean,9999),
	 encode_url(rest2_url,rest2,9999),
	 encode_html(rest2_html,rest2,9999),
	 encode_html(buf2,f[11],9999) /*last*/,
	 encode_html(buf1,f[12],9999) /*first */,
	 encode_html(buf4,f[14],9999) /*middle */,
	 encode_html(buf5,f[34],9999) /*gender*/,
	 encode_html(buf6,f[15],9999) /* address*/,
	 encode_html(buf7,f[22],9999) /*city*/,
	 encode_html(buf8,f[23],9999) /* state*/,
	 encode_html(buf9,f[24],9999) /*zip*/,
	 buf11, /* telephone combo */
	 encode_html(buf13,f[49],9999) /*ssn*/,
	 encode_html(buf14,f[23],9999) /*state for dl */,
	 encode_html(buf15,f[50],9999) /*dl*/,
	 buf12, /* all 3 credit cards */
	 encode_html(buf25,f[60],9999) /*passport*/,
	 encode_html(buf30,f[44],9999) /*birthdate*/
	  );
	
    strcat(e,gbuf);
    e = e+   strlen(e);
    *(e++)='\n';
    found=search_next_range_over(base_searcher,search_field,results,&nextline,1);
    count++;
    if (!found) {
      break;
      }
      
    }
      
  strcat(e,"</table>");
  e=e+strlen("</table>");
      
  if (found) {/* have more to do */
    char obuf[10000];
    char gbuf[10000];
    char ubuf[10000];
    add_from_range_url(obuf,url,from_range,from_range+RANGE_SIZE);
    sprintf(gbuf,"<br><a href=\"%s\">Next set of records.</a><br>\n",
        encode_url(ubuf,obuf,512));
    strcat(e,gbuf);  
    e = e+   strlen(e);	     
    } /* if we have more to do */
  
  *e='\0';
        
      } /* if we are not exact - and doing the table mode */
    else { /* exactly one record this one */
      long long curpos;

      html_header(b,NULL,NULL);
      e = b + strlen(b);
      get_pos(results,&curpos);
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
      
      char gbuf[20000]	;
      char phone1[1000];
      char phone2[1000];
      format_phone(phone1, f[25],f[26],f[27]);
      format_phone(phone2,f[39],f[40],f[41]);
      char cc1[1000];
      char cc2[1000];
      char cc3[1000];
      format_ccard(cc1,f[51]);
      format_ccard(cc2,f[54]);
      format_ccard(cc3,f[57]);
      char buf1[10000];
      char buf2[10000];
      char buf3[10000];
      char buf4[10000];
      char buf5[10000];
      char buf6[10000];
      char buf7[10000];
      char buf8[10000];
      char buf9[10000];
      char buf10[10000];
      char buf11[10000];
      char buf12[10000];
      char buf13[10000];
      char buf14[10000];
      char buf15[10000];
      char buf16[10000];
      char buf17[10000];
      char buf18[10000];
      char buf19[10000];
      char buf20[10000];
      char buf21[10000];
      char buf22[10000];
      char buf23[10000];
      char buf24[10000];
      char buf25[10000];
      char buf26[10000];
      char buf27[10000];
      char buf28[10000];
      char buf29[10000];
      char buf30[10000];
/*
      sprintf(gbuf,"<table border=1><tr><th>Rec</th><th>First</th><th>Last</th><th>MI</th><th>Middle</th>"
	"<th>Gender</th><th>Address</th><th>City</th><th>State</th><th>zip</th><th>Phone</th><th>Phone2</th>"
	"<th>SSN</th><th>Drivers License</th><th>cc1</th><th>cc1 exp</th><th>cc1 ccv</th>"
	"<th>cc2</th><th>cc2 exp</th><th>cc2 ccv</th>"
	"<th>cc3</th><th>cc3 exp</th><th>cc3 ccv</th>"
	"<th>Passport</th><th>Passport Code 1</th><th>Passport Code 2</th>"
	"<th>Maiden</th><th>Birth State</th><th>Birth Date</th></tr>\n");
  */    


/* start */
#if SHOW_GOOGLE_PICTURE
/* embed a nother table if there is a map - the map will go to the right */
sprintf(e,"<table><tr><td>");
      e += strlen(e);
#endif
      sprintf(e,"<table border=1>");
      e += strlen(e);

      /* start and name */  
        sprintf(e,
        "<tr><th>Name</th><td><table border=1><tr><th>First</th><th>Middle</th><th>Last</th><th>Suffix</th></tr>"
	 "<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr></table></td></tr>",
	 encode_html(buf1,f[12],9999) /*first */,
	 encode_html(buf2,f[11],9999) /*last*/,
	 encode_html(buf3,f[14],9999) /*middle */,
	 encode_html(buf4,f[28],9999) /*suffix */
	 );
      e += strlen(e);
      fprintf(stderr,"maiden %s\n",f[42]);
      if ((f[34][0]=='F')&&(f[42][0])) { /* if we are female and have a maiden name */
	sprintf(e,"<tr><th>Maiden Name</th><td>%s</td></tr>",
	   encode_html(buf1,f[42],9999));
        e += strlen(e);
	}

      sprintf(e,"</tr>");
      e += strlen(e);
	 


      /* gender */
      if (f[34][0]=='F')  /* if we are female */
	sprintf(e,"<tr><th>Gender</th><td>Female</td></tr>");
      else
        sprintf(e,"<tr><th>Gender</th><td>Male</td></tr>");
      e += strlen(e);
	 
	 
      /* Age group */
      sprintf(e,"<tr><th>Demographic</th><td>%s</td></tr>",encode_html(buf1,f[30],9999));
      e += strlen(e);

     /* birth date */
     sprintf(e,"<tr><th>%s Birth Date</th><td>%s</td></tr>"
           ,encode_html(buf1,f[43],9999)
	   ,encode_html(buf2,f[44],9999));
     e += strlen(e);

#if SHOW_GOOGLE_PICTURE
/* print out a text for the address */
      sprintf(e,"<tr><th>Address</th><td>%s<br>%s, %s<br>%s%s%s</td></tr>",
        encode_html(buf1,f[15],9999) /*address */,
         encode_html(buf7,f[22],9999) /*city*/, 
         encode_html(buf8,f[23],9999) /* state*/,
         encode_html(buf9,f[24],9999) /*zip*/, 
         (f[29][0])? "-" : "", /* dash if zp4 is there */
         encode_html(buf10,f[29],9999) /*zp4*/);
      e += strlen(e);

#else
  /* print out a hyperlink that goes to google */
      sprintf(e,"<tr><th>Address</th><td>"
        "<a href=\"http://maps.google.com/maps?hl=en&q=%s%%20%s,%%20%s%%20%s&ie=UTF8&hq=&gl=us"
       "&hnear=%s%%20%s,%%20%s%%20%s&z=15\">"
        "%s<br>%s, %s<br>%s%s%s</a></td></tr>"
      ,encode_html(buf1,f[15],9999) /*address */
	,encode_html(buf2,f[22],9999) /*city*/
	,encode_html(buf3,f[23],9999) /* state*/
      ,encode_url(buf4,f[24],9999)  /*zip*/
      ,encode_html(buf5,f[15],9999) /*address */
	,encode_html(buf6,f[22],9999) /*city*/
	,encode_html(buf7,f[23],9999) /* state*/
      ,encode_url(buf8,f[24],9999)  /*zip*/
      ,  encode_html(buf9,f[15],9999) /*address */,
         encode_html(buf10,f[22],9999) /*city*/, 
         encode_html(buf11,f[23],9999) /* state*/,
         encode_html(buf12,f[24],9999) /*zip*/, 
         (f[29][0])? "-" : "", /* dash if zp4 is there */
         encode_html(buf13,f[29],9999) /*zp4*/);
      e += strlen(e);
#endif
  



/* telephone */
if (phone1[0]) {
  sprintf(e,"<tr><th>Home Phone</th><td>%s</td></tr>",phone1);
  e += strlen(e);
  }

/* cell phone */
if (phone2[0]) {
  sprintf(e,"<tr><th>Cell Phone</th><td>%s</td></tr>",phone2);
  e += strlen(e);
  }

/* SSN */
sprintf(e,"<tr><th>Social Security Number</th><td>%s</td></tr>",
     encode_html(buf13,f[49],9999) /*ssn */);
e += strlen(e);

/* DL */
sprintf(e,"<tr><th>%s Drivers License</th><td>%s</td></tr>",encode_html(buf8,f[23],9999) /* state */,
              encode_html(buf15,f[50],9999) /* DL */);
e += strlen(e);

/* passport */
if (f[60][0]) {
  sprintf(e,"<tr><th>Passport</th><td><b>Id:</b> %s<br><b>Exp:</b> %s<br><b>"
                "Extra:</b> %s<br></td></th></tr>",
		    encode_html(buf25,f[60],9999) /*passport*/,
		    encode_html(buf1,f[61],9999) /*passport exp date*/,
		    encode_html(buf2,f[62],9999) /*passport extra code*/);
  e += strlen(e);
  sprintf(e,"<tr><th>Passport Code</th><td><pre>%s\n%s</pre></td></tr>",
                encode_html(buf1,f[63],9999), /* passport code 1 */
		encode_html(buf2,f[64],9999) /* passport code 2 */
		);
  e += strlen(e);
  }  			    	    


/* Credit cards */
if (cc1[0]) { /* first credit card */
  sprintf(e,"<tr><th>Credit Card 1</th>"
       "<td><b>Number:</b> %s<br><b>Expire:</b> %s<br> <b>CCV:</b> %s</td></tr>",
        cc1,
	encode_html(buf18,f[52],9999)  /* exp*/,
	encode_html(buf19,f[53],9999)  /* CCV */
	);
  e += strlen(e);
  if (cc2[0]) {
    sprintf(e,"<tr><th>Credit Card 2</th>"
       "<td><b>Number:</b> %s<br><b>Expire:</b> %s<br> <b>CCV:</b> %s</td></tr>",
        cc2,
	encode_html(buf18,f[55],9999)  /* exp*/,
	encode_html(buf19,f[56],9999)  /* CCV */
	);
    e += strlen(e);
    }
  if (cc3[0]) {
    sprintf(e,"<tr><th>Credit Card 3</th>"
       "<td><b>Number:</b> %s<br><b>Expire:</b> %s<br> <b>CCV:</b> %s</td></tr>",
        cc3,
	encode_html(buf18,f[58],9999)  /* exp*/,
	encode_html(buf19,f[59],9999)  /* CCV */
	);
    e += strlen(e);
    }  
  }	
	      


      /* see if married */
      if (f[65][0]) { /* married */
        char search_string[10000];
	char result[10000];
	long long nl;
	search_first_range_over(main_file,f[65],result,&nl,10);
	/* find the record */
	fprintf(stderr,"found %s\n",result);
	char fname[10000];
	char mname[10000];
	char lname[10000];
	char suffix[10000];
	field(result,fname,12);
	field(result,lname,11);
	field(result,mname,14);
	field(result,suffix,28);
        sprintf(e,
        "<tr><th>Married to</th><td><table border=1><tr><th>First</th>"
	"<th>Middle</th><th>Last</th><th>Suffix</th></tr>"
	 "<tr><td><a href=\"/id/%s/\">%s</a></td><td>"
	 "<a href=\"/id/%s/\">%s</a></td><td>"
	 "<a href=\"/id/%s/\">%s</a></td><td>"
	 "<a href=\"/id/%s/\">%s</a></td></tr></table></a></td></tr>",
	 f[65],
	 encode_html(buf1,fname,9999) /*first */,
	 f[65],
	 encode_html(buf2,lname,9999) /*last*/,
	 f[65],
	 encode_html(buf3,mname,9999) /*middle */,
	 f[65],
	 encode_html(buf4,suffix,9999) /*suffix */
	 );
        e += strlen(e);
	
	}

#if SHOW_GOOGLE_PICTURE
/* show the map in a second table around the first */
      /* map */
      sprintf(e,"</table><td>"
      "<a href=\"http://maps.google.com/maps?hl=en&q=%s%%20%s,%%20%s%%20%s&ie=UTF8&hq=&gl=us"
       "&hnear=%s%%20%s,%%20%s%%20%s&z=15\">"
       "<img alt=\"map\" src=\"http://maps.google.com/maps/api/staticmap?center=%s&size=400x400&sensor=false&markers=%s,%%20%s\">"
       "</a>"
       "</td></tr></table>"
      ,encode_html(buf1,f[15],9999) /*address */
	,encode_html(buf2,f[22],9999) /*city*/
	,encode_html(buf3,f[23],9999) /* state*/
      ,encode_url(buf4,f[24],9999)  /*zip*/
      ,encode_html(buf5,f[15],9999) /*address */
	,encode_html(buf6,f[22],9999) /*city*/
	,encode_html(buf7,f[23],9999) /* state*/
      ,encode_url(buf8,f[24],9999)  /*zip*/
      ,encode_url(buf9,f[24],9999) /*zip again*/
      ,encode_html(buf10,f[15],9999) /*address */
      ,encode_url(buf11,f[24],9999)  /*zip again*/);
      e += strlen(e);
#else
      sprintf(e,"</table>");
      e += strlen(e);

#endif


#ifdef bogus            
     /* 
	"<tr><td>%s</td>"
	"<td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s-%s</td>"
	"<td>%s</td><td>%s</td>"
	"<td>%s</td><td>%s %s</td><td>%s</td><td>%s</td><td>%s</td>"
	"<td>%s</td><td>%s</td><td>%s</td>"
	"<td>%s</td><td>%s</td><td>%s</td>"
	"<td>%s</td><td>%s</td><td>%s</td>"
	"<td>%s</td><td>%s</td><td>%s</td></tr></table>\n",
	 encode_html(buf11,phone1,9999),
	 encode_html(buf12,phone2,9999),
	 encode_html(buf13,f[49],9999) /*ssn*/,
	 encode_html(buf14,f[23],9999) /*state for dl */,
	 encode_html(buf15,f[50],9999) /*dl*/,
	 encode_html(buf16,cc1,9999),
	 encode_html(buf17,f[52],9999),
	 encode_html(buf18,f[53],9999) /*ccard 1*/,
	 encode_html(buf19,cc2,9999),
	 encode_html(buf20,f[55],9999),
	 encode_html(buf21,f[56],9999) /*ccard 2*/,
	 encode_html(buf22,cc3,9999),
	 encode_html(buf23,f[58],9999),
	 encode_html(buf24,f[59],9999) /*ccard 3*/,
	 encode_html(buf25,f[60],9999) /*passport*/,
	 encode_html(buf26,f[63],9999) /*code 1*/,
	 encode_html(buf27,f[64],9999) /*code 2*/,
	 encode_html(buf28,f[42],9999) /*maiden*/,
	 encode_html(buf29,f[43],9999) /*birth state*/,
	 encode_html(buf30,f[44],9999) /*birthdate*/
	  );
	
      strcat(e,gbuf);
      e = e+   strlen(e);
      */
#endif      
      *(e++)='\n';
      } /* if we are an exact match */
    } /* if found */
  else { /* not found something weird */
    /*??? log it */
    return (error_404(b,buflength));
    }
  } /* if table or single entry */
*buflength = (e-b);
return b;   
}

int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
  }
  

/*??? add DL? */
main_file = new_searcher("../out/n001.txt",11,0,0);
id_ss = new_super_searcher("../out/n001_id.txt",1,0,0);
city_state = new_super_searcher("../out/n001_city_state.txt",6,0,0);
first_last_middle = new_super_searcher("../out/n001_first_last_middle.txt",5,0,0);
first_middle_last = new_super_searcher("../out/n001_first_middle_last.txt",4,0,0);
last_first_middle = new_super_searcher("../out/n001_last_first_middle.txt",5,0,0);
phone_area_code = new_super_searcher("../out/n001_phone_area_code.txt",5,0,0);
phone_prefix = new_super_searcher("../out/n001_phone_prefix.txt",5,0,0);
ssn = new_super_searcher("../out/n001_ssn.txt",4,0,0);
state_city = new_super_searcher("../out/n001_state_city.txt",12,0,0);
zip4_street = new_super_searcher("../out/n001_zip4_street.txt",10,0,0);
zip_name = new_super_searcher("../out/n001_zip_name.txt",7,0,0);
zip_street = new_super_searcher("../out/n001_zip_street.txt",10,0,0);
everything = new_super_searcher("../out/n001_everything.txt",4,0,0);
return 0;
}


int init_external_call() {
return (init(0,NULL));
}


char *disclaimer() {
return ("<table border=1><tr><th><font size=1 color=red>1</th><td><font size=1 color=red>This data is fallacious</b></td></tr>"
"<tr><th><font size=1 color=red>2</th><td><font size=1 color=red>Use of this data is a crime</td></tr>"
"<tr><th><font size=1 color=red>3</th><td><font size=1 color=red>We record and will report all access of this data to authorities</td></tr></table>"
);
}

void welcome_page(char *b,int *blen) {
html_header(b,NULL,NULL);
char *b2 = b+strlen(b);
sprintf(b2,
"<title>US Identities</title>"
"<head>US Identities</head>"
"<br><br><center>%s</center><br>"
"<hr>Over 250 million identites searchable by various means."
"Please choose from the following search formats:<br>"
"<a href=search>Search by any identifier you choose</a><br>"
"<a href=flm>browse by First,Last,Middle names</a><br>"
"<a href=fml>browse by First,Middle,Last names</a><br>"
"<a href=lfm>browse by Last,First,Middle names</a><br>"
"<a href=ssn>browse by Social Security Number</a><br>"
"<a href=phn>browse by Phone Number area code first</a><br>"
"<a href=pfx>browse by Phone Number prefix first</a><br>"
"<a href=cs>browse by City and State</a><br>"
"<a href=sc>browse by State and City</a><br>"
"<a href=zip>browse by Zip</a><br>"
"<a href=zlfm>browse by Zip, Last Name, First Name</a><br>"
"<hr><center>%s</center>"
,disclaimer(),disclaimer());
*blen = strlen(b);
}



/* this is the same as evercookie_cache.php from before */
char *evercookie_cache(char *b,int searching,char *url,int offset,int *buflength,struct cookie_struct *cookies) {
struct cookie_struct *c;
HASH_FIND_STR(cookies,"zmqfx_cache",c);
if (c) {
  sprintf(b,"Content-Type: text/html\n"
          "Last-Modified: Wed, 30 Jun 2010 21:36:48 GMT\n"
          "Expires: Tue, 31 Dec 2030 23:30:45 GMT\n"
          "Cache-Control: private, max-age=630720000\n\n"
          "%s\n",c->value);
  }
else { /* if we cannot find the cookie - warn the javascript code that we don't have it */
  return warning_304(b,buflength);
  }
*buflength = strlen(b);
}






char  *make_external_call(char *buf,char *url,int *buflength,struct cookie_struct *cookies) {
char *b=malloc(1000000);
char *e;
if (!b) return(strdup(""));
fprintf(stderr,"%s\n",url);
char f1[20000];
int offset=2;
char buff[513];
decode_url(buff,url,512);
url=buff;
int searching=dirfield(url,f1,1);
if (strcmp(f1,"cs")==0) {
  return(display_page(city_state,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"phn")==0) {
  return(display_page(phone_area_code,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"fml")==0) {
  return(display_page(first_middle_last,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"flm")==0) {
  return(display_page(first_last_middle,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"lfm")==0) {
  return(display_page(last_first_middle,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"ssn")==0) {
  return(display_page(ssn,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"phx")==0) {
  return(display_page(phone_prefix,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"sc")==0) {
  return(display_page(state_city,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"zip")==0) {
  return(display_page(zip_street,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"zlfm")==0) {
  return(display_page(zip_name,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"id")==0) {
  return(display_page(id_ss,b,searching,url,offset,buflength));
  }
if (strcmp(f1,"zmqfx")==0) {
  return(evercookie_cache(b,searching,url,offset,buflength,cookies));
  }
if (strcmp(f1,"")==0) {
  welcome_page(b,buflength);
  return b;
  }
else {
  return (error_404(b,buflength));  
  }
*buflength = (e-b);

return(b);
}
