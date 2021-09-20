#include <stdio.h>
#include <locale.h>
#include <math.h>

void clear_excess_chars()
{
    char temp;
    do
    {
        temp = getchar();
    } 
    while (temp != '\n' && temp != EOF);
}

long double get_number(int counter)
{
    short success = 0;
    long double result;
    char after_number;
    do
    {
        printf("������� %d-� �����: ", counter);
        if (scanf_s("%30Lf%c", &result, &after_number, 10) != 2 || after_number != '\n')
        {
            printf("������! � ����� ����������� ������ �����. ������� ����� ����� ������ ���������� � ������� �������,\n");
            printf("� �� �����. ����� ����� �� ������ �������� ������������.\n");
            clear_excess_chars(); //���� �� ������� ������������� �����, ���������� ������ ������� �� ����. ������
        }
        else if (result <= 0)
        {
            printf("������! �������� ����� ������ ���� ������ ����\n");
        }
        else
        {
            success = 1;
        }

    } 
    while (!success);
    return result;
}

long double to_degrees(long double angle)
{
    return angle * 180.0 / 3.1415926535;
}

void calculate_angles_and_fill(long double* angles, long double first, long double second, long double third)
{
    angles[0] = to_degrees(acos((first * first + second * second - third * third) / (2.0 * first * second)));
    angles[1] = to_degrees(acos((first * first + third * third - second * second) / (2.0 * first * third)));
    angles[2] = to_degrees(acos((third * third + second * second - first * first) / (2.0 * third * second)));
}

void print_angle(long double angle)
{
    long long degrees = (long long)angle;
    long long minutes = (long long)((angle - (long long)angle) * 60.0);
    long long seconds = (long long)((angle - (long long)angle) * 3600.0) % 60;
    printf("�������: %lld ������: %lld ������� %lld\n", degrees, minutes, seconds);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("��������: ��������� �������� ��� ����� �� ������������ � �������, ����� �� � ������ ���������\n");
    printf("��������� ������������� �����������. ���� ��, �� ��������� ����� ���������� ��������� ����\n");
    printf("� ��������� �� �������, ���� ��� ��������. ��������: ��� ������ �����, ��� ������ ��������.\n");
    long double numbers[3];
    for (int i = 1; i <= 3; ++i)
    {
        numbers[i - 1] = get_number(i);
    }
    if (numbers[2] < numbers[1] + numbers[0] && numbers[1] < numbers[2] + numbers[0] && numbers[0] < numbers[1] + numbers[2])
    {
        printf("�� �������������� ������ �������� ��������� ������������� �����������. ��� ����:\n");
        long double angles[3];
        calculate_angles_and_fill(angles, numbers[0], numbers[1], numbers[2]);
        for (int i = 0; i < 3; ++i)
        {
            print_angle(angles[i]);
        }
    }
    else
    {
        printf("�������������� ����� �� ����� ���� ��������� ������������.\n");
    }


    return 0;
}
