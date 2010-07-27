#!/usr/bin/env ruby
require "gl"
require "glu"
require "glut"

class Object3d
	attr_accessor :vertexarray, :polygonarray, :mapcoordarray
	def initialize
		@vertexarray = Array.new
		@polygonarray = Array.new
		@mapcoordarray = Array.new
	end
	def addvert(vert)
		@vertexarray << vert
	end
	def addpoly(poly)
		@polygonarray << poly
	end
	def addmap(map)
		@mapcoordarray << map
	end	
	def name(name)   
		@name = name   
	end
	
	def renderme
		glBegin(GL_POLYGON)
		@polygonarray.each do |poly|
			glVertex3f(vertexarray[poly.a].x, vertexarray[poly.a].y, vertexarray[poly.a].z)
			glVertex3f(vertexarray[poly.b].x, vertexarray[poly.b].y, vertexarray[poly.b].z)
			glVertex3f(vertexarray[poly.c].x, vertexarray[poly.c].y, vertexarray[poly.c].z)
		end
		glEnd()
		
	end
	
end

class Vertex
	attr_accessor :x, :y, :z
	def initialize(x,y,z)   
		@x,@y,@z = x,y,z
	end  
end

class Polygon
	attr_accessor :a, :b, :c
	def initialize(a,b,c)   
		@a,@b,@c = a,b,c
	end 
end

class Mapcoord
	attr_accessor :u, :v
	def initialize(u,v)   
		@u,@v = u,v
	end 
end