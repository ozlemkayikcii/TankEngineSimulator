#pragma once
#include<string>
#include<fstream>
using namespace std;

class Output
{
public:
	static Output* getInstance();
	void giveOutput(string);
private:
	Output();
	static Output* output_singleton;
};