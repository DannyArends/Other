/**
 * \file MYMATH/geneticalgorithm.h
 * \brief Header file, for MYMATH/geneticalgorithm.cpp
 *
 * Copyright (c) 2010 Danny Arends<br>
 * 
 **/
 
 
 /*
 
 DNA:
5' 	--- 	A 	T 	G 	C 	C 	G 	T 	T 	A 	G 	A 	C 	C 	G 	T 	T 	A 	G 	C 	G 	G 	A 	C 	C 	T 	G 	A 	C 	--> 	3'    SENSE
3' 	<-- 	T 	A 	C 	G 	G 	C 	A 	A 	T 	C 	T 	G 	G 	C 	A 	A 	T 	C 	G 	C 	C 	T 	G 	G 	A 	C 	T 	G 	--- 	5'     ANTISENSE

 RNA:
 
5'    --           A    U   G   C   C   G   U   U   A    G   A   C   C   G    T    T  A   G  C  G    G  A    C  C  U  G  A  C    -->3'
 
 PROTEIN:
 
                    START, PROLINE, LEUCINE, ASPARTATE,ETC
 
 */
 
#ifndef GA_H_
  #define GA_H_
  #include "MYMATH.h"
  
  #define CROSSOVER_RATE            0.7
  #define MUTATION_RATE             0.001
  #define POP_SIZE                  50			//must be an even number
  #define CHROMO_LENGTH             300
  #define GENE_LENGTH               4
  #define MAX_ALLOWABLE_GENERATIONS	5000

  //returns a float between 0 & 1
  #define RANDOM_NUM		((float)rand()/(RAND_MAX+1))
  
  /** 
   * \brief The representation of a 4 char word chromosome string
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class bytechromosome : public mathobject{
  public:
    bytechromosome();
  	bytechromosome(string bts, float ftns);
    string    getbits();
    float     getfitness();
    void      setbits(string bts);
    void      setfitness(float ftns);
  private:
    string	  bits;  
  	float	    fitness;
  };
  
  void    PrintGeneSymbol(int val);
  string  GetRandomBits(int length);
  int     BinToDec(string bits);
  float   AssignFitness(string bits, int target_value);
  void    PrintChromo(string bits);
  void    PrintGeneSymbol(int val);
  int     ParseBits(string bits, int* buffer);
  string  Roulette(int total_fitness, bytechromosome* Population);
  void    Mutate(string &bits);
  void    Crossover(string &offspring1, string &offspring2);
  
  int SolveNumber(float Target, int Num_Times);

#endif
