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
add_ccs - read standard in, and read the cc file 
and attach the cc file to standard in - noting the following
* never have 2 discovers
* never have 2 amex
* almost never have 2 mcs



*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "soundex.h"
#include "util.h"




FILE *ccpipe;






int init (int argc, char *argv[]) {
int i;
int r=0;
for (i=1;i<argc;i++) {
    srandom(r=atoi(argv[i]));
    }
char cmd[20000];
sprintf(cmd,"perl mycc.pl 2000000000 %d",r);
ccpipe=popen(cmd,"r");
if (!ccpipe) {
  fprintf(stderr,"Cannot open cc command: %s\n",cmd);
  exit(-1);
  }
return 0;
}

char * getcc(char *cc) {
  return(fgets(cc,20000,ccpipe));
}



int main(int argc, char *argv[]) {
init(argc,argv);
char z[20000];
  
while (gets(z)) {
  int number_ccs;
  int cc_determ = (random()>>2) % 100;
  if (cc_determ <=20) {
    number_ccs=1;
    }
  else if (cc_determ<60) {
    number_ccs=2;
    }
  else {
    number_ccs=3;
    }
  int mc=0;
  int disc=0;
  int visa=0;
  int amex=0;
  char cc1[20000];
  char cc1_exp[20000];
  char cc1_ccv[20000];
  char cc2[20000];
  char cc2_exp[20000];
  char cc2_ccv[20000];
  char cc3[20000];
  char cc3_exp[20000];
  char cc3_ccv[20000];
  cc1[0]='\0';
  cc1_exp[0]='\0';
  cc1_ccv[0]='\0';
  cc2[0]='\0';
  cc2_exp[0]='\0';
  cc2_ccv[0]='\0';
  cc3[0]='\0';
  cc3_exp[0]='\0';
  cc3_ccv[0]='\0';
  int i;
  for (i=0;i<number_ccs;i++) {
    int ok=0;
    char cc[20000];
    do {
      getcc(cc); 
      char type[20000];
      field(cc,type,3);
      if (strcmp(type,"mastercard")==0) {
        if (mc&&((random()>>2)%100)>85) continue;
	mc++;
	}
      else if (strcmp(type,"discover")==0) {
        if (disc) continue;
	disc++;
	}
      else if (strcmp(type,"amex")==0) {
        if (amex) continue;
	amex++;
	}
      else if (strcmp(type,"visa")==0) {
        if (visa>=2) continue;
	visa++;
	}
      ok=1;
      } while (!ok);
    if (i==0) {
      field(cc,cc1,0);
      field(cc,cc1_exp,1);
      field(cc,cc1_ccv,2);
      }
    else if (i==1) {
      field(cc,cc2,0);
      field(cc,cc2_exp,1);
      field(cc,cc2_ccv,2);
      }
    else {
      field(cc,cc3,0);
      field(cc,cc3_exp,1);
      field(cc,cc3_ccv,2);
      }
    }
  printf("%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",z,cc1,cc1_exp,cc1_ccv,
                                             cc2,cc2_exp,cc2_ccv,
					     cc3,cc3_exp,cc3_ccv);
  }
exit(0);
}
