def servecss(session,filename)
	session.print "HTTP/1.1 200/OK\r\nContent-type:text/css\r\n\r\n"
	begin
		displayfile = File.open(filename, 'r')
		content = displayfile.read()
		session.print content
	rescue Errno::ENOENT
		session.print "no.css"
	end
end