#####################################################################
 # 
 # simpleServer.pl
 #
 # Copyright (c) 2009 Danny Arends
 # Last modified Mrt, 2009
 # First written Jun, 2008
 #
 # SimpleServer: 	Server implementation using sockets in perl, as an easy howto example
 # Depends: 	IO::Socket::INET
 # 
 # 
 #
#####################################################################
#!C:\Perl\bin

#Includes
use IO::Socket::INET;

#Global Variable Declaration
my $running;

sub printProgramInfo{
  printf("simpleServer example program made using Perl"."\n");
  printf("Listens to and accepts all connections and messages"."\n");
  printf("Made by: Danny Arends"."\n"."\n");
}#PrintProgramInfo

sub setupDependencies{
	$running = 1;
} #setupDependencies

# Main routine 
sub main{
	# Create a server socket
	$MySocket=new IO::Socket::INET->new(LocalPort=>1234,Proto=>'udp');

	while($running){
		$MySocket->recv($text,128);
		if($text ne ''){
			printf("received msg: '".$text."'"."\n");
			if($text eq "#admin_server_down"){
				$running=0;
			}
			if($text eq "#quit"){
				printf("client has exited!"."\n");
			}
		}		
	}
} # Main routine

sub cleanUp{
	printf("received exit signal going down."."\n");
} #cleanUP

printProgramInfo();
setupDependencies();
main();
cleanUp();
