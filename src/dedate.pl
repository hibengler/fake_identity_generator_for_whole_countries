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


while (<>) {
   chomp($_);
   my ($id,$port,$ser,$date,$ip,$file,$referer) = split(/\t/);
   my ($sec,$min,$hour,$day,$month,$year) = (localtime($date))[0,1,2,3,4,5];
   $year += 1900;
   $month += 1;
   $newdate = sprintf('%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d',$year,$month,$day,$hour,$min,$sec);
   if (substr($id,0,8) ne "qqqqqqqq") {
     print "$newdate|$id|$port|$ser|$ip|$file|$referer\n";
# original:     print "$id|$port|$ser|$newdate|$ip|$file|$referer\n";
     }
   }
