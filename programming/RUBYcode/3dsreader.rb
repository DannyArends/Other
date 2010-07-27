#!/usr/bin/env ruby
require '3dobject.rb'

def read3ds(file)
	object = Object3d.new()
	source = File.open(file,"rb")
	print "Opening file at path:",file,"\n"
	while !source.eof
	chunkid = source.read(2).unpack("s").to_s.to_i.to_s(base=16)
	chunklength = source.read(4).unpack("I").to_s
	#chunklength = source.read(4).unpack("v").to_s
	name = ""
	#print "#{chunkid}->#{chunklength} "
	if(chunkid=="4d4d")
		puts "Main block found"
	elsif(chunkid=="3d3d")
		puts "3D editor chunk"
	elsif(chunkid=="4000")
		print "Objectblock found -> "
		i=0
		char = ""
		while(char != "\0" && i<20)
			char = source.read(1).unpack("a").to_s  rescue "\0"
			name = name + char
			i = i+1
		end
		puts "Objectname: " + name
		object.name(name)
	elsif(chunkid == "4100")
		puts "Triangular mesh block found"
	elsif(chunkid == "4110")
		print "Vertices list found -> "
		nvert = source.read(2).unpack("s").to_s.to_i
		puts "Number of vertices: "+ nvert.to_s
		while(nvert > 0)
			x = source.read(4).unpack("f")[0]
			y = source.read(4).unpack("f")[0]
			z = source.read(4).unpack("f")[0]
			vert = Vertex.new(x,y,z)
			object.addvert(vert)
			#print "#{x},#{y},#{z},\n"
			nvert = nvert-1
		end
	elsif(chunkid == "4120")
		print "Polygon desciption found -> "
		npoly = source.read(2).unpack("s").to_s.to_i
		puts "Number of polygons: "+ npoly.to_s
		while(npoly > 0)
			a = source.read(2).unpack("s")[0]
			b = source.read(2).unpack("s")[0]
			c = source.read(2).unpack("s")[0]
			flags = source.read(2).unpack("s")[0]
			poly = Polygon.new(a,b,c)
			object.addpoly(poly)			
			#print "#{a},#{b},#{c},#{flags}\n"
			npoly = npoly-1
		end
	elsif(chunkid == "4140")
		print "Mapping coordinates found -> "
		nmap = source.read(2).unpack("s").to_s.to_i
		puts "Number of mappings: "+ nmap.to_s
		while(nmap > 0)
			u = source.read(4).unpack("f")[0]
			v = source.read(4).unpack("f")[0]
			map = Mapcoord.new(u,v)
			object.addmap(map)	
			#print "#{u},#{v}\n"
			nmap = nmap-1
		end
	else
	source.seek((chunklength.to_i-6)+source.pos)
	end
	end
	object
end

#Main
puts "3DSreader for ruby v0.1 - (c) Danny Arends 2009\n"
ARGV.each do |a|
	puts "Called with argument: #{a}"+"\n"
end

