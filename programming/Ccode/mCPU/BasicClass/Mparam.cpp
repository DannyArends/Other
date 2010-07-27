#include "StdAfx.h"
#include "Mparam.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Mparam::Mparam(String^ Name,String^ Value):name(Name),value(Value){
}

String^ Mparam::PrintMij(){
	return name;
}
