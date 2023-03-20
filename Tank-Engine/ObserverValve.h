#include "Observer.h"
#include "Output.h"

static int counter;

class ObserverValve :public Observer
{
private:
	string message;
public:
	Output* output = Output::getInstance();
	ObserverValve() {};
	void update() 
	{
		message = "Valve " + to_string(++counter) + " : Simulation stopped.";
		output->giveOutput(message);
	}
};