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

This takes the input wives.txt - and reads birthdate1.txt and outputs
the adjusted birth date for the wives.

Wives are as follows:
10% man 3+_ years younger
52% +-2 years
20% 3-5 years older
18% 6+ older

We will adjust as follows:
5% 5-10 years younger
5% 2-5 years younger
52% +-2 years
20% 2-5 years
9% 5-8 years
9% 8-15 years

$Log$
Revision 1.1  2016/05/19 15:29:23  hib
Initial publish as GPL V2

Revision 1.7  2014/01/08 14:33:03  hib
cleaning up

Revision 1.6  2013/04/08 18:15:28  hib
setup for set 6

Revision 1.5  2013/03/26 10:19:22  hib
getting much closer. xlate handles UK formate pretty well for rtruk.
m_to_phone* now have a uk mode.

Revision 1.4  2013/03/24 02:56:51  hib
make_birthdate2 - fixed a bug that is shown in the UK - there were 30 times more people than
average (female) who were exactly 18, because of the clipping algorithm.
So what I did was to randomize the range a bit so the young spouses are 18-19



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


#define START_DATE "15-May-2013"

struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;

int id=1500000001;




struct searcher *mbirthdate1;








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
  

mbirthdate1 = new_searcher("birthdate1.txt",1,populate,locked);



return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
struct value_struct *values;
struct value_struct *c;
values = NULL;
char buf[20000];
char searchline[20000];
char line[20000];
char age_group[20000];
char id[20000];
while (gets(buf)) {
  int sample;
  int target;
  int f;
  int start_date;
  int size;
  int pos;
  char hid[20000];
  field(buf,id,0);
  field(buf,hid,1);
  int day;
  int hdate=0;
  
  sprintf(searchline,"%s|",hid);
  if (search(mbirthdate1,searchline,line)) {
    hdate = fieldi(line,1);
    int hi,lo;
    /* figure out the age */
    start_date = date_to_code(START_DATE);
    int highest_start_date = start_date - 18*(365+365+365+366)/4;
    int guess;
    again:    
    guess= (random()>>2) % 100;
    if (guess<5) {
      lo= hdate + 5 *(365+365+365+366)/4+1;
      hi= hdate + 10*(365+365+365+366)/4;
      }
    else if (guess<10) {
      lo= hdate + 2 *(365+365+365+366)/4+1;
      hi= hdate + 5*(365+365+365+366)/4;
      }
    else if (guess<62) {
      lo= hdate - 2 *(365+365+365+366)/4+1;
      hi= hdate + 2*(365+365+365+366)/4;
      }
    else if (guess<82) {
      lo= hdate - 5 *(365+365+365+366)/4+1;
      hi= hdate - 2*(365+365+365+366)/4;
      }
    else if (guess<91) {
      lo= hdate - 8 *(365+365+365+366)/4+1;
      hi= hdate - 5*(365+365+365+366)/4;
      }
    else  {
      lo= hdate - 15 *(365+365+365+366)/4+1;
      hi= hdate - 8 *(365+365+365+366)/4;
      }
    if (lo > highest_start_date) goto again;
    if (hi > highest_start_date+1) hi = highest_start_date+1;
    
    day =   (random()>>2)  % (hi-lo) + lo;
    }
  else {
    fprintf(stderr,"cannot find husband %s for wife %s\n",hid,id);
    day = fieldi(buf,2);
    }
  fprintf(stdout,"%s|%d\n",id,day);
  }
return(0);
}


