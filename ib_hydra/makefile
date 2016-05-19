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



system:	 ../out/n001_hydra_segments.txt ../out/n001_hydra_words.txt


../out/n001_hydra_segments.txt: ../out/n001.txt
	field 11 66 <../out/n001.txt | perl $(PLAYER_HOME)/bin/separate_600k.pl >hydra1.txt
	cat >n001_hydraid_build.txt id[0-9].txt id[0-9][0-9].txt id[0-9][0-9][0-9].txt
	mv n001_hydraid_build.txt ../out/n001_hydra_id.txt
	mv id*.txt ../out
	cp hydra1.txt ../out/n001_hydra_segments.txt

../out/n001_hydra_words.txt: shorter_nouns.txt
	grep -v "'" shorter_nouns.txt | randomize   11 | head -46816 >a.txt
	mv a.txt ../out/n001_hydra_words.txt

	
	
	
