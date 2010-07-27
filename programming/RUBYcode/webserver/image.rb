require 'common.rb'

def serveimage(session,filename)
	session.print "HTTP/1.1 200/OK\r\nContent-type:image/#{file_type(filename)}\r\n\r\n"
	begin
		displayfile = File.open(filename, 'rb')
		content = displayfile.read()
		session.print content
	rescue 
		content = nil
	end
	content
end