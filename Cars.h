class Cars{
public:
    Cars();
    void init(int plate, string type);
    bool isHeavyDuty();
    int getCarsPlate();
    string getCarsType();
    void setCarsPlate(int plate);
    void setCarsType(string type);

private:
    int carsPlate;
    string carsType;
};
