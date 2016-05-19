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

rm 2>/dev/null a1 a2 a3 a4
export r1=`cat random_seed`
export r2=`expr $r1 + 1`
export r3=`expr $r1 + 2`
export r4=`expr $r1 + 3`
echo "random $r1 $r2 $r3 $r4"
mknod a1 p
mknod a2 p
mknod a3 p
mknod a4 p
{
flip_flop <../common/l010.txt >a1 2>a2 3>a3 4>a4 4 &
add_ccs $r1 <a1 >../common/b1 &
add_ccs $r2 <a2 >../common/b2 &
add_ccs $r3 <a3 >../common/b3 &
add_ccs $r4 <a4 >../common/b4 &
}
wait
cat >>../common/b1 ../common/b2 ../common/b3 ../common/b4
rm 2>/dev/null a1 a2 a3 a4 ../common/b2 ../common/b3 ../common/b4
mv ../common/b1 ../common/l011.txt
