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


system: ../common/l007.txt
	@echo -j 2 can help a little.



../common/l007.txt: named_households.txt
	@echo l007.txt main
	@echo put l007 together with l006, single people and husbands,  and the wives
	cp ../common/l006.txt ../common/l17.txt
	cat <named_households.txt >>../common/l17.txt
	mv ../common/l17.txt ../common/l007.txt
	@echo l007 is complete








named_households.txt: unnamed_households.txt husband_wife.txt
	@echo named_households.txt main
	@echo named  households include wives, husbands and single people
	@echo we have to figure out the maiden names after all
	@echo then we separate out the wives based on who was married before
	@echo then we filter the wives first name. 
	@echo anyways, lets run the first filters
	echo "0" >prun
	cp unnamed_households.txt redo_lname.txt
	cat </dev/null >redo_fname.txt
	cat </dev/null >good_name.txt
	bash roundup.sh
	@echo named_households.txt main continued
	mv good_name.txt named_households.txt



husband_wife.txt: unnamed_households.txt old_husband_wife.txt
	@echo not here yet
	analyze_new_house_spouse <husband_wife_analysis.txt >lo1.txt 2>lo2.txt
	cat old_husband_wife.txt lo1.txt | fsort 7000000000 >lo3.txt
	cat old_wife_husband.txt lo2.txt | fsort 7000000000 >lo4.txt
	mv lo3.txt husband_wife.txt
	mv lo4.txt wife_husband.txt
	

unnamed_households.txt:	households.txt top_level_random_seed old_husband_wife.txt
	@echo unnamed_households.txt main
	 elaborate_household -p -l `cat top_level_random_seed` <../common/l006.txt >b3.txt 2>b3a.txt
	mv b3.txt unnamed_households.txt
	# used_old_addresses is for debugging if the counts are off
	fsort 9000000000 <b3a.txt >b3b.txt
	rm b3a.txt
	mv b3b.txt husband_wife_analysis.txt



old_husband_wife.txt: address_lname_gender_id.txt
	@echo husband_wife.txt main
	@echo get the current husband wife teams so we can marry our new households like them
	 ../src/find_spouse <address_lname_gender_id.txt >f7.txt 2>f72.txt
	fsort <f7.txt >old_husband_wife.txt
	fsort <f72.txt >old_wife_husband.txt

address_lname_gender_id.txt: ../common/l006.txt
	@echo address_lname_gender_id.txt main
	@echo find the address gender so we can identify and transfer mates
	time clip_to_1_char 26 <../common/l006.txt | fielduc 40000000 -s 16 7 34 26 2  >f44.txt
	mv f44.txt address_lname_gender_id.txt


households.txt: newhouse.txt newhouse_zipcount.txt newhouse2.txt newhouse_zipcount2.txt \
	house_index.txt street.txt zip_a.txt top_level_random_seed
	@echo households.txt main
	generate_random_seed >top_level_random_seed_households
	  make_extra_houses -p -l <zip_a.txt >hh.txt `cat top_level_random_seed_households` \
	      2>households_stats.txt
	 fsort 5000000000 <hh.txt >hh2.txt
	 mv hh2.txt households.txt
	 rm hh.txt

house_index.txt: ../common/l006.txt
	@echo house_index.txt main
	time fielduc 20000000 -m6  16 9 30 10 11 31 8 12 13  >hi.txt <../common/l006.txt
	mv hi.txt house_index.txt


newhouse_zipcount.txt:	newhouse.txt 
	@echo newhouse_zipcount.txt main
	@echo newhouse_zipcount.txt
	time fielduc 50000000 -s 1 <newhouse.txt >nz1.txt
	mv nz1.txt newhouse_zipcount.txt

newhouse_zipcount2.txt:	newhouse2.txt 
	@echo newhouse_zipcount2.txt main
	@echo newhouse_zipcount2.txt
	time fielduc 50000000 -s 1 <newhouse2.txt >nz4.txt
	mv nz4.txt newhouse_zipcount2.txt

newhouse.txt:	house.txt 
	@echo newhouse.txt main
	#time snobol4 -P 10M -S 10M -d 10M -b filter.sno <house.txt 2>e2.txt >e1.txt
	time make_street <house.txt >e1.txt
	mv e1.txt newhouse.txt

newhouse2.txt:	house.txt 
	@echo newhouse2.txt main
	@echo "newhouse2 (Added 2 blocks to every street )"
	#time snobol4 -P 10M -S 10M -d 10M -b filter.sno <house.txt 2>e2w.txt >e1w.txt
	time make_street2 <house.txt >e4w.txt
	mv e4w.txt newhouse2.txt

house.txt:	 ../common/l006.txt
	@echo house.txt main
	fielduc -s 20000000 16 9 30 10 11 31 8 12 13 14 15 >a2.txt <../common/l006.txt
	mv a2.txt house.txt

street.txt:	../common/l006.txt
	@echo street.txt
	fielduc -s 20000000 16 9 30 10 11 31 >a1.txt <../common/l006.txt
	mv a1.txt street.txt
	
zip_a.txt: zip.txt country_a.txt
	@echo zip_a.txt main
	@echo distribute from country to zip
	distribute country_a.txt zip.txt >a4.txt
	field <a4.txt >a4a.txt 2 3 4
	mv a4a.txt zip_a.txt
	rm a4.txt
	
country_a.txt: country.txt
	@echo country_a.txt main
	echo @add enought people to equal the adult population of the us
	awk -F \| <country.txt '{ print "USA|" ($$1 + 0) "|260891336" }' \
	 >a2c.txt
	 mv a2c.txt country_a.txt

zip.txt: ../common/l006.txt
	@echo zip.txt main
	@echo compute gender count per zip
	time fielduc -s 16 <../common/l006.txt >t4.txt
	set_field 3 USA <t4.txt >t4a.txt
	field <t4a.txt >t4.txt 3 1 2
	mv t4.txt zip.txt
	rm t4a.txt

country.txt: ../common/l006.txt
	@echo country.txt main
	@echo compute gender count per country
	time wc -l <../common/l006.txt >t1.txt 
	mv t1.txt country.txt

			
			

	




top_level_random_seed:
	generate_random_seed >top_level_random_seed
	

