#include"Header.h"

int fileValidation(struct infoHeaderOfFile* inf, FILE* importFile)
{
	if (importFile == NULL)
	{
		printf("��������� ������! ��������� �� ������ ������� ��������� ���� ����!");
		return 0;
	}

	// ������ ���������
	fread(inf, sizeof(struct infoHeaderOfFile),1,importFile);
	
	// ��������� ���������
	if (inf->bfType != 0x4D42 && inf->bfType != 0x4349 && inf->bfType != 0x5450)
	{ 
		printf("��������� ������! ������ �� ������ ������ (�� BMP)!");
		return 0; 
	}

	if (inf->biSize != 40 && inf->biSize != 108 && inf->biSize != 124)
	{

		printf("��������� ������! �������� ������ BITMAPINFO!");
		return 0;
	}
	
	

	if (inf->biBitCount != 24 && inf->biBitCount != 32)
	{
		printf("��������� �����, ��������� �������� ������ � 24 � 32-�������� �������\n");
		return 0;
	}

	return inf->biBitCount;
	

}

struct RGBTRIPLE** readArray(int* padding, struct infoHeaderOfFile* infMAP, FILE* importFile)
{
	struct RGBTRIPLE** rgb_arr = calloc(sizeof(struct RGBTRIPLE*), infMAP->biHeight);

	for (int i = 0; i < infMAP->biHeight; i++)
	{
		rgb_arr[i] = calloc(infMAP->biWidth, sizeof(struct RGBTRIPLE));
	}

	*padding = (4 - (infMAP->biWidth * (infMAP->biBitCount / 8)) % 4) & 3;

	for (int i = 0; i < infMAP->biHeight; i++)
	{
		for (int j = 0; j < infMAP->biWidth; j++)
		{
			rgb_arr[i][j].b = (unsigned char)getc(importFile);
			rgb_arr[i][j].g = (unsigned char)getc(importFile);
			rgb_arr[i][j].r = (unsigned char)getc(importFile);
		}

		for (int k = 0; k < *padding; k++)
			getc(importFile);
	}

	fclose(importFile);

	return rgb_arr;
}

struct RGBTRIPLE** readArray32(int* padding, struct infoHeaderOfFile* infMAP, FILE* importFile)
{
	struct RGBTRIPLE** rgb_arr = calloc(sizeof(struct RGBTRIPLE*), infMAP->biHeight);

	for (int i = 0; i < infMAP->biHeight; i++)
	{
		rgb_arr[i] = calloc(infMAP->biWidth, sizeof(struct RGBTRIPLE));
	}

	*padding = (4 - (infMAP->biWidth * (infMAP->biBitCount / 8)) % 4) & 3;

	for (int i = 0; i < infMAP->biHeight; i++)
	{
		for (int j = 0; j < infMAP->biWidth; j++)
		{
			rgb_arr[i][j].b = (unsigned char)getc(importFile);
			rgb_arr[i][j].g = (unsigned char)getc(importFile);
			rgb_arr[i][j].r = (unsigned char)getc(importFile);
			getc(importFile);
		}

		for (int k = 0; k < *padding; k++)
			getc(importFile);
	}

	fclose(importFile);

	return rgb_arr;
}


struct RGBTRIPLE** cpyArray(struct RGBTRIPLE** old_arr, struct infoHeaderOfFile* infMap)
{
	struct RGBTRIPLE** rgb_new = malloc(sizeof(struct RGBTRIPLE*) * infMap->biHeight);

	for (int i = 0; i < infMap->biHeight; i++)
	{
		rgb_new[i] = calloc(sizeof(struct RGBTRIPLE), infMap->biWidth);
		memcpy(rgb_new[i], old_arr[i], sizeof(struct RGBTRIPLE) * infMap->biWidth);

	}


	return rgb_new;

}


