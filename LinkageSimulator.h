/*
Nestor Gomez
24-280 C++ for Engrs.
PS07. Due Apr. 16, 2020

GUI for managing and visualizing a linkage system simulation

*/#pragma once

#include "LinkEditor.h"
#include "LinkageSystem.h"

#include "FlickerLessPanel.h"
// using flickerless panel makes the form design view not work.
// to use flickerless panel or allow the design view, use one of these
// in InitComponents() function
//    for design view >>>>    this->mainPanel = (gcnew System::Windows::Forms::Panel());
//    for flickerless >>>>    this->mainPanel = (gcnew FlickerLessPanel());

namespace ps07LinkageSimulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//using namespace ps05LinkEditor;
	//class LinkEditor;

	/// <summary>
	/// Summary for LinkageSimulator
	/// </summary>
	public ref class LinkageSimulator : public System::Windows::Forms::Form
	{
	public:
		LinkageSimulator(void)
		{
			theSystem = new LinkageSystem;
			panX = panY = 300;
			zoomLevel = 1.;
			scaleSize = recalcScaleSize();

			mouseInPanel = false;

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			panX = panY = 300;
			zoomLevel = 1.;
			scaleSize = recalcScaleSize();

			mouseInPanel = false;
			feedbackLabel->Text = " - - - ";
			coordLabel->Location = Point(offScreenPos, offScreenPos);
			comboBoxGrid->SelectedIndex = 0;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LinkageSimulator()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
		int panX, panY, currX, currY;
		float zoomLevel;
		float scaleSize = 1;   // this is recalculated when the zoomLevel is changed
		bool mouseInPanel;
		int offScreenPos = -200;
		String^ prevFeedback = " - - - ";
		System::Windows::Forms::Form^ theEditor;
		LinkageSystem* theSystem;
		bool editPinModeIsOn = false;
		int crankPinEdit = -1, couplerPinEdit = -1, rockerPinEdit = -1;
		bool simulationIsOn = false;

	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::Button^ buttonHelp;
	private: System::Windows::Forms::Button^ buttonResetView;
	private: System::Windows::Forms::Button^ buttonSave;
	private: System::Windows::Forms::Button^ buttonLoad;
	private: System::Windows::Forms::Label^ feedbackLabel;
	private: System::Windows::Forms::Label^ coordLabel;
	private: System::Windows::Forms::Button^ buttonDeleteCrank;
	private: System::Windows::Forms::Button^ buttonDeleteCoupler;
	private: System::Windows::Forms::Button^ buttonDeleteRocker;






	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ labelCrankID;
	private: System::Windows::Forms::Label^ labelCouplerID;
	private: System::Windows::Forms::Label^ labelRockerID;
	private: System::Windows::Forms::Button^ buttonEditCrank;
	private: System::Windows::Forms::Button^ buttonEditCoupler;
	private: System::Windows::Forms::Button^ buttonEditRocker;
	private: System::Windows::Forms::Label^ labelEditPins;

	private: System::Windows::Forms::Label^ labelRunSimulation;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxRPM;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBoxInterval;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ buttonStep;
	private: System::Windows::Forms::ComboBox^ comboBoxGrid;
	private: System::Windows::Forms::CheckBox^ checkBoxAxes;
	private: System::Windows::Forms::CheckBox^ checkBoxScale;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			//this->mainPanel = (gcnew FlickerLessPanel()); 
			this->buttonHelp = (gcnew System::Windows::Forms::Button());
			this->buttonResetView = (gcnew System::Windows::Forms::Button());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->buttonLoad = (gcnew System::Windows::Forms::Button());
			this->feedbackLabel = (gcnew System::Windows::Forms::Label());
			this->coordLabel = (gcnew System::Windows::Forms::Label());
			this->buttonDeleteCrank = (gcnew System::Windows::Forms::Button());
			this->buttonDeleteCoupler = (gcnew System::Windows::Forms::Button());
			this->buttonDeleteRocker = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->labelCrankID = (gcnew System::Windows::Forms::Label());
			this->labelCouplerID = (gcnew System::Windows::Forms::Label());
			this->labelRockerID = (gcnew System::Windows::Forms::Label());
			this->buttonEditCrank = (gcnew System::Windows::Forms::Button());
			this->buttonEditCoupler = (gcnew System::Windows::Forms::Button());
			this->buttonEditRocker = (gcnew System::Windows::Forms::Button());
			this->labelEditPins = (gcnew System::Windows::Forms::Label());
			this->labelRunSimulation = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxRPM = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxInterval = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonStep = (gcnew System::Windows::Forms::Button());
			this->comboBoxGrid = (gcnew System::Windows::Forms::ComboBox());
			this->checkBoxAxes = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxScale = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Fuchsia;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(201, 25);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Linkage Simulator";
			// 
			// mainPanel
			// 
			this->mainPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->mainPanel->BackColor = System::Drawing::Color::White;
			this->mainPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->mainPanel->Location = System::Drawing::Point(127, 46);
			this->mainPanel->Name = L"mainPanel";
			this->mainPanel->Size = System::Drawing::Size(651, 452);
			this->mainPanel->TabIndex = 2;
			this->mainPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &LinkageSimulator::mainPanel_Paint);
			this->mainPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkageSimulator::mainPanel_MouseDown);
			this->mainPanel->MouseEnter += gcnew System::EventHandler(this, &LinkageSimulator::mainPanel_MouseEnter);
			this->mainPanel->MouseLeave += gcnew System::EventHandler(this, &LinkageSimulator::mainPanel_MouseLeave);
			this->mainPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkageSimulator::mainPanel_MouseMove);
			this->mainPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkageSimulator::mainPanel_MouseUp);
			// 
			// buttonHelp
			// 
			this->buttonHelp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonHelp->Location = System::Drawing::Point(699, 12);
			this->buttonHelp->Name = L"buttonHelp";
			this->buttonHelp->Size = System::Drawing::Size(70, 25);
			this->buttonHelp->TabIndex = 16;
			this->buttonHelp->Text = L"Help";
			this->buttonHelp->UseVisualStyleBackColor = true;
			// 
			// buttonResetView
			// 
			this->buttonResetView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonResetView->Location = System::Drawing::Point(626, 12);
			this->buttonResetView->Name = L"buttonResetView";
			this->buttonResetView->Size = System::Drawing::Size(70, 25);
			this->buttonResetView->TabIndex = 15;
			this->buttonResetView->Text = L"Reset View";
			this->buttonResetView->UseVisualStyleBackColor = true;
			this->buttonResetView->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonResetView_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->Location = System::Drawing::Point(71, 46);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(50, 30);
			this->buttonSave->TabIndex = 14;
			this->buttonSave->Text = L"Save";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonSave_Click);
			// 
			// buttonLoad
			// 
			this->buttonLoad->Location = System::Drawing::Point(8, 46);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(52, 30);
			this->buttonLoad->TabIndex = 13;
			this->buttonLoad->Text = L"Load";
			this->buttonLoad->UseVisualStyleBackColor = true;
			this->buttonLoad->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonLoad_Click);
			// 
			// feedbackLabel
			// 
			this->feedbackLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->feedbackLabel->AutoSize = true;
			this->feedbackLabel->Location = System::Drawing::Point(12, 499);
			this->feedbackLabel->Name = L"feedbackLabel";
			this->feedbackLabel->Size = System::Drawing::Size(28, 13);
			this->feedbackLabel->TabIndex = 17;
			this->feedbackLabel->Text = L" - - - ";
			// 
			// coordLabel
			// 
			this->coordLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->coordLabel->AutoSize = true;
			this->coordLabel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->coordLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->coordLabel->Location = System::Drawing::Point(369, 18);
			this->coordLabel->Name = L"coordLabel";
			this->coordLabel->Size = System::Drawing::Size(92, 15);
			this->coordLabel->TabIndex = 18;
			this->coordLabel->Text = L"coordinate popup";
			this->coordLabel->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// buttonDeleteCrank
			// 
			this->buttonDeleteCrank->Location = System::Drawing::Point(85, 94);
			this->buttonDeleteCrank->Name = L"buttonDeleteCrank";
			this->buttonDeleteCrank->Size = System::Drawing::Size(36, 19);
			this->buttonDeleteCrank->TabIndex = 14;
			this->buttonDeleteCrank->Text = L"Del";
			this->buttonDeleteCrank->UseVisualStyleBackColor = true;
			// 
			// buttonDeleteCoupler
			// 
			this->buttonDeleteCoupler->Location = System::Drawing::Point(85, 142);
			this->buttonDeleteCoupler->Name = L"buttonDeleteCoupler";
			this->buttonDeleteCoupler->Size = System::Drawing::Size(36, 19);
			this->buttonDeleteCoupler->TabIndex = 14;
			this->buttonDeleteCoupler->Text = L"Del";
			this->buttonDeleteCoupler->UseVisualStyleBackColor = true;
			// 
			// buttonDeleteRocker
			// 
			this->buttonDeleteRocker->Location = System::Drawing::Point(85, 194);
			this->buttonDeleteRocker->Name = L"buttonDeleteRocker";
			this->buttonDeleteRocker->Size = System::Drawing::Size(36, 19);
			this->buttonDeleteRocker->TabIndex = 14;
			this->buttonDeleteRocker->Text = L"Del";
			this->buttonDeleteRocker->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 97);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 19;
			this->label2->Text = L"Crank";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(5, 145);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Coupler";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(5, 197);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 13);
			this->label4->TabIndex = 19;
			this->label4->Text = L"Rocker";
			// 
			// labelCrankID
			// 
			this->labelCrankID->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelCrankID->Location = System::Drawing::Point(6, 114);
			this->labelCrankID->Name = L"labelCrankID";
			this->labelCrankID->Size = System::Drawing::Size(115, 20);
			this->labelCrankID->TabIndex = 21;
			this->labelCrankID->Text = L" ";
			this->labelCrankID->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelCouplerID
			// 
			this->labelCouplerID->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelCouplerID->Location = System::Drawing::Point(6, 164);
			this->labelCouplerID->Name = L"labelCouplerID";
			this->labelCouplerID->Size = System::Drawing::Size(115, 20);
			this->labelCouplerID->TabIndex = 21;
			this->labelCouplerID->Text = L" ";
			this->labelCouplerID->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelRockerID
			// 
			this->labelRockerID->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelRockerID->Location = System::Drawing::Point(6, 216);
			this->labelRockerID->Name = L"labelRockerID";
			this->labelRockerID->Size = System::Drawing::Size(115, 20);
			this->labelRockerID->TabIndex = 21;
			this->labelRockerID->Text = L" ";
			this->labelRockerID->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// buttonEditCrank
			// 
			this->buttonEditCrank->Location = System::Drawing::Point(48, 94);
			this->buttonEditCrank->Name = L"buttonEditCrank";
			this->buttonEditCrank->Size = System::Drawing::Size(36, 19);
			this->buttonEditCrank->TabIndex = 14;
			this->buttonEditCrank->Text = L"Edit";
			this->buttonEditCrank->UseVisualStyleBackColor = true;
			this->buttonEditCrank->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonEditCrank_Click);
			// 
			// buttonEditCoupler
			// 
			this->buttonEditCoupler->Location = System::Drawing::Point(48, 142);
			this->buttonEditCoupler->Name = L"buttonEditCoupler";
			this->buttonEditCoupler->Size = System::Drawing::Size(36, 19);
			this->buttonEditCoupler->TabIndex = 14;
			this->buttonEditCoupler->Text = L"Edit";
			this->buttonEditCoupler->UseVisualStyleBackColor = true;
			this->buttonEditCoupler->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonEditCoupler_Click);
			// 
			// buttonEditRocker
			// 
			this->buttonEditRocker->Location = System::Drawing::Point(48, 194);
			this->buttonEditRocker->Name = L"buttonEditRocker";
			this->buttonEditRocker->Size = System::Drawing::Size(36, 19);
			this->buttonEditRocker->TabIndex = 14;
			this->buttonEditRocker->Text = L"Edit";
			this->buttonEditRocker->UseVisualStyleBackColor = true;
			this->buttonEditRocker->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonEditRocker_Click);
			// 
			// labelEditPins
			// 
			this->labelEditPins->BackColor = System::Drawing::Color::Lime;
			this->labelEditPins->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelEditPins->Location = System::Drawing::Point(5, 248);
			this->labelEditPins->Name = L"labelEditPins";
			this->labelEditPins->Size = System::Drawing::Size(115, 28);
			this->labelEditPins->TabIndex = 22;
			this->labelEditPins->Text = L"Edit Pins";
			this->labelEditPins->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelEditPins->Click += gcnew System::EventHandler(this, &LinkageSimulator::labelEditPins_Click);
			// 
			// labelRunSimulation
			// 
			this->labelRunSimulation->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->labelRunSimulation->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelRunSimulation->ForeColor = System::Drawing::Color::Gray;
			this->labelRunSimulation->Location = System::Drawing::Point(6, 445);
			this->labelRunSimulation->Name = L"labelRunSimulation";
			this->labelRunSimulation->Size = System::Drawing::Size(113, 28);
			this->labelRunSimulation->TabIndex = 24;
			this->labelRunSimulation->Text = L"Start Simulation";
			this->labelRunSimulation->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelRunSimulation->Click += gcnew System::EventHandler(this, &LinkageSimulator::labelRunSimulation_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 313);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(31, 13);
			this->label5->TabIndex = 25;
			this->label5->Text = L"RPM";
			// 
			// textBoxRPM
			// 
			this->textBoxRPM->Location = System::Drawing::Point(46, 24);
			this->textBoxRPM->Name = L"textBoxRPM";
			this->textBoxRPM->Size = System::Drawing::Size(64, 20);
			this->textBoxRPM->TabIndex = 26;
			this->textBoxRPM->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkageSimulator::textBoxRPM_KeyDown);
			this->textBoxRPM->Leave += gcnew System::EventHandler(this, &LinkageSimulator::textBoxRPM_Leave);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(9, 339);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(42, 13);
			this->label7->TabIndex = 25;
			this->label7->Text = L"Interval";
			// 
			// textBoxInterval
			// 
			this->textBoxInterval->Location = System::Drawing::Point(46, 50);
			this->textBoxInterval->Name = L"textBoxInterval";
			this->textBoxInterval->Size = System::Drawing::Size(64, 20);
			this->textBoxInterval->TabIndex = 26;
			this->textBoxInterval->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkageSimulator::textBoxInterval_KeyDown);
			this->textBoxInterval->Leave += gcnew System::EventHandler(this, &LinkageSimulator::textBoxInterval_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(6, 292);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(112, 13);
			this->label6->TabIndex = 25;
			this->label6->Text = L"Motion Parameters";
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->textBoxInterval);
			this->panel1->Controls->Add(this->textBoxRPM);
			this->panel1->Location = System::Drawing::Point(5, 286);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(115, 82);
			this->panel1->TabIndex = 28;
			// 
			// buttonStep
			// 
			this->buttonStep->Location = System::Drawing::Point(72, 419);
			this->buttonStep->Name = L"buttonStep";
			this->buttonStep->Size = System::Drawing::Size(45, 23);
			this->buttonStep->TabIndex = 29;
			this->buttonStep->Text = L"Step";
			this->buttonStep->UseVisualStyleBackColor = true;
			this->buttonStep->Click += gcnew System::EventHandler(this, &LinkageSimulator::buttonStep_Click);
			// 
			// comboBoxGrid
			// 
			this->comboBoxGrid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBoxGrid->FormattingEnabled = true;
			this->comboBoxGrid->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"No Grid", L"Ortho Grid", L"Polar on Pin A",
					L"Polar on Pin B", L"Polar on Pin C", L"Polar on Pin D"
			});
			this->comboBoxGrid->Location = System::Drawing::Point(569, 500);
			this->comboBoxGrid->MaxDropDownItems = 3;
			this->comboBoxGrid->Name = L"comboBoxGrid";
			this->comboBoxGrid->Size = System::Drawing::Size(88, 20);
			this->comboBoxGrid->TabIndex = 21;
			this->comboBoxGrid->SelectedIndexChanged += gcnew System::EventHandler(this, &LinkageSimulator::comboBoxGrid_SelectedIndexChanged);
			// 
			// checkBoxAxes
			// 
			this->checkBoxAxes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxAxes->AutoSize = true;
			this->checkBoxAxes->Location = System::Drawing::Point(672, 502);
			this->checkBoxAxes->Name = L"checkBoxAxes";
			this->checkBoxAxes->Size = System::Drawing::Size(49, 17);
			this->checkBoxAxes->TabIndex = 7;
			this->checkBoxAxes->Text = L"Axes";
			this->checkBoxAxes->UseVisualStyleBackColor = true;
			this->checkBoxAxes->CheckedChanged += gcnew System::EventHandler(this, &LinkageSimulator::checkBoxAxes_CheckedChanged);
			// 
			// checkBoxScale
			// 
			this->checkBoxScale->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxScale->AutoSize = true;
			this->checkBoxScale->Location = System::Drawing::Point(725, 501);
			this->checkBoxScale->Name = L"checkBoxScale";
			this->checkBoxScale->Size = System::Drawing::Size(53, 17);
			this->checkBoxScale->TabIndex = 7;
			this->checkBoxScale->Text = L"Scale";
			this->checkBoxScale->UseVisualStyleBackColor = true;
			this->checkBoxScale->CheckedChanged += gcnew System::EventHandler(this, &LinkageSimulator::checkBoxScale_CheckedChanged);
			// 
			// LinkageSimulator
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->ClientSize = System::Drawing::Size(783, 521);
			this->Controls->Add(this->buttonStep);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->labelRunSimulation);
			this->Controls->Add(this->buttonDeleteCrank);
			this->Controls->Add(this->buttonDeleteCoupler);
			this->Controls->Add(this->labelEditPins);
			this->Controls->Add(this->buttonDeleteRocker);
			this->Controls->Add(this->labelRockerID);
			this->Controls->Add(this->labelCouplerID);
			this->Controls->Add(this->labelCrankID);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->coordLabel);
			this->Controls->Add(this->feedbackLabel);
			this->Controls->Add(this->buttonHelp);
			this->Controls->Add(this->buttonResetView);
			this->Controls->Add(this->buttonEditRocker);
			this->Controls->Add(this->buttonEditCoupler);
			this->Controls->Add(this->buttonEditCrank);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->buttonLoad);
			this->Controls->Add(this->mainPanel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->checkBoxScale);
			this->Controls->Add(this->checkBoxAxes);
			this->Controls->Add(this->comboBoxGrid);
			this->Name = L"LinkageSimulator";
			this->Text = L"LinkageSimulator";
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkageSimulator::LinkageSimulator_MouseWheel);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void labelEditPins_Click(System::Object^ sender, System::EventArgs^ e) {
		if (editPinModeIsOn) { // turn it off

			feedbackLabel->Text = "Pin edit mode has been turned off";
			labelEditPins->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			labelEditPins->BackColor = Color::Lime;
			editPinModeIsOn = false;

			mainPanel->Refresh();
		}
		else if (theSystem != nullptr
			&& (theSystem->getCrank() != nullptr || theSystem->getCoupler() != nullptr || theSystem->getRocker() != nullptr)) {

			feedbackLabel->Text = "Now in pin edit mode.";
			labelEditPins->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			labelEditPins->BackColor = Color::Red;
			editPinModeIsOn = true;

			mainPanel->Refresh();;
		}
		else
			feedbackLabel->Text = "There are no pins to edit.";
	}

	private: System::Void buttonEditCrank_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theSystem->getCrank() == nullptr)
			theSystem->setCrank(new Crank);
		showLinkEditor(theSystem->getCrank());
	}
	private: System::Void buttonEditCoupler_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theSystem->getCoupler() == nullptr)
			theSystem->setCoupler(new Coupler);
		showLinkEditor(theSystem->getCoupler());
	}
	private: System::Void buttonEditRocker_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theSystem->getRocker() == nullptr)
			theSystem->setRocker(new Rocker);
		showLinkEditor(theSystem->getRocker());
	}

	private: void showLinkEditor(Link* aLink);
		   // defined in .cpp due to requiring circular #includes

	private: bool checkPinDetection(int currX, int currY) {
		// identify any pin that may be beneath mouse pointer
		Point2D modelPoint = getWorldCoords(currX, currY);
		if (theSystem->getCrank() != nullptr)
			crankPinEdit = theSystem->getCrank()->nearestPin(modelPoint, false);
		if (theSystem->getCoupler() != nullptr)
			couplerPinEdit = theSystem->getCoupler()->nearestPin(modelPoint, false);
		if (theSystem->getRocker() != nullptr)
			rockerPinEdit = theSystem->getRocker()->nearestPin(modelPoint, false);

		return (crankPinEdit > 0 || couplerPinEdit > 0 || rockerPinEdit > 0);
	}

	private: System::Void mainPanel_Paint(System::Object^ sender,
		System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		g->TranslateTransform(panX, panY);
		g->ScaleTransform(zoomLevel, -zoomLevel);

		if (theSystem != nullptr) {
			// draw grid and axes
			drawCoordinateAxes(g);
			auto temp = comboBoxGrid->SelectedIndex;
			if (comboBoxGrid->SelectedIndex > 0) {
				if (comboBoxGrid->SelectedIndex == 1)
					drawOrthoGrid(g);
				else
					drawPolarGrid(g, char(int('A') + comboBoxGrid->SelectedIndex - 2));

			}
			drawScale(g);

			theSystem->paint(g);
			resetInterfaceValues();
		}
	}

	private: System::Void mainPanel_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		// only needed because the panel doesn't take a mousewheel event, so we must use
		// the main form instead to detect the use of mousewheel
		mouseInPanel = true;
	}
	private: System::Void mainPanel_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		// only needed because the panel doesn't take a mousewheel event, so we must use
		// the main form instead to detect the use of mousewheel
		mouseInPanel = false;
	}
	private: void LinkageSimulator_MouseWheel(Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		// panel does not take a mousewheel event, so we must handle it at the the level of the form
		// but only if the mouse pointer is inside the panel
		// amazingly, this will also handle a touchpad pinch event
		if (mouseInPanel) {

			float zoomStep = 1.2f;  // change as needed for more effect per wheel roll
			float oldZoom = zoomLevel; // will need for resetting panX and panY

			// get actual location of pointer inside the panel (as opposed to the form itself)
			int adjustedX = e->X - mainPanel->Location.X - mainPanel->Margin.Left;
			int adjustedY = e->Y - mainPanel->Location.Y - mainPanel->Margin.Top;

			//e->Delta * SystemInformation::MouseWheelScrollLines / 120
			if (e->Delta < 0) // zoom out
				zoomLevel = zoomLevel / zoomStep;
			else
				zoomLevel = zoomLevel * zoomStep;

			// reset panX and panY such that the coords under the mouse pointer are unchanged
			// i.e., we can zoom in/out on a specific point
			panX = (int)round((adjustedX * (oldZoom - zoomLevel)
				+ panX * zoomLevel) / oldZoom);
			panY = (int)round((adjustedY * (oldZoom - zoomLevel)
				+ panY * zoomLevel) / oldZoom);

			scaleSize = recalcScaleSize();
			mainPanel->Refresh();
		}
	}
	private: System::Void mainPanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		// the first if is part of panning (sets the initial mousewheel click position)
		if (e->Button == System::Windows::Forms::MouseButtons::Middle
			|| (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::Shift)) {
			currX = e->X;
			currY = e->Y;
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::None) {
			showCoords(e);
			checkPinDetection(e->X, e->Y);
		}
	}

	private: System::Void mainPanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		coordLabel->Top = offScreenPos;
		coordLabel->Left = offScreenPos;
	}

	private: System::Void mainPanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		// the first if allows panning by pressing down on mousewheel and dragging
		// or by dragging with left button while holding down the shift key
		// essentially, we adjust panning by however much the mouse is moved
		if (e->Button == System::Windows::Forms::MouseButtons::Middle
			|| (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::Shift)) {
			panX += (e->X - currX);
			panY += (e->Y - currY);
			mainPanel->Refresh();  // this will "repaint" the main panel
			currX = e->X; currY = e->Y; // need to constantly update to allow drag
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Left
			&& Control::ModifierKeys == Keys::None) {
			if (editPinModeIsOn) {
				Point2D newPointCoords = getWorldCoords(e->X, e->Y);
				if (this->Cursor == Cursors::SizeAll) {    // time to move a pin (not great condition check)
					bool movedSomething = false;
					if (crankPinEdit != -1) {  // should never be false, but just to be sure
						theSystem->getCrank()->setPin(crankPinEdit, false, newPointCoords);
						movedSomething = true;
					}
					if (couplerPinEdit != -1) {  // should never be false, but just to be sure
						theSystem->getCoupler()->setPin(couplerPinEdit, false, newPointCoords);
						movedSomething = true;
					}
					if (rockerPinEdit != -1) {  // should never be false, but just to be sure
						theSystem->getRocker()->setPin(rockerPinEdit, false, newPointCoords);
						movedSomething = true;
					}
					mainPanel->Refresh();
					if (movedSomething && theEditor != nullptr && theEditor->Visible) {
						// need to refresh other interface
						((ps05LinkEditor::LinkEditor^)theEditor)->resetLoopBreaker();
						theEditor->Refresh();
						((ps05LinkEditor::LinkEditor^)theEditor)->resetLoopBreaker();
					}
				}
			}
			else
				showCoords(e);
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::None) {
			if (theSystem != nullptr) {
				if (editPinModeIsOn) {
					Point2D model = getWorldCoords(e->X, e->Y);

					if (checkPinDetection(e->X, e->Y)) {
						feedbackLabel->Text = " Moving Pin at ("
							+ model.X.ToString("0.#####") + ", " + model.Y.ToString("0.#####") + ")";
						this->Cursor = Cursors::SizeAll;
					}
					else
						this->Cursor = Cursors::Default;
				}
				else
					this->Cursor = Cursors::Default;
			}
			else
				this->Cursor = Cursors::Default;
		}

	}

	private: void showCoords(System::Windows::Forms::MouseEventArgs^ e) {
		feedbackLabel->Text = "Clicked on screen coords (" + e->X + ", " + e->Y + ")";

		Point2D model = getWorldCoords(e->X, e->Y);

		coordLabel->Text = model.X.ToString("0.##") + ", " + model.Y.ToString("0.##");
		coordLabel->Left = e->X - coordLabel->Width + mainPanel->Left + 5;
		coordLabel->Top = e->Y + coordLabel->Height + mainPanel->Top + 5;
		feedbackLabel->Text += " model coords (" + model.X.ToString("0.###")
			+ ", " + model.Y.ToString("0.###") + ")";
	}

	private: void resetInterfaceValues() {
		if (theSystem != nullptr) {
			showLinkID(theSystem->getCrank(), labelCrankID);
			showLinkID(theSystem->getCoupler(), labelCouplerID);
			showLinkID(theSystem->getRocker(), labelRockerID);
			//showMotionParams();  // cannot put here if I want to change during simulation
			formatSimulateButton();
		}
	}

	private: void showLinkID(Link* currLink, Label^ currLabel) {
		if (currLink != nullptr) {
			currLabel->Text = gcnew String(currLink->getID().c_str());
			currLabel->BackColor = currLink->getColor();
		}
	}

	private: Point2D getScreenCoords(float worldX, float worldY) {
		return { roundf(worldX * zoomLevel) + panX , roundf(worldY * -zoomLevel) + panY };
	}

	private: Point2D getScreenCoords(Point2D worldCoords) {
		return getScreenCoords(worldCoords.X, worldCoords.Y);
	}

	private: Point2D getWorldCoords(float screenX, float screenY) {
		return { (screenX - panX) / zoomLevel, (screenY - panY) / -zoomLevel };
	}

	private: Point2D getWorldCoords(Point2D screenCoords) {
		return getWorldCoords(screenCoords.X, screenCoords.Y);
	}

	private: System::Void buttonLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		//feedbackLabel->Text = "Cannot load now";
		IO::Stream^ myStream; // needed to capture the results
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = ".";  // current folder
		openFileDialog1->Filter = "Linkage System files (*.linksys)|*.linksys|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 1;  // will show only linkage files, but user can choose to show all files
		openFileDialog1->Multiselect = false;  // this is the default, but nice to know
		openFileDialog1->RestoreDirectory = true;

		// actually open the file dialog and get the name of the file user wants
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// user did not press cancel button nor closed the dialog
			// create filestream for the file
			if ((myStream = openFileDialog1->OpenFile()) != nullptr)
			{
				feedbackLabel->Text = openFileDialog1->FileName + " is opening";

				myStream->Close();
				ifstream inFile;
				inFile.open(StringPlus::convertString(openFileDialog1->FileName));
				//inFile.open(Convert::ToString(openFileDialog1->FileName));
				if (inFile.is_open()) {
					// create object as in PS02 tester
					if (theSystem != nullptr)
						delete theSystem;
					theSystem = new LinkageSystem();

					// overwrite link data
					theSystem->readFile(inFile);

					// close file
					inFile.close();

					// perform other action(s)
					resetView();
					//mainPanel->Refresh(); 
					//resetInterfaceValues(); // done by Refresh()
					showMotionParams();

					feedbackLabel->Text = openFileDialog1->FileName + " has been loaded.";
				}
				else
					feedbackLabel->Text = "Could not open " + openFileDialog1->FileName;

			}
		}
	}

	private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theSystem == nullptr)
			feedbackLabel->Text = "There is no system to save.";

		else {
			IO::Stream^ myStream;
			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;

			saveFileDialog1->InitialDirectory = ".";  // current folder
			saveFileDialog1->Filter = "Linkage System files (*.linksys)|*.linksys|All files (*.*)|*.*";
			saveFileDialog1->FilterIndex = 1;  // will show only linkage files, but user can choose to show all files
			saveFileDialog1->RestoreDirectory = true;

			// get the name of the file user wants
			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				// user did not press cancel button nor closed the dialog
				// create filestream for the file
				if ((myStream = saveFileDialog1->OpenFile()) != nullptr)
				{
					feedbackLabel->Text = "Saving file : " + saveFileDialog1->FileName;
					myStream->Close();
					delete myStream;
					ofstream outFile;
					outFile.open(StringPlus::convertString(saveFileDialog1->FileName));
					if (outFile.is_open()) {
						outFile << *theSystem;
						feedbackLabel->Text = saveFileDialog1->FileName + " has been saved.";
						outFile.close();
					}
					else
						feedbackLabel->Text = "Could not open " + saveFileDialog1->FileName + " for writing";
				}
			}
		}
	}

	private: System::Void buttonResetView_Click(System::Object^ sender, System::EventArgs^ e) {
		resetView();
	}

	private: void resetView() {
		if (theSystem != nullptr) {
			Point2D lowerBound = theSystem->lowerBoundingBox();
			Point2D upperBound = theSystem->upperBoundingBox();
			if (lowerBound.X > -INFINITY && upperBound.X > -INFINITY) {
				float borderSpaceRatio = 0.85;

				float shapeHeight = upperBound.Y - lowerBound.Y;
				float shapeWidth = upperBound.X - lowerBound.X;

				float heightRatio = mainPanel->Height / shapeHeight;
				float widthRatio = mainPanel->Width / shapeWidth;

				zoomLevel = min(heightRatio, widthRatio) * borderSpaceRatio;

				panY = mainPanel->Height / 2;
				panX = mainPanel->Width / 2;
				panX += -(upperBound.X + lowerBound.X) / 2. * zoomLevel;
				panY += (upperBound.Y + lowerBound.Y) / 2. * zoomLevel;
				// note that panY adjustment is not negative because panY is applied before scaling

				scaleSize = recalcScaleSize();

				mainPanel->Refresh();
				feedbackLabel->Text = "View has been reset.";

			}
		}
	}

	private: System::Void buttonStep_Click(System::Object^ sender, System::EventArgs^ e) {

		if (theSystem != nullptr && theSystem->canSimulate()) {
			// advance one step
			theSystem->getCrank()->moveLink(nullptr, theSystem->getCoupler());
			theSystem->getCoupler()->moveLink(theSystem->getCrank(), theSystem->getRocker());
			theSystem->getRocker()->moveLink(theSystem->getCoupler(), nullptr);
			mainPanel->Refresh();
		}
		else
			feedbackLabel->Text = "Cannot step simulation with model in its current state.";

	}

	private: System::Void labelRunSimulation_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theSystem != nullptr && theSystem->canSimulate()) {
			simulationIsOn = !simulationIsOn;
			getRPMFromBox(); getIntervalFromBox();  // having problems with _Leave event
			formatSimulateButton();
			if (simulationIsOn) {

				//exit editpinMode, maybe later I'll allow this
				editPinModeIsOn = true;
				labelEditPins_Click(nullptr, nullptr);

				feedbackLabel->Text = "Simulation has been started.";

				// turn on simulation
				theSystem->turnSimulationOn();

				// start thread
				// setting the following to false risks cross-thread issues, but these
				// risks are not very applicable here since it is what I want.
				System::Windows::Forms::Form::CheckForIllegalCrossThreadCalls = false;

				// define the thread that will run the simulation
				System::Threading::Thread^ simulationThread = gcnew System::Threading::Thread(
					gcnew System::Threading::ThreadStart(this, &LinkageSimulator::simulateContinuous));

				// actually start the thread
				simulationThread->Start();

			}
			else {
				// turn off simulation, causing thread to end
				theSystem->turnSimulationOff();

				feedbackLabel->Text = "Simulation has been stopped.";
			}
		}
		else {
			simulationIsOn = false;
			formatSimulateButton();
			feedbackLabel->Text = "Simulation of the linkage system is not possible in its current state";
		}
	}

	private: void simulateContinuous() {
		theSystem->simulate(this);
	}

	private: void formatSimulateButton() {
		if (theSystem == nullptr || !theSystem->canSimulate()) {
			// turn button gray
			labelRunSimulation->Text = "Start Simulation";
			labelRunSimulation->BackColor = Color::FromArgb(224, 224, 224);
			labelRunSimulation->ForeColor = Color::Gray;

			// turn step button gray
			buttonStep->BackColor = Color::FromArgb(224, 224, 224);
			buttonStep->ForeColor = Color::Gray;
		}
		else {
			if (simulationIsOn) {
				// turn button red
				labelRunSimulation->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				labelRunSimulation->BackColor = Color::Red;
				labelRunSimulation->Text = "Stop Simulation";
				labelRunSimulation->ForeColor = Color::White;

				// turn step button gray
				buttonStep->BackColor = Color::FromArgb(224, 224, 224);
				buttonStep->ForeColor = Color::Gray;

			}
			else {
				// turn button green
				labelRunSimulation->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				labelRunSimulation->BackColor = Color::Lime;
				labelRunSimulation->Text = "Start Simulation";
				labelRunSimulation->ForeColor = Color::Black;

				// turn step button regular
				buttonHelp->UseVisualStyleBackColor = true;
				buttonStep->ForeColor = Color::Black;
			}
		}


	}

	private: void showMotionParams() {
		if (theSystem != nullptr && theSystem->getMotion() != nullptr) {
			textBoxRPM->Text = theSystem->getMotion()->getSpeed().ToString("0.###");
			textBoxInterval->Text = theSystem->getMotion()->getInterval().ToString("0.###");
		}
		else {
			textBoxRPM->Text = "";
			textBoxInterval->Text = "";
		}
	}

	private: void getRPMFromBox() {
		if (textBoxRPM->Text != "") {
			try {
				float currValue;

				currValue = Convert::ToDouble(textBoxRPM->Text);
				if (theSystem->getMotion() == nullptr) {
					theSystem->setMotion(new InputMotion);
				}
				theSystem->getMotion()->setSpeed(currValue);

			}
			catch (Exception ^ excep) {
				MessageBox::Show(this, "Value -> " + textBoxRPM->Text
					+ " <- could not be converted to a rotation speed.\n"
					+ excep->Message, "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
				textBoxRPM->Focus();
			}
		}
	}
	private: void getIntervalFromBox() {
		if (textBoxInterval->Text != "") {
			try {
				float currValue;

				currValue = Convert::ToDouble(textBoxInterval->Text);

				InputMotion* aMotion;
				if (theSystem->getMotion() == nullptr) {
					theSystem->setMotion(new InputMotion);
				}
				theSystem->getMotion()->setInterval(currValue);

			}
			catch (Exception ^ excep) {
				MessageBox::Show(this, "Value -> " + textBoxInterval->Text
					+ " <- could not be converted to a time interval.\n"
					+ excep->Message, "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
				textBoxInterval->Focus();
			}
		}

	}
	private: System::Void textBoxInterval_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getIntervalFromBox();
			e->SuppressKeyPress = true;
		}
	}
	private: System::Void textBoxInterval_Leave(System::Object^ sender, System::EventArgs^ e) {
		getIntervalFromBox();
	}

	private: System::Void textBoxRPM_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getRPMFromBox();
			e->SuppressKeyPress = true;
		}
	}
	private: System::Void textBoxRPM_Leave(System::Object^ sender, System::EventArgs^ e) {
		getRPMFromBox();
	}

	public: void showMessage(String^ aMessage) {
		feedbackLabel->Text = aMessage;
	}

	public: void showFeedback(String^ aMessage) {
		feedbackLabel->Text = aMessage;
	}
	private: float recalcScaleSize() {
		Point2D topCorner = getWorldCoords(10, 10);
		Point2D botCorner = getWorldCoords(90, 20);
		int decimalPlaces = -5;
		float sizeX = roundf(botCorner.X - topCorner.X) * pow(10., decimalPlaces);
		while (sizeX <= 0.) {
			decimalPlaces++;
			sizeX = roundf((botCorner.X - topCorner.X) * pow(10., decimalPlaces));
		}
		sizeX /= pow(10., decimalPlaces);
		return sizeX;
	}

	private: void drawCoordinateAxes(Graphics^ g) {
		if (checkBoxAxes->Checked) {
			float axesLength = scaleSize * 2;

			Pen^ xPen = gcnew Pen(Color::Red, axesLength / 40.);
			Pen^ yPen = gcnew Pen(Color::Green, axesLength / 40.);
			float arrowLength = axesLength * 0.1;

			// draw lines with arrowheads
			g->DrawLine(xPen, 0., 0., axesLength, 0.);
			g->DrawLine(xPen, axesLength - arrowLength, arrowLength / 2., axesLength, 0.);
			g->DrawLine(xPen, axesLength - arrowLength, -arrowLength / 2., axesLength, 0.);

			g->DrawLine(yPen, 0., 0., 0., axesLength);
			g->DrawLine(yPen, arrowLength / 2., axesLength - arrowLength, 0., axesLength);
			g->DrawLine(yPen, -arrowLength / 2., axesLength - arrowLength, 0., axesLength);

		}
	}

	private: void drawOrthoGrid(Graphics^ g) {
		Pen^ gridPen = gcnew Pen(colorFromHSV(240, 0.1, 1.0), 0.);

		float spacing = scaleSize * 0.25;

		Point2D topLeftCorner = getWorldCoords(0, 0);
		Point2D botRightCorner = getWorldCoords(mainPanel->Width, mainPanel->Height);
		float minX = topLeftCorner.X, maxX = botRightCorner.X;
		float maxY = topLeftCorner.Y, minY = botRightCorner.Y;
		float xLimit = max(fabs(minX), fabs(maxX));
		float yLimit = max(fabs(minY), fabs(maxY));
		float currGridX = -spacing;
		float currGridY = -spacing;
		while (currGridX <= xLimit || currGridY <= yLimit) {
			currGridX += spacing;
			currGridY += spacing;
			g->DrawLine(gridPen, currGridX, minY, currGridX, maxY);
			g->DrawLine(gridPen, minX, currGridY, maxX, currGridY);
			g->DrawLine(gridPen, -currGridX, minY, -currGridX, maxY);
			g->DrawLine(gridPen, minX, -currGridY, maxX, -currGridY);
		}
	}

	private: void drawPolarGrid(Graphics^ g, char pinForCenter) {

		// change center to whatever pin is wanted

		Point2D transPoint = { -INFINITY, -INFINITY };
		switch (pinForCenter) {
		case 'A':
			if (theSystem->getCrank() != nullptr)
				transPoint = theSystem->getCrank()->getPin(1, false);
			break;
		case 'B':
			if (theSystem->getCrank() != nullptr)
				transPoint = theSystem->getCrank()->getPin(2, false);
			else if (theSystem->getCoupler() != nullptr)
				transPoint = theSystem->getCoupler()->getPin(1, false);
			break;
		case 'C':
			if (theSystem->getRocker() != nullptr)
				transPoint = theSystem->getRocker()->getPin(1, false);
			else if (theSystem->getCoupler() != nullptr)
				transPoint = theSystem->getCoupler()->getPin(2, false);
			break;
		case 'D':
			if (theSystem->getRocker() != nullptr)
				transPoint = theSystem->getRocker()->getPin(2, false);
			break;
		}

		if (transPoint.X > -INFINITY && transPoint.Y > -INFINITY) {
			g->TranslateTransform(transPoint.X, transPoint.Y);

			Pen^ gridPen = gcnew Pen(colorFromHSV(240, 0.1, 1.0), 0.);

			// draw circles
			int numbCircles = 30.; // change as needed
			float circleSpacing = scaleSize * 0.5;
			float currDiam;

			for (int i = 1; i <= numbCircles; i++) {
				currDiam = circleSpacing * i * 2;
				g->DrawEllipse(gridPen, -currDiam / 2., -currDiam / 2., currDiam, currDiam);
			}

			// draw radial lines
			int groupCount = 8; // 4 lines per group
			for (int i = 0; i < groupCount; i++) {
				g->DrawLine(gridPen, 0., 0., numbCircles * circleSpacing, 0.);
				g->RotateTransform(360. / groupCount / 2.);
				g->DrawLine(gridPen, 2 * circleSpacing, 0., numbCircles * circleSpacing, 0.);
				g->RotateTransform(-360. / groupCount / 4.);
				g->DrawLine(gridPen, 4 * circleSpacing, 0., numbCircles * circleSpacing, 0.);
				g->RotateTransform(360. / groupCount / 2.);
				g->DrawLine(gridPen, 4 * circleSpacing, 0., numbCircles * circleSpacing, 0.);
				g->RotateTransform(360. / groupCount / 4.);
			}

			g->TranslateTransform(-transPoint.X, -transPoint.Y);
		}
	}

	private: void drawScale(Graphics^ g) {

		if (checkBoxScale->Checked && theSystem != nullptr) {
			// convert from screen size and location I want it to appear to
			// corresponding world coords
			Point2D topCorner = getWorldCoords(10, 10);
			Point2D botCorner = getWorldCoords(90, 20);
			float sizeX = scaleSize;
			float sizeY = (topCorner.Y - botCorner.Y);
			sizeY = max(1e-8, sizeY);  // sizeY cannot be zero

			// draw the scale box
			Brush^ fillBrush = gcnew SolidBrush(Color::Aquamarine);
			g->FillRectangle(fillBrush, topCorner.X, botCorner.Y, sizeX, sizeY);

			// draw the number
			float locX = topCorner.X + sizeX, locY = botCorner.Y;
			g->TranslateTransform(locX, locY);
			g->ScaleTransform(1, -1);

			System::Drawing::Font^ scaleFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif",
				sizeY, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0));
			g->DrawString(sizeX.ToString(), scaleFont, fillBrush, 0., 0.);
			g->ScaleTransform(1, -1);
			g->TranslateTransform(-locX, -locY);
		}
	}

	private: System::Void comboBoxGrid_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
	}
	private: System::Void checkBoxAxes_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
		if (checkBoxAxes->Checked)
			feedbackLabel->Text = "Turned on Geometric Axes";
		else
			feedbackLabel->Text = "Turned off Geometric Axes";
	}
	private: System::Void checkBoxScale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
		if (checkBoxAxes->Checked)
			feedbackLabel->Text = "Turned on Scale Display";
		else
			feedbackLabel->Text = "Turned off Scale Display";
	}
	

};
}
