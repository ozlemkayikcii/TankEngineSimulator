#include "External.h"

External::External() :Tank() {}

External::~External() {}

External External::operator+(External& e_tank)
{
	// This command wil fill tank 1
	e_tank.setFuelQuantity(this->getFuelQuantity() + e_tank.getFuelQuantity());
	this->setFuelQuantity(0);
	return e_tank;
}

int External::counter = 0;

int External::getCounter()
{
	return counter;
}

Valve& External::getValve()
{
	return valve;
}

void External::setValve(External& e_tank, bool is_open)
{
	this->valve.setValveStatus(is_open);
}

int External::getId()const
{
	return this->id;
}

void External::setId(int& id)
{
	this->id = id;
}

bool External::operator == (const External& e_tank) const
{
	return id == e_tank.getId();
}

bool External::operator != (const External& e_tank) const
{
	return id != e_tank.getId();
}
