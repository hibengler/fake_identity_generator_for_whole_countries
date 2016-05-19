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
/* Make dl
A very tough problem for a little number 
We need the state code and the dl as a full idnetification.



also look at http://www.employmentscreens.net/driving.html

Alabama - 1-7 numbers  - order by birthdate, or ssn?
Alaska - 1-7 numbers - order by birthdate, or ssn?
Arizona - 1 letter, 3-6 number or 2 letter 3-5 numb, or 1 letter 8 num, or ssn?
Arkansas - 8 or 9 num
California - 1 letter 7 num
colorado - 1-2 letter, 1-6 number
Conneticut - 9 number
deleware - 1-6 number
Dist of Columbia - SSN
Florida - 1 letter, 12 number,
Georgia, 7-9 number
hawaii - 9 number
idaho - ssn
Illinois - 1 letter 11 num
Indiana - 1 letter, 9 number, or 9 or 10 number
iowa - 3 num, 2 ltr, 4 num, or ssn
kansas - 6_alphanum
kentucky - 1 letter, 12 number, or ssn
louisiana - 9 number
maine - 7 number
maryland - 1 letter, 12 number
mass - ssn
michigan - 1 letter 12 num
minnesota - 1 letter 12 num
mississippi - 9 num or ssn
missouri - 9 number or ssn
montana - 1 letter 6 num, or ssn
nebraska - 1 letter 3-8 number
nevada - ssn
new hampshire - 2 num, 3 letter, 5 num
new jersey - 1 letter 14 num
new mexico - 8 num or ssn
new york - 1 letter 18 num
north carolina 1-7 num or 8 num
north dakota - 9 num
ohio - 2 letter 6 num or ssn
oklahoma - 9 num
oregon - 1-7 num
pennslvaneia - 6-8 num
rhode idland - 7 num
south carolina - 7 num
south dakota - 7 num
tenessee - 7 or 8 num
texas - 8 num
utah - 1-9 alphanum
vermont - 7-8 num
virginaa - 9 num or 1 letter 8 num
washington - 12 alphanum
west virginia - 2 aqlphanum 5 num
wisconsin 1 letter 13 num
wyoming - 1-10 num



from a different source: http://www.pimall.com/nais/n.dldecod.html

AK - driver's #'s sequentially issued. 7 digits
AL - driver's #'s sequentially issued. 7 digits
AR - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
AZ - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
CA - issues an 8 character alpha-numeric DL#
CO - issues a license # of up to 7 characters.
CT - issues a 9 digit #
DC - uses driver's SSN
DE - issues a 1 to 7 digit sequentially issued #
FL - issues a 13 character alpha-numeric #
GA - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
HI - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
IA - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
ID - issues a 9 digit #
IL - issues a 12 or 13 character alpha-numeric #
IN - issues a 10 digit #
KS - uses driver's SSN. Will assign a nine digit sequentially issued # upon
request
Older licenses consist of six alpha numeric characters
KY - uses driver's SSN. Will assign a nine or 10 digit sequentially issued
# upon request
LA - issues a 9 digit #
MA - uses driver's SSN. Will assign a nine character sequentially issued
alpha-numeric # upon request
MD - issues a 13 character alpha-numeric #
ME - issues a 7 digit numeric #
MI - issues a 13 character alpha-numeric #
MN - issues a 13 character alpha-numeric #
MO - uses driver's SSN. Will assign a sequentially issued # upon request
MS - uses driver's SSN. Will assign a nine digit sequentially issued numeric
# upon request
MT - uses driver's SSN. Will assign a sequentially issued # upon request
NC - issues a 7 digit numeric #
ND - uses driver's SSN. Will assign a sequentially issued # for
non-commercial drivers upon request
NE - issues a 9 character alpha numeric #
NH - issues a 10 character alpha numeric #
NJ - issues a 15 character alpha numeric #
NM - issues a 9 digit numeric #. Older licenses use an 8 digit #
NV - issues a 12 character alpha numeric #
NY - issues a 9 character alpha numeric #
OH - issues a 8 character alpha numeric #
OK - uses driver's SSN. Will assign a nine digit sequentially issued numeric
# upon request
OR - issues a 7 digit numeric #
PA - issues a 8 digit numeric #
RI - issues a 7 digit numeric #
SC - issues a 9 digit numeric #
SD - uses driver's SSN.
TN - issues an 8 digit numeric #
TX - issues an 8 digit numeric #
UT - issues a 4 to 8 digit numeric #
VA - uses driver's SSN. Will assign a sequentially issued # upon request
VT - issues an 8 digit numeric # or an 8 character alpha numeric #
WA - issues a 14 character alpha-numeric #
WI - issues a 14 character alpha-numeric #
WV - issues a 7 digit numeric #
WY - issues a 9 digit numeric #

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "soundex.h"
#include "uthash.h"
#include "util.h"


struct dl_struct {
char *value;
UT_hash_handle hh;
};



char z[20000];

char dl[20000];

char the_state[20000]; /* holds the current state for each line */




char *fmr_first_male_string[] = {
  "Albert","Arthur","Bernard","Carl",
  "Charles","Donald","Edward","Frank",
  "George","Harold","Harry","Henry",
  "James","John","Joseph","Martin",
  "Marvin","Melvin","Paul","Richard",
  "Robert","Thomas","Walter","William",NULL};
int fmr_first_male_number[] = {
  20,40,80,120,
  140,180,220,260,
  300,340,360,380,
  440,460,480,560,
  580,600,680,740,
  760,820,900,920};

char *fmr_first_female_string[] = {
"Alice","Ann","Anna","Anne","Annie",
"Bette","Bettie","Betty","Catherine",
"Clara","Dorothy","Elizabeth",
"Florence","Grace","Harriet",
"Hazel","Helen","Jane","Jayne",
"Jean","Joan","Mary","Mildred",
"Patricia","Ruby","Ruth","Thelma",
"Wanda","Wilma",NULL
};


int fmr_first_female_number[] = {
      20,40,40,40,40,
      80,80,80,120,
      140,180,220,
      260,300,340,
      360,380,440,440,
      460,480,580,600,
      680,740,760,820,
      900,920};

      
char *fmr_first_init_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int fmr_first_init_number[] = {
 0,60,100,160,200,240,
 280,320,400,420,500,520,
 540,620,640,660,700,720,
 780,800,840,860,880,940,
 960,980};
 
char *fmr_middle_init_char = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int fmr_middle_init_number[] = {
0,1,2,3,4,
5,6,7,8,
9,10,11,12,
13,14,14,15,15,16,
17,18,18,18,19,19,19,19};

  
    
        
int simple_string_search(char *string_list[],int value_list[],char *search_value) {
int i=0;
char *sl;
while (sl=string_list[i]) {
  if (strcmp(search_value,sl)==0) return(value_list[i]);
  i++;
  }
return(-1);
}

int simple_char_search(char char_list[],int value_list[],char search_value) {
int i=0;
char sl;
while (sl=char_list[i]) {
  if (sl==search_value) return value_list[i];
  i++;
  }
return(-1);
}
  
int dlfirstmiddle_encode(char *infirst,char *inmiddle) {
char first[20000];
char middle[20000];
initcap(first,infirst);
initcap(middle,inmiddle);
int num;
int num1;
if (first[0]=='\0') {strcpy(first,"X");} /* hack  see 1000003170 */
num1 = simple_string_search(fmr_first_male_string,fmr_first_male_number,first);
if (num1==-1)
  num1 = simple_string_search(fmr_first_female_string,fmr_first_female_number,first);
if (num1==-1)
  num1 = simple_char_search(fmr_first_init_char,fmr_first_female_number,first[0]);
if (num1==-1) return(num1);
num = num1;
char x=middle[0];
if (x=='\0') x=' ';
num1 = simple_char_search(fmr_middle_init_char,fmr_middle_init_number,x);
if (num1==-1) num1=0;
num = num + num1;
return num;
}


struct dl_struct *license_used= NULL;



int license_in_use(char * state,char *code) {
struct dl_struct *c;
char thelicense[20000];
strcpy(thelicense,state);
strcat(thelicense,code);
HASH_FIND_STR(license_used,thelicense,c);
if (c) return(1);
return 0;
}


int use_license(char * state,char *code) {
struct dl_struct *c;
char thelicense[20000];
int l;
strcpy(thelicense,state);
strcat(thelicense,code);
l=strlen(thelicense);
c = (struct dl_struct *) malloc(sizeof(struct dl_struct) + (l+1) * sizeof(char));
if (!c) {
  fprintf(stderr,"error mallocing license %s\n",thelicense);
  exit(-1);
  }
c->value = (char *)(c+1);
strcpy(c->value,thelicense);
HASH_ADD_KEYPTR(hh,license_used,c->value,l,c);
if (c) return(1);
return 0;
}


int month_day_gender(
 int month,int day,
 char *gender,
 int female_add,
 int month_mult) {
int dateno;
dateno = (month-1) * month_mult + day;
if (gender[0]=='F') {
  dateno += female_add;
  }
return dateno;
}



char *generate_numbers(char *buf,int length) {
int i;
for (i=0;i<length;i++) {
  if (i || (length==1)) {
    *(buf++) = (random()>>2) % 10 + '0';
    }
  else {
    *(buf++) = (random()>>2) % 9 + '1';
    }
  }
*(buf++) = '\0';
}


char *generate_letters(char *buf, int length) {
int i;
for (i=0;i<length;i++) {
  *(buf++) = (random()>>2) % 25 + 'A';
  }
*(buf++) = '\0';
}


char *generate_alphanum(char *buf,int length) {
int i;
for (i=0;i<length;i++) {
  int v;
  if (i || (length==1)) {
    v= (random()>>2) % 36;
    }
  else {
    v = (random()>>2) % 35 + 1;
    }
  if (v<10) {
    *(buf++) = v+'0';
    }
  else {
    *(buf++) = v-10+'A';
    }
  }
*(buf++) = '\0';
}






#define FNAME_CODELENGTH 973
char *stupid_fname_codes[FNAME_CODELENGTH] = {
"a",
"aa",
"ab",
"ac",
"ad",
"ae",
"af",
"ag",
"ah",
"ai",
"aj",
"ak",
"al",
"ala",
"alb",
"alc",
"ald",
"ale",
"alf",
"alg",
"alh",
"ali",
"alj",
"alk",
"all",
"alm",
"aln",
"alo",
"alp",
"alq",
"alr",
"als",
"alt",
"alu",
"alv",
"alw",
"alx",
"aly",
"alz",
"am",
"an",
"ao",
"ap",
"aq",
"ar",
"as",
"at",
"au",
"av",
"aw",
"ax",
"ay",
"az",
"b",
"ba",
"bb",
"bc",
"bd",
"be",
"bf",
"bg",
"bh",
"bi",
"bj",
"bk",
"bl",
"bm",
"bn",
"bo",
"bp",
"bq",
"br",
"bs",
"bt",
"bu",
"bv",
"bw",
"bx",
"by",
"bz",
"c",
"ca",
"cb",
"cc",
"cd",
"ce",
"cf",
"cg",
"ch",
"ci",
"cj",
"ck",
"cl",
"cm",
"cn",
"co",
"cp",
"cq",
"cr",
"cs",
"ct",
"cu",
"cv",
"cw",
"cx",
"cy",
"cz",
"d",
"da",
"db",
"dc",
"dd",
"de",
"df",
"dg",
"dh",
"di",
"dj",
"dk",
"dl",
"dm",
"dn",
"do",
"dp",
"dq",
"dr",
"ds",
"dt",
"du",
"dv",
"dw",
"dx",
"dy",
"dz",
"e",
"ea",
"eb",
"ec",
"ed",
"eda",
"edb",
"edc",
"edd",
"ede",
"edf",
"edg",
"edh",
"edi",
"edj",
"edk",
"edl",
"edm",
"edn",
"edo",
"edp",
"edq",
"edr",
"eds",
"edt",
"edu",
"edv",
"edw",
"edward",
"edx",
"edy",
"edz",
"ee",
"ef",
"eg",
"eh",
"ei",
"ej",
"ek",
"el",
"ela",
"elb",
"elc",
"eld",
"ele",
"elf",
"elg",
"elh",
"eli",
"elizabeth",
"elj",
"elk",
"ell",
"ellen",
"elm",
"eln",
"elo",
"elp",
"elq",
"elr",
"els",
"elt",
"elu",
"elv",
"elw",
"elx",
"ely",
"elz",
"em",
"en",
"eo",
"ep",
"eq",
"er",
"es",
"et",
"eu",
"ev",
"ew",
"ex",
"ey",
"ez",
"f",
"fa",
"fb",
"fc",
"fd",
"fe",
"ff",
"fg",
"fh",
"fi",
"fj",
"fk",
"fl",
"fm",
"fn",
"fo",
"fp",
"fq",
"fr",
"fs",
"ft",
"fu",
"fv",
"fw",
"fx",
"fy",
"fz",
"g",
"ga",
"gb",
"gc",
"gd",
"ge",
"gf",
"gg",
"gh",
"gi",
"gj",
"gk",
"gl",
"gm",
"gn",
"go",
"gp",
"gq",
"gr",
"gs",
"gt",
"gu",
"gv",
"gw",
"gx",
"gy",
"gz",
"h",
"ha",
"hb",
"hc",
"hd",
"he",
"henry",
"hf",
"hg",
"hh",
"hi",
"hj",
"hk",
"hl",
"hm",
"hn",
"ho",
"hp",
"hq",
"hr",
"hs",
"ht",
"hu",
"hv",
"hw",
"hx",
"hy",
"hz",
"i",
"ia",
"ib",
"ic",
"id",
"ie",
"if",
"ig",
"ih",
"ii",
"ij",
"ik",
"il",
"im",
"in",
"io",
"ip",
"iq",
"ir",
"is",
"it",
"iu",
"iv",
"iw",
"ix",
"iy",
"iz",
"j",
"ja",
"jaa",
"jab",
"jac",
"jad",
"jae",
"jaf",
"jag",
"jah",
"jai",
"jaj",
"jak",
"jal",
"jam",
"james",
"jan",
"jao",
"jap",
"jaq",
"jar",
"jas",
"jat",
"jau",
"jav",
"jaw",
"jax",
"jay",
"jaz",
"jb",
"jc",
"jd",
"je",
"jea",
"jeb",
"jec",
"jed",
"jee",
"jef",
"jeg",
"jeh",
"jei",
"jej",
"jek",
"jel",
"jem",
"jen",
"jeo",
"jep",
"jeq",
"jer",
"jes",
"jet",
"jeu",
"jev",
"jew",
"jex",
"jey",
"jez",
"jf",
"jg",
"jh",
"ji",
"jj",
"jk",
"jl",
"jm",
"jn",
"jo",
"joa",
"job",
"joc",
"jod",
"joe",
"jof",
"jog",
"joh",
"john",
"joi",
"joj",
"jok",
"jol",
"jom",
"jon",
"joo",
"jop",
"joq",
"jor",
"jos",
"joseph",
"jot",
"jou",
"jov",
"jow",
"jox",
"joy",
"joz",
"jp",
"jq",
"jr",
"js",
"jt",
"ju",
"jv",
"jw",
"jx",
"jy",
"jz",
"k",
"ka",
"kb",
"kc",
"kd",
"ke",
"kf",
"kg",
"kh",
"ki",
"kj",
"kk",
"kl",
"km",
"kn",
"ko",
"kp",
"kq",
"kr",
"ks",
"kt",
"ku",
"kv",
"kw",
"kx",
"ky",
"kz",
"l",
"la",
"lb",
"lc",
"ld",
"le",
"lea",
"leb",
"lec",
"led",
"lee",
"lef",
"leg",
"leh",
"lei",
"lej",
"lek",
"lel",
"lem",
"len",
"leo",
"lep",
"leq",
"ler",
"les",
"let",
"leu",
"lev",
"lew",
"lex",
"ley",
"lez",
"lf",
"lg",
"lh",
"li",
"lj",
"lk",
"ll",
"lm",
"ln",
"lo",
"loa",
"lob",
"loc",
"lod",
"loe",
"lof",
"log",
"loh",
"loi",
"loj",
"lok",
"lol",
"lom",
"lon",
"loo",
"lop",
"loq",
"lor",
"los",
"lot",
"lou",
"lov",
"low",
"lox",
"loy",
"loz",
"lp",
"lq",
"lr",
"ls",
"lt",
"lu",
"lv",
"lw",
"lx",
"ly",
"lz",
"m",
"ma",
"maa",
"mab",
"mac",
"mad",
"mae",
"maf",
"mag",
"mah",
"mai",
"maj",
"mak",
"mal",
"mam",
"man",
"mao",
"map",
"maq",
"mar",
"margaret",
"mary",
"mas",
"mat",
"mau",
"mav",
"maw",
"max",
"may",
"maz",
"mb",
"mc",
"md",
"me",
"mf",
"mg",
"mh",
"mi",
"mj",
"mk",
"ml",
"mm",
"mn",
"mo",
"mp",
"mq",
"mr",
"ms",
"mt",
"mu",
"mv",
"mw",
"mx",
"my",
"mz",
"n",
"na",
"nb",
"nc",
"nd",
"ne",
"nf",
"ng",
"nh",
"ni",
"nj",
"nk",
"nl",
"nm",
"nn",
"no",
"np",
"nq",
"nr",
"ns",
"nt",
"nu",
"nv",
"nw",
"nx",
"ny",
"nz",
"o",
"oa",
"ob",
"oc",
"od",
"oe",
"of",
"og",
"oh",
"oi",
"oj",
"ok",
"ol",
"om",
"on",
"oo",
"op",
"oq",
"or",
"os",
"ot",
"ou",
"ov",
"ow",
"ox",
"oy",
"oz",
"p",
"pa",
"pb",
"pc",
"pd",
"pe",
"pf",
"pg",
"ph",
"pi",
"pj",
"pk",
"pl",
"pm",
"pn",
"po",
"pp",
"pq",
"pr",
"ps",
"pt",
"pu",
"pv",
"pw",
"px",
"py",
"pz",
"q",
"qa",
"qb",
"qc",
"qd",
"qe",
"qf",
"qg",
"qh",
"qi",
"qj",
"qk",
"ql",
"qm",
"qn",
"qo",
"qp",
"qq",
"qr",
"qs",
"qt",
"qu",
"qv",
"qw",
"qx",
"qy",
"qz",
"r",
"ra",
"rb",
"rc",
"rd",
"re",
"rf",
"rg",
"rh",
"ri",
"rj",
"rk",
"rl",
"rm",
"rn",
"ro",
"robert",
"rp",
"rq",
"rr",
"rs",
"rt",
"ru",
"rv",
"rw",
"rx",
"ry",
"rz",
"s",
"sa",
"sb",
"sc",
"sd",
"se",
"sf",
"sg",
"sh",
"si",
"sj",
"sk",
"sl",
"sm",
"sn",
"so",
"sp",
"sq",
"sr",
"ss",
"st",
"su",
"sv",
"sw",
"sx",
"sy",
"sz",
"t",
"ta",
"tb",
"tc",
"td",
"te",
"tf",
"tg",
"th",
"ti",
"tj",
"tk",
"tl",
"tm",
"tn",
"to",
"tp",
"tq",
"tr",
"ts",
"tt",
"tu",
"tv",
"tw",
"tx",
"ty",
"tz",
"u",
"ua",
"ub",
"uc",
"ud",
"ue",
"uf",
"ug",
"uh",
"ui",
"uj",
"uk",
"ul",
"um",
"un",
"uo",
"up",
"uq",
"ur",
"us",
"ut",
"uu",
"uv",
"uw",
"ux",
"uy",
"uz",
"v",
"va",
"vb",
"vc",
"vd",
"ve",
"vf",
"vg",
"vh",
"vi",
"vj",
"vk",
"vl",
"vm",
"vn",
"vo",
"vp",
"vq",
"vr",
"vs",
"vt",
"vu",
"vv",
"vw",
"vx",
"vy",
"vz",
"w",
"wa",
"wb",
"wc",
"wd",
"we",
"wf",
"wg",
"wh",
"wi",
"wia",
"wib",
"wic",
"wid",
"wie",
"wif",
"wig",
"wih",
"wii",
"wij",
"wik",
"wil",
"william",
"wim",
"win",
"wio",
"wip",
"wiq",
"wir",
"wis",
"wit",
"wiu",
"wiv",
"wiw",
"wix",
"wiy",
"wiz",
"wj",
"wk",
"wl",
"wm",
"wn",
"wo",
"wp",
"wq",
"wr",
"ws",
"wt",
"wu",
"wv",
"ww",
"wx",
"wy",
"wz",
"x",
"xa",
"xb",
"xc",
"xd",
"xe",
"xf",
"xg",
"xh",
"xi",
"xj",
"xk",
"xl",
"xm",
"xn",
"xo",
"xp",
"xq",
"xr",
"xs",
"xt",
"xu",
"xv",
"xw",
"xx",
"xy",
"xz",
"y",
"ya",
"yb",
"yc",
"yd",
"ye",
"yf",
"yg",
"yh",
"yi",
"yj",
"yk",
"yl",
"ym",
"yn",
"yo",
"yp",
"yq",
"yr",
"ys",
"yt",
"yu",
"yv",
"yw",
"yx",
"yy",
"yz",
"z",
"za",
"zb",
"zc",
"zd",
"ze",
"zf",
"zg",
"zh",
"zi",
"zj",
"zk",
"zl",
"zm",
"zn",
"zo",
"zp",
"zq",
"zr",
"zs",
"zt",
"zu",
"zv",
"zw",
"zx",
"zy",
"zz",
};

int stupid_fname_numbers[FNAME_CODELENGTH] = {
27,
28,
29,
30,
31,
32,
33,
34,
35,
36,
37,
38,
39,
40,
41,
42,
43,
44,
45,
46,
47,
48,
49,
50,
51,
52,
53,
54,
55,
56,
57,
58,
59,
60,
61,
62,
63,
64,
65,
66,
67,
68,
69,
70,
71,
72,
73,
74,
75,
76,
77,
78,
79,
80,
81,
82,
83,
84,
85,
86,
87,
88,
89,
90,
91,
92,
93,
94,
95,
96,
97,
98,
99,
100,
101,
102,
103,
104,
105,
106,
107,
108,
109,
110,
111,
112,
113,
114,
115,
116,
117,
118,
119,
120,
121,
122,
123,
124,
125,
126,
127,
128,
129,
130,
131,
132,
133,
134,
135,
136,
137,
138,
139,
140,
141,
142,
143,
144,
145,
146,
147,
148,
149,
150,
151,
152,
153,
154,
155,
156,
157,
158,
159,
160,
161,
162,
163,
164,
165,
166,
167,
168,
169,
170,
171,
172,
173,
174,
175,
176,
177,
178,
179,
180,
181,
182,
183,
184,
185,
186,
187,
188,
189,
190,
191,
192,
193,
194,
195,
196,
197,
198,
199,
200,
201,
202,
203,
204,
205,
206,
207,
208,
209,
210,
211,
212,
213,
214,
215,
216,
217,
218,
219,
220,
221,
222,
223,
224,
225,
226,
227,
228,
229,
230,
231,
232,
233,
234,
235,
236,
237,
238,
239,
240,
241,
242,
243,
244,
245,
246,
247,
248,
249,
250,
251,
252,
253,
254,
255,
256,
257,
258,
259,
260,
261,
262,
263,
264,
265,
266,
267,
268,
269,
270,
271,
272,
273,
274,
275,
276,
277,
278,
279,
280,
281,
282,
283,
284,
285,
286,
287,
288,
289,
290,
291,
292,
293,
294,
295,
296,
297,
298,
299,
300,
301,
302,
303,
304,
305,
306,
307,
308,
309,
310,
311,
312,
313,
314,
315,
316,
317,
318,
319,
320,
321,
322,
323,
324,
325,
326,
327,
328,
329,
330,
331,
332,
333,
334,
335,
336,
337,
338,
339,
340,
341,
342,
343,
344,
345,
346,
347,
348,
349,
350,
351,
352,
353,
354,
355,
356,
357,
358,
359,
360,
361,
362,
363,
364,
365,
366,
367,
368,
369,
370,
371,
372,
373,
374,
375,
376,
377,
378,
379,
380,
381,
382,
383,
384,
385,
386,
387,
388,
389,
390,
391,
392,
393,
394,
395,
396,
397,
398,
399,
400,
401,
402,
403,
404,
405,
406,
407,
408,
409,
410,
411,
412,
413,
414,
415,
416,
417,
418,
419,
420,
421,
422,
423,
424,
425,
426,
427,
428,
429,
430,
431,
432,
433,
434,
435,
436,
437,
438,
439,
440,
441,
442,
443,
444,
445,
446,
447,
448,
449,
450,
451,
452,
453,
454,
455,
456,
457,
458,
459,
460,
461,
462,
463,
464,
465,
466,
467,
468,
469,
470,
471,
472,
473,
474,
475,
476,
477,
478,
479,
480,
481,
482,
483,
484,
485,
486,
487,
488,
489,
490,
491,
492,
493,
494,
495,
496,
497,
498,
499,
500,
501,
502,
503,
504,
505,
506,
507,
508,
509,
510,
511,
512,
513,
514,
515,
516,
517,
518,
519,
520,
521,
522,
523,
524,
525,
526,
527,
528,
529,
530,
531,
532,
533,
534,
535,
536,
537,
538,
539,
540,
541,
542,
543,
544,
545,
546,
547,
548,
549,
550,
551,
552,
553,
554,
555,
556,
557,
558,
559,
560,
561,
562,
563,
564,
565,
566,
567,
568,
569,
570,
571,
572,
573,
574,
575,
576,
577,
578,
579,
580,
581,
582,
583,
584,
585,
586,
587,
588,
589,
590,
591,
592,
593,
594,
595,
596,
597,
598,
599,
600,
601,
602,
603,
604,
605,
606,
607,
608,
609,
610,
611,
612,
613,
614,
615,
616,
617,
618,
619,
620,
621,
622,
623,
624,
625,
626,
627,
628,
629,
630,
631,
632,
633,
634,
635,
636,
637,
638,
639,
640,
641,
642,
643,
644,
645,
646,
647,
648,
649,
650,
651,
652,
653,
654,
655,
656,
657,
658,
659,
660,
661,
662,
663,
664,
665,
666,
667,
668,
669,
670,
671,
672,
673,
674,
675,
676,
677,
678,
679,
680,
681,
682,
683,
684,
685,
686,
687,
688,
689,
690,
691,
692,
693,
694,
695,
696,
697,
698,
699,
700,
701,
702,
703,
704,
705,
706,
707,
708,
709,
710,
711,
712,
713,
714,
715,
716,
717,
718,
719,
720,
721,
722,
723,
724,
725,
726,
727,
728,
729,
730,
731,
732,
733,
734,
735,
736,
737,
738,
739,
740,
741,
742,
743,
744,
745,
746,
747,
748,
749,
750,
751,
752,
753,
754,
755,
756,
757,
758,
759,
760,
761,
762,
763,
764,
765,
766,
767,
768,
769,
770,
771,
772,
773,
774,
775,
776,
777,
778,
779,
780,
781,
782,
783,
784,
785,
786,
787,
788,
789,
790,
791,
792,
793,
794,
795,
796,
797,
798,
799,
800,
801,
802,
803,
804,
805,
806,
807,
808,
809,
810,
811,
812,
813,
814,
815,
816,
817,
818,
819,
820,
821,
822,
823,
824,
825,
826,
827,
828,
829,
830,
831,
832,
833,
834,
835,
836,
837,
838,
839,
840,
841,
842,
843,
844,
845,
846,
847,
848,
849,
850,
851,
852,
853,
854,
855,
856,
857,
858,
859,
860,
861,
862,
863,
864,
865,
866,
867,
868,
869,
870,
871,
872,
873,
874,
875,
876,
877,
878,
879,
880,
881,
882,
883,
884,
885,
886,
887,
888,
889,
890,
891,
892,
893,
894,
895,
896,
897,
898,
899,
900,
901,
902,
903,
904,
905,
906,
907,
908,
909,
910,
911,
912,
913,
914,
915,
916,
917,
918,
919,
920,
921,
922,
923,
924,
925,
926,
927,
928,
929,
930,
931,
932,
933,
934,
935,
936,
937,
938,
939,
940,
941,
942,
943,
944,
945,
946,
947,
948,
949,
950,
951,
952,
953,
954,
955,
956,
957,
958,
959,
960,
961,
962,
963,
964,
965,
966,
967,
968,
969,
970,
971,
972,
973,
974,
975,
976,
977,
978,
979,
980,
981,
982,
983,
984,
985,
986,
987,
988,
989,
990,
991,
992,
993,
994,
995,
996,
997,
998,
999,
};


static int stupid_search(char *table[],int size,char *searchy,
char *plast_unmatched_character) {
/* search for the name, starting with the first character,  then 
match the subsequent characters until we have filled it up.
*/
int lo;
int hi;
int mid;
int digits;
int l;
int lastmatch=-1;
char searchy2[20000];
l=strlen(searchy);
digits=0;
*plast_unmatched_character = '\0';
while (digits<=l) {
  *plast_unmatched_character = searchy2[digits]=searchy[digits];
  digits++;
  searchy2[digits]='\0';
  hi=size-1;
  lo=0;
  
  while (hi>=lo) {
    mid=(hi+lo)>>1;
    int comp = strcmp(table[mid],searchy2);
//    fprintf(stderr,"%d < %d < %d  (%s) - %s\n",lo,mid,hi,table[mid],searchy2);
    if (comp==0) {
      lastmatch=mid;
      break;
      }
    else if (comp>0) {
      hi=mid-1;
      }
    else { /* comp<0*/
      lo=mid+1;
      }
    }
  if (hi<lo) return lastmatch;
  }
*plast_unmatched_character = '\0'; /* full match! yeah*/
return lastmatch;
}


int middle_numbers[26] = {
1,2,3,4,5,
6,7,8,9,10,
11,12,13,14,15,
16,17,18,19,20,
21,22,23,24,25,
26};


/* used by maryland, michgan, and other states */
void encode_first_middle(char *first,char *middle,int *pfirst_code,
  int *pmiddle_code) {
  int fully_coded_flag;
char last_unmatched_character;
char nfirst[20000],nmiddle[20000];
lower(nfirst,first);

/* hack because someone does nothave a first name - fuck!*/
if (nfirst[0]=='\0') {
  nfirst[0]='a';
  nfirst[1]='\0';
  }
  
lower(nmiddle,middle);
int id=stupid_search(stupid_fname_codes,FNAME_CODELENGTH,nfirst,
                    &last_unmatched_character);
if (id==-1) {
  fprintf(stderr,"Real bad first name search %s,%s 	%s\n",first,middle,z);
  exit(-1);
  }
*pfirst_code = stupid_fname_numbers[id];
if (nmiddle[0] == '\0') {
  nmiddle[0] = last_unmatched_character;
  nmiddle[1]='\0';
  if (nmiddle[0] == '\0') { /* no unmatched character */
    *pmiddle_code = 000;
    }
  else if ((nmiddle[0] <'a')||(nmiddle[0] >'z'))
    *pmiddle_code = 000;
  else
    *pmiddle_code = middle_numbers[nmiddle[0]-'a'];
  }
else {
  int id=stupid_search(stupid_fname_codes,FNAME_CODELENGTH,nmiddle,
                    &last_unmatched_character);
  if (id==-1) {
    fprintf(stderr,"Real bad middle name search %s,%s 	%s\n",first,middle,z);
    exit(-1);
    }
  *pmiddle_code = stupid_fname_numbers[id];
  }
}






static int codemonth_01[] = {
0, // 00 
2, // 01 
7, // 02 
10, // 03 
12, // 04 
17, // 05 
20, // 06 
22, // 07 
25, // 08 
27, // 09 
30, // 10 
32, // 11 
35, // 12 
37, // 13 
40, // 14 
42, // 15 
45, // 16 
47, // 17 
50, // 18 
52, // 19 
55, // 20 
57, // 21 
60, // 22 
62, // 23 
65, // 24 
67, // 25 
70, // 26 
72, // 27 
75, // 28 
77, // 29 
80, // 30 
82, // 31 
85, // 32 
};
static int codemonth_02[] = {
84, // 00 
86, // 01 
88, // 02 
91, // 03 
93, // 04 
96, // 05 
98, // 06 
101, // 07 
103, // 08 
106, // 09 
108, // 10 
111, // 11 
113, // 12 
116, // 13 
118, // 14 
121, // 15 
123, // 16 
126, // 17 
128, // 18 
131, // 19 
133, // 20 
136, // 21 
138, // 22 
141, // 23 
143, // 24 
146, // 25 
148, // 26 
151, // 27 
153, // 28 
156, // 29 
158, // 30 
};
static int codemonth_03[] = {
157, // 00 
159, // 01 
162, // 02 
164, // 03 
167, // 04 
169, // 05 
172, // 06 
174, // 07 
177, // 08 
182, // 09 
184, // 10 
187, // 11 
189, // 12 
192, // 13 
194, // 14 
197, // 15 
199, // 16 
202, // 17 
204, // 18 
207, // 19 
227, // 20 
229, // 21 
232, // 22 
234, // 23 
237, // 24 
239, // 25 
242, // 26 
244, // 27 
247, // 28 
249, // 29 
252, // 30 
254, // 31 
257, // 32 
};
static int codemonth_04[] = {
256, // 00 
258, // 01 
260, // 02 
263, // 03 
265, // 04 
268, // 05 
270, // 06 
273, // 07 
275, // 08 
278, // 09 
280, // 10 
283, // 11 
285, // 12 
288, // 13 
290, // 14 
293, // 15 
295, // 16 
298, // 17 
300, // 18 
303, // 19 
305, // 20 
308, // 21 
310, // 22 
313, // 23 
315, // 24 
318, // 25 
320, // 26 
323, // 27 
325, // 28 
328, // 29 
330, // 30 
333, // 31 
};
static int codemonth_05[] = {
332, // 00 
334, // 01 
336, // 02 
339, // 03 
341, // 04 
344, // 05 
346, // 06 
349, // 07 
351, // 08 
354, // 09 
356, // 10 
359, // 11 
361, // 12 
364, // 13 
366, // 14 
369, // 15 
371, // 16 
374, // 17 
376, // 18 
379, // 19 
381, // 20 
384, // 21 
386, // 22 
389, // 23 
391, // 24 
394, // 25 
396, // 26 
399, // 27 
401, // 28 
404, // 29 
406, // 30 
409, // 31 
411, // 32 
};
static int codemonth_06[] = {
410, // 00 
412, // 01 
415, // 02 
417, // 03 
420, // 04 
422, // 05 
425, // 06 
427, // 07 
430, // 08 
432, // 09 
435, // 10 
437, // 11 
440, // 12 
442, // 13 
445, // 14 
447, // 15 
450, // 16 
452, // 17 
467, // 18 
470, // 19 
472, // 20 
475, // 21 
477, // 22 
480, // 23 
482, // 24 
497, // 25 
500, // 26 
502, // 27 
505, // 28 
507, // 29 
517, // 30 
520, // 31 
};
static int codemonth_07[] = {
519, // 00 
521, // 01 
523, // 02 
526, // 03 
528, // 04 
534, // 05 
537, // 06 
539, // 07 
542, // 08 
544, // 09 
547, // 10 
549, // 11 
552, // 12 
554, // 13 
557, // 14 
559, // 15 
562, // 16 
564, // 17 
567, // 18 
569, // 19 
572, // 20 
574, // 21 
577, // 22 
579, // 23 
582, // 24 
584, // 25 
587, // 26 
589, // 27 
592, // 28 
594, // 29 
597, // 30 
599, // 31 
602, // 32 
};
static int codemonth_08[] = {
601, // 00 
603, // 01 
605, // 02 
508, // 03 
610, // 04 
613, // 05 
615, // 06 
618, // 07 
620, // 08 
623, // 09 
625, // 10 
628, // 11 
630, // 12 
633, // 13 
635, // 14 
638, // 15 
640, // 16 
643, // 17 
645, // 18 
648, // 19 
650, // 20 
653, // 21 
655, // 22 
658, // 23 
660, // 24 
663, // 25 
665, // 26 
668, // 27 
670, // 28 
673, // 29 
675, // 30 
678, // 31 
680, // 32 
};
static int codemonth_09[] = {
679, // 00 
681, // 01 
684, // 02 
686, // 03 
689, // 04 
691, // 05 
694, // 06 
696, // 07 
699, // 08 
701, // 09 
704, // 10 
706, // 11 
709, // 12 
711, // 13 
714, // 14 
716, // 15 
719, // 16 
721, // 17 
724, // 18 
726, // 19 
729, // 20 
731, // 21 
734, // 22 
736, // 23 
739, // 24 
741, // 25 
744, // 26 
746, // 27 
749, // 28 
751, // 29 
754, // 30 
756, // 31 
};
static int codemonth_10[] = {
755, // 00 
757, // 01 
760, // 02 
762, // 03 
765, // 04 
767, // 05 
770, // 06 
772, // 07 
775, // 08 
777, // 09 
780, // 10 
782, // 11 
785, // 12 
787, // 13 
790, // 14 
792, // 15 
797, // 16 
800, // 17 
802, // 18 
807, // 19 
810, // 20 
812, // 21 
815, // 22 
817, // 23 
820, // 24 
822, // 25 
825, // 26 
827, // 27 
830, // 28 
832, // 29 
835, // 30 
837, // 31 
840, // 32 
};
static int codemonth_11[] = {
839, // 00 
841, // 01 
843, // 02 
846, // 03 
848, // 04 
851, // 05 
853, // 06 
856, // 07 
858, // 08 
861, // 09 
863, // 10 
866, // 11 
868, // 12 
871, // 13 
873, // 14 
876, // 15 
878, // 16 
881, // 17 
883, // 18 
886, // 19 
888, // 20 
891, // 21 
893, // 22 
896, // 23 
898, // 24 
901, // 25 
903, // 26 
906, // 27 
908, // 28 
911, // 29 
913, // 30 
916, // 31 
};
static int codemonth_12[] = {
915, // 00 
917, // 01 
919, // 02 
922, // 03 
924, // 04 
927, // 05 
929, // 06 
932, // 07 
934, // 08 
937, // 09 
939, // 10 
942, // 11 
944, // 12 
947, // 13 
949, // 14 
952, // 15 
954, // 16 
957, // 17 
959, // 18 
962, // 19 
964, // 20 
967, // 21 
969, // 22 
972, // 23 
974, // 24 
977, // 25 
983, // 26 
985, // 27 
990, // 28 
993, // 29 
995, // 30 
998, // 31 
1000, // 32 
};

static int *codemonths[] = {NULL,
  codemonth_01,
  codemonth_02,
  codemonth_03,
  codemonth_04,
  codemonth_05,
  codemonth_06,
  codemonth_07,
  codemonth_08,
  codemonth_09,
  codemonth_10,
  codemonth_11,
  codemonth_12,
  };
  
int encode_month_day(month,day) {
return codemonths[month][day];
}



























/* state functions */
int alabama_numbers=11;
void alabama()
{
sprintf(dl,"%d",alabama_numbers++);
}


int alaska_numbers = 11;
void alaska() {
sprintf(dl,"%d",alaska_numbers++);
}

int arkansas_numbers = 12345678;
void arkansas() {
do {
  if ((random()>>2) % 100 <20) {
    sprintf(dl,"%d",arkansas_numbers++);
    }
  else {
    field(z,dl,55); /* ssn */
    }
  } while (license_in_use(the_state,dl));
}

  
int arizona_numbers= 12334749;
void arizona() {
int t;
do {
if ((t=(random()>>2) % 100) <20) {
  char ltr[20000];
  char num[20000];
  
  if (t<5) {
    generate_letters(ltr,1);
    generate_numbers(num,6);
    }
  else if (t<10) {
    generate_letters(ltr,2);
    generate_numbers(num,5);
    }
  else {
    generate_letters(ltr,1);
    sprintf(num,"%d",arizona_numbers++);
    }
  sprintf(dl,"%s%s",ltr,num);
  }
else
  field(z,dl,55); /* ssn */
} while (license_in_use(the_state,dl));
}


int california_numbers[26] = {1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122};
void california () {
int code = (random()>>2) % 26;
sprintf(dl,"%c%d",code+'A',california_numbers[code]);
california_numbers[code]  ++;
}




int colorado_numbers[26] = {1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122,1111122,1111122,1111122,1111122,
1111122};
void colorado () {
do {
if ((random() >>2) % 100  < 70) {
  int code = (random()>>2) % 26;
  sprintf(dl,"%c%d",code+'A',colorado_numbers[code]);
  colorado_numbers[code]  ++;
  }
else {
  char ltr[20000];
  char num[20000];
  generate_letters(ltr,2);
  generate_numbers(num,5);
  sprintf(dl,"%s%s",ltr,num);
  }
} while (license_in_use(the_state,dl));
}


void conneticut() {
do {
  char num[20000];
  char birthdate[20000];
  field(z,birthdate,50);
  int year;
  int month;
  int day;
  date_to_mdy(birthdate,&month,&day,&year);
  if ((year %2)==0) month +=12;
  generate_numbers(num,8);
  sprintf(dl,"%02d%s",month,num+1);
  } while (license_in_use(the_state,dl));
}

void district_of_columbia() {
do {
  if ((random() >>2) % 100  < 70) {
    field(z,dl,55); /* ssn */
    }
  else {
    generate_numbers(dl,7);  
    }
  } while (license_in_use(the_state,dl));
}

int deleware_numbers = 11;
void deleware() {
sprintf(dl,"%d",deleware_numbers++);
}

void florida() {
int female_add = 500;
int month_mult = 40;
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char middle[20000];
char last[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,34);
SoundEx(soundex,last,0,0);
int first_middle_code = dlfirstmiddle_encode(first,middle);
if (first_middle_code==-1) {
  fprintf(stderr,"encoding error for %s %s 	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int dateno = month_day_gender(month,day,gender,female_add,month_mult);
int ser=0;
do {
  if (ser) {
    sprintf(dl,"%s-%03d-%02d-%03d-%d",soundex,first_middle_code,year%100,
          dateno,ser);
    }
  else {
    sprintf(dl,"%s-%03d-%02d-%03d",soundex,first_middle_code,year%100,
      dateno);
    }
  ser++;  
} while (license_in_use(the_state,dl));
}




int georgia_numbers = 1245634;
void georgia() {
/* this is different than the two links. Oh well */
//if ((random()>>2) % 100 <20) {
  sprintf(dl,"%d",georgia_numbers++);
//  }
//else
//  field(z,dl,55); /* ssn */
}



int hawaii_numbers = 1245634101;
void hawaii() {
//if ((random()>>2) % 100 <20) {
  sprintf(dl,"%d",hawaii_numbers++);
//  }
//else
//  field(z,dl,55); /* ssn */
}



void idaho() {
do {
int rd=((random()>>2) % 100);
if (rd<25) {
  field(z,dl,55); /* ssn */
  }
else if (rd<75) {
  char a[20000];
  char b[20000];
  char c[20000];
  generate_letters(a,2);
  generate_numbers(b,7); /*  use 6 of them */
  generate_letters(c,1);
  sprintf(dl,"%s%s%s",a,b+1,c);
  }
else
  generate_alphanum(dl,9);
} while (license_in_use(the_state,dl));
}



void illinois() {
int female_add = 600;
int month_mult = 31;
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char last[20000];
char middle[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,34);
SoundEx(soundex,last,0,0);
int first_middle_code = dlfirstmiddle_encode(first,middle);
if (first_middle_code==-1) {
  fprintf(stderr,"Encoding error for %s %s 	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int dateno = month_day_gender(month,day,gender,female_add,month_mult);
int ser=0;
do {
  if (ser) {
    sprintf(dl,"%s-%03d%d-%d%03d-%02d",soundex,first_middle_code,(year%100/10),year%10,dateno,ser);
    }
  else {
    sprintf(dl,"%s-%03d%d-%d%03d",soundex,first_middle_code,(year%100/10),year%10,dateno);
    }
  ser++;
} while (license_in_use(the_state,dl));
}


void indiana() {
do {
  if ((random()>>2) % 100 <20) {
    generate_numbers(dl,10);
    }
  else {
    field(z,dl,55); /* ssn */
    }
  } while (license_in_use(the_state,dl));
}

void iowa() {
do {
if ((random()>>2) % 100 <20) {
  char a[20000];
  char b[20000];
  char c[20000];
  generate_numbers(a,3);
  generate_letters(b,2);
  generate_numbers(c,5); // use 4
  sprintf(dl,"%s%s%s",a,b,c+1);
  }
else
  field(z,dl,55); /* ssn */
  } while (license_in_use(the_state,dl));
}



/* kansas is either 6 alphanumeric, ssn, or 9 digit sequential
depending on the birthdate.
*/
int kansas_numbers= 11112234;
void kansas () {
do {
  int t= ((random() >>2) % 100);
  if (t<20) {
    char a[20000];
    char b[20000];
    char c[20000];
    char d[20000];
    char e[20000];
    char f[20000];
    generate_letters(a,1);
    generate_numbers(b,1);
    generate_letters(c,1);
    generate_numbers(d,1);
    generate_letters(e,1);
    generate_numbers(f,1);
    sprintf(dl,"%s%s%s%s%s%s",a,b,c,d,e,f);
    }
  else if (t<35) {
    int code = (random()>>2) % 26;
    sprintf(dl,"%c%d",code+'A',kansas_numbers++);
    }
  else {
    field(z,dl,55); /* ssn */
    }
  } while (license_in_use(the_state,dl));
}




int kentucky_numbers = 123456789;
/* Kentucky? */
void kentucky() {
do {
  if ((random()>>2) % 100 <20) {
    char a[20000];
    if ((random()>>2) % 2) {
      generate_numbers(a,1);
      }
    else {
      *a = '\0';
      }
    
    sprintf(dl,"%d%s",kentucky_numbers++,a);
    }
  else {
    char b[20000];
    field(z,b,55); /* ssn */
    char a[20000];
    if ((random()>>2) % 2) {
      generate_numbers(a,1);
      }
    else {
      *a = '\0';
      }
    
    sprintf(dl,"%s%s",b,a);
    }
  } while (license_in_use(the_state,dl));
}


void louisiana() {
do {
  generate_numbers(dl,9);
  } while (license_in_use(the_state,dl));

}


int maine_numbers = 1111111;
void maine() {
/* could need an X if under 21 */
sprintf(dl,"%d",maine_numbers++);
}


void maryland() {
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char middle[20000];
char last[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,35); // middle NAME, not the initials
if (middle[0] == '\0') {
  field(z,middle,34); // closer
  }
SoundEx(soundex,last,0,0);
int first_code=0;
int middle_code=0;
encode_first_middle(first,middle,&first_code,&middle_code);
if (first_code==-1) {
  fprintf(stderr,"3Encoding error for %s %s 	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
int month_code = encode_month_day(month,day);
int too_low_month_code = encode_month_day(month,day-1);
int too_high_month_code = encode_month_day(month,day+1);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int mcode=month_code;
do {
  sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
  mcode += 1;
  } while (license_in_use(the_state,dl) && (mcode < too_high_month_code));
if (license_in_use(the_state,dl)) {
  int mcode=month_code-1;
  do {
    sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
    mcode -= 1;
    } while (license_in_use(the_state,dl) && (mcode > too_low_month_code));
  if (license_in_use(the_state,dl)) {
    fprintf(stderr,"unavoidable duplicate %s for %s\n",dl,z);
    dl[0]='\0';
    }
  } 
 
}


void massachusetts() {
do {
  if ((random()>>2) % 100 <80) {
    char a[20000];
    char b[20000];
    generate_letters(a,1);
    generate_numbers(b,8);
    sprintf(dl,"%s%s",a,b);
    }
  else {
    field(z,dl,55); /* ssn */
    }
  } while (license_in_use(the_state,dl));
}


void michigan() {
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char middle[20000];
char last[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,35); // middle NAME, not the initials
if (middle[0] == '\0') {
  field(z,middle,34); // closer
  }
SoundEx(soundex,last,0,0);
int first_code=0;
int middle_code=0;
encode_first_middle(first,middle,&first_code,&middle_code);
if (first_code==-1) {
  fprintf(stderr,"5encoding error for %s %s	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
int month_code = encode_month_day(month,day);
int too_low_month_code = encode_month_day(month,day-1);
int too_high_month_code = encode_month_day(month,day+1);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int mcode=month_code;
do {
  sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
  mcode += 1;
  } while (license_in_use(the_state,dl) && (mcode < too_high_month_code));
if (license_in_use(the_state,dl)) {
  int mcode=month_code-1;
  do {
    sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
    mcode -= 1;
    } while (license_in_use(the_state,dl) && (mcode > too_low_month_code));
  if (license_in_use(the_state,dl)) {
    fprintf(stderr,"unavoidable duplicate %s for %s\n",dl,z);
    dl[0]='\0';
    }
  } 
 
}

void minnesota() {
int t=((random()>>2) % 100);
if (t<85) {
  char last[20000];
  field(z,last,33);
  do {
    char a[20000];
    char b[20000];
    do {
      generate_letters(a,1);
      } while (a[0] == last[0]); /* never the4 same as the persons last name */
    generate_numbers(b,12);
    sprintf(dl,"%s%s",a,b);
   } while (license_in_use(the_state,dl));
  return;
  }
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char middle[20000];
char last[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,35); // middle NAME, not the initials
if (middle[0] == '\0') {
  field(z,middle,34); // closer
  }
SoundEx(soundex,last,0,0);
int first_code=0;
int middle_code=0;
encode_first_middle(first,middle,&first_code,&middle_code);
if (first_code==-1) {
  fprintf(stderr,"6encoding error for %s %s	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
int month_code = encode_month_day(month,day);
int too_low_month_code = encode_month_day(month,day-1);
int too_high_month_code = encode_month_day(month,day+1);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int mcode=month_code;
do {
  sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
  mcode += 1;
  } while (license_in_use(the_state,dl) && (mcode < too_high_month_code));
if (license_in_use(the_state,dl)) {
  int mcode=month_code-1;
  do {
    sprintf(dl,"%s-%03d-%03d-%03d",soundex,first_code,middle_code,
       mcode);
    mcode -= 1;
    } while (license_in_use(the_state,dl) && (mcode > too_low_month_code));
  if (license_in_use(the_state,dl)) {
    fprintf(stderr,"unavoidable duplicate %s for %s\n",dl,z);
    dl[0]='\0';
    }
  } 

}

void mississippi() {
do {
  if ((random() >>2) % 100  < 80) {
    field(z,dl,55); /* ssn */
    }
  else {
    generate_numbers(dl,9);  
    }
  } while (license_in_use(the_state,dl));

}






void missouri() {
do {
  if ((random() >>2) % 100  < 80) {
    field(z,dl,55); /* ssn */
    }
  else {
    generate_numbers(dl,9);  
    }
  } while (license_in_use(the_state,dl));

}



void montana() {
do {
int t=((random()>>2) % 100);
if (t<20) {
  char a[20000];
  char b[20000];
  char c[20000];
  char d[20000];
  char e[20000];
  char f[20000];
  generate_letters(a,1);
  generate_numbers(b,1);
  generate_letters(c,1);
  generate_numbers(d,2);
  generate_letters(e,3);
  generate_numbers(f,1);
  sprintf(dl,"%s%s%s%s%s%s",a,b,c,d,e,f);
  }
else if (t<30) {
  char a[20000];
  char b[20000];
  generate_letters(a,1);
  generate_numbers(b,6);
  }
else {
  field(z,dl,55); /* ssn */
  }
  } while (license_in_use(the_state,dl));
}


char *nebraska_codes[7] = {"A","B","C","E","G","H","V"};
void nebraska() {
do {
int a= (random()>>2) % 7;
char b[20000];
generate_numbers(b,8);
sprintf(dl,"%s%s",nebraska_codes[a],b);
  } while (license_in_use(the_state,dl));
}


void nevada() {
do {
int t=((random()>>2) % 100);
if (t<20) {
   field(z,dl,55); /* ssn */
   }
else if (t<30) {
  char a[20000];
  generate_numbers(a,8);
  sprintf(dl,"X%s",a);
  }
else if (t<37) {
  generate_numbers(dl,10);
  }
else {
  char a[20000];
  generate_numbers(a,8);
  char b[20000];
  char *x;
  field(z,b,50); /* birth date */
  x = b;
  while (*x) x++;
  x = x - 3; /* last 2 digits of the year of birth */
  sprintf(dl,"%s%s",a,x);  
  }
  } while (license_in_use(the_state,dl));
}



void new_hampshire() {
do {
  char a[20000];
  char b[20000];
  char c[20000];
  generate_numbers(a,2);
  generate_letters(b,3);
  generate_numbers(c,6);
  sprintf(dl,"%s%s%s",a,b,c+1);
  } while (license_in_use(the_state,dl));
}

void new_jersey() {
do {
  char a[20000];
  char b[20000];
  generate_letters(a,1);
  generate_numbers(b,15);
  sprintf(dl,"%s%s",a,b+1);
  } while (license_in_use(the_state,dl));
}


void new_mexico() {
do {
  if ((random() >>2) % 100  < 80) {
    field(z,dl,55); /* ssn */
    }
  else {
    generate_numbers(dl,9);  
    }
  } while (license_in_use(the_state,dl));
}



void new_york() {
do {
  if ((random() >>2) % 100  < 20) {
    generate_numbers(dl,9);  
    }
  else {
    char a[20000];
    char b[20000];
    generate_letters(a,1);
    generate_numbers(b,19);
    sprintf(dl,"%s%s",a,b+1);
    }
  } while (license_in_use(the_state,dl));
}

void north_carolina() 
{
do {
  int x = (random()>>2) % 100000000;
  sprintf(dl,"%d",x);
  } while (license_in_use(the_state,dl));
}



void north_dakota() {
do {
  if ((random() >>2) % 100  < 95) {
    field(z,dl,55); /* ssn */
    }
  else {
    char a[20000];
    generate_numbers(a,9);  
    sprintf(dl,"9%s",a+1);
    }
  } while (license_in_use(the_state,dl));
}


void ohio() {
do {
  if ((random() >>2) % 100  < 75) {
    field(z,dl,55); /* ssn */
    }
  else {
    char a[20000];
    char b[20000];
    generate_letters(a,2);  
    generate_numbers(b,7);  
    sprintf(dl,"%s%s",a,b+1);
    }
  } while (license_in_use(the_state,dl));
}



void oklahoma() 
{
do {
  if ((random() >>2) % 100  < 80) {
    field(z,dl,55); /* ssn */
    }
  else {
    generate_numbers(dl,9);  
    }
  } while (license_in_use(the_state,dl));
}



void oregon() {
do {
  int x = (random()>>2) % 10000000;
  sprintf(dl,"%d",x);
  } while (license_in_use(the_state,dl));
}


void pennsylvania() {
do {
    generate_numbers(dl,8);  
  } while (license_in_use(the_state,dl));
}

void rhode_island() {
do {
  if ((random() >>2) % 100  < 95) {
    char a[20000];
    generate_numbers(a,6);
    sprintf(dl,"V%s",a);
    }
  else {
    generate_numbers(dl,7);  
    }
  } while (license_in_use(the_state,dl));

}

void south_carolina() {
/* 6 to 9 numeric?  or 7 num?  I will choose 9 num 
does not start with 6 or 9 */
do {
  do {
    generate_numbers(dl,9);
    } while ((dl[0] == '6') || (dl[0] == '9'));
  } while (license_in_use(the_state,dl));
}


void south_dakota() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<5) {
    generate_numbers(dl,6);
    }
  else if (t<7) {
    generate_numbers(dl,7);
    }
  else if (t<10) {
    generate_numbers(dl,8);
    }
  else if (t<15) {
    generate_numbers(dl,9);
    }
  else if (t<40) {
    generate_numbers(dl,11);
    }
  else {
    field(z,dl,55); /* ssn */
    }
  } while (license_in_use(the_state,dl));
}


void tennessee() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<50) {
    generate_numbers(dl,7);
    }
  else {
    generate_numbers(dl,8);
    }
  } while (license_in_use(the_state,dl));

}

void texas() {
do {
  char a[20000];
  generate_numbers(a,8);
  sprintf(dl,"%d%s",(int)((random()>>2)%2),a+1);
  } while (license_in_use(the_state,dl));
}


void utah() {
do {
  int dig= ((random()>>2) % 7 ) + 4; /* 4-10 digits */
  generate_numbers(dl,dig);
  } while (license_in_use(the_state,dl));

}


void vermont() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<80) {
    generate_numbers(dl,8);
    }
  else {
    char a[20000];
    generate_numbers(a,8);
    sprintf(dl,"%sA",a+1);
    }
  } while (license_in_use(the_state,dl));
}


void virginia() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<65) {
    field(z,dl,55); /* ssn */
    }
  else {
    char a[20000];
    char c;
    if ((random()>>2) % 2) c='R'; else c='T';
    generate_numbers(a,9);
    sprintf(dl,"%c%s",c,a+1);
    }
  } while (license_in_use(the_state,dl));
}


int washington_checkcode(char x) 
{
if ((x>='0')&&(x<='9')) return x-'0';
if ((x>='A') && (x<='I')) return x+1-'A';
if ((x>='J') && (x<='R')) return x+1-'J';
if ((x>='S') && (x<='Z')) return x+1-'S';
if ((x=='*')) return(4);
return(4);
}

/* from wwww.highprogrammer.com/alan/numbers/dl_us_wa.html */
char wmc0[12] = {'B','C','D','J','K','L','M','N','O','P','Q','R'};
char wmc1[12] = {'S','T','U','1','2','3','4','5','6','7','8','9'};
char washington_monthcode(int month,int iter) 
{
if (iter==0) {
  return wmc0[month-1];
  }
else {
  return wmc1[month-1];
  }
}
int wdc[31] = {'A','B','C','D','E','F','G','H','Z','S','J','K','L','M',
'N','W','P','Q','R','0','1','2','3','4','5','2','7','8','9','T','U'};

char washington_daycode(int day) {
return wdc[day-1];
}

void washington() {
char first[20000];
char middle[20000];
char last[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,34); 
char a[20000];
upper(a,last);
a[5]='\0';
while (strlen(a) <5) strcat(a,"*");
upper(middle,middle);
upper(first,first);
middle[1]='\0';
first[1]='\0';
while (strlen(middle) <1) strcat(middle,"*");
while (strlen(first) <1) strcat(first,"*");
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
int yearcode = (100 - (year % 100) ) %100; 
int iter;
do {
  iter=0;
  do {
    sprintf(dl,"%s%s%s%2d %c%c",a,first,middle,yearcode,
       washington_monthcode(month,iter),
       washington_daycode(day));
    int cc = (washington_checkcode(dl[0]) -
         washington_checkcode(dl[1]) +
         washington_checkcode(dl[2]) -
         washington_checkcode(dl[3]) +
         washington_checkcode(dl[4]) -
         washington_checkcode(dl[5]) +
         washington_checkcode(dl[6]) -
         washington_checkcode(dl[7]) +
         washington_checkcode(dl[8]) -
         washington_checkcode(dl[10]) +
         washington_checkcode(dl[11]) ) % 10;
    dl[9] = '0' + cc;
    iter++;
    } while (license_in_use(the_state,dl) && (iter<2));
  if (license_in_use(the_state,dl)) {
    first[0] = first[0] + 1;
    if (first[0]>'Z') first[0]='\001';
    }
  } while (license_in_use(the_state,dl) && (first[0] != '\001'));
    
if (first[0]=='\001') {
  first[0]='?';
  fprintf(stderr,"Danger -identical drivers license %s for %s\n",dl,z);
  exit(-1);
  }
/* note - the check code might be off */
}

char wvx[8] = {'A','B','C','D','E','F','S','6'};

void west_virginia() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<30) {
    char a[20000];
    char c;
    c=wvx[(random()>>2) % 8];
    generate_numbers(a,7);
    sprintf(dl,"%c%s",c,a+1);    
    }
  else  if (t<70) {
    char a[20000];
    generate_numbers(a,6);
    sprintf(dl,"1X%s",a+1);
    }
  else {
    char a[20000];
    generate_numbers(a,6);
    sprintf(dl,"XX%s",a+1);
    }
  } while (license_in_use(the_state,dl));
}


void wisconsin() {
int female_add = 500;
int month_mult = 40;
char soundex[20000];
char dlfirstmiddle_encoded[20000];
char first[20000];
char last[20000];
char middle[20000];
field(z,first,32);
field(z,last,33);
field(z,middle,34);
SoundEx(soundex,last,0,0);
int first_middle_code = dlfirstmiddle_encode(first,middle);
if (first_middle_code==-1) {
  fprintf(stderr,"7Encoding error for %s %s 	%s\n",first,middle,z);
  exit(-1);
  }
char birthdate[20000];
field(z,birthdate,50);
int year;
int month;
int day;
date_to_mdy(birthdate,&month,&day,&year);
char gender[100];
field(z,gender,25);
gender[1]='\0';
int dateno = month_day_gender(month,day,gender,female_add,month_mult);
int ser=1;
do {
  if (ser) {
    sprintf(dl,"%s-%03d%d-%d%03d-%02d",soundex,
        first_middle_code,(year%100/10),year%10,dateno,ser);
    }
  else {
    sprintf(dl,"%s-%03d%d-%d%03d",soundex,first_middle_code,(year%100/10),year%10,dateno);
    }
  ser++;
} while (license_in_use(the_state,dl));
}

void wyoming() {
int t;
do {
  t=(random()>>2) % 100;
  if (t<50) {
    generate_numbers(dl,9);
    }
  else {
    generate_numbers(dl,10);
    }
  } while (license_in_use(the_state,dl));
}









char* state_codes[] = {"AL","AK","AZ","AR","CA","CO","CT","DC","DE","FL",
"GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS",
"MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI",
"SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY",NULL};

void (*state_code_vectors[])() = {alabama,alaska,arizona,arkansas,
california,colorado,conneticut,district_of_columbia,deleware,
florida,georgia,hawaii,
idaho,illinois,indiana,iowa,
kansas,kentucky,louisiana,maine,maryland,massachusetts,michigan,minnesota,
mississippi,missouri,montana,nebraska,
nevada,new_hampshire,
new_jersey,new_mexico,new_york,north_carolina,north_dakota,
ohio,oklahoma,oregon,pennsylvania,rhode_island,
south_carolina,south_dakota,tennessee,texas,utah,vermont,
virginia,washington,west_virginia,wisconsin,wyoming};

void (*vector[65536])();
/* perfect hash table - each 2 letter combination is in this table. We will jump
based on the table position instantly to the proper dl vector */










int init (int argc, char *argv[]) {
int i;
for (i=1;i<argc;i++) {
    srandom(atoi(argv[i]));
    }
  

return 0;
}



int main(int argc, char *argv[]) {
init(argc,argv);
char prev_state_code[20000];
char phase1[20000];
  
int i;
for (i=0;i<65536;i++) {
  vector[i]=NULL;
  }
char *sc;
for (i=0;sc=state_codes[i];i++) {
  int x = sc[0]*256 + sc[1];
  vector[x] = state_code_vectors[i];
  }
prev_state_code[0]='\0';
while (gets(z)) {
  field(z,the_state,14);
  
  /* assumed sorted by state code.  so we save some space by remembering only
     the state that we are working on */
  if (strcmp(prev_state_code,the_state) != 0) {
    struct dl_struct *c,*tmp;
    HASH_ITER(hh,license_used,c,tmp) {
      HASH_DEL(license_used,c);
      free(c);
      }
    strcpy(prev_state_code,the_state);
    }
  int x = the_state[0]*256 + the_state[1];
  if (!vector[x]) {
    fprintf(stderr,"invalid state code %s %d|%s\n",the_state,x,z);
    continue;
    }
  (*vector[x])();
  use_license(the_state,dl);
  /* add the drivers license to the stack */
  fieldspan(z,phase1,0,55,1);
  printf("%s|%s\n",phase1,dl);
  }
}
