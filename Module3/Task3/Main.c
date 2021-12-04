#include"Header.h"

#define Name 
int main()
{
	system("chcp 1251");
	system("cls");
	printf("��� #1. ����������, ������� ���� (��������): ");

	char pathToTheFile[bufer_size] ;
	char pathToTheFileExit[bufer_size];

	scanf("%s", pathToTheFile);


	FILE* fileImport = fopen(pathToTheFile, "rb");
	
	struct infoHeaderOfFile* headerFile = malloc(sizeof(struct infoHeaderOfFile));

	int result = fileValidation(headerFile,fileImport);

	if (!result)
	{
		//fclose(fileImport);
		return 0;
	}

	int p;
	if (result == 24)
	{
		struct RGBTRIPLE** rgb_triple = readArray(&p, headerFile, fileImport);
	}
	else
	{
		struct RGBTRIPLE** rgb_triple = readArray32(&p, headerFile, fileImport);
	}

	
	struct RGBTRIPLE** rgb_triple = readArray(&p, headerFile, fileImport);;
		
	int choser, res;

	struct RGBTRIPLE** rgb_new = cpyArray(rgb_triple, headerFile);

	do
	{

		printf("��� #2. �������� ���� �� ����������� ��������: \n");
		printf(" 1 - ����������� ������ 3x3 \n");
		printf(" 2 - ����������� ������ ������ 3x3 \n");
		printf(" 3 - ����������� ������ ������ 5x5 \n");
		printf(" 4 - ������ ������ �� X \n");
		printf(" 5 - ������ ������ �� Y \n");
		printf(" 6 - ������� ����������� �� �������� � ������� ������ \n"); 
	

	} while (!inputValidation(&choser));
	
	switch (choser)
	{

	case 1:
	{
		filterMedian(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new);
		break;
	}
	case 2:
	{
		filterGauss(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new, 3);
		break;
	}
	case 3:
	{
		filterGauss(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new, 5);
		break;
	}
	case 4:
	{
		 filterSobelX(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new);
		break;
	}
	case 5:
	{
		filterSobelY(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new);
		break;
	}
	case 6:
	{
		filterBlackandWhite(headerFile->biWidth, headerFile->biHeight, rgb_triple, rgb_new);
		break;
	}
	default:

		
		break;
	}


	printf("��� #3. ����������, ������� ��� �������� ���� (��������): ");
	scanf("%s", pathToTheFileExit);
	FILE* fileExport = fopen(pathToTheFileExit, "wb");

	
	fwrite(headerFile, sizeof(struct infoHeaderOfFile),1, fileExport);
	if (result == 24)
	{
		for (int i = 0; i < headerFile->biHeight; i++)
		{
			for (int j = 0; j < headerFile->biWidth; j++)
				fwrite(&rgb_new[i][j], sizeof(struct RGBTRIPLE), 1, fileExport);

			for (int k = 0; k < p; k++)
				fputc(0, fileExport);
		}
	}
	else
	{
		for (int i = 0; i < headerFile->biHeight; i++)
		{
			for (int j = 0; j < headerFile->biWidth; j++)
				fwrite(&rgb_new[i][j], sizeof(struct RGBTRIPLE), 1, fileExport);
				putc(0, fileExport);
			for (int k = 0; k < p; k++)
				fputc(0, fileExport);
		}
	}



	fclose(fileExport);

	free(headerFile);
	free(rgb_triple);
	free(rgb_new);

	return 0;

}