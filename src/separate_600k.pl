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



# used to separate the list inot 2700 k chunks.


$file = 0;
$count = 0;
$from = 0;
$fullcount = 0;
@in = ();

open(XF,">id" . $file . ".txt");

while (<>) {
  ($me,$spouse) = split(/\|/);
  $spouse =~ s/\n$//g;
  if ($in[$me]) {
    next;
    }
  $in[$me] = 1;
  print XF "$me\n";
  $count++;
  $fullcount++;
  if ($spouse) {
    $in[$spouse] = 1;
    print XF "$spouse\n";    
    $count++;
    $fullcount++;
    }
  if ($count >= 2700000) {
    close(XF);
    print "$file|$from|$fullcount\n";
    $file++;
    open(XF,">id" . $file . ".txt");
    $count = 0;
    $from = $fullcount;
    }
  }  
close(XF);
print "$file|$from|$fullcount\n";

