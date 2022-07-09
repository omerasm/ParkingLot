#include "Cars.h"

class Lot{
public:
    Lot();
    Lot(Lot &obj);
    ~Lot();
    void init(int id, int rows, int columns);
    int getLotColumn();
    int getLotRow();
    int getLotId();
    int checkAvailability(int rows, int columns);
    string locationStr(int rows, int columns);
    int numberOfEmptySlots();
    bool isCarsExist(int id);
    void parkedCars();
    void lotRemoved();

    Cars **lotArr;
private:
    int lotId;
    int row;
    int column;
};
