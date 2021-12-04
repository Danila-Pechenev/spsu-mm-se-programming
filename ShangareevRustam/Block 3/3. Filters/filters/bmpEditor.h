#define _CRT_NO_SECURE_WARNINGS

#include <stdio.h>

struct rgb
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct img
{
	int height;
	int width;
	struct rgb** rgb;
};

struct bmpHeader
{
	char identifier[2]; // ������������� 
	unsigned int size; // ������ bmp �����
	int garbage; // �� �����
	unsigned int imageOffset; // �������� �����������
	// (��������� ����� �����, � ������� �����������)
};

struct bmpInfoHeader
{
	unsigned int headerSize; // ������ ����� ���������
	// � �����������
	int width; // ������ �����������
	int height; // ������ �����������
	unsigned short int numberOfColorPlanes;
	unsigned short int numberBitsPerPixel; // ��������� ���/����
	unsigned int compressionMethod; // ����� ������
	unsigned int imageSize; // ������ �����������
	int horizontalResolution; // �������� �� �������������� ����
	int verticalResolution; // �������� �� ������������ ����
	unsigned int numberColors; // ���������� ������ � �������
	unsigned int numberImportantColors; // ���������� ������ ������
};

struct argb
{
	unsigned char alpha;
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct img32
{
	int height;
	int width;
	struct argb** argb;
};

int min(int a, int b);

int cmp(int* x, int* y);

unsigned char grayScale(struct rgb rgb);

void medianFilter(struct img* picture);

void sobelXFilter(struct img* picture);

void sobelYFilter(struct img* picture);

void gaussFilter(struct img* picture);

void grayFilter(struct img* picture);

struct img readImage(FILE* fp, int height, int width);

void writeImage(struct bmpHeader header, struct bmpInfoHeader headerInfo, struct img picture, char** argv);

int cmp(int* x, int* y);

unsigned char grayScale32(struct argb argb);

void medianFilter32(struct img32* picture);

void sobelXFilter32(struct img32* picture);

void sobelYFilter32(struct img32* picture);

void gaussFilter32(struct img32* picture);

void grayFilter32(struct img32* picture);

struct img32 readImage32(FILE* fp, int height, int width);

void writeImage32(struct bmpHeader header, struct bmpInfoHeader headerInfo, struct img32 picture, char** argv);