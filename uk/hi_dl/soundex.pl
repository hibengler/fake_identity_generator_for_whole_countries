
use Text::Soundex;
while (<stdin>) {
  $orig = $_;
  @row =split(/\|/,$_);
  # Original algorithm.
  $row[46] = soundex($row[32]);    # Get the soundex code for a name.

  print join("|",@row);
  }
