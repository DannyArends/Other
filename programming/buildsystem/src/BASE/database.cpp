/**
 * \file BASE/database.cpp
 * \brief Code file, Implementation of class: \ref database
 *
 * Copyright (c) 2010 Danny Arends
 *
 **/

#include "database.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s=%s",azColName[i],argv[i] ? argv[i] : "NULL");
  }
  return 0;
}

/**
* \brief The database class using an sqlite 3 database<BR>
*
* TODO Description
* bugs: none found
*/
database::database(){
  //cout << "[DATABASE]\tStarting" << endl;
  this->errormessage = 0;
  this->debugmode = true;
  initresult = sqlite3_open("store.sqlite", &this->db);
  if(initresult){
    cerr << "Can't open database: " << sqlite3_errmsg(this->db) << endl;
    sqlite3_close(this->db);
  }else{
    //cout << "[DATABASE]\tStarted on store.sqlite" << endl;
  }
}

bool database::executequery(string query){
  initresult = sqlite3_exec(db, query.c_str(), callback, 0, &errormessage);
  if(initresult != SQLITE_OK){
    if(debugmode)cerr << "[DATABASE]\tSQL error: " << errormessage << " on query: " << query << endl;
    return false;
  }else{
    if(debugmode)cout << "[DATABASE]\tSQL successful on query: " << query << endl;
    return true;
  }
}

uint      database::rows(string tablename){
  return 0;
}

uint      database::cols(string tablename){
  return 0;
}

vector<string> database::getheaders(string tablename){
  vector<string> headers;
  int ncol,nrow;
  char** result;
  string query = "select * from " + tablename + ";";

  int rc = sqlite3_get_table(db,query.c_str(),&result,&nrow,&ncol,&errormessage);
  if( rc == SQLITE_OK ){
    for(int i=0; i < ncol; ++i){
      headers.push_back(result[i]);   /* First row heading */
    }
  }
  sqlite3_free_table(result);
  return headers;
}

vector<string> database::getcontent(string tablename){
  vector<string> data;
  int ncol,nrow;
  char** result;
  string query = "select * from " + tablename + ";";

  int rc = sqlite3_get_table(db,query.c_str(),&result,&nrow,&ncol,&errormessage);
  if( rc == SQLITE_OK ){
    for(int j=0; j < ncol*nrow; ++j){
      data.push_back(result[ncol+j]);
    }
  }
  sqlite3_free_table(result);
  return data;
}

vector<string>  database::getcol(string tablename, string colname){
  vector<string> data;
  int ncol,nrow;
  char** result;
  string query = "select " + colname + " from " + tablename + ";";

  int rc = sqlite3_get_table(db,query.c_str(),&result,&nrow,&ncol,&errormessage);
  if( rc == SQLITE_OK ){
    cout << "[DATABASE]\tRetrieved column " << colname << " data:" <<  endl << "[DATABASE]\t";
    for(int j=0; j < ncol*nrow; ++j){
      cout << result[ncol+j] << ", ";
      data.push_back(result[ncol+j]);
    }
    cout << endl;
  }
  sqlite3_free_table(result);
  return data;
}

vector<string> database::getrow(string tablename, uint id){
  vector<string> data;
  int ncol,nrow;
  char** result;
  stringstream oss;
  oss << id;
  string query = "select * from " + tablename + " where "+tablename+"id= "+oss.str() +";";
  int rc = sqlite3_get_table(db,query.c_str(),&result,&nrow,&ncol,&errormessage);
  if( rc == SQLITE_OK ){
    cout << "[DATABASE]\tRetrieved row " << id << " data:" <<  endl << "[DATABASE]\t";
    for(int j=0; j < ncol*nrow; ++j){
      cout << result[ncol+j] << ", ";
      data.push_back(result[ncol+j]);
    }
    cout << endl;
  }
  sqlite3_free_table(result);
  return data;
}

bool database::keyexists(string tablename,string colname, string key){
  vector<string> data = this->getcol(tablename,colname);
  for(uint u=0;u < data.size();u++){
    if(key==data[u]) return true;
  }
  return false;
}

bool database::idofkey(string tablename,string colname, string key){
  vector<string> data = this->getcol(tablename,colname);
  for(uint u=0;u < data.size();u++){
    if(key==data[u]) return true;
  }
  return false;
}

bool database::deleterow(string tablename, uint id){
  stringstream oss;
  oss << id;
  string query = "delete from " + tablename + " where "+tablename+"id= "+oss.str() +";";
  return(executequery(query));
}

string database::getdatafield(string tablename, string colname, uint id){
  string datafield;
  int ncol,nrow;
  char** result;
  stringstream oss;
  oss << id;
  string query = "select "+colname+" from " + tablename + " where "+tablename+"id= "+oss.str() +";";
  int rc = sqlite3_get_table(db,query.c_str(),&result,&nrow,&ncol,&errormessage);
  if( rc == SQLITE_OK ){
    for(int j=0; j < ncol*nrow; ++j){
      datafield = result[ncol+j];
    }
    cout << "[DATABASE]\t retrieved: " << datafield << endl;
  }
  sqlite3_free_table(result);
  return datafield;
}

sqlite3*  database::getdatabase(void){
  return this->db;
}

database::~database(){
  sqlite3_free(this->errormessage);
  sqlite3_close(this->db);
  initresult=1;
}

/* Database object is supposed to receive a certain object and save it into sqlite */
databaseobject::databaseobject(){

}

void databaseobject::initdb(void){
  string query = "create table " + getobjectname() + " (";
  for(uint cname=0;cname<decomposetypes().size();cname++){
    query += decomposestructs()[cname] + " ";
    query += decomposetypes()[cname];
    if(cname<(decomposetypes().size()-1)) query += + ",";
  }
  query += ");";
  this->executequery(query);
}

/**
 * Save object in the database<br>
 * bugs: none found
 */
bool databaseobject::save(void){
  for(uint i=0;i<this->getchildren().size();i++){
    this->getchildren()[i]->save();
  }
  string query = "insert into " + this->getobjectname() + " (";
  for(uint cname=1;cname<this->decomposestructs().size();cname++){
    query += this->decomposestructs()[cname];

    if(cname<(this->decomposestructs().size()-1)) query += + ",";
  }
  query += ") values (";
  for(uint val=1;val<this->decomposevalues().size();val++){
    if(decomposetypes()[val]=="STRING"){
      query += "'" + this->decomposevalues()[val] + "'";
    }else{
      query += this->decomposevalues()[val];
    }
    if(val<(this->decomposevalues().size()-1)) query += + ",";
  }
  query +=");";
  return this->executequery(query);
}

bool    databaseobject::remove(void){
  bool suc6 = true;
  for(uint i=0;i<this->getchildren().size();i++){
    suc6 = suc6 && this->getchildren()[i]->remove();
  }
  suc6 = suc6 && this->deleterow(this->getobjectname(),this->getid());
  return suc6;
}

/**
 * Save object in the database<br>
 * bugs: none found
 */
bool databaseobject::update(void){
  for(uint i=0;i<this->getchildren().size();i++){
    this->getchildren()[i]->update();
  }
  string query = "update " + this->getobjectname() + " set ";
  for(uint cname=1;cname<this->decomposestructs().size();cname++){
    query += this->decomposestructs()[cname] + "=";
    if(decomposetypes()[cname]=="STRING"){
      query += "'" + this->decomposevalues()[cname] + "'";
    }else{
      query += this->decomposevalues()[cname];
    }
    if(cname<(this->decomposestructs().size()-1)) query += + ",";
  }
  query += " where " + decomposestructs()[0] + "=" + this->decomposevalues()[0] + ";";
  for(uint val=0;val<this->decomposevalues().size();val++){

  }
  return this->executequery(query);
}

string  databaseobject::floattostring(float number){
  stringstream ss;
  ss << number;
  return ss.str();
}

string  databaseobject::uinttostring(uint number){
  stringstream ss;
  ss << number;
  return ss.str();
}

databaseobject::~databaseobject(){

}
