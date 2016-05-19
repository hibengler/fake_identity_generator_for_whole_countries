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
#include "m_routines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
/* This is used for making address indexes
1	0	prefix
2	1	rest
3	2	ac
4	3	phone
5	4	random - 0 in this case
6	5	index position

*/


int main(int argc, char *argv[]) {
int uk_mode;
int i;
uk_mode=0;
for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-u")==0) { /* UK mode */
    uk_mode=1;
    }
  }
long long index_position=0;
long long last_index_position;
char buf[20000];
while (gets(buf)) {
  last_index_position=index_position;
  index_position += strlen(buf) + 1;
  char ac[20000];
  char prefix[20000];
  char rest[20000];
  char full[20000];
  field(buf,ac,25);
  field(buf,prefix,26);
  field(buf,rest,27);
  phone_first(buf,full,uk_mode);
  if (*full) {
    printf("%s|%s|%s|%s|0|%lld\n",
	    prefix,rest,ac,full,
            last_index_position);
    }
  field(buf,ac,39);
  field(buf,prefix,40);
  field(buf,rest,41);
  phone_second(buf,full,uk_mode);
  if (*full) {
    printf("%s|%s|%s|%s|0|%lld\n",
	    prefix,rest,ac,full,
            last_index_position);
    }  
  }
exit(0);
}
