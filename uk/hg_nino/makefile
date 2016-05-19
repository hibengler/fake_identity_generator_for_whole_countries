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




../common/l009.txt:  state_area.txt state_area_count.txt  \
	  birthdates.txt random_seed nuid_range_per_year.txt \
	 sorted_with_birthdates.txt
	  echo "if error do fielduc 40000000 1 <l009_error.txt >l009_error_summary.txt"
	time make_nuid_numbers -p -l <sorted_with_birthdates.txt \
	  >../common/m9.txt `cat random_seed` 2>l009_error.txt 
	mv ../common/m9.txt ../common/l009.txt
	
sorted_with_birthdates.txt: ../common/l008.txt random_seed  \
         birthdates.txt state_area.txt state_area_count.txt
	 echo "the uk does not need to be sorted, but the us does"
	 echo "However, sorting is important in the drivers license stage hi"
	 echo "So, we still do it "
	add_birthdate_birth_state -p -l -u <../common/l008.txt `cat random_seed` |  time fsort 12000000000 >sorted_with_birthdates.txt >s34.txt
	mv s34.txt sorted_with_birthdates.txt
		
birthdates.txt: birthdate1.txt random_seed
	make_birthdate2 -p -l <wives.txt >d1.txt `cat random_seed`
	cat birthdate1.txt d1.txt | fsort 7000000000 >d2.txt
	rm d1.txt
	mv d2.txt birthdates.txt

birthdate1.txt: all_wife_husband.txt ../common/l008.txt random_seed
	make_birthdate1 -p -l  <../common/l008.txt >c1.txt 2>c2.txt `cat random_seed`
	fsort <c1.txt >c1b.txt 7000000000
	mv c1b.txt birthdate1.txt
	mv c2.txt wives.txt
	rm c1.txt


all_wife_husband.txt: ../he_extra_houses_and_people/wife_husband.txt
	 cp ../he_extra_houses_and_people/wife_husband.txt wh1.txt
	 mv wh1.txt all_wife_husband.txt



nuid_range_per_year.txt: nino.inp
	 perl nino_range.pl <nino.inp | sort >l9.txt
	 mv l9.txt nuid_range_per_year.txt

	  

state_area.txt:  area_number_state.inp
	fielduc -s -m1 2 1  <area_number_state.inp >y2.txt
	mv y2.txt state_area.txt

state_area_count.txt: area_number_state.inp
	fielduc -s 2 <area_number_state.inp >y1.txt
	mv y1.txt state_area_count.txt
	





	
	


random_seed:   
	generate_random_seed >random_seed
	
	
	
