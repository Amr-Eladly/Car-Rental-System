#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include "cars.h"
using namespace std;
using namespace std::chrono;

// Constructor: Initializes all car attributes
Car::Car(string brand, string model, int year, int regNO, double mileage, bool available)
    : brand(brand), model(model), year(year), regNO(regNO), mileage(mileage), available(available) {
}

Car::~Car() {}

// Getter methods return private member variables
string Car::get_brand() const
{
    return brand;
}

string Car::get_model() const
{
    return model;
}

int Car::get_year() const
{
    return year;
}

int Car::get_regNO() const
{
    return regNO;
}

double Car::get_mileage() const
{
    return mileage;
}

bool Car::isAvailable() const
{
    return available;
}

// Mark car as rented (unavailable)
void Car::rentCar()
{
    available = false;
}

// Mark car as returned (available)
void Car::returnCar()
{
    available = true;
}


// Constructor: Initializes customer data with default license status as valid
Customer::Customer(string name, string idNo, string licenseNo, string address, string email)
    : name(name), idNo(idNo), licenseNo(licenseNo), address(address), email(email),
    license_status(true), membership(false) {
}

string Customer::get_name() const
{
    return name;
}

string Customer::get_idNo() const
{
    return idNo;
}

string Customer::get_licenseNo() const
{
    return licenseNo;
}

string Customer::get_address() const
{
    return address;
}

string Customer::get_email() const
{
    return email;
}

bool Customer::isValid() const
{
    return license_status;
}

void Customer::becomeCustomer()
{
    membership = true;
}

void Customer::cancelMembership()
{
    membership = false;
}

// Destructor: Clean up all dynamically allocated Car objects to prevent memory leaks
System::~System()
{
    for (Car* car : cars)
    {
        delete car;
    }
    cars.clear();
}

// Add a car pointer to the system's inventory
void System::addCar(Car* car)
{
    cars.push_back(car);
}

// Display all cars in the system with their details
void System::displaycars() const
{
    cout << "\nDisplaying all system cars\n";
    int cnt = 1;
    for (const Car* car : cars)
    {
        cout << "\nCar[" << cnt << "]" << endl;
        cout << "Brand : " << car->get_brand() << endl;
        cout << "Model : " << car->get_model() << endl;
        cout << "Mileage = " << car->get_mileage() << endl;
        cout << "Made year : " << car->get_year() << endl;
        cout << "Registration Number : " << car->get_regNO() << endl;
        cout << "Availability : " << (car->isAvailable() ? "Available" : "Rented") << endl;
        cnt++;
    }
}

// Delete a car from the system by model name
void System::deleteCar(const string& model)
{
    for (auto car = cars.begin(); car != cars.end(); ++car)
    {
        if ((*car)->get_model() == model)
        {
            cout << "Deleting car: " << model << " ....." << endl;
            delete* car;  // Free memory
            cars.erase(car);  // Remove from vector
            cout << "Car \"" << model << "\" has been deleted successfully" << endl;
            return;
        }
    }
    cout << "The car \"" << model << "\" cannot be found in the system." << endl;
}

// Search for all cars matching a specific brand
void System::searchBybrand(const string& brand) const
{
    cout << "Cars made by " << brand << endl;
    bool exist = false;
    int cnt = 0;

    for (const Car* car : cars)
    {
        if (car->get_brand() == brand)
        {
            cnt++;
            cout << "\n(" << cnt << ") "
                << "Brand : " << car->get_brand() << endl;
            cout << "Model : " << car->get_model() << endl;
            cout << "Manufacture Date : " << car->get_year() << endl;
            cout << "Registration Number : " << car->get_regNO() << endl;
            cout << "Mileage : " << car->get_mileage() << endl;
            cout << "Availability : " << (car->isAvailable() ? "Available" : "Rented") << endl;
            exist = true;
        }
    }

    if (!exist)
    {
        cout << "There are no cars for " << brand << endl;
    }
}

// Search for all cars manufactured in a specific year
void System::searchByYear(const int& year) const
{
    cout << "Cars made in " << year << endl;
    bool exist = false;
    int cnt = 0;

    for (const Car* car : cars)
    {
        if (car->get_year() == year)
        {
            cnt++;
            cout << "\n(" << cnt << ") "
                << "Brand : " << car->get_brand() << endl;
            cout << "Model : " << car->get_model() << endl;
            cout << "Manufacture Date : " << car->get_year() << endl;
            cout << "Registration Number : " << car->get_regNO() << endl;
            cout << "Mileage : " << car->get_mileage() << endl;
            cout << "Availability : " << (car->isAvailable() ? "Available" : "Rented") << endl;
            exist = true;
        }
    }

    if (!exist)
    {
        cout << "There are no cars made in " << year << " available in our system :( !" << endl;
    }
}

// Rent a car: Mark as unavailable and start tracking rental time
void System::rentCar(const string& model)
{
    for (Car* car : cars)
    {
        if (model == car->get_model())
        {
            if (car->isAvailable())
            {
                car->rentCar();
                // Record the exact time when rental started
                rental_start_times[model] = high_resolution_clock::now();
                cout << "Car \"" << model << "\" rented successfully." << endl;
            }
            else
            {
                cout << "Car \"" << model << "\" is not available at the moment!\n";
            }
            return;
        }
    }
    cout << "The car \"" << model << "\" is not found in the system." << endl;
}

// Return a car: Calculate rental fee based on duration and car year
void System::returnCar(const string& model)
{
    for (Car* car : cars)
    {
        if (model == car->get_model())
        {
            if (!car->isAvailable())
            {
                car->returnCar();

                // Find the rental start time for this car
                auto it = rental_start_times.find(model);
                if (it != rental_start_times.end())
                {
                    auto start = it->second;
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<seconds>(stop - start);

                    // Dynamic pricing: newer cars cost more per hour
                    double base_rate = 5000.0; // Base rate in HUF per hour
                    int car_year = car->get_year();
                    double year_multiplier = 1.0;

                    // Apply multiplier based on car age
                    if (car_year >= 2020) {
                        year_multiplier = 1.5;  // Premium for newest cars
                    }
                    else if (car_year >= 2015) {
                        year_multiplier = 1.2;  // Moderate premium
                    }
                    else if (car_year >= 2010) {
                        year_multiplier = 1.0;  // Standard rate
                    }
                    else {
                        year_multiplier = 0.8;  // Discount for older cars
                    }

                    // Convert seconds to hours and calculate final price
                    double hours = duration.count() / 3600.0;
                    double price = hours * base_rate * year_multiplier;

                    cout << "Rental duration: " << duration.count() << " seconds ("
                        << hours << " hours)" << endl;
                    cout << "Rental fees = " << price << " HUF." << endl;

                    // Remove the rental record
                    rental_start_times.erase(it);
                }
                cout << "Car \"" << model << "\" returned successfully." << endl;
            }
            else
            {
                cout << "Car \"" << model << "\" was not rented!\n";
            }
            return;
        }
    }
    cout << "The car \"" << model << "\" is not found in the system." << endl;
}

// Save all cars to a CSV file for data persistence
void System::savecars(const string& filename) const
{
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        // Write each car's data as comma-separated values
        for (const Car* car : cars)
        {
            outFile << car->get_brand() << ","
                << car->get_model() << ","
                << car->get_regNO() << ","
                << car->get_year() << ","
                << car->get_mileage() << ","
                << car->isAvailable() << endl;
        }
        outFile.close();
        cout << "Cars saved successfully to \"" << filename << "\"." << endl;
    }
    else
    {
        cout << "Error: Cannot access the file \"" << filename << "\"." << endl;
    }
}

// Load cars from a CSV file into the system
void System::getFileCars(const string& filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        // Clear existing inventory before loading
        for (Car* car : cars)
        {
            delete car;
        }
        cars.clear();

        string line;
        while (getline(inFile, line))
        {
            string brand, model, year, regNo, mileage, available_str;

            // Parse CSV line using string stream
            istringstream carstream(line);
            getline(carstream, brand, ',');
            getline(carstream, model, ',');
            getline(carstream, regNo, ',');
            getline(carstream, year, ',');
            getline(carstream, mileage, ',');
            getline(carstream, available_str, ',');

            // Convert availability string to boolean
            bool available = (stoi(available_str) != 0);

            // Create new car and add to system
            Car* car = create_car_from_file(brand, model, stoi(regNo), stoi(year), stod(mileage));
            addCar(car);

            // Restore rental status (but don't start timer for loaded data)
            if (!available)
            {
                car->rentCar();
            }
        }
        inFile.close();
        cout << "Cars loaded successfully from \"" << filename << "\"." << endl;
    }
    else
    {
        cout << "Error: Unable to open the file \"" << filename << "\" for loading data.\n";
    }
}

// Factory function: Create a car object from file data
Car* create_car_from_file(const string& brand, const string& model, int regNo, int year, double mileage)
{
    Car* newcar = new Car(brand, model, year, regNo, mileage, true);
    return newcar;
}

// Interactive function: Create a new car with user input and validation
Car* create_car()
{
    string brand, model;
    int year, regNo;
    double mileage;
    cout << "Creating a new car:\n";

    // Clear any leftover input from previous operations
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter brand: ";
    getline(cin, brand);

    cout << "Enter model: ";
    getline(cin, model);

    // Year input with validation and error handling
    while (true)
    {
        try
        {
            cout << "Enter year: ";
            cin >> year;

            if (cin.fail())
            {
                throw runtime_error("Invalid input. Please enter a proper year.");
            }
            else if (year > 2025 || year < 1900)
            {
                throw runtime_error("Invalid input. Please enter a year between 1900 and 2025.");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Registration number input with validation
    while (true)
    {
        try
        {
            cout << "Enter registration number: ";
            cin >> regNo;

            if (cin.fail() || regNo < 0)
            {
                throw runtime_error("Invalid input. Please enter a positive integer registration number.");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Mileage input with validation
    while (true)
    {
        try
        {
            cout << "Enter mileage: ";
            cin >> mileage;

            if (cin.fail() || mileage < 0)
            {
                throw runtime_error("Invalid input. Please enter a positive mileage value.");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Clean up input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Create new car with all validated data
    Car* newCar = new Car(brand, model, year, regNo, mileage, true);

    cout << "\n    Car added successfully   \n";
    return newCar;
}

// Display main menu and get user's choice with input validation
int Menu()
{
    int option;
    cout << "\n\n"
        << "============"
        << " Main Menu "
        << "============"
        << "\n\n"
        << endl;
    cout << "[1] Add a Car\n";
    cout << "[2] Delete a Car\n";
    cout << "[3] View All Cars\n";
    cout << "[4] Search for a Car\n";
    cout << "[5] Rent a Car\n";
    cout << "[6] Return a Car\n";
    cout << "[7] Exit\n\n";

    // Loop until valid input is received
    while (true)
    {
        try
        {
            cout << "Pick an option between 1 and 7: ";
            cin >> option;
            if (cin.fail())
            {
                throw runtime_error("Invalid input. Please enter a number between 1 to 7.");
            }
            else if (option < 1 || option > 7)
            {
                throw runtime_error("Invalid input. Please enter a number between 1 to 7.");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Clear screen for better UX (platform-specific)
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    return option;
}

// Interactive car search interface with two search options
void carLookUp(const System& sys)
{
    cout << "\n====== Searching for a Car ======\n";
    cout << "Search for a car by: \n";
    cout << "[1] Brand \n";
    cout << "[2] Manufacture Date \n";
    string brand;
    int year;
    int option;

    // Get search method choice with validation
    while (true)
    {
        try
        {
            cout << "Pick an option, please: ";
            cin >> option;
            if (cin.fail())
            {
                throw runtime_error("Invalid input. Please enter either 1 or 2.");
            }
            else if (option < 1 || option > 2)
            {
                throw runtime_error("Invalid input. Please enter either 1 or 2.");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    switch (option)
    {
    case 1:  // Search by brand
        cout << "\nWhat is the brand of the car?\n(Please note that a brand can be something like \"BMW\")\n";
        getline(cin, brand);

        // Cross-platform screen clear
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        sys.searchBybrand(brand);
        break;

    case 2:  // Search by manufacture year
        while (true)
        {
            try
            {
                cout << "\nWhat is the manufacture date of the car?\nPlease input just a year (e.g., 2014): ";
                cin >> year;
                if (cin.fail())
                {
                    throw runtime_error("Error: Please enter a proper year!");
                }
                else if (year < 1900 || year > 2025)
                {
                    throw runtime_error("Error: Please enter a year between 1900 and 2025!");
                }
                break;
            }
            catch (const exception& e)
            {
                cout << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Cross-platform screen clear
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        sys.searchByYear(year);
        break;

    default:
        break;
    }
}