#!/usr/bin/env ruby -rubygems
require "gl"
require "glu"
require "glut"
require "mathn"
require '3dobject.rb'
require '3dsreader.rb'

# Add GL and GLUT namespaces
include Gl
include Glu
include Glut

# Placeholder for the window object
$window = ""

#2 Objects rotating, variables holding this information
$pyramid_angle = 0
$cube_angle = 0

$object1 = Object3d.new

$window_width=640
$window_height=480

def init_gl_window(width = 640, height = 480)
	# Background color to black
	glClearColor(0.0, 0.0, 0.0, 0)
	# Enables clearing of depth buffer
	glClearDepth(1.0)
	# Set type of depth test
	glDepthFunc(GL_LEQUAL)
	# Enable depth testing
	glEnable(GL_DEPTH_TEST)
	# Enable smooth color shading
	glShadeModel(GL_SMOOTH)

	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	# Calculate aspect ratio of the window
	gluPerspective(45.0, width / height, 0.1, 100.0)
end


def reshape(width, height)
	height = 1 if height == 0

	# Reset current viewpoint and perspective transformation
	glViewport(0, 0, width, height)

	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluPerspective(45.0, width / height, 0.1, 100.0)
end


def draw_gl_scene
	# Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

	# Reset the view
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

	# Move left 1.5 units and into the screen 6.0 units
	glTranslatef(-1.5, 0.0, -10.0)

	# Rotate the pyramid on the Y-axis
	glRotatef($pyramid_angle, 0.0, 1.0, 0.0)
	# Set color: Red
	glColor3f(1.0, 0.0, 0.0)
	# Draw a pyramid
	$object1.renderme()

	glLoadIdentity()
	# Move right 1.5 units and into the screen 6.0 units

	glTranslatef(1.5, 0.0, -6.0)
	# Rotate the cube on the X, Y and Z axis
	glRotatef($cube_angle, 1.0, 1.0, 1.0)
	#Set color Green
	glColor3f(0.0, 1.0, 0.0)

	#Draw cube
	glBegin(GL_QUADS)
		# Draw the top side
		glVertex3f( 1.0,  1.0, -1.0)
		glVertex3f(-1.0,  1.0, -1.0)
		glVertex3f(-1.0,  1.0,  1.0)
		glVertex3f( 1.0,  1.0,  1.0)
		# Draw the bottom side
		glVertex3f( 1.0, -1.0,  1.0)
		glVertex3f(-1.0, -1.0,  1.0)
		glVertex3f(-1.0, -1.0, -1.0)
		glVertex3f( 1.0, -1.0, -1.0)
		# Draw the front side
		glVertex3f( 1.0,  1.0,  1.0)
		glVertex3f(-1.0,  1.0,  1.0)
		glVertex3f(-1.0, -1.0,  1.0)
		glVertex3f( 1.0, -1.0,  1.0)
		# Draw the back side
		glVertex3f( 1.0, -1.0, -1.0)
		glVertex3f(-1.0, -1.0, -1.0)
		glVertex3f(-1.0,  1.0, -1.0)
		glVertex3f( 1.0,  1.0, -1.0)
		# Draw the left side
		glVertex3f(-1.0,  1.0,  1.0)
		glVertex3f(-1.0,  1.0, -1.0)
		glVertex3f(-1.0, -1.0, -1.0)
		glVertex3f(-1.0, -1.0,  1.0)
		# Draw the right side
		glVertex3f( 1.0,  1.0, -1.0)
		glVertex3f( 1.0,  1.0,  1.0)
		glVertex3f( 1.0, -1.0,  1.0)
		glVertex3f( 1.0, -1.0, -1.0)
	glEnd()

	$pyramid_angle += 0.2
	$cube_angle -= 0.15

	# Swap buffers for display 
	glutSwapBuffers()
end

#Idle function
def idle
	sleep 0.001
	glutPostRedisplay()
end

# Keyboard handler
def checkkeydown(key,x,y)
	case(key)
		when ?\e
			glutDestroyWindow($window)
			exit(0)
	end
end	


# Initliaze our GLUT code
def ourinit
	$object1 = read3ds("./testdata/Cube.3ds")
	glutInit()
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH)
	glutInitWindowSize($window_width, $window_height)
	glutInitWindowPosition(0, 0)
	$window = glutCreateWindow("OpenGL using ruby v0.1 - (c) Danny Arends 2009")
	glutDisplayFunc(method(:draw_gl_scene).to_proc)
	glutReshapeFunc(method(:reshape).to_proc)
	glutIdleFunc(method(:idle).to_proc)
	glutKeyboardFunc(method(:checkkeydown).to_proc)
	init_gl_window($window_width, $window_height)
end

puts "OpenGL using ruby v0.1 - (c) Danny Arends 2009\n"
ourinit()
glutMainLoop()
