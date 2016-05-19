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
#include <string.h>
#include <stdlib.h>

FILE *indexf;
int index_state=0;
int index_bytes=0;
int index_lines=0;
int index_file_number=0;

FILE *xf;
int state=0;
int bytes=0;
int lines=0;
int file_number=0;


char *starturl;
char *storeurl;
char *fname;


void open_index_file() {
index_state=1;
index_bytes=0;
index_lines=0;
index_file_number++;
char b2[20000];
sprintf(b2,"%s_index_%2.2d.xml",fname,index_file_number);
indexf=fopen(b2,"w");
if (!indexf) {
  fprintf(stderr,"error opening %s\n",b2);
  exit(-1);
  }
fprintf(indexf,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<sitemapindex xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n");
file_number=0;
}

void close_index_file() {
fprintf(indexf,"</sitemapindex>\n");
index_state=0;
fclose(indexf);
}


void open_sitemap_file() {
if (index_state==0) {
  open_index_file();
  }
char b2[20000];
char b2a[20000];
file_number++;
sprintf(b2,"%s_index_%2.2d_%5.5d.xml.gz",fname,index_file_number,file_number);
char b3[20000];
sprintf(b3,"<sitemap><loc>%s%s</loc></sitemap>\n",storeurl,b2);
int len=strlen(b3);
if ((index_lines+1>49000)||((bytes+len) > 10000000)) {
  close_index_file();
  open_index_file();
  sprintf(b2,"%s_index_%2.2d_%5.5d.xml.gz",fname,index_file_number,file_number);
  sprintf(b3,"<sitemap><loc>%s%s</loc></sitemap>\n",storeurl,b2);
  len=strlen(b3);
  }
fputs(b3,indexf);
index_lines++;
index_bytes += len;

sprintf(b2a,"gzip >%s",b2);
xf=popen(b2a,"w");
if (!xf) {
  fprintf(stderr,"error opening %s\n",b2);
  exit(-1);
  }
fprintf(xf,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n");
state=1;
bytes=0;
lines=0;
}


void close_sitemap_file() {
fprintf(xf,"</urlset>\n");
pclose(xf);
state=0;
}


int main (int argc,char *argv[]) {
/* url storeurl fname */
starturl=argv[1];
storeurl=argv[2];
fname=argv[3];

char buf[20000];
while (gets(buf)) {
  if (state==0) {
    open_sitemap_file();
    }
  char b3[20000];
  sprintf(b3,"<url><loc>%s%s</loc><changefreq>yearly</changefreq></url>\n",starturl,buf);
  int len;
  len=strlen(b3);
  if ((lines+1>49000)||((bytes+len) > 10000000)) {
    close_sitemap_file();
    open_sitemap_file();
    }
  fputs(b3,xf);
  lines++;
  bytes += len;
  }

if (state != 0) {
  close_sitemap_file();
  }
if (index_state != 0) {
  close_index_file();
  }
return(0);
}
