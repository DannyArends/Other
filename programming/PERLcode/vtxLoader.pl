#####################################################################
 # 
 # VTXLoader.pl
 #
 # Copyright (c) 2009 Danny Arends
 # Last modified Mrt, 2009
 # First written Jun, 2008
 #
 # VTXLoader: 	loads VTX files (produced by blender/animator) and converts them into vertices that can be used in openGL.pl
 # Depends: 	Math::trig
 # 
 # 
 #
#####################################################################
#!C:\Perl\bin

#Includes
use strict;
use Math::Trig;

#Global variables
my %vertex;
my %face;

#Our datafile (should be gotten via
my $data_file="Data/Round.vtx";

sub printProgramInfo{
  printf("Simple layout of a vtx file loader using Perl."."\n");
  printf("Simple layout of a vtx file loader using Perl."."\n");  
  printf("Made by: Danny Arends."."\n");
}#PrintProgramInfo

sub readModels{

	my $vertex=0;
	my $vertexnum=0;
	my $face=0;
	my $facenum=0;
	my $objectid=0;

	open FILE, "<$data_file" or die $!;
	while (<FILE>) {
		my $line = $_;
		chomp($line);
		if($line eq ".Vertex"){
			$objectid++;
			$vertex=1;
		}
		if($line eq "// end of .Vertex"){
			$vertex=0;
			$vertexnum=0;
		}
		if($line eq ".Index"){
			$face=1;
		}
		if($line eq "// end if .Index"){
			$face=0;
			$facenum=0;
		}
		if($vertex){
			my @coords = split(/ /,$line);
			my $size = scalar @coords;
			if($size > 3){
				$vertex{$objectid}{$vertexnum}{x} = @coords[0];
				$vertex{$objectid}{$vertexnum}{y} = @coords[1];
				$vertex{$objectid}{$vertexnum}{z} = @coords[2];
				$vertexnum++;
			}
		}
		if($face){
			my @coords = split(/ /,$line);
			my $size = scalar @coords;
			if($size > 3){
			$face{$objectid}{$facenum}{1} = @coords[0];
			$face{$objectid}{$facenum}{2} = @coords[1];
			$face{$objectid}{$facenum}{3} = @coords[2];
			$facenum++;
			}
		}
		if($face and $vertex){
			print("readerror");
			return 0;
		}
	}
	close(FILE);
} #readModels

sub printTriangles{
	my $objectid;
	my $faceid;
	my $triangle=0;
	open FILE, ">out.txt" or die $!;
	foreach $objectid (keys %face) {
		foreach $faceid (sort keys %{$face{ $objectid }} ) {
			print FILE "// Triangle" . $triangle."\n";
			print FILE $vertex{$objectid}{$face{$objectid}{$faceid}{1}}{x}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{1}}{y}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{1}}{z}/8 ."\n";
			print FILE $vertex{$objectid}{$face{$objectid}{$faceid}{2}}{x}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{2}}{y}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{2}}{z}/8 ."\n";
			print FILE $vertex{$objectid}{$face{$objectid}{$faceid}{3}}{x}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{3}}{y}/8 ." ".$vertex{$objectid}{$face{$objectid}{$faceid}{3}}{z}/8 ."\n";
			print FILE "\n";
			$triangle++;
		}
		
	}
	close(FILE);
} #printTriangles

printProgramInfo();
readModels();
printTriangles();