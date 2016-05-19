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

??? - noticed that maden name is not being generated here.
But we are probably not filtering for maiden name either, so who fn cares
I care. We will now make the maiden name

Nov 3 - Cleaned it so first name != original, same with last name and middle, also made it so that there is always a middle name if the initial is specified.

Oct 19 - added a check - somehow this is makeing names with null first names

Jul 21 - added gender

ID

The first supersearcher.  
usage make_name_from_name <l004.txt (or regurgitation) >out 2>singleton seed_number


Otherwise we use names based on geography


usage make_name_from_name <l004.txt (or regurgitation) >out 2>singleton seed_number
options:
-l - lock file in memory
-p - preload in memory, otherwise it is by page demand, and is slower.
-f - change first name/middle name/suffix only, not the last name.
     the last name is pulled from the regurgitation, or from maiden name if the person is a wife.
-w wifey mode, used to imply -f, but not any more.
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





struct searcher *last_first_name;
struct searcher *first_last_name;
struct searcher *first_name;
struct searcher *last_name;

struct searcher *first_middle_init;
struct searcher *smiddle_initial_fake;
struct searcher *smiddle_name;
struct searcher *last_name_suffix;
char special_from[10]; /* hack to allow us to change gender on regular people inserts */

int random_last_name_from_first_name(char *fname,
char *gender,char *line) 
{
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|%s|",fname,gender);
search(first_name,searchline,line);
int pos;
int size=fieldi(line,2);
if (size)
  pos =(random()>>2) % size+1;
else pos=0;  
sprintf(searchline2,"%s|%s|%010d|",fname,gender,pos);
search(first_last_name,searchline2,line);
return size;
}


int random_middle_initial_from_first_name(char *fname,
char *gender,char *line) 
{
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|%s|",fname,gender);
search(first_name,searchline,line);
int pos;
int size=fieldi(line,2);
if (size)
  pos =(random()>>2) % size+1;
else pos=0;  
sprintf(searchline2,"%s|%s|%010d|",gender,fname,pos);
search(first_middle_init,searchline2,line);
return size;
}


int random_first_name_from_last_name(char *lname,
char *gender,char *line) 
{
int size;
int pos;
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|%s|",lname,gender);
search(last_name,searchline,line);
size=fieldi(line,2);
if (size)
  pos =(random()>>2) % size+1;
else pos=0;  
sprintf(searchline2,"%s|%s|%010d|",lname,gender,pos);
search(last_first_name,searchline2,line);
return size;
}



int random_suffix_from_last_name(char *lname,
char *gender,char *line) 
{
char searchline[20000];
char searchline2[20000];
sprintf(searchline,"%s|%s|",lname,gender);
search(last_name,searchline,line);
int pos;
int size=fieldi(line,2);
if (size)
  pos =(random()>>2) % size+1;
else pos=0;  
sprintf(searchline2,"%s|%s|%010d|",gender,lname,pos);
search(last_name_suffix,searchline2,line);
return size;
}

#define LIMIT 4
int find_new_names_via_cross_pattern(char *fname, char *lname, 
   char *listed_gender,
   char *new_fname,
   char *new_lname, int first_name_only)
{
char searchline[20000];
char line[20000];
char a[20000];
char b[20000];
char c[20000];
char d[20000];
int size;
int fsize;
int lsize;
int limit;
int limit2;
limit=0;
long long range;
strcpy(new_fname,fname);
  do {
    limit2=0;
    range = 1;
    do {
      char *fname_gen;
      /* wife mode special - make the fname_gen to be M */
      if ((limit2==0)&&(wife_mode)) fname_gen="M"; 
        else fname_gen = special_from; /* hack, cough */
      fsize = random_last_name_from_first_name(new_fname,fname_gen,line);
      lsize = random_first_name_from_last_name(field(line,a,3),listed_gender,b);
      field(b,new_fname,3);
      range = range * lsize * fsize;
      if ((limit2==0)&&(range==1)) {/* we are singletonned */
        return(0); /* f n give up */
	}
      limit2++;
      } while ((range<1000)&&(limit2<LIMIT));
    if ((range<1000)&&(limit2 >=LIMIT)) {
      return(0);
      }
    limit++;
    } while (((strcmp(fname,new_fname)==0)||(strlen(new_fname)<=1))&&(limit<LIMIT)); /* name has to be filled in, different than original name */
if (((strcmp(fname,new_fname)==0)||(strlen(new_fname)<=1))&&(limit >= LIMIT)) { /* to many times to an empty or blank name.*/
  return(0);
  }
  
if (first_name_only==0) {
  limit=0;
  strcpy(new_lname,lname);
  range = 1;
  do {
    limit2=0;
    do {
      fsize = random_first_name_from_last_name(new_lname,listed_gender,line);
      lsize = random_last_name_from_first_name(field(line,a,3),listed_gender,b);
      field(b,new_lname,3);
      range = range * lsize * fsize;
      if ((limit2==0)&&(range==1)) {/* we are singletonned */
        return(0); /* f n give up */
	}
      limit2++;
      limit2++;
      } while ((range<1000)&&(limit2<LIMIT));
    if ((range<1000)&&(limit2>=LIMIT)) {
      return(0);
      }
    limit++;
    } while (((strcmp(new_lname,lname)==0)||(strlen(new_lname)<2))&&(limit<LIMIT));
  if (((strcmp(new_lname,lname)==0)||(strlen(new_lname)<2))&&(limit>=LIMIT)) { /* too many times matching the same new and old last name, or the new last name is blank */
    return(0);
    }
  } /* if we are even doing the last name */
return 1;
}




int first_name_only = 0;






int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
  if (strcmp(argv[i],"-p")==0) {
    populate=1;
    }
  else if (strcmp(argv[i],"-l")==0) {
    locked=1;
    }
  else if (strcmp(argv[i],"-f")==0) {
    first_name_only=1;
    }
  else if (strcmp(argv[i],"-w")==0) { /* wife mode */
    wife_mode=1;
    }
  else {
    srandom(atoi(argv[i]));
    }
  }
  

last_first_name = new_searcher("../common/last_first_name.txt",3,populate,locked);
first_last_name = new_searcher("../common/first_last_name.txt",3,populate,locked);
first_name = new_searcher("../common/fname.txt",2,populate,locked);
last_name = new_searcher("../common/lname.txt",2,populate,locked);
first_middle_init = new_searcher("../common/first_middle_init.txt",3,populate,locked);
smiddle_initial_fake = new_searcher("../common/minit_fake.txt",2,populate,locked);
smiddle_name = new_searcher("../common/mname.txt",3,populate,locked);
last_name_suffix = new_searcher("../common/last_name_suffix.txt",3,populate,locked);
return 0;
}





int main (int argc, char *argv[]) {
init(argc,argv);
char buf[20000];
char phase1[20000];
char phase2[20000];
char phase3[20000];
char oldid[20000];
char new_fname[20000];
char new_lname[20000];
char fname[20000];
char lname[20000];
char middle_init[20000];
char middle_name[20000];
char idx[20000];
char listed_from[10];
char listed_gender[10];
while (gets(buf)) {

  fieldspan(buf,phase2,6,24,1);
  fieldspan(buf,phase3,26,30,0);
  field(buf,oldid,31);
  field(buf,idx,1);
  field(buf,lname,2);
  field(buf,fname,3);
  field(buf,middle_init,4);
  field(buf,middle_name,5);
  if (middle_name[0]) {
    middle_init[0] = middle_name[0];
    middle_init[1]='\0';
    }
  field(buf,listed_gender,25);
  
  /* set special_from to the gender of the original person we are deriving from
      For FF or MM, it is the same
      but in many cases,  we "rib" off of the male
      So the gender will be FM
      And this changes how we find the first name.
      */
  if (listed_gender[1] != '\0') {
    strcpy(special_from,listed_gender+1);
    listed_gender[1] = '\0';
    }
  else {
    strcpy(special_from,listed_gender);
    }
    
  sprintf(phase1,"%s|%s|%s|%s|%s",idx,lname,fname,middle_init,middle_name);
  if (first_name_only) {
    /* get maiden name or last name from before */
    field(buf,new_lname,38);
    if (new_lname[0]=='\0') {
      field(buf,new_lname,33);
      }
    }

  if (
    find_new_names_via_cross_pattern(fname,lname,listed_gender,
        new_fname,new_lname,first_name_only)) { /* can find a new name */
    char new_middle_init[20000];
    char new_middle_name[20000];
    char dummy_fname[20000];
    char dummy_lname[20000];
    char new_suffix[20000];
    char searchline[20000];
    char line[20000];
    int pos;
    int limit=0;
    do {
      random_first_name_from_last_name(lname,listed_gender,line);
      field(line,dummy_fname,3);
      random_middle_initial_from_first_name(dummy_fname,
       listed_gender,line);
       field(line,new_middle_init,3);
      
      if (new_middle_init[0]) { /* if we have initials */
        /* Well, we could use the middle name from the first name,  but middle names are crappy in our data set 
	   so instead, we will use the first name.  And I don't care what the initial was, I just want a name that is group-wise relevant
	   So we will get a new last name/first name deal */
	
	
	char *fname_gen;
	char a[20000];
	char b[20000];
        if (wife_mode) fname_gen="M"; 
        else fname_gen = special_from; /* hack, cough */
        random_last_name_from_first_name(fname,fname_gen,line);
        random_first_name_from_last_name(field(line,a,3),listed_gender,b);
        field(b,new_middle_name,3);
        if (new_middle_name[0]) {
          new_middle_init[0] = new_middle_name[0];  
	  new_middle_init[1] = '\0';
 	  }
        }
      else new_middle_name[0]='\0';
      limit++;
      } while ( (limit<=LIMIT)&& (
                ((new_middle_init[0]!='\0')&&(strlen(new_middle_name)<=1))||
                ((new_middle_name[0]!=0) && (strcmp(new_middle_name,middle_name)==0))||
		(middle_init[0] && (new_middle_init[0]==middle_init[0])) ||
		((new_middle_init[0]!='\0') && (strcmp(new_fname,new_middle_name)==0)) ||
		((new_middle_init[0]!='\0') && (strcmp(fname,new_middle_name)==0)))); /* Make sure the middle name is found, and different than the original 
		                                                                             And it is different than the first name old or new */
    if (limit>LIMIT) goto fuckit;
    /* suffix */
    random_last_name_from_first_name(fname,special_from,line);
    field(line,dummy_lname,3);
    random_suffix_from_last_name(dummy_lname,listed_gender,line);
    field(line,new_suffix,3);

    printf("|%s|%s%s%s|%s|%s|%s|%s|%s|%s|%s||\n",phase1,phase2,
      listed_gender,special_from,phase3,oldid,
      new_fname,new_lname,
       new_middle_init,new_middle_name,new_suffix);
    }
  else { /* cannot find a nee name */
fuckit:
    fprintf(stderr,"|%s|%s%s%s|%s|%s|||s|\n",phase1,phase2,listed_gender,
        special_from,phase3,
    oldid);
    }
  }
return(0);
}


