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



/* This is a delicate watermark - we are going to print out the full versus not full name here.
It is a single bit,  yes,  but once you get a bunch of them, it will be eas-ier to find the set.
Probably have to do a random distriubtion search or something.

I could flip the number on the cc number - but I decided not to.  Just because.
And the CCV numbers  are xored with a 3 digit code.  There are 3 such codes - but most likely we will only receive 1

We will want to use the best randomness for this - maybee urandom to set the random seed, maybee more than that.  Probably best to have
some random cpu going full bore, and providing sets to its blocking parent whenever. Iduknow.


*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int street_suffix_size=560;

char *street_suffixes[] = {
"","",
"Allee","Alley",
"Alley","Alley",
"Ally","Alley",
"Aly","Alley",
"Anex","Annex",
"Annex","Annex",
"Annx","Annex",
"Anx","Annex",
"Arc","Arcade",
"Arcade","Arcade",
"Av","Avenue",
"Ave","Avenue",
"Aven","Avenue",
"Avenu","Avenue",
"Avenue","Avenue",
"Avn","Avenue",
"Avnue","Avenue",
"Bayoo","Bayoo",
"Bayou","Bayoo",
"Bch","Beach",
"Beach","Beach",
"Belle","Belle",
"Bend","Bend",
"Bg","Burg",
"Bgs","Burgs",
"Blf","Bluff",
"Blfs","Bluffs",
"Bluf","Bluff",
"Bluff","Bluff",
"Bluffs","Bluffs",
"Blvd","Boulevard",
"Bnd","Bend",
"Bot","Bottom",
"Bottm","Bottom",
"Bottom","Bottom",
"Boul","Boulevard",
"Boulevard","Boulevard",
"Boulv","Boulevard",
"Br","Branch",
"Branch","Branch",
"Brdge","Bridge",
"Brg","Bridge",
"Bridge","Bridge",
"Brk","Brook",
"Brks","Brooks",
"Brnch","Branch",
"Brook","Brook",
"Brooks","Brooks",
"Btm","Bottom",
"Burg","Burg",
"Burgs","Burgs",
"Byp","Bypass",
"Bypa","Bypass",
"Bypas","Bypass",
"Bypass","Bypass",
"Byps","Bypass",
"Byu","Bayoo",
"Camp","Camp",
"Canyn","Canyon",
"Canyon","Canyon",
"Cape","Cape",
"Causeway","Causeway",
"Causway","Causeway",
"Cen","Center",
"Cent","Center",
"Center","Center",
"Centers","Centers",
"Centr","Center",
"Centre","Center",
"Cir","Circle",
"Circ","Circle",
"Circl","Circle",
"Circle","Circle",
"Circles","Circles",
"Cirs","Circles",
"Clb","Club",
"Clf","Cliff",
"Clfs","Cliffs",
"Cliff","Cliff",
"Cliffs","Cliffs",
"Club","Club",
"Cmn","Common",
"Cmns","Commons",
"Cmp","Camp",
"Cnter","Center",
"Cntr","Center",
"Cnyn","Canyon",
"Common","Common",
"Commons","Commons",
"Cor","Corner",
"Corner","Corner",
"Corners","Corners",
"Cors","Corners",
"Course","Course",
"Court","Court",
"Courts","Courts",
"Cove","Cove",
"Coves","Coves",
"Cp","Camp",
"Cpe","Cape",
"Crcl","Circle",
"Crcle","Circle",
"Creek","Creek",
"Cres","Crescent",
"Crescent","Crescent",
"Crest","Crest",
"Crk","Creek",
"Crossing","Crossing",
"Crossroad","Crossroad",
"Crossroads","Crossroads",
"Crse","Course",
"Crsent","Crescent",
"Crsnt","Crescent",
"Crssing","Crossing",
"Crssng","Crossing",
"Crst","Crest",
"Cswy","Causeway",
"Ct","Court",
"Ctr","Center",
"Ctrs","Centers",
"Cts","Courts",
"Curv","Curve",
"Curve","Curve",
"Cv","Cove",
"Cvs","Coves",
"Cyn","Canyon",
"Dale","Dale",
"Dam","Dam",
"Div","Divide",
"Divide","Divide",
"Dl","Dale",
"Dm","Dam",
"Dr","Drive",
"Driv","Drive",
"Drive","Drive",
"Drives","Drives",
"Drs","Drives",
"Drv","Drive",
"Dv","Divide",
"Dvd","Divide",
"Est","Estate",
"Estate","Estate",
"Estates","Estates",
"Ests","Estates",
"Exp","Expressway",
"Expr","Expressway",
"Express","Expressway",
"Expressway","Expressway",
"Expw","Expressway",
"Expy","Expressway",
"Ext","Extension",
"Extension","Extension",
"Extensions","Extensions",
"Extn","Extension",
"Extnsn","Extension",
"Exts","Extensions",
"Fall","Fall",
"Falls","Falls",
"Ferry","Ferry",
"Field","Field",
"Fields","Fields",
"Flat","Flat",
"Flats","Flats",
"Fld","Field",
"Flds","Fields",
"Fls","Falls",
"Flt","Flat",
"Flts","Flats",
"Ford","Ford",
"Fords","Fords",
"Forest","Forest",
"Forests","Forest",
"Forg","Forge",
"Forge","Forge",
"Forges","Forges",
"Fork","Fork",
"Forks","Forks",
"Fort","Fort",
"Frd","Ford",
"Frds","Fords",
"Freeway","Freeway",
"Freewy","Freeway",
"Frg","Forge",
"Frgs","Forges",
"Frk","Fork",
"Frks","Forks",
"Frry","Ferry",
"Frst","Forest",
"Frt","Fort",
"Frway","Freeway",
"Frwy","Freeway",
"Fry","Ferry",
"Ft","Fort",
"Fwy","Freeway",
"Garden","Garden",
"Gardens","Gardens",
"Gardn","Garden",
"Gateway","Gateway",
"Gatewy","Gateway",
"Gatway","Gateway",
"Gdn","Garden",
"Gdns","Gardens",
"Glen","Glen",
"Glens","Glens",
"Gln","Glen",
"Glns","Glens",
"Grden","Garden",
"Grdn","Garden",
"Grdns","Gardens",
"Green","Green",
"Greens","Greens",
"Grn","Green",
"Grns","Greens",
"Grov","Grove",
"Grove","Grove",
"Groves","Groves",
"Grv","Grove",
"Grvs","Groves",
"Gtway","Gateway",
"Gtwy","Gateway",
"Harb","Harbor",
"Harbor","Harbor",
"Harbors","Harbors",
"Harbr","Harbor",
"Haven","Haven",
"Hbr","Harbor",
"Hbrs","Harbors",
"Heights","Heights",
"Highway","Highway",
"Highwy","Highway",
"Hill","Hill",
"Hills","Hills",
"Hiway","Highway",
"Hiwy","Highway",
"Hl","Hill",
"Hllw","Hollow",
"Hls","Hills",
"Hollow","Hollow",
"Hollows","Hollow",
"Holw","Hollow",
"Holws","Hollow",
"Hrbor","Harbor",
"Ht","Heights",
"Hts","Heights",
"Hvn","Haven",
"Hway","Highway",
"Hwy","Highway",
"Inlet","Inlet",
"Inlt","Inlet",
"Is","Island",
"Island","Island",
"Islands","Islands",
"Isle","Isle",
"Isles","Isle",
"Islnd","Island",
"Islnds","Islands",
"Iss","Islands",
"Jct","Junction",
"Jction","Junction",
"Jctn","Junction",
"Jctns","Junctions",
"Jcts","Junctions",
"Junction","Junction",
"Junctions","Junctions",
"Junctn","Junction",
"Juncton","Junction",
"Key","Key",
"Keys","Keys",
"Knl","Knoll",
"Knls","Knolls",
"Knol","Knoll",
"Knoll","Knoll",
"Knolls","Knolls",
"Ky","Key",
"Kys","Keys",
"Lake","Lake",
"Lakes","Lakes",
"Land","Land",
"Landing","Landing",
"Lane","Lane",
"Lck","Lock",
"Lcks","Locks",
"Ldg","Lodge",
"Ldge","Lodge",
"Lf","Loaf",
"Lgt","Light",
"Lgts","Lights",
"Light","Light",
"Lights","Lights",
"Lk","Lake",
"Lks","Lakes",
"Ln","Lane",
"Lndg","Landing",
"Lndng","Landing",
"Loaf","Loaf",
"Lock","Lock",
"Locks","Locks",
"Lodg","Lodge",
"Lodge","Lodge",
"Loop","Loop",
"Loops","Loop",
"Mall","Mall",
"Manor","Manor",
"Manors","Manors",
"Mdw","Meadow",
"Mdw","Meadows",
"Mdws","Meadows",
"Meadow","Meadow",
"Meadows","Meadows",
"Medows","Meadows",
"Mews","Mews",
"Mill","Mill",
"Mills","Mills",
"Mission","Mission",
"Missn","Mission",
"Ml","Mill",
"Mls","Mills",
"Mnr","Manor",
"Mnrs","Manors",
"Mnt","Mount",
"Mntain","Mountain",
"Mntn","Mountain",
"Mntns","Mountains",
"Motorway","Motorway",
"Mount","Mount",
"Mountain","Mountain",
"Mountains","Mountains",
"Mountin","Mountain",
"Msn","Mission",
"Mssn","Mission",
"Mt","Mount",
"Mtin","Mountain",
"Mtn","Mountain",
"Mtns","Mountains",
"Mtwy","Motorway",
"Nck","Neck",
"Neck","Neck",
"Opas","Overpass",
"Orch","Orchard",
"Orchard","Orchard",
"Orchrd","Orchard",
"Oval","Oval",
"Overpass","Overpass",
"Ovl","Oval",
"Park","Park",
"Park","Parks",
"Parks","Parks",
"Parkway","Parkway",
"Parkways","Parkways",
"Parkwy","Parkway",
"Pass","Pass",
"Passage","Passage",
"Path","Path",
"Paths","Path",
"Pike","Pike",
"Pikes","Pike",
"Pine","Pine",
"Pines","Pines",
"Pkway","Parkway",
"Pkwy","Parkway",
"Pkwy","Parkways",
"Pkwys","Parkways",
"Pky","Parkway",
"Pl","Place",
"Pl","Plain",
"Place","Place",
"Plain","Plain",
"Plains","Plains",
"Plaza","Plaza",
"Pln","Plain",
"Plns","Plains",
"Plz","Plaza",
"Plza","Plaza",
"Pne","Pine",
"Pnes","Pines",
"Point","Point",
"Points","Points",
"Port","Port",
"Ports","Ports",
"Pr","Prairie",
"Prairie","Prairie",
"Prk","Park",
"Prr","Prairie",
"Prt","Port",
"Prts","Ports",
"Psge","Passage",
"Pt","Point",
"Pts","Points",
"Rad","Radial",
"Radial","Radial",
"Radiel","Radial",
"Radl","Radial",
"Ramp","Ramp",
"Ranch","Ranch",
"Ranches","Ranch",
"Rapid","Rapid",
"Rapids","Rapids",
"Rd","Road",
"Rdg","Ridge",
"Rdge","Ridge",
"Rdgs","Ridges",
"Rds","Roads",
"Rest","Rest",
"Ridge","Ridge",
"Ridges","Ridges",
"Riv","River",
"River","River",
"Rivr","River",
"Rnch","Ranch",
"Rnchs","Ranch",
"Road","Road",
"Roads","Roads",
"Route","Route",
"Row","Row",
"Rpd","Rapid",
"Rpds","Rapids",
"Rst","Rest",
"Rte","Route",
"Rue","Rue",
"Run","Run",
"Rvr","River",
"Shl","Shoal",
"Shls","Shoals",
"Shoal","Shoal",
"Shoals","Shoals",
"Shoar","Shore",
"Shoars","Shores",
"Shore","Shore",
"Shores","Shores",
"Shr","Shore",
"Shrs","Shores",
"Skwy","Skyway",
"Skyway","Skyway",
"Smt","Summit",
"Spg","Spring",
"Spgs","Springs",
"Spng","Spring",
"Spngs","Springs",
"Spring","Spring",
"Springs","Springs",
"Sprng","Spring",
"Sprngs","Springs",
"Spur","Spur",
"Spur","Spurs",
"Spurs","Spurs",
"Sq","Square",
"Sqr","Square",
"Sqre","Square",
"Sqrs","Squares",
"Sqs","Squares",
"Squ","Square",
"Square","Square",
"Squares","Squares",
"St","Street",
"Sta","Station",
"Station","Station",
"Statn","Station",
"Stn","Station",
"Str","Street",
"Stra","Stravenue",
"Strav","Stravenue",
"Straven","Stravenue",
"Stravenue","Stravenue",
"Stravn","Stravenue",
"Stream","Stream",
"Street","Street",
"Streets","Streets",
"Streme","Stream",
"Strm","Stream",
"Strt","Street",
"Strvn","Stravenue",
"Strvnue","Stravenue",
"Sts","Streets",
"Sumit","Summit",
"Sumitt","Summit",
"Summit","Summit",
"Ter","Terrace",
"Terr","Terrace",
"Terrace","Terrace",
"Throughway","Throughway",
"Tpke","Turnpike",
"Trace","Trace",
"Traces","Trace",
"Track","Track",
"Tracks","Track",
"Trafficway","Trafficway",
"Trail","Trail",
"Trailer","Trailer",
"Trails","Trail",
"Trak","Track",
"Trce","Trace",
"Trfy","Trafficway",
"Trk","Track",
"Trks","Track",
"Trl","Trail",
"Trlr","Trailer",
"Trlrs","Trailer",
"Trls","Trail",
"Trnpk","Turnpike",
"Trwy","Throughway",
"Tunel","Tunnel",
"Tunl","Tunnel",
"Tunls","Tunnel",
"Tunnel","Tunnel",
"Tunnels","Tunnel",
"Tunnl","Tunnel",
"Turnabout","Turnabout",
"Turnaround","Turnaround",
"Turnpike","Turnpike",
"Turnpk","Turnpike",
"Un","Union",
"Underpass","Underpass",
"Union","Union",
"Unions","Unions",
"Uns","Unions",
"Upas","Underpass",
"Valley","Valley",
"Valleys","Valleys",
"Vally","Valley",
"Vdct","Viaduct",
"Via","Viaduct",
"Viadct","Viaduct",
"Viaduct","Viaduct",
"View","View",
"Views","Views",
"Vill","Village",
"Villag","Village",
"Village","Village",
"Villages","Villages",
"Ville","Ville",
"Villg","Village",
"Villiage","Village",
"Vis","Vista",
"Vist","Vista",
"Vista","Vista",
"Vl","Ville",
"Vlg","Village",
"Vlgs","Villages",
"Vlly","Valley",
"Vly","Valley",
"Vlys","Valleys",
"Vst","Vista",
"Vsta","Vista",
"Vw","View",
"Vws","Views",
"Walk","Walk",
"Walk","Walks",
"Walks","Walks",
"Wall","Wall",
"Way","Way",
"Ways","Ways",
"Well","Well",
"Wells","Wells",
"Wl","Well",
"Wls","Wells",
"Wy","Way",
"Xing","Crossing",
"Xrd","Crossroad",
"Xrds","Crossroads",
"zzz","zzz"
};





char *generate_numbers(char *buf,int length) {
int i;
for (i=0;i<length;i++) {
  *(buf++) = (random()>>2) % 10 + '0';
  }
*(buf++) = '\0';
return buf;
}


/* the random code
keep the ccards the same.  But change the CCV's 
0 or 1 or 2 for the first number - 2 means we cannot tell.
So every 0..... might be a 2.......
Then the ccv
4 numbers
01 or null
ddd   + mod to encrypt,  - mon to decrypt,  xor gets in the way
ddd
ddd
So we take base -> + dddbase + dddrand = new number
*/




void  gen_watermark_code(char *line,char *wm1, char *wm2, char *wm3,char *wm4) 
{
{
  char stype[20000];
  field(line,stype,19);
  int hi=street_suffix_size-1;
  int lo=0;
  int i;
  int flag=0;
  for (i=(hi+lo)/2;hi>=lo;i=(hi+lo)/2) {
    int c=strcmp(stype,street_suffixes[i*2]);
    if (c>0) {
      lo=i+1;
      }
    else if (c<0) {
      hi=i-1;
      } 
    else /*c==0*/ {
      if (strcmp(street_suffixes[i*2],street_suffixes[i*2+1])!=0) {
        flag=1;
        }
      break;
      }
    }

  if (flag) {
    wm1[0] = '0' + ((random()>>2) & 1);
    wm1[1]='\0';
    }
  else {
    wm1[0]='\0';
    }
  }
{
  char ccv[20000];
  wm2[0]='\0';
  wm3[0]='\0';
  wm4[0]='\0';
  field(line,ccv,53);
  int l;
  if (l=strlen(ccv)) {
    generate_numbers(wm2,l);
    }
  field(line,ccv,56);
  if (l=strlen(ccv)) {
    generate_numbers(wm3,l);
    }
  field(line,ccv,59);
  if (l=strlen(ccv)) {
    generate_numbers(wm4,l);
    }
  }
}





void watermark(char *in_line,
      char *outline,char *wm1,
      char *wm2,
      char *wm3, 
      char *wm4) {
char part_00_to_14[20000];
char full_address[20000];
char part_16_to_18[20000];
char street_type[20000];
char part_20_to_52[20000];
char cc1_ccv[20000];
char part_54_to_55[20000];
char cc2_ccv[20000];
char part_57_to_58[20000];
char cc3_ccv[20000];
char part_60_to_69[20000]; /* we clip it, watermark info does not come out */
int w1 = atoi(wm1);
int w2 = atoi(wm2);
int w3 = atoi(wm3);
int w4 = atoi(wm4);
int wi1= (wm1[0]);
int wi2= strlen(wm2);
int wi3= strlen(wm3);
int wi4= strlen(wm4);
char *e=outline;
fieldspan(in_line,part_00_to_14,0,14,1);
field(in_line,full_address,15);
fieldspan(in_line,part_16_to_18,16,18,1);
field(in_line,street_type,19);
fieldspan(in_line,part_20_to_52,20,52,1);
field(in_line,cc1_ccv,53);
fieldspan(in_line,part_54_to_55,54,55,1);
field(in_line,cc2_ccv,56);
fieldspan(in_line,part_57_to_58,57,58,1);
field(in_line,cc3_ccv,59);
fieldspan(in_line,part_60_to_69,60,69,1);


if (wi1) { /* if we are doing the first watermark */
  int hi=street_suffix_size-1;
  int lo=0;
  int i;
  int flag=0;
  for (i=(hi+lo)/2;hi>=lo;i=(hi+lo)/2) {
    int c=strcmp(street_type,street_suffixes[i*2]);
    if (c>0) {
      lo=i+1;
      }
    else if (c<0) {
      hi=i-1;
      } 
    else /*c==0*/ {
      flag=1; /* flag indicates a rebuild */
      break;
      }
    } /* for binary search */
    
  if (flag) {
    if (w1) w1=1;
    char thenumber[2000];
    char thestreet_direction[2000];
    char thestreet_name[2000];
    char thestreet_type[2000];
    char thestreet_direction2[2000];
    char thespanish_street_type[2000];
    char thesubdivision_type[2000];
    char thesubdivision_number[2000];

      
    field(in_line,thenumber,16);
    field(in_line,thestreet_direction,17);
    field(in_line,thestreet_name,18);
/*    field(inline,thestreet_type,19);*/
    /* first things first - set street_type*/
    initcap(thestreet_type,street_suffixes[i*2+w1]);
    field(in_line,thestreet_direction2,38);
    field(in_line,thespanish_street_type,37);
    field(in_line,thesubdivision_type,20);
    field(in_line,thesubdivision_number,21);
      
      
    /* Ok - rebuild the damn full address with the watermark - this is mirroed in name.sno back at section ha */
    char theaddress[20000];
    theaddress[0]='\0';
    char *e = theaddress;
    char *comma;;
    comma="";
    if (thenumber[0]) {
        sprintf(e,"%s%s",comma,thenumber);
	e += strlen(e);
	comma = " ";
	}
    if (thestreet_direction[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction);
	e += strlen(e);
	comma = " ";
        }
    if (thespanish_street_type[0]) {
        sprintf(e,"%s%s",comma,thespanish_street_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_name[0]) {
        sprintf(e,"%s%s",comma,thestreet_name);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_type[0]) {
        sprintf(e,"%s%s",comma,thestreet_type);
        e += strlen(e);
	comma = " ";
	}
    if (thestreet_direction2[0]) {
        sprintf(e,"%s%s",comma,thestreet_direction2);
        e += strlen(e);
	comma = " ";
	}
    if (thesubdivision_type[0]) {
        sprintf(e,"%s%s",comma,thesubdivision_type);
        e += strlen(e);
	comma = " ";
	}
    if (thesubdivision_number[0]) {
        sprintf(e,"%s%s",comma,thesubdivision_number);
        e += strlen(e);
	comma = " ";
	}
    strcpy(full_address,theaddress);
    } /* if we are changing the street type */
  } /* if we are doing the first watermark */
    
if (wi2)  { /* watermark the ccv */
  int ccv = atoi(cc1_ccv);
  int m;
  if (wi2<=3) m=1000;
  else m=10000;
  ccv = (ccv+w2) % m;
  if (wi2<=3) 
    sprintf(cc1_ccv,"%03d",ccv);
  else 
    sprintf(cc1_ccv,"%04d",ccv); 
  }
if (wi3)  { /* watermark the ccv */
  int m;
  if (wi3<=3) m=1000;
  else m=10000;
  int ccv = atoi(cc2_ccv);
  ccv = (ccv+w3) % m;
  if (wi3<=3) 
  sprintf(cc2_ccv,"%03d",ccv);
  else 
    sprintf(cc2_ccv,"%04d",ccv); 
  }
if (wi4)  { /* watermark the ccv */
  int m;
  if (wi4<=3) m=1000;
  else m=10000;
  int ccv = atoi(cc3_ccv);
  ccv = (ccv+w4) % 10000;
  if (wi4<=3)
  sprintf(cc3_ccv,"%03d",ccv);
  else
  sprintf(cc3_ccv,"%04d",ccv);
  }
  
sprintf(outline,"%s%s|%s%s|%s%s|%s%s|%s%s|%s",part_00_to_14,
   full_address,part_16_to_18,
   street_type,part_20_to_52,cc1_ccv,part_54_to_55,
   cc2_ccv,part_57_to_58,cc3_ccv,part_60_to_69);

strcpy(wm2,cc1_ccv);
strcpy(wm3,cc2_ccv);
strcpy(wm4,cc3_ccv);

}
