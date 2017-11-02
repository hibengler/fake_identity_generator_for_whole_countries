Fake Identity Generator
Copyright (C) 2011-2017 Hibbard M. Engler (Bitcoin address 1ERDHsxtekdh5FAsxdb92PBFK7nnuwMkbp for gifts)

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

This is the source code that made the websites xdd.org, xdd2.org, and xdduk.org.  It uses bar_database as the database server, information processor.   Lanuages are C, Perl, snobol4, bash, awk.

Development took 18 months,a nd the website was released in 2012.  The idea was to make data for corporate honeypots, to help keep the real infomration safe.

Then google started crawling the website.
They at one point (2014) had 140 million entries in their search engine, which caused some confusion.  We were getting 70,000 page views from users a day, and made some money on advertizing until google did a manual edit, and said that xdd doesn't fit with their guidelines. 

I also did xdduk.org for england, and wante to do Austrlia, Canada, China, and India.
What happened when this was on google, is that people would not get everyone's real information. I was protecting the identity of everyone in the country.  :)

Right now, xdd.org is down for maintennace, but it is still running.  
There are many components that make this real cool including:

rtr - a web server in C that does single thread assymetric blocking.  It could handle about 400 page views a second, that with reading a huge 600 gb database.

The database (bar_database) - binary search on bar delimited files (bar|delimited|files|).   The file was memory mapped, and the drives are 3 raid 0 SSD's.  Real fast.

And of course, the final result - a complete set of people with reasonable names, addresses, phone numbers, Social security numbers, passport numbers, credit card numbers,  all consistent with eachother, and believable , but entirely fallacious. Thats the best part.

I did this with extreme do-diligance. Including queryiong with the FBI before doing it.  I also was investigated by the Social Security Administration special services, but never was commited of a crime.

So, please, use this for good, maybe a video game that needs a realistic fake town or faks country with fake peopl? maybe as the honeypot to alert companies of a break-in before they get to the real customer data, things like that.
Don't use it for comitting fraud. I do not hand have never condoned doing that. Some people have tried using the fake names to commit crimes, and I worked with law enforcement in those cases. Blah Blah Blah.



Hib

Below is the readme when I first started the project.


My idea was simple:

1. make billions of fake names - the ultamite honey pot.
2. Send out a net of leaders to the honeypot, and collect information.
3. sell the informtion of who used the fake data
4. Make sure that all data is externally verifiable - to prove no illintent.
5. generate a context based knowledge sytem using prime numbers.
6. Become the defacto place to verify documents.


Fake names:
states
  cities
    zip code
      zip cities

area codes
   prefiex (exchanges)
   
first names
last names
   ssn death index  feed into ssn death, first name, last name
       ssn formula
       name frequency and grouping analysis - to identify weights and occurrences of names.

zp4 ---> streets for cities and states
               use streets and city names to find real addresses with real people - whitepages at first.
	       But terms of use does not allow - so instead

Do not use zp4 -- purchase an occupant list for the entire country.

Then for each batch
   For each city
      for each zipcode
         for each street
	    for each house
	       for the number of people in each house
	          pick a random last name
		  if the last name is on this street in real life,   try again
		  pick a random first name -- with a distribution to go with the last name or the group more likely.
		  if the first name, last name is in theis cipcode or city in real life, try again.
		  pick a middle name.
		  If the state uses the names to produce the drivers license,  and there is a real person in the
		  state with first, middle initial, and last name, try again
		  pick a birth date
		  generate a ssn based on the birth date, and a city close to the living in city.
		  generate a drivers license, based on the state rules.
		  Generate 2-3 fake credit card numbers
		  generate a phone number within the area - not picking a number already used.
		  record the information - and sign it so there is a paper trail back to the beginning.

Now the data is generated.  The next step is to make the honeypot.  
Make the honeypot look like an apache web server with files just there for browsing.  Actually though,  the 
server is running a cgi program.
serving up folders - in actuality it is reading the database, producing the results on the fly.
  For each hit -  record the date and time, and sign it.
  For each new ip address, or ip addresses over a month old, performa  traceroute.
  Use cookies- if allowed,  to gain other information
  Use SSL - and record response times for each packet - if possiblem
  Find out about web browser plugins and whatnot - to get a computer fingerprint.
  All this information will then be signed by the program - keeps evidence from being altered.


All documents will be hash coded and converted to something like the ID system I developed: 
ID_1h324873223481284g_ID.<document_type>
All documents will get a "key"  - a key is a large prime number.
Docuemnts can be accessed by the ID- in some cases, or by the key.
Cross reference -- association of atoms are performed by multiplying keys together.
If n keys are known,   then to search through the keys takes n divisions-- modulo's actually.

If you know two large numbers,  you can use the sieve to quickly find out all the primes of those numbers. :)

All content - be it words, etc,  will have a set of numbers that make up the content.
The earlier primes will allow arrangement of the value primes +-
the prime number 2 is reserved for the hyperdocument.

So If you know something, and someone else knows something,  and you get the idea s together,  then you know more 
than you could know apart.  This means that sharing increases the knowledge of information.
number : number


Well, thats enough of that.  I got real stressed out about this thing.  I sent a letter to the FBI asking if generating fake nmes is legal or not.
I will table this idea for a while,  maybee talk to gary about it.  My time is better spent looking into a document solutions.


  

Time with 16gb memory:

ha - 231m     89737163
hb - 4.43m    89737163
hc -j 1  431m 89737163
hd - 164m 127113427
he -j 2   - 250375111
hf - -j 4   750m 250375111
hg_ssn -j 4 135m 250375111
hi_dl -j 2 62m 250375111
hj -j 2 165m 250375111
hk -j 2 23m 250375111
hl -j 2 132m 250375111

export SET=0
export OWN=0
hm - 55
hn - 258
ho -  time make -j 2 405 + more cause of everything and stuff
transfer to machine over 1000-base-t encrypted drive - 137 minutes


Edit c programs - set minimum date to current date
edit filter_me.sh in hc... hd... and he... - and add new exlfza stuff

time with 32gb memory:
export SET=PUB5
export OWN=KCD5
# copy leads.txt into ~/common

# edit make_birthdate.c and make_birthdate2.c and make_ssn_numbers.c and add_birthdate_birth_date.c

ha - 303 + 35
hb - short
hc - 13 hours 11 minutes = 700 minutes
hd -

he
cd he*
time bash save_new.sh - to make the next set

