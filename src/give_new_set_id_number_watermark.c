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

This is pretty close to the end stage.  We look up the new internal id's from
the base ids using the file internal_to_external_m.txt

And also, we generate the initial watermark code for each contact.

For the public data,  
this watermark will pass through,  but the external id's might be different
- for different web servers.

options:
-l - lock file in memory
-p - preload in memory, otherwise it is by page demand, and is slower.


It would be great to use build id to internal id to do this,  
BUT we don't have enough room
to read in the ascii.  
So instead, we convert it to a binary table of 300 million
integers- and read in the file and convert it.
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


int populate=0;
int locked=0;

int *external;
int external_count=0;


struct searcher *all_spouse;

char * external_id_from_internal_id(char *internal_id,
char *external_id)
{
int internal,externala;
if (internal_id[0]=='\0') {
  external_id[0]='\0';
  return external_id;
  }
internal = atoi(internal_id);
int hi=external_count-1;
int lo=0;
int m;
for (m=(hi+lo)/2;hi>=lo;m=(hi+lo)/2) {
  if (internal > external[m+m]) lo=m+1;
  else if (internal < external[m+m]) hi=m-1;
  else {
    externala = external[m+m+1];
    sprintf(external_id,"%010d",externala);
    return(external_id);
    }
  }
fprintf(stderr,"error cannot find internal %s i %d e %d\n",internal_id,internal,externala);
exit(-1);
}




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

  
external=calloc(1,sizeof(int)*600000000);  
if (!external) {
 fprintf(stderr,"memory\n");
 exit(-1);
 }
for (i=0;i<600000000;i++) { external[i]=0;}

FILE *fd;
fd = fopen("internal_to_external_m.txt","r");
if (!fd) {
  fprintf(stderr,"file not found\n");
  exit(-1);
  }
char buf[20000];
external_count=0;
while (fgets(buf,20000,fd)) {
  int l=strlen(buf);
  if (l) buf[l-1]='\0';
  
  int internal=fieldi(buf,0);
  int externala=fieldi(buf,1);
  external[external_count+external_count] = internal;
  external[external_count+external_count+1] = externala;
  external_count++;
  }
fclose(fd);

return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char *set;
char *own;
set=getenv("SET");
if (!set) {
  fprintf(stderr,"Error need SET!\n");
  exit(-1);
  }
own=getenv("OWN");
if (!own) {
  fprintf(stderr,"Error need OWN!\n");
  exit(-1);
  }
  
char buf[20000];
char obuf[20000];
char phase1[20000];
char phase2[20000];
char idx[20000];
char idy[20000];
char newid[20000];
char newspouseid[20000];
char street_type[20000];
while (gets(buf)) {
  fieldspan(buf,phase1,11,64,1);
  fieldspan(buf,phase2,66,74,1);
  field(buf,idx,10); /* main id */
  external_id_from_internal_id(idx,newid);
  field(buf,idy,65); /* spouse id */
  external_id_from_internal_id(idy,newspouseid);
  sprintf(buf,"||||||||||%s|%s%s|%s\n",newid,phase1,newspouseid,phase2);
  char wm1[20];
  char wm2[20];
  char wm3[20];
  char wm4[20];
  gen_watermark_code(buf,wm1,wm2,wm3,wm4);
  watermark(buf,obuf,wm1,wm2,wm3,wm4);
  printf("%s\n",obuf);
   /* should make a file showing the watermarks for the base - so we know
   if the base was compromised */
  if (wm1[0]) {
    char addr[20000];
    char zip[20000];
    field(obuf,addr,15);
    field(obuf,zip,24);
    fprintf(stderr,"addr+zip|%s|%s||||%s|%s|%s|%s|||\n",
      addr,zip,set,own,newid,idx);
    }
  if (wm2[0]) {
    char cc[20000];
    field(obuf,cc,51);
    fprintf(stderr,"cc+ccv|%s|%s||||%s|%s|%s|%s|||\n",
       cc,wm2,set,own,newid,idx);
    }
  if (wm3[0]) {
    char cc[20000];
    field(obuf,cc,54);
    fprintf(stderr,"cc+ccv|%s|%s||||%s|%s|%s|%s|||\n",
       cc,wm3,set,own,newid,idx);
    }
  if (wm4[0]) {
    char cc[20000];
    field(obuf,cc,57);
    fprintf(stderr,"cc+ccv|%s|%s||||%s|%s|%s|%s|||\n",
       cc,wm4,set,own,newid,idx);
    }  
  }
return(0);
}


