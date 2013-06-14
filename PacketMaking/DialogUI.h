#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace ReadingText {

	/// <summary>
	/// DialogUI の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class DialogUI : public System::Windows::Forms::Form
	{
	public:
		DialogUI(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~DialogUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  OpenFileButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::ListBox^  TextStock;


	private: System::Windows::Forms::TextBox^  LoadedText;
	private: System::Windows::Forms::Button^  EncodeButton;
	protected: 

	protected: 

	protected: 

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->OpenFileButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->TextStock = (gcnew System::Windows::Forms::ListBox());
			this->LoadedText = (gcnew System::Windows::Forms::TextBox());
			this->EncodeButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// OpenFileButton
			// 
			this->OpenFileButton->Location = System::Drawing::Point(12, 12);
			this->OpenFileButton->Name = L"OpenFileButton";
			this->OpenFileButton->Size = System::Drawing::Size(75, 23);
			this->OpenFileButton->TabIndex = 0;
			this->OpenFileButton->Text = L"ファイルを開く";
			this->OpenFileButton->UseVisualStyleBackColor = true;
			this->OpenFileButton->Click += gcnew System::EventHandler(this, &DialogUI::OpenFileButton_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
			// 
			// TextStock
			// 
			this->TextStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->TextStock->FormattingEnabled = true;
			this->TextStock->ItemHeight = 12;
			this->TextStock->Location = System::Drawing::Point(12, 42);
			this->TextStock->Name = L"TextStock";
			this->TextStock->Size = System::Drawing::Size(260, 172);
			this->TextStock->TabIndex = 2;
			this->TextStock->SelectedValueChanged += gcnew System::EventHandler(this, &DialogUI::TextStock_SelectedValueChanged);
			// 
			// LoadedText
			// 
			this->LoadedText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->LoadedText->Location = System::Drawing::Point(12, 231);
			this->LoadedText->Name = L"LoadedText";
			this->LoadedText->Size = System::Drawing::Size(260, 19);
			this->LoadedText->TabIndex = 3;
			this->LoadedText->TextChanged += gcnew System::EventHandler(this, &DialogUI::LoadedText_TextChanged);
			// 
			// EncodeButton
			// 
			this->EncodeButton->Location = System::Drawing::Point(93, 12);
			this->EncodeButton->Name = L"EncodeButton";
			this->EncodeButton->Size = System::Drawing::Size(75, 23);
			this->EncodeButton->TabIndex = 1;
			this->EncodeButton->Text = L"エンコード";
			this->EncodeButton->UseVisualStyleBackColor = true;
			this->EncodeButton->Click += gcnew System::EventHandler(this, &DialogUI::EncodeButton_Click);
			// 
			// DialogUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->EncodeButton);
			this->Controls->Add(this->LoadedText);
			this->Controls->Add(this->TextStock);
			this->Controls->Add(this->OpenFileButton);
			this->Name = L"DialogUI";
			this->Text = L"IceCoffee PacketMaker";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region 自作イベント関数
	private:
		//ファイル読み込みボタンのクリックイベント
		System::Void OpenFileButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if(openFileDialog->ShowDialog()==System::Windows::Forms::DialogResult::OK)
			{
				StreamReader ^sr=gcnew StreamReader(openFileDialog->FileName);
				String ^text=sr->ReadToEnd();
				LoadedText->Text=text;
				TextStock->Items->Add(text);
				sr->Close();
			}
		}
	private:
		//テキストストック用リストボックスの選択イベント
		System::Void TextStock_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e)
		{
			LoadedText->Text=TextStock->SelectedItem->ToString();
		}
	private:
		//クリップボードへの自動コピー用イベント
		System::Void LoadedText_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			//Clipboard::SetText(LoadedText->Text);
		 }
	private:
		//エンコードボタンのクリックイベント
		System::Void EncodeButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			//エンコードする
			//(デバッグ)デコードして平文と同じかチェック
			//サイコロ配置のダイアログを表示する
		}
#pragma endregion
};
}
