#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Mparam
{
public:
	Mparam(String^ Name,String^ Value);

	String^ PrintMij();
	String^ name;
	String^ value;
};
