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
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "util.h"
#include "uthash.h"


/* Makes newhouse.txt - which is used to pick new houses out

Input: house.txt:
field int	froml	name
1	0	16	zip
2	1	9	street direction
3	2	30	spanish street type
4	3	10	street name
5	4	11	street type
6	5	31	second street direction
7	6	8	street number
8	7	12	subdivision type
9	8	13	subdivision number
10	9	14	city
11	10	15	state


Output:
1	0	zip
2	1	index
3	2	street direction
4	3	spanish street type
5	4	street name
6	5	street type
7	6	second street direction
8	7	street number
9	8	blank
10	9	blank
11	10	city
12	11	state

*/

char buf[20000];
char obuf[20000];


struct xstruct {
int address;
char *city_state;
UT_hash_handle hh;
};

int key_sort(struct xstruct *a,struct xstruct *b) {
if (a->address>b->address) return(1);
if (a->address<b->address) return(-1);
return(0);
}


int init (int argc, char *argv[]) {
return 0;
}



struct xstruct *values = NULL;
struct xstruct *c;
char old_heading[20000];
char heading[20000];
char old_zip[20000];
char zip[20000];
char addy[20000];
char city_state[20000];
int icount;
int the_index;
int even[100000];
char *even_city[100000];
int evencount;
int odd[100000];
char *odd_city[100000];
int oddcount;


int expand(int arr[],char *city_arr[],int count) 
{
int i;
int prev=0;
int current=0;
for (i=0;i<count;i++) {
  prev=current;
  current = arr[i];
  if (!prev) continue;
  if (current-prev >1000) continue;
  if ((current-prev<=300) && ((current/100) != (prev/100)) ) continue;
  int j;
  j = prev+2;
  while (j<current) {
    the_index++;
    printf("%s|%010d|%s%d|||%s\n",zip,the_index,old_heading,j,city_arr[i]);
    j += 2;
    }
  free(city_arr[i]);
  }
}


int heading_change() {
if (strcmp(old_zip,zip)) {
  the_index=0;
  }

evencount=0;
oddcount=0;
HASH_SORT(values,key_sort);
for (c=values;c!=NULL;c=values) {
  if (c->address%2 ==0) {
    even[evencount]=c->address;
    even_city[evencount++]=c->city_state;
    }
  else {
    odd[oddcount] = c->address;
    odd_city[oddcount++] = c->city_state;
    }
  HASH_DELETE(hh,values,c);
  free(c);
  }
expand(even,even_city,evencount);
expand(odd,odd_city,oddcount);
icount=0;
}

int main (int argc, char *argv[]) {
int i;
old_heading[0]='\0';
old_zip[0]='\0';
icount=0;
while (gets(buf)) {
  field(buf,zip,0);
  fieldspan(buf,heading,1,5,1); /* street direction, spanish name, street name, street typem and second stree dir */
  field(buf,addy,6); /* street number */
  fieldspan(buf,city_state,9,10,0);
  if (strcmp(heading,old_heading)) {
    heading_change();
    }
  strcpy(old_heading,heading);
  strcpy(old_zip,zip);
  icount = icount + 1;
  c = malloc(sizeof(struct xstruct));
  if (!c) { fprintf(stderr,"memory!\n"); exit(-1); }
  c->address = atoi(addy);
  c->city_state=strdup(city_state);
  HASH_ADD_INT(values,address,c);
  }
if (old_heading[0]) heading_change();
return(0);
}



