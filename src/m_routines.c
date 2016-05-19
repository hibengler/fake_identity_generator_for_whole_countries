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
#include <string.h>
#include "util.h"

   

char *full_name(char *b,char *full_name) {
char last_name[20000];
char first_name[20000];
char middle_init[20000];
char suffix[20000];
char *comma;
comma="";
full_name[0]='\0';
field(b,last_name,11);
field(b,first_name,12);
field(b,middle_init,13);
field(b,suffix,28);
if (*last_name) {
  strcat(full_name,comma);
  strcat(full_name,last_name);
  comma = ", ";
  }
if (*first_name) {
  strcat(full_name,comma);
  strcat(full_name,first_name);
  comma = " ";
  }
if (*middle_init) {
  strcat(full_name,comma);
  strcat(full_name,middle_init);
  comma = " ";
  } 
if (*suffix) {
  strcat(full_name,comma);
  strcat(full_name,suffix);
  comma = " ";
  } 
return(full_name);
}





char *street_name(char *buf,char *street_name)
{
    char thenumber[2000];
    char thestreet_direction[2000];
    char thestreet_name[2000];
    char thestreet_type[2000];
    char thestreet_direction2[2000];
    char thespanish_street_type[2000];
    char thesubdivision_type[2000];
    char thesubdivision_number[2000];

      
    field(buf,thenumber,16);
    field(buf,thestreet_direction,17);
    field(buf,thestreet_name,18);
    field(buf,thestreet_type,19);
    field(buf,thestreet_direction2,38);
    field(buf,thespanish_street_type,37);
    field(buf,thesubdivision_type,20);
    field(buf,thesubdivision_number,21);
      
      
    /* Ok - rebuild the damn full address with the watermark - this is mirroed in name.sno back at section ha */
    street_name[0]='\0';
    char *e = street_name;
    char *comma;;
    comma="";
    if (thestreet_direction[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction);
	e += strlen(e);
	comma = " ";
        }
    if (thespanish_street_type[0]) {
        sprintf(e,"%s%s",comma,thespanish_street_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_name[0]) {
        sprintf(e,"%s%s",comma,thestreet_name);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_type[0]) {
        sprintf(e,"%s%s",comma,thestreet_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_direction2[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction2);
        e += strlen(e);
	comma = " ";
	}
return street_name;
}


char *full_address(char *buf,char *full_address)
{
    char thenumber[2000];
    char thestreet_direction[2000];
    char thestreet_name[2000];
    char thestreet_type[2000];
    char thestreet_direction2[2000];
    char thespanish_street_type[2000];
    char thesubdivision_type[2000];
    char thesubdivision_number[2000];

      
    field(buf,thenumber,16);
    field(buf,thestreet_direction,17);
    field(buf,thestreet_name,18);
    field(buf,thestreet_type,19);
    field(buf,thestreet_direction2,38);
    field(buf,thespanish_street_type,37);
    field(buf,thesubdivision_type,20);
    field(buf,thesubdivision_number,21);
      
      
    /* Ok - rebuild the damn full address with the watermark - this is mirroed in name.sno back at section ha */
    full_address[0]='\0';
    char *e = full_address;
    char *comma;;
    comma="";
    if (thenumber[0]) {
        sprintf(e,"%s%s",comma,thenumber);
	e += strlen(e);
	comma = " ";
	}
    if (thestreet_direction[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction);
	e += strlen(e);
	comma = " ";
        }
    if (thespanish_street_type[0]) {
        sprintf(e,"%s%s",comma,thespanish_street_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_name[0]) {
        sprintf(e,"%s%s",comma,thestreet_name);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_type[0]) {
        sprintf(e,"%s%s",comma,thestreet_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_direction2[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction2);
        e += strlen(e);
	comma = " ";
	}
    if (thesubdivision_type[0]) {
        sprintf(e,"%s%s",comma,thesubdivision_type);
        e += strlen(e);
	comma = " ";
	}
    if (thesubdivision_number[0]) {
        sprintf(e,"%s%s",comma,thesubdivision_number);
        e += strlen(e);
	comma = " ";
	}
return full_address;
}




char *full_address_csz(char *buf,char *full_address_csz)
{
full_address(buf,full_address_csz);
char *e;
e = full_address_csz + strlen(full_address_csz);
  char city[20000];
  char state[20000];
  char zip[20000];
  field(buf,city,22);
  field(buf,state,23);
  field(buf,zip,24);
sprintf(e," %s, %s %s",city,state,zip);
return full_address_csz;
}


char *full_address_csz4(char *buf,char *full_address_csz4, char *z4_separator /* - or " " for us or uk */)
{
full_address(buf,full_address_csz4);
char *e;
e = full_address_csz4 + strlen(full_address_csz4);
  char city[20000];
  char state[20000];
  char zip[20000];
  char zip4[20000];
  field(buf,city,22);
  field(buf,state,23);
  field(buf,zip,24);
  field(buf,zip4,29);
  if (zip4[0]) {
    sprintf(e," %s, %s %s%s%s",city,state,zip,z4_separator,zip4);
    }
  else {
    sprintf(e," %s, %s %s",city,state,zip);
    }
return full_address_csz;
}


char *phone_first(char *buf,char *phone_first,int lang_flag) 
{
char phone_ac[20000];
char phone_prefix[20000];
char phone_rest[20000];
field(buf,phone_ac,25);
field(buf,phone_prefix,26);
field(buf,phone_rest,27);
if (*phone_ac) {
  if (lang_flag) { /* UK language */
    sprintf(phone_first,"%s.%s",phone_ac,phone_rest);
    }
  else { /* US language */
    sprintf(phone_first,"(%s)%s-%s",phone_ac,phone_prefix,phone_rest);
    }
  }
else
  *phone_first = '\0';
return phone_first;
}



char *phone_second(char *buf,char *phone_second,int lang_flag) 
{
char phone_ac[20000];
char phone_prefix[20000];
char phone_rest[20000];
field(buf,phone_ac,39);
field(buf,phone_prefix,40);
field(buf,phone_rest,41);
if (*phone_ac) {
  if (lang_flag) { /* UK language */
    sprintf(phone_second,"%s.%s",phone_ac,phone_rest);
    }
  else { /* US language */
    sprintf(phone_second,"(%s)%s-%s",phone_ac,phone_prefix,phone_rest);
    }
  }
else
  *phone_second = '\0';
return phone_second;
}
