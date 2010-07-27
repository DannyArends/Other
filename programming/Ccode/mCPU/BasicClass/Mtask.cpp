#include "StdAfx.h"
#include "Mtask.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Mtask::Mtask(String^ name,int numtasks):name(name)
{
	 //New task intance
	 array <Mjob^>^ jobs = gcnew array <Mjob^>(numtasks);
	 this->jobs = jobs;
	 this->numjobs = 0;
}

Void Mtask::addJob(String^ command){
	//Add a job
	Mjob^ temp = gcnew Mjob(command);
	this->jobs[this->numjobs] = temp;
	this->numjobs++;
}

Void Mtask::addParam(Mparam^ param){
	//Add a Parameter to each job
	for(int x=0;x < this->numjobs;x++){
		this->jobs[x]->addParameter(param);
	}
}

int Mtask::getnumjobs(){
	//number of jobs
	return (this->numjobs);
}

Mjob^ Mtask::getJob(int Job){
	return this->jobs[Job];
}

String^ Mtask::PrintJob(int x){
	//string interpretation og a job by index
	if(x < 0){
		return "No jobs";
	}else{
		return this->jobs[x]->PrintMij();
	}
}

String^ Mtask::PrintMij(){
	//returns the task in stringformat
	return name;
}
