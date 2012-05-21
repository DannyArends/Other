/**
 * \file BASE/BASE.h
 * \brief Header file, for the BASE directory
 *
 * This class is used to share the objects within the BASE directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 * - \ref object<br>
 * - \ref object2d<br>
 * - \ref object3d<br>
 * - \ref moveable<br>
 * - \ref bufferable<br>
 * - \ref database<br>
 * - \ref databaseobject<br>
 * - \ref tree<br>
 *
 **/

#ifndef BASE_H_
  #define BASE_H_

  #include "includes.h"
  //ALL DEPENDENCIES FOR THIS LIBRARY
  #include <sqlite/sqlite3.h>
  #include "BASEstructures.h"

  /**
   * \brief Object factory class, should create all identifiable objects.<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class objectfactory {
    public:
      objectfactory(){
        this->current_id=0;
      }
      object* newobject(){
        this->current_id++;
        return new object(this->current_id);
      }
      ~objectfactory();
    private:
      uint current_id;
  };

  /**
   * \brief Virtual class, adds a parental object and the ability to store child objects.<br>
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  template<class objecttype>
  class node {
    public:
      node(){
        this->parent=0;
        this->children.clear();
      }
      ~node(){
        this->children.clear();
      }
     /**
      * Add an objecttype* as parent<br>
      * bugs: none found
      * @param p objecttype* to parent object<br>
      */
      void setparent(objecttype* p){
        this->parent=p;
      }
     /**
      * Get parent as objecttype*<br>
      * bugs: none found
      */
      objecttype* getparent(void){
        return this->parent;
      }
     /**
      * Add an objecttype* as child<br>
      * bugs: none found
      * @param c objecttype* to child object<br>
      */
      void addchild(objecttype* c){
        c->setparent((objecttype*)this);
        this->children.push_back(c);
      }

      /**
       * Remove a child<br>
       * bugs: none found
       * @param id of child object to remove<br>
       */
       void removechild(uint id){
         this->children.erase(this->children.begin()+id);
       }
     /**
      * Get a vector containing the children as objecttype*<br>
      * bugs: none found
      */
      vector<objecttype*> getchildren(void){
        return this->children;
      }
     /**
      * Update all the children with new children<br>
      * bugs: none found
      * @param c vector<objecttype*> to new children<br>
      */
      void setchildren(vector<objecttype*> c){
        this->children=c;
      }

    private:
      objecttype*               parent;
      vector<objecttype*>       children;
  };

  /**
  * \brief The superclass of all three dimensional objects with impulse
  *
  * TODO Description<br>
  * bugs: none found
  */
  template<class objecttype>
  class moveable: public objecttype{
    public:
      moveable(){
        this->impulse[0]  =0.0f;
        this->impulse[1]  =0.0f;
        this->impulse[2]  =0.0f;
      }
      ~moveable(){

      }
      void addimpulse(float x, float y, float z){
        this->impulse[0] += x;
        this->impulse[1] += y;
        this->impulse[2] += z;
      }
      void setimpulse(float x, float y, float z){
        this->impulse[0] = x;
        this->impulse[1] = y;
        this->impulse[2] = z;
      }
      float* getimpulse(void){
        return this->impulse;
      }
    private:
      float impulse[3];
  };

  /**
   * \brief Virtual bufferable class, all bufferable things should inherit from this class.
   *
   * TODO Description<br>
   * bugs: none found
   */
  template<class objecttype>
  class bufferable : public objecttype{
    public:
      bufferable(){
        this->buffered=false;
      }
      /**
      * \brief Buffer function of \ref bufferable (overwritten by the object)<br>
      *
      * Should be implemented by the deriving class
      * bugs: none found
      * @return True, if the object is buffered, false otherwise<br>
      */
      virtual bool buffer(void) = 0;
     /**
      * Set the buffered variable<br>
      * bugs: none found
      * @param bufferstatus Set the bufferstatus to this<br>
      */
      void setbuffered(bool bufferstatus){
        this->buffered = bufferstatus;
      }
     /**
      * Is the object buffered<br>
      * bugs: none found
      * @return True, if the object is buffered<br>
      */
      bool isbuffered(void){ return this->buffered; }
      virtual ~bufferable(){ }
    private:
      bool buffered;
  };

  template<typename element, class sequence> class lsystem;

  //Share the objects
  #include "configfile.h"
  #include "object.h"
  #include "datatypes.h"
  #include "database.h"
  #include "keyboard.h"
  #include "myio.h"
  #include "lsystem.h"
  #include "tree.h"

  class object2d;
  class object3d;
  class databaseobject;
#endif

