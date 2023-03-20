#include "Output.h"

Output::Output() {}

Output* Output::output_singleton;

Output* Output::getInstance()
{
	return output_singleton;
}

void Output::giveOutput(string write)  // Writes given string to "output.txt" file.
{
	fstream output_file;
	output_file.open("output.txt", ios_base::app);
	output_file << write << "\n";
	output_file.close();
}