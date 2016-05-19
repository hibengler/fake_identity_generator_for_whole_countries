#
# Fake Identity Generator
# Copyright (C) 2011-2016 Hibbard M. Engler (Bitcoin address 1ERDHsxtekdh5FAsxdb92PBFK7nnuwMkbp for gifts)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
{
# address, city,state variants
awk -F '|' <../out/n001_city_state.txt '
 { print $1 "|" $6 "|" $8;
   print $1 "|" $2 ", " $3 " " $6 "|" $8;
   print $1 "|" $3 ", " $2 " " $6 "|" $8;
   }' | everything_format
# name - all variants
awk -F '|' <../out/n001_last_first_middle.txt '{ print $1 "|" $2,$3 "|" $5 "|" $7; print $1 "|" $2 ", " $3 "|" $5 "|" $7 ;
                                                 if ($5 ne "") { 
						    print $1 "|" $3,$5,$2 "|" $7; 
						    $5 = "," $5;						    
						    }
						 print $1 "|" $3,$2 "|" $5 "|" $7}' | everything_format
awk -F '|'  <../out/n001_zip_street.txt '{ 
print $1 "|" $2,$8 "|" $10; 
print $1 "|" $2,$3,$8 "|" $10; 
print $1 "|" $2 $3,$8 "|" $10;
}' | everything_format
awk -F '|'  <../out/n001_phone_area_code.txt '{ print $1 "|" $2 "." $4 "|" $7;
   print $1 "|0" $2 "." $4 "|" $7;
   print $1 "|" $2 $4 "|" $7;
   print $1 "|0" $2 $4 "|" $7;
     }'| everything_format 
awk -F '|'  <../out/n001_nino.txt '{
   print $1 "|" $2 "|" $3;
   print $1 "|" substr($2,1,2),substr($2,3,2),substr($2,5,2),substr($2,7,2),substr($2,9,1) "|" $3;
   }' | everything_format 
  awk <../out/n001_city_state.txt -F '|' '{
    print $1,$4;
    print $4,$1;
    }' | everything_format 
# MISSING    
#    street name full addreess city 
#    city street_name full addrtess
#    city street name full address
#    city full address
} | fsort -Q 21000000000  | add_id
