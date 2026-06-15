#pragma once
#pragma once
#include <iostream>
#include "MyInputLib.h"
#include <vector>
#include <string>
#include <fstream>

namespace MyVectorLib
{

	void PrintVictorNumbers(const vector<int>& vNumbers)
	{
		for (const int& n : vNumbers)
			cout << n << " ";
		cout << endl;
	}

	void PrintFileContent(string FileName)
	{
		fstream myFile;
		myFile.open(FileName, ios::in);//Read (input) mode.

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				cout << line << endl;
			}
			myFile.close();
		}
	}

	void LoadDataFromFileToVector(string FileName, vector<string>& vFileContent)
	{
		fstream myFile;
		myFile.open(FileName, ios::in);//Read (input) mode.

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				vFileContent.push_back(line);
			}
			myFile.close();
		}
	}

	void SaveVectorToFile(string FileName, const vector<string>& vFileContent)
	{
		fstream myFile;
		myFile.open(FileName, ios::out);

		if (myFile.is_open())
		{

			for (const string& line : vFileContent)
			{
				if (line != "")
					myFile << line << endl;
			}

			myFile.close();
		}
	}

	void DeleteVectorFromFile(string FileName, string Record)
	{
		vector <string> vFileContent;
		LoadDataFromFileToVector(FileName, vFileContent);

		for (string& line : vFileContent)
		{
			if (line == Record) line = "";
		}
		SaveVectorToFile(FileName, vFileContent);
	}

	void DeleteVectorFromFileUsingIterator(string FileName, string Record)
	{
		vector<string> vFileContent;
		LoadDataFromFileToVector(FileName, vFileContent);

		// استخدام الـ Iterator للحذف الفعلي من الفيكتور
		for (vector<string>::iterator iter = vFileContent.begin(); iter != vFileContent.end(); )
		{
			if (*iter == Record) {
				iter = vFileContent.erase(iter); // يحذف العنصر ويرجع المؤشر للي بعده
			}
			else {
				iter++;
			}
		}

		SaveVectorToFile(FileName, vFileContent);
	}
	void UpdateRecordInFile(string FileName, string Record, string updateTo)
	{
		vector <string> vFileContent;
		LoadDataFromFileToVector(FileName, vFileContent);

		for (string& line : vFileContent)
		{
			if (line == Record) line = updateTo;
		}
		SaveVectorToFile(FileName, vFileContent);
	}

	void UpdateRecordInFileUsingIterator(string FileName, string Record, string updateTo)
	{
		vector<string> vFileContent;
		LoadDataFromFileToVector(FileName, vFileContent);

		// استخدام Iterator للبحث عن أول عنصر مطابق
		vector<string>::iterator it;
		for (it = vFileContent.begin(); it != vFileContent.end(); ++it)
		{
			if (*it == Record)
			{
				*it = updateTo; // تعديل القيمة باستخدام الـ Pointer (Dereferencing)
				break; // توقف بمجرد التعديل (أسرع للأداء)
			}
		}

		SaveVectorToFile(FileName, vFileContent);
	}


	bool isIdentityMatrix(vector<vector<int>>& matrix)
	{ // تجربة من دروس المصفوفات   Problem #13/3
		/*
		ن مميزات الفيكتور (وعيوبه لو مش واخد بالك) إنه بيسمح بحاجة اسمها Jagged Array، يعني ممكن تلاقي الصف الأول فيه 3 أعمدة، والصف التاني فيه 10 أعمدة!
لذلك، برمجياً بنروح لـ matrix[0] كمعيار قياسي، لكن لازم نتأكد الأول إن المصفوفة مش فاضية، فغالباً الكود الأنضف بيكون كده:
		*/
		if (!matrix.empty()) 
		{
			short rows = matrix.size();
			short cols = matrix[0].size();
		for (short i = 0; i < rows; i++)
		{
			for (short j = 0; j < cols; j++)
			{
				if (i == j && matrix[i][j] != 1) return false;
				if (i != j && matrix[i][j] != 0) return false;
			}
		}
		}
		return true;
	}

	void CalculateFibonacciSeriesUsingVectors(int Number, vector<int>& vFibonacci)
	{
		int prev1 = 1;
		int prev2 = 1;
		int Feb = 0;
		vFibonacci.push_back(1);
		vFibonacci.push_back(1);

		for (short i = 3; i <= Number; i++)
		{
			Feb = prev1 + prev2;
			vFibonacci.push_back(Feb);

			prev2 = prev1;
			prev1 = Feb;
		}
	}

	void PrintVectorString(const vector<string>& vString) // Also included in MyStringLib
	{
		for (const string& s : vString)
			cout << s << endl;
	}

	vector<string> SplitString(string s1, string delim = " ")  // Also included in MyStringLib
	{
		vector<string>vWord;
		string sWord = "";
		short pos = 0, count = 0;

		while ((pos = s1.find(delim)) != std::string::npos)
		{
			sWord = s1.substr(0, pos);
			if (sWord != "") vWord.push_back(sWord);

			s1.erase(0, pos + delim.length());
		}
		if (s1 != "") vWord.push_back(s1);

		return vWord;
	}
	
}