
sub showFile{
	my $dir = shift;
	my $name = shift;
	my @rawdata;
	my $line;
	my $text;
	open(FILE, "$dir/$name");
	@raw_data=<FILE>; 
	close(FILE);
	foreach $line (@raw_data)
	{
		chomp($line);
		if($line =~ /<h\C{1}>/){
			#Headers
			$text .= $line."\n";
		}elsif($line eq ""){
			#Empty lines
			$text .= "\n";
		}else{
			#Normal line
			$text .= $line."<br/>"."\n";
		}	
	} 
	return $text;
}

sub ShowTopMenu{
	my $dirname = shift;
	my @files;
	my $full_fileName;
	my $FileName;
	
	@files = <$dirname/*>;
	print("<div align='right'>"."\n");
	foreach $full_fileName (@files) {
		if($full_fileName =~ /\/(\C*)\./){
			$fileName = $1;
			print("<a href='index.cgi?Page=$fileName' class='SButton'>$fileName</a><br/>"."\n");
		}
		
	}
	print("</div>"."\n");
	return;
}

sub printLayout{
	print("\t<form method='post' action='index.cgi'>"."\n");
  print("\t\t<div align='center'>"."\n");
  print("\t\t\t<br/>"."\n");
	print("\t\t\t<table width='1024px'>"."\n");
	print("\t\t\t<tr><td class='span'>&nbsp;</td><td colspan='5' class='top'>"."\n");
	print("\t\t\t<div class='slideshow'>"."\n");
	print("\t\t\t\t<img src='images/bio_top1.png' width='1024px' height='100px' alt='topimage biosources' />"."\n");
	print("\t\t\t\t<img src='images/bio_top2.png' width='1024px' height='100px' alt='topimage biosources' />"."\n");
	print("\t\t\t\t<img src='images/bio_top3.png' width='1024px' height='100px' alt='topimage biosources' />"."\n");
  print("\t\t\t\t<img src='images/bio_top4.png' width='1024px' height='100px' alt='topimage biosources' />"."\n");
  print("\t\t\t\t<img src='images/bio_top5.png' width='1024px' height='100px' alt='topimage biosources' />"."\n");
	print("\t\t\t</div>"."\n");
	print("\t\t\t</td><td class='span'>&nbsp;</td></tr>"."\n");
  print("\t\t\t<tr><td class='span'></td>"."\n");
	print("\t\t\t<td class='navi'>"."\n");
	print(ShowTopMenu("pages")."\n");
	print("\t\t\t</td><td class='main'>"."\n");
	print(showFile("pages",$form{"Page"}.".txt")."\n");
	print("\t\t\t</td><td class='spaning'>&nbsp;</td><td class='span'>&nbsp;</td>"."\n");
	print("\t\t\t<td class='Rnavi'>"."\n");
	print(ShowTopMenu("various")."\n");
	print("\t\t\t</td><td class='span'></td></tr>"."\n");
	print("\t\t\t<tr><td class='span'></td><td colspan='2'>&nbsp;</td><td class='foot' colspan='3'>"."\n");
	print(printVisitor()."\n");
	print("\t\t\t</td><td class='span'></td></tr>"."\n");	 
}

sub printEnviromental{
	print("<h2>Enviromental Variables</h2>"."\n");
	foreach my $key (sort(keys(%ENV))) {
		print("$key = $ENV{$key}<br/>"."\n");
	}
}

sub printVisitor{
	#Variables
	my $client_ip = $ENV{REMOTE_ADDR};
	my $client_hostname = gethostbyaddr(inet_aton($client_ip), AF_INET);	
	my $r_string;
	
	$r_string .= "<font size='1'>Visitor IP: $client_ip<br/></font>"."\n";

	#logger("Visitors.txt","$client_ip, hostname: $client_hostname");

	return $r_string;
}
return 1;