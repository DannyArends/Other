#!/usr/bin/env ruby
require 'socket'  

def checkinput(string)
	case(string)
		when "#client_exit\n"
			puts "Exit program received...\n"
			exit(0)
		else
			puts "Going to send:" + string
			server = TCPSocket.new( "127.0.0.1", 3000 ) rescue false
			if(server)
				server.write(string)
				aa = server.recv(100)
				puts "Response from server:"+aa+"\n"
				server.close 
			elsif
				puts "No server connection available."
			end
	end
end	

#Main
puts "Client v0.1 - (c) Danny Arends 2009\n"
ARGV.each do|a|
	puts "Called with argument: #{a}"+"\n"
end
while(1)
	input = STDIN.readline()
	checkinput(input)
end


