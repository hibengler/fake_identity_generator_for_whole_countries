#!/usr/bin/perl
# usage: perl mycc.pl <number> <seed>
# Modified to do the following
# modifications are also GPL 
# get a list of common 6 digit iis's  - more than 6 digits will not work 
# correctly.
# then make an array of them all and pick from the array - this means
# bigger prefixes have more cc numbers, kinda like rality I bet.
# the list is generated externally in special.pl
#
# but not for discover.  Discoverer is limited to 10% of its values.
# Then go through and psuedo-randomly pick numbers.
# we do psuedo-random, so we can reproduce the results
# important for auditing.

use Data::Dumper;
=pod
gencc: A simple program to generate credit card numbers that pass the MOD 10 check
(Luhn formula).
Usefull for testing e-commerce sites during development.

Copyright 2003 Graham King

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

=over

=cut


#increase the prefix list as defined in 
# http://en.wikipedia.org/wiki/List_of_Bank_Identification_Numbers#48_.28Visa.29


		    
					
							                        

sub setup_list {
@type_list = ();
@prefix_list = ();
$curyear = `date +"%y"`;
$curmonth = `date +"%m"`;
require "special.pl";
}

=item completed_number(prefix, length)
'prefix' is the start of the CC number as a string, any number of digits.
'length' is the length of the CC number to generate. Typically 13 or 16
=cut

	sub completed_number($$) {

		my ($prefix, $length) = @_;
   	 	my $ccnumber = $prefix;

	    # generate digits

   		while (length($ccnumber) < ($length - 1)) {
    		my $digit = int(rand(10));
			$ccnumber .= $digit;
		}

	    # Calculate sum 
		my $sum = 0;
		my $pos = 0;

		my @reversedCCnumber = ();

		@reversedCCnumber = reverse(split //, $ccnumber);

		while ($pos < $length - 1) {

			my $odd = $reversedCCnumber[$pos] * 2;
			$odd -= 9 if $odd > 9;

			$sum += $odd;

			if ($pos != ($length - 2)) {
				$sum += $reversedCCnumber[$pos+1];
			}
			$pos += 2;
		}

    	# Calculate check digit
		my $checkdigit = (int($sum / 10 + 1) * 10 - $sum) % 10;
		$ccnumber .= $checkdigit;

		return $ccnumber;
	}

=item credit_card_number(length, howMany)

=cut
	sub credit_card_number {
		my ($length, $howMany) = @_;

		my @result;
		foreach my $i (1...$howMany) {
			my $count = @prefix_list;
			my $index = int(rand($count));
			my $ccv;
			if ($type_list[$index] eq "amex") {
			  $ccv = int(rand(9960))+20;
			  }
			else {
			  $ccv = int(rand(996))+2;
			  }
			my $monthsout = $curmonth + 2+ int(rand(48));
			my $yearsout += $curyear + int(($monthsout-1)/12);
			$monthsout = ($monthsout -1 )% 12+1;
			$yearsout = sprintf("%02d",$yearsout);
			$monthsout = sprintf("%02d",$monthsout);
			my $pin = int(rand(10000));
			$pin = sprintf("%04d",$pin);			
			my $ccnumber = $prefix_list[$index];
			$ccnumber = completed_number($ccnumber,$length);
			print STDOUT $ccnumber . "|" . 
			   $monthsout . $yearsout . "|" . 
			   $ccv . "|" . 
			   $type_list[$index] . 
			   "|" . $pin . "\n";
			
		}		
		return \@result
	}

=item output(title, numbers) 

=cut

	sub output($$) {

		my $title = shift;
		my @numbers = @{shift()};
		my @result;

		push @result, $title;
		push @result, '-'x(length($title));
		push @result, join("\n", @numbers);
		push @result, '';
		return join("\n", @result) . "\n";
	}


unless (caller) {
	__PACKAGE__->main();
}




sub push3 {
local ($type,$prefix) = @_;
my $i;
for ($i = 0;$i < 10; $i++) {
  $d = rand(100);
  $d = sprintf("%02d",$d);
  push5($type,$prefix . $d);
  }
}

sub push4 {
local ($type,$prefix) = @_;
my $i;
for ($i = 0;$i < 10; $i++) {
  push5($type,$prefix . $i);
  }
}

sub push5 {
local ($type,$prefix) = @_;
my $i;
for ($i = 0;$i < 10; $i++) {
  push6($type,$prefix . $i);
  }
}

sub push6 {
local ($type,$prefix) = @_;
push (@type_list,$type);
push (@prefix_list,$prefix);
}





#
# Main
#
sub main() {
	
# setup count
$the_count = $ARGV[0];

# setup seed if provided
$seed = $ARGV[1];
if ($seed ne "") {
  srand($seed);
  }	
# note - srand needs to be set up BEFORE calling setup_list
# this is because we randomize the push3 values - to only give 100 prefixes instead of 1000
# lets face it 	
setup_list();
credit_card_number(16, $the_count);
}
