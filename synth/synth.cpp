// synth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "olcNoiseMaker.h"

using namespace std;



atomic<double> dFrequencyOutput =0;

double MakeNoise(double dTime)
{
	//dtime is time since the start of program
	//A major
	double dOutput = 0.3*sin(dFrequencyOutput* 2 * 3.14159*dTime);
	
	if (dOutput > 0.0)
		return 0.2;
	else
		return -0.2;

	

}

int main()
{
	wcout << " Synthesizer test" << endl;

	//get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short> ::Enumerate();

	//Display findings
	for (auto d : devices) wcout << "found output device:" << d << endl;

	//---- Create sound machine
	//sample rate , channels, 
	olcNoiseMaker<char> sound(devices[0], 44100, 1, 8, 512);

	//Link noise
	sound.SetUserFunction(MakeNoise);

	double dOctaveBaseFrequency = 110.0; 
	double d12thRootOf2 = pow(2.0, 1.0 / 12.0);


	while (1)
	{
		if (GetAsyncKeyState('A') & 0x8000)
		{
			dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, 12);

		}
		else
		{
			dFrequencyOutput = 0;
		}
	}

    return 0;
}

