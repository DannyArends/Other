#!/usr/bin/env ruby

puts "Filereader v0.1 - (c) Danny Arends 2009\n"
ARGV.each do |a|
	puts "Called with argument: #{a}"+"\n"
end
path = ["./testdata/README.txt","./testdata/Cube.3ds"]
path.each do |file|
	source = File.open(file,"r")
	puts "Opening file at path:",file
	text = true
	source.each_byte do |byte|
		if byte < 9
			text = false
		end
	end
	source.rewind
	source.each_byte do |byte|		
		if(text)
			print "#{byte.chr}"
		elsif	
			print "#{byte.to_s(base=16)} "
		end
	end
	puts "\n"
	source.close
end


