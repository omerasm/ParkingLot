#include <iostream>
#include <string>
using namespace std;
#include "Lot.h"

//simple constructor
Lot::Lot()
{
    lotId = 0;
    row = 0;
    column = 0;
}

//copy constructor
Lot::Lot(Lot &obj)
{
    lotId = obj.getLotId();
    row = obj.getLotRow();
    column = obj.getLotColumn();
    lotArr = new Cars*[row];

    for (int i = 0; i < row; ++i)
    {
        lotArr[i] = new Cars[column];

        for (int j = 0; j < column; ++j)
            lotArr[i][j] = obj.lotArr[i][j];
    }
}

//destructor
Lot::~Lot()
{
    if(lotId)
    {
        for ( int i = 0 ; i < row; ++i)
            delete [] lotArr[i];
        delete [] lotArr;
    }
}

//init functon
void Lot::init(int id, int rows, int columns)
{
    lotId = id;
    row = rows;
    column = columns;

    lotArr = new Cars*[row];

    for (int i = 0; i < row; ++i)
    {
        lotArr[i] = new Cars[column];
        for(int j = 0; j < column; ++j)
            lotArr[i][j] = Cars();
    }
}

//getter for column
int Lot::getLotColumn()
{
    return column;
}

//getter for row
int Lot::getLotRow()
{
    return row;
}

//getter for id
int Lot::getLotId()
{
    return lotId;
}

//checks whether that position is available or not
int Lot::checkAvailability(int rows, int columns)
{
    if(rows == 0 && lotArr[rows][columns].getCarsType() == "+")
        return 1;
    if ( lotArr[rows][columns].getCarsType() == "+" && lotArr[rows-1][columns].getCarsType() == "+")
        return 2;
    if ( lotArr[rows][columns].getCarsType() == "+" )
        return 1;
    return 0;
}

//returns positions with string from integers
string Lot::locationStr(int rows, int columns)
{
    string strRow;
    string strColumn;

    strRow = (char) (rows + 65);

    switch(columns + 1){
        case 1:
            strColumn = "1";
            break;
        case 2:
            strColumn = "2";
            break;
        case 3:
            strColumn = "3";
            break;
        case 4:
            strColumn = "4";
            break;
        case 5:
            strColumn = "5";
            break;
        case 6:
            strColumn = "6";
            break;
        case 7:
            strColumn = "7";
            break;
        case 8:
            strColumn = "8";
            break;
        case 9:
            strColumn = "9";
            break;
        case 10:
            strColumn = "10";
            break;
        case 11:
            strColumn = "11";
            break;
        case 12:
            strColumn = "12";
    }

    return (strRow + strColumn);
}

//returns the number of empty parking lot spots
int Lot::numberOfEmptySlots()
{
    int counter = 0;

    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(lotArr[i][k].getCarsType() == "+" )
                counter++;
        }
    }
    return counter;
}

//checks whether car with certain id exist
bool Lot::isCarsExist(int id)
{
    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(lotArr[i][k].getCarsPlate() == id )
                return true;
        }
    }
    return false;
}

//lists the parked cars in parking lot
void Lot::parkedCars()
{
    bool punctiation = false;
    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(lotArr[i][k].getCarsPlate() != 0 )
            {
                if(punctiation)
                    cout << ", ";
                cout << lotArr[i][k].getCarsPlate();
            }
            punctiation = true;
        }
    }
}

void Lot::lotRemoved()
{
    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(lotArr[i][k].getCarsPlate() != 0 )
            {
                if(lotArr[i][k].getCarsType() == "b")
                    cout << "Heavy-duty car with number plate " << lotArr[i][k].getCarsPlate() << " has been removed from slot " << locationStr(i,k) <<", lot " << lotId << endl;
                else
                    cout << "Light-duty car with number plate " << lotArr[i][k].getCarsPlate() << " has been removed from slot " << locationStr(i,k) <<", lot " << lotId << endl;
            }
        }
    }
}

