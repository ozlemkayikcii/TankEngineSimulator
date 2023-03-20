#include "Output.h"
#include "Observer.h"

class ObserverEngine :public Observer
{
private:
	string message;
public:
	Output* output = Output::getInstance();
	ObserverEngine() {};
	void update()
	{
		message = "Engine: Simulation stopped.";
		output->giveOutput(message);
	}
};
