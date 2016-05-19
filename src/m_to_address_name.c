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
#include "m_routines.h"
#include <stdio.h>
#include <string.h>
#include "util.h"
/* This is used for making address indexes
1	0	city
2	1	state
3	2	zip
4	3	street
5	4	full street name
6	5	full address (not watermarked)
7	6	full address (watermarked)
8	7	full name last, first middle
9	8	index position

If -u (UK) we add the zip+4 information:

1	0	city
2	1	state
3	2	zip
4	3	zip+4
5	4	street
6	5	full street name
7	6	full address (not watermarked)
8	7	full address (watermarked)
9	8	full name last, first middle
10	9	index position

*/


int main(int argc,char *argv[]) {
int i;
int uk_mode;
uk_mode=0;
i=0;
while (i<argc) {
  if (strcmp(argv[i],"-u")==0) {
    uk_mode = 1;
    }
  if (strcmp(argv[i],"-u2")==0) {
    uk_mode = 2; /* dont expand the cities - for a uk zip code */
    }
  i++;
  }

long long index_position=0;
long long last_index_position;
char buf[20000];
while (gets(buf)) {
  last_index_position=index_position;
  index_position += strlen(buf) + 1;
  char city[20000];
  char state[20000];
  char zip[20000];
  char street[20000];
  char tstreet_name[20000];
  char tfull_address[20000];
  char wm_full_address[20000];
  
  field(buf,city,22);
  field(buf,state,23);
  field(buf,zip,24);
  field(buf,street,18);
  street_name(buf,tstreet_name);
  if (uk_mode==0) {
    full_address_csz(buf,tfull_address);
    printf("%s|%s|%s|%s|%s|%s|%lld\n",
            city,
	    state,
	    zip,street,
	    tstreet_name,
            tfull_address,last_index_position);
    }
  else {
    char zip4[20000];
    field(buf,zip4,29);
    full_address_csz4(buf,tfull_address," ");
    
    /* make each city, town, county separately */
    if ((uk_mode!=2)&&(index(city,','))) {
      char c[20000];
      char reverse[20000];
      char last[20000];
      char *comma;
      strcpy(c,city);
      char *cc = c;
      char *cb = c;
      comma="";
      reverse[0]='\0';
      last[0]='\0';
      while (*cc) {
        if (*cc == ',') {
	  *cc = '\0';
	  /*trim spaces off the end */
	  while ((cc>cb)&&(cc[-1]<=' ')) {
	    cc--;
	    cc = '\0';
	    }
	  /* trim spaces off the fromt */
	  while ((cb<cc)&&(cb[0]<=' ')) {
	    cb++;
	    }
          if (strcmp(last,cb) != 0) { /* watch out for London, London */
  	    printf("%s|%s|%s|%s|%s|%s|%s|%lld\n",
              cb,
	      state,
	      zip,zip4,street,
	      tstreet_name,
              tfull_address,last_index_position);
	    char r[20000];
	    strcpy(r,reverse);
	    strcpy(reverse,cb);
	    strcat(reverse,comma);
	    strcat(reverse,r);
	    comma=", ";
	    strcpy(last,cb);
	    }
	  cb = cc;
          }
	cc++;
	}
      /* print out the last one */
      /*trim spaces off the end */
      while ((cc>cb)&&(cc[-1]<=' ')) {
        cc--;
	cc = '\0';
	}
      /* trim spaces off the fromt */
	while ((cb<cc)&&(cb[0]<=' ')) {
	cb++;
	}
      if (strcmp(last,cb) != 0) {
        printf("%s|%s|%s|%s|%s|%s|%s|%lld\n",
            cb,
	    state,
	    zip,zip4,street,
	    tstreet_name,
            tfull_address,last_index_position);
	}
      char r[20000];
      strcpy(r,reverse);
      strcpy(reverse,cb);
      strcat(reverse,comma);
      strcat(reverse,r);
      
      if (strcmp(reverse,city)!= 0) { /* watch out for london, london */
        /* print out the reverse order one */
        printf("%s|%s|%s|%s|%s|%s|%s|%lld\n",
            reverse,
	    state,
	    zip,zip4,street,
	    tstreet_name,
            tfull_address,last_index_position);
	}
      }	/* if we are not mode 2 (zip no expand city) and there are multiple cities, townes in this record */	  
    char *cx;
    cx = city;
    while (*cx <= ' ') cx++;
    printf("%s|%s|%s|%s|%s|%s|%s|%lld\n",
            cx,
	    state,
	    zip,zip4,street,
	    tstreet_name,
            tfull_address,last_index_position);
    }
  }
}
