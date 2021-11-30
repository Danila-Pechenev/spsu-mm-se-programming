#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mman.h"
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <locale.h>

int my_string_cmpr(const void* first, const void* second)
{
	return strcmp(*(char**)first, *(char**)second);
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	if (argc != 3)
	{
		printf("������! ������ ����������� �������: <��������_���������> <������� ����> <�������� ����>");
		return -1;
	}

	printf("������ ��������� ����������� ������ �� ������� �������� strcmp(������������������\n");
	printf("�������). ���� �������������� � \"%s\".\n", argv[1]);
	printf("����� �������������� � \"%s\"(���������, ���� �� ����������).\n", argv[2]);
	printf("��������: ������ ������ ����� ��������� � ����������.\n");

	// ����������� ������
	int file_in, file_out;
	// ��������� �� ������� ����
	char* source;
	// ����� ����� ����� ��������� ���������� � �������� �����
	struct stat in_file_stats;

	/*
	�������� �������������� ����� / ������ ��� ����� ������,
	���� ���������� ����� �������������, �� �������� ������,
	�������� �� ���� ������������ � ����������� ������ ���������
	*/
	file_in = open(argv[1], O_RDWR);
	if (file_in < 0)
	{
		printf("��������� ������: �� ������� ������� ������� ����\n");
		return -1;
	}

	if (fstat(file_in, &in_file_stats) < 0)
	{
		printf("��������� ������: �� ������� �������� ���������� � ������� �����");
		close(file_in);
		return -1;
	}

	file_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file_out < 0)
	{
		printf("��������� ������: �� ������� �������/������� �������� ����\n");
		close(file_in);
		return -1;
	}

	if ((source = mmap(0, in_file_stats.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, file_in, 0)) == MAP_FAILED)
	{
		printf("��������� ������: �� ������� ���������� ������� ���� �� ������");
		close(file_in);
		close(file_out);
		return -1;
	}

	long long str_count = 0;

	for (long long symbol = 0; symbol <= in_file_stats.st_size; ++symbol)
	{
		if (source[symbol] == '\n' || source[symbol] == '\0')
		{
			++str_count;
		}
	}

	// ������ � ��������� ������ �����
	char** string_array = (char**)malloc(str_count * sizeof(char*));
	int* string_lengths = (int*)malloc(str_count * sizeof(int));
	long long current_symbol = 0;

	for (long long str_number = 0; str_number < str_count; ++str_number)
	{
		long long string_length = 0;
		while (source[current_symbol + string_length] != '\0' && source[current_symbol + string_length] != '\n' && current_symbol + string_length <= in_file_stats.st_size)
		{
			++string_length;
		}
		string_array[str_number] = &source[current_symbol];
		string_array[str_number][string_length] = '\0';
		current_symbol += string_length;
		printf("str len %d\n", string_length);
		string_lengths[str_number] = string_length;
		if (source[current_symbol] == '\n' || source[current_symbol] == '\0')
		{
			++current_symbol;
		}
	}


	// ���������� ����� � ����� � ����
	qsort(string_array, str_count, sizeof(char*), my_string_cmpr);

	for (long long i = 0; i < str_count; ++i)
	{
		if (string_array[i][strlen(string_array[i]) - 1] != '\r')
		{
			write(file_out, string_array[i], strlen(string_array[i]));
		}
		else
		{
			write(file_out, string_array[i], strlen(string_array[i]) - 1);
		}
		if (i < str_count - 1)
		{
			write(file_out, "\n", 1);
		}
	}

	printf("\n���� �� ������� ���, �� ������ ���� ������������� � �������� � �������� ����.\n");

	for (long long str_number = 0; str_number < str_count - 1; ++str_number)
	{
		string_array[str_number][strlen(string_array[str_number])] = '\n';
	}

	free(string_array);

	munmap(source, in_file_stats.st_size);
	close(file_in);
	close(file_out);
	return 0;
}