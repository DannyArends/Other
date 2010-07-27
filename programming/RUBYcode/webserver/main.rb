def listcontent(filename)
	begin
		file = File.open(filename, 'rb')
		content = file.read().gsub("\n","<br/>")
	rescue Errno::ENOENT
		content = "File not found"
	end
	content
end