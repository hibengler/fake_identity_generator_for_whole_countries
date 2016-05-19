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


system:	../common/l008.txt





../common/l008.txt: ../common/l007.txt numbers_per_street.txt \
	acs_per_zip.txt acs_by_zip.txt fulllist.txt \
	phone_fname.txt phone_lname.txt phone_numbers.txt
	@echo l008.txt
	make_phone_numbers_uk <../common/l007.txt -p -l >../common/e4.txt 2>rac.txt
	mv ../common/e4.txt ../common/l008.txt
	mv rac.txt randomized_area_codes.txt
	



numbers_per_street.txt:	004_has_phone.txt
	@echo numbers per street.txt
	@echo make street.txt - count of phone numbers per street and area code as well
	time fielduc -s  20000000 16 9 30 10 11 31 17 >a1.txt <004_has_phone.txt
	mv a1.txt numbers_per_street.txt
	@echo done making street count of phone numbers




cell_prefixes.txt: prefixes.txt
	@echo cell_prefixes.txt
	field 4 1 2 <prefixes.txt | grep "^Cell" | fieldu 2 3 >o.txt
	mv o.txt cell_prefixes.txt



phone_numbers.txt: ../common/l007.txt
	cat ../common/l004.txt ../common/l003_duplicates.txt | fielduc 40000000 17 18 19 >po.txt
	mv po.txt phone_numbers.txt


oldprefixes.txt : phone_numbers.txt phone_prefix_state_code.txt
	cat  phone_numbers.txt phone_prefix_state_code.txt | fielduc -s 1 >l.txt
	bash get_phone_line_type.sh <l.txt >m.txt
	@rm l.txt
	mv m.txt prefixes.txt
			
prefixes.txt: prefixes.inp
	cp prefixes.inp prefixes.txt		
	

004_has_phone.txt:	../common/l004.txt
	@echo make 004_has_phone.txt for all people who have a phone
	is_it_filled_in <../common/l004.txt 17 2>/dev/null >a3.txt
	mv a3.txt 004_has_phone.txt
	@echo done 004


acs_per_zip.txt: acs_zip.txt
	time fielduc <acs_zip.txt -s 10000000 1 >o1.txt
	mv o1.txt acs_per_zip.txt

acs_by_zip.txt: acs_zip.txt
	time fielduc <acs_zip.txt -s 10000000 -m1 1 2	 >o2.txt
	mv o2.txt acs_by_zip.txt

acs_zip.txt: ../ha_clean_city/002_has_phone.txt
	time field 16 17 <../ha_clean_city/002_has_phone.txt | grep -v "|7" | grep -v "|8" >a1.txt
	grep <a1.txt  -v "|6" | grep -v "|3" | grep -v "|4" >a2.txt
	@rm a1.txt
#	echo "AAAAAAA|231213" >>a2.txt
	mv a2.txt acs_zip.txt


fulllist.txt: calvary/fulllist.txt
	cp calvary/fulllist.txt .



phone_fname.txt: ../common/l002.txt
	fielduc <../common/l002.txt 40000000 -s 17 19 4 >p4.txt
	awk -F '|' <p4.txt '{ print $$1 $$2 "|" $$3 "|" }' >p4b.txt
	mv p4b.txt phone_fname.txt

phone_lname.txt: ../common/l002.txt
	fielduc <../common/l002.txt 40000000 -s 17 19 4 >p5.txt
	awk -F '|' <p5.txt '{ print $$1 $$2 "|" $$3 "|" }' >p5b.txt
	mv p5b.txt phone_lname.txt
