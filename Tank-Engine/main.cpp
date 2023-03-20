#include"Simulation.h"

int main()
{
	remove("output.txt");
    Input input = Input("input.txt");
    input.readInput();

	Simulation Simulation(input);
	Simulation.processCommands(input.getCommands());
	return 0;
}
