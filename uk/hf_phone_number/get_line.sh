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




geturl1 "http://phones.whitepages.com/"$1 e1.txt
table_extract e1.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=2" e2.txt
table_extract e2.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=3" e3.txt
table_extract e3.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=4" e4.txt
table_extract e4.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=5" e5.txt
table_extract e5.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=6" e6.txt
table_extract e6.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=7" e7.txt
table_extract e7.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=8" e8.txt
table_extract e8.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=9" e9.txt
table_extract e9.txt 1 | snobol4 -b find_Type.sno 
geturl1 "http://phones.whitepages.com/"$1"?page=10" e10.txt
table_extract e10.txt 1 | snobol4 -b find_Type.sno 
