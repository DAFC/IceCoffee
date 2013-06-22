#pragma once

namespace ReadingText {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// ReadingText の概要
	/// </summary>
	public ref class ReadingTextDialogUI : public System::Windows::Forms::Form
	{
	public:
		ReadingTextDialogUI(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//

			//退避したテキストを読み込む
			try
			{
				StreamReader ^sr=gcnew StreamReader("_RT.txt");
				while (sr->Peek()>-1)
				{
					TextStock->Items->Add(sr->ReadLine());
				}
				sr->Close();
			}
			catch(FileNotFoundException ^ignore)
			{
				//スルー
			}
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~ReadingTextDialogUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  OpenButton;
	private: System::Windows::Forms::Button^  EncodeButton;
	private: System::Windows::Forms::ListBox^  TextStock;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;

	protected: 

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->OpenButton = (gcnew System::Windows::Forms::Button());
			this->EncodeButton = (gcnew System::Windows::Forms::Button());
			this->TextStock = (gcnew System::Windows::Forms::ListBox());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// OpenButton
			// 
			this->OpenButton->Location = System::Drawing::Point(13, 13);
			this->OpenButton->Name = L"OpenButton";
			this->OpenButton->Size = System::Drawing::Size(75, 23);
			this->OpenButton->TabIndex = 0;
			this->OpenButton->Text = L"ファイルを開く";
			this->OpenButton->UseVisualStyleBackColor = true;
			this->OpenButton->Click += gcnew System::EventHandler(this, &ReadingTextDialogUI::OpenButton_Click);
			// 
			// EncodeButton
			// 
			this->EncodeButton->Location = System::Drawing::Point(94, 13);
			this->EncodeButton->Name = L"EncodeButton";
			this->EncodeButton->Size = System::Drawing::Size(75, 23);
			this->EncodeButton->TabIndex = 2;
			this->EncodeButton->Text = L"エンコード";
			this->EncodeButton->UseVisualStyleBackColor = true;
			this->EncodeButton->Click += gcnew System::EventHandler(this, &ReadingTextDialogUI::EncodeButton_Click);
			// 
			// TextStock
			// 
			this->TextStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->TextStock->FormattingEnabled = true;
			this->TextStock->ItemHeight = 12;
			this->TextStock->Location = System::Drawing::Point(13, 43);
			this->TextStock->Name = L"TextStock";
			this->TextStock->Size = System::Drawing::Size(259, 208);
			this->TextStock->TabIndex = 3;
			// 
			// ReadingTextDialogUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->TextStock);
			this->Controls->Add(this->EncodeButton);
			this->Controls->Add(this->OpenButton);
			this->Name = L"ReadingTextDialogUI";
			this->Text = L"ReadingText";
			this->ResumeLayout(false);

		}
#pragma endregion

#pragma region 自作イベント関数
	private:
		//ファイル読み込みボタンのクリックイベント
		System::Void OpenButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if(openFileDialog->ShowDialog()==System::Windows::Forms::DialogResult::OK&&openFileDialog->SafeFileName!="_RT.txt")
			{
				//ファイルの内容を読み込む
				StreamReader ^sr=gcnew StreamReader(openFileDialog->FileName);
				String ^text=sr->ReadToEnd();
				sr->Close();

				//テキスト履歴に追加
				TextStock->Items->Add(text);
				TextStock->SelectedIndex=TextStock->Items->Count-1;

				//テキストを外部ファイルに退避
				StreamWriter ^sw= gcnew StreamWriter("_RT.txt",false);
				for each (Object ^var in TextStock->Items)
				{
					sw->WriteLine(var->ToString());
				}
				sw->Close();
			}
		}
	private:
		//エンコードボタンのクリックイベント
		System::Void EncodeButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			//エンコードする
			//サイコロ配置のダイアログを表示する
		}
#pragma endregion
	};
}
