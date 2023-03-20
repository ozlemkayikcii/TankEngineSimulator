#include "Tank.h"

Tank::Tank()
{
	this->is_broken = 0;
	this->fuel_quantity = 0;
}

Tank::~Tank() {}

double Tank::getCapacity() const
{
	return this->capacity;
}

void Tank::setCapacity(double capacity)
{
	this->capacity = capacity;
}

double Tank::getFuelQuantity() const
{
	return fuel_quantity;
}

void Tank::setFuelQuantity(double quantity)
{
	this->fuel_quantity = quantity;
}

bool Tank::getBroken() const
{
	return this->is_broken;
}

void Tank::setBroken(bool is_broken)
{
	this->is_broken = is_broken;
}
