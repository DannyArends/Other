#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Mjob
{
public:
	Mjob(String^ Name);
	int getnumparams();
	Void addParameter(Mparam^ param);
	String^ PrintMij();
private:
	String^ name;
	int numparams;
	array <Mparam^>^ jobparameters;
};
