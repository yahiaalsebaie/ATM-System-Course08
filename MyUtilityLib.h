#pragma once
#pragma warning(disable : 4996)


#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace MyUtilityLib 
{

    int RandomNumber(int From, int To) 
    {
        //Seeds the random number generator in C++, called only once
        //srand((unsigned)time(NULL)); //Put it in main()
        return rand() % (To - From + 1) + From;
    }

    string EncryptText(string txt, short Key) {
        for (int i = 0; i < txt.length(); i++)
            txt[i] += Key;
        return txt;
    }

    string DecryptText(string txt, short Key) {
        for (int i = 0; i < txt.length(); i++)
            txt[i] -= Key;
        return txt;
    }

    void PrintInvertedNumberPattern(int Number) {
        for (int i = Number; i >= 1; i--) {
            for (int j = 1; j <= i; j++) cout << i;
            cout << "\n";
        }
    }

    bool GuessPassword(string Password) {
        string word = "";
        int Counter = 0;
        for (int i = 65; i <= 90; i++) {
            for (int j = 65; j <= 90; j++) {
                for (int k = 65; k <= 90; k++) {
                    word = string(1, char(i)) + char(j) + char(k);
                    Counter++;
                    if (word == Password) {
                        std::cout << "Found after " << Counter << " trials.\n";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    string GetSystemDateTime() {
        time_t t = time(0);
        tm* now = localtime(&t);

        // تنسيق: YYYY-MM-DD | HH:MM:SS
        return to_string(now->tm_year + 1900) + "-" +
            to_string(now->tm_mon + 1) + "-" +
            to_string(now->tm_mday) + " | " +
            to_string(now->tm_hour) + ":" +
            to_string(now->tm_min) + ":" +
            to_string(now->tm_sec);
    }

    void PrintFibonacciUsingLoop(int Number)
    {
        int prev1 = 1, prev2 = 1, Feb = 0;

        cout << "1  1  ";
        for (short i = 3; i <= Number; i++)
        {
            Feb = prev1 + prev2;
            prev2 = prev1;
            prev1 = Feb;
            cout << Feb << "  ";
        }
    }

    
string ConvertNumberToText(unsigned long long Number)
{
    // متنساش تستخدم unsigned long long ReadLongPositiveNumber()
    if (Number == 0) return "";

    if (Number >= 1 && Number < 20)
    {
        string arr[]{
            "","One","Two","Three","Four","Five","Six","Seven",
            "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
            "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return arr[Number];
    }

    if (Number >= 20 && Number < 100)
    {
        string arr[]{
            "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
        return arr[Number / 10] + (Number % 10 != 0 ? " " + ConvertNumberToText(Number % 10) : "");
    }

    if (Number >= 100 && Number < 1000)
    {
        return ConvertNumberToText(Number / 100) + " Hundred" + (Number % 100 != 0 ? " " + ConvertNumberToText(Number % 100) : "");
    }

    // Thousands: 1,000 to 999,999
    if (Number >= 1'000ULL && Number < 1'000'000ULL) //(unsigned long long)1000000
    {
        return ConvertNumberToText(Number / 1'000ULL) + " Thousand" + (Number % 1'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000ULL) : "");
    }

    // Millions: 1,000,000 to 999,999,999
    if (Number >= 1'000'000ULL && Number < 1'000'000'000ULL)
    {
        // Or: if (Number >= (unsigned long long)1e6 && Number < (unsigned long long)1e9)
        return ConvertNumberToText(Number / 1'000'000ULL) + " Million" + (Number % 1'000'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000'000ULL) : "");
    }

    // Billions: 1,000,000,000 to 999,999,999,999
    if (Number >= 1'000'000'000ULL && Number < 1'000'000'000'000ULL)
    {
        return ConvertNumberToText(Number / 1'000'000'000ULL) + " Billion" + (Number % 1'000'000'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000'000'000ULL) : "");
    }

    // Trillions: 1,000,000,000,000 to 999,999,999,999,999
    if (Number >= 1'000'000'000'000ULL && Number < 1'000'000'000'000'000ULL)
    {
        return ConvertNumberToText(Number / 1'000'000'000'000ULL) + " Trillion" + (Number % 1'000'000'000'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000'000'000'000ULL) : "");
    }

    // Quadrillions: 1,000,000,000,000,000 to 999,999,999,999,999,999
    if (Number >= 1'000'000'000'000'000ULL && Number < 1'000'000'000'000'000'000ULL)
    {
        return ConvertNumberToText(Number / 1'000'000'000'000'000ULL) + " Quadrillion" + (Number % 1'000'000'000'000'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000'000'000'000'000ULL) : "");
    }

    // Quintillions: 1,000,000,000,000,000,000 to 9,223,372,036,854,775,807 
   // unsigned long long int RealMaxNumber = 18'446'744'073'709'551'615ULL;
    if (Number >= 1'000'000'000'000'000'000ULL && Number <= 18'446'744'073'709'551'615ULL)
    {
        return ConvertNumberToText(Number / 1'000'000'000'000'000'000ULL) + " Quintillion" + (Number % 1'000'000'000'000'000'000ULL != 0 ? " " + ConvertNumberToText(Number % 1'000'000'000'000'000'000ULL) : "");
    }

    return "Out of range...";
}
struct NumberScale
{
    unsigned long long Value;
    string Name;
};
string ConvertNumberToTextUsingVectors(unsigned long long Number)
{
    // متنساش تستخدم unsigned long long ReadUnsignedLongPositiveNumber()
   // if (Number == 0) return "";

    if (Number > 0 && Number < 20)
    {
        const   string arr[]{
               "","One","Two","Three","Four","Five","Six","Seven",
               "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
               "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return arr[Number];
    }

    if (Number >= 20 && Number < 100)
    {
        const string arr[]{
              "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
        return arr[Number / 10] + (Number % 10 != 0 ? " " + ConvertNumberToTextUsingVectors(Number % 10) : "");
    }

    if (Number >= 100 && Number < 1000)
    {
        return ConvertNumberToTextUsingVectors(Number / 100) + " Hundred" + (Number % 100 != 0 ? " " + ConvertNumberToTextUsingVectors(Number % 100) : "");
    }
    if (Number == 0)
        return "Zero";
    const vector<NumberScale> Scales
    {
        //{(unsigned long long)1e3,"Thousand"},
        {1'000'000'000'000'000'000ULL, "Quintillion"},
        {1'000'000'000'000'000ULL,     "Quadrillion"},
        {1'000'000'000'000ULL,         "Trillion"},
        {1'000'000'000ULL,             "Billion"},
        {1'000'000ULL,                 "Million"},
        {1'000ULL,                     "Thousand"}
        //لو اتكتبوا تصاعدي مش هيكتب اسم الفئة الخاصة بكل رقم
        /*
         {1'000ULL,"Thousand"},
        {1'000'000ULL,"Million"},
        {1'000'000'000ULL,"Billion"},
        {1'000'000'000'000ULL,"Trillion"},
        {1'000'000'000'000'000ULL,"Quadrillion"},
        {1'000'000'000'000'000'000ULL,"Quintillion"} // كده غلط
        */
    };

    for (const NumberScale& Scale : Scales)
    {
        if (Number >= Scale.Value)
        {
            return ConvertNumberToTextUsingVectors(Number / Scale.Value) + " " + Scale.Name + (Number % Scale.Value ? " " + ConvertNumberToTextUsingVectors(Number % Scale.Value) : "");
        }
    }
    return "Out of range...";

}

string ConvertNumberTo1eNum(unsigned long long number)
{
    if (number == 0) return "Zero";
    short count = 0;

    while (number >= 10)
    {
        number /= 10;
        count++;
    }
    return to_string(number) + "e" + to_string(count);
}


}