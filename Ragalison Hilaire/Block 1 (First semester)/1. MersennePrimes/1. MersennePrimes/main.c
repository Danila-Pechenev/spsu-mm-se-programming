
/*Name and first name : Ragalison Hilaire ;
  adress email: st085683@student.spbu.ru ;
  ���� ������: ������� �� ����� ��� ������� ����� �������� �� ������� [1; 2^31 -1] */


#include <stdio.h>
#include <math.h>
#include "checkPrimeNumbers.h"


int main()
{
    int a = 0;
    double b = 0, c = 0;

    for (a = 1; a <= 31; a++) //�� ������� [1; 2^31 -1].
    {

        b = pow(2, a);//����� a - �������, b - 2 � ������� a.
        c = b - 1; //����������� c - ��������� ����� ��������.

        if (isPrime(c) == 1)
        {
            printf("\n   2^%d = %f", a, b);
            printf("\n *** Mersenne number is equal to : %f ***\n", c);
            printf("\4-->   %f IS a Mersenne prime. \n\n", c);
        }

        /*
        else if (isPrime(c) == 0)
        {
            printf(" --> %f is NOT a Mersenne prime. \n\n", c);
        };
        */

    }

    return 0;
}

