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



../common/l009.txt:  state_area.txt state_area_count.txt by_code.txt \
	by_date_fudged.txt ssdi_sample_cleaned.txt birthdates.txt random_seed \
	state_migration_count.txt state_migration.txt sorted_with_birthdates.txt
	time make_ssn_numbers -p -l <sorted_with_birthdates.txt >../common/m9.txt `cat random_seed`
	mv ../common/m9.txt ../common/l009.txt
	
sorted_with_birthdates.txt: birthdates.txt  ../common/l008.txt random_seed state_area.txt state_area_count.txt \
        by_date_fudged.txt ssdi_sample_cleaned.txt birthdates.txt \
	        state_migration_count.txt state_migration.txt
	add_birthdate_birth_state -p -l <../common/l008.txt  `cat random_seed` | \
		time fsort 4000000000 >sorted_with_birthdates.txt
		
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



state_migration_count.txt: state_clean.inp ssdi_sample_cleaned.txt area_number_state.inp
	deduct_state_migration <ssdi_sample_cleaned.txt | \
	  fielduc -s 2 > t1.txt
	  mv t1.txt state_migration_count.txt
	  
state_migration.txt: state_clean.inp ssdi_sample_cleaned.txt area_number_state.inp
	deduct_state_migration <ssdi_sample_cleaned.txt | \
	  fielduc -m1 2 1 > t2.txt
	  mv t2.txt state_migration.txt
	  

state_area.txt:  area_number_state.inp
	fielduc -s -m1 2 1  <area_number_state.inp >y2.txt
	mv y2.txt state_area.txt

state_area_count.txt: area_number_state.inp
	fielduc -s 2 <area_number_state.inp >y1.txt
	mv y1.txt state_area_count.txt
	


by_date_fudged.txt: by_date.txt
	grep -v '|-' by_date.txt | fsort 1 2 >a1.txt
	grep -v '|-' by_date.txt | fsort 1 3 >a2.txt
	perl merge.pl | field 1 2 4 >by_date_fudged.txt 


by_date.txt: ssdi_sample_cleaned.txt
	field <ssdi_sample_cleaned.txt 2 19 5 | fsort >by_date.txt

by_code.txt: ssdi_sample_cleaned.txt
	fsort 4000000000 <ssdi_sample_cleaned.txt 2 5 >by_code.txt

# this is a small sample.  We will be getting a bigger one from the ssdi
ssdi_sample_cleaned.txt:	ssdi_sample_smaller.txt ssdi_sample_bigger.txt
	cat ssdi_sample_smaller.txt  ssdi_sample_bigger_*.txt | fsort 26000000000 | field -u1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20  >llo.txt
	mv llo.txt ssdi_sample_cleaned.txt
	
ssdi_sample_smaller.txt:	../common/ssdi_sample.txt
	snobol4 -b ssdi_cleanup.sno <../common/ssdi_sample.txt >ssdi_sample_smaller.txt
	
../common/ssdi_sample.txt:	../common/ssdi_sample.txt.gz
	gunzip <../common/ssdi_sample.txt.gz >../common/t43.txt
	mv ../common/t43.txt ../common/ssdi_sample.txt

ssdi_sample_bigger.txt:	
	bash make_ssdi_sample_bigger.sh
	touch ssdi_sample_bigger.txt


random_seed:   
	generate_random_seed >random_seed
	
	
	
