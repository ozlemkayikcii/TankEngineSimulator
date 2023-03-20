#include "Valve.h"

Valve::Valve(){}

Valve::~Valve(){}

bool Valve::getValveStatus() const
{
	return this->valve_status;
}

void Valve::setValveStatus(bool is_on)
{
	this->valve_status = is_on;
}