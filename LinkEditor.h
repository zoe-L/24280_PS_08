/*
Nestor Gomez
24-280 C++ for Engrs.
PS05. Due Mar. 5, 2020

GUI for editing a link.

*/

#pragma once
#include <fstream>
#include "ColorConverter.h"
#include "StringPlus.h"
#include "Shape2D.h"
#include "Link.h"
//#include "LinkageSimulator.h"



#include "FlickerLessPanel.h"
// using flickerless panel makes the form design view not work.
// to use flickerless panel or allow the design view, use one of these
// in InitComponents() function
//    for design view >>>>    this->mainPanel = (gcnew System::Windows::Forms::Panel());
//    for flickerless >>>>    this->mainPanel = (gcnew FlickerLessPanel());


namespace ps05LinkEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

		/// <summary>
		/// Summary for LinkEditor
		/// </summary>
	public ref class LinkEditor : public System::Windows::Forms::Form
	{
	public:
		LinkEditor(void)
		{
			panX = panY = 300;
			zoomLevel = 1.;
			mouseInPanel = false;

			InitializeComponent();

			panX = panY = 300;
			zoomLevel = 1.;
			mouseInPanel = false;
			coordLabel->Location = System::Drawing::Point(offScreenPos, offScreenPos);
			labelEditPoints_Click(nullptr, nullptr);
			comboBoxGrid->SelectedIndex = 0;
			feedbackLabel->Text = " - - - ";
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LinkEditor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ mainPanel;

	private: System::Windows::Forms::Button^ buttonLoad;
	private: System::Windows::Forms::Label^ feedbackLabel;

	protected:
		Shape2D* theShape = nullptr;
		Link* theLink = nullptr;
		int panX, panY, currX, currY;
		float zoomLevel;
		bool mouseInPanel;
		float lineWidthScale = 30.;
		int offScreenPos = -200;
		String^ prevFeedback = " - - - ";
		bool editPointModeIsOn = true;
		int currPointIndex = 1;
		int currLinkPin = -1;
		System::Windows::Forms::Form^ theSimulator = nullptr;
		bool loopBreaker = false;

		// float shapeLineWidth = 0; // can get from scroll directly
		// Color lineColor;  // can get from color label directly

	private:


	private: System::Windows::Forms::Button^ buttonResetView;
	private: System::Windows::Forms::CheckBox^ checkBoxCentroid;
	private: System::Windows::Forms::CheckBox^ checkBoxAxes;
	private: System::Windows::Forms::HScrollBar^ hScrollBarLineWidth;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ labelLinkColor;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ coordLabel;
	private: System::Windows::Forms::CheckBox^ checkBoxCentering;
	private: System::Windows::Forms::Button^ buttonHelp;
	private: System::Windows::Forms::TextBox^ textBoxLineWidth;
	private: System::Windows::Forms::RadioButton^ radioButtonLocalCoords;
	private: System::Windows::Forms::RadioButton^ radioButtonGlobalCoords;


	private: System::Windows::Forms::Button^ buttonSave;
	private: System::Windows::Forms::TextBox^ textLocal1;




	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textLocal2;


	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textGlobal1;


	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textGlobal2;


	private: System::Windows::Forms::Label^ label9;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textThickness;

	private: System::Windows::Forms::Label^ labelEditPoints;
	private: System::Windows::Forms::TextBox^ textEditPoints;
	private: System::Windows::Forms::HScrollBar^ hScrollBarEditPoints;
	private: System::Windows::Forms::Label^ labelCurrEditPoint;
	private: System::Windows::Forms::Button^ buttonRemovePoint;
	private: System::Windows::Forms::Button^ buttonInsertPoint;
	private: System::Windows::Forms::Label^ labelLinkArea;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxLinkID;
	private: System::Windows::Forms::ComboBox^ comboBoxGrid;





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
			   //this->mainPanel = (gcnew System::Windows::Forms::Panel());
			   this->mainPanel = (gcnew FlickerLessPanel()); 
			   this->buttonLoad = (gcnew System::Windows::Forms::Button());
			   this->feedbackLabel = (gcnew System::Windows::Forms::Label());
			   this->buttonResetView = (gcnew System::Windows::Forms::Button());
			   this->checkBoxCentroid = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBoxAxes = (gcnew System::Windows::Forms::CheckBox());
			   this->hScrollBarLineWidth = (gcnew System::Windows::Forms::HScrollBar());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->labelLinkColor = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->coordLabel = (gcnew System::Windows::Forms::Label());
			   this->checkBoxCentering = (gcnew System::Windows::Forms::CheckBox());
			   this->buttonHelp = (gcnew System::Windows::Forms::Button());
			   this->textBoxLineWidth = (gcnew System::Windows::Forms::TextBox());
			   this->radioButtonLocalCoords = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButtonGlobalCoords = (gcnew System::Windows::Forms::RadioButton());
			   this->buttonSave = (gcnew System::Windows::Forms::Button());
			   this->textLocal1 = (gcnew System::Windows::Forms::TextBox());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->textLocal2 = (gcnew System::Windows::Forms::TextBox());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->textGlobal1 = (gcnew System::Windows::Forms::TextBox());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->textGlobal2 = (gcnew System::Windows::Forms::TextBox());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->label11 = (gcnew System::Windows::Forms::Label());
			   this->textThickness = (gcnew System::Windows::Forms::TextBox());
			   this->labelEditPoints = (gcnew System::Windows::Forms::Label());
			   this->textEditPoints = (gcnew System::Windows::Forms::TextBox());
			   this->hScrollBarEditPoints = (gcnew System::Windows::Forms::HScrollBar());
			   this->labelCurrEditPoint = (gcnew System::Windows::Forms::Label());
			   this->buttonRemovePoint = (gcnew System::Windows::Forms::Button());
			   this->buttonInsertPoint = (gcnew System::Windows::Forms::Button());
			   this->labelLinkArea = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->textBoxLinkID = (gcnew System::Windows::Forms::TextBox());
			   this->comboBoxGrid = (gcnew System::Windows::Forms::ComboBox());
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->label1->ForeColor = System::Drawing::Color::Fuchsia;
			   this->label1->Location = System::Drawing::Point(14, 12);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(125, 25);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Link Editor";
			   // 
			   // mainPanel
			   // 
			   this->mainPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->mainPanel->BackColor = System::Drawing::SystemColors::Window;
			   this->mainPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			   this->mainPanel->Location = System::Drawing::Point(128, 44);
			   this->mainPanel->Name = L"mainPanel";
			   this->mainPanel->Size = System::Drawing::Size(657, 394);
			   this->mainPanel->TabIndex = 1;
			   this->mainPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &LinkEditor::mainPanel_Paint);
			   this->mainPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkEditor::mainPanel_MouseDown);
			   this->mainPanel->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::mainPanel_MouseEnter);
			   this->mainPanel->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::mainPanel_MouseLeave);
			   this->mainPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkEditor::mainPanel_MouseMove);
			   this->mainPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkEditor::mainPanel_MouseUp);
			   // 
			   // buttonLoad
			   // 
			   this->buttonLoad->Location = System::Drawing::Point(9, 44);
			   this->buttonLoad->Name = L"buttonLoad";
			   this->buttonLoad->Size = System::Drawing::Size(52, 30);
			   this->buttonLoad->TabIndex = 1;
			   this->buttonLoad->Text = L"Load";
			   this->buttonLoad->UseVisualStyleBackColor = true;
			   this->buttonLoad->Click += gcnew System::EventHandler(this, &LinkEditor::buttonLoad_Click);
			   this->buttonLoad->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::buttonLoad_MouseEnter);
			   this->buttonLoad->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::buttonLoad_MouseLeave);
			   // 
			   // feedbackLabel
			   // 
			   this->feedbackLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->feedbackLabel->AutoSize = true;
			   this->feedbackLabel->Location = System::Drawing::Point(12, 446);
			   this->feedbackLabel->Name = L"feedbackLabel";
			   this->feedbackLabel->Size = System::Drawing::Size(28, 13);
			   this->feedbackLabel->TabIndex = 3;
			   this->feedbackLabel->Text = L" - - - ";
			   // 
			   // buttonResetView
			   // 
			   this->buttonResetView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->buttonResetView->Location = System::Drawing::Point(638, 12);
			   this->buttonResetView->Name = L"buttonResetView";
			   this->buttonResetView->Size = System::Drawing::Size(70, 25);
			   this->buttonResetView->TabIndex = 6;
			   this->buttonResetView->Text = L"Reset View";
			   this->buttonResetView->UseVisualStyleBackColor = true;
			   this->buttonResetView->Click += gcnew System::EventHandler(this, &LinkEditor::buttonResetView_Click);
			   this->buttonResetView->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::buttonResetView_MouseEnter);
			   this->buttonResetView->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::buttonResetView_MouseLeave);
			   // 
			   // checkBoxCentroid
			   // 
			   this->checkBoxCentroid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->checkBoxCentroid->AutoSize = true;
			   this->checkBoxCentroid->Location = System::Drawing::Point(690, 448);
			   this->checkBoxCentroid->Name = L"checkBoxCentroid";
			   this->checkBoxCentroid->Size = System::Drawing::Size(95, 17);
			   this->checkBoxCentroid->TabIndex = 7;
			   this->checkBoxCentroid->Text = L"Show Centroid";
			   this->checkBoxCentroid->UseVisualStyleBackColor = true;
			   this->checkBoxCentroid->CheckedChanged += gcnew System::EventHandler(this, &LinkEditor::checkBoxCentroid_CheckedChanged);
			   // 
			   // checkBoxAxes
			   // 
			   this->checkBoxAxes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->checkBoxAxes->AutoSize = true;
			   this->checkBoxAxes->Location = System::Drawing::Point(605, 448);
			   this->checkBoxAxes->Name = L"checkBoxAxes";
			   this->checkBoxAxes->Size = System::Drawing::Size(79, 17);
			   this->checkBoxAxes->TabIndex = 7;
			   this->checkBoxAxes->Text = L"Show Axes";
			   this->checkBoxAxes->UseVisualStyleBackColor = true;
			   this->checkBoxAxes->CheckedChanged += gcnew System::EventHandler(this, &LinkEditor::checkBoxAxes_CheckedChanged);
			   // 
			   // hScrollBarLineWidth
			   // 
			   this->hScrollBarLineWidth->Location = System::Drawing::Point(11, 405);
			   this->hScrollBarLineWidth->Name = L"hScrollBarLineWidth";
			   this->hScrollBarLineWidth->Size = System::Drawing::Size(66, 12);
			   this->hScrollBarLineWidth->TabIndex = 8;
			   this->hScrollBarLineWidth->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &LinkEditor::hScrollBarLineWidth_Scroll);
			   this->hScrollBarLineWidth->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::hScrollBarLineWidth_MouseEnter);
			   this->hScrollBarLineWidth->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::hScrollBarLineWidth_MouseLeave);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(12, 391);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(58, 13);
			   this->label2->TabIndex = 9;
			   this->label2->Text = L"Line Width";
			   // 
			   // labelLinkColor
			   // 
			   this->labelLinkColor->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(192)));
			   this->labelLinkColor->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->labelLinkColor->Location = System::Drawing::Point(49, 210);
			   this->labelLinkColor->Name = L"labelLinkColor";
			   this->labelLinkColor->Size = System::Drawing::Size(72, 22);
			   this->labelLinkColor->TabIndex = 10;
			   this->labelLinkColor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->labelLinkColor->Click += gcnew System::EventHandler(this, &LinkEditor::labelLinkColor_Click);
			   this->labelLinkColor->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::labelLinkColor_MouseEnter);
			   this->labelLinkColor->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::labelLinkColor_MouseLeave);
			   // 
			   // label3
			   // 
			   this->label3->Location = System::Drawing::Point(5, 113);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(46, 13);
			   this->label3->TabIndex = 9;
			   this->label3->Text = L"Local 1";
			   this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // coordLabel
			   // 
			   this->coordLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->coordLabel->AutoSize = true;
			   this->coordLabel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(128)));
			   this->coordLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->coordLabel->Location = System::Drawing::Point(220, 18);
			   this->coordLabel->Name = L"coordLabel";
			   this->coordLabel->Size = System::Drawing::Size(92, 15);
			   this->coordLabel->TabIndex = 11;
			   this->coordLabel->Text = L"coordinate popup";
			   this->coordLabel->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			   // 
			   // checkBoxCentering
			   // 
			   this->checkBoxCentering->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->checkBoxCentering->AutoSize = true;
			   this->checkBoxCentering->Checked = true;
			   this->checkBoxCentering->CheckState = System::Windows::Forms::CheckState::Checked;
			   this->checkBoxCentering->Location = System::Drawing::Point(485, 447);
			   this->checkBoxCentering->Name = L"checkBoxCentering";
			   this->checkBoxCentering->Size = System::Drawing::Size(114, 17);
			   this->checkBoxCentering->TabIndex = 7;
			   this->checkBoxCentering->Text = L"Center on Centroid";
			   this->checkBoxCentering->UseVisualStyleBackColor = true;
			   // 
			   // buttonHelp
			   // 
			   this->buttonHelp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->buttonHelp->Location = System::Drawing::Point(713, 12);
			   this->buttonHelp->Name = L"buttonHelp";
			   this->buttonHelp->Size = System::Drawing::Size(70, 25);
			   this->buttonHelp->TabIndex = 12;
			   this->buttonHelp->Text = L"Help";
			   this->buttonHelp->UseVisualStyleBackColor = true;
			   this->buttonHelp->Click += gcnew System::EventHandler(this, &LinkEditor::buttonHelp_Click);
			   // 
			   // textBoxLineWidth
			   // 
			   this->textBoxLineWidth->Location = System::Drawing::Point(85, 397);
			   this->textBoxLineWidth->Name = L"textBoxLineWidth";
			   this->textBoxLineWidth->Size = System::Drawing::Size(36, 20);
			   this->textBoxLineWidth->TabIndex = 13;
			   this->textBoxLineWidth->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBoxLineWidth_KeyDown);
			   this->textBoxLineWidth->Leave += gcnew System::EventHandler(this, &LinkEditor::textBoxLineWidth_Leave);
			   // 
			   // radioButtonLocalCoords
			   // 
			   this->radioButtonLocalCoords->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->radioButtonLocalCoords->AutoSize = true;
			   this->radioButtonLocalCoords->Checked = true;
			   this->radioButtonLocalCoords->Location = System::Drawing::Point(546, 6);
			   this->radioButtonLocalCoords->Name = L"radioButtonLocalCoords";
			   this->radioButtonLocalCoords->Size = System::Drawing::Size(87, 17);
			   this->radioButtonLocalCoords->TabIndex = 14;
			   this->radioButtonLocalCoords->TabStop = true;
			   this->radioButtonLocalCoords->Text = L"Local Coords";
			   this->radioButtonLocalCoords->UseVisualStyleBackColor = true;
			   this->radioButtonLocalCoords->Click += gcnew System::EventHandler(this, &LinkEditor::radioButtonLocalCoords_Click);
			   // 
			   // radioButtonGlobalCoords
			   // 
			   this->radioButtonGlobalCoords->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->radioButtonGlobalCoords->AutoSize = true;
			   this->radioButtonGlobalCoords->Location = System::Drawing::Point(546, 23);
			   this->radioButtonGlobalCoords->Name = L"radioButtonGlobalCoords";
			   this->radioButtonGlobalCoords->Size = System::Drawing::Size(91, 17);
			   this->radioButtonGlobalCoords->TabIndex = 14;
			   this->radioButtonGlobalCoords->Text = L"Global Coords";
			   this->radioButtonGlobalCoords->UseVisualStyleBackColor = true;
			   this->radioButtonGlobalCoords->Click += gcnew System::EventHandler(this, &LinkEditor::radioButtonGlobalCoords_Click);
			   // 
			   // buttonSave
			   // 
			   this->buttonSave->Location = System::Drawing::Point(72, 44);
			   this->buttonSave->Name = L"buttonSave";
			   this->buttonSave->Size = System::Drawing::Size(50, 30);
			   this->buttonSave->TabIndex = 2;
			   this->buttonSave->Text = L"Save";
			   this->buttonSave->UseVisualStyleBackColor = true;
			   this->buttonSave->Click += gcnew System::EventHandler(this, &LinkEditor::buttonSave_Click);
			   this->buttonSave->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::buttonSave_MouseEnter);
			   this->buttonSave->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::buttonSave_MouseLeave);
			   // 
			   // textLocal1
			   // 
			   this->textLocal1->Location = System::Drawing::Point(52, 110);
			   this->textLocal1->Name = L"textLocal1";
			   this->textLocal1->Size = System::Drawing::Size(70, 20);
			   this->textLocal1->TabIndex = 15;
			   this->textLocal1->Text = L"x, y";
			   this->textLocal1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBox_KeyDown);
			   this->textLocal1->Leave += gcnew System::EventHandler(this, &LinkEditor::textBox_Leave);
			   // 
			   // label6
			   // 
			   this->label6->Location = System::Drawing::Point(5, 135);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(46, 13);
			   this->label6->TabIndex = 9;
			   this->label6->Text = L"Local 2";
			   this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // textLocal2
			   // 
			   this->textLocal2->Location = System::Drawing::Point(52, 132);
			   this->textLocal2->Name = L"textLocal2";
			   this->textLocal2->Size = System::Drawing::Size(70, 20);
			   this->textLocal2->TabIndex = 15;
			   this->textLocal2->Text = L"x, y";
			   this->textLocal2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBox_KeyDown);
			   this->textLocal2->Leave += gcnew System::EventHandler(this, &LinkEditor::textBox_Leave);
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Location = System::Drawing::Point(5, 157);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(46, 13);
			   this->label7->TabIndex = 9;
			   this->label7->Text = L"Global 1";
			   this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // textGlobal1
			   // 
			   this->textGlobal1->Location = System::Drawing::Point(52, 154);
			   this->textGlobal1->Name = L"textGlobal1";
			   this->textGlobal1->Size = System::Drawing::Size(70, 20);
			   this->textGlobal1->TabIndex = 15;
			   this->textGlobal1->Text = L"x, y";
			   this->textGlobal1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBox_KeyDown);
			   this->textGlobal1->Leave += gcnew System::EventHandler(this, &LinkEditor::textBox_Leave);
			   // 
			   // label8
			   // 
			   this->label8->AutoSize = true;
			   this->label8->Location = System::Drawing::Point(5, 179);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(46, 13);
			   this->label8->TabIndex = 9;
			   this->label8->Text = L"Global 2";
			   this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // textGlobal2
			   // 
			   this->textGlobal2->Location = System::Drawing::Point(52, 176);
			   this->textGlobal2->Name = L"textGlobal2";
			   this->textGlobal2->Size = System::Drawing::Size(70, 20);
			   this->textGlobal2->TabIndex = 15;
			   this->textGlobal2->Text = L"x, y";
			   this->textGlobal2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBox_KeyDown);
			   this->textGlobal2->Leave += gcnew System::EventHandler(this, &LinkEditor::textBox_Leave);
			   // 
			   // label9
			   // 
			   this->label9->Location = System::Drawing::Point(15, 202);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(31, 35);
			   this->label9->TabIndex = 9;
			   this->label9->Text = L"Link Color";
			   this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // label11
			   // 
			   this->label11->Location = System::Drawing::Point(5, 241);
			   this->label11->Name = L"label11";
			   this->label11->Size = System::Drawing::Size(64, 17);
			   this->label11->TabIndex = 9;
			   this->label11->Text = L"Thickness";
			   this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // textThickness
			   // 
			   this->textThickness->Location = System::Drawing::Point(71, 238);
			   this->textThickness->Name = L"textThickness";
			   this->textThickness->Size = System::Drawing::Size(36, 20);
			   this->textThickness->TabIndex = 15;
			   // 
			   // labelEditPoints
			   // 
			   this->labelEditPoints->BackColor = System::Drawing::Color::Lime;
			   this->labelEditPoints->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->labelEditPoints->Location = System::Drawing::Point(10, 301);
			   this->labelEditPoints->Name = L"labelEditPoints";
			   this->labelEditPoints->Size = System::Drawing::Size(42, 32);
			   this->labelEditPoints->TabIndex = 17;
			   this->labelEditPoints->Text = L"Edit Points";
			   this->labelEditPoints->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->labelEditPoints->Click += gcnew System::EventHandler(this, &LinkEditor::labelEditPoints_Click);
			   // 
			   // textEditPoints
			   // 
			   this->textEditPoints->Enabled = false;
			   this->textEditPoints->Location = System::Drawing::Point(9, 336);
			   this->textEditPoints->Name = L"textEditPoints";
			   this->textEditPoints->Size = System::Drawing::Size(112, 20);
			   this->textEditPoints->TabIndex = 15;
			   this->textEditPoints->Text = L"x, y";
			   this->textEditPoints->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textEditPoints_KeyDown);
			   this->textEditPoints->Leave += gcnew System::EventHandler(this, &LinkEditor::textEditPoints_Leave);
			   // 
			   // hScrollBarEditPoints
			   // 
			   this->hScrollBarEditPoints->LargeChange = 1;
			   this->hScrollBarEditPoints->Location = System::Drawing::Point(55, 301);
			   this->hScrollBarEditPoints->Name = L"hScrollBarEditPoints";
			   this->hScrollBarEditPoints->Size = System::Drawing::Size(66, 15);
			   this->hScrollBarEditPoints->TabIndex = 8;
			   this->hScrollBarEditPoints->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &LinkEditor::hScrollBarEditPoints_Scroll);
			   this->hScrollBarEditPoints->MouseEnter += gcnew System::EventHandler(this, &LinkEditor::hScrollBarLineWidth_MouseEnter);
			   this->hScrollBarEditPoints->MouseLeave += gcnew System::EventHandler(this, &LinkEditor::hScrollBarLineWidth_MouseLeave);
			   // 
			   // labelCurrEditPoint
			   // 
			   this->labelCurrEditPoint->AutoSize = true;
			   this->labelCurrEditPoint->Location = System::Drawing::Point(54, 320);
			   this->labelCurrEditPoint->Name = L"labelCurrEditPoint";
			   this->labelCurrEditPoint->Size = System::Drawing::Size(16, 13);
			   this->labelCurrEditPoint->TabIndex = 18;
			   this->labelCurrEditPoint->Text = L"---";
			   // 
			   // buttonRemovePoint
			   // 
			   this->buttonRemovePoint->Location = System::Drawing::Point(66, 361);
			   this->buttonRemovePoint->Name = L"buttonRemovePoint";
			   this->buttonRemovePoint->Size = System::Drawing::Size(55, 20);
			   this->buttonRemovePoint->TabIndex = 19;
			   this->buttonRemovePoint->Text = L"Remove";
			   this->buttonRemovePoint->UseVisualStyleBackColor = true;
			   this->buttonRemovePoint->Click += gcnew System::EventHandler(this, &LinkEditor::buttonRemovePoint_Click);
			   // 
			   // buttonInsertPoint
			   // 
			   this->buttonInsertPoint->Location = System::Drawing::Point(9, 361);
			   this->buttonInsertPoint->Name = L"buttonInsertPoint";
			   this->buttonInsertPoint->Size = System::Drawing::Size(55, 20);
			   this->buttonInsertPoint->TabIndex = 19;
			   this->buttonInsertPoint->Text = L"Insert";
			   this->buttonInsertPoint->UseVisualStyleBackColor = true;
			   this->buttonInsertPoint->Click += gcnew System::EventHandler(this, &LinkEditor::buttonInsertPoint_Click);
			   // 
			   // labelLinkArea
			   // 
			   this->labelLinkArea->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->labelLinkArea->Location = System::Drawing::Point(71, 267);
			   this->labelLinkArea->Name = L"labelLinkArea";
			   this->labelLinkArea->Size = System::Drawing::Size(36, 20);
			   this->labelLinkArea->TabIndex = 20;
			   this->labelLinkArea->Text = L" ";
			   this->labelLinkArea->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label5
			   // 
			   this->label5->Location = System::Drawing::Point(6, 266);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(64, 17);
			   this->label5->TabIndex = 9;
			   this->label5->Text = L"Area";
			   this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			   // 
			   // textBoxLinkID
			   // 
			   this->textBoxLinkID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->textBoxLinkID->Location = System::Drawing::Point(9, 84);
			   this->textBoxLinkID->Name = L"textBoxLinkID";
			   this->textBoxLinkID->Size = System::Drawing::Size(113, 22);
			   this->textBoxLinkID->TabIndex = 15;
			   this->textBoxLinkID->Text = L" - - - ";
			   this->textBoxLinkID->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LinkEditor::textBoxLinkID_KeyDown);
			   this->textBoxLinkID->Leave += gcnew System::EventHandler(this, &LinkEditor::textBoxLinkID_Leave);
			   // 
			   // comboBoxGrid
			   // 
			   this->comboBoxGrid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->comboBoxGrid->FormattingEnabled = true;
			   this->comboBoxGrid->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				   L"No Grid", L"Ortho Grid", L"Polar on Pin 1",
					   L"Polar on Pin 2"
			   });
			   this->comboBoxGrid->Location = System::Drawing::Point(439, 12);
			   this->comboBoxGrid->MaxDropDownItems = 3;
			   this->comboBoxGrid->Name = L"comboBoxGrid";
			   this->comboBoxGrid->Size = System::Drawing::Size(88, 17);
			   this->comboBoxGrid->TabIndex = 21;
			   this->comboBoxGrid->SelectedIndexChanged += gcnew System::EventHandler(this, &LinkEditor::comboBoxGrid_SelectedIndexChanged);
			   // 
			   // LinkEditor
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(192)));
			   this->ClientSize = System::Drawing::Size(797, 468);
			   this->Controls->Add(this->comboBoxGrid);
			   this->Controls->Add(this->labelLinkArea);
			   this->Controls->Add(this->buttonInsertPoint);
			   this->Controls->Add(this->buttonRemovePoint);
			   this->Controls->Add(this->labelCurrEditPoint);
			   this->Controls->Add(this->labelEditPoints);
			   this->Controls->Add(this->textEditPoints);
			   this->Controls->Add(this->textGlobal2);
			   this->Controls->Add(this->textGlobal1);
			   this->Controls->Add(this->textLocal2);
			   this->Controls->Add(this->textBoxLinkID);
			   this->Controls->Add(this->textLocal1);
			   this->Controls->Add(this->textThickness);
			   this->Controls->Add(this->radioButtonGlobalCoords);
			   this->Controls->Add(this->radioButtonLocalCoords);
			   this->Controls->Add(this->textBoxLineWidth);
			   this->Controls->Add(this->label8);
			   this->Controls->Add(this->buttonHelp);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->coordLabel);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->label11);
			   this->Controls->Add(this->labelLinkColor);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label9);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->hScrollBarEditPoints);
			   this->Controls->Add(this->hScrollBarLineWidth);
			   this->Controls->Add(this->checkBoxCentering);
			   this->Controls->Add(this->checkBoxAxes);
			   this->Controls->Add(this->checkBoxCentroid);
			   this->Controls->Add(this->buttonResetView);
			   this->Controls->Add(this->feedbackLabel);
			   this->Controls->Add(this->buttonSave);
			   this->Controls->Add(this->buttonLoad);
			   this->Controls->Add(this->mainPanel);
			   this->Controls->Add(this->label1);
			   this->DoubleBuffered = true;
			   this->Name = L"LinkEditor";
			   this->Text = L"LinkEditor";
			   this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &LinkEditor::LinkEditor_MouseWheel);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion
	private: System::Void buttonLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		//feedbackLabel->Text = "Cannot load now";
		IO::Stream^ myStream; // needed to capture the results
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = ".";  // current folder
		openFileDialog1->Filter = "Link files (*.link)|*.link|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 1;  // will show only txt files, but user can choose to show all files
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
					//// create object as in PS02 tester
					//if (theLink != nullptr)
					//	delete theLink;
					//theLink = new Link();

					// cannot delete since I need to keep reference from simulator
					if (theLink == nullptr) // should never be true
						theLink = new Link();

					// overwrite link data
					theLink->readFile(inFile);
					theShape = theLink->getShape();

					// close file
					inFile.close();

					// perform other action(s)
					resetView();
					//resetInterfaceValues();
					//mainPanel->Refresh();

					feedbackLabel->Text = openFileDialog1->FileName + " has been loaded.";
				}
				else
					feedbackLabel->Text = "Could not open " + openFileDialog1->FileName;

			}
		}
	}

	private: void resetInterfaceValues() {
		if (theLink != nullptr) {
			showPinCoords(textLocal1);
			showPinCoords(textLocal2);
			showPinCoords(textGlobal1);
			showPinCoords(textGlobal2);
			showLinkColor();
			showLinkThickness();
			showLinkArea();
			showLinkID();
		}
	}

	private: void showLinkID() {
		if (theLink != nullptr)
			textBoxLinkID->Text = gcnew String(theLink->getID().c_str());
		else
			labelLinkArea->Text = prevFeedback;
	}
	public: void resetLoopBreaker() {
		loopBreaker = !loopBreaker;
	}

	private: void showLinkArea() {
		if (theLink != nullptr)
			labelLinkArea->Text = theLink->getArea().ToString("0.###");
		else
			labelLinkArea->Text = "0.0";
	}
	private: void drawCentroidAxes(Graphics^ g) {
		if (checkBoxCentroid->Checked && radioButtonLocalCoords->Checked) {
			float shapeLineWidth = hScrollBarLineWidth->Value;
			Pen^ axesPen = gcnew Pen(Color::LightGray, shapeLineWidth / lineWidthScale / 3.);
			cli::array<float>^ dashCode = gcnew cli::array<float>(4)
			{
				5. / zoomLevel, 2. / zoomLevel, 10. / zoomLevel, 2. / zoomLevel
			};
			axesPen->DashPattern = dashCode;

			g->DrawLine(axesPen, theShape->centroid().X, theShape->centroid().Y,
				theShape->centroid().X, theShape->upperBoundingBox().Y);
			g->DrawLine(axesPen, theShape->centroid().X, theShape->centroid().Y,
				theShape->centroid().X, theShape->lowerBoundingBox().Y);
			g->DrawLine(axesPen, theShape->centroid().X, theShape->centroid().Y,
				theShape->upperBoundingBox().X, theShape->centroid().Y);
			g->DrawLine(axesPen, theShape->centroid().X, theShape->centroid().Y,
				theShape->lowerBoundingBox().X, theShape->centroid().Y);
		}
	}

	private: void drawCoordinateAxes(Graphics^ g) {
		if (checkBoxAxes->Checked) {
			float axesLength;
			float shapeLineWidth = hScrollBarLineWidth->Value / lineWidthScale;

			if (theLink != nullptr && theShape != nullptr) {
				if (radioButtonLocalCoords->Checked)
					axesLength = max(theShape->upperBoundingBox().X - theShape->lowerBoundingBox().X,
						theShape->upperBoundingBox().Y - theShape->lowerBoundingBox().Y) / 2.;
				else {
					Point2D pin1 = theLink->getPin(1, false);
					Point2D pin2 = theLink->getPin(2, false);
					if (pin1.X > -INFINITY && pin2.X > -INFINITY)
						axesLength = Line2D::getLength(pin1, pin2) * 0.5;
					else
						axesLength = 50;
				}
			}
			else {
				axesLength = 50;
			}

			Pen^ xPen = gcnew Pen(Color::Red, shapeLineWidth / 5.);
			Pen^ yPen = gcnew Pen(Color::Green, shapeLineWidth / 5.);
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

	private: System::Void mainPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;

		g->TranslateTransform(panX, panY);
		g->ScaleTransform(zoomLevel, -zoomLevel);

		changeEditPoint();
		resetInterfaceValues();

		if (comboBoxGrid->SelectedIndex == 1)
			drawOrthoGrid(g);
		else if (comboBoxGrid->SelectedIndex == 2)
			drawPolarGrid(g, 1);
		else if (comboBoxGrid->SelectedIndex == 3)
			drawPolarGrid(g, 2);

		hScrollBarEditPoints->Value = 50;

		float shapeLineWidth = hScrollBarLineWidth->Value / lineWidthScale;
		// the factor is just a guess

		bool useLocal = radioButtonLocalCoords->Checked;
		if (theLink != nullptr) {
			theLink->paint(g, useLocal, shapeLineWidth); // this may further transform g
			drawCentroidAxes(g);
		}

		drawCoordinateAxes(g);
		drawScale(g);
		if (theSimulator != nullptr && !loopBreaker) {
			theSimulator->Refresh();

		}
	}

	private: float getScaleSizeX() {
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
	private: void drawScale(Graphics^ g) {
		if (theLink != nullptr) {
			// convert from screen size and location I want it to appear to
			// corresponding world coords
			Point2D topCorner = getWorldCoords(10, 10);
			Point2D botCorner = getWorldCoords(90, 20);
			float sizeY = (topCorner.Y - botCorner.Y);
			float sizeX = getScaleSizeX();

			// draw the scale box
			Brush^ fillBrush = gcnew SolidBrush(theLink->getColor());
			g->FillRectangle(fillBrush, topCorner.X, botCorner.Y, sizeX, sizeY);

			// draw the number
			float locX = topCorner.X + sizeX, locY = botCorner.Y;
			g->TranslateTransform(locX, locY);
			g->ScaleTransform(1, -1);
			sizeY = max(1e-8, sizeY);  // sizeY cannot be zero

			System::Drawing::Font^ scaleFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif",
				sizeY, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0));
			g->DrawString(sizeX.ToString(), scaleFont, fillBrush, 0., 0.);
			g->ScaleTransform(1, 1);
			g->TranslateTransform(-locX, -locY);
		}
	}
	private: void drawOrthoGrid(Graphics^ g) {
		Pen^ gridPen = gcnew Pen(colorFromHSV(240, 0.2, 1.0), 0.);
		float spacing = getScaleSizeX();
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
	private: void drawPolarGrid(Graphics^ g, int pinNumberForCenter) {
		Pen^ gridPen = gcnew Pen(colorFromHSV(240, 0.2, 1.0), 0.);

		// change center to whatever pin of link
		Point2D transPoint = theLink->getPin(pinNumberForCenter, radioButtonLocalCoords->Checked);
		if (transPoint.X > -INFINITY && transPoint.Y > -INFINITY)
			g->TranslateTransform(transPoint.X, transPoint.Y);

		// draw circles
		int numbCircles = 30.; // change as needed
		float circleSpacing = getScaleSizeX() * 0.5;
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

		if (transPoint.X > -INFINITY && transPoint.Y > -INFINITY)
			g->TranslateTransform(-transPoint.X, -transPoint.Y);

	}

	protected: void resetView() {
		// sets the pan and zoom so that shape appears perfectly
		if (theShape != nullptr && theShape->area() > 0.) {
			float borderSpaceRatio = 0.95;
			bool centerOnCentroid = checkBoxCentering->Checked;
			float shapeHeight, shapeWidth;
			Point2D pin1C = theLink->getPin(1, false);
			Point2D pin2C = theLink->getPin(2, false);

			if (radioButtonGlobalCoords->Checked) {  // simple for now
				shapeWidth = fabs(pin1C.X - pin2C.X) / borderSpaceRatio;
				shapeHeight = fabs(pin1C.Y - pin2C.Y) / borderSpaceRatio;
			}
			else if (centerOnCentroid) {
				shapeHeight = 2. * max(theShape->centroid().Y - theShape->lowerBoundingBox().Y,
					theShape->upperBoundingBox().Y - theShape->centroid().Y);
				shapeWidth = 2. * max(theShape->centroid().X - theShape->lowerBoundingBox().X,
					theShape->upperBoundingBox().X - theShape->centroid().X);
			}
			else {
				shapeHeight = theShape->upperBoundingBox().Y - theShape->lowerBoundingBox().Y;
				shapeWidth = theShape->upperBoundingBox().X - theShape->lowerBoundingBox().X;
			}

			// provide a bit of a buffer around shape
			//shapeHeight *= borderSpaceRatio; shapeWidth *= borderSpaceRatio;

			float heightRatio = mainPanel->Height / shapeHeight;
			float widthRatio = mainPanel->Width / shapeWidth;

			zoomLevel = min(heightRatio, widthRatio) * borderSpaceRatio;

			panY = mainPanel->Height / 2;
			panX = mainPanel->Width / 2;
			if (radioButtonGlobalCoords->Checked) {
				panX += -(pin1C.X + pin2C.X) / 2. * zoomLevel;
				panY += (pin1C.Y + pin2C.Y) / 2. * zoomLevel;
				// note that panY adjustment is not negative because panY is applied before scaling
			}
			else if (centerOnCentroid) {
				panX += -theShape->centroid().X * zoomLevel;

				panY += theShape->centroid().Y * zoomLevel;
				// note that panY adjustment is not negative because panY is applied before scaling
			}
			else {
				panX += -(theShape->upperBoundingBox().X + theShape->lowerBoundingBox().X)
					/ 2. * zoomLevel;
				panY += (theShape->upperBoundingBox().Y + theShape->lowerBoundingBox().Y)
					/ 2. * zoomLevel;
				// note that panY adjustment is not negative because panY is applied before scaling
			}
			mainPanel->Refresh();
			feedbackLabel->Text = "View has been reset.";
		}
		else {
			feedbackLabel->Text = "Cannot reset view: ";
			if (theShape == nullptr)
				feedbackLabel->Text += "No shape loaded.";
			else
				feedbackLabel->Text += "Loaded shape has self-intersection.";
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

	private: void LinkEditor_MouseWheel(Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
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
		// the second if is part of displaying coordinates on the screen
		if (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::None) {
			showCoords(e);
			if (editPointModeIsOn && theLink != nullptr && theLink->getShape() != nullptr) {
				Point2D model = getWorldCoords(e->X, e->Y);

				if (radioButtonGlobalCoords->Checked)
					model = getLocalFromWorld(model);

				int possiblePoint = theLink->getShape()->indexOfNearestPoint(model);
				if (possiblePoint != -1) {
					feedbackLabel->Text = " Editing Point " + possiblePoint + " at ("
						+ model.X.ToString("0.#####") + ", " + model.Y.ToString("0.#####") + ")";
					currPointIndex = possiblePoint;
					mainPanel->Refresh();

				}
			}
			currLinkPin = checkPinDetection(e->X, e->Y);
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
		// the second if is part of displaying coordinates on the screen or moving points
		else if (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::None) {
			if (editPointModeIsOn) {
				Point2D newPointCoords = getWorldCoords(e->X, e->Y);
				if (this->Cursor == Cursors::Hand) {    // time to move a point (not great condition check)
					if (radioButtonGlobalCoords->Checked)
						newPointCoords = getLocalFromWorld(newPointCoords);
					theLink->getShape()->movePoint(newPointCoords, currPointIndex);
					mainPanel->Refresh();
				}
				else if (this->Cursor == Cursors::SizeAll) {    // time to move a pin (not great condition check)
					//int pinToMove = checkPinDetection(e->X, e->Y);
					if (currLinkPin != -1) {  // should never be false, but just to be sure
						theLink->setPin(currLinkPin, radioButtonLocalCoords->Checked, newPointCoords);
						//resetInterfaceValues(); // now done in Refresh
						mainPanel->Refresh();
					}
				}
			}
			else
				showCoords(e);
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::None) {
			if (theLink != nullptr && theLink->getShape() != nullptr) {
				if (editPointModeIsOn) {
					Point2D model = getWorldCoords(e->X, e->Y);
					if (radioButtonGlobalCoords->Checked)
						model = getLocalFromWorld(model);

					int possiblePoint = theLink->getShape()->indexOfNearestPoint(model);
					if (possiblePoint != -1) {
						feedbackLabel->Text = " Edit Point " + possiblePoint + " at ("
							+ model.X.ToString("0.#####") + ", " + model.Y.ToString("0.#####") + ")";
						this->Cursor = Cursors::Hand;
					}
					else if (checkPinDetection(e->X, e->Y) != -1)
						this->Cursor = Cursors::SizeAll;
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

		if (radioButtonGlobalCoords->Checked) {
			Point2D local = getLocalFromWorld(model);
			feedbackLabel->Text += ", local (" + local.X.ToString("0.###") + ", "
				+ local.Y.ToString("0.###") + ")";
		}
	}

	private: System::Void buttonResetView_Click(System::Object^ sender, System::EventArgs^ e) {
		resetView();
	}

	private: System::Void checkBoxCentroid_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
		if (checkBoxCentroid->Checked)
			feedbackLabel->Text = "Turned on Centroid Axes";
		else
			feedbackLabel->Text = "Turned off Centroid Axes";
	}
	private: System::Void checkBoxAxes_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
		if (checkBoxAxes->Checked)
			feedbackLabel->Text = "Turned on Geometric Axes";
		else
			feedbackLabel->Text = "Turned off Geometric Axes";
	}

	private: System::Void hScrollBarLineWidth_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		mainPanel->Refresh();
		textBoxLineWidth->Text = (hScrollBarLineWidth->Value / lineWidthScale).ToString();
		feedbackLabel->Text = "Changed Line thickness to " + hScrollBarLineWidth->Value / lineWidthScale;
	}

	private: System::Void labelLinkColor_Click(System::Object^ sender, System::EventArgs^ e) {
		ColorDialog^ color01 = gcnew ColorDialog;
		if (color01->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			labelLinkColor->BackColor = color01->Color;
			theLink->setColor(color01->Color);
			mainPanel->Refresh();
			feedbackLabel->Text = "Changed color of link to " + color01->Color;
		}
	}
	private: System::Void labelLinkColor_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		prevFeedback = feedbackLabel->Text;
		feedbackLabel->Text = "Click on color box to change link color.";
	}
	private: System::Void labelLinkColor_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		feedbackLabel->Text = prevFeedback;
	}

	private: System::Void buttonLoad_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		prevFeedback = feedbackLabel->Text;
		feedbackLabel->Text = "Opens file dialog so that user can select a link data file to edit.";
	}
	private: System::Void buttonLoad_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		feedbackLabel->Text = prevFeedback;
	}

	private: System::Void buttonSave_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		prevFeedback = feedbackLabel->Text;
		if (theLink == nullptr)
			feedbackLabel->Text = "Would open save dialog, but no link data has been defined.";
		else
			feedbackLabel->Text = "Opens save dialog so that user can save the link data.";
	}
	private: System::Void buttonSave_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		feedbackLabel->Text = prevFeedback;
	}

	private: System::Void buttonResetView_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		prevFeedback = feedbackLabel->Text;
		feedbackLabel->Text = "Resets zoom and pan so that full link is displayed, centered on centroid or middle";
	}
	private: System::Void buttonResetView_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		feedbackLabel->Text = prevFeedback;
	}

	private: System::Void hScrollBarLineWidth_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		prevFeedback = feedbackLabel->Text;
		feedbackLabel->Text = "Slide scrollbar to change the line width";
	}
	private: System::Void hScrollBarLineWidth_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		feedbackLabel->Text = prevFeedback;
	}

	private: System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ helpText = "Hover over buttons for help on each.\n\n"
			+ "Left click on panel for coordinate feedback.\n\n"
			+ "Shift+Left button drag (or Middle button drag) for panning.\n\n"
			+ "Touchpad pinch (or Mousewheel roll) for zooming about cursor position.\n\n"
			+ "Use EditPoints button to change geometry points and pin locations.\n"
			+ "   Can use textboxes or drag with mouse.\n"
			+ "   Pin movement is dependent on local or global coordinates.\n\n";
		MessageBox::Show(this, helpText, "Help", MessageBoxButtons::OK, MessageBoxIcon::Question);
	}

	private: void getLineWidthFromBox() {

		try {
			float shapeLineWidth;
			if (textBoxLineWidth->Text == "")
				shapeLineWidth = 0.;
			else
				shapeLineWidth = Convert::ToDouble(textBoxLineWidth->Text);

			hScrollBarLineWidth->Value = shapeLineWidth * lineWidthScale;

			mainPanel->Refresh();
		}
		catch (System::ArgumentOutOfRangeException ^ excep) {
		}
		catch (Exception ^ excep) {
			// most likely exception: System::FormatException^
			MessageBox::Show(this, "Value -> " + textBoxLineWidth->Text
				+ " <- in line width input could not be converted to number.\n\n"
				+ excep->Message, "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			textBoxLineWidth->Text = (hScrollBarLineWidth->Value / lineWidthScale).ToString();
		}
	}

	private: System::Void textBoxLineWidth_Leave(System::Object^ sender, System::EventArgs^ e) {
		getLineWidthFromBox();
	}

	private: System::Void textBoxLineWidth_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getLineWidthFromBox();
			e->SuppressKeyPress = true;
		}
	}

	private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theLink == nullptr)
			feedbackLabel->Text = "There is no link to save.";

		else {
			IO::Stream^ myStream;
			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;

			saveFileDialog1->InitialDirectory = ".";  // current folder
			saveFileDialog1->Filter = "Link files (*.link)|*.link|All files (*.*)|*.*";
			saveFileDialog1->FilterIndex = 1;  // will show only link files, but user can choose to show all files
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
						outFile << *theLink;
						feedbackLabel->Text = saveFileDialog1->FileName + " has been saved.";
						outFile.close();
					}
					else
						feedbackLabel->Text = "Could not open " + saveFileDialog1->FileName + " for writing";
				}
			}
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
	private: Point2D getLocalFromWorld(Point2D worldCoords) {
		// more natural and useful to have this as part of Link class
		if (theLink != nullptr)
			return theLink->getLocalFromCurr(worldCoords);
		else
			return { -INFINITY, -INFINITY };
	}

	private: System::Void labelEditPoints_Click(System::Object^ sender, System::EventArgs^ e) {
		if (editPointModeIsOn) { // turn it off
			feedbackLabel->Text = "Point edit mode has been turned off";
			labelEditPoints->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			labelEditPoints->BackColor = Color::Lime;
			labelCurrEditPoint->Text = "---";
			if (theLink != nullptr && theLink->getShape() != nullptr)
				theLink->getShape()->setHighlight(-1);
			editPointModeIsOn = false;
			textEditPoints->Enabled = false;
			buttonInsertPoint->Enabled = false;
			buttonRemovePoint->Enabled = false;
			mainPanel->Refresh();
		}
		else if (theLink != nullptr && theLink->getShape() != nullptr) {
			editPointModeIsOn = true;
			textEditPoints->Enabled = true;
			buttonInsertPoint->Enabled = true;
			buttonRemovePoint->Enabled = true;

			feedbackLabel->Text = "Now in point edit mode.";
			if (theLink != nullptr && theLink->getShape() != nullptr) {
				currPointIndex = min(currPointIndex, theLink->getShape()->getPointCount());
				theLink->getShape()->setHighlight(currPointIndex);
			}
			else
				currPointIndex = 1;

			labelEditPoints->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			labelEditPoints->BackColor = Color::Red;
			mainPanel->Refresh();;
		}
		else
			feedbackLabel->Text = "There are no points to edit.";

		//editPointModeIsOn = !editPointModeIsOn;
	}
	private: System::Void textBox_Leave(System::Object^ sender, System::EventArgs^ e) {
		getPinCoordsFromBox((TextBox^)sender);
	}

	private: System::Void textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getPinCoordsFromBox((TextBox^)sender);
			e->SuppressKeyPress = true;
		}
	}

	private: void showLinkColor() {
		if (theLink != nullptr) {
			labelLinkColor->BackColor = theLink->getColor();
		}
	}
	private: void showLinkThickness() {
		if (theLink != nullptr) {
			float thickness = theLink->getThickness();
			if (thickness > -INFINITY)
				textThickness->Text = thickness.ToString("0.###");
			else
				textThickness->Text = "";
		}

	}
	private: void showPinCoords(TextBox^ currBox) {
		if (theLink != nullptr) {
			String^ boxName = currBox->Name;
			int pinNumber;
			bool useLocal = (boxName->IndexOf("Local") != -1);

			if (boxName->IndexOf("1") != -1)
				pinNumber = 1;
			else
				pinNumber = 2;

			Point2D currPoint = theLink->getPin(pinNumber, useLocal);
			if (currPoint.X > -INFINITY && currPoint.Y > -INFINITY) {
				currBox->Text = currPoint.X.ToString("0.###") + ", "
					+ currPoint.Y.ToString("0.###");
			}
			else
				currBox->Text = "x, y";
		}

	}
	private: void getPinCoordsFromBox(TextBox^ currBox) {
		String^ boxName = currBox->Name;
		int pinNumber;
		bool useLocal = (boxName->IndexOf("Local") != -1);

		if (boxName->IndexOf("1") != -1)
			pinNumber = 1;
		else
			pinNumber = 2;

		// alternate code for pinNumber
		//pinNumber = (boxName->IndexOf("1") != -1) ? 1 : 2;

		try {
			float currX, currY;
			if (currBox->Text == "" || currBox->Text == "x, y") {
				currX = 0.; currY = 0.;
			}
			else {
				int commaLoc = currBox->Text->IndexOf(",");
				currX = Convert::ToDouble(currBox->Text->Substring(0, commaLoc));
				currY = Convert::ToDouble(currBox->Text->Substring(commaLoc + 1));
			}
			if (boxName == "textEditPoints") {
				if (!(theLink->getShape()->movePoint({ currX, currY }, currPointIndex))) {
					feedbackLabel->Text = "Could not move point because it would create a self-intersecting shape.";
					// reset the previous coordinates into editPoints text box
					// changeEditPoint(); // moved this to be part of refresh, so don't need it here
				}
			}
			else {
				if (theLink == nullptr)
					theLink = new Link();
				theLink->setPin(pinNumber, useLocal, { currX, currY });
			}
			mainPanel->Refresh();
		}
		catch (Exception ^ excep) {
			MessageBox::Show(this, "Values -> " + currBox->Text
				+ " <- in " + boxName + " could not be converted to a point.\n"
				+ excep->Message, "ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
			currBox->Focus();
		}
	}

	private: System::Void hScrollBarEditPoints_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		if (editPointModeIsOn && theLink != nullptr && theLink->getShape() != nullptr) {
			if (e->NewValue < e->OldValue)
				currPointIndex--;
			else if (e->NewValue > e->OldValue)
				currPointIndex++;

			if (currPointIndex < 1)
				currPointIndex = theLink->getShape()->getPointCount();
			else if (currPointIndex > theLink->getShape()->getPointCount())
				currPointIndex = 1;

			mainPanel->Refresh();
		}

		hScrollBarEditPoints->Value = 50;

	}

	private: void changeEditPoint() {
		if (editPointModeIsOn && theLink != nullptr && theLink->getShape() != nullptr) {
			theLink->getShape()->setHighlight(currPointIndex);
			Point2D currPoint = theLink->getShape()->getPoint(currPointIndex);
			textEditPoints->Text = currPoint.X.ToString("0.###") + ", "
				+ currPoint.Y.ToString("0.###");
		}

		labelCurrEditPoint->Text = "Point " + currPointIndex;
	}
	private: System::Void radioButtonLocalCoords_Click(System::Object^ sender, System::EventArgs^ e) {
		resetView();
		mainPanel->Refresh();
	}
	private: System::Void radioButtonGlobalCoords_Click(System::Object^ sender, System::EventArgs^ e) {
		//editPointModeIsOn = true;

		//labelEditPoints_Click(nullptr, nullptr);
		resetView();
		mainPanel->Refresh();

	}
	private: System::Void textEditPoints_Leave(System::Object^ sender, System::EventArgs^ e) {
		getPinCoordsFromBox(textEditPoints);
	}
	private: System::Void textEditPoints_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getPinCoordsFromBox(textEditPoints);
			e->SuppressKeyPress = true;
		}
	}
	private: System::Void buttonInsertPoint_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theLink != nullptr && theLink->getShape() != nullptr) {
			theLink->getShape()->addPoint(currPointIndex, 0.5);


			mainPanel->Refresh();
		}
	}
	private: System::Void buttonRemovePoint_Click(System::Object^ sender, System::EventArgs^ e) {
		if (theLink != nullptr && theLink->getShape() != nullptr) {
			theLink->getShape()->removePoint(currPointIndex);

			mainPanel->Refresh();
		}
	}

	private: int checkPinDetection(int currX, int currY) {
		int proximity = 10;  // in pixels
		Point2D pin1 = theLink->getPin(1, radioButtonLocalCoords->Checked);
		Point2D pin2 = theLink->getPin(2, radioButtonLocalCoords->Checked);
		if (pin1.X > -INFINITY && pin2.X > -INFINITY) {
			pin1 = getScreenCoords(pin1);
			pin2 = getScreenCoords(pin2);
			if (fabs(pin1.X - currX) < proximity && fabs(pin1.Y - currY) < proximity) {
				this->Cursor = Cursors::SizeAll;
				return 1;
			}
			else if (fabs(pin2.X - currX) < proximity && fabs(pin2.Y - currY) < proximity) {
				this->Cursor = Cursors::SizeAll;
				return 2;
			}
		}

		return -1;

	}
	private: System::Void textBoxLinkID_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			getLinkIDfromBox();
			e->SuppressKeyPress = true;
		}
	}
	private: System::Void textBoxLinkID_Leave(System::Object^ sender, System::EventArgs^ e) {
		getLinkIDfromBox();
	}
	private: void getLinkIDfromBox() {
		if (theLink == nullptr)
			theLink = new Link();
		theLink->setID(StringPlus::convertString(textBoxLinkID->Text));
		mainPanel->Refresh();
	}
	public: void setLink(Link* aLink) {
		theLink = aLink;
		theShape = theLink->getShape();
		resetView();
		mainPanel->Refresh();
	}
	public: void setSimulator(Form^ aForm) {
		theSimulator = aForm;
	}

	private: System::Void comboBoxGrid_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		mainPanel->Refresh();
	}
	};
}
