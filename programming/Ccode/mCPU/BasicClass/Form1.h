#pragma once

namespace BasicClass {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		taskMngr^ taskInterface;
	private: System::Windows::Forms::Button^  doJob;
	public: 
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  StopTask;
	private: System::Windows::Forms::Button^  StopJob;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  CoreNum;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  resetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  taskToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  howDoIToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  jobToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  taskToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;





	private: System::Windows::Forms::ListBox^  JobsBox;
	public:
		Form1(void)
		{
			InitializeComponent();
			this->taskInterface = (gcnew taskMngr());
			this->CoreNum->Text = Convert::ToString(System::Environment::ProcessorCount);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  TaskBox;
	protected: 
	private: System::Windows::Forms::TextBox^  CommandBox;
	private: System::Windows::Forms::TextBox^  PNameBox;
	private: System::Windows::Forms::TextBox^  PValueBox;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::NumericUpDown^  JobBox;
	private: System::Windows::Forms::Button^  AddTaskB;
	private: System::Windows::Forms::Button^  AddParam;
	private: System::Windows::Forms::Button^  RemParam;
	private: System::Windows::Forms::Button^  RemTask;
	private: System::Windows::Forms::Button^  StartTask;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->TaskBox = (gcnew System::Windows::Forms::ListBox());
			this->CommandBox = (gcnew System::Windows::Forms::TextBox());
			this->PNameBox = (gcnew System::Windows::Forms::TextBox());
			this->PValueBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->JobBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->AddTaskB = (gcnew System::Windows::Forms::Button());
			this->AddParam = (gcnew System::Windows::Forms::Button());
			this->RemParam = (gcnew System::Windows::Forms::Button());
			this->RemTask = (gcnew System::Windows::Forms::Button());
			this->StartTask = (gcnew System::Windows::Forms::Button());
			this->JobsBox = (gcnew System::Windows::Forms::ListBox());
			this->doJob = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->StopTask = (gcnew System::Windows::Forms::Button());
			this->StopJob = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->CoreNum = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->taskToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->howDoIToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->jobToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->taskToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->JobBox))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// TaskBox
			// 
			this->TaskBox->FormattingEnabled = true;
			this->TaskBox->Location = System::Drawing::Point(299, 70);
			this->TaskBox->Name = L"TaskBox";
			this->TaskBox->Size = System::Drawing::Size(132, 238);
			this->TaskBox->TabIndex = 0;
			this->TaskBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::TaskBox_SelectedIndexChanged);
			// 
			// CommandBox
			// 
			this->CommandBox->Location = System::Drawing::Point(66, 74);
			this->CommandBox->Name = L"CommandBox";
			this->CommandBox->Size = System::Drawing::Size(100, 20);
			this->CommandBox->TabIndex = 1;
			// 
			// PNameBox
			// 
			this->PNameBox->Location = System::Drawing::Point(66, 247);
			this->PNameBox->Name = L"PNameBox";
			this->PNameBox->Size = System::Drawing::Size(100, 20);
			this->PNameBox->TabIndex = 2;
			// 
			// PValueBox
			// 
			this->PValueBox->Location = System::Drawing::Point(66, 273);
			this->PValueBox->Name = L"PValueBox";
			this->PValueBox->Size = System::Drawing::Size(100, 20);
			this->PValueBox->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 250);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Parameter";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 276);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(34, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Value";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 77);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(54, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Command";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 102);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(51, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"# of Jobs";
			// 
			// JobBox
			// 
			this->JobBox->Location = System::Drawing::Point(66, 102);
			this->JobBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->JobBox->Name = L"JobBox";
			this->JobBox->Size = System::Drawing::Size(47, 20);
			this->JobBox->TabIndex = 8;
			this->JobBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// AddTaskB
			// 
			this->AddTaskB->Location = System::Drawing::Point(181, 70);
			this->AddTaskB->Name = L"AddTaskB";
			this->AddTaskB->Size = System::Drawing::Size(112, 23);
			this->AddTaskB->TabIndex = 9;
			this->AddTaskB->Text = L"Add Task";
			this->AddTaskB->UseVisualStyleBackColor = true;
			this->AddTaskB->Click += gcnew System::EventHandler(this, &Form1::AddTaskB_Click);
			// 
			// AddParam
			// 
			this->AddParam->Location = System::Drawing::Point(181, 244);
			this->AddParam->Name = L"AddParam";
			this->AddParam->Size = System::Drawing::Size(75, 23);
			this->AddParam->TabIndex = 10;
			this->AddParam->Text = L"Add";
			this->AddParam->UseVisualStyleBackColor = true;
			this->AddParam->Click += gcnew System::EventHandler(this, &Form1::AddParam_Click);
			// 
			// RemParam
			// 
			this->RemParam->Location = System::Drawing::Point(181, 273);
			this->RemParam->Name = L"RemParam";
			this->RemParam->Size = System::Drawing::Size(75, 23);
			this->RemParam->TabIndex = 11;
			this->RemParam->Text = L"Remove";
			this->RemParam->UseVisualStyleBackColor = true;
			this->RemParam->Click += gcnew System::EventHandler(this, &Form1::RemParam_Click);
			// 
			// RemTask
			// 
			this->RemTask->Location = System::Drawing::Point(181, 99);
			this->RemTask->Name = L"RemTask";
			this->RemTask->Size = System::Drawing::Size(112, 23);
			this->RemTask->TabIndex = 12;
			this->RemTask->Text = L"Remove Task";
			this->RemTask->UseVisualStyleBackColor = true;
			this->RemTask->Click += gcnew System::EventHandler(this, &Form1::RemTask_Click);
			// 
			// StartTask
			// 
			this->StartTask->Location = System::Drawing::Point(181, 128);
			this->StartTask->Name = L"StartTask";
			this->StartTask->Size = System::Drawing::Size(112, 23);
			this->StartTask->TabIndex = 13;
			this->StartTask->Text = L"Start Task";
			this->StartTask->UseVisualStyleBackColor = true;
			this->StartTask->Click += gcnew System::EventHandler(this, &Form1::StartTask_Click);
			// 
			// JobsBox
			// 
			this->JobsBox->FormattingEnabled = true;
			this->JobsBox->Location = System::Drawing::Point(448, 70);
			this->JobsBox->Name = L"JobsBox";
			this->JobsBox->Size = System::Drawing::Size(257, 199);
			this->JobsBox->TabIndex = 14;
			// 
			// doJob
			// 
			this->doJob->Location = System::Drawing::Point(618, 276);
			this->doJob->Name = L"doJob";
			this->doJob->Size = System::Drawing::Size(87, 23);
			this->doJob->TabIndex = 15;
			this->doJob->Text = L"(Re)Start Job";
			this->doJob->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label5->Location = System::Drawing::Point(299, 52);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(44, 15);
			this->label5->TabIndex = 16;
			this->label5->Text = L"TASKS";
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label6->Location = System::Drawing::Point(448, 52);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 15);
			this->label6->TabIndex = 17;
			this->label6->Text = L"JOBS";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label7->Location = System::Drawing::Point(6, 52);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(63, 15);
			this->label7->TabIndex = 18;
			this->label7->Text = L"SETTINGS";
			// 
			// StopTask
			// 
			this->StopTask->Location = System::Drawing::Point(181, 157);
			this->StopTask->Name = L"StopTask";
			this->StopTask->Size = System::Drawing::Size(112, 23);
			this->StopTask->TabIndex = 19;
			this->StopTask->Text = L"Stop Task";
			this->StopTask->UseVisualStyleBackColor = true;
			// 
			// StopJob
			// 
			this->StopJob->Location = System::Drawing::Point(525, 276);
			this->StopJob->Name = L"StopJob";
			this->StopJob->Size = System::Drawing::Size(87, 23);
			this->StopJob->TabIndex = 20;
			this->StopJob->Text = L"Stop Job";
			this->StopJob->UseVisualStyleBackColor = true;
			this->StopJob->Click += gcnew System::EventHandler(this, &Form1::StopJob_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 133);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(58, 13);
			this->label8->TabIndex = 21;
			this->label8->Text = L"# of CPU\'s";
			// 
			// CoreNum
			// 
			this->CoreNum->AutoSize = true;
			this->CoreNum->Location = System::Drawing::Point(67, 133);
			this->CoreNum->Name = L"CoreNum";
			this->CoreNum->Size = System::Drawing::Size(0, 13);
			this->CoreNum->TabIndex = 22;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->viewToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(717, 24);
			this->menuStrip1->TabIndex = 23;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->newToolStripMenuItem, 
				this->toolStripSeparator1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->jobToolStripMenuItem, 
				this->taskToolStripMenuItem1});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->editToolStripMenuItem->Text = L"&Edit";
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->viewToolStripMenuItem->Text = L"&View";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->howDoIToolStripMenuItem, 
				this->helpToolStripMenuItem1, this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->resetToolStripMenuItem, 
				this->taskToolStripMenuItem});
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"New";
			// 
			// resetToolStripMenuItem
			// 
			this->resetToolStripMenuItem->Name = L"resetToolStripMenuItem";
			this->resetToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->resetToolStripMenuItem->Text = L"Reset";
			// 
			// taskToolStripMenuItem
			// 
			this->taskToolStripMenuItem->Name = L"taskToolStripMenuItem";
			this->taskToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->taskToolStripMenuItem->Text = L"Task";
			// 
			// howDoIToolStripMenuItem
			// 
			this->howDoIToolStripMenuItem->Name = L"howDoIToolStripMenuItem";
			this->howDoIToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->howDoIToolStripMenuItem->Text = L"How Do I\?";
			// 
			// helpToolStripMenuItem1
			// 
			this->helpToolStripMenuItem1->Name = L"helpToolStripMenuItem1";
			this->helpToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->helpToolStripMenuItem1->Text = L"Helpfile";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// jobToolStripMenuItem
			// 
			this->jobToolStripMenuItem->Name = L"jobToolStripMenuItem";
			this->jobToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->jobToolStripMenuItem->Text = L"Job";
			// 
			// taskToolStripMenuItem1
			// 
			this->taskToolStripMenuItem1->Name = L"taskToolStripMenuItem1";
			this->taskToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->taskToolStripMenuItem1->Text = L"Task";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(717, 316);
			this->Controls->Add(this->CoreNum);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->StopJob);
			this->Controls->Add(this->StopTask);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->doJob);
			this->Controls->Add(this->JobsBox);
			this->Controls->Add(this->StartTask);
			this->Controls->Add(this->RemTask);
			this->Controls->Add(this->RemParam);
			this->Controls->Add(this->AddParam);
			this->Controls->Add(this->AddTaskB);
			this->Controls->Add(this->JobBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->PValueBox);
			this->Controls->Add(this->PNameBox);
			this->Controls->Add(this->CommandBox);
			this->Controls->Add(this->TaskBox);
			this->Controls->Add(this->menuStrip1);
			this->ForeColor = System::Drawing::SystemColors::InfoText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"mCPU v0.1 (c) Danny Arends";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->JobBox))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
//Buttons on this form
private: System::Void AddParam_Click(System::Object^  sender, System::EventArgs^  e) {
		int index = this->TaskBox->SelectedIndex;
		int index2 = this->JobsBox->SelectedIndex;
		if(this->PNameBox->Text != "" && index >-1){
			 Mparam^ temp = gcnew Mparam(this->PNameBox->Text,this->PValueBox->Text);
			 if(index2 > -1){
			   this->taskInterface->addParam(temp,index,index2);
			 }else{
			   this->taskInterface->addParam(temp,index);
			 }
		 }
		 this->refreshboxes();
		 }

private: System::Void AddTaskB_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->CommandBox->Text != ""){
			   this->taskInterface->addTask(this->CommandBox->Text,(int) this->JobBox->Value);
			 }
			 this->TaskBox->Items->Clear();
			 this->JobsBox->Items->Clear();
			 for(int x = 0;x < this->taskInterface->getnumtasks();x++){
			 	 this->TaskBox->Items->Add(this->taskInterface->PrintTask(x));
			 }
			 this->TaskBox->SelectedIndex = this->taskInterface->getnumtasks()-1;
		 }

private: System::Void RemTask_Click(System::Object^  sender, System::EventArgs^  e) {
		 int index = this->TaskBox->SelectedIndex;
		 if(index > -1){
				this->taskInterface->removeTask(index);
		 }
		 this->TaskBox->Items->Clear();
		 this->JobsBox->Items->Clear();
		 for(int x = 0;x < this->taskInterface->getnumtasks();x++){
		 	 this->TaskBox->Items->Add(this->taskInterface->PrintTask(x));
		 }
		 }

private: System::Void StartTask_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void RemParam_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
		 
private: System::Void TaskBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->refreshboxes();
		 }

public: System::Void refreshboxes(){
			 int index = this->TaskBox->SelectedIndex;
			 Mtask^ temp = this->taskInterface->getTask(index);
			 this->JobsBox->Items->Clear();
			 for(int x = 0;x < temp->getnumjobs();x++){
				this->JobsBox->Items->Add(temp->PrintJob(x));
			 }
		}

private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void StopJob_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

