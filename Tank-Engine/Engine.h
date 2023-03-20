#include"Tank.h"
#include"External.h"
#include"Internal.h"
#include<list>
using namespace std;

class Engine
{
public:
	static Engine* getInstance();
	void startEngine();
	void stopEngine();
	bool getStatus();
	void setStatus(bool);
	Internal& getInternal();
	void setInternal(Internal&);
	void setInternalFuelQuantity(double);
	list<External> getListTankConnected();
	void setListTankConnected(list<External>);
	double getFuelPerSecond();
	bool getFullThrottle();
	void setFullThrottle(bool);
	int getHealth();
	void setHealth(int);
	int getHeat();
	void setHeat(int);
private:
	Engine();
	bool is_full_throttle;
	static Engine* engine_singleton;
	static double fuel_per_second;
	bool is_on;
	int heat;
	int health;
	Internal internal;
	list<External> list_tank_connected;
};