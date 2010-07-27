#####################################################################
 # 
 # executeR.pl
 #
 # Copyright (c) 2009 Danny Arends
 # Last modified Mrt, 2009
 # First written Feb, 2009
 #
 # executeR: 	executing and R-script from perl and receiving back the resulting calculation. Exposing basic R routines to Perl, 
 #			It batches the R script in slave mode, to only catch meaningfull information
 # Depends: 	NONE
 # 
 # 
 #
#####################################################################
#!C:\Perl\bin

#Includes

#Global Variable Declaration

sub printProgramInfo{
  printf("Example program executing an Rscript, and gets result made using Perl"."\n");
  printf("Made by: Danny Arends"."\n"."\n");
}#PrintProgramInfo

sub setupDependencies{

}#setupDependencies

sub generateRscript{
	open FILE, ">script.r" or die $!;
	print FILE "x<-1:10"."\n";
	print FILE "x"."\n";
	print FILE "y<-rbind(1:10,11:20,21:30)"."\n";
	print FILE "y"."\n";	
	print FILE "quit(save=\"no\")"."\n";
	close(FILE);	
} #generateRscript

sub executeRscript{
	my $command;
	my $result;

	$command = "R CMD BATCH -q --slave script.r out.txt";
	printf($command."\n");
	$result = `$command`;
	printf($result."\n");
} #executeRscript

sub parseOutput{
	open FILE, "<out.txt" or die $!;
	while (<FILE>) {
		my $line = $_;
		chomp($line);
		if ($line =~ m/\[\d\]\ +(.+)/) {
			printf("Result: '".$1."'"."\n");
		}elsif($line =~ m/\[(\d),\]\ +(.+)/){
			printf("Matrixrow ".$1.": '".$2."'"."\n");
		}elsif ($line =~ m/(\d+\.?\d*)\ +(\d+\.?\d*)\ +(\d+\.?\d*)/) {
			printf("Time: '".$1."','".$2."','".$3."'"."\n");
		}
	}
	close(FILE);	
} #parseOutput

# Main routine 
sub main{
	generateRscript();
	executeRscript();
	parseOutput();
} # Main routine

sub cleanUp{
	my $command;
	my $result;

	printf("Deleting temp files"."\n");	
	$command = "rm script.r";
	$result = `$command`;
	$command = "rm out.txt";
	$result = `$command`;
	printf("Done"."\n");	
} # cleanUp

printProgramInfo();
setupDependencies();
main();
cleanUp();
