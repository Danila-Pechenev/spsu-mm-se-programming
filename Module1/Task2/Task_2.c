#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#define CLI_BUFFER_SIZE 12

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
    if (a > 0 && b > 0 && c > 0)
    {

        if (pow(a, 2) + pow(b, 2) == pow(c, 2))
        {
            return true;
        }
    }
    return false;
}

bool check_error(int *value)
{
    size_t length = 0;
    char* end = NULL;
    char buf[CLI_BUFFER_SIZE] = "";



    fflush(stdout);


    if (!fgets(buf, sizeof(buf), stdin)) {
        return false;
    }

    
    length = strlen(buf);
    if (buf[length - 1] == '\n') 
    {
        buf[--length] = '\0';

      
        errno = 0;
        *value = strtod(buf, &end);

    
        if (length == 0) {
            printf("������: ������� ������ ������.\n");
            return false;
        }
        if (errno != 0 || *end != '\0') {
            printf("������: ������������ ������.\n");
            printf("\t%s\n", buf);
            printf("\t%*c\n", (int)(end - buf) + 1, '^');
            
            return false;
        }

        if (INT_MAX<*value || INT_MIN >= *value)
        {
            printf("������: ������������� ������������ ��������� .\n");
            return false;
        }
            
    }
    else 
    {
        scanf("%*[^\n]");
        scanf("%*c");
        printf("������: �� ������� ������ ��� %d �������(��).\n", CLI_BUFFER_SIZE-2);

        return false;
    }

    return true;
}

void check_enter(int *cislo)
{
    bool status = false;
   
    do {
        status = check_error(cislo);
        if (!status) {
            printf("����������, ���������� ��� ���.\n");
        }
    } while (!status);
}



int main()
{
    system("chcp 1251");
    system("cls");
    int a = 0 , b =0 , c = 0 ;

    printf("����������, ������� ������ ����������� �����: \n");
    printf("a = "); check_enter(&a);
    printf("b = "); check_enter(&b);
    printf("c = "); check_enter(&c);
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

