def file_type( filename )
	File.extname( filename ).gsub( /^\./, '' ).downcase 
end

def servepdf(session,filename)
	session.print "HTTP/1.1 200/OK\r\nContent-type:text/#{file_type(filename)}\r\n\r\n"
	begin
		displayfile = File.open(filename, 'rb')
		content = displayfile.read()
		session.print content
	rescue 
		content = nil
	end
	content
end

def listlog()
	content = "<font size='1'>"
	begin
		file = File.open("log.txt", 'r')
		counter=0
		
		file.read.split("\n").reverse.each do |line|
			if (counter < 5 && line =~ /theme.css/)
			content = content + line.gsub(":Style/theme.css","") + "<br/>" 
			counter = counter+1
			end
		end
		content = content + "</font>"
	rescue Errno::ENOENT
		content = "File not found"
	end
end