#!/usr/bin/env ruby
require "socket"

def accept_data(s)
    print("Receiving data from:",s.peeraddr,"\n")   
	str = s.recv(100)   
	checkinput(str)
	s.write("Received") 
    s.close 
end	

def checkinput(string)
	case(string)
		when "#server_exit\n"
			puts "Exit program received...\n"
			exit(0)
		else
		puts "> " + string
	end
end	

#Main
puts "Server v0.1 - (c) Danny Arends 2009\n"
ARGV.each do|a|
	puts "Called with Argument: #{a}"+"\n"
end
server = TCPServer.new('localhost', 3000)
while(1)
	#AND UNFORTUNATELY HERE THERE IS A RUBY BUG.... under windows select doesn't set STDIN to nonblocking
	result = select([server],nil,nil)
	if(result != nil)
		for read in result[0]
			if(read == server)
				Thread.start(server.accept) do |s|   
					accept_data(s)
				end
			elsif(read == STDIN)	
			#we end up here
			end
		end
	end	
end  
