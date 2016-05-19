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

/* simple formatter foe the everything.txt search file */
int main(int argc,char *argv[]) {
int rflag = (argc>=2);
char buf[20000];
char *bbuf;
char obuf[20000];
while (gets(buf)) {
  char ch;
  char *x;
  char *l1;
  char *l2;
  bbuf=buf;
  
  /* skip the row number */
  while ((*bbuf)&& (*bbuf != '|')) {bbuf++;}
  if (*bbuf=='|') bbuf++;
  
  l1=l2=x=bbuf;
  while (*x) {
    if (*x == '|') {
      l2=l1;
      l1=x;
      }
    if (*x == '\n') {
      *x='\0';
      }
    x++;
    }
  if (rflag) *l2='\0'; else *l1='\0';
  if (l1!=x) l1++;
  x=bbuf;
  char *y=obuf+1;
  obuf[0]=' ';
  while (*x) {
    if (*x == '|') {
      if (y[-1]!=' ')
        *(y++) = ' ';
      }
    else if (*x == ' ') {
      if (y[-1]!=' ')
        *(y++) = ' ';
      }
    else {
      *(y++) = *x;
      }
    x++;
    }
  while ((y>obuf+1)&&(y[-1]==' ')) y--;
  *y = '\0';
  printf("%s|%s\n",(obuf+1),l1);
  }
}
