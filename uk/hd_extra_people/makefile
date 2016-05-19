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

system:../common/l006.txt
	@echo you can do a make -j 2 here for faster speeds
	

../common/l006.txt: named_wives.txt named_person.txt
	cp ../common/l005.txt ../common/l16.txt
	cat <named_wives.txt >>../common/l16.txt
	cat <named_person.txt >>../common/l16.txt
#	time field  1 2 33 32 34 35 7 8 9 10 11 12 13 14 15 16 17 18 99 \
#	        20 21 22 23 24 25 \
#	  26 27 28 29 30 31 37 38 <named_wives.txt >>../common/ll6.txt
#	time field  1 2 33 32 34 35 7 8 9 10 11 12 13 14 15 16 17 18 99 \
#	        20 21 22 23 24 25 \
#	  26 27 28 29 30 31 37 38 <named_person.txt >>../common/ll6.txt
	  mv ../common/l16.txt ../common/l006.txt


# we wait for named_wives because the temp fiels are being reused between the roudnup
# androundupp
named_person.txt: unnamed_person.txt named_wives.txt
	@echo named_person.txt - this is a big one
	echo "0" >prun
	cat </dev/null >good_name.txt
	cp unnamed_person.txt redo_lname.txt
	cat </dev/null >redo_fname.txt
	bash roundupp.sh 
	mv good_name.txt named_person.txt
	

unnamed_person.txt: person.txt person_by_house.txt
	@echo unnamed_person.txt 
	 elaborate_person person.txt person_by_house.txt >b3.txt 2>b3a.txt
	mv b3.txt unnamed_person.txt
	mv b3a.txt extra_persons.txt

person.txt: unnamed_wives.txt gender_zip_b.txt house.txt zip.txt
	@echo person.txt  make more men and women
	#echo we ignore the extra girls
	 make_extra_people_in_houses <gender_zip_b.txt -p -l >r1.txt
	echo add extra_girls below to the cat if you want them, but they are small and messy
	time cat r1.txt | fsort 7000000000 >r1a.txt
	mv r1a.txt person.txt
	rm r1.txt

named_wives.txt: unnamed_wives.txt new_last_name.txt wife_husband.txt
	@echo named_wives.txt
	echo "0" >run
	cp unnamed_wives.txt redo_lname.txt
	cat </dev/null >redo_fname.txt
	cat </dev/null >good_name.txt
	bash roundup.sh 
	mv good_name.txt named_wives.txt
	

new_last_name.txt: unnamed_wives.txt
	fsort  7000000000 32 34 99 <unnamed_wives.txt >f3e.txt
	mv f3e.txt new_last_name.txt

wife_husband.txt: unnamed_wives.txt
	fsort 5000000000  2 32 <unnamed_wives.txt >wh21.txt
	mv wh21.txt wife_husband.txt


unnamed_wives.txt: wives.txt person_by_house.txt
	@echo unnamed_wives.txt main
	 elaborate_wives wives.txt person_by_house.txt >b3.txt 2>b3a.txt
	mv b3.txt unnamed_wives.txt
	mv b3a.txt extra_girls.txt



wives.txt: gender_zip_a.txt mhouse.txt mzip.txt
	@echo wives.txt main
	@echo make wive\'s for the men
	time make_wives <gender_zip_a.txt -p -l >b1.txt
	time fsort 7000000000 <b1.txt >b1a.txt
	mv b1a.txt wives.txt
	rm b1.txt



house.txt: house1.txt
	@echo house.txt main
	@echo compute house index on zipcode - 1 per house
	fielduc <house1.txt -m1 -s 20000000 1 2  >k6.txt
	mv k6.txt house.txt

zip.txt: house1.txt
	@echo zip.txt main
	@echo compute zip count - 1 per house
	 fielduc -s 1 <house1.txt >k3.txt
	mv k3.txt zip.txt


house1.txt: ../common/l005.txt
	@echo house1.txt main
	@echo compute house count - 1 per house
	fielduc <../common/l005.txt -s 20000000 16 7 >k1.txt
	mv k1.txt house1.txt

gender_zip_b.txt: gender_zip.txt gender_country_b.txt
	@echo gender_zip_b.txt main
	@echo distribute from country to zip
	distribute gender_country_b.txt gender_zip.txt >a4.txt
	@echo sort by zip code so we can eliminate duplicates for peoples houses without
	@echo running out of memory
	fsort <a4.txt >a4b.txt 2 1 3 4
	mv a4b.txt gender_zip_b.txt
	rm a4.txt

# this was 10 percent more.  Now it is 5 percent more - because there are too many uncle eds in some cases
# it could be from this, or something in he
gender_country_b.txt: gender_country.txt
	@echo gender_country_b.txt main
	echo @add 10 % more people, and make more women
	awk -F \| <gender_country.txt '/F/{ print $$1 "|" int($$2*2.0) "|" \
	int($$2*2.0* 1.05) } /M/{ print $$1 "|" $$2 "|" int($$2 * 1.05) }' \
	 >a2b.txt
	 mv a2b.txt gender_country_b.txt

gender_zip_a.txt: gender_zip.txt gender_country_a.txt
	@echo gender_zip.txt main
	@echo distribute from country to zip
	distribute gender_country_a.txt gender_zip.txt >a4.txt
	mv a4.txt gender_zip_a.txt

gender_country_a.txt: gender_country.txt
	@echo gender_county_a.txt main
	echo @add 25 % more people, and make more women
	awk -F \| <gender_country.txt '/F/{ print $$1 "|" $$2 "|" \
	int($$2*2.0) } /M/{ print $$1 "|" $$2 "|" int($$2) }' \
	 >a2.txt
	 mv a2.txt gender_country_a.txt

person_by_house.txt: ../common/l005.txt
	time fsort <../common/l005.txt  \
	3000000000 16 7 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 \
	 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 >b2.txt
	mv b2.txt person_by_house.txt

mhouse.txt: mhouse1.txt
	@echo mhouse1.txt main
	@echo compute males only house index
	fielduc <mhouse1.txt -m1 -s 20000000 1 2  >t6.txt
	mv t6.txt mhouse.txt

mzip.txt: mhouse1.txt
	@echo mzip.txt 
	@echo compute zip count - males only.  We are going to marry people!
	 fielduc -s 1 <mhouse1.txt >t3.txt
	mv t3.txt mzip.txt

mhouse1.txt: ../common/l005.txt
	@echo mhouse1.txt main
	@echo compute gender count per house males only
	time fsort 7000000000 16 7 26  <../common/l005.txt | \
	  filter_eligable_bachelors >y3.txt
	mv y3.txt mhouse1.txt


gender_zip.txt: ../common/l005.txt
	@echo gender_zip.txt main
	@echo compute gender count per zip
	time fielduc -s 26 16 <../common/l005.txt >t4.txt
	mv t4.txt gender_zip.txt

gender_country.txt: ../common/l005.txt
	@echo gender_country.txt main
	@echo compute gender count per country
	time fielduc -s 26 <../common/l005.txt >t1.txt 
	mv t1.txt gender_country.txt
			



	

random_seed:
	generate_random_seed >random_seed
	
	
