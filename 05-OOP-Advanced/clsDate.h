#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
#pragma warning(disable : 4996)

class clsDate
{
private:
    string _Date;
    short _Year = 1900;
    short _Month = 1;
    short _Day = 1;

public:

    clsDate()
    {
        time_t t = time(0);

        tm* now = localtime(&t);

        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;

        _Date = to_string(_Day) + '/' + to_string(_Month) + '/' + to_string(_Year);
    }
    clsDate(string Date)
    {
        _Date = Date;

        string Write = Date;
        string delim = "/";
        vector <string> SplitString;

        short pos = 0;
        string sword;

        while ((pos = Write.find(delim)) != std::string::npos)
        {
            sword = Write.substr(0, pos);
            if (sword != "")
            {
                SplitString.push_back(sword);
            }
            Write.erase(0, pos + delim.length());
        }

        if (Write != "")
        {

            SplitString.push_back(Write);
        }

        _Day = stoi(SplitString[0]);
        _Month = stoi(SplitString[1]);
        _Year = stoi(SplitString[2]);

    }
    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;

        _Date = to_string(_Day) + '/' + to_string(_Month) + '/' + to_string(_Year);
    }
    clsDate(int TotalDays, int Year)
    {
        int RemainderDays = 0;
        int i = 0;

        while (TotalDays > 0)
        {
            i++;

            short DaysInMonth = HowManyDaysInMonth(Year, i);

            if (TotalDays <= DaysInMonth)
            {
                RemainderDays = TotalDays;
                break;
            }
            else
            {
                TotalDays -= DaysInMonth;
            }

        }

        _Day = RemainderDays;
        _Month = i;
        _Year = Year;

        _Date = to_string(_Day) + '/' + to_string(_Month) + '/' + to_string(_Year);
    }

    static string GetSystemDateTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
            + to_string(Hour) + ":" + to_string(Minute)
            + ":" + to_string(Second));
    }

    void Print()
    {
        cout << _Date << endl;
    }

    static bool IsLeapYearOrNot(int year)
    {
        return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
    }
    bool IsLeapYearOrNot()
    {
        return IsLeapYearOrNot(_Year);
    }

    static int HowManyDaysInMonth(int nYear, int nMonth)
    {
        if (nMonth < 1 || nMonth>12)
            return 0;

        int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (nMonth == 2) ? (IsLeapYearOrNot(nYear) ? 29 : 28) : NumberOfDays[nMonth - 1];

    }
    int HowManyDaysInMonth()
    {
        return HowManyDaysInMonth(_Year, _Month);
    }

    static int HowManyDaysInYear(int nYear)
    {
        if (IsLeapYearOrNot(nYear))
        {
            return 366;
        }
        else
        {
            return 365;
        }
    }
    int HowManyDaysInYear()
    {
        return HowManyDaysInYear(_Year);
    }

    static int HowManyHoursInYear(int nDays)
    {
        return nDays * 24;
    }
    int HowManyHoursInYear()
    {
        return HowManyHoursInYear(_Day);
    }

    static int HowManyMinutesInYear(int nHours)
    {
        return nHours * 60;
    }
    int HowManyMinutesInYear()
    {
        int nHours;
        return HowManyMinutesInYear(nHours);
    }

    static int HowManySecondsInYear(int nMinutes)
    {
        return nMinutes * 60;
    }
    int HowManySecondsInYear()
    {
        int nMinutes;
        return HowManySecondsInYear(nMinutes);
    }

    static int HowManyHoursInMonth(int nYear, int nMonth)
    {
        return HowManyDaysInMonth(nYear, nMonth) * 24;
    }
    int HowManyHoursInMonth()
    {
        return HowManyHoursInMonth(_Year, _Month);
    }

    static int HowManyMinutesInMonth(int nYear, int nMonth)
    {
        return HowManyHoursInMonth(nYear, nMonth) * 60;
    }
    int HowManyMinutesInMonth()
    {
        return HowManyMinutesInMonth(_Year, _Month);
    }

    static int HowManySecondsInMonth(int nYear, int nMonth)
    {
        return HowManyMinutesInMonth(nYear, nMonth) * 60;
    }
    int HowManySecondsInMonth()
    {
        return HowManySecondsInMonth(_Year, _Month);
    }

    static int GregorianWeekDay(int year, int month, int day)
    {
        int a = (14 - month) / 12;
        int y = year - a;
        int m = month + (12 * a) - 2;

        int d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

        return d;
    }
    int GregorianWeekDay()
    {
        return GregorianWeekDay(_Year, _Month, _Day);
    }

    static void PrintDayName_DayOrder(int year, int month, int day)
    {
        string weekDays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        int NumberofDay = GregorianWeekDay(year, month, day);

        cout << endl;
        cout << "Day Order :" << NumberofDay << endl;
        cout << "Day Name  :" << weekDays[NumberofDay] << endl;
    }
    void PrintDayName_DayOrder()
    {
        PrintDayName_DayOrder(_Year, _Month, _Day);
    }

    static void MonthCalendar(int year, int month)
    {
        string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        int NumberOfDays = HowManyDaysInMonth(year, month);
        int WeekDay = GregorianWeekDay(year, month, 1);

        cout << endl << "  " << string(15, '_') << months[month - 1] << string(15, '_') << endl;
        cout << endl << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue"
            << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;

        int c = 0;

        for (int i = 0; i < WeekDay; i++)
        {
            cout << setw(5) << " ";
            c++;
        }

        for (int i = 1; i <= NumberOfDays; i++)
        {
            cout << setw(5) << i;
            c++;
            if (c == 7)
            {
                c = 0;
                cout << endl;
            }
        }

        cout << endl << "  " << string(33, '_') << endl;

    }
    void MonthCalendar()
    {
        MonthCalendar(_Year, _Month);
    }

    static void YearCalendar(int year)
    {
        for (int i = 1; i <= 12; i++)
        {
            MonthCalendar(year, i);
        }

    }
    void YearCalendar()
    {
        YearCalendar(_Year);
    }

    static int TotalDaysFromBeginningYear(int year, int month, int day)
    {
        int TotalDays = 0;
        for (int i = 1; i < month;i++)
        {
            TotalDays = TotalDays + HowManyDaysInMonth(year, i);
        }
        TotalDays = TotalDays + day;

        return TotalDays;
    }
    int TotalDaysFromBeginningYear()
    {
        return TotalDaysFromBeginningYear(_Year, _Month, _Day);
    }

    static void ConvertTotalDaysToDate(int TotalDays, int year)
    {
        cout << "Date for [" << TotalDays << "] is: ";

        int RemainderDays = 0;
        int i = 0;

        while (TotalDays > 0)
        {
            i++;

            short DaysInMonth = HowManyDaysInMonth(year, i);

            if (TotalDays <= DaysInMonth)
            {
                RemainderDays = TotalDays;
                break;
            }
            else
            {
                TotalDays -= DaysInMonth;
            }

        }

        cout << RemainderDays << '/' << i << '/' << year;

    }
    void ConvertTotalDaysToDate()
    {
        ConvertTotalDaysToDate(TotalDaysFromBeginningYear(), _Year);
    }

    static void AfterAddDays_ConvertTotalDaysToDate(int year, int month, int day)
    {
        int AddDays;
        cout << "\nHow many days to add? ";
        cin >> AddDays;

        cout << "\nDate after adding [" << AddDays << "] days is: ";

        for (int i = AddDays; i > 0; i--)
        {
            if (day == HowManyDaysInMonth(year, month))
            {
                month++;
                day = 1;

                if (month == 13)
                {
                    year++;
                    month = 1;
                }

            }
            else
            {
                day++;
            }

        }

        cout << day << '/' << month << '/' << year;

    }
    void AfterAddDays_ConvertTotalDaysToDate()
    {
        AfterAddDays_ConvertTotalDaysToDate(_Year, _Month, _Day);
    }

    static string IsDate1LessThanOrNotOrEqualDate2(clsDate Date1, clsDate Date2)
    {
        if (Date1._Year < Date2._Year ||
            (Date1._Year == Date2._Year && Date1._Month < Date2._Month) ||
            (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day < Date2._Day))
        {
            return "Yes, Date1 is Less than Date2.";
        }
        else if (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day)
        {
            return "Date1 is equal to Date2.";
        }
        else
        {
            return "No, Date1 is not Less than Date2.";
        }

    }
    string IsDate1LessThanOrNotOrEqualDate2(clsDate Date2)
    {
        return IsDate1LessThanOrNotOrEqualDate2(*this, Date2);
    }

    static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2)
    {
        return  (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ?
            (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ?
                Date1._Day < Date2._Day : false)) : false);

    }
    bool IsDate1LessThanDate2(clsDate Date2)
    {
        return IsDate1LessThanDate2(*this, Date2);
    }

    static string IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        if (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day)
        {
            return "Yes, Date1 is Equal to Date2.";
        }
        else
        {
            return "No, Date1 is NOT Equal to Date2.";
        }

    }
    string IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2boolian(clsDate Date1, clsDate Date2)
    {
        if (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    bool IsDate1EqualDate2boolian(clsDate Date2)
    {
        return IsDate1EqualDate2boolian(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return Date._Day == HowManyDaysInMonth(Date._Year, Date._Month);
    }
    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(clsDate Date)
    {
        return Date._Month == 12;
    }
    bool IsLastMonthInYear()
    {
        return IsLastMonthInYear(*this);
    }

    static void IncreaseDateByOneDay(clsDate Date)
    {
        cout << "Date after adding one day is: ";

        if (Date._Day == HowManyDaysInMonth(Date._Year, Date._Month))
        {
            Date._Day = 1;
            Date._Month++;

            if (Date._Month == 13)
            {
                Date._Month = 1;
                Date._Year++;
            }
        }
        else
        {
            Date._Day++;
        }

        cout << Date._Day << '/' << Date._Month << '/' << Date._Year << endl;
    }
    void IncreaseDateByOneDay()
    {
        IncreaseDateByOneDay(*this);
    }

    static clsDate IncreaseDateByOneDayInClass(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date))
            {
                Date._Month = 1;
                Date._Day = 1;
                Date._Year++;
            }
            else
            {
                Date._Day = 1;
                Date._Month++;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }
    clsDate IncreaseDateByOneDayInClass()
    {
        return IncreaseDateByOneDayInClass(*this);
    }

    static int CalculateDiffrenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;

        while (IsDate1LessThanDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDayInClass(Date1);

        }

        return (IncludeEndDay) ? ++Days : Days;

    }
    int CalculateDiffrenceBetweenTwoDates(clsDate Date2, bool IncludeEndDay = false)
    {
        return CalculateDiffrenceBetweenTwoDates(*this, Date2, IncludeEndDay);
    }

    static clsDate CurrentDate()
    {
        clsDate NowDate;

        time_t t = time(0);

        tm* now = localtime(&t);

        NowDate._Year = now->tm_year + 1900;
        NowDate._Month = now->tm_mon + 1;
        NowDate._Day = now->tm_mday;

        return NowDate;
    }

    static void YourAgeInDays(clsDate Date1, clsDate Date2)
    {
        cout << "\nYour Age is : " << CalculateDiffrenceBetweenTwoDates(Date1, Date2) << " Day(s).";
    }
    void YourAgeInDays(clsDate Date1)
    {
        YourAgeInDays(Date1, *this);
    }

    void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate;

        TempDate._Year = Date1._Year;
        TempDate._Month = Date1._Month;
        TempDate._Day = Date1._Day;

        Date1._Year = Date2._Year;
        Date1._Month = Date2._Month;
        Date1._Day = Date2._Day;

        Date2._Year = TempDate._Year;
        Date2._Month = TempDate._Month;
        Date2._Day = TempDate._Day;
    }

    int DiffrenceDays2Dates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1LessThanDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1LessThanDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDayInClass(Date1);
        }

        return (IncludeEndDay) ? ++Days * SwapFlagValue : Days * SwapFlagValue;
    }

    static clsDate IncreaseDateBy10Days(clsDate Date)
    {
        for (int i = 1; i <= 10; i++)
        {
            Date = IncreaseDateByOneDayInClass(Date);
        }

        return Date;
    }
    clsDate IncreaseDateBy10Days()
    {
        return IncreaseDateBy10Days(*this);
    }

    static clsDate IncreaseDateByOneWeek(clsDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = IncreaseDateByOneDayInClass(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByOneWeek()
    {
        return IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate Date, short Weeks)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByXWeeks(short Weeks)
    {
        return IncreaseDateByXWeeks(*this, Weeks);
    }

    static clsDate IncreaseDateByOneMonth(clsDate Date)
    {
        if (IsLastMonthInYear(Date))
        {
            Date._Month = 1;
            Date._Year++;
        }
        else
        {
            Date._Month++;
        }

        if (Date._Day > HowManyDaysInMonth(Date._Year, Date._Month))
        {
            Date._Day = HowManyDaysInMonth(Date._Year, Date._Month);
        }

        return Date;
    }
    clsDate IncreaseDateByOneMonth()
    {
        return IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(clsDate Date, short Months)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByXMonths(short Months)
    {
        return IncreaseDateByXMonths(*this, Months);
    }

    static clsDate IncreaseDateByOneYear(clsDate Date)
    {
        Date._Year++;

        return Date;
    }
    clsDate IncreaseDateByOneYear()
    {
        return IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(clsDate Date, short Years)
    {
        for (int i = 1; i <= Years; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByXYears(short Years)
    {
        return IncreaseDateByXYears(*this, Years);
    }

    static clsDate IncreaseDateByXYears_Faster(clsDate Date, short Years)
    {
        Date._Year += Years;

        return Date;
    }
    clsDate IncreaseDateByXYears_Faster(short Years)
    {
        return IncreaseDateByXYears_Faster(*this, Years);
    }

    static clsDate IncreaseDateByOneDecade(clsDate Date)
    {
        Date._Year += 10;

        return Date;
    }
    clsDate IncreaseDateByOneDecade()
    {
        return IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(clsDate Date, short Decades)
    {
        for (int i = 1; i <= Decades; i++)
        {
            Date = IncreaseDateByOneDecade(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByXDecades(short Decades)
    {
        return IncreaseDateByXDecades(*this, Decades);
    }

    static clsDate IncreaseDateByXDecade_Faster(clsDate Date, short Decades)
    {
        Date._Year += 10 * Decades;

        return Date;
    }
    clsDate IncreaseDateByXDecade_Faster(short Decades)
    {
        return IncreaseDateByXDecade_Faster(*this, Decades);
    }

    static clsDate IncreaseDateByOneCentury(clsDate Date)
    {
        Date._Year += 100;

        return Date;
    }
    clsDate IncreaseDateByOneCentury()
    {
        return IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate Date)
    {
        for (int i = 1; i <= 10; i++)
        {
            Date = IncreaseDateByOneCentury(Date);
        }

        return Date;
    }
    clsDate IncreaseDateByOneMillennium()
    {
        return IncreaseDateByOneMillennium(*this);
    }

    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date._Day == 1)
        {
            if (Date._Month == 1)
            {
                Date._Day = 31;
                Date._Month = 12;
                Date._Year--;
            }
            else
            {
                Date._Month--;
                Date._Day = HowManyDaysInMonth(Date._Year, Date._Month);
            }
        }
        else
        {
            Date._Day--;
        }

        return Date;
    }
    clsDate DecreaseDateByOneDay()
    {
        return DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(clsDate Date, short Days)
    {
        for (int i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByXDays(short Days)
    {
        return DecreaseDateByXDays(*this, Days);
    }

    static clsDate DecreaseDateByOneWeek(clsDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByOneWeek()
    {
        return DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(clsDate Date, short Weeks)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByXWeeks(short Weeks)
    {
        return DecreaseDateByXWeeks(*this, Weeks);
    }

    static clsDate DecreaseDateByOneMonth(clsDate Date)
    {
        if (Date._Month == 1)
        {
            Date._Month = 12;
            Date._Year--;
        }
        else
        {
            Date._Month--;
        }

        if (Date._Day > HowManyDaysInMonth(Date._Year, Date._Month))
        {
            Date._Day = HowManyDaysInMonth(Date._Year, Date._Month);
        }

        return Date;
    }
    clsDate DecreaseDateByOneMonth()
    {
        return DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(clsDate Date, short Months)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByXMonths(short Months)
    {
        return DecreaseDateByXMonths(*this, Months);
    }

    static clsDate DecreaseDateByOneYear(clsDate Date)
    {
        Date._Year--;

        return Date;
    }
    clsDate DecreaseDateByOneYear()
    {
        return DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(clsDate Date, short Years)
    {
        for (int i = 1; i <= Years; i++)
        {
            Date = DecreaseDateByOneYear(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByXYears(short Years)
    {
        return DecreaseDateByXYears(*this, Years);
    }

    static clsDate DecreaseDateByXYears_Faster(clsDate Date, short Years)
    {
        Date._Year -= Years;

        return Date;
    }
    clsDate DecreaseDateByXYears_Faster(short Years)
    {
        return DecreaseDateByXYears_Faster(*this, Years);
    }

    static clsDate DecreaseDateByOneDecade(clsDate Date)
    {
        Date._Year -= 10;

        return Date;
    }
    clsDate DecreaseDateByOneDecade()
    {
        return DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(clsDate Date, short Decades)
    {
        for (int i = 1; i <= Decades; i++)
        {
            Date = DecreaseDateByOneDecade(Date);
        }

        return Date;
    }
    clsDate DecreaseDateByXDecades(short Decades)
    {
        return DecreaseDateByXDecades(*this, Decades);
    }

    static clsDate DecreaseDateByXDecade_Faster(clsDate Date, short Decades)
    {
        Date._Year -= 10 * Decades;

        return Date;
    }
    clsDate DecreaseDateByXDecade_Faster(short Decades)
    {
        return DecreaseDateByXDecade_Faster(*this, Decades);
    }

    static clsDate DecreaseDateByOneCentury(clsDate Date)
    {
        Date._Year -= 100;

        return Date;
    }
    clsDate DecreaseDateByOneCentury()
    {
        return DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate Date)
    {
        Date._Year -= 1000;

        return Date;
    }
    clsDate DecreaseDateByOneMillennium()
    {
        return DecreaseDateByOneMillennium(*this);
    }

    enum enCompareDate { Before = -1, Equal = 0, After = 1 };
    static enCompareDate CompareDate(clsDate Date1, clsDate Date2)
    {
        if (IsDate1EqualDate2boolian(Date1, Date2))
        {
            return enCompareDate::Equal;
        }
        else if (IsDate1LessThanDate2(Date1, Date2))
        {
            return enCompareDate::Before;
        }
        else
        {
            return enCompareDate::After;
        }

    }
    enCompareDate CompareDate(clsDate Date2)
    {
        return CompareDate(*this, Date2);
    }

    static bool IsValidateDate(clsDate Date)
    {
        if (Date._Day <= 0 || Date._Month <= 0 || Date._Year <= 0)
        {
            return false;
        }

        if (Date._Day > HowManyDaysInMonth(Date._Year, Date._Month) || Date._Month > 12)
        {
            return false;
        }

        return true;
    }
    bool IsValidateDate()
    {
        return IsValidateDate(*this);
    }



};