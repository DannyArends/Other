#####################################################################
 # 
 # openGL.pl
 #
 # Copyright (c) 2009 Danny Arends
 # Last modified Mrt, 2009
 # First written Jun, 2008
 #
 # openGL: 	Example on howto easely initialize an openGL program in the perl programming langauge
 # Depends: 	OpenGL
 # 			Math::Trig
 # 
 #
#####################################################################

#!C:\Perl\bin

#Includes
use strict;
use Math::Trig;
#openGL include make sure u have openGL for perl installed
use OpenGL qw/ :all /;

#Constants
use constant PROGRAM => "OpenGL Benchmark - Perl Binding";

#Global Variable Declaration
my $running;
my %data;

my $window;
my $window_X = 512;
my $window_Y = 512;

my $idVertexProg = 0;
my $idFragProg = 0;

my $incY = 0.5;
my $rotY = 0.0;


sub printProgramInfo{
	printf("Layout of an Perl program using the openGL extensions"."\n");
	printf("Made by: Danny Arends"."\n"."\n");
}#PrintProgramInfo

sub resizeScene
{ my($width,$height) = @_;
  if (!$height){
	$height = 1;
  }

  glViewport(0, 0, $width, $height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,$width/$height,0.1,100.0);

  glMatrixMode(GL_MODELVIEW);

  #$window_X  = $width;
  #$window_Y = $height;
}

sub checkVersion
{
  my $version = glGetString(GL_VERSION);
  my $vendor = glGetString(GL_VENDOR);
  my $renderer = glGetString(GL_RENDERER);
  my $exts = glGetString(GL_EXTENSIONS);

  printf("%s\n\n", PROGRAM);
  printf("OpenGL: %s\n", $version);
  printf("Vendor: %s\n", $vendor);
  printf("Renderer: %s\n", $renderer);
  printf("\n");
}

sub initProgs
{
  # NOP Vertex shader
  my $vertexProg = qq
  {!!ARBvp1.0
    TEMP vertexClip;
    DP4 vertexClip.x, state.matrix.mvp.row[0], vertex.position;
    DP4 vertexClip.y, state.matrix.mvp.row[1], vertex.position;
    DP4 vertexClip.z, state.matrix.mvp.row[2], vertex.position;
    DP4 vertexClip.w, state.matrix.mvp.row[3], vertex.position;
    MOV result.position, vertexClip;
    MOV result.color, vertex.color;
    MOV result.texcoord[0], vertex.texcoord;
    MOV result.texcoord[1], vertex.normal;
    END
  };

  # Black Light Fragment shader
  my $fragProg = qq
  {!!ARBfp1.0
    TEMP decal,color;
    TEX decal, fragment.texcoord[0], texture[0], 2D;
    MUL result.color, decal, fragment.texcoord[1];
    END
  };

  ($idVertexProg,$idFragProg) = glGenProgramsARB_p(2);


  glBindProgramARB(GL_VERTEX_PROGRAM_ARB, $idVertexProg);
  glProgramStringARB_p(GL_VERTEX_PROGRAM_ARB, $vertexProg);


  glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, $idFragProg);
  glProgramStringARB_p(GL_FRAGMENT_PROGRAM_ARB, $fragProg);

}

sub setupDependencies{
	$running = 1;
}

sub init{
 checkVersion();
 resizeScene();
 initProgs();
}

sub display{
  # Set up ModelView
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0,0.0,-1.0);
  glRotated(0.0,1.0,0.0,0.0);
  
  # Set attributes
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  # Clear render buffer and rendering color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1.0,1.0,1.0);
   
  # Render using our shader and fragment program
  glEnable(GL_VERTEX_PROGRAM_ARB);
  glEnable(GL_FRAGMENT_PROGRAM_ARB);
 
  # TODO Render

  glDisable(GL_FRAGMENT_PROGRAM_ARB);
  glDisable(GL_VERTEX_PROGRAM_ARB);

  # Double-buffer and done
  glutSwapBuffers();

}

sub keyPressed
{
  my $key = shift;
  my $c = uc chr $key;
  if ($key == 27 or $c eq 'Q')
  {
	exit(0);
  }
}
 
# Main routine 
sub main{
	#Start Main_Loop
	while($running){
		glutInit(@ARGV);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
		glutInitWindowSize($window_X,$window_Y);
		$window = glutCreateWindow(PROGRAM);
		glutDisplayFunc(\&display);
		glutIdleFunc(\&display);
		glutReshapeFunc(\&resizeScene);
		glutKeyboardFunc(\&keyPressed);
		init();
		glutMainLoop();
	}
	#End Main_Loop
}#Main

#Main functions of the program
printProgramInfo();
setupDependencies();
main();