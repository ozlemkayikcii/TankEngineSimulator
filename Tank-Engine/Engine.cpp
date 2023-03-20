#include "Engine.h"

Engine::Engine()
{
	double capacity = 55.0;

	this->health = 100;
	this->heat = 20;

	this->internal.setCapacity(capacity);
	this->internal.setFuelQuantity(capacity);

	this->is_on = false;
	this->is_full_throttle = false;	
}

double Engine::fuel_per_second = 5.5;

Engine* Engine::engine_singleton;

Engine* Engine::getInstance()
{
	if (engine_singleton == NULL)
	{
		engine_singleton = new Engine();
	}
	return engine_singleton;
}

void Engine::startEngine()
{
	if (health > 20)  // Engine can only be started when health is above 20
	{
		this->setStatus(true);
	}
}

void Engine::stopEngine()
{
	this->setStatus(false);
}

list<External> Engine::getListTankConnected()
{
	return list_tank_connected;
}

void Engine::setListTankConnected(list<External> _list_tank)
{
	this->list_tank_connected = _list_tank;
}

bool Engine::getStatus()
{
	return is_on;
}

void Engine::setStatus(bool status)
{
	this->is_on = status;
}

Internal& Engine::getInternal()
{
	return internal;
}

void Engine::setInternal(Internal& internal)
{
	this->internal = internal;
}

void Engine::setInternalFuelQuantity(double amount)
{
	this->internal.setFuelQuantity(amount);
}

double Engine::getFuelPerSecond()
{
	return this->fuel_per_second;
}

bool Engine::getFullThrottle()
{
	return this->is_full_throttle;
}

void Engine::setFullThrottle(bool is_full_throttle)
{
	this->is_full_throttle = is_full_throttle;
}

int Engine::getHealth()
{
	return this->health;
}

void Engine::setHealth(int health)
{
	this->health = health;
}

int Engine::getHeat()
{
	return this->heat;
}

void Engine::setHeat(int heat)
{
	this->heat = heat;
}