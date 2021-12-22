#include"Header.h"

int main(int argc, char* argv[])
{
	system("chcp 1251");
	system("cls");

	printf("�������������� ����: \n");
	printf(" 1 - ����������� ������ 3x3 \n");
	printf(" 2 - ����������� ������ ������ 3x3 \n");
	printf(" 3 - ����������� ������ ������ 5x5 \n");
	printf(" 4 - ������ ������ �� X \n");
	printf(" 5 - ������ ������ �� Y \n");
	printf(" 6 - ������� ����������� �� �������� � ������� ������ \n\n");

	printf(" ������ �����: ��������1 ��������2  ��������3, ���   \n");
	printf(" - �������� 1 - ��� ���� � ����� ���������; ������ �����: �:\\file.bpm\n");
	printf(" - �������� 2 - ����� �������; ������ �����: 2\n");
	printf(" - �������� 3 - ��� ���� � ����� ��������;  �:\\file_test.bpm\n\n");

	char* partToTheFile = argv[1];
	char* partToTheFileExport = argv[3];
	char* numberOfFilter = argv[2];

	if (readArgument(argc))
	{
		printf("\n ������ ����� ���������� ����������!\n");
		return 0;
	}

	if (strcmp(numberOfFilter, "1") && strcmp(numberOfFilter, "2") && strcmp(numberOfFilter, "3") && strcmp(numberOfFilter, "4") && strcmp(numberOfFilter, "5") && strcmp(numberOfFilter, "6"))
	{
		printf("\n���������� ���� ������� ��� � ����\n");
		return 0;
	}

	FILE* fileImport = fopen(partToTheFile, "rb");

	struct infoHeaderOfFile* headerFile = malloc(sizeof(struct infoHeaderOfFile));

	int result = fileValidation(headerFile, fileImport);

	if (!result)
	{
		fclose(fileImport);
		printf("������ ������ ����� �������");
		return 0;
	}

	int p;
	struct RGBTRIPLE** rgbTriple = readArray(&p, headerFile, fileImport);
	struct RGBTRIPLE** rgbNew = cpyArray(rgbTriple, headerFile);

	if (!strcmp(numberOfFilter, "1"))
	{
		filterMedian(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew);
	}
	if (!strcmp(numberOfFilter, "2"))
	{
		filterGauss(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew, 3);
	}
	if (!strcmp(numberOfFilter, "3"))
	{
		filterGauss(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew, 5);
	}
	if (!strcmp(numberOfFilter, "4"))
	{
		filterSobelXY(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew, 1);
	}
	if (!strcmp(numberOfFilter, "5"))
	{
		filterSobelXY(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew, 1);
	}
	if (!strcmp(numberOfFilter, "6"))
	{
		filterBlackandWhite(headerFile->biWidth, headerFile->biHeight, rgbTriple, rgbNew);
	}

	FILE* fileExport = fopen(partToTheFileExport, "wb");

	fwrite(headerFile, sizeof(struct infoHeaderOfFile), 1, fileExport);

	for (int i = 0; i < headerFile->biHeight; i++)
	{
		for (int j = 0; j < headerFile->biWidth; j++)
			fwrite(&rgbNew[i][j], sizeof(struct RGBTRIPLE), 1, fileExport);
		if (headerFile->biBitCount == 32)
		{
			putc(0, fileExport);
		}
		for (int k = 0; k < p; k++)
			fputc(0, fileExport);
	}

	printf("��������� ������ ���������:\n");
	printf(" - �������� 1 - %s\n", argv[1]);
	printf(" - �������� 2 - %s\n", argv[2]);
	printf(" - �������� 3 - %s\n\n", argv[3]);
	printf("��������� ������� ��������� ���������!\n\n");

	fclose(fileExport);
	free(headerFile);
	free(rgbTriple);
	free(rgbNew);

	return 0;
}