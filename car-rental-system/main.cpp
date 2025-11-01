#include <iostream>
#include <fstream>
#include "cars.h"
using namespace std;

int main()
{
    // Set console color (Windows only - comment out for cross-platform)
#ifdef _WIN32
    system("color E1");
#endif

    string file_name = "cars_data.txt";

    // Initialize the car rental system
    System carSystem;

    // Load existing car data from file (if file exists)
    carSystem.getFileCars(file_name);

    int choice;
    choice = Menu();

    // Main program loop - continues until user chooses to exit (option 7)
    while (choice != 7)
    {
        if (choice == 1)  // Add a new car
        {
            Car* newCar = create_car();
            carSystem.addCar(newCar);
            carSystem.savecars(file_name);
        }
        else if (choice == 2)  // Delete a car
        {
            string model;
            cout << "\nEnter the car model (for example: I3 for BMW I3): ";
            cin.ignore();  // Clear input buffer
            getline(cin, model);
            carSystem.deleteCar(model);
            carSystem.savecars(file_name);
        }
        else if (choice == 3)  // View all cars
        {
            carSystem.displaycars();
        }
        else if (choice == 4)  // Search for a car
        {
            carLookUp(carSystem);
        }
        else if (choice == 5)  // Rent a car
        {
            string model;
            cout << "\nEnter the car model (for example: I3 for BMW I3): ";
            cin.ignore();  // Clear input buffer
            getline(cin, model);
            carSystem.rentCar(model);
            carSystem.savecars(file_name);
        }
        else if (choice == 6)  // Return a car
        {
            string model;
            cout << "\nEnter the car model (for example: I3 for BMW I3): ";
            cin.ignore();  // Clear input buffer
            getline(cin, model);
            carSystem.returnCar(model);
            carSystem.savecars(file_name);
        }

        // Display menu again for next operation
        choice = Menu();
    }

    // Final save before exiting
    carSystem.savecars(file_name);

    cout << "\nThank you for using the Car Rental System. Goodbye!\n";

    return 0;
}