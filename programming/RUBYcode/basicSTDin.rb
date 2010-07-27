#!/usr/bin/env ruby
# Keyboard handler
def checkinput(string)
	case(string)
		when "exit\n"
			puts "Exit program received...\n"
			exit(0)
		else
		puts "> " + string
	end
end	

#Check incomming parameters and print em
ARGV.each do|a|
	puts "Called with Argument: #{a}"+"\n"
end

#Go into while looping
while(1)
	input = STDIN.readline()
	checkinput(input)
end
