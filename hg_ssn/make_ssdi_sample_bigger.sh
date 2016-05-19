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
# We run through all letters and make 6 files via snobol with 6 streams.
#
#
export SOURCE_DIR=~/cvs/player/common/ftm_source
{
cat $SOURCE_DIR/[a-d]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_1.txt 2>ssdi_sample_bigger_1.err &
cat $SOURCE_DIR/[e-h]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_2.txt 2>ssdi_sample_bigger_2.err &
cat $SOURCE_DIR/[i-l]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_3.txt 2>ssdi_sample_bigger_3.err &
cat $SOURCE_DIR/[m-p]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_4.txt 2>ssdi_sample_bigger_4.err &
cat $SOURCE_DIR/[q-t]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_5.txt 2>ssdi_sample_bigger_5.err &
cat $SOURCE_DIR/[u-z]/*.txt | snobol4 -b ssdi_bigger_cleanup.sno >ssdi_sample_bigger_6.txt 2>ssdi_sample_bigger_6.err &
wait
}
 
