

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
# expect MATCH_FLAGS to be set
export MATCH_FLAGS="$1"

#good_name_p5.txt:	good_name_p2.txt 
echo 1>&2  good_name_p5.txt run `cat run`
echo 1>&2  check if first name last name in same city
multiproc.sh match -n $MATCH_FLAGS 15 14 10  34  \
	  ../common/city_street_lname.txt  <good_name_p2.txt 2>d1.txt | \
multiproc.sh match -n $MATCH_FLAGS 16 10 34 \
	  ../common/zipcode_street_lname.txt   2>d3.txt  	>d2a.txt
multiproc.sh match <d2a.txt -n $MATCH_FLAGS 15 14 34 33 \
	 ../common/city_lname_fname.txt   2>d4.txt  >d2.txt
rm d2a.txt

echo 1>&2 good_name_p5.txt check maiden names
is_it_filled_in 39 <d2.txt 2>good_name_p5.txt |
  multiproc.sh match -n $MATCH_FLAGS 15 14 10  39  \
	  ../common/city_street_lname.txt  2>>d1.txt | \
  multiproc.sh match -n $MATCH_FLAGS 16 10 39 \
	  ../common/zipcode_street_lname.txt   2>>d3.txt  	>d2a.txt
  multiproc.sh match <d2a.txt -n $MATCH_FLAGS 15 14 39 33 \
	 ../common/city_lname_fname.txt   2>>d4.txt  >>good_name_p5.txt
mv d4.txt good_name_redo_p5.txt
mv d3.txt good_name_redo_p4.txt
mv d1.txt good_name_redo_p3.txt


#good_name_p6.txt:	good_name_p5.txt 
echo 1>&2  good_name_p6.txt run `cat run`
is_it_filled_in <good_name_p5.txt 17 2>d0_skippy.txt | \
multiproc.sh match -n $MATCH_FLAGS 17 34 33  ../common/area_code_lname_fname.txt 2>d1.txt  >d2.txt
echo 1>&2 good_name_p6.txt check maiden names
is_it_filled_in 39 <d2.txt 2>>d0_skippy.txt | \
  multiproc.sh match -n $MATCH_FLAGS 17 39 33  ../common/area_code_lname_fname.txt 2>>d1.txt  >d3.txt
cat >>d3.txt d0_skippy.txt
rm  d0_skippy.txt 
mv d3.txt good_name_p6.txt
mv d1.txt good_name_redo_p6.txt




#good_name_p7.txt:	good_name_p6.txt 
echo 1>&2  good_name_p7.txt run `cat run`
multiproc.sh match <good_name_p6.txt $MATCH_FLAGS 15 special_states.inp\
  2>pass_p7.txt | \
 multiproc.sh match $MATCH_FLAGS -n 15 34 33 35 ../common/state_lname_fname_minit.txt  2>d1.txt >d2.txt
echo 1>&2 good_name_p7.txt check maiden names
is_it_filled_in  39 <d2.txt 2>>pass_p7.txt | \
 multiproc.sh match $MATCH_FLAGS -n 15 39 33 35 ../common/state_lname_fname_minit.txt  2>>d1.txt >d3.txt
cat >>pass_p7.txt d3.txt
rm d2.txt
rm d3.txt
mv pass_p7.txt good_name_p7.txt
mv d1.txt good_name_redo_p7.txt


#good_name_p7bis.txt:	good_name_p7.txt 
echo 1>&2  good_name_p7bis.txt run `cat run`
multiproc.sh match -n $MATCH_FLAGS 16 34 33 ../common/zipcode_lname_fname.txt \
	  <good_name_p7.txt 2>d1.txt   >d2.txt
echo 1>&2 good_name_p7bis.txt check maiden names
is_it_filled_in  39 <d2.txt 2>good_name_p7bis.txt | \
  multiproc.sh match -n $MATCH_FLAGS 16 39 33 ../common/zipcode_lname_fname.txt \
	   2>>d1.txt   >d3.txt
cat >>good_name_p7bis.txt d3.txt
rm d2.txt d3.txt
mv d1.txt good_name_redo_p7bis.txt
	



#good_name_p8.txt:      good_name_p7bis.txt
cp good_name_p7bis.txt test.txt
rm 2>/dev/null d1.txt

# check run 001
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_001.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_001.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt

# check run TST1
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_TST1.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_TST1.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt


# check run PUB2
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_PUB2.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_PUB2.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt


# check run PUB3
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_PUB3.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_PUB3.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt



# check run PUB4
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_PUB4.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_PUB4.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt

# check run PUB5
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_PUB5.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_PUB5.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt

# check run PUB6
echo 1>&2  good_name_p8.txt run `cat run`
multiproc.sh match -n -p -l 34 33 16 7 ../common/exlfza_PUB6.txt \
          <test.txt 2>>d1.txt   >d2.txt
echo 1>&2 good_name_p8.txt check maiden names
is_it_filled_in  39 <d2.txt 2>test.txt | \
  multiproc.sh match -n -p -l 39 33 16 7 ../common/exlfza_PUB6.txt \
           2>>d1.txt   >d3.txt
cat >>test.txt d3.txt
rm d2.txt d3.txt

# final cleanup
mv d1.txt good_name_redo_p8.txt
mv test.txt good_name_p8.txt



