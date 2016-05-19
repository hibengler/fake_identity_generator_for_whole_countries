/*
Fake Identity Generator
Copyright (C) 2011-2016 Hibbard M. Engler (Bitcoin address 1ERDHsxtekdh5FAsxdb92PBFK7nnuwMkbp for gifts)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
void  gen_watermark_code(char *line,char *wm1, char *wm2, char *wm3,char *wm4);
void double_code_forward(char *wma1, char *wma2, char *wma3, char *wma4,
                         char *wmb1, char *wmb2, char *wmb3, char *wmb4,
			 char *wmc1, char *wmc2, char *wmc3, char *wmc4);
void watermark(char *in_line,char *outline,char *wm1,char *wm2,char *wm3, char *wm4);
