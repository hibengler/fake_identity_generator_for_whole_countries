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
#include <stdio.h>
#include "util.h"
#include "bsearch.h"
#include "phone_common.h"


static struct searcher *phone_fname;
static struct searcher *phone_lname;

int init_phone_name_filters(int argc, char *argv[]) {
int populate,locked;
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

phone_fname = new_searcher("phone_fname.txt",2,populate,locked);
phone_lname = new_searcher("phone_lname.txt",2,populate,locked);
return 0;
}                                                                         
                                                              

int phone_match_with_name(long long number,char *fname,char *lname) {
char searchline[20000];
char results[20000];
if (fname[0]) {
  sprintf(searchline,"%qd|%s|",number,fname);
  if (search(phone_fname,searchline,results)) {
//    fprintf(stderr,"%s -> %s\n",searchline,results);
    return(1);
    }
  sprintf(searchline,"%qd|%c|",number,fname[0]);
  if (search(phone_fname,searchline,results)) { 
//    fprintf(stderr,"%s -> %s\n",searchline,results);
    return(1);
    }
  }
if (lname[0]) {
  sprintf(searchline,"%qd|%s|",number,lname);
  if (search(phone_lname,searchline,results)) {
//    fprintf(stderr,"%s -> %s\n",searchline,results);
    return(1);
    }
  }
return(0);
}
