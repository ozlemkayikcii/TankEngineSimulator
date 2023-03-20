#pragma once
#include "Valve.h"

class Tank
{
public:
	Tank();
	~Tank();
	double getCapacity() const;
	void setCapacity(double);
	double getFuelQuantity() const;
	void setFuelQuantity(double);
	bool getBroken() const;
	void setBroken(bool);
protected:
	bool is_broken;
	double capacity;
	double fuel_quantity;
};