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
gunzip <$a/cs_d.txt.gz | randomize 314675912 | gzip >cs_e.txt.gz
gunzip <$a/flm_d.txt.gz | randomize 31475912 | gzip >flm_e.txt.gz
gunzip <$a/lfm_d.txt.gz | randomize 3146912 | gzip >lfm_e.txt.gz
gunzip <$a/phn_d.txt.gz | randomize 375912 | gzip >phn_e.txt.gz
gunzip <$a/ssn_d.txt.gz | randomize 3412 | gzip >ssn_e.txt.gz
 

mkdir cs
cd cs
gunzip <../cs_e.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try3/cs/" cs_01
cd ..
mkdir flm
cd flm
gunzip <../flm_e.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try3/flm/" flm_01
cd ..
mkdir lfm
cd lfm
gunzip <../lfm_e.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try3/lfm/" lfm_01
cd ..
mkdir phn
cd phn
gunzip <../phn_e.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try3/phn/" phn_01
cd ..
mkdir ssn
cd ssn
gunzip <../ssn_e.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try3/ssn/" ssn_01
cd ..

nohup randomize 324367 <urls_cs.txt | split -l 30000000 - urls_cs_r.txt
cat urls_cs_r.txtaa | list_to_site_map <urls_cs_r.txtaa "http://www.xdd.org" "http://www.xdd.org/geometry/try2/cs/" wcs_01

nohup randomize 432123 <urls_phn.txt >urls_phn_r.txt
list_to_site_map <urls_phn.txt "http://www.xdd.org" "http://www.xdd.org/geometry/try2/phn/" wphn_01

randomize <urls_ssn.txt 3214 >urls_ssn_r.txt
list_to_site_map <urls_ssn_r.txt "http://www.xdd.org" "http://www.xdd.org/geometry/try2/ssn/" wssn_01

list_to_site_map <urls_flm.txt "http://www.xdd.org" "http://www.xdd.org/geometry/try2/flm/" wflm_01

list_to_site_map <urls_lfm.txt "http://www.xdd.org" "http://www.xdd.org/geometry/try2/lfm/" wlfm_01

list_to_site_map  "http://f.xdd.org" "http://f.xdd.org/geometry/try1/" fml
#head -100000 <urls_cs.txt | list_to_site_map  "http://f.xdd.org" "http://f.xdd.org/sitemap/" cs

# these are the middle men because I think google has a disconnect, from source to destinaion

mkdir l01
cd l01
gunzip <../l1.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try2a/l01/" l_01
cd ..

mkdir l02
cd l02
gunzip <../l2.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try2a/l02/" l_02
cd ..



mkdir l03
cd l03
gunzip <../l3.txt.gz | list_to_site_map "http://www.xdd.org" "http://www.xdd.org/geometry/try2a/l03/" l_03
cd ..




# ^^^ xdd

# xdd2:

list_to_site_map <../phnb.txt "http://xdd2.org" "http://xdd2.org/geometry/phn/" phn_02
list_to_site_map <../ssnb.txt "http://xdd2.org" "http://xdd2.org/geometry/ssn/" ssn_02
