use strict;
use warnings;
 
my $filename = $ARGV[0];
my $sp_outfile = 'cutt';
##open (my $fh, "<", "or1200_PPI_0");
open(my $sp_format, '>', $sp_outfile) or die "Could not open file '$sp_outfile' $!";
print $sp_format "cut -f\\\n";
my $i=0;
if (open(my $fh, $filename)) {
  while (my $row = <$fh>) {
    chomp $row;

    ## $row =~ s/\s+$//; ##trim whitespace from right
     $row =~ s/^\s+|\s+$//g;
     $row =~ s/\.00//;
    ##my @values = split('.', $row);
    if ($i==0) {print $sp_format "$row\\\n";}
    else  {print $sp_format ",$row\\\n";}

    $i=$i+1;
    #print $sp_format ",$row\n";
  }
print $sp_format " sp > sp_reduced "
} 
