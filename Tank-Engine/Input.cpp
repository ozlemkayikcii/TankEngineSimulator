#include "Input.h"

Input::Input() {}

Input::~Input() {}

Input::Input(string file_path)
{
	this->file_path = file_path;
}

void Input::readInput()  // Takes all the lines in "input.txt" file one by one and appends them to a list of commands.
{
	ifstream file;
	file.open(this->file_path);
	if (file.is_open())
	{
		string line;
		while(getline(file, line))
		{
			commands.push_back(line);
		}
	}
	else
		cout << "File not found.";
}

vector<string> Input::getCommands()
{
	return this->commands;
}