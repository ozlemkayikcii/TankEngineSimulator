#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class LineParser
{
public:
	LineParser();
	~LineParser();
	vector<double> readValues(string);
};