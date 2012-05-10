/**
 * \file BASE/tree.cpp
 * \brief Code file, Several routines to construct/delete tree structures
 *
 * Copyright (c) 2010 Danny Arends
 * 
 **/

#include "tree.h"

/**
 * \brief Class that is a representation of an in memory tree<br>
 *
 * bugs: none found
 */
tree::tree(){
  this->root = (treenode*)calloc(1,sizeof(treenode));
  this->root->height  = 0;
  this->root->data    = "RootNode";
  this->root->nleafs  = 0;
}

/**
 * Set the data in the root node (and get a proper tree)<br>
 *
 * bugs: none found
 * @param data char* to the data that the root node should hold<br>
 * @return void<br>
 */
void tree::setrootnode(const char* data){
  this->root->data   = data;

}

/**
 * Get the root for attachment of items<br>
 *
 * bugs: none found
 * @return treenode* root of the tree<br>
 */
treenode* tree::getrootnode(void){
  return this->root;
}

/**
 * Initializing of a new tree node<br>
 *
 * bugs: none found
 * @param data char* to the data that the root node should hold<br>
 * @param height uint height in the tree<br>
 * @return treenode* A pointer to the new tree node<br>
 */
treenode* tree::newtreenode(const char* data,uint height){
  treenode* n = (treenode*)calloc(1,sizeof(treenode));
  n->height  = height;
  n->data    = data;
  n->nleafs  = 0;
  return n;
}

/**
 * Adds a leaf to the tree<br>
 *
 * bugs: none found
 * @param data char* to the data that the new node should hold<br>
 * @param parent the node to attach the new node to<br>
 * @return treenode* A pointer to the new (and attached) tree node<br>
 */
treenode* tree::addleaf(const char* data, treenode* parent){
  treenode** temp = (treenode**)calloc((parent->nleafs+1),sizeof(treenode*));
  treenode* newtreenode = (treenode*)this->newtreenode(data,(parent->height+1));
  for(uint i=0;i<(parent->nleafs);i++){
    temp[i] = (treenode*)parent->leafs[i];
  }  
  temp[parent->nleafs] = newtreenode;
  parent->leafs = temp;
  parent->nleafs++;
  return newtreenode;
}

/**
 * Print the tree from node n downwards<br>
 *
 * bugs: none found
 * @param n Node to start printing from<br>
 * @return void<br>
 */
void tree::printtree(treenode* n){
  for(uint i=0;i<n->height;i++){
    cout << "\t";
  }
  cout << n->height << "\t" << n->data << endl;
  for(uint i=0;i<n->nleafs;i++){
    printtree(n->leafs[i]);
  }
}

/**
 * Free parts of the tree from node n downwards<br>
 *
 * bugs: none found
 * @param n Node to start cleaning from<br>
 * @return void<br>
 */
void tree::freetree(treenode* n){
  for(uint i=0;i<n->nleafs;i++){
    freetree(n->leafs[i]);
  }
  free(n);
}
