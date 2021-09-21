#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <stdbool.h>

bool check_number(int number)
{
    for (int i = 2; i < sqrt(number) + 1; i++) {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool check_Pifagor(int a, int b, int c)
{
    if (pow(a, 2) + pow(b, 2) == pow(c, 2))
    {
        return true;
    }
    return false;
}


int main()
{
    system("chcp 1251");
    system("cls");
    int a = 0, b = 0, c = 0;

    printf("����������, ������� ������ ����������� �����: \n");
    printf("a = "); scanf("%d", &a);
    printf("b = "); scanf("%d", &b);
    printf("c = "); scanf("%d", &c);

    printf("��������� ������ ��������� ��������: \n");

    if (check_Pifagor(a, b, c))
    {
        printf("1. ��, �������� ������ ����������� ����� (a,b,c) ������������� ������� x^2 + y^2 = z^2.\n");
        printf("���������: %d^2 + %d^2 = %d^2 \n", a, b, c);

        if (check_number(a) && check_number(b) && check_number(c))
        {
            printf("2. ��, �������� ������ ����������� ����� (a,b,c) �������� �������� ����������� �������\n");
        }
        else
        {
            printf("2. ���, �������� ������ ����������� ����� (a,b,c) �� �������� �������� ����������� �������\n");
        }
    }
    else
    {
        printf("1. ���, �������� ������ ����������� ����� (a,b,c) �� ������������� ������� x^2 + y^2 = z^2.\n");
        printf("���������: %d^2 + %d^2 <> %d^2", a, b, c);
    }




    return 0;
}

