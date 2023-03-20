#define EXTERNAL_H_
#include "Tank.h"

class External :public Tank {
public:
	External();
	~External();
	static int counter;
	static int getCounter();
	int getId() const;
	void setId(int&);
	Valve& getValve();
	void setValve(External&, bool);
	External operator+(External& e_tank);
	bool operator == (const External& e_tank) const;
	bool operator != (const External& e_tank) const;
private:
	int id;
	Valve valve;
};