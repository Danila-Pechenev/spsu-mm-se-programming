#define _USE_MATH_DEFINES
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define bufer_size  10

bool check_tangle(double a, double b, double c)
{

	if (a > 0 && b > 0 && c > 0)
	{

		if (a + b > c && a + c > b && c + b > a)
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

double result_angle(double a, double b, double c)
{
	return acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b)) * 180 / M_PI;
}

bool check_error(double* value)
{
	size_t length = 0;
	char* end = NULL;
	char buf[bufer_size] = "";

	fflush(stdout);

	if (!fgets(buf, sizeof(buf), stdin))
	{
		return false;
	}


	length = strlen(buf);

	if (buf[length - 1] == '\n')
	{
		buf[--length] = '\0';


		errno = 0;
		*value = strtod(buf, &end);


		if (length == 0)
		{
			printf("������: ������� ������ ������.\n");
			return false;
		}

		if (errno != 0 || *end != '\0')
		{
			printf("������: ������������ ������.\n");
			printf("\t%s\n", buf);
			printf("\t%*c\n", (int)(end - buf) + 1, '^');

			return false;
		}

		if (*value < 0)
		{
			printf("������: ������� ������������� ����.\n");
			return false;
		}

	}
	else
	{
		scanf_s("%*[^\n]");
		scanf_s("%*c");
		printf("������: �� ������� ������ ��� %d �������(��).\n", bufer_size - 2);

		return false;
	}

	return true;
}

void check_enter(double* cislo)
{
	bool status = false;

	do
	{

		status = check_error(cislo);

		if (!status)
		{
			printf("����������, ���������� ��� ���.\n");
		}

	} while (!status);
}

void translete_in_the_normal_angle(double znach)
{
	int a = 0, b = 0, c = 0;

	a = (int)(znach);
	b = (int)((znach - (double)a) * 60);
	c = (int)(((znach - (double)a) * 60 - b) * 60);

	printf("%d(��); %d(���); %d(���);\n", a, b, c);
}

int main()
{

	double a = 0, b = 0, c = 0;

	bool error = false;
	system("chcp 1251");
	system("cls");

	printf("����������, ������� 3 ������� ������������: \n");
	printf("������� �������� ������� � 1: "); check_enter(&a);
	printf("������� �������� ������� � 2: "); check_enter(&b);
	printf("������� �������� ������� � 3: "); check_enter(&c);


	if (check_tangle(a, b, c))
	{
		double a1 = 0, b1 = 0, c1 = 0;

		a1 = result_angle(a, c, b);
		b1 = result_angle(a, b, c);
		c1 = result_angle(b, c, a);


		printf("���� � 1 - %.2lf ����� ����������� � ����: ", a1);  translete_in_the_normal_angle(a1);
		printf("���� � 2 - %.2lf ����� ����������� � ����: ", b1);  translete_in_the_normal_angle(b1);
		printf("���� � 3 - %.2lf ����� ����������� � ����: ", c1);  translete_in_the_normal_angle(c1);

	}
	else
	{
		printf("\n �����: � ���������, ��������� ������������� ����������� � ���������� ��������� ����������! \n");
	}
	return 0;
}
