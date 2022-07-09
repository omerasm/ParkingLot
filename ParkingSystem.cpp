#include <iostream>
using namespace std;
#include "ParkingSystem.h"

//simple constructor
ParkingSystem::ParkingSystem()
{
    numberOfLots = 0;
}

//destructor
ParkingSystem::~ParkingSystem()
{
    if (numberOfLots)
        delete [] lots;
    numberOfLots = 0;
}

//function for creating lots
void ParkingSystem::createLot(int id, int rows, int columns)
{
    for (int i = 0; i < numberOfLots; ++i)
    {
        if (id == lots[i].getLotId())
        {
             cout << "Cannot create the parking lot " << id << ", a lot with this ID already exists" << endl;
             return;
        }
    }

    if( rows > 12 || columns > 12)
    {
        cout << "Cannot create the parking lot " << id << ", dimensions exceed acceptable bounds" << endl;
        return;
    }

    Lot *substitue = lots;
    lots = new Lot[numberOfLots + 1];

    for (int i = 0; i < numberOfLots; ++i)
    {
        lots[i].init(substitue[i].getLotId(), substitue[i].getLotRow(), substitue[i].getLotColumn());
    }

    lots[numberOfLots].init(id, rows, columns);

    numberOfLots++;

    //deletes the substitue
    if (numberOfLots != 1)
        delete [] substitue;

    cout << "Parking lot with ID " << id << " and dimensions (" << rows << "," << columns << ") has been added to the system" << endl;
}

//function for removing existing lots
void ParkingSystem::removeLot(int id)
{
    int check = -1;
    for (int i = 0; i < numberOfLots; ++i)
    {
        if (lots[i].getLotId() == id)
        {
            check = i;
        }
    }
    if (check == -1)
    {
        cout<< "Lot "<< id << " is not in the system"<< endl ;
        return;
    }
    lots[check].lotRemoved();
    Lot *substitue = new Lot[numberOfLots - 1];
    int counter = 0;
    for (int i = 0; i < numberOfLots; ++i)
    {
        if( lots[i].getLotId() != id)
        {
            substitue[counter].init(lots[i].getLotId(), lots[i].getLotRow(), lots[i].getLotColumn());
            counter++;
        }
    }

    delete [] lots ;

    lots = substitue;
    numberOfLots--;
    cout<< "Lot " << id << " has been successfully removed from the system" << endl;
}

//listing lots and their contents
void ParkingSystem::listLots()
{
    if( numberOfLots == 0 )
    {
        cout << "no lots to list" << endl;
        return;
    }
    cout << "List of lots:\n";
    for (int i = 0; i < numberOfLots; ++i)
        cout << "ID:" << lots[i].getLotId() << ", Dim: (" << lots[i].getLotRow() << "," << lots[i].getLotColumn() << "), number of empty parking spaces: " << lots[i].numberOfEmptySlots() << endl;
}

//listing lot contents in 2d table
void ParkingSystem::lotContents(int id)
{
    for (int i = 0; i < numberOfLots; ++i)
    {
        if (lots[i].getLotId() == id)
        {
            cout << "ID: " << lots[i].getLotId() << ", (" << lots[i].getLotRow() << "," << lots[i].getLotColumn() << "), empty slots: " <<  lots[i].numberOfEmptySlots() << ", parked cars: ";
            lots[i].parkedCars();
            cout << endl;
            cout << "  ";
            for(int j = 1; j < lots[i].getLotColumn() + 1; ++j)
                cout << j << " ";
            cout << endl;
            for(int k = 0; k < lots[i].getLotRow(); ++k)
            {
                cout << char(k + 65) << " ";
                for(int l = 0; l < lots[i].getLotColumn(); ++l){
                    if ( l < 9)
                        cout << lots[i].lotArr[k][l].getCarsType() << " ";
                    else
                        cout << lots[i].lotArr[k][l].getCarsType() << "  ";
                }
                cout << endl;
            }
            return;
        }
    }
}

//parking car
void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber)
{
    int row;
    int column;
    int check = -1;
    for (int i = 0; i < numberOfLots; ++i)
    {
        if (lots[i].getLotId() == lotId)
        {
            check = i;
        }
        if(lots[i].isCarsExist(plateNumber) && check != -1)
        {
            cout << "Cannot park the car with id " << plateNumber << ", already exist in the system" << endl;
            return;
        }
    }

    if (check == -1)
    {
        cout<< "Lot "<< lotId << " does not exist in the system"<< endl ;
        return;
    }

    row = int(location.at(0)) - int('A');
    column = int(location.at(1)) - int('1');

    if(carType == "b"){
        if (lots[check].checkAvailability(row, column) == 2)
        {
            lots[check].lotArr[row][column].setCarsPlate(plateNumber);
            lots[check].lotArr[row][column].setCarsType(carType);
            lots[check].lotArr[row-1][column].setCarsType(carType);
            cout << "Heavy-duty car with number plate " << plateNumber << " has been parked at location " << lots[check].locationStr(row,column) << ", lot " << lotId << endl;
            return;
        }
        if(lots[check].checkAvailability(row, column) == 1)
        {
            cout << "Cannot park heavy-duty car with number plate " << plateNumber << " at location " << lots[check].locationStr(row,column) << ", not enough space"<< endl;
            return;
        }
        else
        {
            cout << "Cannot park heavy-duty car with number plate " << plateNumber << " at location " << lots[check].locationStr(row,column) << ", already occupied"<< endl;
            return;
        }
    }
    if(carType == "a"){
        if (lots[check].checkAvailability(row, column))
        {
            lots[check].lotArr[row][column].setCarsPlate(plateNumber);
            lots[check].lotArr[row][column].setCarsType(carType);
            cout << "Light-duty car with number plate " << plateNumber << " has been parked at location " << lots[check].locationStr(row,column) << ", lot " << lotId << endl;
            return;
        }
        else
        {
            cout << "Cannot park light-duty car with number plate " << plateNumber << " at location " << lots[check].locationStr(row,column) << ", already occupied"<< endl;
            return;
        }
    }
}

//finding car in system
void ParkingSystem::findCar(int id)
{
    for(int i = 0; i < numberOfLots; ++i)
    {
        for(int j = 0; j < lots[i].getLotRow(); ++j)
        {
            for(int k = 0; k < lots[i].getLotColumn(); ++k)
            {
                if(lots[i].lotArr[j][k].getCarsPlate() == id)
                {
                    if(lots[i].lotArr[j][k].getCarsType() == "b" )
                    {
                        cout << "Heavy-duty car with number plate " << id << " is at location " << lots[i].locationStr(j,k) <<", lot " << lots[i].getLotId() << endl;
                        return;
                    }
                    cout << "Light-duty car with number plate " << id << " is at location " << lots[i].locationStr(j,k) <<", lot " << lots[i].getLotId() << endl;
                    return;
                }

            }
        }
    }
    cout << "The car with number plate " << id << " is not in the system"<< endl;
    return;
}

//removing existing car
void ParkingSystem::removeCar(int id)
{
    for(int i = 0; i < numberOfLots; ++i)
    {
        for(int j = 0; j < lots[i].getLotRow(); ++j)
        {
            for(int k = 0; k < lots[i].getLotColumn(); ++k)
            {
                if(lots[i].lotArr[j][k].getCarsPlate() == id)
                {
                    if(lots[i].lotArr[j][k].getCarsType() == "a")
                    {
                        lots[i].lotArr[j][k].setCarsPlate(0);
                        lots[i].lotArr[j][k].setCarsType("+");
                        cout << "Light-duty car with number plate " << id << " has been removed from slot " << lots[i].locationStr(j,k) <<", lot " << lots[i].getLotId() << endl;
                        return;
                    }
                    if(lots[i].lotArr[j][k].getCarsType() == "b")
                    {
                        lots[i].lotArr[j][k].setCarsPlate(0);
                        lots[i].lotArr[j][k].setCarsType("+");
                        lots[i].lotArr[j-1][k].setCarsType("+");
                        cout << "Heavy-duty car with number plate " << id << " has been removed from slot " << lots[i].locationStr(j,k) <<", lot " << lots[i].getLotId() << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "The car with number plate " << id << " is not in the system" << endl;
}
