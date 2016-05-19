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
/* phone expand - for the m series of records
This will print out 2 rows possibly - depending on if the phone number is entered or not
for each phone number it will also have the index of the position in the original file
Also has a random number
Cool, eh?
  */
#include <stdio.h>
#include <string.h>


int fields[1000];
int fieldcount=0;

char *fpos[10000];

char buf[20000];

int main (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
  int w=0;
  w=atoi(argv[i]);
  if (w != 0) {
    fields[fieldcount++] = w;
    }
  }

while(gets(buf) != NULL) {
  int cols=0;
  char *q= buf;
  char *r = q;
  while (*r) {
    while (*r &&(*r != '|')) r++;
    fpos[cols++] =q;
    if (*r) {
      *r = '\0';
      r++;
      }
    q=r;    
    }
  if (fpos[25][0]) {
    ???
  for (i=0;i<fieldcount;i++) {
    int pos = fields[i]-1;
    if (pos<cols) {
      if (i) printf("|%s",fpos[pos]);
      else printf("%s",fpos[pos]);
      }
    else {
      if (i) putchar('|');
      }
    }
  putchar('\n');
  } 
return(0);
}
