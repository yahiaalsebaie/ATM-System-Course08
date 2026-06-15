#pragma once
#include <iostream>
#include <iomanip> // For setw()
#include "MyMathLib.h" // For CheckPrime
#include "MyUtilityLib.h" // For FillMatrixWithRandomNumbers

namespace MyArrayLib {
    void AddArrayElement(int Number, int arr[100], int& arrLength) {
        arr[arrLength] = Number;
        arrLength++;
    }

    void PrintArray(int arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
    void PrintArray(int arr[], int arrLength, short ZeroFormat = 2)
    {
        for (int i = 0; i < arrLength; i++)
            printf(" %0*d \t", ZeroFormat, arr[i]);

        cout << "\n";
    }

    bool IsNumberInArray(int arr[100], int NumberToSearch, int arrLength) {
        for (int i = 0; i < arrLength; i++)
            if (arr[i] == NumberToSearch) return true;
        return false;
    }

    void CopyDistinctNumbersToArray(int arrSource[100], int arrDest[100], int srcLen, int& destLen) {
        destLen = 0;
        for (int i = 0; i < srcLen; i++) {
            if (!IsNumberInArray(arrDest, arrSource[i], destLen)) {
                AddArrayElement(arrSource[i], arrDest, destLen);
            }
        }
    }

    bool IsPalindromeArray(int arr[100], int arrLength) {
        for (int i = 0; i < arrLength / 2; i++)
            if (arr[i] != arr[arrLength - i - 1]) return false;
        return true;
    }

    void ShuffleArray(int arr[100], int arrLength) {
        for (int i = 0; i < arrLength; i++) {
            std::swap(arr[i], arr[rand() % arrLength]);
        }
    }

    void FillMatrixWithRandomNumbers(int arr[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                arr[i][ii] = MyUtilityLib::RandomNumber(1, 100);
            }
        }
    }
    void FillMatrixWithRandomNumbers(int arr[3][3], short rows, short cols, short From = 1, short To = 100)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                arr[i][ii] = MyUtilityLib::RandomNumber(From, To);
            }
        }
    }

    void PrintMatrix(int arr[3][3], int rows, int cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                cout << setw(3) << arr[i][ii] << "\t";
            }
            cout << endl;
        }
    }
    int RowSum(int arr[3][3], short rows, short cols)
    {
        int sum = 0;
        for (short i = 0; i < cols; i++)
        {
            sum += arr[rows][i];
        }
        return sum;
    }
    void PrintEachRowSum(int arr[3][3], short Rows, short Cols)
    {
        cout << "\nThe the following are the sum of each row in the matrix:\n";
            for (short i = 0; i < Rows; i++)
            {
                cout << " Row " << i + 1 << " Sum = " << RowSum(arr, i,Cols) << endl;
            }
    }

    void FillSumMatrixRowsInArray(int arr[3][3], int arrSum[3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            arrSum[i] = RowSum(arr, i, cols);
        }
    }

    void PrintRowsSumArray(int arrSum[3], short row)
    {
        cout << "\nSum row numbers:\n";

        for (short i = 0; i < row; i++)
        {
            cout << "Row " << i + 1 << " Sum = " << arrSum[i] << endl;
        }
    }

    int ColSum(int arr[3][3], short rows, short colNumber)
    {
        int sum = 0;
        for (short i = 0; i < rows; i++)
        {
            sum += arr[i][colNumber];
        }
        return sum;
    }


    void FillSumMatrixColsInArray(int arr[3][3], int arrSum[3], short rows, short cols)
    {
        for (short i = 0; i < cols; i++)
        {
            arrSum[i] = ColSum(arr, rows, i);
        }
    }

    void PrintColsSumArray(int arrSum[3], short colLength)
    {
        cout << "\nSum cols numbers:\n";
        for (short i = 0; i < colLength; i++)
        {
            cout << "Col " << i + 1 << " Sum = " << arrSum[i] << endl;
        }
    }
    void FillMatrixWithOrderedNumbers(int arr[3][3], short Rows, short Cols)
    {
        short Counter = 0;
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                Counter++;
                arr[i][j] = Counter;
            }
        }
    }

    void TransposeMatrix(int arr[3][3], int arr2[3][3], int rows, int cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                arr2[ii][i] = arr[i][ii];
            }
        }
    }

    void PrintMatrix(int arr[3][3], int rows, int cols, short ZeroFormat = 2)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                printf(" %0*d \t", ZeroFormat, arr[i][ii]);
                //cout << setw(3) << arr[i][ii] << "\t";
            }
            cout << endl;
        }
    }
    void FillOrderedMatrix(int arr[3][3], int rows, int cols)
    {
        short Counter = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                Counter++;
                arr[i][ii] = Counter;
            }
        }
    }
    void FillArrayWithResultOfMultiply2Matrices(int arr[3][3], int arr2[3][3], int arrResult[3][3], int rows, int cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                arrResult[i][ii] = arr2[i][ii] * arr[i][ii];
            }
        }
    }
    void GetMatrixMiddleRow(int arr[3][3], int arrMiddleRow[3], short rows, short cols)
    {
        short rowsMid = floor(rows / 2), colsMid = floor(cols / 2);
        for (short i = 0; i < rows; i++)
        {
            arrMiddleRow[i] = arr[rowsMid][i];
        }
    }
    void GetMatrixMiddleCol(int arr[3][3], int arrMiddleCol[3], short rows, short cols)
    {
        short rowsMid = floor(rows / 2), colsMid = floor(cols / 2);
        for (short i = 0; i < rows; i++)
        {
            arrMiddleCol[i] = arr[i][colsMid];
        }
    }
    void GetMatrixMiddleRowAndCol(int arr[3][3], int arrMiddle[3], short rows, short cols, bool isRow)
    {
        short rowsMid = floor(rows / 2), colsMid = floor(cols / 2);

        if (isRow)
            for (short i = 0; i < rows; i++)
                arrMiddle[i] = arr[rowsMid][i];
        else
            for (short i = 0; i < rows; i++)
                arrMiddle[i] = arr[i][colsMid];
    }

    int SumMatrixNumbers(int arr[3][3], short rows, short cols)
    {
        int Sum = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                Sum += arr[i][ii];
            }
        }
        return Sum;
    }
    bool areMatricesEquals(int matrix1[3][3], int matrix2[3][3],short rows,short cols)
    {
        return SumMatrixNumbers(matrix1, rows, cols) == SumMatrixNumbers(matrix2, rows, cols);
    }

    bool areMatricesTypical(int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                if (matrix1[i][ii] != matrix2[i][ii]) return false;
            }
        }
        return true;
    }
    void FillIdentityMatrix(int matrix[3][3], short length)
{
	for (short i = 0; i < length; i++)
	{
		for (short ii = 0; ii < length ; ii++)
		{
			matrix[i][ii] = 0;
		}
		matrix[i][i] = 1;
	}
}

    bool isIdentityMatrix(int matrix1[3][3], short length)
    {
        int IdentityMatrix[3][3];
        FillIdentityMatrix(IdentityMatrix, length);
        return areMatricesTypical(matrix1, IdentityMatrix, length, length);
    }
    bool isIdentityMatrix(int matrix1[3][3], int rows, int cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                //chk diagonal
                if (i == ii && matrix1[i][ii] != 1) return false;
                //chk other elements
                if (i != ii && matrix1[i][ii] != 0) return false;
            }
        }
        return true;
    }
   
    bool isScalarMatrix(int matrix1[3][3], int rows, int cols)
    {
        int ScalarNumber = matrix1[0][0];
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                //chk diagonal
                if (i == ii && matrix1[i][ii] != ScalarNumber) return false;
                //chk other elements
                else if (i != ii && matrix1[i][ii] != 0) return false;
            }
        }
        return true;
    }
    short CountNumberInMatrix(int matrix[3][3], int NumberToCount, short rows, short cols)
    {
        short Count = 0;
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
                if (matrix[i][ii] == NumberToCount) Count++;
        }
        return Count;
    }
    bool isSparseMatrix(int matrix[3][3], short rows, short cols)
    {
        //المصفوفة الـ Sparse: هي اللي عدد الأصفار فيها "أكثر" من عدد الأرقام التانية.
        short matrixSize = rows * cols;
        short zerosCount = CountNumberInMatrix(matrix, 0, rows, cols);
        short OtherNumbersCount = matrixSize - zerosCount;
        return (zerosCount > OtherNumbersCount);
    }
    
    bool isNumberInMatrix(int matrix[3][3], int NumberToFind, short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
                if (matrix[i][ii] == NumberToFind) return true;
        }
        return false;
    }
    void PrintIntersectedNumbers(int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            for (short ii = 0; ii < cols; ii++)
            {
                if (isNumberInMatrix(matrix1, matrix2[i][ii], rows, cols))
                    cout << setw(3) << matrix2[i][ii] << "\t";
            }
        }
    }
    int MinimumNumberInMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int Min = Matrix[0][0];
        for (short i = 0; i < Rows; i++)
        {
            for (short ii = 0; ii < Cols; ii++)
            {
                if (Min > Matrix[i][ii]) Min = Matrix[i][ii];
            }
        }
        return Min;
    }
    int MaximumNumberInMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int Max = Matrix[0][0];
        for (short i = 0; i < Rows; i++)
        {
            for (short ii = 0; ii < Cols; ii++)
            {
                if (Max < Matrix[i][ii]) Max = Matrix[i][ii];
            }
        }
        return Max;
    }
    void GetMinAndMaxInMatrix(int Matrix[3][3], short Rows, short Cols, int& Min, int& Max)
    {
        Max = Matrix[0][0];
        Min = Matrix[0][0];
        for (short i = 0; i < Rows; i++)
        {
            for (short ii = 0; ii < Cols; ii++)
            {
                if (Max < Matrix[i][ii]) Max = Matrix[i][ii];
                if (Min > Matrix[i][ii]) Min = Matrix[i][ii];
            }
        }
    }
    pair <int, int> GetMinAndMaxInMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int Max = Matrix[0][0];
        int Min = Matrix[0][0];
        for (short i = 0; i < Rows; i++)
        {
            for (short ii = 0; ii < Cols; ii++)
            {
                if (Max < Matrix[i][ii]) Max = Matrix[i][ii];
                if (Min > Matrix[i][ii]) Min = Matrix[i][ii];
            }
        }
        return{ Min,Max };

        //How to call:
    /*pair<int,int> Result = GetMinAndMaxInMatrix(Matrix1, 3, 3);

    cout << "\n\nMinimum number is : " << Result.first;
    cout << "\n\nMaximum number is : " << Result.second;*/

    /*
    auto [Mini, Maxi] = GetMinAndMaxInMatrix(Matrix1, 3, 3);
    cout << "Min: " << Mini << " Max: " << Maxi;
    */
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




}