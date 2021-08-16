#pragma once
#include <iostream>
#include "yolo_v2_class.hpp"
#include <msclr/marshal_cppstd.h>

cv::Mat mat;
std::string cfg, weights, names;

namespace test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	protected:

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(9, 10);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(653, 10);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(640, 480);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(11, 494);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(186, 39);
			this->button1->TabIndex = 2;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(201, 494);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(186, 39);
			this->button2->TabIndex = 3;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(391, 494);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(186, 39);
			this->button3->TabIndex = 4;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->ClientSize = System::Drawing::Size(1301, 539);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ dlg = gcnew OpenFileDialog;
		dlg->Filter = "‰æ‘œÌ§²Ù(*.bmp,*.jpg,*.png,*.tif,*.ico)|*.bmp;*.jpg;*.png;*.tif;*.ico";
		if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;

		Bitmap^ bmp1 = gcnew Bitmap(dlg->FileName);
		pictureBox1->Image = bmp1;

		std::string imgPath;
		MarshalString(dlg->FileName, imgPath);
		mat = cv::imread(imgPath);
		cv::resize(mat, mat, cv::Size(640, 480));
		drawImage(pictureBox2, mat);
	}

	private: System::Void MarshalString(System::String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)((Marshal::StringToHGlobalAnsi(s)).ToPointer());
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	private: System::Void drawImage(PictureBox^ pic, cv::Mat mat) {

		if ((pic->Image == nullptr) || (pic->Width != mat.cols)
			|| (pic->Height != mat.rows)) {
			pic->Width = mat.cols;
			pic->Height = mat.rows;
			Bitmap^ bmpPicBox = gcnew Bitmap(pic->Width, pic->Height);
			pic->Image = bmpPicBox;
		}
		Graphics^ g = Graphics::FromImage(pic->Image);
		Bitmap^ bmp = gcnew Bitmap(mat.cols, mat.rows, mat.step,
			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(mat.data));
		g->DrawImage(bmp, 0, 0, mat.cols, mat.rows);
		pic->Refresh();
		delete g;
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		button3->Enabled = TRUE;
		cfg = "yolov3.cfg";
		weights = "yolov3.weights";
		names = "coco.names";
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		Detector detector(cfg, weights);
		auto obj_names = objects_names_from_file(names);
		auto det_image = detector.mat_to_image_resize(mat);
		std::vector<bbox_t> result_vec = detector.detect_resized(*det_image, mat.size().width, mat.size().height);
		draw_boxes(mat, result_vec, obj_names);
		drawImage(pictureBox2, mat);
	}
};
}
