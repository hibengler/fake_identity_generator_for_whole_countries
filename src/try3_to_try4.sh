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

#  gunzip <flm_01_index_01_00621.xml.gz | sed s/\<url\>\<loc\>//g | sed s.\</loc\>\<changefreq\>yearly\</changefreq\>\</url\>..g | grep -v '^<' | head
ls | awk '{ print "gunzip <" $1 " | sed s/\\<url\\>\\<loc\\>//g | sed s.\\</loc\\>\\<changefreq\\>yearly\\</changefreq\\>\\</url\\>..g | grep -v '\''^<'\''" }' 
