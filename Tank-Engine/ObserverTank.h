#include "Observer.h"
#include "Output.h"

static int counter1;

class ObserverTank :public Observer
{
private:
	string message;
public:
	Output* output = Output::getInstance();
	ObserverTank() {};
	void update()
	{
		message = "Tank " + to_string(++counter1) + " : Simulation stopped.";
		output->giveOutput(message);
	}
};