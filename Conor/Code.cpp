#include <iostream>
#include <string.h>
using namespace std;

class Sensor;
class Reading;
class Observation;
class Button;
class Observation_Log

//! Base Sensor class
/********************************************//**
Abstract base class Sensor, to be used to implement different types of sensors.
***********************************************/
class Sensor
{
	public:

    //! Fully-defined Sensor constructor.
	/*!
	    \param d_id an integer value of the desired ID.
	    \param d_description a string of the desired Sensor description.
	    \param d_units a string describing the desired units for the Sensor.
	*/
	Sensor(int d_id, string d_description, string d_units)
	{
		ID = d_id;
		description = d_description;
		units = d_units;
	}

	//! Sensor constructor requiring only a Sensor ID.
	/*!
        Allows a Sensor to be declared without needing to set its description or units. These can be set separately using the relevant member functions.
	    \param d_id an integer value of the desired ID.
	    \sa setDescription()
	    \sa setUnits()
	*/
	Sensor(int d_id)
	{
		ID = d_id;
		description = "No description.";
		units = "No units.";
	}

	//! A pure virtual member function to return a reading from the Sensor.
	/*!

	*/
	virtual Reading getReading() = 0;

	//! A member function to set the Sensor's ID.
	/*!
	    \param d_id an integer value of the desired ID.
	*/
	void setID(int d_id)
	{
		ID = d_id;
	}

	//! A member function to set the Sensor's description.
	/*!
	    \param d_description a string of the desired Sensor description.
	*/
	void setDescription(string d_description)
	{
		description = d_description;
	}

	//! A member function to set the Sensor's units.
	/*!
	    \param d_units a string describing the desired units for the Sensor.
	*/
	void setUnits(string d_units)
	{
		units = d_units;
	}

	protected:
	//! Sensor ID variable.
	int ID;
	//! Sensor Description string.
	string description;
	//! Sensor units in which the data is presented.
	string units;
};

//! Reading class
/********************************************//**
Class for a Reading, which is created by a Sensor, and has a data value, units, and a pointer to the Sensor it recorded from.
***********************************************/
class Reading
{
    public:

    //! Reading constructor for creating a new reading.
	/*!
        Allows a Sensor to be declared without needing to set its description or units. These can be set separately using the relevant member functions.
	    \param val the value of the recorded reading.
	    \param d_units a string describing the units of the reading value.
	    \param *sens_source, a pointer to the Sensor which measured the Reading.
	*/
	Reading(double val, string d_units, Sensor *sens_source)
	{
		value = val;
		units = d_units;
		source = sens_source;
	}

    protected:
    //! Variable containing value of recorded reading.
	double value;
	//! String containing units of recorded reading.
	string units;
	//! Pointer to the Sensor from which the recording came from.
	Sensor *source;
};

//! Observation class
/********************************************//**
Class for Observations, which are a collection of one to many different Readings, and a timestamp of when the Readings were recorded.
***********************************************/
class Observation
{
    public:

    //! A member function to add a Reading from a given Sensor to the Observation's list of Readings.
	/*!
	    \param *sens a pointer to the Sensor to get a Reading from.
	*/
    void addReading(Sensor *sens)
    {

    }

    //! A member function to return a Reading contained in the Observation from a specified Sensor.
	/*!
	    \param sens_ID, the ID of the Sensor to return the Reading from.
	*/
    Reading getReading(int sens_ID)
    {

    }

    protected:

    Reading readings[];
    //! Timestamp of when the readings were recorded.
	string timestamp;
};

//! Observation_Log class
/********************************************//**
Class for a log of Observations, which are a collection of one to many different Observations.
***********************************************/
class Observation_Log
{
    public:

    //! A member function to add an Observation to the Observation log.
	/*!
	    \param *obs a pointer to the Observation object to add to the log.
	*/
    void addObservation(Observation *obs)
    {

    }

    //! A member function to return an Observation from a specified time.
	/*!
	    \param time, the timestamp of the desired Observation.
	*/
    Observation getObservation(string time)
    {

    }

    protected:

    Observation log[];
};

//! Base Button class
/********************************************//**
Base class for the buttons used to select options from the system's menu.
***********************************************/
class Button
{
    public:

	//! A pure virtual member function to perform an action when the button is pressed.
	/*!

	*/
	virtual void push() = 0;

	//! A member function to set the Button's ID.
	/*!
	    \param d_id an integer value of the desired ID.
	*/
	void setID(int d_id)
	{
		ID = d_id;
	}

	protected:
	//! Button ID variable.
	int ID;
};


int main(void)
{
	return 0;
}
