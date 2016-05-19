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

system: ../common/l005.txt
	@echo hey you should only do a make -j 1 here for faster speeds


../common/l005.txt:	filtered.txt
	@echo this is temporary: compute l005
	@echo we should probably sort the damn thing
	cp good_name.txt ../common/a1.txt
	mv ../common/a1.txt ../common/l005.txt

	
	
filtered.txt:	filters.txt make_singleton_prep.txt singletons.txt  
	@echo filter_done being done main
	@echo good_name_p8.txt is ready
	@echo calling roundup.sh
	-rm 2>/dev/null redo_lname.txt
	ln ../common/l004.txt redo_lname.txt
	-rm 2>/dev/null wife_husband.txt
	ln ../common/wife_husband004.txt wife_husband.txt
	-rm 2>/dev/null -rf redo_fname.txt
	touch redo_fname.txt
	time bash roundup.sh
	@echo done calling roundup.sh 
	touch filtered.txt
	



filters.txt:  singletons.txt
	make -j 6 -f filters_prep_makefile

make_singleton_prep.txt: singletons.txt
	make -j 6 -f make_singleton_prep_makefile

singletons.txt: random_seed make_name_prep.txt
	@echo singletons.txt main	
	multiproc.sh  <../common/l004.txt  >yyo.txt 2>ye.txt make_name_from_name `cat random_seed`  -l -p
	 -grep -v ^warning  <ye.txt >singletons.txt
	 rm ye.txt
	 mv yyo.txt fixed_middle_initials.txt

make_name_prep.txt: ../common/l004.txt
	make -j 6 -f make_name_prep_makefile


random_seed:
	generate_random_seed >random_seed
	
	
