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

../common/l013.txt:	../common/internal_id_to_build_id.txt all_spouse.txt
	time give_new_id_number -p -l <../common/l012.txt | fsort 2000000000 >../common/m13.txt
	mv ../common/m13.txt ../common/l013.txt



../common/internal_id_to_build_id.txt:	 ../common/l012.txt random_seed
	@echo building a map from internal to external and vise versa
	@echo this maxes out an 8g machine by the way
	field 2 <../common/l012.txt  | time randomize | add_id | tee ../common/i19.txt | fsort 1600000000 2 1 >../common/i20.txt
	mv ../common/i19.txt ../common/internal_id_to_build_id.txt
	mv ../common/i20.txt ../common/build_id_to_internal_id.txt



all_spouse.txt: ../hg_nino/all_wife_husband.txt
	cp  ../hg_nino/all_wife_husband.txt aw.txt
	field <../hg_nino/all_wife_husband.txt 2 1 >>aw.txt
	fsort 1600000000 <aw.txt >as.txt
	rm aw.txt
	mv as.txt all_spouse.txt


random_seed:
	generate_random_seed >random_seed
	
	
	
