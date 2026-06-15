#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include "MyInputLib.h"
#include <iomanip>
#include <ctime>


using namespace std;
namespace MyDateLib {
    const string DayName[7] = { "Sun" ,"Mon","Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" };
    struct stDate
    {
        short Day;
        short Month;
        short Year;
    };
    
    string GetMonthFullName(short MonthNumber);
    short NumberOfDaysInMonth(stDate Date);
    bool IsValidDate(stDate Date);

    stDate ReadDate(bool turnValidOn = true)
    {
        stDate Date;
        Date.Day = MyInputLib::ReadNumberInRange(1, 31, "Enter a Day : ", false);
        Date.Month = MyInputLib::ReadNumberInRange(1, 12, "Enter a Month : ", false);
        Date.Year = MyInputLib::ReadPositiveNumber("Enter a year  : ");
        if (turnValidOn)
        {
            while (!IsValidDate(Date))
            {
                string MonthName = GetMonthFullName(Date.Month);
                short MonthDays = NumberOfDaysInMonth(Date);
                cout << "\nThe Day is Not Valid!\n[";
                cout << MonthName << "] Max Days are [" << MonthDays << "].\n";
                Date.Day = MyInputLib::ReadNumberInRange(1, 31, "Enter a Day : ", false);
            }
        }
        return Date;
    }

    bool IsLeapYear(short Year)
    {
        // if year is divisible by 4 AND not divisible by 100
     // OR if year is divisible by 400
     // then it is a leap year
        return ((Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0));
        /* return ((Year % 400 == 0) ? true : (Year % 100 == 0) ? false : (Year % 4 == 0)? true : false);*/
    }
    //In Year
    short NumberOfDaysInYear(short Year)
    {
        return (IsLeapYear(Year)) ? 366 : 365;
    }
    short NumberOfHoursInYear(short Year)
    {
        return NumberOfDaysInYear(Year) * 24;
    }
    int NumberOfMinutesInYear(short Year)
    {
        return NumberOfHoursInYear(Year) * 60;
    }
    int NumberOfSecondsInYear(short Year)
    {
        return NumberOfMinutesInYear(Year) * 60;
    }
    //In Month

//In Month
    short NumberOfDaysInMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12) return 0;
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;

        //Or using const array like this..
       /* if (Month < 1 || Month>12)
            return 0;
        int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
            NumberOfDays[Month - 1];*/

    }
    short NumberOfHoursInMonth(short Month, short Year)
    {
        return NumberOfDaysInMonth(Month, Year) * 24;
    }
    int NumberOfMinutesInMonth(short Month, short Year)
    {
        return NumberOfHoursInMonth(Month, Year) * 60;
    }
    int NumberOfSecondsInMonth(short Month, short Year)
    {
        return NumberOfMinutesInMonth(Month, Year) * 60;
    }
    //In Month Overload
    short NumberOfDaysInMonth(stDate Date)
    {
        return NumberOfDaysInMonth(Date.Month, Date.Year);
    }
    short NumberOfHoursInMonth(stDate Date)
    {
        return NumberOfDaysInMonth(Date) * 24;
    }
    int NumberOfMinutesInMonth(stDate Date)
    {
        return NumberOfHoursInMonth(Date) * 60;
    }
    int NumberOfSecondsInMonth(stDate Date)
    {
        return NumberOfMinutesInMonth(Date) * 60;
    }

    short DayOfWeekOrder(short Day, short Month, short Year)
    {
        //CalculateGregorianCalendar
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        //short d = (Day + y + (y / a) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7; //Division by Zero cuz of (y/a) >> (y/0).
        short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
        //The value of d is 0 for a Sunday, 1 for a Monday, 2 for a Tuesday etc.
        return d;
    }

    short DayOfWeekOrder(stDate Date)
    {
        //CalculateGregorianCalendar
        //The value of d is 0 for a Sunday, 1 for a Monday, 2 for a Tuesday etc.
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    string GetDayShortName(short Day, short Month, short Year)
    {
        short d = DayOfWeekOrder(Day, Month, Year);
        const string DayName[7] = { "Sun" ,"Mon","Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" };

        return DayName[d];
    }
    string GetDayShortName(stDate Date)
    {
        short d = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        const string DayName[7] = { "Sun" ,"Mon","Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" };

        return DayName[d];
    }
    
    short GetDayOfWeekOrder(short Day, short Month, short Year)
    {
        //CalculateGregorianCalendar
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        //short d = (Day + y + (y / a) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7; //Division by Zero cuz of (y/a) >> (y/0).
        short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
        //The value of d is 0 for a Sunday, 1 for a Monday, 2 for a Tuesday etc.
        return d;
    }
  /*  string GetDayShortName(short Day, short Month, short Year)
    {
        short d = GetDayOfWeekOrder(Day, Month, Year);
          const string DayName[7] = { "Sun" ,"Mon","Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" };

        return DayName[d];

    }*/
    string GetMonthFullName(short MonthNumber)
    {
        const string MonthName[13] = { "" ,"January","February","March","April","May","June","July","August","September","October","November","December" };

        return MonthName[MonthNumber];
    }
    string GetMonthShortName(short MonthNumber)
    {
        const string MonthName[13] = { "" ,"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

        return MonthName[MonthNumber];
    }
    void PrintMonthHeader(short Month)
    {
        cout << "\n   _________________[" << GetMonthShortName(Month) << "]_________________\n";
        for (short i = 0; i < 7; i++)
        {
            cout << "   " << left << setw(3) << DayName[i];
        }
    }
    void PrintMonthCalendar(short Month, short Year)
    {

        string currentDayOrder = GetDayShortName(1, Month, Year);
        short NumberOfDays = NumberOfDaysInMonth(Month, Year);

        PrintMonthHeader(Month);
        cout << endl;
        short Count = 0; // Reuse Count in detect week days instead of call GetDayShortName() every loop
        for (Count = 0; Count < 7; Count++)
        {
            if (currentDayOrder != DayName[Count])
                cout << setw(6) << ""; // First day Place
            else break;
        }
        //Print Week Days
        for (short i = 0; i < NumberOfDaysInMonth(Month, Year); i++) // Days Numbers
        {
            cout << "   " << right << setw(3) << i + 1;
            /* if (GetDayShortName(i + 1, Month, Year) == "Sat") cout << "\n";*/
            Count++;
            if (Count == 7) // Week completed
            {
                Count = 0;
                cout << endl;
            }

        }
        cout << "\n   _______________________________________\n";

    }

    void PrintYearCalendar(short Year)
    {
        cout << "\n   _______________________________________\n";
        cout << "\n   \t\tCalendar - " << Year;
        cout << "\n   _______________________________________\n";

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }
    short TotalDaysFromYearBeginning(stDate Date)
    {
        short DaysCount = 0;

        for (short i = 1; i < Date.Month; i++)
        {
            DaysCount += NumberOfDaysInMonth(i, Date.Year);
        }

        return DaysCount + Date.Day;
    }

    
    stDate GetDateFromDayOrderInYear(short TotalDays, short Year)
    {
        stDate Date;
        short RemainderDays = TotalDays;
        short MonthCounter = 1;
        for (; MonthCounter <= 12; MonthCounter++)
        {
            short DaysInCurrentMonth = NumberOfDaysInMonth(MonthCounter, Year);
            if (RemainderDays <= DaysInCurrentMonth) break;
            RemainderDays -= DaysInCurrentMonth;
        }
        /*cout << "Day " << RemainderDays << endl;
        cout << "Month " << MonthCounter << endl;
        cout << "Year " << Year << endl;*/
        // cout << RemainderDays << "/" << MonthCounter << "/" << Year << endl;
        Date.Day = RemainderDays;
        Date.Month = MonthCounter;
        Date.Year = Year;
        return Date;

    }
    stDate GetDateFromDayOrderInYearUsingWhileLoop(short DateOrderInYear, short Year)
    {
        stDate Date;
        short RemainderDays = DateOrderInYear;
        short currentMonthDays = 0;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            currentMonthDays = NumberOfDaysInMonth(Date.Month, Year);
            if (RemainderDays > currentMonthDays)
            {
                RemainderDays -= currentMonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainderDays;
                break;
            }
        }

        return Date;

    }


    stDate GetDateAfterAddingDays_MyMethod(stDate Date, int DaysToAdd)
    {
        DaysToAdd += Date.Day;

        while (DaysToAdd > 0)
        {
            short CurrentMonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
            if (DaysToAdd > CurrentMonthDays)
            {
                DaysToAdd -= CurrentMonthDays;
                Date.Month++;
                Date.Day = 1;
                if (Date.Month > 12)
                {
                    Date.Month = 1;
                    Date.Year++;
                }
            }
            else
            {
                Date.Day = DaysToAdd;
                DaysToAdd = 0;
            }
        }

        return Date;

    }

    bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true
            : ((Date1.Year == Date2.Year) ?
                (Date1.Month < Date2.Month ? true
                    : (Date1.Month == Date2.Month ?
                        Date1.Day < Date2.Day : false))
                : false);
       /*if (Date1.Year < Date2.Year) return true;
        if (Date1.Year > Date2.Year) return false;

        if (Date1.Month < Date2.Month) return true;
        if (Date1.Month > Date2.Month) return false;

        return Date1.Day < Date2.Day;*/
    }

    bool IsDate1EqualDate2(stDate Date1, stDate Date2)
    {
      //  return (Date2.Year != Date1.Year) ? false : (Date2.Month != Date1.Month) ? false : (Date2.Day != Date1.Day) ? false : true;
        return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
    }
    bool IsDate1AfterDate2(stDate Date1, stDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2)) && !IsDate1EqualDate2(Date1, Date2);
    }

    bool IsLastDayInMonth(stDate Date)
    {
        short NumberOfDays = NumberOfDaysInMonth(Date.Month, Date.Year);
        return (NumberOfDays == Date.Day);
    }

    bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }
    bool IsFirstDayInMonth(short Day)
    {
        return (Day == 1);
    }

    bool IsFirstMonthInYear(short Month)
    {
        return (Month == 1);
    }

    stDate IncreaseDateByOneDayUsingAnotherFunction(stDate Date)
    {
        return GetDateAfterAddingDays_MyMethod(Date, 1);
    }
    stDate IncreaseDateByOneDay(stDate Date)
    {
        if (IsLastMonthInYear(Date.Month) && IsLastDayInMonth(Date))
        {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;
            return Date;
        }

        if (IsLastDayInMonth(Date))
        {
            Date.Day = 1;
            Date.Month++;
            return Date;
        }
        Date.Day++;
        return Date;
    };
    void swapDates(stDate& Date1, stDate& Date2)
    {
        stDate tempDate = Date1;
        Date1 = Date2;
        Date2 = tempDate;
    }
    int GetDiffrenceInDaysBetweenTwoDates(stDate Date1, stDate Date2, bool IncludingEndDay = false)
    {
        //غيرتها عشان بتديني -1 مع CountOverlapDays
       /* int count = 0;
        short swapFlagValue = 1;
        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            swapDates(Date1, Date2);
            swapFlagValue = -1;
        }
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            count++;
            Date1 = IncreaseDateByOneDay(Date1);
        }

        return (count + (IncludingEndDay ? 1 : 0)) * swapFlagValue;*/

        int count = 0;
        short swapFlagValue = 1;

        if (IsDate1AfterDate2(Date1, Date2))//        //غيرتها عشان بتديني -1 مع CountOverlapDays

        {
            swapDates(Date1, Date2);
            swapFlagValue = -1;
        }
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            count++;
            Date1 = IncreaseDateByOneDay(Date1);
        }
        return (count + (IncludingEndDay ? 1 : 0)) * swapFlagValue;

    }
    int GetDiffrenceInDaysBetweenTwoDatesInclusive(stDate Date1, stDate Date2)
    {
        return GetDiffrenceInDaysBetweenTwoDates(Date1, Date2, true);
    }
    stDate GetSystemDate()
    {
        stDate  Date;
        time_t t = time(0);
        tm* now = localtime(&t);

        Date.Day = now->tm_mday;
        Date.Month = now->tm_mon + 1;
        Date.Year = now->tm_year + 1900;

        return Date;
    }
    string PrintDate(stDate  Date, bool includeDayShortName = true)
    {
        if(includeDayShortName) return GetDayShortName(Date) + " , " + to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }
    stDate CorrectInvalidDayInMonth(stDate Date)
    {
        /*شكلها كان كده وعشان مكتبهاش في كل الأكواد
        stDate IncreaseDateByOneYear(stDate Date)
    {
        // 29/2/2000 + 1 year >> 29/2/2001 تاريخ غلط
        short DaysInNextYearMonth = NumberOfDaysInMonth(Date.Month, Date.Year + 1);
        if (Date.Day > DaysInNextYearMonth) Date.Day = DaysInNextYearMonth;
        Date.Year++;
        return Date;
    }
        */
        // بنعدل السنة الأول عشان تخش مظبوط على التاريخ
        // 29/2/2000 + 1 year >> 29/2/2001 تاريخ غلط 
        short DaysInNextYearMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
        if (Date.Day > DaysInNextYearMonth)
        {
            Date.Day = DaysInNextYearMonth;
        }
        return Date;
    }

    //IncreaseDateBy
    stDate IncreaseDateByXDays_UsingMyMethod(stDate Date, int Days)
    {
        return GetDateAfterAddingDays_MyMethod(Date, Days);
    }
    stDate IncreaseDateByXDays(stDate Date, int Days)
    {
        for (int i = 0; i < Days; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate IncreaseDateByOneWeek(stDate Date)
    {
        return IncreaseDateByXDays(Date, 7);
    }
    stDate IncreaseDateByXWeeks(stDate Date, int Weeks)
    {
        for (int i = 0; i < Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }
    stDate IncreaseDateByOneMonth(stDate Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }
        // لو يناير 31 يوم وفبراير 28 فهنا مشكلة في الأيام اللس هتتحفظ - وممكن أستخدم الميثود بتاعتي فوق وتنفع لكل حاجة بس المطلوب هنا إني أعمل تداخل للدوال-
        //GetDateAfterAddingDays_MyMethod
        //لو قلت إن الشهر 31 وشهر 2 28 يوم لو زودت شهر بالدالة دي فأنا هكون 28/3 يعني خسرت 3 ايام وعشان كده الميثود بتاعتي هي الأصح
        // أعتقد شركات الاتصالات بتضيع علينا الاشتراكات بالطريقة دي _يلا هي جت عليهم_ # نت غير موجود في مصر ☻.
        short DaysInNewMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
        if (Date.Day > DaysInNewMonth) Date.Day = DaysInNewMonth;

        return Date;

    }
    stDate IncreaseDateByXMonths(stDate Date, int Months)
    {
        for (int i = 0; i < Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }
    stDate IncreaseDateByOneYear(stDate Date)
    {
        Date.Year++;
        // 29/2/2000 + 1 year >> 29/2/2001 تاريخ غلط 
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate IncreaseDateByXYears(stDate Date, int Years)
    {
        for (int i = 0; i < Years; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }
    stDate IncreaseDateByXYearsFaster(stDate Date, int Years)
    {
        Date.Year += Years;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate IncreaseDateByOneDecade(stDate Date)
    {
        Date.Year += 10;
        return  CorrectInvalidDayInMonth(Date);
    }
    stDate IncreaseDateByXDecades(stDate Date, int Decades)
    {
        for (int i = 0; i < Decades; i++)
        {
            Date = IncreaseDateByOneDecade(Date);
        }
        return Date;
    }
    stDate IncreaseDateByXDecadesFaster(stDate Date, int Decades)
    {

        Date.Year += (Decades * 10);
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate IncreaseDateByOneCentury(stDate Date)
    {
        Date.Year += 100;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate IncreaseDateByXCenturies(stDate Date, int Century)
    {
        for (int i = 0; i < Century; i++)
        {
            Date = IncreaseDateByOneCentury(Date);
        }
        return Date;
    }
    stDate IncreaseDateByXCenturiesFaster(stDate Date, int Century)
    {
        if (Century == 0) return Date;
        Date.Year += (Century * 100);
        return  CorrectInvalidDayInMonth(Date);
    }
    stDate IncreaseDateByOneMillennium(stDate Date)
    {
        Date.Year += 1000;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate IncreaseDateByXMillenniums(stDate Date, int Millennuim)
    {
        for (int i = 0; i < Millennuim; i++)
        {
            Date = IncreaseDateByOneMillennium(Date);
        }
        return Date;
    }
    stDate IncreaseDateByXMillenniumsFaster(stDate Date, int Millennuim)
    {
        if (Millennuim == 0) return Date;

        Date.Year += (Millennuim * 1000);
        return  CorrectInvalidDayInMonth(Date);

    }


    //DecreaseDateBy
 
    stDate DecreaseDateByOneDay(stDate Date)
    {
        if (IsFirstMonthInYear(Date.Month))
        {
            if (IsFirstDayInMonth(Date.Day))
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
                return Date;
            }
        }
        if (IsFirstDayInMonth(Date.Day))
        {
            Date.Month--;
            short PrevMonthLastDay = NumberOfDaysInMonth(Date.Month, Date.Year);
            Date.Day = PrevMonthLastDay;
            return Date;
        }
        Date.Day--;
        return Date;
    };

    stDate DecreaseDateByXDays(stDate Date, int Days)
    {
        for (int i = Days; i > 0; i--)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate DecreaseDateByOneWeek(stDate Date)
    {
        return DecreaseDateByXDays(Date, 7);
    }
    stDate DecreaseDateByXWeeks(stDate Date, int Weeks)
    {
        for (int i = Weeks; i > 0; i--)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }
    stDate DecreaseDateByOneMonth(stDate Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }
        //30/3/2000  - 1m => 30/2/2000 Wrong Date
        short DaysInPrevMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
        if (Date.Day > DaysInPrevMonth) Date.Day = DaysInPrevMonth;

        return Date;

    }
    stDate DecreaseDateByXMonths(stDate Date, int Months)
    {
        for (int i = Months; i > 0; i--)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }
    stDate DecreaseDateByOneYear(stDate Date)
    {
        Date.Year--;
        // 31/2/2001 - 1 year >> 31/2/2000 تاريخ غلط 
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate DecreaseDateByXYears(stDate Date, int Years)
    {
        for (int i = Years; i > 0; i--)
        {
            Date = DecreaseDateByOneYear(Date);
        }
        return Date;
    }
    stDate DecreaseDateByXYearsFaster(stDate Date, int Years)
    {
        Date.Year -= Years;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate DecreaseDateByOneDecade(stDate Date)
    {
        Date.Year -= 10;
        return  CorrectInvalidDayInMonth(Date);
    }
    stDate DecreaseDateByXDecades(stDate Date, int Decades)
    {
        for (int i = Decades; i > 0; i--)
        {
            Date = DecreaseDateByOneDecade(Date);
        }
        return Date;
    }
    stDate DecreaseDateByXDecadesFaster(stDate Date, int Decades)
    {

        Date.Year -= (Decades * 10);
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate DecreaseDateByOneCentury(stDate Date)
    {
        Date.Year -= 100;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate DecreaseDateByXCenturies(stDate Date, int Century)
    {
        for (int i = Century; i > 0; i--)
        {
            Date = DecreaseDateByOneCentury(Date);
        }
        return Date;
    }
    stDate DecreaseDateByXCenturiesFaster(stDate Date, int Century)
    {
        if (Century == 0) return Date;
        Date.Year -= (Century * 100);
        return  CorrectInvalidDayInMonth(Date);
    }
    stDate DecreaseDateByOneMillennium(stDate Date)
    {
        Date.Year -= 1000;
        return  CorrectInvalidDayInMonth(Date);

    }
    stDate DecreaseDateByXMillenniums(stDate Date, int Millennuim)
    {
        for (int i = Millennuim; i > 0; i--)
        {
            Date = DecreaseDateByOneMillennium(Date);
        }
        return Date;
    }
    stDate DecreaseDateByXMillenniumsFaster(stDate Date, int Millennuim)
    {
        if (Millennuim == 0) return Date;

        Date.Year -= (Millennuim * 1000);
        return  CorrectInvalidDayInMonth(Date);

    }

    //Weekends , BusinessDays and Vacations.
    bool IsEndOfWeek(stDate Date)
    {
        return (DayOfWeekOrder(Date) == 6); //Saturday
    }
    bool IsWeekend(stDate Date)
    {
        short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex == 5 || DayIndex == 6); //Friday and Saturday.
    }
    bool IsBusinessDay(stDate Date)
    {
        return !IsWeekend(Date);
    }
    short DaysUntilTheEndOfWeek(stDate Date)
    {
       /* if (IsEndOfWeek(Date)) return 0;
        short DaysCounter = 0;
        while (DayOfWeekOrder(Date) != 6)
        {
            DaysCounter++;
            Date = IncreaseDateByOneDay(Date);
        }
        return DaysCounter;*/
        return 6 - DayOfWeekOrder(Date);
    }
    short DaysUntilTheEndOfMonth(stDate Date, bool includeEndDay = false)
    {
        short EndOfMonth = NumberOfDaysInMonth(Date);

        return (includeEndDay) ?
            (EndOfMonth - Date.Day + 1) :
            (EndOfMonth - Date.Day);
    }
    short DaysUntilTheEndOfYear(stDate Date, bool includeEndDay = false)
    {
        short RemainingDays = NumberOfDaysInYear(Date.Year) - TotalDaysFromYearBeginning(Date);
        return (includeEndDay) ? (RemainingDays + 1) : (RemainingDays);
    }

    short DaysUntilEndOfMonthInclusive(stDate Date)
    {
        return DaysUntilTheEndOfMonth(Date, 1);
    }
    short DaysUntilEndOfYearInclusive(stDate Date)
    {
        return DaysUntilTheEndOfYear(Date, 1);
    }

    short CalculateActualVacationDays(stDate VacationStartDate, stDate VacationEnd, bool isIncludedLastDay = false)
    {
        short AllDays = GetDiffrenceInDaysBetweenTwoDates(VacationStartDate, VacationEnd, isIncludedLastDay);

        short ActualVacationDaysCounter = 0;

        for (short i = 0; i < AllDays; i++)
        {
            if (IsBusinessDay(VacationStartDate)) ActualVacationDaysCounter++;
            VacationStartDate = IncreaseDateByOneDay(VacationStartDate);
        }
        return ActualVacationDaysCounter;
    }
    short CalculateHowManyWeekendsInDate(stDate DateFrom, stDate DateTo, bool isIncludedLastDay = false)
    {

        short AllDays = GetDiffrenceInDaysBetweenTwoDates(DateFrom, DateTo, isIncludedLastDay);

        short WeekendsCounter = 0;

        for (short i = 0; i < AllDays; i++)
        {
            if (IsWeekend(DateFrom)) WeekendsCounter++;
            DateFrom = IncreaseDateByOneDay(DateFrom);
        }
        return WeekendsCounter;
    }
    stDate CalculateVacationReturnDate(stDate DateFrom, short VacationDays)
    {
        stDate ReturnDate = DateFrom;

        while (VacationDays > 0)
        {
            if (IsBusinessDay(ReturnDate)) VacationDays--;

            ReturnDate = IncreaseDateByOneDay(ReturnDate);
        }

        /*stDate ReturnDate = DateFrom;
        ReturnDate = IncreaseDateByXDays(ReturnDate, VacationDays);
        while (CalculateActualVacationDays(DateFrom, ReturnDate) != VacationDays) // شغالة بس فيها لوبس خفية هتخليها O(n^2).
        {
            ReturnDate = IncreaseDateByOneDay(ReturnDate);
        }
        return ReturnDate;*/

        //if ReturnDate == Friday or Saturday
        while (IsWeekend(ReturnDate)) ReturnDate = IncreaseDateByOneDay(ReturnDate);

        return ReturnDate;
    }
    enum enBeforAfter
    {
        Before = -1, Equal = 0, After = 1
    };
    enBeforAfter CompareDates(stDate Date1, stDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2)) return enBeforAfter::Before; //First Circuit  // من أول نبضة في المعالج
        return (IsDate1EqualDate2(Date1, Date2)) ? enBeforAfter::Equal : enBeforAfter::After;
        /*
         if (IsDate1EqualsDate2(Date1, Date2)) return enBeforAfter::Equal;
        return (IsDate1AfterDate2(Date1, Date2)) ? enBeforAfter::After : enBeforAfter::Before; // بيستدعي 3 دوال جوه بعض IsDate1AfterDate2
        */
    }


    // Periods
    struct stPeriod {
        stDate StartDate;
        stDate EndDate;
    };
    stPeriod ReadPeriod()
    {
        stPeriod Period;
        cout << "\nEnter Start Date:\n";
        Period.StartDate = ReadDate();

        cout << "\nEnter End Date:\n";
        Period.EndDate = ReadDate();
        return Period;
    }
    /*bool  IsOverlapPeriod(stPeriod Period1, stPeriod Period2)
    {

        if (CompareDates(Period1.EndDate, Period2.StartDate) == enBeforAfter::Before) return false;
        if (CompareDates(Period2.EndDate, Period1.StartDate) == enBeforAfter::Before) return false;

        return true;

    }*/
  
    bool  IsOverlapPeriod(stPeriod Period1, stPeriod Period2, bool isIncludedLastDayAsOverlap = true)
    {
        if (isIncludedLastDayAsOverlap)
        {
            if (CompareDates(Period1.EndDate, Period2.StartDate) == enBeforAfter::Before) return false;
            if (CompareDates(Period2.EndDate, Period1.StartDate) == enBeforAfter::Before) return false;
        }

        else
        {
            if (CompareDates(Period1.EndDate, Period2.StartDate) != enBeforAfter::After) return false; // لو نهاية الفترة الأولى مش بعد بداية الفترة التانية
            // != enBeforAfter::After >> Before Or Equal
            if (CompareDates(Period2.EndDate, Period1.StartDate) != enBeforAfter::After) return false;
        }
        return true;
    }
    int CalculatePeriodLength(stPeriod Period, bool IncludingEndDay = false)
    {
        return GetDiffrenceInDaysBetweenTwoDates(Period.StartDate, Period.EndDate, IncludingEndDay);
    }

    bool IsDateInPeriod(stPeriod Period, stDate Date)
    {
        return((CompareDates(Period.StartDate, Date) != enBeforAfter::After) && CompareDates(Period.EndDate, Date) != enBeforAfter::Before);
    }

    void SwapPeriod(stPeriod& Period1, stPeriod& Period2)
    {
        stPeriod tempP;
        tempP = Period1;
        Period1 = Period2;
        Period2 = tempP;
    }

    int CountOverlapDays(stPeriod Period1, stPeriod Period2)
    {
        if (!IsOverlapPeriod(Period1, Period2)) return 0;

        stPeriod SharedDaysPeriod;

        // Newest start date
        SharedDaysPeriod.StartDate = (CompareDates(Period1.StartDate, Period2.StartDate) == enBeforAfter::After) ? Period1.StartDate : Period2.StartDate;

        // Oldest End date
        SharedDaysPeriod.EndDate = (CompareDates(Period1.EndDate, Period2.EndDate) == enBeforAfter::Before) ? Period1.EndDate : Period2.EndDate;

        return CalculatePeriodLength(SharedDaysPeriod, true);

    }

    bool IsValidDate(stDate Date)
    {
        if (Date.Month < 1 || Date.Month > 12 || Date.Day < 1) return false;
        short MonthDays = NumberOfDaysInMonth(Date);
        if (MonthDays < Date.Day) return false;

        return true;

    }

    //Read/Print Date Format With Comprehensive Check
    enum enDateFormat {
        DayMonthYearSlash = 1,      // 24/6/2026
        MonthDayYearSlash = 2,      // 6/24/2026
        YearMonthDaySlash = 3,      // 2026/6/24
        FullDateText = 4,           // Sun , 24/6/2026
        YearDayMonthSlash = 5,      // 2026/24/6 
        MonthDayYearDash = 6,       // 6-24-2026
        DayMonthYearDash = 7,       // 24-6-2026
        MultiLineCustom = 8         // Day: 24, Month: 6, Year: 2026
    };

    stDate StringToDate(string sDate/*, string Separator = "/"*/)
    {// dd/mm/yyyy

        stDate Date = { 0,0,0 };
        short FindPos = sDate.find_first_of("/-.,\\|* ");
        string Separator = (FindPos != string::npos) ? string(1, sDate[FindPos]) : "/";
        vector<string> vDate = MyStringLib::SplitString(sDate, Separator);
        if (vDate.size() == 3)
        {
            try
            {
                Date.Day = stoi(vDate[0]);
                Date.Month = stoi(vDate[1]);
                Date.Year = stoi(vDate[2]);

            }
            catch (...)
            {
                return { 0,0,0 };
            }
        }

        return Date;

    }
    enDateFormat ChooseDateFormat()
    {
        short Choose = 1;

        cout << "\nDate Format:";
        cout << "\n===============================================================\n";
        cout << "[1] Day Month Year         -> [DD/MM/YYYY]          \n";
        cout << "[2] Month Day Year         -> [MM/DD/YYYY]          \n";
        cout << "[3] Year Month Day         -> [YYYY/MM/DD]          \n";
        cout << "[4] Full Date Text         -> [DayName , DD/MM/YYYY]\n";
        cout << "[5] Year Day Month         -> [YYYY/DD/MM]          \n";
        cout << "[6] Month Day Year (Dash)  -> [MM-DD-YYYY]          \n";
        cout << "[7] Day Month Year (Dash)  -> [DD-MM-YYYY]          \n";
        cout << "[8] Date Text Details      -> [Day: DD, Month: MM, Year: YYYY]\n";
        cout << "===============================================================\n";

        Choose = MyInputLib::ReadNumberInRange(1, 8, "Choose Date Format ");
        return (enDateFormat)Choose;
    }

    string DateToString(stDate Date, enDateFormat Format = enDateFormat::DayMonthYearSlash)
    {
        switch (Format)
        {
        case enDateFormat::DayMonthYearSlash:
            return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);

        case enDateFormat::MonthDayYearSlash:
            return to_string(Date.Month) + "/" + to_string(Date.Day) + "/" + to_string(Date.Year);

        case enDateFormat::YearMonthDaySlash:
            return to_string(Date.Year) + "/" + to_string(Date.Month) + "/" + to_string(Date.Day);

        case enDateFormat::FullDateText:
            return PrintDate(Date, true);

        case enDateFormat::YearDayMonthSlash:
            return to_string(Date.Year) + "/" + to_string(Date.Day) + "/" + to_string(Date.Month);

        case enDateFormat::MonthDayYearDash:
            return to_string(Date.Month) + "-" + to_string(Date.Day) + "-" + to_string(Date.Year);

        case enDateFormat::DayMonthYearDash:
            return to_string(Date.Day) + "-" + to_string(Date.Month) + "-" + to_string(Date.Year);

        case enDateFormat::MultiLineCustom:
            return "Day: " + to_string(Date.Day) + ", Month: " + to_string(Date.Month) + ", Year: " + to_string(Date.Year);

        default:
            return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
        }
    }
    string ReadStringDateFormat()
    {
        string sDate;
        cout << "\nPlease Enter Date dd/mm/yyyy : ";
        getline(cin >> ws, sDate);
        /*while (sDate.length() < 8)
        {
            cout << "\nInvalid Date!\n";
            cout << "Please Enter Date : ";
            getline(cin >> ws, sDate);
        }*/
        stDate Date = StringToDate(sDate);

        while (Date.Day == 0 || Date.Month == 0 || Date.Year == 0 || !IsValidDate(Date))
        {
            cout << "\nInvalid Date Format!\n";
            cout << "Please enter a valid date like [dd/mm/yyyy]\n";
            cout << "You can use one delimiter of [/-.|,*\\ ]\n";
            cout << "Please Enter Date : ";
            getline(cin >> ws, sDate);
            Date = StringToDate(sDate);
        }
        return sDate;
    }

    string FormatDate(stDate Date, string DateFormat = "dd/mm/yyyy")
    {
        string FormattedDateString = DateFormat;

        FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "dd", to_string(Date.Day));
        FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "mm", to_string(Date.Month));
        FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "yyyy", to_string(Date.Year));

        return FormattedDateString;
        /*
        string FormatDate(stDate Date, string DateFormat = "dd/mm/yyyy",string Separator = "/")
    {
        string FormattedDateString = DateFormat;
        // كنت مصمم أكتر من دالة تبديل كل واحدة بطريقة مختلفة فلو هستخدمهم لازم أعمل التعديل ده على الدالة.
        FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "dd", to_string(Date.Day));

        FormattedDateString = MyStringLib::ReplaceStringUsingIterator(FormattedDateString, "mm", to_string(Date.Month),"/",1);

        FormattedDateString = MyStringLib::ReplaceStringUsingSplit(FormattedDateString, "yyyy", to_string(Date.Year), "/", 1);

        return FormattedDateString;
    }
        */
    }

}