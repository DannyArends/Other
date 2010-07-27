#!/usr/bin/env ruby
class Hail
  def world
    puts "Hello, Earthlings"+"!\n"
  end
  def mars
    puts "Hello, Martians"+"!\n"
  end
  def other(string)
	puts "Hello, "+string+"!\n"
  end
  public :world
  public :mars
  public :other
end

hello = Hail.new  
hello.world()
hello.mars()
hello.other("Danny")
