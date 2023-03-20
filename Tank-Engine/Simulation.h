#include "Input.h"
#include "Output.h"
#include "LineParser.h"
#include "Engine.h"
#include "ObserverTank.h"
#include "ObserverValve.h"
#include "ObserverEngine.h"
#include "Subject.h"

class Simulation
{
private:
	Input input;
	list<External> tank_list;
	LineParser line;
	Subject* subject = new Subject();
	Observer* observer;
public:
	Simulation(Input);
	~Simulation();
	Engine* engine = Engine::getInstance();
	Output* output = Output::getInstance();
	double total_consumed_fuel = 0.0;
	void connectFuelTankToEngine(int);
	void disconnectFuelTankToEngine(int);
	void addFuelTank(double);
	void removeFuelTank(int);
	void fillTank(int, double);
	void repairEngine();
	void changeEngineBlock();
	void openValve(int);
	void closeValve(int);
	void wait(double);
	void stopSimulation();
	void printTankInfo(int);
	void repairFuelTank(int);
	void breakFuelTank(int);
	void listFuelTanks();
	void listConnectedTanks();
	void printFuelTankCount();
	void printTotalConsumedFuel();
	void printTotalFuel();
	void processCommands(vector<string>);
	void sum_operator(External&, External&, External&);
};