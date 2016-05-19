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

V1.2 Jan 2012 - Added a fudge factor - 20% so that we can alievieate some of the states
V1.1
State migration from every state to every state.

We will load in 1 dummy record from evey state to every state.
Just so that anything is possiuble.
Then we read the ssdi cleaned up sample, convert states to upper case, and
convert the ssn to the born in state.  This will allow us to better distribute
people based on their born in state, so states like alaska will work.
Cuz nobody is born in alaska, they just move there.

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



struct value_struct {
char *value;
int id;
UT_hash_handle hh;
};

int populate=0;
int locked=0;





struct searcher *marea_number_state;
struct searcher *mstate_clean;

int state_count=55;
char * statez[55] = {
"AK",
"AL",
"AR",
"AS",
"AZ",
"CA",
"CO",
"CT",
"DC",
"DE",
"FL",
"GA",
"GU",
"HI",
"IA",
"ID",
"IL",
"IN",
"KS",
"KY",
"LA",
"MA",
"MD",
"ME",
"MI",
"MN",
"MO",
"MS",
"MT",
"NC",
"ND",
"NE",
"NH",
"NJ",
"NM",
"NV",
"NY",
"OH",
"OK",
"OR",
"PA",
"PR",
"RI",
"SC",
"SD",
"TN",
"TX",
"UT",
"VA",
"VI",
"VT",
"WA",
"WI",
"WV",
"WY"
};




double statez_factor[55] = {
0.74,		// "AK",
0.85,		// "AL",
1.,		// "AR",
1.,		// "AS",
1.,		// "AZ",
1.,		// "CA",
1.,		// "CO",
0.6,		// "CT",
0.75,		// "DC",
0.6,		// "DE",
1.,		// "FL",
1.,		// "GA",
1.,		// "GU",
1.,		// "HI",
0.7,		// "IA",
0.95,		// "ID",
0.95,		// "IL",
0.65,		// "IN",
0.7,		// "KS",
0.9,		// "KY",
1.,		// "LA",
0.5,		// "MA",
0.9,		// "MD",
0.5,		// "ME",
0.7,		// "MI",
0.8,		// "MN",
0.65,		// "MO",
1.,		// "MS",
0.75,		// "MT",
1.,		// "NC",
0.65,		// "ND",
0.8,		// "NE",
0.5,		// "NH",
0.6,		// "NJ",
1.,		// "NM",
1.,		// "NV",
0.3,		// "NY",  Really 0.5 but we will use new york as the main filler
0.6,		// "OH",
0.65,		// "OK",
0.9,		// "OR",
0.4,		// "PA",
1.,		// "PR",
0.4,		// "RI",
1.0,		// "SC",
0.75,		// "SD",
1.0,		// "TN",
1.0,		// "TX",
1.0,		// "UT",
1.0,		// "VA",
0.68,		// "VI",
0.5,		// "VT",
1.,		// "WA",
0.6,		// "WI",
0.8,		// "WV",
0.8		// "WY"
};




int statez_area_count[55] = {
1,		// "AK",
9,		// "AL",
4,		// "AR",
0,		// "AS",
4,		// "AZ",
54,		// "CA",
4,		// "CO",
10,		// "CT",
3,		// "DC",
2,		// "DE",
14,		// "FL",
9,		// "GA",
0,		// "GU",
2,		// "HI",
8,		// "IA",
2,		// "ID",
44,		// "IL",
15,		// "IN",
7,		// "KS",
8,		// "KY",
7,		// "LA",
25,		// "MA",
9,		// "MD",
4,		// "ME",
25,		// "MI",
10,		// "MN",
15,		// "MO",
6,		// "MS",
2,		// "MT",
10,		// "NC",
2,		// "ND",
4,		// "NE",
3,		// "NH",
24,		// "NJ",
4,		// "NM",
1,		// "NV",
85,		// "NY",  Really 0.5 but we will use new york as the main filler
35,		// "OH",
9,		// "OK",
5,		// "OR",
53,		// "PA",
8,		// "PR",
5,		// "RI",
5,		// "SC",
2,		// "SD",
8,		// "TN",
38,		// "TX",
4,		// "UT",
9,		// "VA",
1,		// "VI",
2,		// "VT",
9,		// "WA",
13,		// "WI",
5,		// "WV",
1		// "WY"
};

double statez_pos[55];

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
  

marea_number_state = new_searcher("area_number_state.inp",1,populate,locked);
mstate_clean = new_searcher("state_clean.inp",1,populate,locked);

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

/* states pos setup */
{
  int i;
  int other_count;
  other_count = 0;
  for (i=0;i<state_count;i++) {
    statez_pos[i] = (1.0 -statez_factor[i]) * ((double)(statez_area_count[i]));
    if (statez_factor[i] == 1.0) other_count += statez_area_count[i];
    }

  /* make a distribution */    
  for (i=1;i<state_count;i++) {
    statez_pos[i] += statez_pos[i-1];
    }
  }


/* first prepopulate with every state transfer */
{
  int i,j;
  for (i=0;i<state_count;i++) {
    for (j =0;j<state_count;j++) {
      printf("%s|%s\n",statez[i],statez[j]);
      }
    }
  }

while (gets(buf)) {
  char die_state[20000];
  char ssn1[20000];
  char fstate[20000];
  char tstate[20000];
  field(buf,die_state,11);
  field(buf,ssn1,1);

  sprintf(searchline,"%s|",ssn1);
  if (search(marea_number_state,searchline,line)) {
    field(line,fstate,1);
    
    sprintf(searchline,"%s|",die_state);
    if (search(mstate_clean,searchline,line)) {
      field(line,tstate,1);
      printf("%s|%s\n",fstate,tstate);
      }
    if (rand() % 100 <20 ) { /* 20 percent add on */
      double x;
      x = ((double)(rand() % 10000)) * 0.0001;
      x = x * statez_pos[state_count-1];
      int i;
      for (i=0;i<state_count;i++) {
        if (x <=statez_pos[i]) break;
        }
      if (i==state_count) i--;
      printf("%s|%s|d\n",statez[i],tstate); /* duplicate fudge */
      } /* if we are selected to fudge */
    }
  }
return(0);
}


