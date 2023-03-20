#ifndef OBSERVER_H
#define OBSERVER_H
#include<iostream>
using namespace std;

class Observer    // Abstract Class
{
public:
	virtual void update() = 0;  // Pure Virtual Function
};
#endif