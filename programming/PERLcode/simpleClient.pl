#####################################################################
 # 
 # simpleClient.pl
 #
 # Copyright (c) 2009 Danny Arends
 # Last modified Mrt, 2009
 # First written Jun, 2008
 #
 # SimpleClient: 	Client implementation using sockets in perl, as an easy howto example
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
my $def_msg = "Enter message to send to server : ";

sub printProgramInfo{
  printf("simpleClient example program made using Perl"."\n");
  printf("Made by: Danny Arends"."\n"."\n");
}#PrintProgramInfo

sub setupDependencies{
	$running = 1;
}#setupDependencies

# Main routine 
sub main{
	# Create a client socket
	$MySocket = new IO::Socket::INET->new(PeerPort=>1234,Proto=>'udp',PeerAddr=>'localhost');
	
	while($running){
		# Print message to user that he can type
		printf($def_msg);
		# Get message from STDIN
		$msg = <STDIN>;
		chomp $msg;
		if($msg ne ''){
			printf("sending message '".$msg."' ... ");
			if($MySocket->send($msg)){
				#Assertion: $MySocket->send($msg) never fails. Even if there is no server.
				printf("<done>"."\n");
			}
			# "#quit" exits the client
			if($msg eq "#quit"){
				$running = 0;			
			}			
		}
	}
} # Main routine

sub cleanUp{
	print("received exit signal going down."."\n");
} # cleanUp

printProgramInfo();
setupDependencies();
main();
cleanUp();
