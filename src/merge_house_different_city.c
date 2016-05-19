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
Usage: merge_house_different_city house_city.txt house_nocity.txt >house_fix.txt

Takes house and house_nocity and merges them - assumed sorted.

For each record in hose - compare to house_nocity.  If they are equal:
See if the count is equal, do nohting, if not, we need to identify which city to make this house, and output it.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "uthash.h"

char *house_nocity_fname;
char *house_city_fname;
FILE *hcity;
FILE *hnocity;

int init (int argc, char *argv[]) {
int i;
if (argc>=3) {
  house_city_fname=argv[1];
  house_nocity_fname=argv[2];
  }
else {
  fprintf(stderr,"files not there\n");
  exit(-1);
  }
  
hcity = fopen(house_city_fname,"r");
if (!hcity) {
  fprintf(stderr,"error cannot open %s\n",house_city_fname);
  exit(-1);
  }
  
hnocity = fopen(house_nocity_fname,"r");
if (!hnocity) {
  fprintf(stderr,"error cannot open %s\n",house_nocity_fname);
  }

}

int main (int argc, char *argv[]) {
char buf[20000];
char zipland[20000];
char cityland[20000];
char buf2[20000];
char bufa[100][20000];
int buf2_flag;

init(argc,argv);
buf2_flag=0;

while (fgets(buf,19999,hnocity)) {
  buf[19999]='\0';
  fieldspan(buf,zipland,0,7,1);
  
  if (buf2_flag || (!fgets(buf2,19999,hcity))) {
    if (buf2_flag) {
      buf2[19999]='\0';
      fieldspan(buf2,cityland,0,7,1);
      buf2_flag = 0;
      }
    if (strcmp(zipland,cityland)) /* if different, we are not sorted or something, DIE! */
      {
      fprintf(stderr,"Error. Mismatch, wanted %s (nocity) but found %s in city\n",zipland,cityland);
      exit(-1);
      }
    int max;
    if ((max=fieldi(buf2,11)) != fieldi(buf,9)) {
      /* we need to decide which city to use */
      int biggest=0;
      strcpy(bufa[0],buf2);
      int count=1;
      buf2_flag = 1;
      do {
        if (!fgets(bufa[count],19999,hcity)) {
	  buf2_flag=0; /* last record */
	  break;
	  }
	bufa[count][19999]='\0';
        fieldspan(bufa[count],cityland,0,7,1);
        if (strcmp(zipland,cityland)) {
	  break;
	  }
	int x;
	x = fieldi(buf2,11);
	if (x>max) {
	  max=x;
	  biggest=count;
	  }
	} while (1);
      printf("%s",bufa[biggest]);
      } /* if we need to clarify */
    }
  } /* for every line in the buffer */
}
