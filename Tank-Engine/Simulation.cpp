#include "Simulation.h"

Simulation::Simulation(Input input)
{
	input = input;
}

Simulation::~Simulation() {}

void Simulation::connectFuelTankToEngine(int id)  // Takes an already existing tank and connects it to Engine
{
	list<External> connected_tanks = engine->getListTankConnected();
	bool has_tank = false;
	bool is_succeeded = false;
	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			has_tank = true;
		}

		if (has_tank && !e_tank.getBroken())
		{
			is_succeeded = true;
			connected_tanks.push_back(e_tank);
			break;
		}
	}

	if (!has_tank)
	{
		output->giveOutput("Tank [ID: " + to_string(id) + "] could not be found.");
		return;
	}

	if (!is_succeeded)
	{
		output->giveOutput("Broken tank [ID: " + to_string(id) + "] could not get connected.");
		return;
	}

	engine->setListTankConnected(connected_tanks);
	output->giveOutput("Tank [ID: " + to_string(id) + "] is connected.");
}

void Simulation::disconnectFuelTankToEngine(int id)  // Disconnects a given tank from Engine
{
	list<External> connected_tanks = engine->getListTankConnected();
	bool has_tank = false;
	for (External& tank : engine->getListTankConnected())
	{
		if (tank.getId() == id)
		{
			has_tank = true;
			connected_tanks.remove(tank);
		}
	}

	if (!has_tank)
	{
		output->giveOutput("Tank [ID: " + to_string(id) + "] could not be found.");
		return;
	}

	engine->setListTankConnected(connected_tanks);

	if (engine->getStatus())  // Stops engine if disconnected a tank while running
	{
		engine->stopEngine();
		output->giveOutput("Tank [ID: " + to_string(id) + "] is disconnected and the engine is stopped.");
	}
	else
	{
		output->giveOutput("Tank [ID: " + to_string(id) + "] is disconnected.");
	}
}

void Simulation::addFuelTank(double capacity)  // Adds a new external fuel tank with given capacity
{
	External::counter++;
	External new_tank;
	new_tank.setId(External::counter);
	new_tank.setCapacity(capacity);
	tank_list.push_back(new_tank);
	output->giveOutput("Added a tank [ID: " + to_string(External::counter) + "] and capacity of " + to_string(capacity));
	observer = new ObserverTank();
    subject->registerObserver(observer);
}

void Simulation::removeFuelTank(int id)  // Remmoves an external fuel tank with given id from simuatlion
{
	bool has_tank = false;
	for (External& tank : tank_list)
	{
		if (tank.getId() == id)
		{
			has_tank = true;
			tank_list.remove(tank);
			output->giveOutput("Tank [ID: " + to_string(id) + "] is removed.");
			subject->unregisterObserver(observer);
			break;
		}
	}

	if (!has_tank)
	{
		output->giveOutput("Tank [ID: " + to_string(id) + "] could not be found.");
	}
}

void Simulation::fillTank(int id, double amount) // Increases the given tank's fuel quantity by the given parameter (amount) by using parameter of amount
{
	bool has_tank = false;
	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			has_tank = true;
			if (e_tank.getCapacity() - e_tank.getFuelQuantity() <= 0)
			{
				output->giveOutput("Tank [ID: " + to_string(id) + "] is already completely full.");
			}
			else if (e_tank.getCapacity() - e_tank.getFuelQuantity() <= amount)
			{
				e_tank.setFuelQuantity(e_tank.getCapacity());
				output->giveOutput("Tank [ID: " + to_string(id) + "] is completely topped up to full capacity " + to_string(e_tank.getCapacity()) + ".");
			}
			else
			{
				e_tank.setFuelQuantity(e_tank.getFuelQuantity() + amount);
				output->giveOutput("Tank [ID: " + to_string(id) + "] is topped up with " + to_string(amount) + " fuel.");
			}
		}
	}

	if (!has_tank)
	{
		output->giveOutput("Tank [ID: " + to_string(id) + "] could not be found.");
	}
}

void Simulation::repairEngine() // Repairs the engine if its broken
{
	if (engine->getStatus())
	{
		output->giveOutput("Engine cannot be reparied while it's running.");
		return;
	}

	if (engine->getHealth() == 0)  // Engine cannot be repaired if health is not 0
	{
		output->giveOutput("Engine cannot be reparied if health is above 0%.");
	}
	else
	{
		engine->setHealth(100);
	}
}

void Simulation::changeEngineBlock() // Sets the engine blocks as default
{
	if (engine->getStatus())
	{
		output->giveOutput("You cannot change the engine block  while engine is running.");
		return;
	}

	if (engine->getHealth() == 0)  // Engine block can only be changed if health is 0
	{
		engine->setHealth(100);
		engine->setHeat(20);
		output->giveOutput("Engine properties are reset.");
	}
	else
	{
		output->giveOutput("You cannot change the engine block if health is above 0.");
	}
}

void Simulation::openValve(int id)
{
	bool tank_exists = false;
	bool tank_connected = false;

	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			tank_exists = true;
		}

		for (External& e_tank_connected : engine->getListTankConnected())
		{
			if (e_tank_connected.getId() == e_tank.getId())
			{
				tank_connected = true;
			}
		}

		if (tank_exists && tank_connected)  // Only connected existing tanks can get their valves opened
		{
			e_tank.setValve(e_tank, true);
			output->giveOutput("The valve of Tank [ID: " + to_string(id) + "] is opened.");
			return;
		}
	}

	output->giveOutput("The valve cannot be opened. Tank [ID: " + to_string(id) + "] could not be found.");
}

void Simulation::closeValve(int id)
{
	bool tank_exists = false;
	bool tank_connected = false;

	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			tank_exists = true;
		}

		for (External& e_tank_connected : engine->getListTankConnected())
		{
			if (e_tank_connected.getId() == e_tank.getId())
			{
				tank_connected = true;
			}
		}

		if (tank_exists && tank_connected)
		{
			e_tank.setValve(e_tank, true);
			output->giveOutput("The valve of Tank [ID: " + to_string(id) + "] is opened.");
			return;
		}
		
		output->giveOutput("The valve cannot be closed. Tank [ID: " + to_string(id) + "] could not be found.\n");
	}
}

void Simulation::wait(double seconds)
{
	if (engine->getHeat() > 130)  // Hotter than 130C will damage the engine by 1% health every second
	{
		engine->setHealth(engine->getHealth() - (int)seconds);
	}

	if (engine->getHealth() <= 0)
	{
		engine->stopEngine();
		output->giveOutput("Engine broke and stopped.");
	}

	if (engine->getStatus() == false)
	{
		if (engine->getHeat() > 20)  // While engine isn't running, it cools down 1C per second
		{
			engine->setHeat(engine->getHeat() - (int)seconds);
		}
		return;
	}

	double consumption_multiplier = engine->getFullThrottle() ? 5.0 : 1.0;  // Full-throttle consumes 5x fuel
	double consumed_fuel = engine->getFuelPerSecond() * seconds * consumption_multiplier;
	double left_fuel = engine->getInternal().getFuelQuantity();

	if (left_fuel >= consumed_fuel)
	{
		engine->getInternal().setFuelQuantity(engine->getInternal().getFuelQuantity() - consumed_fuel);
		total_consumed_fuel += consumed_fuel;
	}
	else // Fuel left in internal tank isn't enough for running
	{
		engine->getInternal().setFuelQuantity(0);
		engine->stopEngine();
		output->giveOutput("Engine ran out of fuel and stopped.");
		return;
	}
		
	if (engine->getFullThrottle())
	{
		engine->setHeat(engine->getHeat() + 5 * (int)seconds);  // Full-throttle engine heats up 5C per second
		if (engine->getHeat() < 90)
		{
			engine->setHealth(engine->getHealth() - (int)seconds);  // Damages the engine health by 1% per second if the it's colder than 90C
		}
	}

	if (engine->getInternal().getFuelQuantity() < 20)  // Internal tank absorbs fuel from external tanks when it falls below 20 units
	{
		for (External& e_tank : tank_list)
		{
			double amount = e_tank.getFuelQuantity();
			if (amount > 0)
			{
				double remaining_capacity = engine->getInternal().getCapacity() - engine->getInternal().getFuelQuantity();
				amount = amount >= remaining_capacity ? remaining_capacity : amount;  // Amount cannot be higher than remaining capacity of internal tank


				if (e_tank.getValve().getValveStatus() == true)  // Valve needs to be on for absorption
				{
					e_tank.setFuelQuantity(e_tank.getFuelQuantity() - amount);
					engine->setInternalFuelQuantity(engine->getInternal().getFuelQuantity() + amount);
					output->giveOutput("The internal tank absorbed " + to_string(amount) + " fuel from Tank [ID: " + to_string(e_tank.getId()) + "].");
					return;
				}
			}
		}
	}
}

void Simulation::printTankInfo(int id)
{
	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			string outFile = "ID: " + to_string(e_tank.getId()) + "\tCapacity: " + to_string(e_tank.getCapacity()) + "\tFuel quantity: " 
									+ to_string(e_tank.getFuelQuantity()) + "\tBroken status: " + to_string(e_tank.getBroken()) + "\tValve status: " + to_string(e_tank.getValve().getValveStatus());
			output->giveOutput(outFile);
		}
	}
}

void Simulation::repairFuelTank(int id)
{
	bool tank_exists = false;
	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			tank_exists = true;
			if (e_tank.getBroken())
			{
				e_tank.setBroken(false);
				output->giveOutput("The tank [ID: " + to_string(id) + "] is repaired.");
			}
			else
			{
				output->giveOutput("The tank [ID: " + to_string(id) + "] is already repaired.");
			}
		}
	}

	if (!tank_exists)
	{
		output->giveOutput("The tank cannot be repaired. Tank [ID: " + to_string(id) + "] could not be found.");
	}
}

void Simulation::breakFuelTank(int id)
{
	bool tank_exists = false;
	bool is_succeeded = false;
	for (External& e_tank : tank_list)
	{
		if (e_tank.getId() == id)
		{
			tank_exists = true;
		}

		if (tank_exists && !e_tank.getBroken())
		{
			e_tank.setBroken(true);
			is_succeeded = true;
			break;
		}
	}

	if (!tank_exists)
	{
		output->giveOutput("The tank cannot be broken. Tank [ID: " + to_string(id) + "] could not be found.\n");
		return;
	}

	if (!is_succeeded)
	{
		output->giveOutput("The tank cannot be broken. Tank [ID: " + to_string(id) + "] is already broken.");
		return;
	}

	disconnectFuelTankToEngine(id);
	output->giveOutput("The tank [ID: " + to_string(id) + "] is broken and disconnected.");
}

void Simulation::listFuelTanks()
{
	for (External& e_tank : tank_list)
	{
			output->giveOutput("Tank ID: " + to_string(e_tank.getId()) + "\tCapacity: " + to_string(e_tank.getCapacity()) + "\tFuel quantity: " 
										  + to_string(e_tank.getFuelQuantity()) + "\tBroken status: " + to_string(e_tank.getBroken()) + "\tValve status: " + to_string(e_tank.getValve().getValveStatus()));
	}
}

void Simulation::listConnectedTanks()
{
	for (External& e_tank : engine->getListTankConnected())
	{
		if (e_tank.getValve().getValveStatus())
		{
			output->giveOutput("Tank ID: " + to_string(e_tank.getId()) + "\tCapacity: " + to_string(e_tank.getCapacity()) + "\tFuel quantity: " 
										  + to_string(e_tank.getFuelQuantity()) + "\tBroken status: " + to_string(e_tank.getBroken()) + "\tValve status: " + to_string(e_tank.getValve().getValveStatus()));

		}
	}
}

void Simulation::printFuelTankCount()
{
	output->giveOutput("Fuel Tank Count: " + to_string(tank_list.size()));
}

void Simulation::printTotalFuel()
{
	double total_fuel = 0;
	for (Tank& tank : tank_list)
	{
		total_fuel += tank.getFuelQuantity();
	}
	output->giveOutput("Total Fuel Quantity: " + to_string(total_fuel));
}

void Simulation::printTotalConsumedFuel()
{
	output->giveOutput("Total Consumed Fuel Quantity: " + to_string(total_consumed_fuel));
}

void Simulation::sum_operator(External &Tank1, External &Tank2, External &Tank3) {

	// For sum operation all of the given tanks’ valves must be on open state.
	if (Tank1.getValve().getValveStatus() && Tank2.getValve().getValveStatus() && Tank3.getValve().getValveStatus()) {
		
		double remaining_capacity = Tank1.getCapacity() - Tank1.getFuelQuantity();
		double quantityToBeFilled = Tank2.getFuelQuantity() + Tank3.getFuelQuantity();

		
		if (remaining_capacity - quantityToBeFilled < 0)
		{
			// There is no enough space in the tank 1
			output->giveOutput("There is no enough space in Tank " + Tank1.getCounter());
		}
		else if (remaining_capacity - quantityToBeFilled >= 0)
		{
			// Writing a statement Tank1 = tank2 + tank3 would cause loss of information for tank1
			// So creating a temp with only purpose of carrying the quantity would do good
			// And then set the quantity of tank1.
			External temp;
			temp = Tank2 + Tank3;
			Tank1.setFuelQuantity(Tank1.getFuelQuantity() + temp.getFuelQuantity());
			Tank2.setFuelQuantity(0);
			Tank3.setFuelQuantity(0);
		}
	}
	else {
		// At least one of the three valve are not opened
		output->giveOutput("Valves are not opened.");
	}
	
}

void Simulation::stopSimulation()
{
	exit(0);
}

void Simulation::processCommands(vector<string> commands)
{
	for (unsigned int i = 0; i < commands.size(); i++)
	{
		if (commands[i] == "start_engine;")
		{
			if (engine->getStatus())
			{
				output->giveOutput("Engine already running.");
				observer = new ObserverEngine();
				subject->registerObserver(observer);
			}
			else
			{
				engine->startEngine();
				output->giveOutput("Engine started.");
			}

			if (!engine->getStatus())
			{
				output->giveOutput("Engine could not be started.");
			}
		}
		else if (commands[i].find("fill_tank") != string::npos)
		{
			int id = (int)line.readValues(commands[i]).at(0);
			double amount = line.readValues(commands[i]).at(1);
			fillTank(id, amount);
			wait(1);
		}
		else if (commands[i] == "stop_engine;")
		{
			engine->stopEngine();

		}
		else if (commands[i] == "change_engine_block;")
		{
			changeEngineBlock();
		}
		else if (commands[i].find("add_fuel_tank") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			addFuelTank(n);
			wait(1);
		}
		else if (commands[i].find("connect_fuel_tank_to_engine") != string::npos)
		{
			int tank_id = (int)line.readValues(commands[i]).at(0);
			connectFuelTankToEngine(tank_id);
			wait(1);
		}
		else if (commands[i].find("remove_fuel_tank") != string::npos)
		{
			int tank_id = (int)line.readValues(commands[i]).at(0);
			removeFuelTank(tank_id);
			wait(1);
		}
		else if (commands[i].find("disconnect_fuel_tank_from_engine") != string::npos)
		{
			int tank_id = (int)line.readValues(commands[i]).at(0);
			disconnectFuelTankToEngine(tank_id);
			wait(1);
		}
		else if (commands[i].find("wait") != string::npos)
		{
			int seconds = (int)line.readValues(commands[i]).at(0);
			wait(seconds);
		}
		else if (commands[i].find("full_throttle") != string::npos)
		{
			engine->setFullThrottle(true);
			double seconds = line.readValues(commands[i]).at(0);
			wait(seconds);
			engine->setFullThrottle(false);
		}
		else if (commands[i] == "repair_engine;")
		{
			repairEngine();
			wait(1);
		}
		else if (commands[i] == "change_engine_block;")
		{
			changeEngineBlock();
			wait(1);
		}
		else if (commands[i].find("open_valve") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			openValve(n);
			observer = new ObserverValve();
			subject->registerObserver(observer);
			wait(1);
		}
		else if (commands[i].find("close_valve") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			closeValve(n);
			wait(1);
		}
		else if (commands[i] == "list_fuel_tanks;")
		{
			listFuelTanks();
			wait(1);
		}
		else if (commands[i] == "print_fuel_tank_count;")
		{
			printFuelTankCount();
			wait(1);
		}
		else if (commands[i] == "list_connected_tanks;")
		{
			listConnectedTanks();
			wait(1);
		}
		else if (commands[i].find( "break_fuel_tank") != string::npos)
		{
		    int n = (int)line.readValues(commands[i]).at(0);
			breakFuelTank(n);
			wait(1);
		}
		else if (commands[i].find("repair_fuel_tank") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			repairFuelTank(n);
			wait(1);
		}
		else if (commands[i] == "print_total_fuel_quantity;")
		{
			printTotalFuel();
			wait(1);
		}
		else if (commands[i] == "print_total_consumed_fuel_quantity;")
		{
			printTotalConsumedFuel();
			wait(1);
		}
		else if (commands[i].find("print_tank_info") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			printTankInfo(n);
			wait(1);
		}
		else if (commands[i].find("sum_operator") != string::npos)
		{
			int n = (int)line.readValues(commands[i]).at(0);
			int m = (int)line.readValues(commands[i]).at(1);
			int l = (int)line.readValues(commands[i]).at(2);

			External tanks[3];

			for (External& tank : tank_list)
			{
				if (tank.getId() == n)
				{
					tanks[0] = tank;
				}
				else if (tank.getId() == m)
				{
					tanks[1] = tank;
				}
				else if (tank.getId() == l)
				{
					tanks[2] = tank;
				}
			}
			sum_operator(tanks[0], tanks[1], tanks[2]);
			for (External& tank : tank_list)
			{
				if (tank.getId() == n)
				{
					tank = tanks[0];
				}
				else if (tank.getId() == m)
				{
					tank = tanks[1] ;
				}
				else if (tank.getId() == l)
				{
					tank = tanks[2];
				}
			}
			wait(1);
		}
		else if (commands[i] == "stop_simulation;")
		{
		    subject->notifyObservers();
			stopSimulation();
		}
	}
}