#pragma once
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class Image
{
public:
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;

	};

	struct Pixel
	{
		// for this project, treat pixels like unsinged chars with values from 0 - 255
		unsigned char blue = 0;
		unsigned char green = 0;
		unsigned char red = 0;
	};

	unsigned int totalPixels = 0;
	unsigned int pixelCount = 0;
	vector<Pixel> pixelData;
	Header header;

	Image();
	void AddData(string filePath);
	void WriteTGA(string name);
	void FillColor(unsigned char _blue, unsigned char _green, unsigned char _red);
	void setHeader(Image top);
	void MultiplyColor(Image top, Image bottom);
	void SubtractColor(Image top, Image bottom);
	void ScreenColor(Image top, Image bottom);
	void OverlayColor(Image top, Image bottom);
	void AddToChannel(int amt, char c);
	void ScaleChannel(int amt, char c);
	void LoadChannels(Image B, Image G, Image C);
	void Flip();
	Image SeperateChannel(string color);
	void extraCredit(Image br, Image bl, Image tl, Image tr);


	//overlaoded operators
	bool operator==(const Image& p);
};

