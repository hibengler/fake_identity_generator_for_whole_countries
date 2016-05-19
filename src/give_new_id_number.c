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
the base ids using the file ../common/build_id_to_internal_id.txt

And also, we generate the initial watermark code for each contact.

For the public date,  this watermark will pass through,  but the external id's might be different
- for different web servers.

But we cannot do the watermarks yet
usage make_name_from_name <l004.txt (or regurgitation) >out 2>singleton seed_number
options:
-l - lock file in memory
-p - preload in memory, otherwise it is by page demand, and is slower.


It would be great to use build id to internal id to do this,  BUT we don't have enough room
to read in the ascii.  So instead, we convert it to a binary table of 300 million
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

int *internal;
int internal_count=0;


struct searcher *build_id_to_internal;
struct searcher *all_spouse;

char * internal_id_from_base_id(char *base_id,
char *internal_id)
{
int base,internala;
base = atoi(base_id);
int hi=internal_count-1;
int lo=0;
int m;
for (m=(hi+lo)/2;hi>=lo;m=(hi+lo)/2) {
  if (base > internal[m+m]) lo=m+1;
  else if (base < internal[m+m]) hi=m-1;
  else {
    internala = internal[m+m+1];
    sprintf(internal_id,"%010d",internala);
    return(internal_id);
    }
  }
fprintf(stderr,"error cannot find base %s b %d i %d\n",base_id,base,internala);
exit(-1);
}


char * spouse_internal_id_from_base_id(char *base_id,
char *spouse_internal_id)
{
/* This looks for a spouse,  and if one is found, we get the internal spouse id
and store it.
It is a little bad because it correlates 100% with last name MF pairs, oh well */
char searchline[20000];
char line[20000];
sprintf(searchline,"%s|",base_id);
char spouse_base_id[20000];
if (search(all_spouse,searchline,line)) {
  field(line,spouse_base_id,1);
  internal_id_from_base_id(spouse_base_id,spouse_internal_id);
  }
else {
  spouse_base_id[0]='\0';
  spouse_internal_id[0]='\0';
  }
return(spouse_internal_id);
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

  
internal=calloc(1,sizeof(int)*600000000);  
if (!internal) {
 fprintf(stderr,"memory\n");
 exit(-1);
 }
for (i=0;i<300000000;i++) { internal[i]=0;}

FILE *fd;
fd = fopen("../common/build_id_to_internal_id.txt","r");
if (!fd) {
  fprintf(stderr,"file not found\n");
  exit(-1);
  }
char buf[20000];
internal_count=0;
while (fgets(buf,20000,fd)) {
  int l=strlen(buf);
  if (l) buf[l-1]='\0';
  
  int base=fieldi(buf,0);
  int internala=fieldi(buf,1);
  if (base >=1000000001) {
    internal[internal_count+internal_count] = base;
    internal[internal_count+internal_count+1] = internala;
    }
  internal_count++;
  }
fclose(fd);

all_spouse = new_searcher("all_spouse.txt",1,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char phase1[20000];
char idx[20000];
char newid[20000];
char newspouseid[20000];
while (gets(buf)) {
  fieldspan(buf,phase1,1,73,1);
  field(buf,idx,1);
  internal_id_from_base_id(idx,newid);
  spouse_internal_id_from_base_id(idx,newspouseid);
  printf("|%s|%s|%s\n",phase1,newid,newspouseid);
  }
return(0);
}


