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
export run=1
echo $run >prun
rm 2>/dev/null good_name.txt

while  [ 1 ]
do 

  if [[ $run -gt 9 ]]
  then

  if [[ $run -gt 20 ]]
  then

  if [ -s redo_lname.txt ]
  then
    echo "run $run"
    make -f pfiltermakefile tiny
  else
    if [ -s redo_fname.txt ]
      then
      echo "no more last names. getting close at run $run, but need to go again"
      rm 2>/dev/null another_good2
      make -f pfiltermakefile tiny
    else
      ((run=run-1))
      echo "all done. $run runs"
      break;
      fi
    fi
  
  else
  
  if [ -s redo_lname.txt ]
  then
    echo "run $run"
    make -f pfiltermakefile small
  else
    if [ -s redo_fname.txt ]
      then
      echo "no more last names. getting close at run $run, but need to go again"
      rm 2>/dev/null another_good2
      make -f pfiltermakefile small
    else
      ((run=run-1))
      echo "all done. $run runs"
      break;
      fi
    fi
  
  fi  
  else

  if [ -s redo_lname.txt ]
  then
    echo "run $run"
    make -f pfiltermakefile
  else
    if [ -s redo_fname.txt ]
      then
      echo "no more last names. getting close at run $run, but need to go again"
      rm 2>/dev/null another_good2
      make -f pfiltermakefile
    else
      ((run=run-1))
      echo "all done. $run runs"
      break;
      fi
    fi
  fi    

  echo $run >prun
  echo $run is filtered...
  set_field 1 "city_street_lname" <good_name_redo_p3.txt >redo_lname_$run.txt

  set_field 1 "zipcode_street_lname" <good_name_redo_p4.txt >>redo_lname_$run.txt

  set_field 1 "city_lname_fname" <good_name_redo_p5.txt >redo_fname_$run.txt
  set_field 1 "area_code_lname_fname" <good_name_redo_p6.txt >>redo_fname_$run.txt

  set_field 1 "state_lname_fname_minit" <good_name_redo_p7.txt >>redo_fname_$run.txt
  set_field 1 "zipcode_lname_fname" <good_name_redo_p7bis*.txt >>redo_fname_$run.txt
  set_field 1 "older_match" <good_name_redo_p8.txt >>redo_fname_$run.txt
 
  cat >>good_name.txt good_name_p8.txt


  mkdir prun_$run
  mv good_name_p1*.txt good_name_p2*.txt good_name_p5.txt good_name_p6.txt \
   good_name_p7*.txt good_name_p8.txt \
  good_name_redo_p*.txt singleton_name_p1*.txt singleton_name_p2*.txt random_seed_f prun_$run
  cp redo_lname_$run.txt prun_$run
  cp redo_fname_$run.txt prun_$run
  mv redo_lname_$run.txt redo_lname.txt
  mv redo_fname_$run.txt redo_fname.txt

  export run=`cat prun`
  ((run=run+1))
  export run=$run
  # added! need to add in the other roundupp areas.
  echo $run >prun
  done
