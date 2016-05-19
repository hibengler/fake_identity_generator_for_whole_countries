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
system: build
	@echo the addresses are unique by zipcode and address! YEAH
	@echo we tested this,  we do not need to go any further.  You can try
	@echo on nada, it takes 25 minute: make -j 2
	@echo so instead, we are going to make l001.txt, 
	@echo and l002.txt
	@echo and l003.txt

	
build: ../common/l002_error.txt ../common/l003.txt
	
../common/l003.txt: ../common/l003_beta_names_mixed.txt
	fix_fname_lname <../common/l003_beta_names_mixed.txt >../common/j92.txt
	mv ../common/j92.txt ../common/l003.txt

# ../common/l003.txt: l003_pre_ac.txt acs_per_zip.txt acs_by_zip.txt acs_per_street.txt acs_by_street.txt random_seed
../common/l003_beta_names_mixed.txt: l003_pre_ac.txt acs_per_zip.txt acs_by_zip.txt random_seed
	@echo was going to randomize this, but we do that at the end product anyways - so there is no need to do anything
	@echo and we can leave the numbers consistent
	time make_ac <l003_pre_ac.txt -p -l >../common/hy.txt `cat random_seed`
	mv ../common/hy.txt ../common/l003_beta_names_mixed.txt


acs_per_state.txt: 002_has_phone.txt
	time fielduc <002_has_phone.txt -s 10000000 15 >o7.txt
	mv o7.txt acs_per_state.txt

acs_by_state.txt: 002_has_phone.txt
	time fielduc  <002_has_phone.txt -s 10000000 -m1 15 17	 >o8.txt
	mv o8.txt acs_by_state.txt

acs_per_zip.txt: 002_has_phone.txt
	time fielduc <002_has_phone.txt -s 10000000 16 >o1.txt
	mv o1.txt acs_per_zip.txt

acs_by_zip.txt: 002_has_phone.txt
	time fielduc  <002_has_phone.txt -s 10000000 -m1 16 17	 >o2.txt
	mv o2.txt acs_by_zip.txt

acs_per_street.txt: 002_has_phone.txt
	time fielduc <002_has_phone.txt -s 10000000 16 9 30 10 11 31  >o3.txt
	mv o3.txt acs_per_street.txt

acs_by_street.txt: 002_has_phone.txt
	time fielduc <002_has_phone.txt -m6 -s 10000000 16 9 30 10 11 31   17 >o4.txt
	mv o4.txt acs_by_street.txt

002_has_phone.txt: ../common/l002.txt
	is_it_filled_in 17 <../common/l002.txt >o6.txt 2>/dev/null
	mv o6.txt 002_has_phone.txt


l003_pre_ac.txt: dedup_id.txt
	@echo l003.txt is just like l002.txt
	@echo but we are randomizing the id numbers
	match -p -l  dedup_id.txt 2 <l002id.txt >lok.txt 2>../common/lbad.txt
	mv lok.txt l003_pre_ac.txt
	mv ../common/lbad.txt ../common/l003_duplicates.txt

dedup_id.txt: name_addr_id.txt l002id.txt
	find_duplicate_records <name_addr_id.txt 2>/dev/null | field 16 >a1.txt
	time fsort 3000000000 1 4 <a1.txt >dd.txt
	mv dd.txt dedup_id.txt
	
name_addr_id.txt: l002id.txt
	@echo figure out name_addr_id.txt
	time fsort 3000000000 3 4 5 6 20   7 8 9 10 11 12 13 14 15 16  2 <l002id.txt >r1.txt
	mv r1.txt name_addr_id.txt

l002id.txt:	../common/l002.txt
	set_id <../common/l002.txt  >l23.txt
	mv l23.txt l002id.txt

testsystem: house_city.txt house_nocity.txt
	time merge_house_different_city house_city.txt house_nocity.txt | tee house_fix.tx
	

house_city.txt:	../common/l002.txt
	@echo house
	export TMP=$(TMP2); time fielduc 5000000 -s 16 7 8 9 10 11 12 13    14 15  <../common/l002.txt >z.txt
	mv z.txt house_city.txt

house_nocity.txt: ../common/l002.txt
	@echo house_nocity
	time fielduc 5000000 -s 16 7 8 9 10 11 12 13   <../common/l002.txt >y.txt
	mv y.txt house_nocity.txt




../common/l001.txt:	../common/ukraw.tab
	@echo this is the big one
	@echo we parse and expand the leads into separate fields
	@echo and standardize on case
	bash ./snob.sh && mv ../common/x.txt ../common/l001.txt

../common/l002.txt: ../common/l001.txt
	@echo filter out errors
	time grep -v ^error <../common/l001.txt >../common/y.txt
	mv ../common/y.txt ../common/l002.txt

../common/l002_error.txt: ../common/l001.txt
	@echo filter out errors
	time grep ^error <../common/l001.txt >../common/e.txt
	mv ../common/e.txt ../common/l002_error.txt

random_seed:
	generate_random_seed >random_seed
	
