#pragma once
#include <iostream>
#include <cmath>

namespace MyMathLib {
    enum enPrimeOrNot { Prime = 1, NotPrime = 2 };
    enum enPerfectNumber { Perfect = 1, NotPerfect = 2 };

    enPrimeOrNot CheckPrimeNumbers(int Number) {
        if (Number <= 1) return enPrimeOrNot::NotPrime;
        int M = sqrt(Number);
        for (int Counter = 2; Counter <= M; Counter++)
            if (Number % Counter == 0) return enPrimeOrNot::NotPrime;
        return enPrimeOrNot::Prime;
    }

    bool isPerfectNumber(int Number) {
        int Sum = 0;
        for (int i = 1; i < Number; i++)
            if (Number % i == 0) Sum += i;
        return Number == Sum;
    }

    int ReverseNumber(int Number) {
        int Remainder = 0, Number2 = 0;
        while (Number > 0) {
            Remainder = Number % 10;
            Number /= 10;
            Number2 = Number2 * 10 + Remainder;
        }
        return Number2;
    }

    // --- Recursive & Math Functions ---
    int SumOfDigits(int Number) {
        if (Number == 0) return 0;
        return (Number % 10) + SumOfDigits(Number / 10); // Recursive logic
    }

    float MyABS(float Number) {
        return (Number >= 0) ? Number : Number * -1;
    }

    int MyRound(float Number) {
        return (Number > 0) ? int(Number + 0.5) : int(Number - 0.5);
    }

    int MyFloor(float Number) {
        int IntPart = (int)Number;
        return (Number >= 0 || Number == IntPart) ? IntPart : IntPart - 1;
    }

    int MyCeil(float Number) {
        int IntPart = (int)Number;
        return (Number <= 0 || Number == IntPart) ? IntPart : IntPart + 1;
    }
}