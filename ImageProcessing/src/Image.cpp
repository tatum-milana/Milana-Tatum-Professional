#include "Image.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Constructors
Image::Image()
{
	
	header.idLength = 0;
	header.colorMapType = 0;
	header.dataTypeCode = 0;
	header.colorMapOrigin = 0;
	header.colorMapLength = 0;
	header.colorMapDepth = 0;
	header.xOrigin = 0;
	header.yOrigin = 0;
	header.width = 0;
	header.height = 0;
	header.bitsPerPixel = 0;
	header.imageDescriptor = 0;

	totalPixels = 0;
	pixelCount = 0;

}
void Image::AddData(string filePath)
{

	ifstream inFile;
	//filePath = "ImageProcessing/" + filePath;
	inFile.open(filePath, ios_base::binary);

	if (inFile.is_open())
	{
		inFile.read((char*)&(header.idLength), sizeof(header.idLength));
		inFile.read((char*)&(header.colorMapType), sizeof(header.colorMapType));
		inFile.read((char*)&(header.dataTypeCode), sizeof(header.dataTypeCode));
		inFile.read((char*)&(header.colorMapOrigin), sizeof(header.colorMapOrigin));
		inFile.read((char*)&(header.colorMapLength), sizeof(header.colorMapLength));
		inFile.read((char*)&(header.colorMapDepth), sizeof(header.colorMapDepth));
		inFile.read((char*)&(header.xOrigin), sizeof(header.xOrigin));
		inFile.read((char*)&(header.yOrigin), sizeof(header.yOrigin));
		inFile.read((char*)&(header.width), sizeof(header.width));
		inFile.read((char*)&(header.height), sizeof(header.height));
		inFile.read((char*)&(header.bitsPerPixel), sizeof(header.bitsPerPixel));
		inFile.read((char*)&(header.imageDescriptor), sizeof(header.imageDescriptor));

		totalPixels = (header.width) * (header.height);

		for (unsigned int i = 0; i < totalPixels; i++)
		{
			Pixel tempPixel;
			inFile.read((char*)&(tempPixel.blue), sizeof(tempPixel.blue));
			inFile.read((char*)&(tempPixel.green), sizeof(tempPixel.green));
			inFile.read((char*)&(tempPixel.red), sizeof(tempPixel.red));
			
			pixelCount++;
			Pixel& pixel = tempPixel;
			pixelData.push_back(pixel);
		}

		/*
		cout << int(header.idLength) << endl;
		cout << int(header.colorMapType) << endl;
		cout << int(header.dataTypeCode) << endl;
		cout << header.colorMapOrigin << endl;
		cout << header.colorMapLength << endl;
		cout << int(header.colorMapDepth) << endl;
		cout << header.xOrigin << endl;
		cout << header.yOrigin << endl;
		cout << header.width << endl;
		cout << header.height << endl;
		cout << int(header.bitsPerPixel) << endl;
		cout << int(header.imageDescriptor) << endl;
		*/
			
	}

	else
	{
		cout << "File did not open!" << endl;
	}
}

void Image::WriteTGA(string name)
{
	fstream outFile;
	string filePath = "output/" + name + ".tga";
	outFile.open(filePath, ios::out | ios::binary); // tga write

	if (outFile.is_open())
	{
		outFile.write((char*)&(header.idLength), sizeof(header.idLength));
		outFile.write((char*)&(header.colorMapType), sizeof(header.colorMapType));
		outFile.write((char*)&(header.dataTypeCode), sizeof(header.dataTypeCode));
		outFile.write((char*)&(header.colorMapOrigin), sizeof(header.colorMapOrigin));
		outFile.write((char*)&(header.colorMapLength), sizeof(header.colorMapLength));
		outFile.write((char*)&(header.colorMapDepth), sizeof(header.colorMapDepth));
		outFile.write((char*)&(header.xOrigin), sizeof(header.xOrigin));
		outFile.write((char*)&(header.yOrigin), sizeof(header.yOrigin));
		outFile.write((char*)&(header.width), sizeof(header.width));
		outFile.write((char*)&(header.height), sizeof(header.height));
		outFile.write((char*)&(header.bitsPerPixel), sizeof(header.bitsPerPixel));
		outFile.write((char*)&(header.imageDescriptor), sizeof(header.imageDescriptor));

		/*
		outFile << header.idLength;
		outFile << header.colorMapType;
		outFile << header.dataTypeCode;
		outFile << header.colorMapOrigin;
		outFile << header.colorMapLength;
		outFile << header.colorMapDepth;
		outFile << header.xOrigin;
		outFile << header.yOrigin;
		outFile << header.width;
		outFile << header.height;
		outFile << header.bitsPerPixel;
		outFile << header.imageDescriptor;
		*/
		
	
		for (unsigned long int i = 0; i < pixelData.size(); i++)
		{
			//unsigned char bluee = pixelData[i].blue;
			//unsigned char greenn = pixelData[i].green;
			//unsigned char redd = pixelData[i].red;

			outFile.write((char*)&(pixelData[i].blue), sizeof(pixelData[i].blue));
			outFile.write((char*)&(pixelData[i].green), sizeof(pixelData[i].green));
			outFile.write((char*)&(pixelData[i].red), sizeof(pixelData[i].red));
		}
		//cout << "finished creating file" << endl;
	}

	else
	{
		cout << "file did not open";
	}
}

bool Image::operator==(const Image& p)
{
	//cout << "comparing header values" << endl;
	if (this->header.idLength != p.header.idLength)
	{
		cout << "unequal id lengths" << endl;
		return false;
	}
	if (this->header.colorMapType != p.header.colorMapType)
	{
		cout << "unequal color map type" << endl;
		return false;
	}
	if (this->header.dataTypeCode != p.header.dataTypeCode)
	{
		cout << "unequal data type code" << endl;
		return false;
	}
	if (this->header.colorMapOrigin != p.header.colorMapOrigin)
	{
		cout << "unequal color map origins" << endl;
		return false;
	}
	if (this->header.colorMapLength != p.header.colorMapLength)
	{
		cout << "unequal color map lengths" << endl;
		return false;
	}
	if (this->header.colorMapDepth != p.header.colorMapDepth)
	{
		cout << "unequal color map depth" << endl;
		return false;
	}
	if (this->header.xOrigin != p.header.xOrigin)
	{
		cout << "unequal color map origin!" << endl;
		return false;
	}
	if (this->header.yOrigin != p.header.yOrigin)
	{
		cout << "unequal y origin" << endl;
		return false;
	}
	if (this->header.width != p.header.width)
	{
		cout << "unequal image widths" << endl;
		return false;
	}
	if (this->header.height != p.header.height)
	{
		cout << "unequal height" << endl;
		return false;
	}
	if (this->header.bitsPerPixel != p.header.bitsPerPixel)
	{
		cout << "unequal bits per pixel" << endl;
		return false;
	}
	if (this->header.imageDescriptor != p.header.imageDescriptor)
	{
		cout << "Unequal image descriptors!" << endl;
		return false;
	}
	//cout << "All header values are equal." << endl;
	//cout << "Checking pixels.." << endl;

	for (unsigned long int i = 0; i < this->pixelData.size(); i++)
	{
		if (this->pixelData[i].blue != p.pixelData[i].blue)
		{
			if (i == 0)
			{
				cout << "it was wrong from the very first pixel..." << endl;
			}
			cout << "blue pixel data unequal";
			return false;
		}
		if (this->pixelData[i].green != p.pixelData[i].green)
		{
			cout << "green pixel data unequal";
			return false;
		}
		if (this->pixelData[i].red != p.pixelData[i].red)
		{
			cout << "red pixel data unequal";
			return false;
		}
	}
	return true;

}

void Image::FillColor(unsigned char _blue, unsigned char _green, unsigned char _red)
{
	for (unsigned long int i = 0; i < pixelData.size(); i++)
	{
		pixelData[i].blue = _blue;
		pixelData[i].green = _green;
		pixelData[i].red = _red;
	}
	
}

void Image::setHeader(Image top)
{
	header.idLength = top.header.idLength;
	header.colorMapType = top.header.colorMapType;
	header.dataTypeCode = top.header.dataTypeCode;
	header.colorMapOrigin = top.header.colorMapOrigin;
	header.colorMapLength = top.header.colorMapLength;
	header.colorMapDepth = top.header.colorMapDepth;
	header.xOrigin = top.header.xOrigin;
	header.yOrigin = top.header.yOrigin;
	header.width = top.header.width;
	header.height = top.header.height;
	header.bitsPerPixel = top.header.bitsPerPixel;
	header.imageDescriptor = top.header.imageDescriptor;

}

void Image::MultiplyColor(Image top, Image bottom)
{
	for (unsigned int i = 0; i < top.pixelData.size(); i++)
	{
		Pixel temp;
		float topB = float(top.pixelData[i].blue) / 255;
		float topG = float(top.pixelData[i].green) / 255;
		float topR = float(top.pixelData[i].red) / 255;

		float bottomB = float(bottom.pixelData[i].blue) / 255;
		float bottomG = float(bottom.pixelData[i].green) / 255;
		float bottomR = float(bottom.pixelData[i].red) / 255;

		float resultB = ((topB * bottomB) * 255) + 0.5;
		float resultG = ((topG * bottomG) * 255) + 0.5;
		float resultR = ((topR * bottomR) * 255) + 0.5;

		if (resultB > 255) { resultB = 255; }
		if (resultG > 255) { resultG = 255; }
		if (resultR > 255) { resultR = 255; }
		if (resultB < 0) { resultB = 0; }
		if (resultG < 0) { resultG = 0; }
		if (resultR < 0) { resultR = 0; }

		resultB = char(int(resultB));
		resultG = char(int(resultG));
		resultR = char(int(resultR));

		temp.blue = resultB;
		temp.green = resultG;
		temp.red = resultR;

		pixelData.push_back(temp);
	}
}

void Image::SubtractColor(Image top, Image bottom)
{
	for (unsigned int i = 0; i < top.pixelData.size(); i++)
	{
		Pixel temp;
		float topB = float(top.pixelData[i].blue) / 255;
		float topG = float(top.pixelData[i].green) / 255;
		float topR = float(top.pixelData[i].red) / 255;

		float bottomB = float(bottom.pixelData[i].blue) / 255;
		float bottomG = float(bottom.pixelData[i].green) / 255;
		float bottomR = float(bottom.pixelData[i].red) / 255;

		float resultB = ((bottomB - topB) * 255) + 0.5;
		float resultG = ((bottomG - topG) * 255) + 0.5;
		float resultR = ((bottomR - topR) * 255) + 0.5;

		if (resultB > 255) { resultB = 255; }
		if (resultG > 255) { resultG = 255; }
		if (resultR > 255) { resultR = 255; }
		if (resultB < 0) { resultB = 0; }
		if (resultG < 0) { resultG = 0; }
		if (resultR < 0) { resultR = 0; }

		resultB = char(int(resultB));
		resultG = char(int(resultG));
		resultR = char(int(resultR));

		temp.blue = resultB;
		temp.green = resultG;
		temp.red = resultR;

		pixelData.push_back(temp);
	}
}

void Image::ScreenColor(Image top, Image bottom)
{
	for (unsigned int i = 0; i < top.pixelData.size(); i++)
	{
		Pixel temp;
		float topB = float(top.pixelData[i].blue) / 255;
		float topG = float(top.pixelData[i].green) / 255;
		float topR = float(top.pixelData[i].red) / 255;

		float bottomB = float(bottom.pixelData[i].blue) / 255;
		float bottomG = float(bottom.pixelData[i].green) / 255;
		float bottomR = float(bottom.pixelData[i].red) / 255;

		float resultB = ((1-((1-topB)*(1-bottomB))) * 255) + 0.5;
		float resultG = ((1 - ((1 - topG) * (1 - bottomG))) * 255) + 0.5;
		float resultR = ((1 - ((1 - topR) * (1 - bottomR))) * 255) + 0.5;

		if (resultB < 0 || resultB > 255) { resultB = 255; }
		if (resultG < 0 || resultG > 255) { resultG = 255; }
		if (resultR < 0 || resultR > 255) { resultR = 255; }
		if (resultB < 0) { resultB = 0; }
		if (resultG < 0) { resultG = 0; }
		if (resultR < 0) { resultR = 0; }

		resultB = char(int(resultB));
		resultG = char(int(resultG));
		resultR = char(int(resultR));

		temp.blue = resultB;
		temp.green = resultG;
		temp.red = resultR;

		pixelData.push_back(temp);
	}
}

void Image::OverlayColor(Image top, Image bottom)
{
	


	for (unsigned int i = 0; i < top.pixelData.size(); i++)
	{
		Pixel temp;
		float topB = float(top.pixelData[i].blue) / 255;
		float topG = float(top.pixelData[i].green) / 255;
		float topR = float(top.pixelData[i].red) / 255;

		float bottomB = float(bottom.pixelData[i].blue) / 255;
		float bottomG = float(bottom.pixelData[i].green) / 255;
		float bottomR = float(bottom.pixelData[i].red) / 255;

		float resultB = 0; 
		if (bottomB <= 0.5)
		{
			resultB = ((2 * (topB * bottomB)) * 255) + 0.5;
		}
		else
		{
			resultB= ((1 - (2*((1 - topB) * (1 - bottomB)))) * 255) + 0.5;
		}

		float resultG = 0;
		if (bottomG <= 0.5)
		{
			resultG = ((2 * (topG * bottomG)) * 255) + 0.5;
		}
		else
		{
			resultG = ((1 - (2 * ((1 - topG) * (1 - bottomG)))) * 255) + 0.5;
		}

		float resultR = 0;
		if (bottomR <= 0.5)
		{
			resultR = ((2*(topR * bottomB)) * 255) + 0.5;
		}
		else
		{
			resultR = ((1 - (2 * ((1 - topR) * (1 - bottomR)))) * 255) + 0.5;
		}
		
	
		if (resultB < 0 || resultB > 255) { resultB = 255; }
		if (resultG < 0 || resultG > 255) { resultG = 255; }
		if (resultR < 0 || resultR > 255) { resultR = 255; }
		if (resultB < 0) { resultB = 0; }
		if (resultG < 0) { resultG = 0; }
		if (resultR < 0) { resultR = 0; }

		resultB = char(int(resultB));
		resultG = char(int(resultG));
		resultR = char(int(resultR));

		temp.blue = resultB;
		temp.green = resultG;
		temp.red = resultR;

		pixelData.push_back(temp);
	}
}

void Image::AddToChannel(int amt, char c)
{
	for (unsigned long int i = 0; i < pixelData.size(); i++)
	{
		if (c == 'b' || c == 'B')
		{
			// would fill in if it mattered for this section
		}

		if (c == 'g' || c == 'G')
		{
			int resultG = int(pixelData[i].green);
			resultG =resultG + amt;
			if (resultG > 255)
			{
				resultG = 255;
			}
			resultG = char(resultG);
			pixelData[i].green = resultG;

		}

		if (c == 'r' || c == 'R')
		{
			// would fill in fi it mattered for this section
		}
	}
}

void Image::ScaleChannel(int amt, char c)
{
	for (unsigned long int i = 0; i < pixelData.size(); i++)
	{
		if (c == 'b' || c == 'B')
		{
			int resultB = int(pixelData[i].blue);
			resultB = resultB * amt;
			if (resultB > 255)
			{
				resultB = 255;
			}
			resultB = char(resultB);
			pixelData[i].blue = resultB;

		}

		if (c == 'g' || c == 'G')
		{
			int resultG = int(pixelData[i].green);
			resultG = resultG * amt;
			if (resultG > 255)
			{
				resultG = 255;
			}
			resultG = char(resultG);
			pixelData[i].green = resultG;

		}

		if (c == 'r' || c == 'R')
		{
			int resultR = int(pixelData[i].red);
			resultR = resultR * amt;
			if (resultR > 255)
			{
				resultR = 255;
			}
			resultR = char(resultR);
			pixelData[i].red = resultR;
		}
	}
}

void Image::LoadChannels(Image B, Image G, Image R)
{
	for (unsigned long int i = 0; i < B.pixelData.size(); i++)
	{
		pixelData[i].blue = B.pixelData[i].blue;
		pixelData[i].green = G.pixelData[i].green;
		pixelData[i].red = R.pixelData[i].red;
	}
}

void Image::Flip()
{
	vector<Pixel> tempPixel;
	int size = (pixelData.size() - 1);
	for(int i = size ; i > -1; i--)
	{
		Pixel temp = pixelData[i];
		tempPixel.push_back(temp);
	}

	for (unsigned long int i = 0; i < tempPixel.size(); i++)
	{
		pixelData[i] = tempPixel[i];
	}
}

Image Image::SeperateChannel(string color)
{
	Image result;
	for (unsigned long i = 0; i < pixelData.size(); i++)
	{
		if (color == "Blue")
		{
			Pixel tempPix;
			tempPix.blue = pixelData[i].blue;
			tempPix.green = pixelData[i].blue;
			tempPix.red = pixelData[i].blue;
			result.pixelData.push_back(tempPix);
		}

		if (color == "Green")
		{
			Pixel tempPix;
			tempPix.blue = pixelData[i].green;
			tempPix.green = pixelData[i].green;
			tempPix.red = pixelData[i].green;
			result.pixelData.push_back(tempPix);
		}
		if (color == "Red")
		{
			Pixel tempPix;
			tempPix.blue = pixelData[i].red;
			tempPix.green = pixelData[i].red;
			tempPix.red = pixelData[i].red;
			result.pixelData.push_back(tempPix);

		}
	}
	return result;
}

void Image::extraCredit(Image br, Image bl, Image tl, Image tr)
{
	int brc = 0;
	int blc = 0;
	int linenum = 0;
	for (int r = 0; r < (header.height / 2) ; r++)
	{
		for (int i = 0; i < (header.width / 2); i++)
		{
			pixelData.push_back(bl.pixelData[blc]);
			blc++;
			pixelCount++;
		}
		for (int i = 0; i < (header.width / 2); i++)
		{
			pixelData.push_back(br.pixelData[brc]);
			brc++;
			pixelCount++;
		}
		
	}

	int tlc = 0;
	int trc = 0;

	for (int r = 0; r < (header.height / 2); r++)
	{
		for (int i = 0; i < (header.width / 2); i++)
		{
			pixelData.push_back(tl.pixelData[tlc]);
			tlc++;
			pixelCount++;
		}
		for (int i = 0; i < (header.width / 2); i++)
		{
			pixelData.push_back(tr.pixelData[trc]);
			trc++;
			pixelCount++;
		}
	}

}