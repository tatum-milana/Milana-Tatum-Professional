#include "Image.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


void TestReadAndWrite();
void Load();

int main()
{
	int pass = 0;
	Image car;
	car.AddData("input/car.tga");

	Image circles;
	circles.AddData("input/circles.tga");

	Image layer_blue;
	layer_blue.AddData("input/layer_blue.tga");

	Image layer_green;
	layer_green.AddData("input/layer_green.tga");

	Image layer_red;
	layer_red.AddData("input/layer_red.tga");

	Image layer1;
	layer1.AddData("input/layer1.tga");

	Image layer2;
	layer2.AddData("input/layer2.tga");

	Image pattern1;
	pattern1.AddData("input/pattern1.tga");

	Image pattern2;
	pattern2.AddData("input/pattern2.tga");

	Image text;
	text.AddData("input/text.tga");

	Image text2;
	text2.AddData("input/text2.tga");


	// Task #1

	Image taskOne;
	taskOne.setHeader(layer1);
	taskOne.MultiplyColor(layer1, pattern1);

	taskOne.WriteTGA("part1");
	Image taskOneCheck;
	taskOneCheck.AddData("examples/EXAMPLE_part1.tga");

	cout << "Test #1...... ";
	if (taskOne == taskOneCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//Task #2

	Image taskTwo;
	taskTwo.setHeader(layer2);
	taskTwo.SubtractColor(layer2, car);
	taskTwo.WriteTGA("part2");

	Image taskTwoCheck;
	taskTwoCheck.AddData("examples/EXAMPLE_part2.tga");

	cout << "Test #2...... ";
	if (taskTwo == taskTwoCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//Task #3
	
	Image taskThreetemp;
	taskThreetemp.setHeader(layer1);
	taskThreetemp.MultiplyColor(layer1, pattern2);

	Image taskThree;
	taskThree.setHeader(layer1);
	taskThree.ScreenColor(text, taskThreetemp);
	taskThree.WriteTGA("part3");

	Image taskThreeCheck;
	taskThreeCheck.AddData("examples/EXAMPLE_part3.tga");

	cout << "Test #3...... ";
	if (taskThree == taskThreeCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//Task 4
	
	Image taskFourtemp;
	taskFourtemp.setHeader(layer2);
	taskFourtemp.MultiplyColor(layer2, circles);

	Image taskFour;
	taskFour.setHeader(layer2);
	taskFour.SubtractColor(pattern2, taskFourtemp);
	taskFour.WriteTGA("part4");

	Image taskFourCheck;
	taskFourCheck.AddData("examples/EXAMPLE_part4.tga");

	cout << "Test #4...... ";
	if (taskFour == taskFourCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//task 5
	Image taskFive;
	taskFive.setHeader(layer1);
	taskFive.OverlayColor(layer1, pattern1);
	taskFive.WriteTGA("part5");

	Image taskFiveCheck;
	taskFiveCheck.AddData("examples/EXAMPLE_part5.tga");

	cout << "Test #5...... ";
	if (taskFive == taskFiveCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//task 6
	Image taskSix;
	taskSix.AddData("input/car.tga");
	taskSix.AddToChannel(200,'g');
	taskSix.WriteTGA("part6");

	Image taskSixCheck;
	taskSixCheck.AddData("examples/EXAMPLE_part6.tga");

	cout << "Test #6...... ";
	if (taskSix == taskSixCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//task 7
	Image taskSeven;
	taskSeven.AddData("input/car.tga");
	taskSeven.ScaleChannel(4, 'r');
	taskSeven.ScaleChannel(0, 'b');
	taskSeven.WriteTGA("part7");

	Image taskSevenCheck;
	taskSevenCheck.AddData("examples/EXAMPLE_part7.tga");

	cout << "Test #7...... ";
	if (taskSeven == taskSevenCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}
	
	// task 8
	Image partEight;
	partEight.AddData("input/car.tga");
	Image part8_b = partEight.SeperateChannel("Blue");
	part8_b.setHeader(car);
	Image part8_g = partEight.SeperateChannel("Green");
	part8_g.setHeader(car);
	Image part8_r = partEight.SeperateChannel("Red");
	part8_r.setHeader(car);
	part8_b.WriteTGA("part8_b");
	part8_g.WriteTGA("part8_g");
	part8_r.WriteTGA("part8_r");

	Image checkb;
	checkb.AddData("examples/EXAMPLE_part8_b.tga");

	Image checkr;
	checkr.AddData("examples/EXAMPLE_part8_r.tga");

	Image checkg;
	checkg.AddData("examples/EXAMPLE_part8_g.tga");

	cout << "Test #8...... ";
	if(part8_b == checkb && part8_g == checkg && part8_r == checkr)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//task 9 
	Image taskNine;
	taskNine.AddData("input/layer_red.tga");
	taskNine.LoadChannels(layer_blue, layer_green, layer_red);
	taskNine.WriteTGA("part9");

	Image taskNineCheck;
	taskNineCheck.AddData("examples/EXAMPLE_part9.tga");

	cout << "Test #9...... ";
	if (taskNine == taskNineCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	//task 10
	Image taskTen;
	taskTen.AddData("input/text2.tga");
	taskTen.Flip(); 
	taskTen.WriteTGA("part10");

	Image taskTenCheck;
	taskTenCheck.AddData("examples/EXAMPLE_part10.tga");

	cout << "Test #10...... ";
	if (taskTen == taskTenCheck)
	{
		cout << "Passed!" << endl;
		pass++;
	}
	else
	{
		cout << "Failed!" << endl;
	}

	cout << "Test Results: " << pass << "/10" << endl;

	//Extra credit task

	Image extraCredit;
	extraCredit.AddData("input/car.tga");
	extraCredit.header.height = (extraCredit.header.height) * 2;
	extraCredit.header.width = (extraCredit.header.width) * 2;
	extraCredit.totalPixels = (extraCredit.header.width) * (extraCredit.header.height);
	extraCredit.pixelCount = 0;
	extraCredit.pixelData.clear();
	  ////extraCredit.pixelData.resize(extraCredit.totalPixels);
	extraCredit.extraCredit(pattern1, text, car, circles);

	
	extraCredit.WriteTGA("extracredit");
	
	Image extraCreditCheck;
	extraCreditCheck.AddData("examples/EXAMPLE_extracredit.tga");

	if (extraCredit == extraCreditCheck)
	{
		cout << "Extra credit...... Passed!" << endl;
	}

}

void TestReadAndWrite()
{
	Image one;
	one.AddData("input/car.tga");

	Image two;
	two.AddData("output/practice.tga");

	if (one == two)
	{
		cout << "the images are equal" << endl;
	}
	else
	{
		cout << "the images are unequal!" << endl;
	} 

}


