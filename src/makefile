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

#
# 
# before start do
# sudo apt-get install imagemagick libmagickcore-dev libmagickwand-dev 
#
# also need BAR_DATABASE set to the home fo bar_Database - usually ~/opencvs/bar_database
#
# $Revision$
#
# $Log$
# Revision 1.1  2016/05/19 15:29:24  hib
# Initial publish as GPL V2
#
# Revision 1.53  2014/12/16 23:55:03  hib
# Moved all this stuff into bar_database as open source
#
# Revision 1.52  2014/11/15 07:53:38  hib
# Time to start prepping
#
# Revision 1.51  2013/04/14 06:35:57  hib
# modified makefile to not do the rtr website - that is separated out
#
# Revision 1.50  2013/04/08 05:57:32  hib
# makefile - rtr2 was going into rtr3. fixed.
# xlate.c - brought FAKE back to xdd and xdd2 main page.
# xdd3 does not have it.
#
# Revision 1.49  2013/04/07 03:02:28  hib
# took the word fake out of txlate.c ? duH!
#
# Revision 1.48  2013/04/01 19:48:01  hib
# MAde the fake UK identities pictures - added more fakes for the fans.
#
# Revision 1.47  2013/03/27 16:12:17  hib
# add more instuctions for setup
#
# Revision 1.46  2013/03/27 16:00:00  hib
# Added comments as to how to install
#

	ALL = make_name_from_name \
    merge_house_different_city make_gender_from_first_name \
    make_singleton_name  find_spouse marry_people marry_people2 \
     distribute  make_wives elaborate_wives \
    filter_eligable_bachelors \
    make_extra_people_in_houses \
    elaborate_person make_extra_houses \
    make_street make_street2 \
    elaborate_household \
    find_new_wife_husband \
    make_phone_numbers \
    make_birthdate1 \
    make_birthdate2 \
    deduct_state_migration \
    make_ssn_numbers \
    make_dl \
    make_dl_sort_code \
    add_birthdate_birth_state \
    add_ccs \
    add_passport \
    everything_format \
    make_ac \
    give_new_set_id_number_watermark \
    m_to_address_name \
    m_to_phone \
    m_to_phone_prefix \
    modify_pic \
    modify_pic.sh \
    analyze_new_house_spouse \
    allurls \
    allurls2 \
    allurls.sh \
    list_to_site_map \
    fix_fname_lname \
    make_phone_numbers_uk \
    make_nuid_numbers \
    make_dl_uk \
    add_passport_uk \
    modify_pic_uk \
    separate_600k.pl 


#    verify_captcha.pl \

system: $(ALL) 
	chmod 755 *.sh *.pl
	cp $(ALL) ../bin

clip_to_1_char: clip_to_1_char.c util.o util.h uthash.h 
	gcc -O3 -o clip_to_1_char clip_to_1_char.c util.o bsearch.o

elaborate_household:	elaborate_household.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o elaborate_household elaborate_household.c util.o bsearch.o

make_street:	make_street.c util.o util.h uthash.h
	gcc -O3 -o make_street make_street.c util.o

make_street2:	make_street2.c util.o util.h uthash.h
	gcc -O3 -o make_street2 make_street2.c util.o

make_extra_houses:	make_extra_houses.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_extra_houses make_extra_houses.c util.o bsearch.o

elaborate_person:	elaborate_person.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o elaborate_person elaborate_person.c util.o bsearch.o

make_extra_people_in_houses:	make_extra_people_in_houses.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_extra_people_in_houses make_extra_people_in_houses.c util.o bsearch.o

filter_eligable_bachelors:	filter_eligable_bachelors.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o filter_eligable_bachelors filter_eligable_bachelors.c util.o bsearch.o

elaborate_wives:	elaborate_wives.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o elaborate_wives elaborate_wives.c util.o bsearch.o

make_wives:	make_wives.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_wives make_wives.c util.o bsearch.o

fsort: fsort.c util.o util.h uthash.h
	gcc  -O3 -o fsort fsort.c util.o

distribute: distribute.c util.o util.h uthash.h
	gcc  -O3 -o distribute distribute.c util.o
	
marry_people: marry_people.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o marry_people marry_people.c util.o bsearch.o

marry_people2: marry_people2.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o marry_people2 marry_people2.c util.o bsearch.o

find_spouse: find_spouse.c util.o util.h uthash.h
	gcc  -O3 -o find_spouse find_spouse.c util.o

match: match.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o match match.c util.o bsearch.o

make_singleton_name: make_singleton_name.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o make_singleton_name make_singleton_name.c util.o bsearch.o

make_gender_from_first_name: make_gender_from_first_name.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o make_gender_from_first_name make_gender_from_first_name.c util.o bsearch.o

merge_house_different_city: merge_house_different_city.c util.o util.h uthash.h
	gcc -O3 -o merge_house_different_city merge_house_different_city.c util.o

make_name_from_name: make_name_from_name.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o make_name_from_name make_name_from_name.c util.o bsearch.o

find_new_wife_husband:	find_new_wife_husband.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o find_new_wife_husband find_new_wife_husband.c util.o bsearch.o

make_phone_numbers:	make_phone_numbers.c util.o util.h uthash.h bsearch.o bsearch.h phone_common.c phone_common.h
	gcc -O3 -o make_phone_numbers make_phone_numbers.c util.o bsearch.o \
	phone_common.c

make_birthdate1:	make_birthdate1.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_birthdate1 make_birthdate1.c util.o bsearch.o

make_birthdate2:	make_birthdate2.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_birthdate2 make_birthdate2.c util.o bsearch.o


make_ssn_numbers:	make_ssn_numbers.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_ssn_numbers make_ssn_numbers.c util.o bsearch.o

deduct_state_migration:	deduct_state_migration.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o deduct_state_migration deduct_state_migration.c util.o bsearch.o

set_number_of_fields:	set_number_of_fields.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o set_number_of_fields set_number_of_fields.c util.o bsearch.o

make_dl:	make_dl.c util.o util.h uthash.h bsearch.o bsearch.h soundex.o soundex.h  
	gcc -O3 -o make_dl make_dl.c util.o bsearch.o soundex.o

make_dl_sort_code:	make_dl_sort_code.c util.o util.h uthash.h 
	gcc -O3 -o make_dl_sort_code make_dl_sort_code.c util.o 


add_birthdate_birth_state:	add_birthdate_birth_state.c util.o util.h uthash.h bsearch.o bsearch.h  
	gcc -O3 -o add_birthdate_birth_state add_birthdate_birth_state.c util.o bsearch.o 

add_ccs:	add_ccs.c util.o util.h uthash.h 
	gcc -O3 -o add_ccs add_ccs.c util.o 

add_passport:	add_passport.c util.o util.h uthash.h 
	gcc -O3 -o add_passport add_passport.c util.o 


make_ac: make_ac.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o make_ac make_ac.c util.o bsearch.o

everything_format:	everything_format.c
	gcc -O3 -o everything_format everything_format.c


give_new_set_id_number_watermark:	give_new_set_id_number_watermark.c util.o util.h uthash.h watermark.o
	gcc -O3 -o give_new_set_id_number_watermark give_new_set_id_number_watermark.c \
		util.o watermark.o

m_to_address_name:	m_to_address_name.c util.o util.h uthash.h  m_routines.o
	gcc -O3 -o m_to_address_name m_to_address_name.c \
		util.o m_routines.o

m_to_phone:	m_to_phone.c util.o util.h uthash.h  m_routines.o
	gcc -O3 -o m_to_phone m_to_phone.c \
		util.o m_routines.o

m_to_phone_prefix:	m_to_phone_prefix.c util.o util.h uthash.h  m_routines.o
	gcc -O3 -o m_to_phone_prefix m_to_phone_prefix.c \
		util.o m_routines.o

m_routines.o: m_routines.c m_routines.h
	gcc -O3 -c m_routines.c

util.o:  $(BAR_DATABASE)/lib/util.o
	cp $(BAR_DATABASE)/lib/util.o .


soundex.o: $(BAR_DATABASE)/lib/soundex.o
	cp $(BAR_DATABASE)/lib/soundex.o .

		
bsearch.o:  $(BAR_DATABASE)/lib/bsearch.o
	cp $(BAR_DATABASE)/lib/bsearch.o .


util.h:  $(BAR_DATABASE)/include/util.h
	cp $(BAR_DATABASE)/include/util.h .

soundex.h: $(BAR_DATABASE)/include/soundex.h
	cp $(BAR_DATABASE)/include/soundex.h .

		
bsearch.h:  $(BAR_DATABASE)/include/bsearch.h
	cp $(BAR_DATABASE)/include/bsearch.h .

uthash.h:  $(BAR_DATABASE)/include/uthash.h
	cp $(BAR_DATABASE)/include/uthash.h .


watermark.o: watermark.c watermark.h
	gcc -O3 -c watermark.c

combine_pipes: util.o util.h uthash.h combine_pipes.c
	gcc -O3 -o combine_pipes combine_pipes.c util.o

modify_pic: modify_pic.c
#	gcc -O3  `pkg-config --cflags --ldflags --libs MagickWand` -o modify_pic /usr/lib/libMagickWand.a modify_pic.c
	gcc -O3  `MagickWand-config --cflags` modify_pic.c `MagickWand-config --ldflags --libs` -o modify_pic

dos2unix: dos2unix.c
	gcc -o dos2unix dos2unix.c


analyze_new_house_spouse: util.o util.h uthash.h analyze_new_house_spouse.c
	gcc -O3 -o analyze_new_house_spouse analyze_new_house_spouse.c util.o


allurls:	util.o util.h uthash.h bsearch.o bsearch.h allurls.c
	gcc -O3 -o allurls  util.o bsearch.o allurls.c

allurls2:	util.o util.h uthash.h bsearch.o bsearch.h allurls.c
	gcc -O3 -o allurls2 -DXDD2 util.o bsearch.o allurls.c

list_to_site_map:	list_to_site_map.c
	gcc -o list_to_site_map list_to_site_map.c


apate:	util.o util.h uthash.h bsearch.o bsearch.h xlate_apate.c apate.c xlate_colors.h apate.h
	gcc -O3 -o apate apate.c  util.o bsearch.o xlate_apate.c 

fix_fname_lname: fix_fname_lname.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc  -O3 -o fix_fname_lname fix_fname_lname.c util.o bsearch.o


make_phone_numbers_uk:	make_phone_numbers_uk.c util.o util.h uthash.h bsearch.o bsearch.h phone_common.c phone_common.h
	gcc -O3 -o make_phone_numbers_uk make_phone_numbers_uk.c phone_common.c util.o bsearch.o


make_nuid_numbers:	make_nuid_numbers.c util.o util.h uthash.h bsearch.o bsearch.h
	gcc -O3 -o make_nuid_numbers make_nuid_numbers.c util.o bsearch.o


make_dl_uk:	make_dl_uk.c util.o util.h uthash.h bsearch.o bsearch.h soundex.o   
	gcc -O3 -o make_dl_uk make_dl_uk.c util.o bsearch.o soundex.o


add_passport_uk:	add_passport_uk.c util.o util.h uthash.h 
	gcc -O3 -o add_passport_uk add_passport_uk.c util.o 

modify_pic_uk: modify_pic_uk.c
#	gcc -O3  `pkg-config --cflags --ldflags --libs MagickWand` -o modify_pic_uk /usr/lib/libMagickWand.a modify_pic_uk.c
	gcc -O3  `MagickWand-config --cflags` modify_pic_uk.c `MagickWand-config --ldflags --libs` -o modify_pic_uk


