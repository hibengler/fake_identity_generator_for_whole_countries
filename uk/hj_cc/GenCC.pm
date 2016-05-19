#!/usr/bin/perl
use strict;
use warnings;
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
package GenCC;
{

	my @visaPrefixList = (
					['4', '5', '3', '9'], 
	            	['4', '5', '5', '6'], 
               		['4', '9', '1', '6'],
                    ['4', '5', '3', '2'], 
             	    ['4', '9', '2', '9'],
                    ['4', '0', '2', '4', '0', '0', '7', '1'],
                    ['4', '4', '8', '6'],
                    ['4', '7', '1', '6'],
                    ['4']
					);

	my @mastercardPrefixList = (
							['5', '1'],
                            ['5', '2'],
                            ['5', '3'],
                            ['5', '4'],
                            ['5', '5']
						);

	my @amexPrefixList = (
	  						['3', '4'],
                   			 ['3', '7']
						);

	my @discoverPrefixList = (
							['6', '0', '1', '1'] 
							);

	my @dinersPrefixList = (
						['3', '0', '0'],
                        ['3', '0', '1'],
                        ['3', '0', '2'],
                        ['3', '0', '3'],
                        ['3', '6'],
                        ['3', '8']
						);	

	my @enRoutePrefixList = (
	 					['2', '0', '1', '4'],
                        ['2', '1', '4', '9']
						);	

	my @jcbPrefixList16 = (
	 				['3', '0', '8', '8'],
                    ['3', '0', '9', '6'],
                    ['3', '1', '1', '2'],
                    ['3', '1', '5', '8'],
                    ['3', '3', '3', '7'],
                    ['3', '5', '2', '8'] 
					);

	my @jcbPrefixList15 = ( 
					['2', '1', '0', '0'],
                    ['1', '8', '0', '0']
					);	

	my @voyagerPrefixList = (
	   				['8', '6', '9', '9']
					);	
                    

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
		my $checkdigit = (($sum / 10 + 1) * 10 - $sum) % 10;
		$ccnumber .= $checkdigit;

		return $ccnumber;
	}

=item credit_card_number(prefixList, length, howMany)

=cut
	sub credit_card_number(\@$$) {
		my @prefixList = @{shift()};
		my ($length, $howMany) = @_;

		my @result;
		foreach my $i (1...$howMany) {
			my $ccnumber = join('', @{$prefixList[int(rand($#prefixList))]});
			push @result, completed_number($ccnumber, $length);
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

	#
	# Main
	#

	sub main() {

		print "darkcoding credit card generator\n\n";

		my $mastercard = 
				credit_card_number(@mastercardPrefixList, 16, 10);
		print output("Mastercard", $mastercard);
	
		my $visa16 = 
				credit_card_number(@visaPrefixList, 16, 10);
		print output("VISA  16 digit", $visa16);
	
		my $visa13 = 
				credit_card_number(@visaPrefixList, 13, 5);
		print output("VISA  13 digit", $visa13);
	
		my $amex = 
				credit_card_number(@amexPrefixList, 15, 5);
		print output("American Express", $amex);
	
		# Minor cards
		my $discover = 
				credit_card_number(@discoverPrefixList, 16, 3);
		print output("Discover", $discover);
	
		my $diners = 
				credit_card_number(@dinersPrefixList, 14, 3);
		print output("Diners Club / Carte Blanche", $diners);
	
		my $enRoute = 
				credit_card_number(@dinersPrefixList, 15, 3);
		print output("enRoute", $enRoute);
	
		my $jcb15 = 
				credit_card_number(@jcbPrefixList15, 15, 3);
		print output("JCB 15 digit", $jcb15);
	
		my $jcb16 = 
				credit_card_number(@jcbPrefixList16, 16, 3);
		print output("JCB 16 digit", $jcb16);
	
		my $voyager = 
				credit_card_number(@voyagerPrefixList, 15, 3);
		print output("Voyager", $voyager);
	}
}

unless (caller) {
	__PACKAGE__->main();
}
1;







