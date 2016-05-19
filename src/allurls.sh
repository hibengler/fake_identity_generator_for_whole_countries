#!/bin/bash
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
date
echo cs flm
#!1*


# this is for XDD - with each url being listed
# for XDD2, go below
time echo "/cs" | allurls | fielduc 1 10000000  | field 1 >csa.txt
time randomize <csa.txt | gzip >csb.txt.gz 64273499



time echo "/flm" | allurls | fielduc 1 10000000  | field 1 >flma.txt
time randomize <flma.txt | gzip >flmb.txt.gz 64363230


time echo "/lfm" | allurls | fielduc 1 10000000  | field 1 >lfma.txt
time randomize <lfma.txt | gzip >lfmb.txt.gz 64363230



time echo "/phn" | allurls | fielduc 1 10000000  | field 1 >phna.txt
time randomize <phna.txt | gzip >phnb.txt.gz 64363230

time echo "/ssn" | allurls | fielduc 1 10000000  | field 1 >ssna.txt
time randomize <ssna.txt | gzip >ssnb.txt.gz 64363230



#here is xdd2  we just get the indexes with addurl and compute the ssn and phn separately
#as root:
echo 0 >/proc/sys/vm/swappiness
swappiness
drop_caches 0 ->
vfs_cache_pressure 100->
zone_reclaim_mode
min_slab_ratio 5 ->

1649267441664


export TMP=/u1/tmp
export PATH=~/cvs/player/src:$PATH
cd player/i 
time echo "/phn" | allurls2 >phn1.txt
awk  <../out/n001_phone_area_code.txt  -F \| '{print "/phn/" $2 "/" $3 "/" $4 "/" $5 "/" $6 }' >phn2.txt

|  fielduc 1 20000000  | field 1  >phna.txt
time randomize <phna.txt 12143247 | gzip >phnb.txt.gz 

time echo "/ssn" | allurls2 >ssn1.txt
time awk  <../out/n001_ssn.txt  -F \| '{print "/ssn/" $2 "/" $3 "/" $4 "/" $5 }' >ssn2.txt
|  fielduc 1 20000000  | field 1   >ssna.txt
time randomize <ssna.txt 12143218 | gzip >ssnb.txt.gz 
