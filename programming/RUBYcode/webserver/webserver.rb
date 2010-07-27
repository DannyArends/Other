#!/usr/bin/env ruby
require "socket"
require 'layout.rb'
require 'image.rb'
require 'styles.rb'
require 'common.rb'

$running = 1

def accept_data(server,session)
	request = session.gets
	raw_peer_struct = session.getpeername
    port = raw_peer_struct[2]*0x100+raw_peer_struct[3]
    adress = "#{(4...8).map{|x|raw_peer_struct[x]}.join(".")}"
	trimmedrequest = request.gsub(/GET\ \//, '').gsub(/\ HTTP.*/, '')
	filename = trimmedrequest.chomp.gsub("html","txt") rescue ""

	if filename == ""
		filename = "index.txt"
	end
	if filename == "restart" && adress=="127.0.0.1"
		session.print "HTTP/1.1 200/OK\r\nContent-type:text/html\r\n\r\n"
		session.print "<html><head><meta HTTP-EQUIV='REFRESH' content='1; url=/index.html'></head><body><h3>Restarting now...</h3></body></html>"
		session.close()
		server.close()
		exec("ruby webserver.rb")
	end
	if filename == "shutdown" && adress=="127.0.0.1"
		session.print "HTTP/1.1 200/OK\r\nContent-type:text/html\r\n\r\n"
		session.print "<html><body><h2>Bye now</h2></body></html>"
		session.close()
		server.close()
		exit(0)
	end

	print "Handling request for data from: ",adress,":" ,port, ":",filename,"\n"
	log = File.open("log.txt", "a")
	log.print Time.now.strftime("[%y/%m/%d %H:%M")   ," : ",adress,":" ,port, ":",filename,"]\n"
	log.close
	if file_type(filename) == "css"
		servecss(session,filename)
	elsif file_type(filename) == "ico"
		serveimage("Images/favicon.png")
	elsif file_type(filename) == "txt"
		session.print "HTTP/1.1 200/OK\r\nContent-type:text/html\r\n\r\n"
		filename = "./Pages/"+filename
		layout(session,filename)
	elsif file_type(filename) == "pdf"
		filename = "./Pages/"+filename
		servepdf(session,filename)
	else
		if(serveimage(session,filename)==nil)
			print("unknown format requested by:",session,"\n")
			session.print("HTTP/1.1 200/OK\r\nContent-type:text/html\r\n\r\n")
			session.print("Not available")
		end
	end
	session.close()
end	


#Main
puts "WebServer v0.2 - (c) Danny Arends 2009\n"
server = TCPServer.new("localhost", 80)
while($running==1)
	result = select([server],nil,nil)
	if(result != nil)
		for read in result[0]
			if(read == server)
				Thread.start(server.accept) do |s|   
					accept_data(server,s)
				end
			end
		end
	end	
end  
