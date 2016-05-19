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


touch ../common/exlfza.txt
#time cat ../common/exlfza.txt ../common/l007.txt |
# Get the regular name and the maiden name
field 34 33 16 7 39 <../common/l007.txt >exlim1.txt
field 1 2 3 4 <exlim1.txt >exlim2.txt
is_it_filled_in 2>/dev/null 5 <exlim1.txt | field 5 2 3 4 >>exlim2.txt


time fsort <exlim2.txt 27000000000 |
  find_duplicate_records 2>/dev/null 4 >exlfzanew.txt
mv exlfzanew.txt exlfza_$SET.txt

