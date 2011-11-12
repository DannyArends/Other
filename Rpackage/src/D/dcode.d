module dcode;

import std.c.stdio;
import std.math;
import std.array;

import dll.raux;
import libs.r;

//D function
void test_function(){

}

extern (C){
  //C style interface to the DLL that is callable by R
  export void R_test_function(){
    test_function();
  }  
}
