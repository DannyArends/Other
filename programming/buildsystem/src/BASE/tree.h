/**
 * \file BASE/tree.h
 * \brief Header file, for BASE/tree.cpp
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

 #ifndef TREESTRUCTURE_H_
  #define TREESTRUCTURE_H_

  #include "BASE.h"

 /** 
  * \brief Represent a tree node.
  *
  * bugs: none found
  */
  struct treenode{
    uint                  height;
    const char*           data;
    uint                  nleafs;
    struct treenode**     leafs;
  };

  /**
   * \brief Stores an entire tree of nodes.
   *
   * bugs: none found
   */
  class tree: public object{
    public:
      tree();
      ~tree();
      void        setrootnode(const char* data);
      treenode*   getrootnode(void);
      treenode*   addleaf(const char* data, treenode* parent);
      void        printtree(treenode* n);
      void        freetree(treenode* n);
    private:
      treenode*   newtreenode(const char* data,uint height);
      treenode*   root;
  };

#endif
