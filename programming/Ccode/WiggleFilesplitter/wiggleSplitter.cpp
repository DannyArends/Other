/**********************************************************************
 * 
 * wiggleSplitter.c
 *
 * copyright (c) 2009 Danny Arends
 * last modified Mrt, 2009
 * first written Mrt, 2009
 *
 * Wiggle file splitter splits at each new variable step, variable step 
 * Contains: main.c
 * Input: Data.wiggle
 * Output: 
 *         - first.wiggle (any headers present in the wiggle file)
 *         - output<NUM>.wiggle (output in variable step in wiggle format)
 *
 * Constraints: Max 300 chars per line
 **********************************************************************/
using namespace std;
#include <fstream>
#include <iostream>

int main(){
	char *wiggle = "Data.wiggle";   				//input filename
	char line[300];									//Variable holding 300 chars per line
	int cnt =0;										//Number of output file currently writing to
	char *pch;										//Variable holding the check Line Contains variable step
	
	printf("wiggleSplitter.c\n");
	printf("Made by: Danny Arends\n");
	printf("Info: Trying to open '%s'\n",wiggle);
	
	//Opening Wiggle file
	ifstream wfile(wiggle, ios::in);
	//First.wiggle output file for any headers
	ofstream fff("first.wiggle", ios::out | ios::app);           
	while (!wfile.eof()){
		wfile.getline(line,300);
		pch=strstr(line,"variableStep");
		//DEBUG: printf("%s\n",line);
		if((pch!=NULL)){
			//Variable step found, print some info close the output file and open the next output file
			char o_name[10];
			printf("Info: Found 'variableStep'\n");
			fff.close();
			sprintf(o_name,"output%d.wiggle",cnt);
			printf("Info: Creating file: '%s'\n",o_name);
			fff.open(o_name, ios::out | ios::app);
			cnt++;
		}
		//Copy this line into output file
		fff << line << endl;
	}
	wfile.close();
	fff.close();
}
