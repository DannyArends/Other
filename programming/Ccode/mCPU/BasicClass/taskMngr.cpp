#include "StdAfx.h"
#include "Mtask.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

taskMngr::taskMngr(){
	 //new instance of the task manager
	 array <Mtask^>^ tasks = gcnew array <Mtask^>(100);
	 this->tasks = tasks;
	 this->numtasks = 0;
}

Void taskMngr::addTask(String^ command, int njobs){
	//add a task with njobs
	Mtask^ temp = gcnew Mtask(command,njobs);
	for(int x=0;x < njobs;x++){
		temp->addJob((x+1) + " - " + command);
	}
	this->tasks[this->numtasks] = temp;
	this->numtasks++;
}

Void taskMngr::removeTask(int index){
	array <Mtask^>^ temp = gcnew array <Mtask^>(100);
	for(int x=0;x<this->numtasks-1;x++){
		if(x<index){
			temp[x] = this->tasks[x];
		}else{
			temp[x] = this->tasks[x+1];
		}
	}
	this->tasks = temp;
	this->numtasks--;
}

Void taskMngr::addParam(Mparam^ param,int Task){
	this->getTask(Task)->addParam(param);
}

Void taskMngr::addParam(Mparam^ param,int Task,int Job){
	this->getTask(Task)->getJob(Job)->addParameter(param);
}

int taskMngr::getnumtasks(){
	//number of tasks in the taskmanager
	return (this->numtasks);
}

Mtask^ taskMngr::getTask(int x){
	//taskobject from index
	Mtask^ temp = gcnew Mtask("No tasks",0);
	if(x > -1 && x < this->numtasks){
		temp = this->tasks[x];
	}
	return temp;
}

String^ taskMngr::PrintTask(int x){
	//taskobject string from index
	if(x < 0){
		return "No tasks";
	}else{
		return this->tasks[x]->PrintMij();
	}
}
