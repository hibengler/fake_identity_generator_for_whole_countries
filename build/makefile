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
system:	h


h:	ho


ho:	hn
	cd ../ho* && time make
	touch ho


hn:	hm
	cd ../hn* && time make
	touch hn



hm:	hl
	cd ../hm* && time make
	touch hm

hl:	hk
	cd ../hl* && time make
	touch hl


hk:	hj
	cd ../hk* && time make
	touch hk

hj:	hi
	cd ../hj* && time make
	touch hj

hi:	hg
	cd ../hi* && time make
	touch hi

hg:	hf
	cd ../hg* && time make
	touch hg

hf:	he
	cd ../hf* && time make
	touch hf

he:	hd
	cd ../he* && time make
	touch he

hd:	hc
	cd ../hd* && time make
	touch hd

hc:	hb
	cd ../hc* && time make
	touch hc

hb:	ha
	cd ../hb* && time make
	touch hb
	

ha:	
	cd ../ha* && time make
	touch ha

oldsystem: preliminary all_people fakeit







fakeit: all_people gm


all_people: preliminary be
	touch all_people

preliminary: ai ag ad
	touch preliminary
break:	
	cd ../aa_build_version_1 && make break
	cd ../be_person && make break
	cd ../bd_phone && make break
	cd ../bc_streets && make break
	cd ../bb_state_city_zip && make break
	cd ../ba_name && make break
	cd ../ai_initial_last_names && make break
	cd ../ag_prefixes && make break
	cd ../af_city_area_code && make break
	cd ../ae_area_codes && make break
	cd ../ad_zipcodes && make break
	cd ../ac_cities_from_zipcode_list && make break
	cd ../ab_state && make break
	-rm a[a-z] b[a-z] preliminary all_people
	
	

be:	bd bc ba 
	cd ../be_person && time make
	touch be

bd:	aa bb
	cd ../bd_phone && time make
	touch bd

bc:	aa bb
	cd ../bc_streets && time make
	touch bc

bb:	aa
	cd ../bb_state_city_zip && time make
	touch bb

ba:	aa
	cd ../ba_name && time make
	touch ba

aa:
	cd ../aa_build_version_1 && time make
	touch aa

ab: aa
	cd ../ab_state && time make
	touch ab

ac: ab
	cd ../ac_cities_from_zipcode_list && time make
	touch ac
	
ad: ac
	cd ../ad_zipcodes && time make
	touch ad

ae: ac
	cd ../ae_area_codes && time make
	touch ae

af: ae 
	cd ../af_city_area_code && time make
	touch af
	
ag: af
	cd ../ag_prefixes && time make
	touch ag

ai:	aa
	cd ../ai_initial_last_names && time make
	touch ai

gm:   all_people
	cd ../gm* && time make

