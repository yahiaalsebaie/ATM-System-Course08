#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace MyStringLib
{
	string ReadString()
	{
		string s1;
		cout << "Please Enter Your String:\n";
		getline(cin, s1);
		return s1;
	}
	string ReadString(string Message)
	{
		string s1;
		cout << Message;
		getline(cin, s1);
		return s1;
	}
	char ReadChar()
	{
		char Ch1;
		cout << "Please Enter a Character?\n";
		cin >> Ch1;
		return Ch1;
	}
	void PrintFirstLetterOfEachWord(const string& s1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1.at(i) != ' ' && isFirstLetter)
				cout << s1.at(i) << endl;
			isFirstLetter = (s1.at(i) == ' ');		// لو الحرف الحالي مسافة، يبقى الحرف اللي جاي احتمال يكون بداية كلمة

		}
	}
	string UpperFirstLetterOfEachWord(string s1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1.at(i) != ' ' && isFirstLetter)
				s1[i] = toupper(s1[i]);
			isFirstLetter = (s1[i] == ' ');		// لو الحرف الحالي مسافة، يبقى الحرف اللي جاي احتمال يكون بداية كلمة
		}
		return s1;
	}
	string lowerFirstLetterOfEachWord(string s1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1.at(i) != ' ' && isFirstLetter)
				s1[i] = tolower(s1[i]);
			isFirstLetter = (s1[i] == ' ');		// لو الحرف الحالي مسافة، يبقى الحرف اللي جاي احتمال يكون بداية كلمة
		}
		return s1;
	}
	string UpperAllString(string s1)
	{

		for (short i = 0; i < s1.length(); i++)
			s1[i] = toupper(s1[i]);
		return s1;
	}
	string lowerAllString(string s1)
	{

		for (short i = 0; i < s1.length(); i++)
			s1[i] = tolower(s1[i]);
		return s1;
	}
	
	char InvertLetterCase(char c)
	{
		return (islower(c) ? toupper(c) : tolower(c));
	}

	string InvertAllStringLettersCase(string s)
	{
		for (short i = 0; i < s.length(); i++)
		{
			s[i] = InvertLetterCase(s[i]);
		}
		return s;
	}

	//GetCapitalAndSmallLettersCount
	pair<int, int> CountLetters(string s1)
	{
		int Capital = 0, small = 0;
		for (short i = 0; i < s1.length(); i++)
		{
			if (isupper(s1[i])) Capital++;
			else if (islower(s1[i])) small++;
		}
		return { Capital, small };
		//call
		//	auto [Capital, small] = CapitalAndSmallLettersCount(s1);
	}
	enum enCountLetters {
		SmallLetters = 0, CapitalLetters = 1, PunctLetters = 2, Digits = 3, Spaces = 4, AllLeters = 5
	};
	short CountLetters(string s1, enCountLetters WhatToCount = enCountLetters::AllLeters)
	{

		if (WhatToCount == enCountLetters::AllLeters) return s1.length();
		short Counter = 0;

		/* using for loop
		for (short i = 0; i < s1.length(); i++)
	{
		if (WhatToCount == enCountLetters::SmallLetters && islower(s1[i]))
			Counter++;
		else if (WhatToCount == enCountLetters::CapitalLetters && isupper(s1[i]))
			Counter++;
		else if (WhatToCount == enCountLetters::PunctLetters && ispunct(s1[i]))
			Counter++;
		else if (WhatToCount == enCountLetters::Digits && isdigit(s1[i]))
			Counter++;
		else if (WhatToCount == enCountLetters::Spaces && s1[i] == ' ')
		Counter++;
	}
		*/
		switch (WhatToCount)
		{
		case SmallLetters:
			for (const char& c : s1)
				if (islower(c)) Counter++;
			break;
		case CapitalLetters:
			for (const char& c : s1)
				if (isupper(c)) Counter++;
			break;
		case PunctLetters:
			for (const char& c : s1)
				if (ispunct(c)) Counter++;
			break;
		case Digits:
			for (const char& c : s1)
				if (isdigit(c)) Counter++;
			break;
		case Spaces:
			for (const char& c : s1)
				if (c == ' ') Counter++;
			break;
		case AllLeters:
			return s1.length();
		default:
			return s1.length();
		}

		return Counter;
	}
	
	short CountLetterCharacter(string s1, char c1, bool MatchCase = true)
	{
		short count = 0;
		for (short i = 0; i < s1.length(); i++)
		{
			if (MatchCase)
			{
				if (s1[i] == c1) count++;
			}
			else
			{
				if (tolower(s1[i]) == tolower(c1)) count++;
			}
		}
		return count;
	}

	bool isVowel(char ch)
	{
		ch = tolower(ch);

		switch (ch)
		{
		case 'a':case 'e':case 'i':case 'o':case 'u': return true;
		default: return false;
		}
		//static char arrVowels[5] = { 'a', 'e', 'i', 'o', 'u' };
	//bool isVowel(char ch)
	//{
	//	ch = tolower(ch);
	//	
	//	for (short i = 0; i < 5; i++)
	//		if (arrVowels[i] == ch) return true;
	//	
	//	return false;
	//}
	}
	short CountVowels(string s1)
	{
		short counter = 0;
		for (short i = 0; i < s1.length(); i++)
		{
			if (isVowel(s1[i])) counter++;
		}return counter;
	}
	void PrintAllVowels(string s1)
	{
		for (short i = 0; i < s1.length(); i++)
			if (isVowel(s1[i])) cout << s1[i] << "  ";
	}

	void PrintEachWordInStringUsingForLoop(string s1)
	{

		bool isFirstLetter = true;

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ') cout << s1[i];
			if (s1[i] == ' ' && !isFirstLetter)
				cout << endl;
			isFirstLetter = (s1[i] == ' ');		// لو الحرف الحالي مسافة، يبقى الحرف اللي جاي احتمال يكون بداية كلمة

		}
	}

	void PrintEachWordInString(string S1)
	{
		string delim = " "; // delimiter
		cout << "\nYour string wrords are: \n\n";
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, pos + delim.length()); /* erase() until
			positon and move to next word. */
		}
		if (S1 != "")
		{
			cout << S1 << endl; // it print last word of the string.
		}
	}

	short CountWords(string s1)
	{
		string delim = " ", sWord = "";
		short pos = 0, count = 0;

		while ((pos = s1.find(delim)) != std::string::npos)
		{
			sWord = s1.substr(0, pos);
			if (sWord != "") count++;

			s1.erase(0, pos + delim.length());
		}
		if (s1 != "") count++;
		return count;
	}

	vector<string> SplitString(string S1, string Separator)
	{
		vector<string> vString;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Separator)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + Separator.length()); /* erase() until
			position and move to next word. */
		}
		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}
		return vString;
	}

	void PrintVectorString(const vector<string>& vString)
	{
		for (const string& s : vString)
			cout << s << endl;
	}

	
	string TrimLeft(string S1)
	{
		// 1. بيمشي من أول حرف (index 0) لحد آخر حرف
		for (short i = 0; i < S1.length(); i++)
		{
			// 2. أول ما يقابل "أول حرف" مش مسافة
			if (S1[i] != ' ')
			{
				// 3. هنا السر! بيستخدم دالة substr
				return S1.substr(i, S1.length() - i);
			}
		}
		return ""; // لو الجملة كلها مسافات
	}
	
	string TrimRight(string S1)
	{
		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ') // أول ما يقابل حرف من ناحية اليمين
			{
				return S1.substr(0, i + 1); // اقطع من الصفر لحد المكان ده
			}
		}
		return ""; // لو الجملة كلها مسافات

	}
	string Trim(string S1)
	{
		return (TrimLeft(TrimRight(S1)));
	}

	string TrimLeftUsingErase(string& s1)
	{

		for (short i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ') return s1.erase(0, i);
		}
		// لو وصل هنا معناه إن الجملة كلها مسافات
		return s1.erase(0, s1.length()); // عشان لو الجملة فراغات فقط ترجع صفر مسافات
	}
	string TrimRightUsingErase(string& s1)
	{
		for (short i = s1.length() - 1; i >= 0; i--)
		{
			if (s1[i] != ' ') return s1.erase(i + 1, s1.length());
		}
		return s1.erase(0, s1.length()); // عشان لو الجملة فراغات فقط ترجع صفر مسافات
	}
	string TrimAllUsingErase(string& s1)
	{
		TrimLeftUsingErase(s1);
		return TrimRightUsingErase(s1);
	}
	string JoinString(const vector<string>& vString, string Delim)
	{
		string s1 = "";
		for (const string& s : vString)
			s1 += s + Delim;
		return s1.substr(0, s1.length() - Delim.length());
	}
	string JoinString(string arr[], short length, string Delim)
	{
		string s1 = "";
		for (short i = 0; i < length - 1; i++)
		{
			s1 += arr[i] + Delim;
		}
		return s1 + arr[length - 1]; // بضيف آخر عنصر بدون الفاصل
	}

	string ReverseWordsInString(string s1, string delim)
	{
		vector<string> vString = SplitString(s1, " ");
		string s2 = "";
		for (short i = vString.size() - 1; i >= 0; i--)
		{
			s2 += vString[i] + delim;
		}
		return (s2.substr(0, s2.length() - delim.length()));
	}
	string ReverseWordsInString(string s1)
	{
		vector<string> vString = SplitString(s1, " ");
		vector<string>::iterator iter = vString.end();
		string s2 = "";

		while (iter != vString.begin())
		{
			--iter;
			s2 += *iter + " ";
		}
		return (s2.substr(0, s2.length() - 1));

	}
	vector<string> ReverseWordsInVector(string s1, string delim = " ")
	{
		vector<string> vString = SplitString(s1, " ");
		string s2 = "";
		vector<string> v2;
		for (int i = vString.size() - 1; i >= 0; i--)
		{
			v2.push_back(vString[i]);
		}
		vString.clear();
		return (v2);
	}

	string ReplaceStringUsingBuiltinFunction(string s1, string oldString, string updateTo)
	{
		short pos = s1.find(oldString);

		while (pos != std::string::npos)
		{
			s1.replace(pos, oldString.length(), updateTo);
			pos = s1.find(oldString);
		}
		return s1;
	}

	string ReplaceStringUsingIterator(string s1, string OldWord, string updateTo,string Separator = " ", bool matchCase = true)
	{
		vector<string> vString = SplitString(s1, Separator);
		vector<string>::iterator iter;
		for (iter = vString.begin(); iter != vString.end(); iter++)
		{
			if (matchCase)
			{
				if (*iter == OldWord) *iter = updateTo;
			}
			else
			{
				if (lowerAllString(*iter) == lowerAllString(OldWord)) *iter = updateTo;
			}
		}

		return JoinString(vString, Separator);
	}
	string ReplaceStringUsingSplit(string s1, string OldWord, string updateTo, string Separator = " ", bool matchCase = true)
	{
		vector <string >vString = SplitString(s1, Separator);
		for (string& s : vString)
		{
			if (matchCase)
			{
				if (s == OldWord) s = updateTo;
			}
			else
			{
				if (lowerAllString(s) == lowerAllString(OldWord)) s = updateTo;
			}
		}
		return JoinString(vString, Separator);
	}

	string RemoveAllPunctuationsAndPutSpace(string s1)
	{
		for (int i = 0; i < s1.length(); i++)
		{
			if (ispunct(s1[i])) s1[i] = ' '; // O(N)
		}
		return s1;
	}

	string RemovePunctuationsFromString(string s1)
	{
		string s2;
		for (int i = 0; i < s1.length(); i++)
		{
			if (!ispunct(s1[i])) s2 += s1[i]; // O(N)
		}
		return s2;
	}

};