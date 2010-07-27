==Description
Rubyexamples
A place to test some basic ruby:

- helloworld.rb, one of the classic examples
- hellowworldclass.rb, one of the classic examples using ruby classes
- basicSTDin.rb, test of input handling from different sources
- openGL.rb, openGL using ruby
- win32.rb, testing windows32 API
- 3dsreader.rb, Testing the loading of 3ds binary file format (to be used with opengl)
- 3dobject.rb, Class for 3Dobject holding the 3ds binairy data
- server.rb & client.rb - Testing sockets, found: MAYOR bug in RUBY win32 functionality using select([socket,STDIN])

== REQUIREMENTS:

Ruby 1.8 +

=== DEPENDENCIES
I always try to keep dependencies to a minimum however:
- openGL.rb, depends on "gl", "glu", "glut", "mathn" (RubyGem)
- win32.rb, depends on "Win32API"
- client.rb, server.rb depends on "socket"
- No known other dependencies

== LICENSE:

Copyright (c) 2009 Danny Arends

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.