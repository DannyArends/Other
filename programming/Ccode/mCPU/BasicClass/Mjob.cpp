#include "StdAfx.h"
#include "Mjob.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Mjob::Mjob(String^ name):name(name)
{
	 array <Mparam^>^ params = gcnew array <Mparam^>(20);
	 this->jobparameters = params;
	 this->numparams = 0;
}

int Mjob::getnumparams(){
	return this->numparams;
}

Void Mjob::addParameter(Mparam^ param){
	if(this->numparams < 20){
		this->jobparameters[numparams] = param;
		this->numparams++;
	}
}

String^ Mjob::PrintMij(){
	String^ r = this->name;
	for(int x=0; x < this->numparams ; x++){
		r += " -" + this->jobparameters[x]->name;
		if(this->jobparameters[x]->value != ""){	
			r += "=" + this->jobparameters[x]->value;
		}
	}
	return r;
}
