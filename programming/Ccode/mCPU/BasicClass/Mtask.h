#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Mtask
{
public:
	Mtask(String^ Name,int numtasks);
	Void addJob(String^ command);
	Void addParam(Mparam^ param);
	int getnumjobs();
	Mjob^ getJob(int x);
	String^ PrintJob(int x);
	String^ PrintMij();
private:
	String^ name;
	int numjobs;
	array <Mjob^>^ jobs;
};
