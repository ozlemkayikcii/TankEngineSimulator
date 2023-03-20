#pragma once
#include<fstream>
#include<iostream>
#include <string>
#include<vector>

using namespace std;

class Input
{
public:
	Input();
	~Input();
	Input(string);
	void readInput();
	vector<string> getCommands();
private:
	string file_path;
	vector<string> commands;
};