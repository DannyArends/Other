require 'menu.rb'
require 'main.rb'

def layout(session,filename)
	name = filename.gsub(".txt",".html")
	name = name.gsub("./Pages/","")	
	session.print "<html>"
	session.print "<head>"
	session.print "<link href='Style/theme.css' type='text/css' rel='stylesheet'>"
	session.print "<title>Webservice v0.2 Danny Arends - "+name+"</title>"
	session.print "</head>"
	session.print "<body>"
	session.print "<table width='100%' height='100%'>"
	session.print "<tr>"
	session.print "<td colspan='3' class='top'><h1>"+name+"</h1></td>"
	session.print "</tr>"
	session.print "<tr>"
	session.print "<td class='navi'>"+listall(session,"Pages")+"</td>"
	session.print "<td class='main'>"+listcontent(filename)+"</td>"
	session.print "<td class='navi'>"+listall(session,"Server") + "<br/><br/>Previous visitors:<br/>" + listlog() + "</td>"
	session.print "</tr>"
	session.print "<tr>"
	session.print "<td colspan='3' class='foot'>FOOTER</td>"
	session.print "</tr>"
	session.print "</table>"
	session.print "</body>"
	session.print "</html>"
end