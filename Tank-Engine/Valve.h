#pragma once

class Valve
{
public:
	Valve();
	~Valve();
	bool getValveStatus() const;
	void setValveStatus(bool);
private:
	bool valve_status = false;
};