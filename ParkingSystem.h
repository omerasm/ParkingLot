#include "Lot.h"

class ParkingSystem{
public:
    ParkingSystem();
    ~ParkingSystem();
    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId, string location, string carType, int plateNumber);
    void findCar(int id);
    void removeCar(int id);
private:
    int numberOfLots;
    Lot *lots;
};
