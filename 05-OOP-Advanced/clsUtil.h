#pragma once
#pragma warning(disable : 4996)

#include<iostream>
#include<string>
#include "clsDate.h"

using namespace std;

class clsUtil
{


public:

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int from, int to)
    {

        int Randomnum = rand() % (to - from + 1) + from;

        return Randomnum;
    }

    static enum enCharType { small_letters = 1, capital_letters = 2, special_character = 3, digit = 4, MixChars = 5 };
    static char GetRandomCharacter(enCharType type)
    {
        char rsl = clsUtil::RandomNumber(97, 122);
        char rcl = clsUtil::RandomNumber(65, 90);
        char rsc = clsUtil::RandomNumber(33, 38);
        char rd = clsUtil::RandomNumber(48, 57);

        short rMC;
        do {
            rMC = clsUtil::RandomNumber(enCharType::small_letters, enCharType::digit);
        } while (rMC == enCharType::special_character);


        if (type == enCharType::small_letters)
        {
            return rsl;
        }
        else if (type == enCharType::capital_letters)
        {
            return rcl;
        }
        else if (type == enCharType::special_character)
        {
            return rsc;
        }
        else if (type == enCharType::digit)
        {
            return rd;
        }
        else if (type == enCharType::MixChars)
        {
            clsUtil::GetRandomCharacter((enCharType)rMC);
        }

    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int i = 1; i <= Length; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void Swap(int& num1, int& num2)
    {
        int temp1 = num1;
        num1 = num2;
        num2 = temp1;
    }

    static void Swap(double& num1, double& num2)
    {
        double temp1 = num1;
        num1 = num2;
        num2 = temp1;
    }

    static void Swap(string& s1, string& s2)
    {
        string temp1 = s1;
        s1 = s2;
        s2 = temp1;
    }

    static void Swap(clsDate& d1, clsDate& d2)
    {
        clsDate temp1 = d1;
        d1 = d2;
        d2 = temp1;
    }

    static void ShuffleArrays(int arr[100], int arrlength)
    {
        for (int i = 0; i < arrlength;i++)
        {
            Swap(arr[RandomNumber(1, arrlength) - 1], arr[RandomNumber(1, arrlength) - 1]);
        }
    }

    static void ShuffleArrays(string arr[100], int arrlength)
    {
        for (int i = 0; i < arrlength;i++)
        {
            Swap(arr[RandomNumber(1, arrlength) - 1], arr[RandomNumber(1, arrlength) - 1]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int numarrays, int from, int to)
    {
        for (int i = 0; i < numarrays;i++)
        {
            arr[i] = RandomNumber(from, to);
        }
        cout << "\n";
    }

    static void FillArrayWithRandomWords(string arr[100], int numarrays, enCharType CharType, int to)
    {
        for (int i = 0; i < numarrays;i++)
        {
            arr[i] = GenerateWord(CharType, to);
        }
        cout << "\n";
    }

    static void FillArrayWithRandomKeys(string arr[100], int numarrays, enCharType CharType)
    {
        for (int i = 0; i < numarrays;i++)
        {
            arr[i] = GenerateKey(CharType);
        }
        cout << "\n";
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i <= Text.length();i++)
        {
            Text[i] += EncryptionKey;
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i <= Text.length();i++)
        {
            Text[i] -= EncryptionKey;
        }

        return Text;
    }

    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }

    }



};