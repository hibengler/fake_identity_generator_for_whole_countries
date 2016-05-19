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

system:	../out/n001.txt minternal_to_external_$(SET)_$(OWN) 


../out/n001.txt: ../common/m001.txt internal_to_external_m.txt
	time give_new_set_id_number_watermark -p -l `cat random_seed` \
	  <../common/m001.txt 2>k20.txt | \
	  fsort 7000000000 >../out/k19.txt 
	fsort 12000000000 <k20.txt >k20b.txt
	rm k20.txt
	mv k20b.txt initial_trail_$(SET)_$(OWN).txt
	mv ../out/k19.txt ../out/n001.txt
	

minternal_to_external_$(SET)_$(OWN): internal_to_external_m.txt ../out/n001.txt
	set_field "$(SET)|$(OWN)" <internal_to_external_m.txt >j19.txt
	set_field "$(SET)|$(OWN)" <external_to_internal_m.txt | field 3 4 1 2 >j20.txt
	mv j19.txt minternal_to_external_$(SET)_$(OWN)
	mv j20.txt mexternal_to_internal_$(SET)_$(OWN)

internal_to_external_m.txt: ../common/m001.txt random_seed
	field 11 <../common/m001.txt | time randomize `cat random_seed` | add_id | tee i19.txt | fsort 1600000000 2 1 >i20.txt
	mv i19.txt internal_to_external_m.txt
	mv i20.txt external_to_internal_m.txt

random_seed:
	generate_random_seed >random_seed
	
