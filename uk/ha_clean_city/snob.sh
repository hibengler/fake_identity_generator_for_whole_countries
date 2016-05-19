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
rm -rf $>/dev/null /tmp/p1$$
rm -rf $>/dev/null /tmp/p2$$
rm -rf $>/dev/null /tmp/p3$$
rm -rf $>/dev/null /tmp/p4$$
rm -rf $>/dev/null /tmp/p5$$
rm -rf $>/dev/null /tmp/p6$$
mknod /tmp/p1$$ p
mknod /tmp/p2$$ p
mknod /tmp/p3$$ p
mknod /tmp/p4$$ p
mknod /tmp/p5$$ p
mknod /tmp/p6$$ p
{
flip_flop <../common/ukraw.tab >/tmp/p1$$ 2>/tmp/p2$$ 3>/tmp/p3$$ 4>/tmp/p4$$ 5>/tmp/p5$$ 6>/tmp/p6$$ 6 &
snobol4 -d 100m -b  name.sno </tmp/p1$$ >../common/x.txt &
snobol4 -d 100m -b  name.sno </tmp/p2$$ >x2.txt &
snobol4 -d 100m -b  name.sno </tmp/p3$$ >x3.txt &
snobol4 -d 100m -b  name.sno </tmp/p4$$ >x4.txt &
snobol4 -d 100m -b  name.sno </tmp/p5$$ >x5.txt &
snobol4 -d 100m -b  name.sno </tmp/p6$$ >x6.txt &
}
wait
cat >>../common/x.txt x2.txt x3.txt x4.txt x5.txt x6.txt
rm -rf 2>/dev/null x2.txt x3.txt x4.txt x5.txt x6.txt
rm -rf 2>/dev/null x2.txt x3.txt x4.txt x5.txt x6.txt
echo done

