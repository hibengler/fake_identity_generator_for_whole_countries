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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <wand/MagickWand.h>
/* 
derived from modify_pic.c on 3/31/2013
This thing is real cool because it reads binary bit maps from generating a hologram
and then changes the color to be lighter/darker and then
puts in text that is random
And then it randomly puts in a hidden message
But the problem is that the size of the file is too big and causes problems uploading it
So we are going to eschew the pattern
And just draw some fricking text and call it a day,
*/


int the_bg_color = 0xf0f0f0;


int bits[] = {0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};


/* borrowed from fp_to_txt.c for eyes code */
/* color wheel from green to cyan,blue,purple, etc 
But we want to start at blue - so we will add 180 */
static int chroma[] = {
0,255,0,
0,255,6,
0,255,12,
0,255,18,
0,255,24,
0,255,30,
0,255,36,
0,255,43,
0,255,49,
0,255,55,
0,255,61,
0,255,67,
0,255,73,
0,255,79,
0,255,85,
0,255,91,
0,255,97,
0,255,103,
0,255,109,
0,255,115,
0,255,121,
0,255,128,
0,255,134,
0,255,140,
0,255,146,
0,255,152,
0,255,158,
0,255,164,
0,255,170,
0,255,176,
0,255,182,
0,255,188,
0,255,194,
0,255,300,
0,255,206,
0,255,214,
0,255,219,
0,255,225,
0,255,231,
0,255,237,
0,255,243,
0,255,249,
0,255,255,
0,250,255,
0,244,255,
0,238,255,
0,232,255,
0,226,255,
0,220,255,
0,213,255,
0,208,255,
0,202,255,
0,196,255,
0,190,255,
0,184,255,
0,178,255,
0,172,255,
0,166,255,
0,160,255,
0,154,255,
0,148,255,
0,142,255,
0,136,255,
0,130,255,
0,125,255,
0,119,255,
0,113,255,
0,107,255,
0,101,255,
0,95,255,
0,89,255,
0,83,255,
0,77,255,
0,71,255,
0,65,255,
0,59,255,
0,53,255,
0,47,255,
0,42,255,
0,36,255,
0,30,255,
0,24,255,
0,18,255,
0,12,255,
0,6,255,
0,0,255,
6,0,255,
12,0,255,
18,0,255,
24,0,255,
30,0,255,
36,0,255,
43,0,255,
49,0,255,
55,0,255,
61,0,255,
67,0,255,
73,0,255,
79,0,255,
85,0,255,
91,0,255,
97,0,255,
103,0,255,
109,0,255,
115,0,255,
121,0,255,
128,0,255,
134,0,255,
140,0,255,
146,0,255,
152,0,255,
158,0,255,
164,0,255,
170,0,255,
176,0,255,
182,0,255,
188,0,255,
194,0,255,
300,0,255,
206,0,255,
214,0,255,
219,0,255,
225,0,255,
231,0,255,
237,0,255,
243,0,255,
249,0,255,
255,0,255,
255,0,250,
255,0,244,
255,0,238,
255,0,232,
255,0,226,
255,0,220,
255,0,213,
255,0,208,
255,0,202,
255,0,196,
255,0,190,
255,0,184,
255,0,178,
255,0,172,
255,0,166,
255,0,160,
255,0,154,
255,0,148,
255,0,142,
255,0,136,
255,0,130,
255,0,125,
255,0,119,
255,0,113,
255,0,107,
255,0,101,
255,0,95,
255,0,89,
255,0,83,
255,0,77,
255,0,71,
255,0,65,
255,0,59,
255,0,53,
255,0,47,
255,0,42,
255,0,36,
255,0,30,
255,0,24,
255,0,18,
255,0,12,
255,0,6,
255,0,0,
255,6,0,
255,12,0,
255,18,0,
255,24,0,
255,30,0,
255,36,0,
255,43,0,
255,49,0,
255,55,0,
255,61,0,
255,67,0,
255,73,0,
255,79,0,
255,85,0,
255,91,0,
255,97,0,
255,103,0,
255,109,0,
255,115,0,
255,121,0,
255,128,0,
255,134,0,
255,140,0,
255,146,0,
255,152,0,
255,158,0,
255,164,0,
255,170,0,
255,176,0,
255,182,0,
255,188,0,
255,194,0,
255,300,0,
255,206,0,
255,214,0,
255,219,0,
255,225,0,
255,231,0,
255,237,0,
255,243,0,
255,249,0,
255,255,0,
250,255,0,
244,255,0,
238,255,0,
232,255,0,
226,255,0,
220,255,0,
213,255,0,
208,255,0,
202,255,0,
196,255,0,
190,255,0,
184,255,0,
178,255,0,
172,255,0,
166,255,0,
160,255,0,
154,255,0,
148,255,0,
142,255,0,
136,255,0,
130,255,0,
125,255,0,
119,255,0,
113,255,0,
107,255,0,
101,255,0,
95,255,0,
89,255,0,
83,255,0,
77,255,0,
71,255,0,
65,255,0,
59,255,0,
53,255,0,
47,255,0,
42,255,0,
36,255,0,
30,255,0,
25,255,0,
20,255,0,
15,255,0,
10,255,0,
5,255,0,
};




void rgb_from_brightness_and_phase(double phase,int brightness,int *pr,int *pg,int *pb) {
/* phase is in radians, and brightness is in 0-255*/
int ig = (int)(phase * 256. / 6.28318531);
ig = ig % 256;
if (ig<0) ig = ig + 256;
int g = brightness;
    /* ig now has the imaginary value */
    /* now look up the chroma to use for the given imaginary value */
    double r1,g1,b1;
    double rvalue;
    rvalue = g; /* convert to floating point once */
    r1 = chroma[ig*3];
    g1 = chroma[ig*3+1];
    b1 = chroma[ig*3+2];
    
      
      
    /* all right - now we need to binary search for a rate where the rate is as big as it can get.
       The rate can go from 0 to 1 inclusive.
       What we do - 
       First add the color as much as we can by the rate.
       Then look at the effective black and white luma
       then offset the values so the luma is bigger
       Then see if any numbers are outside the boundary (0-255)
       And if so, it failed - try smaller.
       0 will always succeed
       We do this by using a delta
       */
    double lo,hi;
    double delta;
    int r4,b4,g4; /* same as spreadsheet */
    hi=1.0;
    lo=0.0;
    delta = 1.;
    r4 = g;
    g4 = g;
    b4 = g;
    while (delta > 0.000000001) {
      double rate;
      double r2,g2,b2; /* with rate applied */
      double effective_total;
      double offset;
      double diff;
      int r3,b3,g3; /* same as spreadsheet */
      
      rate = (hi+lo)*0.5; /* try half way */
      r2 = rvalue + (r1-rvalue)* rate;
      g2 = rvalue + (g1-rvalue)* rate;
      b2 = rvalue + (b1-rvalue)* rate;
      
      
      effective_total = (r2*76.+g2*151.+b2*28)/255.;
      diff = rvalue - effective_total;
      
      r3 = r2 + diff;
      g3 = g2 + diff;
      b3 = b2 + diff;
      
      
      /* OK - if this works, then we will go higher and try to find a more vivid color
         If it cant( because of range issues ) we stay lower */
      if ((r3<0)||(g3<0)||(b3<0)||
          (r3>255)||(g3>255)||(b3>255)) {
	hi=rate; /* no fit, try a lower rate */
	}
      else {
        r4=r3;
	g4=g3;
	b4=b3;
        lo=rate; /* it fits - try something higher */
	}
      delta = hi-lo;
      }

	
*pr = r4;
*pg = g4;
*pb = b4;	
}






/* if the bit is in the gpg encoded message then send it otherwise 
use the boilerplate text */  
int get_bit(int pos,char *buf,int max_size) { 
int p1 = pos >>3;
int p2 = pos & 7;
if (p1<max_size) {
  return (buf[p1] & bits[p2]);
  }
else {
  p1 = (p1-max_size) % 45;
  char *x = "The quick brown fox jumped over the lazy dog.";
  return (x[p1] & bits[p2]);
  }
}


























int main(int argc,char **argv)
{
/* seed1 ip_Address fname */
char *ip_address=argv[1];
char *fname=argv[2];
int data_size=259200; /* will actually be the gpg size */

unsigned char *otherrand;
int other;
unsigned char rbuf[259200]; // extra 4 bites to make this unpredictable 
unsigned char mbuf[259200];
{ 


  FILE *xf;
  /* get the information from god and obscure it by one of the image templates */
  xf=fopen("/dev/urandom","r"); /* This was /dev/god as a joke */
  fread( rbuf, sizeof(unsigned char), 259200, xf);
  other = 0;
  otherrand = (unsigned char *) &other;
  fread( otherrand, sizeof(unsigned char), 4, xf); /* ask god for the next random seed */
  fclose(xf);
  srand(rand() ^ other);


  
#define NPICS 90197


  srand(rand() ^ atoi(ip_address));

  }



MagickWandGenesis();

/* we need 3 colors:
1. brighter color 1
2. darker color 2
3. darker text 3
And,  the colors will be rainbowed
*/
int iii;
for (iii=0;iii<256;iii++) {
 
  
double phase1 = iii * 6.28 / 256.;
int br1 = 240; /* brighter background */
int br2 = 160; /* darker background */
int br3 = 145; /* words background */
int r1,g1,b1;
int r2,g2,b2;
int r3,g3,b3;
double offset=2.0943951; /* pi * 2/3 for 3 phase */
if (rand() &1) { offset = - offset; } /* randomly switch directions */

rgb_from_brightness_and_phase(phase1,br1,&r1,&g1,&b1);
rgb_from_brightness_and_phase(phase1+offset*0.5,br2,&r2,&g2,&b2);
rgb_from_brightness_and_phase(phase1-offset,br3,&r3,&g3,&b3);
int avg;
avg=(r1+g1+b1)/3;
r1 = r1 /2 + avg/2;
g1 = g1 /2 + avg/2;
b1 = b1 /2 + avg/2;
avg=(r2+g2+b2)/3;
r2 = r2 /2 + avg/2;
g2 = g2 /2 + avg/2;
b2 = b2 /2 + avg/2;
avg=(r3+g3+b3)/3;
r3 = r3 /2 + avg/2;
g3 = g3 /2 + avg/2;
b3 = b3 /2 + avg/2;
/*r1 = r1 <<8;
g1 = g1 <<8;
b1 = b1 <<8;
r2 = r2 <<8;
g2 = g2 <<8;
b2 = b2 <<8;
*/
the_bg_color=r1*256*256+g1*256+b1;
printf("%d,\n",the_bg_color);
fflush(stdout);
{ /* print to the color space too */
  char buf[200];
  sprintf(buf,"i/%u.clr",iii);
  FILE *xf;
  xf=fopen(buf,"w");
  if (xf) {
    fprintf(xf,"%d\n",the_bg_color);
    fclose(xf);
    }
  }

/* we dont shift r3 g3 and b3 because we use these differently */



	MagickWand *m_wand = NULL;
	DrawingWand *d_wand = NULL;
	PixelWand *c_wand = NULL;
	PixelWand *c2_wand = NULL;
        MagickPixelPacket
          pixel;


	m_wand = NewMagickWand();
	d_wand = NewDrawingWand();
	c_wand = NewPixelWand();
	c2_wand = NewPixelWand();
      {
      char buf[2000];
      sprintf(buf,"rgb(%d,%d,%d)",r1,g1,b1);
/*      fprintf(stderr,"%s\n",buf);*/
      PixelSetColor(c_wand,buf); /* for now */
      }


	MagickNewImage(m_wand,1920,1080,c_wand);
        MagickSetImageChannelDepth(m_wand, AllChannels, 8);
        MagickSetImageDepth(m_wand, 8);
        DrawSetStrokeOpacity(d_wand,1);

#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

  MagickBooleanType
    status;


  PixelIterator
    *iterator;

  PixelWand
    **pixels;

  register ssize_t
    x;

  size_t
    width;

  ssize_t
    y;


      
  
{
  char pbuf[100];  
  unsigned int c;
  c=(unsigned int)r3 * (65536*256) + g3 * 65536 + b3 * 256 + 48;
  sprintf(pbuf  ,"#%8.8x",c);
  PixelSetColor(c_wand,pbuf);
  
  /* now for color 2 */
  c=(unsigned int)r2 * (65536*256) + g2 * 65536 + b2 * 256 + 48;
  sprintf(pbuf  ,"#%8.8x",c);
  PixelSetColor(c2_wand,pbuf);
  
  }

/* Draw fake identity at the top and bottom */
/* right.  now draw some spooky text to spookify them */
	// Set up a 72 point font 
	DrawSetFillColor(d_wand,c2_wand);
	DrawSetStrokeColor(d_wand,c2_wand);
	DrawSetFont (d_wand, "Verdana-Bold-Italic" ) ;
	DrawSetFontSize(d_wand,35);
	// Now draw the text
	{
	char buf[1000];
	unsigned int t=atoi(ip_address);
	unsigned int a,b,c,d;
	a=t&255;
	t = t >>8;
	b=t&255;
	t = t >>8;
	c=t&255;
	t = t >>8;
	d=t&255;
	sprintf(buf,"Fake");
	int u;
	int cc;
	cc=0;
	for (u=0;u<=1800;u += 1800/8) {
	  DrawAnnotation(d_wand,29+u,80,buf);	
	  if ((cc==0)||(cc>=6)) {
	    DrawAnnotation(d_wand,29+u,387,buf);	
	    }
	  DrawAnnotation(d_wand,29+u,694,buf);	
	  DrawAnnotation(d_wand,29+u,1080-80,buf);	
          cc++;
	  }
	}	
	
	
	// Set up a 72 point font 
	DrawSetFillColor(d_wand,c_wand);
	DrawSetStrokeColor(d_wand,c_wand);
	DrawSetFont (d_wand, "Verdana-Bold-Italic" ) ;
	DrawSetFontSize(d_wand,40);

	char *choice[] = {
	  "This data is fake.",
	  "We record all access logs",
	  "Fraudulent use of this data is a crime",
	  "It is better to publish fake identity,  than real identity."
	  };
	 int choices[5] = {1,1,1,1,1};
	int t=420;
	int tx = 440;
	int c;
	int i;
	for (i=0;i<3;i++) {
 	  while (!choices[(c=  (rand()%7) /2)]);
	  choices[c]=0;
	  DrawAnnotation(d_wand,240,t,choice[c]);
  	  t = t + 40;
          tx = tx + 20;	  
	  }
	
	{
	DrawSetFontSize(d_wand,50);
	char buf[1000];
	unsigned int t=atoi(ip_address);
	unsigned int a,b,c,d;
	a=t&255;
	t = t >>8;
	b=t&255;
	t = t >>8;
	c=t&255;
	t = t >>8;
	d=t&255;
	sprintf(buf,"Fake U.K. Identities");
	DrawAnnotation(d_wand,230,318,buf);	
	sprintf(buf,"Protecting our real identity since 2012");
	DrawAnnotation(d_wand,230,370,buf);	
	}
MagickDrawImage(m_wand,d_wand);    
      
	  
  

  
  
  
  
  
  
 
  
  
  
  
  
  
  /*
    Write the image then destroy it.
  */
  char fname2[10000];
  sprintf(fname2,"%d.png",iii);
  status=MagickWriteImages(m_wand,fname2,MagickTrue);
  if (status == MagickFalse)
    ThrowWandException(m_wand);
  m_wand=DestroyMagickWand(m_wand);
  
  }
  
  MagickWandTerminus();
  return(0);
}

