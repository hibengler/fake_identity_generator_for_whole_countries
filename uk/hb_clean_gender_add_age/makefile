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
system:  ../common/l004.txt

../common/l004.txt: fname_gender.txt fname_only.txt ../common/l003.txt random_seed
	echo clean up gender and assign a new id
	time make_gender_from_first_name <../common/l003.txt >../common/yy.txt `cat random_seed`  -p -l -k
	mv ../common/yy.txt ../common/l004.txt

random_seed:
	generate_random_seed >random_seed
	

fname_gender.txt:	../common/us_fname_gender.txt
	@echo gender
	cp ../common/us_fname_gender.txt fname_gender.txt

fname_only.txt: ../common/us_fname_only.txt
	@echo fname
	cp ../common/us_fname_only.txt fname_only.txt

