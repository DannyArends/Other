/**
 * \file BASE/database.h
 * \brief Header file, for BASE/database.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#ifndef DATABASE_H_
  #define DATABASE_H_
  #include "BASE.h"

  /** 
  * \brief SQLlite3 database front end
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class database{
    public:
      database();
      bool            executequery(string query);
      sqlite3*        getdatabase(void);
      uint            rows(string tablename);
      uint            cols(string tablename);
      vector<string>  getheaders(string tablename);
      vector<string>  getcontent(string tablename);
      vector<string>  getcol(string tablename, string colname);
      vector<string>  getrow(string tablename, uint id);
      bool            keyexists(string tablename,string colname, string key);
      bool            idofkey(string tablename,string colname, string key);
      bool            deleterow(string tablename, uint id);
      string          getdatafield(string tablename, string colname,uint id);
      ~database();
    private:
    sqlite3* db;
    bool     debugmode;
    char*    errormessage;
    int      initresult;
  };

  /**
  * \brief Virtual class, the ability to database save / update any object<br>
  *
  * TODO Description<br>
  * bugs: none found<br>
  */
  class databaseobject : public object, public node<databaseobject>, public database{
    public:
              databaseobject();
      void    initdb(void);
      bool    save(void);
      bool    remove(void);
      virtual bool    load(void){ return false; }
      string  uinttostring(uint number);
      string  floattostring(float number);
      bool    update(void);
      virtual ~databaseobject();
      /**
       * Decompose the name of an object into a string. Helper function to be able to do SELECT * from X
       * bugs: none found
       * @return string String decomposition of the name of the object<br>
       */
      virtual string           getobjectname()=0;
    private:
      /**
       * Decompose an object into structures strings. These are type specific <b>columns names</b> for a given
       * database object aware type. An example an object with a UINT id will have a column primary key
       * id of type INTEGER). All the structured types of the refered object p are checked and converted
       * into the database stringnamed counterparts.
       * bugs: none found
       * @return vector<string> String decomposition that we can feed to the database<br>
       */
      virtual vector<string>   decomposestructs()=0;
      /**
       * Decompose an object into types strings. These will end up as the <b>column type constraints</b> for a
       * given database aware object item. Thus int,uint will be translated to INTEGER.
       * bugs: none found
       * @return vector<string> String decomposition that we can feed to the database<br>
       */
      virtual vector<string>   decomposetypes()=0;
      /**
       * Decompose the values of an object into strings. Helper function for inserting gets the values of all
       * the structs for insertion into the database. the resulting string needs to be concatenated with ','
       * to be used as SQL INSERT X into Y
       * bugs: none found
       * @return vector<string> String decomposition that we can feed to the database<br>
       */
      virtual vector<string>   decomposevalues()=0;
  };
  
#endif
