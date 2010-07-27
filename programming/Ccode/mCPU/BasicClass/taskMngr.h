#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class taskMngr
{
public:
	taskMngr();									//Initialization
	Void addTask(String^ command, int njobs);	//Adds a task with njobs
	Void removeTask(int index);	//Remove a Task
	Void addParam(Mparam^param,int Task);
	Void addParam(Mparam^param,int Task,int Job);
	int getnumtasks();							//return number of tasks
	Mtask^ getTask(int x);						//returns a certain Task
	String^ PrintTask(int x);					//Print a task
private:
	array <Mtask^>^ tasks;
	int numtasks;
};
