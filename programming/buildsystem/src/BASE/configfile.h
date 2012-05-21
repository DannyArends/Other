/**
 * \file BASE/configfile.h
 * \brief Header file, for BASE/configfile.cpp
 *
 * Copyright (c) 2004 Richard J. Wagner
 *
 **/
// Class for reading named values from configuration files
// Richard J. Wagner  v2.1  24 May 2004  wagnerr@umich.edu

//
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef CONFIGFILE_H_
  #define CONFIGFILE_H_
  #include "basicincludes.h"

  /**
  * \brief The configuration file reader/writer.<br>
  *
  * Class for reading named values from configuration files
  * Richard J. Wagner  v2.1  24 May 2004  wagnerr@umich.edu
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class configfile {
  protected:
    string myDelimiter;  // separator between key and value
    string myComment;    // separator between value and comments
    string mySentry;     // optional string to signal end of file
    map<string,string> myContents;  // extracted keys and values

    typedef map<string,string>::iterator mapi;
    typedef map<string,string>::const_iterator mapci;

  // Methods
  public:
    configfile( string filename,
                string delimiter = "=",
                string comment = "#",
          string sentry = "EndConfigFile" );
    configfile();

    // Search for key and read value or optional default value
    template<class T> T read( const string& key ) const;  // call as read<T>
    template<class T> T read( const string& key, const T& value ) const;
    template<class T> bool readInto( T& var, const string& key ) const;
    template<class T>
    bool readInto( T& var, const string& key, const T& value ) const;

    // Modify keys and values
    template<class T> void add( string key, const T& value );
    void remove( const string& key );

    // Check whether key exists in configuration
    bool keyExists( const string& key ) const;

    // Check or change configuration syntax
    string getDelimiter() const { return myDelimiter; }
    string getComment() const { return myComment; }
    string getSentry() const { return mySentry; }
    string setDelimiter( const string& s )
      { string old = myDelimiter;  myDelimiter = s;  return old; }
    string setComment( const string& s )
      { string old = myComment;  myComment = s;  return old; }

    // Write or read configuration
    friend ostream& operator<<( ostream& os, const configfile& cf );
    friend istream& operator>>( istream& is, configfile& cf );

  protected:
    template<class T> static string T_as_string( const T& t );
    template<class T> static T string_as_T( const string& s );
    static void trim( string& s );


  // Exception types
  public:
    /**
    * \brief Helper structure for the configuration file reader/writer.<br>
    *
    * Class for handling file not found events
    * Richard J. Wagner  v2.1  24 May 2004  wagnerr@umich.edu
    *
    * TODO Description<br>
    * bugs: none found<br>
    */
    struct file_not_found {
      string filename;
      file_not_found( const string& filename_ = string() )
        : filename(filename_) {}
    };
    /**
    * \brief Helper structure for the configuration file reader/writer.<br>
    *
    * Class for handling key not found events
    * Richard J. Wagner  v2.1  24 May 2004  wagnerr@umich.edu
    *
    * TODO Description<br>
    * bugs: none found<br>
    */
    struct key_not_found {  // thrown only by T read(key) variant of read()
      string key;
      key_not_found( const string& key_ = string() )
        : key(key_) {}
    };
  };


  /* static */
  template<class T>
  string configfile::T_as_string( const T& t )
  {
    // Convert from a T to a string
    // Type T must support << operator
    ostringstream ost;
    ost << t;
    return ost.str();
  }


  /* static */
  template<class T>
  T configfile::string_as_T( const string& s )
  {
    // Convert from a string to a T
    // Type T must support >> operator
    T t;
    istringstream ist(s);
    ist >> t;
    return t;
  }


  /* static */
  template<>
  inline string configfile::string_as_T<string>( const string& s )
  {
    // Convert from a string to a string
    // In other words, do nothing
    return s;
  }


  /* static */
  template<>
  inline bool configfile::string_as_T<bool>( const string& s )
  {
    // Convert from a string to a bool
    // Interpret "false", "F", "no", "n", "0" as false
    // Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
    bool b = true;
    string sup = s;
    for( string::iterator p = sup.begin(); p != sup.end(); ++p )
      *p = toupper(*p);  // make string all caps
    if( sup==string("FALSE") || sup==string("F") ||
        sup==string("NO") || sup==string("N") ||
        sup==string("0") || sup==string("NONE") )
      b = false;
    return b;
  }


  template<class T>
  T configfile::read( const string& key ) const
  {
    // Read the value corresponding to key
    mapci p = myContents.find(key);
    if( p == myContents.end() ) throw key_not_found(key);
    return string_as_T<T>( p->second );
  }


  template<class T>
  T configfile::read( const string& key, const T& value ) const
  {
    // Return the value corresponding to key or given default value
    // if key is not found
    mapci p = myContents.find(key);
    if( p == myContents.end() ) return value;
    return string_as_T<T>( p->second );
  }


  template<class T>
  bool configfile::readInto( T& var, const string& key ) const
  {
    // Get the value corresponding to key and store in var
    // Return true if key is found
    // Otherwise leave var untouched
    mapci p = myContents.find(key);
    bool found = ( p != myContents.end() );
    if( found ) var = string_as_T<T>( p->second );
    return found;
  }


  template<class T>
  bool configfile::readInto( T& var, const string& key, const T& value ) const
  {
    // Get the value corresponding to key and store in var
    // Return true if key is found
    // Otherwise set var to given default
    mapci p = myContents.find(key);
    bool found = ( p != myContents.end() );
    if( found )
      var = string_as_T<T>( p->second );
    else
      var = value;
    return found;
  }


  template<class T>
  void configfile::add( string key, const T& value )
  {
    // Add a key with given value
    string v = T_as_string( value );
    trim(key);
    trim(v);
    myContents[key] = v;
    return;
  }

#endif  // CONFIGFILE_H_

