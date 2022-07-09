#include <iostream>
using namespace std;
#include "Cars.h"

//simple car constructor
Cars::Cars()
{
    carsPlate = 0;
    carsType = "+";
}

//checks whether car is heavy duty car or not
bool Cars::isHeavyDuty()
{
    if(carsType == "b")
        return true;
    return false;
}

//initializes the car with given values
void Cars::init(int plate, string type)
{
    carsPlate = plate;
    carsType = type;
}

//getter for car plate
int Cars::getCarsPlate()
{
    return carsPlate;
}

//getter for car type
string Cars::getCarsType()
{
    return carsType;
}

//setter for car plate
void Cars::setCarsPlate(int plate)
{
    carsPlate = plate;
}

//setter for car type
void Cars::setCarsType(string type)
{
    carsType = type;
}
