def listall(session,path)
	fullpath = Dir.pwd + "/" + path
	str = ""
	Dir.foreach(fullpath) do |entry|
		name = entry.gsub(".#{file_type(entry)}","")
		ref = entry.gsub(".txt",".html")
		str = str + "<a href='"+ref+"' class='SButton'>"+name+"</a><br/>" if(!(entry.length < 3))
	end
	str
end
