#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <stdbool.h>


bool CheckTangle(double* angle)
{
    if (angle[0] > 0 && angle[1] > 0 && angle[2] > 0)
    {
        if (angle[0] + angle[1] > angle[2] && angle[0] + angle[2] > angle[1] && angle[2] + angle[1] > angle[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
double Result_angle(double a, double b, double c)
{
    return acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b)) * 180 / M_PI;
}
int main()
{
    double  angle[3];
    bool error = false;
    system("chcp 1251");
    system("cls");

    printf("����������, ������� 3 ������� ������������: \n");
    for (int i = 0; i < 3; i++)
    {
        printf("������� �������� ������� � %d -", i); scanf("%lf", &angle[i]);
    }

    if (CheckTangle(angle))
    {
        double a = 0, b = 0, c = 0;
        a = angle[0];
        b = angle[1];
        c = angle[2];

        printf("���� � 1 - %.2lf \n", Result_angle(a, c, b));
        printf("���� � 2 - %.2lf \n", Result_angle(a, b, c));
        printf("���� � 3 - %.2lf \n", Result_angle(b, c, a));
    }
    else
    {
        printf("� ���������, ��������� ������������� ����������� � ���������� ��������� ����������!");
    }
    return 0;
}
