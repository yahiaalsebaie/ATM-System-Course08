#pragma once
#pragma warning(disable : 4996)
#include "MyInputLib.h"
#include "MyStringLib.h"
#include "MyDateLib.h"
#include <iostream>
#include <istream>
#include <string>
#include <vector>


// بسم الله الرحمن الرحيم .. دالة حساب التاريخ الهجري
// أغلب المعادلات هنا هي معادلات ثابتة متاخدة زي ما هي زي معادلة التاريخ الغريغوري المستخدمة في مكتبة التاريخ الميلادي
//كان ممكن أستعين بالمكتبة الميلادية اللي عملتها قبل كده ولكن فضلت تكون دي مكتبة مستقلة
// الاعتماد على المعادلات الرياضية بيخلي السرعة أعلى من اللفات
// حاولت أعتمد على المعادلات الفكلية ولكن ديماً فيه أخطاء تتعدى اليومين بكتير فرجعت للوبس

namespace MyHijriDateLib {

	/*const string DayLongName[7] = { "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday" };
	const string DayShortName[7] = { "Fri", "Sat", "Sun", "Mon", "Tue", "Wed", "Thu" };

	// علقتهم عشان جتلي فكرة في تحسين الكود وهي كالتالي :
	*تثبيت اسم اليوم وهو الثابت الوحيد في التاريخين الهجري والميلادي 
	* لو وجدنا اليوم هو الأحد وعند التحويل طلع السبت 17 فاحنا نشوف أقصر طريق وهنا هيكون التقدم للأحد 18 بإضافة يوم نزود يوم على التاريخ
	*ولو كان اليوم الميلادي الجمعة وعند التحويل وجدناه الجمعة هجري فهو صحيح
	*لو كان اليوم الميلادي الجمعة وعند التحويل وجدناه السبت 21 هنرجعه للجمعة 20 هجري 
	*/
	// توحيد الترتيب مع الترتيب الميلادي 
	const string DayLongName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	const string DayShortName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	const short LeapHijriYears[] = { 2, 5, 7, 10, 13, 16, 18, 21, 24, 26, 29 };

	const string HijriMonthsNames[] = {
		"", "Muharram", "Safar", "Rabi' al-Awwal", "Rabi' al-Thani",
		"Jumada al-Awwal", "Jumada al-Thani", "Rajab", "Sha'ban",
		"Ramadan", "Shawwal", "Zhu al-Qi'dah", "Zhu al-Hijjah"
	};
	string GetHijriMonthFullName(short MonthNumber)
	{
		return HijriMonthsNames[MonthNumber];
	}
	struct stHijriDate
	{
		short Day;
		short Month;
		short Year;
	};
	enum enBeforAfter { Before = -1, Equal = 0, After = 1 };
	bool IsLeapHijriYear(short Year)
	{
		/*
		​زي ما التقويم الميلادي فيه سنة كبيسة كل 4 سنين
		التقويم الهجري الاصطلاحي عنده دورة مدتها 30 سنة
		جوة الـ 30 سنة هجرية دول يوجد 11 سنة كريمة
		بيزيد فيهم يوم في شهر ذو الحجة فيبقى 30 يوم بدل 29
		وتصبح السنة 355 يوم بدل 354
		والسنة الكريمة تسمى كريمة عشان لو ضربنا 32 في 11 يوم الفرق هيدينا سنة كاملة
		يبقى كل 32 سنة ييجي رمضان مرتين في السنة.
	*/
	// بنجيب باقي القسمة على 30 عشان نعرف ترتيب السنة جوة الدورة
		short IndexInCycle = Year % 30;

		for (short i = 0; i < 11; i++)
			if (IndexInCycle == LeapHijriYears[i]) return true;

		return false;
	}

	short NumberOfDaysInHijriMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12) return 0;

		// شهر ذو الحجة (الشهر 12) يعتمد على السنة كريمة أو عادية
		if (Month == 12)
			return IsLeapHijriYear(Year) ? 30 : 29;

		// الشهور الفردية 30 يوم، والزوجية 29 يوم
		// طبعاً الرؤية زمان بتتأثر بالغيوم وحتى دلوقتي بيغم علينا رؤية الهلال زي رمصان ولكن بطبيعة الحال بنتبع السعودية في ذو الحجة زي اليوم المبارك ده ثالث ايام العيد لعام 1447هـ
		//عشان كده هضيف خيار تعديل التقويم الهجري +/- يوم زي تطبيق صلاتك
		return (Month % 2 != 0) ? 30 : 29;
	}
	short NumberOfDaysInHijriMonth(stHijriDate Date)
	{
		return NumberOfDaysInHijriMonth(Date.Month, Date.Year);
	}

	short NumberOfDaysInHijriYear(short Year)
	{
		return IsLeapHijriYear(Year) ? 355 : 354;
	}
	long GetAbsoluteHijriDays(short Day, short Month, short Year)
	{
		/*
		long TotalDays = 0;

		// حساب أيام السنوات السابقة بالكامل
		// السنة الهجرية المتوسطة في الدورة الـ 30 تساوي 354.3666 يوم
		// المعادلة دي بتحسب أيام السنين اللي فاتت مع أخذ السنوات الكريمة في الاعتبار بدقة:
		TotalDays = (Year - 1) * 354 + ((30 * Year + 11) / 30);

		// حساب أيام الشهور المكتملة في السنة الحالية
		// بما إن الشهور فردي (30) وزوجي (29)، فمتوسط الشهرين ورا بعض 59 يوم
		TotalDays += (Month - 1) * 29 + (Month / 2);

		// إضافة أيام الشهر الحالي
		TotalDays += Day;

		return TotalDays;
		*/

		long TotalDays = 0;
		//السنين السابقة
		for (short i = 1; i < Year; i++)
		{
			TotalDays += NumberOfDaysInHijriYear(i);
		}

		// الشهور السابقة في السنة الحالية
		for (short m = 1; m < Month; m++)
		{
			TotalDays += NumberOfDaysInHijriMonth(m, Year);
		}

		TotalDays += Day;

		return TotalDays;

	}
	long GetAbsoluteHijriDays(stHijriDate Date)
	{
		return GetAbsoluteHijriDays(Date.Day, Date.Month, Date.Year);
	}
	//short GetDayOfWeekIndexOrder(short Day, short Month, short Year, bool ReturnDayShortName = false)
	//{
	//	// نجيب الرقم المطلق للأيام
	//	long AbsoluteDays = GetAbsoluteHijriDays(Day, Month, Year);
	//	return (AbsoluteDays - 1) % 7; // هنا ده صح لو كنا بنبدأ من يوم الجمعة كمدخل 0 
	//}
	short GetDayOfWeekIndexOrder(short Day, short Month, short Year, bool ReturnDayShortName = false)
	{
		long AbsoluteDays = GetAbsoluteHijriDays(Day, Month, Year);

		// الإزاحة 5 أيام: يوم 1 محرم عام 1 هـ كان يوم جمعة. 
		// في المصفوفة الجديدة، الجمعة ترتيبه 5. إذن نضبط المعادلة بإضافة 5 أيام
		return (AbsoluteDays + 5 - 1) % 7;
	}
	short GetDayOfWeekIndexOrder(stHijriDate Date, bool ReturnDayShortName = false)
	{
		return GetDayOfWeekIndexOrder(Date.Day, Date.Month, Date.Year, ReturnDayShortName);
	}

	string GetDayOfWeekName(short Day, short Month, short Year, bool ReturnDayShortName = false)
	{
		short DayIndex = GetDayOfWeekIndexOrder(Day, Month, Year, ReturnDayShortName);
		if (ReturnDayShortName) return DayShortName[DayIndex];

		return DayLongName[DayIndex];
	}
	string GetDayOfWeekName(stHijriDate Date, bool ReturnDayShortName = false)
	{
		return GetDayOfWeekName(Date.Day, Date.Month, Date.Year, ReturnDayShortName);
	}


	stHijriDate GetHijriDateFromAbsoluteDays(long AbsoluteDays)
	{
		stHijriDate Date;
		short RemainingDays = 0;
		short DaysInYear = 0;
		short DaysInMonth = 0;

		// استخراج السنة عن طريق طرح أيام السنين المكتملة
		short Year = 1;
		while (true)
		{
			DaysInYear = NumberOfDaysInHijriYear(Year);
			if (AbsoluteDays > DaysInYear)
			{
				AbsoluteDays -= DaysInYear;
				Year++;
			}
			else break;
		}
		Date.Year = Year;

		// استخراج الشهر عن طريق طرح أيام الشهور المكتملة
		short Month = 1;
		while (true)
		{
			DaysInMonth = NumberOfDaysInHijriMonth(Month, Date.Year);
			if (AbsoluteDays > DaysInMonth)
			{
				AbsoluteDays -= DaysInMonth;
				Month++;
			}
			else break;
		}
		Date.Month = Month;

		// الأيام المتبقية هي اليوم الحالي جوه الشهر
		Date.Day = (short)AbsoluteDays;

		return Date;
	}

	bool isLeapMiladiYear(short Year)
	{
		return ((Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0));
	}
	short NumberOfDaysInMiladiMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12) return 0;
		return (Month == 2) ? (isLeapMiladiYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;

	}

	long GetAbsoluteMiladiDays(short Day, short Month, short Year)
	{
		/*
		// معادلة فلكية ثابتة زي ما هي لتحويل التاريخ الميلادي التراكمي لأيام صافية
		if (Month <= 2)
		{
			Year--;
			Month += 12;
		}
		return (36525 * Year) / 100 + (306001 * (Month + 1)) / 10000 + Day - 428;*/

		long TotalDays = 0;
		for (short i = 1; i < Year; i++)
		{
			TotalDays += isLeapMiladiYear(i) ? 366 : 365;
		}

		for (short m = 1; m < Month; m++)
		{
			TotalDays += NumberOfDaysInMiladiMonth(m, Year);
		}
		TotalDays += Day;

		return TotalDays;
	}
	long GetAbsoluteMiladiDays(stHijriDate Date)
	{
		return GetAbsoluteMiladiDays(Date.Day, Date.Month, Date.Year);
	}
	stHijriDate ConvertMiladiToHijri(short MiladiDay, short MiladiMonth, short MiladiYear)
	{
		long AbsoluteMiladiDays = GetAbsoluteMiladiDays(MiladiDay, MiladiMonth, MiladiYear);

		// نطرح منها الإزاحة الثابتة لحد يوم هجرة الرصول صلى الله عليه وسلم --> 16 يوليو 622م
		long AbsoluteHijriDays = (AbsoluteMiladiDays - 227015);
		// نحول الأيام الصافية ليوم وشهر وسنة
		return GetHijriDateFromAbsoluteDays(AbsoluteHijriDays);
	}

	string ConvertHijriToMiladi(short HijriDay, short HijriMonth, short HijriYear, bool includedDayName = false, bool shortName = true)
	{
		long AbsoluteHijriDays = GetAbsoluteHijriDays(HijriDay, HijriMonth, HijriYear);

		// نضيف عليها الإزاحة الثابتة لحد يوم هجرة الرصول صلى الله عليه وسلم --> 16 يوليو 622م
		long AbsoluteMiladiDays = AbsoluteHijriDays + 227015;

		/*
		* // حاولت أستخدم المعادلات زي ما هي عشان أوصل لتعقيد O(1)
		* // لكن كل مرة بيطلع معايا مشاكل في حساب التاريخ وعشان كجه هعتمد على اللوبس أفضل
		long long J = AbsoluteMiladiDays + 1721425;
		long long Y = (4 * J - 1) / 146097;
		J = 4 * J - 1 - 146097 * Y;
		long long D = J / 4;

		J = (4 * D + 3) / 1461;
		D = 4 * D + 3 - 1461 * J;
		D = (D + 4) / 4;

		long long M = (5 * D - 3) / 153;
		D = 5 * D - 3 - 153 * M;
		short Day = (D + 5) / 5;

		short Month = M < 10 ? M + 3 : M - 9;
		short Year = M < 10 ? Y * 100 + J : Y * 100 + J + 1;*/

		short Year = 1;
		while (true)
		{
			short DaysInMiladiYear = isLeapMiladiYear(Year) ? 366 : 365;

			if (AbsoluteMiladiDays > DaysInMiladiYear)
			{
				AbsoluteMiladiDays -= DaysInMiladiYear;
				Year++;
			}
			else break;
		}

		short Month = 1;
		while (true)
		{
			short mDays = NumberOfDaysInMiladiMonth(Month, Year);
			if (AbsoluteMiladiDays > mDays)
			{
				AbsoluteMiladiDays -= mDays;
				Month++;
			}
			else break;
		}
		short Day = (short)AbsoluteMiladiDays;

		cout << "\n[Notice]: Calendar conversion is based on arithmetic approximation; a 1-2 day variance may occur due to lunar sightings.\n";

		if (includedDayName)
		{
			//short DayOfWeekIndex = (AbsoluteHijriDays - 1) % 7; // صح في المعادلة القديمة اللي بتبدأ من يوم الجمعة
			 
			
			//	long TotalMiladiAbsolute = AbsoluteHijriDays + 227001;
				//short DayOfWeekIndex = (TotalMiladiAbsolute - 1) % 7;

			short DayOfWeekIndex = (AbsoluteHijriDays - 1) % 7; // الأصح بعد ما غيرت المصفوفة لتناسب التاريخ الميلادي
			string DayName = (shortName) ? DayShortName[DayOfWeekIndex] : DayLongName[DayOfWeekIndex];
			return DayName + " : " + to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
		}
		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
	}
	string ConvertHijriToMiladi(stHijriDate Date, bool includDayName = false, bool shortName = true)
	{
		return ConvertHijriToMiladi(Date.Day, Date.Month, Date.Year, includDayName, shortName);
	}

	string PrintHijriDate(stHijriDate Date, bool shortName = true)
	{
		string DayName = GetDayOfWeekName(Date.Day, Date.Month, Date.Year, shortName);

		return DayName + " : " + to_string(Date.Day) + "/" + HijriMonthsNames[Date.Month] + "/" + to_string(Date.Year) + " AH";
	}

	bool IsLastDayInMonth(stHijriDate Date)
	{
		short NumberOfDays = NumberOfDaysInHijriMonth(Date.Month, Date.Year);
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
	bool IsDate1EqualDate2(stHijriDate Date1, stHijriDate Date2)
	{
		//  return (Date2.Year != Date1.Year) ? false : (Date2.Month != Date1.Month) ? false : (Date2.Day != Date1.Day) ? false : true;
		return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
	}
	bool IsHijriDate1BeforeDate2(stHijriDate Date1, stHijriDate Date2)
	{
		return  (Date1.Year < Date2.Year) ? true :
			((Date1.Year == Date2.Year) ?
				((Date1.Month < Date2.Month) ? true :
					((Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false)) : false);
	}

	bool IsDate1AfterDate2(stHijriDate Date1, stHijriDate Date2)
	{
		return (!IsHijriDate1BeforeDate2(Date1, Date2)) && !IsDate1EqualDate2(Date1, Date2);
	}


	stHijriDate IncreaseHijriDateByOneDay(stHijriDate Date)
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
	void swapDates(stHijriDate& Date1, stHijriDate& Date2)
	{
		stHijriDate tempDate = Date1;
		Date1 = Date2;
		Date2 = tempDate;
	}

	long GetDifferenceInHijriDays(stHijriDate Date1, stHijriDate Date2, bool IncludeEndDay = false)
	{
		long Days1 = GetAbsoluteHijriDays(Date1.Day, Date1.Month, Date1.Year);
		long Days2 = GetAbsoluteHijriDays(Date2.Day, Date2.Month, Date2.Year);

		long Diff = Days2 - Days1;

		return IncludeEndDay ? ++Diff : Diff;
	}
	stHijriDate CorrectInvalidDayInHijriMonth(stHijriDate Date)
	{
		short DaysInNextYearMonth = NumberOfDaysInHijriMonth(Date.Month, Date.Year);
		if (Date.Day > DaysInNextYearMonth)
		{
			Date.Day = DaysInNextYearMonth;
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByXDays(stHijriDate Date, int Days)
	{
		for (int i = 0; i < Days; i++)
		{
			Date = IncreaseHijriDateByOneDay(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByOneWeek(stHijriDate Date)
	{
		return IncreaseHijriDateByXDays(Date, 7);
	}
	stHijriDate IncreaseHijriDateByXWeeks(stHijriDate Date, int Weeks)
	{
		for (int i = 0; i < Weeks; i++)
			Date = IncreaseHijriDateByOneWeek(Date);
		return Date;
	}
	stHijriDate IncreaseHijriDateByOneMonth(stHijriDate Date)
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

		short DaysInNewMonth = NumberOfDaysInHijriMonth(Date.Month, Date.Year);
		if (Date.Day > DaysInNewMonth) Date.Day = DaysInNewMonth;

		return Date;

	}
	stHijriDate IncreaseHijriDateByXMonths(stHijriDate Date, int Months)
	{
		for (int i = 0; i < Months; i++)
		{
			Date = IncreaseHijriDateByOneMonth(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByOneYear(stHijriDate Date)
	{
		Date.Year++;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate IncreaseHijriDateByXYears(stHijriDate Date, int Years)
	{
		for (int i = 0; i < Years; i++)
		{
			Date = IncreaseHijriDateByOneYear(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByXYearsFaster(stHijriDate Date, int Years)
	{
		Date.Year += Years;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate IncreaseHijriDateByOneDecade(stHijriDate Date)
	{
		Date.Year += 10;
		return  CorrectInvalidDayInHijriMonth(Date);
	}
	stHijriDate IncreaseHijriDateByXDecades(stHijriDate Date, int Decades)
	{
		for (int i = 0; i < Decades; i++)
		{
			Date = IncreaseHijriDateByOneDecade(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByXDecadesFaster(stHijriDate Date, int Decades)
	{

		Date.Year += (Decades * 10);
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate IncreaseHijriDateByOneCentury(stHijriDate Date)
	{
		Date.Year += 100;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate IncreaseHijriDateByXCenturies(stHijriDate Date, int Century)
	{
		for (int i = 0; i < Century; i++)
		{
			Date = IncreaseHijriDateByOneCentury(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByXCenturiesFaster(stHijriDate Date, int Century)
	{
		if (Century == 0) return Date;
		Date.Year += (Century * 100);
		return  CorrectInvalidDayInHijriMonth(Date);
	}
	stHijriDate IncreaseHijriDateByOneMillennium(stHijriDate Date)
	{
		Date.Year += 1000;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate IncreaseHijriDateByXMillenniums(stHijriDate Date, int Millennium)
	{
		for (int i = 0; i < Millennium; i++)
		{
			Date = IncreaseHijriDateByOneMillennium(Date);
		}
		return Date;
	}
	stHijriDate IncreaseHijriDateByXMillenniumsFaster(stHijriDate Date, int Millennuim)
	{
		if (Millennuim == 0) return Date;

		Date.Year += (Millennuim * 1000);
		return  CorrectInvalidDayInHijriMonth(Date);

	}


	//DecreaseHijriDateBy

	stHijriDate DecreaseHijriDateByOneDay(stHijriDate Date)
	{
		if (IsFirstMonthInYear(Date.Month))
		{
			if (IsFirstDayInMonth(Date.Day))
			{
				Date.Month = 12;
				Date.Year--;
				short PrevMonthLastDay = NumberOfDaysInHijriMonth(Date);
				Date.Day = PrevMonthLastDay;
				return Date;
			}
		}
		if (IsFirstDayInMonth(Date.Day))
		{
			Date.Month--;
			short PrevMonthLastDay = NumberOfDaysInHijriMonth(Date);
			Date.Day = PrevMonthLastDay;
			return Date;
		}
		Date.Day--;
		return Date;
	};

	stHijriDate DecreaseHijriDateByXDays(stHijriDate Date, int Days)
	{
		for (int i = Days; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneDay(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByOneWeek(stHijriDate Date)
	{
		return DecreaseHijriDateByXDays(Date, 7);
	}
	stHijriDate DecreaseHijriDateByXWeeks(stHijriDate Date, int Weeks)
	{
		for (int i = Weeks; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneWeek(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByOneMonth(stHijriDate Date)
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
		short DaysInPrevMonth = NumberOfDaysInHijriMonth(Date.Month, Date.Year);
		if (Date.Day > DaysInPrevMonth) Date.Day = DaysInPrevMonth;

		return Date;

	}
	stHijriDate DecreaseHijriDateByXMonths(stHijriDate Date, int Months)
	{
		for (int i = Months; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneMonth(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByOneYear(stHijriDate Date)
	{
		Date.Year--;
		// 31/2/2001 - 1 year >> 31/2/2000 تاريخ غلط 
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate DecreaseHijriDateByXYears(stHijriDate Date, int Years)
	{
		for (int i = Years; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneYear(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByXYearsFaster(stHijriDate Date, int Years)
	{
		Date.Year -= Years;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate DecreaseHijriDateByOneDecade(stHijriDate Date)
	{
		Date.Year -= 10;
		return  CorrectInvalidDayInHijriMonth(Date);
	}
	stHijriDate DecreaseHijriDateByXDecades(stHijriDate Date, int Decades)
	{
		for (int i = Decades; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneDecade(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByXDecadesFaster(stHijriDate Date, int Decades)
	{

		Date.Year -= (Decades * 10);
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate DecreaseHijriDateByOneCentury(stHijriDate Date)
	{
		Date.Year -= 100;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate DecreaseHijriDateByXCenturies(stHijriDate Date, int Century)
	{
		for (int i = Century; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneCentury(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByXCenturiesFaster(stHijriDate Date, int Century)
	{
		if (Century == 0) return Date;
		Date.Year -= (Century * 100);
		return  CorrectInvalidDayInHijriMonth(Date);
	}
	stHijriDate DecreaseHijriDateByOneMillennium(stHijriDate Date)
	{
		Date.Year -= 1000;
		return  CorrectInvalidDayInHijriMonth(Date);

	}
	stHijriDate DecreaseHijriDateByXMillenniums(stHijriDate Date, int Millennuim)
	{
		for (int i = Millennuim; i > 0; i--)
		{
			Date = DecreaseHijriDateByOneMillennium(Date);
		}
		return Date;
	}
	stHijriDate DecreaseHijriDateByXMillenniumsFaster(stHijriDate Date, int Millennuim)
	{
		if (Millennuim == 0) return Date;

		Date.Year -= (Millennuim * 1000);
		return  CorrectInvalidDayInHijriMonth(Date);

	}

	//Weekends , BusinessDays and Vacations.
	bool IsEndOfWeek(stHijriDate Date)
	{
		return (GetDayOfWeekIndexOrder(Date) == 6); //Saturday
	}
	bool IsWeekend(stHijriDate Date)
	{
		short DayIndex = GetDayOfWeekIndexOrder(Date);
		return (DayIndex == 5 || DayIndex == 6); //Friday and Saturday.
	}
	bool IsBusinessDay(stHijriDate Date)
	{
		return !IsWeekend(Date);
	}
	short DaysUntilTheEndOfWeek(stHijriDate Date)
	{
		/* if (IsEndOfWeek(Date)) return 0;
		 short DaysCounter = 0;
		 while (GetDayOfWeekOrder(Date) != 6)
		 {
			 DaysCounter++;
			 Date = IncreaseHijriDateByOneDay(Date);
		 }
		 return DaysCounter;*/
		return 6 - GetDayOfWeekIndexOrder(Date);
	}
	short DaysUntilTheEndOfMonth(stHijriDate Date, bool includeEndDay = false)
	{
		short EndOfMonth = NumberOfDaysInHijriMonth(Date);

		return (includeEndDay) ?
			(EndOfMonth - Date.Day + 1) :
			(EndOfMonth - Date.Day);
	}
	short TotalDaysFromYearBeginning(stHijriDate Date)
	{
		short DaysCount = 0;

		for (short i = 1; i < Date.Month; i++)
		{
			DaysCount += NumberOfDaysInHijriMonth(i, Date.Year);
		}

		return DaysCount + Date.Day;
	}
	short DaysUntilTheEndOfYear(stHijriDate Date, bool includeEndDay = false)
	{
		short RemainingDays = NumberOfDaysInHijriYear(Date.Year) - TotalDaysFromYearBeginning(Date);
		return (includeEndDay) ? (RemainingDays + 1) : (RemainingDays);
	}

	short DaysUntilEndOfMonthInclusive(stHijriDate Date)
	{
		return DaysUntilTheEndOfMonth(Date, 1);
	}
	short DaysUntilEndOfYearInclusive(stHijriDate Date)
	{
		return DaysUntilTheEndOfYear(Date, 1);
	}


	short CalculateHowManyWeekendsInDate(stHijriDate DateFrom, stHijriDate DateTo, bool isIncludedLastDay = false)
	{

		short AllDays = GetDifferenceInHijriDays(DateFrom, DateTo, isIncludedLastDay);

		short WeekendsCounter = 0;

		for (short i = 0; i < AllDays; i++)
		{
			if (IsWeekend(DateFrom)) WeekendsCounter++;
			DateFrom = IncreaseHijriDateByOneDay(DateFrom);
		}
		return WeekendsCounter;
	}
	stHijriDate CalculateVacationReturnDate(stHijriDate DateFrom, short VacationDays)
	{
		stHijriDate ReturnDate = DateFrom;

		while (VacationDays > 0)
		{
			if (IsBusinessDay(ReturnDate)) VacationDays--;

			ReturnDate = IncreaseHijriDateByOneDay(ReturnDate);
		}

		/*stHijriDate ReturnDate = DateFrom;
		ReturnDate = IncreaseDateByXDays(ReturnDate, VacationDays);
		while (CalculateActualVacationDays(DateFrom, ReturnDate) != VacationDays) // شغالة بس فيها لوبس خفية هتخليها O(n^2).
		{
			ReturnDate = IncreaseHijriDateByOneDay(ReturnDate);
		}
		return ReturnDate;*/

		//if ReturnDate == Friday or Saturday
		while (IsWeekend(ReturnDate)) ReturnDate = IncreaseHijriDateByOneDay(ReturnDate);

		return ReturnDate;
	}

	short CalculateActualVacationDays(stHijriDate VacationStartDate, stHijriDate VacationEnd, bool isIncludedLastDay = false)
	{
		short AllDays = GetDifferenceInHijriDays(VacationStartDate, VacationEnd, isIncludedLastDay);

		short ActualVacationDaysCounter = 0;

		for (short i = 0; i < AllDays; i++)
		{
			if (IsBusinessDay(VacationStartDate)) ActualVacationDaysCounter++;
			VacationStartDate = IncreaseHijriDateByOneDay(VacationStartDate);
		}
		return ActualVacationDaysCounter;
	}

	// Periods
	struct stPeriod {
		stHijriDate StartDate;
		stHijriDate EndDate;
	};
	bool IsValidDate(stHijriDate Date)
	{
		if (Date.Month < 1 || Date.Month > 12 || Date.Day < 1) return false;
		short MonthDays = NumberOfDaysInHijriMonth(Date);
		if (MonthDays < Date.Day) return false;

		return true;

	}
	stHijriDate ReadDate(bool turnValidOn = true)
	{
		stHijriDate Date;
		Date.Day = MyInputLib::ReadNumberInRange(1, 31, "Enter a Day : ", false);
		Date.Month = MyInputLib::ReadNumberInRange(1, 12, "Enter a Month : ", false);
		Date.Year = MyInputLib::ReadPositiveNumber("Enter a year  : ");
		if (turnValidOn)
		{
			while (!IsValidDate(Date))
			{
				string MonthName = GetHijriMonthFullName(Date.Month);
				short MonthDays = NumberOfDaysInHijriMonth(Date);
				cout << "\nThe Day is Not Valid!\n[";
				cout << MonthName << "] Max Days are [" << MonthDays << "].\n";
				Date.Day = MyInputLib::ReadNumberInRange(1, 31, "Enter a Day : ", false);
			}
		}
		return Date;
	}

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
	enBeforAfter CompareDates(stHijriDate Date1, stHijriDate Date2)
	{
		if (IsHijriDate1BeforeDate2(Date1, Date2)) return enBeforAfter::Before; //First Circuit  // من أول نبضة في المعالج
		return (IsDate1EqualDate2(Date1, Date2)) ? enBeforAfter::Equal : enBeforAfter::After;
		/*
		 if (IsDate1EqualsDate2(Date1, Date2)) return enBeforAfter::Equal;
		return (IsDate1AfterDate2(Date1, Date2)) ? enBeforAfter::After : enBeforAfter::Before; // بيستدعي 3 دوال جوه بعض IsDate1AfterDate2
		*/
	}

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
		return GetDifferenceInHijriDays(Period.StartDate, Period.EndDate, IncludingEndDay);
	}

	bool IsDateInPeriod(stPeriod Period, stHijriDate Date)
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


	//Read/Print Date Format With Comprehensive Check
	enum enDateFormat {
		DayMonthYearSlash = 1,      // 24/6/2026
		MonthDayYearSlash = 2,      // 6/24/2026
		YearMonthDaySlash = 3,      // 2026/6/24
		FullDateText = 4,           // Sun , 24/6/2026
		YearDayMonthSlash = 5,      // 2026/24/6 
		MonthDayYearDash = 6,       // 6-24-2026
		DayMonthYearDash = 7,       // 24-6-2026
		NamedCustom = 8,            // Day: 24, Month: 6, Year: 2026
		CustomFormat = 9           // [dd/mm/yyyy] You can use one delimiter of [/-.|,*\\ ]
	};

	stHijriDate StringToDate(string sDate/*, string Separator = "/"*/)
	{// dd/mm/yyyy

		stHijriDate Date = { 0,0,0 };
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
	string ReadStringDateFormat(bool UsingAllFunction = false, string sDate = { 0,0,0 })
	{
		// string sDate;

		if (UsingAllFunction)
		{
			cout << "\nPlease Enter Date dd/mm/yyyy : ";
			getline(cin >> ws, sDate);
		}
		/*while (sDate.length() < 8)
		{
			cout << "\nInvalid Date!\n";
			cout << "Please Enter Date : ";
			getline(cin >> ws, sDate);
		}*/
		stHijriDate Date = StringToDate(sDate);

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
		//        cout << "[9] Enter Your Format      -> [dd/mm/yyyy] use one delimiter of [/-.|,*\\ ]\n";
		cout << "===============================================================\n";

		Choose = MyInputLib::ReadNumberInRange(1, 8, "Choose Date Format ");
		return (enDateFormat)Choose;
	}

	string DateToString(stHijriDate Date, enDateFormat Format = enDateFormat::DayMonthYearSlash)
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
			return PrintHijriDate(Date, true);

		case enDateFormat::YearDayMonthSlash:
			return to_string(Date.Year) + "/" + to_string(Date.Day) + "/" + to_string(Date.Month);

		case enDateFormat::MonthDayYearDash:
			return to_string(Date.Month) + "-" + to_string(Date.Day) + "-" + to_string(Date.Year);

		case enDateFormat::DayMonthYearDash:
			return to_string(Date.Day) + "-" + to_string(Date.Month) + "-" + to_string(Date.Year);

		case enDateFormat::NamedCustom:
			return "Day: " + to_string(Date.Day) + ", Month: " + to_string(Date.Month) + ", Year: " + to_string(Date.Year);
			/*   case enDateFormat::CustomFormat:
			   return FormatDate(Date,ReadStringDateFormat());
   */

		default:
			return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
		}
	}

	string FormatDate(stHijriDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = DateFormat;

		FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "dd", to_string(Date.Day));
		FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = MyStringLib::ReplaceStringUsingBuiltinFunction(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
		/*
		string FormatDate(stHijriDate Date, string DateFormat = "dd/mm/yyyy",string Separator = "/")
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
	stHijriDate ConvertMiladiToHijriTrastedUsingMiladiDay(short MiladiDay, short MiladiMonth, short MiladiYear)
	{
		//  حساب رقم يوم الأسبوع الميلادي الفعلي Target Weekday
		/*long AbsoluteMiladiDays = GetAbsoluteMiladiDays(MiladiDay, MiladiMonth, MiladiYear);
		short TargetWeekday = (AbsoluteMiladiDays - 1 + 5) % 7;*/
		short TargetWeekday = MyDateLib::GetDayOfWeekOrder(MiladiDay, MiladiMonth, MiladiYear); // مكنتش عايز أناديها بس هي اللي بتجيب اليوم الأصح

		// التاريخ التقريبي
		stHijriDate ApproxHijriDate = ConvertMiladiToHijri(MiladiDay, MiladiMonth, MiladiYear);

		// حساب رقم يوم الأسبوع الناتج من الحساب التقريبي 
		short CalculatedWeekday = GetDayOfWeekIndexOrder(ApproxHijriDate.Day, ApproxHijriDate.Month, ApproxHijriDate.Year);

		// هنا بنطبق طريقة حساب الفارق أو الإزاحة
		short AutoOffset = TargetWeekday - CalculatedWeekday;

		// معالجة الالتفاف الأسبوعي لأقصر طريق
		if (AutoOffset > 3)  AutoOffset -= 7;
		if (AutoOffset < -3) AutoOffset += 7;

		// لو كانت الإزاحة صفر تعيد التاريخ التقريبي كما هو فوراً 
		if (AutoOffset == 0) return ApproxHijriDate;

		//  لو كان هناك فارق بنحصل على الأيام الهجرية المطلقة ونضيف عليها الفارق
		long CorrectAbsoluteHijriDays = GetAbsoluteHijriDays(ApproxHijriDate) + AutoOffset;

		// والنتيجة النهائية لما بنحول الأيام لتاريخ مظبوط بناءً على اليوم نفسه لتجنب فرق اليوم أو اليومين في التاريخ
		return GetHijriDateFromAbsoluteDays(CorrectAbsoluteHijriDays);
	}
}