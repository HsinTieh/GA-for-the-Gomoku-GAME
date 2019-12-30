#pragma once
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"GA.h"
#include "rule.h"
#include "geneticA.h"
#include <msclr\marshal_cppstd.h>
namespace gomokuGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// gomokuForm 的摘要
	#define lineCount 16
	int fisishList[lineCount-1][lineCount-1];
	std::string user = "white";
	bool blackFirst = false;
	struct coordinate
	{
		int x;
		int y;
		/*******************
		  -------------
		  | 0 | 1 | 2 |
		  -------------
		  | 3 | o | 4 |
		  -------------
		  | 5 | 6 | 7 |
		  -------------
		  [x][y][LatticeIndex]=weight
		**********************/
		int weightLattice[8];
	};
	/// </summary>
	public ref class gomokuForm : public System::Windows::Forms::Form
	{

	private: System::Windows::Forms::Label^  positionX;
	public:
	private: System::Windows::Forms::Label^  positionY;
	private: System::Windows::Forms::GroupBox^  GB_cursorPosition;
	private: System::Windows::Forms::RadioButton^  RB_users;
	private: System::Windows::Forms::RadioButton^  RB_PCs;
	private: System::Windows::Forms::RadioButton^  RB_userToPC;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  BT_reset;

			
			
	public:
		Color lineColor;
		Color backgroundColor;
		String^ who;
		String^ mes;
		int win = 0;
		int userChange;//1:black 2:white
	private: System::Windows::Forms::Label^  LB_who;
	public:
		rule* PC;
		GA* ga;
	private: System::ComponentModel::BackgroundWorker^  BW_PCs;
	private: System::Windows::Forms::ListBox^  LB_msg;
	public:
		geneticA* GA_AI;
		gomokuForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			PC = new rule();

		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~gomokuForm()
		{
			srand((unsigned)time(0));
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  PB_checkerboard;
	private: System::Windows::Forms::MenuStrip^  MS_set;

	private: System::Windows::Forms::ToolStripMenuItem^  setCheckerboardToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  checkerboardToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  gomokuToolStripMenuItem;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->PB_checkerboard = (gcnew System::Windows::Forms::PictureBox());
			this->MS_set = (gcnew System::Windows::Forms::MenuStrip());
			this->setCheckerboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->checkerboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gomokuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->positionX = (gcnew System::Windows::Forms::Label());
			this->positionY = (gcnew System::Windows::Forms::Label());
			this->BT_reset = (gcnew System::Windows::Forms::Button());
			this->GB_cursorPosition = (gcnew System::Windows::Forms::GroupBox());
			this->RB_users = (gcnew System::Windows::Forms::RadioButton());
			this->RB_PCs = (gcnew System::Windows::Forms::RadioButton());
			this->RB_userToPC = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->LB_who = (gcnew System::Windows::Forms::Label());
			this->BW_PCs = (gcnew System::ComponentModel::BackgroundWorker());
			this->LB_msg = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_checkerboard))->BeginInit();
			this->MS_set->SuspendLayout();
			this->GB_cursorPosition->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PB_checkerboard
			// 
			this->PB_checkerboard->Cursor = System::Windows::Forms::Cursors::Default;
			this->PB_checkerboard->Location = System::Drawing::Point(271, 41);
			this->PB_checkerboard->Margin = System::Windows::Forms::Padding(2);
			this->PB_checkerboard->Name = L"PB_checkerboard";
			this->PB_checkerboard->Size = System::Drawing::Size(670, 636);
			this->PB_checkerboard->TabIndex = 0;
			this->PB_checkerboard->TabStop = false;
			this->PB_checkerboard->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &gomokuForm::PB_checkerboard_MouseDown);
			this->PB_checkerboard->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &gomokuForm::PB_checkerboard_MouseMove);
			// 
			// MS_set
			// 
			this->MS_set->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->MS_set->ImageScalingSize = System::Drawing::Size(20, 20);
			this->MS_set->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->setCheckerboardToolStripMenuItem });
			this->MS_set->Location = System::Drawing::Point(0, 0);
			this->MS_set->Name = L"MS_set";
			this->MS_set->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->MS_set->Size = System::Drawing::Size(988, 24);
			this->MS_set->TabIndex = 1;
			this->MS_set->Text = L"menuStrip1";
			// 
			// setCheckerboardToolStripMenuItem
			// 
			this->setCheckerboardToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->checkerboardToolStripMenuItem,
					this->gomokuToolStripMenuItem
			});
			this->setCheckerboardToolStripMenuItem->Name = L"setCheckerboardToolStripMenuItem";
			this->setCheckerboardToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->setCheckerboardToolStripMenuItem->Text = L"Set";
			// 
			// checkerboardToolStripMenuItem
			// 
			this->checkerboardToolStripMenuItem->Name = L"checkerboardToolStripMenuItem";
			this->checkerboardToolStripMenuItem->Size = System::Drawing::Size(225, 22);
			this->checkerboardToolStripMenuItem->Text = L"Checkerboard Background";
			this->checkerboardToolStripMenuItem->Click += gcnew System::EventHandler(this, &gomokuForm::checkerboardToolStripMenuItem_Click);
			// 
			// gomokuToolStripMenuItem
			// 
			this->gomokuToolStripMenuItem->Name = L"gomokuToolStripMenuItem";
			this->gomokuToolStripMenuItem->Size = System::Drawing::Size(225, 22);
			this->gomokuToolStripMenuItem->Text = L"Checkerboard Line";
			this->gomokuToolStripMenuItem->Click += gcnew System::EventHandler(this, &gomokuForm::gomokuToolStripMenuItem_Click);
			// 
			// positionX
			// 
			this->positionX->AutoSize = true;
			this->positionX->Location = System::Drawing::Point(13, 25);
			this->positionX->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->positionX->Name = L"positionX";
			this->positionX->Size = System::Drawing::Size(17, 12);
			this->positionX->TabIndex = 2;
			this->positionX->Text = L"X:";
			// 
			// positionY
			// 
			this->positionY->AutoSize = true;
			this->positionY->Location = System::Drawing::Point(13, 55);
			this->positionY->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->positionY->Name = L"positionY";
			this->positionY->Size = System::Drawing::Size(17, 12);
			this->positionY->TabIndex = 3;
			this->positionY->Text = L"Y:";
			// 
			// BT_reset
			// 
			this->BT_reset->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->BT_reset->FlatAppearance->BorderSize = 10;
			this->BT_reset->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->BT_reset->Font = (gcnew System::Drawing::Font(L"標楷體", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->BT_reset->Location = System::Drawing::Point(17, 41);
			this->BT_reset->Margin = System::Windows::Forms::Padding(2);
			this->BT_reset->Name = L"BT_reset";
			this->BT_reset->Size = System::Drawing::Size(56, 26);
			this->BT_reset->TabIndex = 4;
			this->BT_reset->Text = L"重置";
			this->BT_reset->UseVisualStyleBackColor = true;
			this->BT_reset->Click += gcnew System::EventHandler(this, &gomokuForm::BT_reset_Click);
			// 
			// GB_cursorPosition
			// 
			this->GB_cursorPosition->Controls->Add(this->positionX);
			this->GB_cursorPosition->Controls->Add(this->positionY);
			this->GB_cursorPosition->Font = (gcnew System::Drawing::Font(L"標楷體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->GB_cursorPosition->Location = System::Drawing::Point(14, 90);
			this->GB_cursorPosition->Margin = System::Windows::Forms::Padding(2);
			this->GB_cursorPosition->Name = L"GB_cursorPosition";
			this->GB_cursorPosition->Padding = System::Windows::Forms::Padding(2);
			this->GB_cursorPosition->Size = System::Drawing::Size(128, 78);
			this->GB_cursorPosition->TabIndex = 5;
			this->GB_cursorPosition->TabStop = false;
			this->GB_cursorPosition->Text = L"滑鼠在棋盤上的位置";
			// 
			// RB_users
			// 
			this->RB_users->AutoSize = true;
			this->RB_users->Checked = true;
			this->RB_users->Location = System::Drawing::Point(11, 28);
			this->RB_users->Margin = System::Windows::Forms::Padding(2);
			this->RB_users->Name = L"RB_users";
			this->RB_users->Size = System::Drawing::Size(65, 16);
			this->RB_users->TabIndex = 6;
			this->RB_users->TabStop = true;
			this->RB_users->Text = L"Man-Man";
			this->RB_users->UseVisualStyleBackColor = true;
			// 
			// RB_PCs
			// 
			this->RB_PCs->AutoSize = true;
			this->RB_PCs->Location = System::Drawing::Point(11, 57);
			this->RB_PCs->Margin = System::Windows::Forms::Padding(2);
			this->RB_PCs->Name = L"RB_PCs";
			this->RB_PCs->Size = System::Drawing::Size(53, 16);
			this->RB_PCs->TabIndex = 7;
			this->RB_PCs->Text = L"PC-PC";
			this->RB_PCs->UseVisualStyleBackColor = true;
			// 
			// RB_userToPC
			// 
			this->RB_userToPC->AutoSize = true;
			this->RB_userToPC->Location = System::Drawing::Point(11, 86);
			this->RB_userToPC->Margin = System::Windows::Forms::Padding(2);
			this->RB_userToPC->Name = L"RB_userToPC";
			this->RB_userToPC->Size = System::Drawing::Size(59, 16);
			this->RB_userToPC->TabIndex = 8;
			this->RB_userToPC->Text = L"Man-PC";
			this->RB_userToPC->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->RB_userToPC);
			this->groupBox1->Controls->Add(this->RB_users);
			this->groupBox1->Controls->Add(this->RB_PCs);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"標楷體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(17, 203);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(104, 129);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"選擇對戰模式";
			// 
			// LB_who
			// 
			this->LB_who->AutoSize = true;
			this->LB_who->BackColor = System::Drawing::SystemColors::Desktop;
			this->LB_who->Font = (gcnew System::Drawing::Font(L"標楷體", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LB_who->ForeColor = System::Drawing::Color::Snow;
			this->LB_who->Location = System::Drawing::Point(149, 48);
			this->LB_who->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->LB_who->Name = L"LB_who";
			this->LB_who->Size = System::Drawing::Size(93, 19);
			this->LB_who->TabIndex = 10;
			this->LB_who->Text = L"黑子下手";
			// 
			// BW_PCs
			// 
			this->BW_PCs->WorkerReportsProgress = true;
			this->BW_PCs->WorkerSupportsCancellation = true;
			this->BW_PCs->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &gomokuForm::BW_PCs_DoWork);
			this->BW_PCs->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &gomokuForm::BW_PCs_ProgressChanged);
			this->BW_PCs->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &gomokuForm::BW_PCs_RunWorkerCompleted);
			// 
			// LB_msg
			// 
			this->LB_msg->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LB_msg->FormattingEnabled = true;
			this->LB_msg->ItemHeight = 16;
			this->LB_msg->Location = System::Drawing::Point(22, 396);
			this->LB_msg->Name = L"LB_msg";
			this->LB_msg->Size = System::Drawing::Size(164, 164);
			this->LB_msg->TabIndex = 11;
			// 
			// gomokuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 680);
			this->Controls->Add(this->LB_msg);
			this->Controls->Add(this->LB_who);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->GB_cursorPosition);
			this->Controls->Add(this->BT_reset);
			this->Controls->Add(this->PB_checkerboard);
			this->Controls->Add(this->MS_set);
			this->MainMenuStrip = this->MS_set;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"gomokuForm";
			this->Text = L"gomokuForm";
			this->Load += gcnew System::EventHandler(this, &gomokuForm::gomokuForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_checkerboard))->EndInit();
			this->MS_set->ResumeLayout(false);
			this->MS_set->PerformLayout();
			this->GB_cursorPosition->ResumeLayout(false);
			this->GB_cursorPosition->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region draw the checkerground
		/*************
		*  繪製棋盤  *
		**************/
	void drawCheckerBoard(int line, int lineSpace, Color backgroundColor, Color lineColor, PictureBox^ PB)
	{
		Bitmap^ bmp = gcnew Bitmap(PB_checkerboard->Width, PB_checkerboard->Height);
		Graphics^ gra = gra->FromImage(bmp);

		SolidBrush^ brush = gcnew SolidBrush(backgroundColor);
		Pen^ pen = gcnew Pen(lineColor, 1);
		//繪製棋盤
		gra->FillRectangle(brush, 0, 0, (line)*lineSpace, (line)*lineSpace);
		//繪製棋盤線條	
		for (int i = 1; i < line; i++)
		{
			//橫
			Point^ startHorizontal = gcnew Point(1*lineSpace, i*lineSpace);
			Point^ endHorizontal = gcnew Point(startHorizontal->X + (line-2)*lineSpace, i*lineSpace);
			gra->DrawLine(pen, startHorizontal->X, startHorizontal->Y, endHorizontal->X, endHorizontal->Y);
			//直
			Point^ startVertical = gcnew Point(i*lineSpace, 1 * lineSpace);
			Point^ endVertical = gcnew Point(startVertical->X, startVertical->Y + (line-2) * lineSpace);
			gra->DrawLine(pen, startVertical->X, startVertical->Y, endVertical->X, endVertical->Y);
		}

		PB->BackgroundImage = bmp;
		//gra->Dispose();
	}
	/*****  L   O   A    D  **********/
	private: System::Void gomokuForm_Load(System::Object^  sender, System::EventArgs^  e) {

		srand(time(NULL));
		backgroundColor = Color::Gold;
		lineColor = Color::Black;

		PB_checkerboard->Width = 640;
		PB_checkerboard->Height = 640;
		drawCheckerBoard(lineCount, (PB_checkerboard->Width) / lineCount, backgroundColor, lineColor, PB_checkerboard);
		//userChange = rand()%2;
		userChange = 1;
		//清空陣列，這陣列是為了確認哪些地方已經下過了
		for (int i = 0; i < lineCount; i++) 
		{
			for (int j = 0; j < lineCount; j++)
				fisishList[i][j] = 0;
		}
		if (RB_users->Checked || RB_userToPC->Checked)
			who = "user";
		else if (RB_PCs->Checked)
			who = "PC";
		
	}
	private: System::Void checkerboardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		/*修改棋盤背景*/
		ColorDialog  dlg;
		if (dlg.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			backgroundColor =  dlg.Color;
		drawCheckerBoard(lineCount, PB_checkerboard->Width / lineCount, backgroundColor, lineColor, PB_checkerboard);

	}
	private: System::Void gomokuToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		/*修改棋盤線條*/
		ColorDialog  dlg;
		if (dlg.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			lineColor = dlg.Color;
		drawCheckerBoard(lineCount, PB_checkerboard->Width / lineCount, backgroundColor, lineColor, PB_checkerboard);
	}
#pragma endregion
#pragma region draw the chessman

			 /*************
			 *  繪製棋子   *
			 **************/
	void drawGomoku(int x, int y, int lineSpace, Color chessColor, PictureBox^ PB)
	{
		
		Graphics^ gra = PB->CreateGraphics();

		SolidBrush^ brush = gcnew SolidBrush(chessColor);
		Pen^ pen = gcnew Pen(chessColor, 1);
		int indexX;
		int indexY;
		
		if (who == "user")
		{
			if ((x%lineSpace) < (lineSpace / 2))
				x -= (x%lineSpace);
			else
				x += (x%lineSpace);

			if ((y%lineSpace) < (lineSpace / 2))
				y -= (y%lineSpace);
			else
				y += (y%lineSpace);
			indexX = (x / lineSpace);
			indexY = (y / lineSpace);
			mes = "black" + "  (" + (indexX-1) + "," + (indexY-1) + ") 人";
			LB_msg->Items->Add(mes);
		}
		else if(who == "PC")
		{
			//初始位置為(1,1)->(x,y)=(0,0) ,in fact(1,1)
			indexX = x+1;
			indexY = y+1;
		}
		/*防止重複下到同樣的位置*/

		if (!fisishList[indexX - 1][indexY - 1])
		{
			gra->DrawEllipse(pen, indexX*lineSpace - (lineSpace / 2), indexY*lineSpace - (lineSpace / 2), lineSpace - 2, lineSpace - 2);
			gra->FillEllipse(brush, indexX*lineSpace - (lineSpace / 2), indexY*lineSpace - (lineSpace / 2), lineSpace - 2, lineSpace - 2);
			if (chessColor == Color::Black)
				fisishList[indexX - 1][indexY - 1] = 1;
			else if (chessColor == Color::White)
				fisishList[indexX - 1][indexY - 1] = 2;
		}
	}
	int whowin()
	{
		rule* rule_ = new rule();
		int count[8];
		bool whiteWin = false;
		bool blackWin = false;

	
		for (int i = 0; i < gomokuline; i++)
		{
			for (int j = 0; j < gomokuline; j++)
			{
				//if (fisishList[i][j] != 0)
				//{
					//init
					for(int r=0;r<8;r++)
						count[r] = 1;

					if (fisishList[i][j] == 1)
					{
						
						//black 向四處找相同的棋子
						for (int k = 1; k < 5; k++)
						{
							
							if (fisishList[rule_->calculationPositionX(i, 0, k)][rule_->calculationPositionY(j, 0, k)] == 1)
							{
								//過濾邊界
								if ((rule_->calculationPositionX(i, 0, k) == i && rule_->calculationPositionY(j, 0, k) == j))
									break;
								count[0]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							if (fisishList[rule_->calculationPositionX(i, 7, k)][rule_->calculationPositionY(j, 7, k)] == 1)
							{
								//過濾邊界
								if (rule_->calculationPositionX(i, 7, k) == i && rule_->calculationPositionY(j, 7, k) == j)
									break;
								count[7]++; 
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							//|
							if (fisishList[rule_->calculationPositionX(i, 1, k)][rule_->calculationPositionY(j, 1, k)] == 1 )
								
							{
								if (rule_->calculationPositionX(i, 1, k) == i && rule_->calculationPositionY(j, 1, k) == j) 
									break;
								//printf("!!!!!!(%d,%d) %d\n", rule_->calculationPositionX(i, 1, k), rule_->calculationPositionY(i, 1, k), fisishList[rule_->calculationPositionX(i, 1, k)][rule_->calculationPositionY(j, 1, k)]);
								//printf("22222(%d,%d) %d\n", rule_->calculationPositionX(i, 6, k), rule_->calculationPositionY(i, 6, k), fisishList[rule_->calculationPositionX(i, 6, k)][rule_->calculationPositionY(j, 6, k)]);

								count[1]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							//|
							if(fisishList[rule_->calculationPositionX(i, 6, k)][rule_->calculationPositionY(j, 6, k)] == 1)
							{
								if (rule_->calculationPositionX(i, 6, k) == i && rule_->calculationPositionY(j, 6, k) == j)
									break;
								count[6]++;
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							// /
							if (fisishList[rule_->calculationPositionX(i, 2, k)][rule_->calculationPositionY(j, 2, k)] == 1)
								
							{
								if (rule_->calculationPositionX(i, 2, k) == i && rule_->calculationPositionY(j, 2, k) == j) 
									break;
								count[2]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							// /
							if (fisishList[rule_->calculationPositionX(i, 5, k)][rule_->calculationPositionY(j, 5, k)] == 1)
							{
								if(rule_->calculationPositionX(i, 5, k) == i && rule_->calculationPositionY(j, 5, k) == j)
									break;
								count[5]++;
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							// 一
							if (fisishList[rule_->calculationPositionX(i, 3, k)][rule_->calculationPositionY(j, 3, k)] == 1)
							{
								if (rule_->calculationPositionX(i, 3, k) == i && rule_->calculationPositionY(j, 3, k) == j)	
									break;
								count[3]++;
							}
							else
								break;
							//printf("(%d,%d)=%d", rule_->calculationPositionX(i, 3, k), rule_->calculationPositionY(j, 3, k), fisishList[rule_->calculationPositionX(i, 3, k)][rule_->calculationPositionY(j, 3, k)]);

						}
						for (int k = 1; k < 5; k++)
						{
							// 一
							if (fisishList[rule_->calculationPositionX(i, 4, k)][rule_->calculationPositionY(j, 4, k)] == 1)
							{
								if (rule_->calculationPositionX(i, 4, k) == i && rule_->calculationPositionY(j, 4, k) == j)
									break;
								count[4]++;
							}
							else
								break;
							//printf("(%d,%d)=%d", rule_->calculationPositionX(i, 3, k), rule_->calculationPositionY(j, 3, k), fisishList[rule_->calculationPositionX(i, 3, k)][rule_->calculationPositionY(j, 3, k)]);

						}
						for (int k = 0; k <= sizeof(count) / sizeof(count[0])/2; k++)
						{
						//printf("B %d  ", count[k]);
							//五連
							if (count[k]+count[sizeof(count) / sizeof(count[0])-1-k] == 6)
								blackWin = true;
							
						}
					//printf("\n");
					}
					else if (fisishList[i][j] == 2)
					{
						//white 向四處找相同的棋子
						for (int k = 1; k < 5; k++)
						{

							if (fisishList[rule_->calculationPositionX(i, 0, k)][rule_->calculationPositionY(j, 0, k)] == 2)
							{
								//過濾邊界
								if ((rule_->calculationPositionX(i, 0, k) == i && rule_->calculationPositionY(j, 0, k) == j))
									break;
								count[0]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							if (fisishList[rule_->calculationPositionX(i, 7, k)][rule_->calculationPositionY(j, 7, k)] == 2)
							{
								//過濾邊界
								if (rule_->calculationPositionX(i, 7, k) == i && rule_->calculationPositionY(j, 7, k) == j)
									break;
								count[7]++;
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							//|
							if (fisishList[rule_->calculationPositionX(i, 1, k)][rule_->calculationPositionY(j, 1, k)] == 2)

							{
								if (rule_->calculationPositionX(i, 1, k) == i && rule_->calculationPositionY(j, 1, k) == j)
									break;
								count[1]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							//|
							if (fisishList[rule_->calculationPositionX(i, 6, k)][rule_->calculationPositionY(j, 6, k)] == 2)
							{
								if (rule_->calculationPositionX(i, 6, k) == i && rule_->calculationPositionY(j, 6, k) == j)
									break;
								count[6]++;
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							// /
							if (fisishList[rule_->calculationPositionX(i, 2, k)][rule_->calculationPositionY(j, 2, k)] == 2)

							{
								if (rule_->calculationPositionX(i, 2, k) == i && rule_->calculationPositionY(j, 2, k) == j)
									break;
								count[2]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							// /
							if (fisishList[rule_->calculationPositionX(i, 5, k)][rule_->calculationPositionY(j, 5, k)] == 2)
							{
								if (rule_->calculationPositionX(i, 5, k) == i && rule_->calculationPositionY(j, 5, k) == j)
									break;
								count[5]++;
							}
							else
								break;
						}

						for (int k = 1; k < 5; k++)
						{
							// 一
							if (fisishList[rule_->calculationPositionX(i, 3, k)][rule_->calculationPositionY(j, 3, k)] == 2)
							{
								if (rule_->calculationPositionX(i, 3, k) == i && rule_->calculationPositionY(j, 3, k) == j)
									break;
								count[3]++;
							}
							else
								break;
						}
						for (int k = 1; k < 5; k++)
						{
							// 一
							if (fisishList[rule_->calculationPositionX(i, 4, k)][rule_->calculationPositionY(j, 4, k)] == 2)
							{
								if (rule_->calculationPositionX(i, 4, k) == i && rule_->calculationPositionY(j, 4, k) == j)
									break;
								count[4]++;
							}
							else
								break;
						}
						for (int k = 0; k <= sizeof(count) / sizeof(count[0]) / 2; k++)
						{
							//五連
							if (count[k] + count[sizeof(count) / sizeof(count[0]) - 1 - k] == 6)
								whiteWin = true;

						}
					}
			}
		}
		if (whiteWin)
			return 2;
		else if (blackWin)
			return 1;
		else
			return 0;
		
	}

	private: System::Void PB_checkerboard_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (RB_users->Checked)
		{
			/* 防止落到外面*/
			if (e->X > (PB_checkerboard->Width / lineCount / 2) && e->Y > (PB_checkerboard->Width / lineCount / 2)
				&& e->X < (PB_checkerboard->Width - (PB_checkerboard->Width / lineCount / 2)) && e->Y < (PB_checkerboard->Width - (PB_checkerboard->Width / lineCount / 2)))
			{
				if (userChange == 1)
				{
					userChange = 2;
					drawGomoku(e->X, e->Y, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);
					LB_who->Text = "白子下手";
				}
				else if(userChange == 2)
				{
					userChange = 1;
					drawGomoku(e->X, e->Y, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
					LB_who->Text = "黑子下手";
				}
			}
			PC->calculationNextStep(fisishList, user);
		}
		else if (RB_userToPC->Checked)
		{
			//if (!blackFirst)
			//{
			//	who = "PC";
			//	drawGomoku(7, 7, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);
			//	blackFirst = true;
			//}
			/* 防止落到外面*/
			if (e->X > (PB_checkerboard->Width / lineCount / 2) && e->Y > (PB_checkerboard->Width / lineCount / 2)
				&& e->X < (PB_checkerboard->Width - (PB_checkerboard->Width / lineCount / 2)) && e->Y < (PB_checkerboard->Width - (PB_checkerboard->Width / lineCount / 2)))
			{
				who = "user";
				drawGomoku(e->X, e->Y, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);

			}
			LB_who->Text = "白子下手";
			//PC->calculationNextStep(fisishList, user);
			//int bestX, bestY;
			/*bestX = PC->bestX;
			bestY = PC->bestY;
			printf("(%d , %d)\n", bestX, bestY);
			who = "PC";
			drawGomoku(bestX, bestY, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
			*/
			int win = whowin();
			messageWin(win, 0);//win mode:1->backgroundworker
			if (win == 0)
			{
				who = "PC";
				point_ p = start("white");
				
				drawGomoku(p.x, p.y, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
				mes = msclr::interop::marshal_as<String^>(user) + "  (" + p.x + "," + p.y + ") G";
				LB_msg->Items->Add(mes);
				int win_ = whowin();
				messageWin(win_, 0);
			}
			LB_who->Text = "黑子下手";
		}
		else if (RB_PCs->Checked)
		{
			
			if (!BW_PCs->IsBusy)
			{
				BW_PCs->RunWorkerAsync();
			}
		}
		//判斷誰贏的
		//int win = whowin();
		//messageWin(win,0);//win mode:1->backgroundworker

	}
	point_ start(std::string user)
	{
		GA_AI = new geneticA(fisishList, user,5, 7, 0.1, 200, 300, 0.1,10);//ok
		point_ move;
		move = GA_AI->get_action(user);

		coordinate_ checkP;
		printf("%s\n", user.c_str());
		int val=0;
		std::vector<std::vector<int>> canForecastingPosition;
		canForecastingPosition = PC->findNeedCalculationCoordinate(fisishList);
		
		for (int i = 0; i < gomokuline; i++)
		{
			if (val != 0)
				break;
			for (int j = 0; j < gomokuline; j++)
			{

				if (canForecastingPosition[i][j] == 0)
				{

					checkP = PC->calculationChessCount(i, j, fisishList, (user == "white" ? "black" : "white"));

					val = PC->getLongLink(checkP, (user == "white" ? "black" : "white"), fisishList);
					//printf("(x,y) (%d,%d) ", i, j);
					if (val == longLink)
					{
						//printf("!!!(x,y) (%d,%d) ", i, j);;
						move.x = checkP.x;
						move.y = checkP.y;
						
						break;
					}
				}
			}
		}
		//printf("\n(%d,%d)\n", move.x, move.y);
		return move;
	}
	private: System::Void PB_checkerboard_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		int^ x = e->X;
		int^ y = e->Y;

		positionX->Text = "X: "+ x->ToString();
		positionY->Text = "Y: "+y->ToString();

	}			 
#pragma endregion
	private: System::Void BT_reset_Click(System::Object^  sender, System::EventArgs^  e) {
		if (BW_PCs->IsBusy)
		{
			who = "user";
			BW_PCs->CancelAsync();
		}
		drawCheckerBoard(lineCount, (PB_checkerboard->Width) / lineCount, backgroundColor, lineColor, PB_checkerboard);
		userChange = 1;
		//清空陣列，這陣列是為了確認哪些地方已經下過了
		for (int i = 0; i < lineCount; i++)
		{
			for (int j = 0; j < lineCount; j++)
				fisishList[i][j] = 0;
		}
		blackFirst = false;
		LB_msg->Items->Clear();
	}
	 //啟動GA的function 
	void GAstart() 
	{
		//GO~GO~
		printf("enter");
		ga = new GA(fisishList);//ok
		ga->enter(user,fisishList);
		printf("best fitness :%lf \n", ga->bestGenome.reFitness());
		if (ga->bestGenome.reFitness() > 0)
		{
			point best = ga->bestGenome.genes[0];
			drawGomoku(best.x, best.y, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);
		}
		else
		{
			point best = ga->bestGenome.genes[ga->bestGenome.reBestGenesIndex()];
			drawGomoku(best.x, best.y, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
		}

	}
	std::vector<point> creatGene(int count, int recodeList[][gomokuline])
	{
		std::vector<point> list;
		point p;
		p.x = -1;
		p.y = -1;
		probability pro;
		for (int i = 0; i < count; i++)
		{
			while (true)
			{
				p = pro.CreateRandGene();
				/////// ==? != ?
				if (recodeList[p.x][p.y] == 0 && !(PC->checkChess(p, recodeList)))
				{
					list.push_back(p);
					printf("gene : (%d , %d) \n", p.x, p.y);
					break;
				}
			}
		}
		return list;
	}

	int SinglePower(point p, std::string user) 
	{
		coordinate_ coor = PC->calculationChessCount(p.x, p.y, fisishList, user);
		if (PC->getLongLink(coor, user, fisishList) > 0)
			return (user == "white") ? longLink : longLink*(-1);
		if (PC->getLive4(coor, user) > 0)
			return (user == "white") ? live4 : live4*(-1);
		if (PC->getRush4(coor, user) > 0)
			return (user == "white") ? rush4 : rush4*(-1);
		if (PC->getLive3(coor, user) > 0)
			return (user == "white") ? live3 : live3 *(-1);
		if (PC->getRush3(coor, user) > 0)
			return (user == "white") ? rush3 : rush3 * (-1);
		
		int count = PC->computing2_1(p, user, fisishList);
		
		return (user == "white") ? count : (count * -1);
	}
	private: System::Void BW_PCs_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	
		int win=0;
		int rule = rand() % (2);
		std::string one,two ;
		if (rule == 1) {
			one = "black";
			two = "white";
		}
		else
		{
			one = "white";
			two = "black";
		}
		//畫製第一個位置
		who = "PC";
		
		drawGomoku(7, 7, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);

		mes = "black  (7,7)";
		BW_PCs->ReportProgress(2);
		int a = 0;//沒什麼意義
		while (true) {
			if (this->BW_PCs->CancellationPending)
			{
				break;
			}
			if (one == "black")
			{
				if(a!=0)
					version_based_rule(one);
				version_GA(two);
				a++;
				int win_ = whowin();
				messageWin(win_, 1);
				if (win != 0)
					break;
			}
			else 
			{
				if (a != 0)
					version_GA(two);

				version_based_rule(one);
				a++;
				win = whowin();
				messageWin(win, 1);//win mode:1->backgroundworker
				if (win != 0)
					break;
			}


		}
		

	}


	void version_based_rule(std::string user)
	{
		PC->calculationNextStep(fisishList, user);
		int bestX, bestY;
		bestX = PC->bestX;
		bestY = PC->bestY;
		if(user == "white")
			drawGomoku(bestX, bestY, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
		if (user == "black")
			drawGomoku(bestX, bestY, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);
		mes = msclr::interop::marshal_as<String^>(user)+ "  (" + bestX + "," + bestY + ")";
		BW_PCs->ReportProgress(2);

	}
	void version_GA(std::string user)
	{

		point_ p = start(user);
		if (user == "white")
			drawGomoku(p.x, p.y, PB_checkerboard->Width / lineCount, Color::White, PB_checkerboard);
		if (user == "black")
			drawGomoku(p.x, p.y, PB_checkerboard->Width / lineCount, Color::Black, PB_checkerboard);

		mes = msclr::interop::marshal_as<String^>(user)+"  (" + p.x + "," + p.y + ") G";
		BW_PCs->ReportProgress(2);
	}
	private: System::Void BW_PCs_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

	

	}
			 //messagebox
	void messageWin(int win,int mode)
	{
		if (win == 1)
		{
			//printf("黑棋獲勝");
			if (MessageBox::Show("黑棋已經獲勝了~~~~~~~", "這場遊戲已經結束! \n 是否要進行下一場遊戲呢?", MessageBoxButtons::YesNo)
				== System::Windows::Forms::DialogResult::Yes)
			{
				if(mode == 1)
					BW_PCs->ReportProgress(1);
				else
					this->BT_reset->PerformClick();
			}
			else
			{

			}
		}
		else if (win == 2)
		{
			printf("白棋獲勝");
			if (MessageBox::Show("白棋已經獲勝了~~~~~~~", "這場遊戲已經結束! \n 是否要進行下一場遊戲呢?", MessageBoxButtons::YesNo)
				== System::Windows::Forms::DialogResult::Yes)
			{
				if (mode == 1)
					BW_PCs->ReportProgress(1);
				else
					this->BT_reset->PerformClick();
			}
			else
			{

			}
		}
	}

private: System::Void BW_PCs_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
	if(e->ProgressPercentage == 1)
		this->BT_reset->PerformClick();
	if (e->ProgressPercentage == 2)
		LB_msg->Items->Add(mes);
}
};

	
}
