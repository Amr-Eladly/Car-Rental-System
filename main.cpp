#include <fstream>
#include "cars.h"


int main()
{
    system("color E1");
    fstream file;
    string file_name = "cars_data.txt";
    file.open(file_name, ios::in | ios::out | ios::app);

    if (!file.is_open())
    {
        cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    System carSystem;
    carSystem.getFileCars("cars_data.txt");
    int C;
    C = Menu();
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    time_point<high_resolution_clock> stop = high_resolution_clock::now();


    while (C != 7)
    {
        if (C == 1)
        {
            Car* newCar = create_car();
            carSystem.addCar(newCar);
            carSystem.savecars("cars_data.txt");
        }
        else if (C == 2)
        {
            string model, unusedline;
            cout << "\nEnter the car model (for example : BMW I3) : ";
            getline(cin, unusedline);
            getline(cin, model);
            carSystem.deleteCar(model);
            carSystem.savecars("cars_data.txt");
        }
        else if (C == 3)
        {
            carSystem.displaycars();
        }
        else if (C == 4)
        {
            carLookUp(carSystem);
        }
        else if (C == 5)
        {
            string model, unusedline;
            cout << "\nEnter the car model (for example : BMW I3) : ";
            getline(cin, unusedline);
            getline(cin, model);
            carSystem.rentCar(model);
            auto start = std::chrono::high_resolution_clock::now();
            carSystem.savecars("cars_data.txt");
        }
        else if (C == 6)
        {
            string model, unusedline;
            cout << "\nEnter the car model (for example : BMW I3) : ";
            getline(cin, unusedline);
            getline(cin, model);
            carSystem.returnCar(model);
            carSystem.savecars("cars_data.txt");
        }
        C = Menu();
    }

    file.close();
    return 0;
}