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
/* make_dl_sort_code - this makes a drivers license sort code 
which is the State followed by the number of days +- 700
This gives a nice way to order things approximately by 
state and birthdate, so we can assign drivers license numbers based on when 
they generally will get them
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "soundex.h"
#include "uthash.h"
#include "util.h"

int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
    }
  

return 0;
}



int main(int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char *bufa;
while (gets(buf)) {
  bufa=buf;
  while ((*bufa)&&(*bufa != '|')) bufa++;
  char state_code[20000];
  field(buf,state_code,14);
  int bdcode=fieldi(buf,51); /* birthdate code */
  bdcode = bdcode + 350 - ((random()>>2) % 700);
  bdcode = bdcode * 100 +  ((random()>>2) % 100); /* add some more randomness
                                                    so we don't end up always going
						    in the order of the id if 
						     the date cod eis the same */
  printf("%s%010d%s\n",state_code,bdcode,bufa);
  }
exit(0);
}
