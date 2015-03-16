use strict;
use warnings;
use autodie;  #So I dont have to worry about my file

my $input = $ARGV[0]; 
my $num_of_workloads=4;

my $sp_outfile = 'sp';
open (my $fh, "<", "or1200_PPI_0");
open(my $sp_format, '>', $sp_outfile) or die "Could not open file '$sp_outfile' $!";
my @file_array;
my @total_value=0;
my $line_count=0;
my $size_of_array=0 ;
for (my $iter=0; $iter < $num_of_workloads; $iter++) {
	my $PPI_string = './input_test/'.$input.'/'.$input.'_PPI_'.$iter;
	my $PO_string = './input_test/'.$input.'/'.$input.'_PO_'.$iter;
	
	
	open (my $ppi, "<", $PPI_string);
	open (my $po, "<", $PO_string);
	#open(PPI, "$PPI") || die("Can't open $PPI:!\n");
	#open(PO, "$PO") || die("Can't open $PO:!\n");
	

while (my $line = <$ppi>) {
    chomp $line;
    my @line_array = split(/\s+/, $line);
    $size_of_array = @line_array;
    $line_count ++;
    for (my $i=0; $i < $size_of_array; $i++)
    {
		if ($line_count==1)
		{
		$total_value[$i]=  $line_array[$i];
		}
		else
		{	
		$total_value[$i]=  $total_value[$i]+ $line_array[$i];
		}
	}
   
}
 for (my $i=0; $i < $size_of_array; $i++)
    {
	my $sp=$total_value[$i]/$line_count;
  print $sp_format  "$sp \t";
		   
}

$line_count=0;

while (my $line = <$po>) {
    chomp $line;
    my @line_array = split(/\s+/, $line);
    $size_of_array = @line_array;
    $line_count ++;
    for (my $i=0; $i < $size_of_array; $i++)
    {
		if ($line_count==1)
		{
		$total_value[$i]=  $line_array[$i];
		}
		else
		{	
		$total_value[$i]=  $total_value[$i]+ $line_array[$i];
		}
	}
    
}
 for (my $i=0; $i < $size_of_array; $i++)
    {
	my $sp=$total_value[$i]/$line_count;
  print $sp_format  "$sp \t";
		   
}

print $sp_format "\n";
$line_count=0;

}
