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



../common/l010.txt:	bystate.txt
	time make_dl <bystate.txt >../common/m10.txt `cat random_seed` 2>errors.txt
	mv ../common/m10.txt ../common/l010.txt

bystate.txt:	../common/l009.txt random_seed
	time make_dl_sort_code <../common/l009.txt `cat random_seed` | fsort 26000000000 >bystatem.txt
	mv bystatem.txt bystate.txt


random_seed:
	generate_random_seed >random_seed
	
