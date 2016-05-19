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
/* these routines extract information from a m format record in different ways
*/

char *full_name(char *b,char *full_name);
/* last, first middle */

char *street_name(char *buf,char *street_name);
/* name of the streew without the number or apt */

char *full_address(char *buf,char *full_address);
/* full name of the street - without the watermark! */

char *full_address_csz(char *buf,char *full_address_csz);
/* full name of the street city state zip without the watermark! */

char *full_address_csz4(char *buf,char *full_address_csz4, char *z4_separator /* - or " " for us or uk */);
/* full name of the street city state zip without the watermark and with the zip+4
This was added fopr UK which has a different postal code system than the US */

char *phone_first(char *buf,char *phone_first,int lang_flag);
char *phone_second(char *buf,char *phone_second,int lang_flag);
