/*
 *  main.cpp
 *  Spot a Pro Tools region from an external program
 *  Author: Bob Lee, 2/7/2005
 *
 *  Copyright (c) 2005
 *  Digidesign, A Division of Avid
 *
 */

#include "RegionSpotter.h"
#include <iostream>

int main()
{
	RegionSpotter* myRegionSpotterPtr = NULL;

	char* regionName = new char[40];
	char* sourceFile = new char[200];
	sourceFile[0] = 0;
	short trackOffset = 0, stream = 0, result = 0;
	long startSample = 0, stopSample = 0, sampleLoc = 0;


	while (true) {

		using namespace std;

		cout << "\nError code was: " << result << endl;
		result = 0;

		cout << "---------------------------------------------------\n"
			<< "Current source audio: " << sourceFile << "\n"
			<< "\tFrom sample " << startSample << " to sample " << stopSample << "\n"
			<< endl;

		cout << "Choose one of the following options:\n"
			<< "\t1) Specify source audio\n"
			<< "\t2) Spot source audio to selection\n"
			<< "\t3) Exit program\n"
			<< "---------------------------------------------------"
			<< endl;


		switch (cin.get()) {

		case '1':  // Creating a piece of audio to be spotted
			cin.ignore();
			cout << "\nType the absolute path and name of the source file: \n"
				<< "  Windows: d:\\folder name\\test.wav\n"
				<< "  Mac: Macintosh HD:Folder name:test.wav\n" << endl;
			cin.getline(sourceFile, 200);

			cout << "Which sample in the source file should be the start of the region? ";
			cin >> startSample;

			cout << "Which sample in the source file should be the end of the region? ";
			cin >> stopSample;
			cin.ignore();

			delete myRegionSpotterPtr;
			myRegionSpotterPtr = RegionSpotter::CreateRegionSpotter(sourceFile, startSample, stopSample);

			cout << endl;
			break;


		case '2':  // Spotting audio to the current selection
			cin.ignore();
			cout << "\nType the name of the region you wish to create: ";
			cin.getline(regionName, 40);

			cout << "Type the track offset from the first selected track: ";
			cin >> trackOffset;

			cout << "Type the sample offset from the beginning of the selection: ";
			cin >> sampleLoc;

			cout << "Type the number of the multichannel stream (1 = Left) you wish to spot to: ";
			cin >> stream;
			cin.ignore();

			// See parameter definitions in RegionSpotter.h
			if (myRegionSpotterPtr)
				result = myRegionSpotterPtr->spot(trackOffset, sampleLoc, stream, regionName);

			cout << endl;
			break;


		case '3':
			delete myRegionSpotterPtr;
			delete[] sourceFile;
			delete[] regionName;
			return 0;
		}

	}

}
