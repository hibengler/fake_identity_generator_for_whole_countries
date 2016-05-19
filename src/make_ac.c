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
Derived by make_name_from_name

usage make_name_from_name <l004.txt (or regurgitation) >out 2>singleton seed_number
options:
-l - lock file in memory
-p - preload in memory, otherwise it is by page demand, and is slower.
-f - change first name/middle name/suffix only, not the last name.
     the last name is pulled from the regurgitation, or from maiden name if the person is a wife.
-w wifey mode, implies -f
   we are a wife! For wives, we do things differently - and still use the first name last name prefix.
-g generic mode.  
  We get the first name/last name 
     
This is meant to read from l004 and try to rename everybody.

Some names are still singletons - these are separated out.  They will have to be named differently.


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
int wife_mode=0;





struct searcher *acs_per_zip;
struct searcher *acs_by_zip;

int random_ac_from_zip(char *zip,
char *line) 
{
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|",zip);
search(acs_per_zip,searchline,line);
int pos;
int size=fieldi(line,1);
if (size)
  pos =(random()>>2) % size+1;
else pos=0;  
sprintf(searchline2,"%s|%010d|",zip,pos);
search(acs_by_zip,searchline2,line);
return size;
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
  

acs_per_zip = new_searcher("acs_per_zip.txt",3,populate,locked);
acs_by_zip = new_searcher("acs_by_zip.txt",3,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char phase1[20000];
char phase2[20000];
char ac[20000];
char zip[20000];

while (gets(buf)) {
  field(buf,ac,16);
  if (ac[0]=='\0') {
    field(buf,zip,15);
    fieldspan(buf,phase1,0,15,1);
    fieldspan(buf,phase2,17,30,0);
    char line[20000];
    random_ac_from_zip(zip,line);
    field(line,ac,2);
    if (ac[0]=='\0') {
      fprintf(stderr,"failed %s\n",buf);
      exit(-1);
      }
    printf("%s%s|%s\n",phase1,ac,phase2);
    }
  else { /* cannot find a nee name */
    puts(buf);
    }
  }
return(0);
}


