#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include "cars.h"
using namespace std;
using namespace std::chrono;
fstream file;

Car::Car(string brand, string model, int year, int regNO, double mileage, bool available) : brand(brand), model(model), year(year), regNO(regNO), mileage(mileage), available(true) {}

Car::~Car() {}

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

void Car::rentCar()
{
    available = false;
}

void Car::returnCar()
{
    available = true;
}

////////////////////////////////////

Customer::Customer(string name, string idNo, string licenseNo, string address, string email) : name(name), idNo(idNo), licenseNo(licenseNo), address(address), email(email), license_status(), membership(false) {}

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

/////////////////////////////////////////////

System::~System()
{
    // Free the dynamically allocated memory for the Car
    for (Car *car : cars)
    {
        delete car;
    }
    cars.clear();
}

void System::addCar(Car *car)
{
    cars.push_back(car);
}

void System::displaycars() const
{
    cout << "\nDisplaying all system cars\n";
    int cnt = 1;
    for (const Car *Car : cars)
    {
        cout << "\nCar[" << cnt << "]" << endl;
        cout << "Brand : " << Car->get_brand() << endl;
        cout << "Model : " << Car->get_model() << endl;
        cout << "Mileage = " << Car->get_mileage() << endl;
        cout << "Made year : " << Car->get_year() << endl;
        cout << "Registration Number : " << Car->get_regNO() << endl;
        cout << "Availability : " << Car->isAvailable() << endl;
        cnt++;
    }
}

void System::deleteCar(const string &model)
{
    bool exist = false;
    for (auto car = cars.begin(); car != cars.end(); ++car)
    {
        if ((*car)->get_model() == model)
        {
            exist = true;
            cout << "Deleting car: " << model << "  ....." << endl;
            delete *car;
            cars.erase(car);
            cout << "car \"" << model << "\" has been deleted successfully" << endl;
            return;
        }
    }
    if (!exist)
    {
        cout << "The car \"" << model << "\" cannnot be found on the system." << endl;
    }
}

void System::searchBybrand(string &brand) const
{
    cout << "Cars made by " << brand << endl;
    bool exist;
    exist = false;
    int cnt = 0;
    for (const Car *car : cars)
    {
        if (car->get_brand() == brand)
        {
            cnt++;
            cout << "(" << cnt << ")"
                 << "Brand : " << car->get_brand() << endl;
            cout << "Model : " << car->get_model() << endl;
            cout << "Manufacture Date : " << car->get_year() << endl;
            cout << "Registration Number : " << car->get_regNO() << endl;
            cout << "Mileage : " << car->get_mileage() << endl;
            cout << "Availability : " << car->isAvailable() << endl;
            exist = true;
        }
    }

    if (!exist)
    {
        cout << "There is no cars for " << brand << endl;
    }
}

void System::searchByYear(int &year) const
{
    cout << "Cars made in " << year << endl;
    bool exist;
    exist = false;
    int cnt = 0;
    for (const Car *car : cars)
    {
        if (car->get_year() == year)
        {
            cnt++;
            cout << "(" << cnt << ")"
                 << "Brand : " << car->get_brand() << endl;
            cout << "Model : " << car->get_model() << endl;
            cout << "Manufacture Date : " << car->get_year() << endl;
            cout << "Registration Number : " << car->get_regNO() << endl;
            cout << "Mileage : " << car->get_mileage() << endl;
            cout << "Availability : " << car->isAvailable() << endl;
            exist = true;
        }
    }
    if (!exist)
    {
        cout << "There is no cars have been made in " << year << "available on our system :( !" << endl;
    }
}

void System::rentCar(const string &model)
{
    for (Car *car : cars)
    {
        if (model == car->get_model())
        {
            if (car->isAvailable())
            {
                car->rentCar();
                rental_start_times[model] = high_resolution_clock::now(); // start the timer for renting the car
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

void System::returnCar(const string &model)
{
    for (Car *car : cars)
    {
        if (model == car->get_model())
        {
            if (!car->isAvailable())
            {
                car->returnCar();
                auto it = rental_start_times.find(model);
                if (it != rental_start_times.end())
                {
                    auto start = it->second;
                    auto stop = high_resolution_clock::now(); // stop the timer that we have started above.
                    auto duration = duration_cast<seconds>(stop - start);
                    double price = duration.count() * 0.85;  // fixed price for all the cars! (needed to be adjusted based on the category each car or at least the year!)
                    cout << "Rental fees = " << price << " HUF." << endl;
                    rental_start_times.erase(it); // erase the duration after calculating the price for the customer.
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

void System::savecars(const string &filename) const
{
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        for (const Car *car : cars)
        {
            outFile << car->get_brand() << "," << car->get_model() << "," << car->get_regNO() << "," << car->get_year() << "," << car->get_mileage() << "," << car->isAvailable() << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Error: Cannot access the file \"" << filename << "\"." << endl;
    }
}

void System::getFileCars(const string &filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        for (Car *car : cars)
        {
            delete car;
        }
        cars.clear();

        string line;
        while (getline(inFile, line))
        {
            string brand, model, year, regNo, mileage, available0;

            // int year, regNo;
            // double mileage;
            istringstream carstream(line);
            getline(carstream, brand, ',');
            getline(carstream, model, ',');
            getline(carstream, regNo, ',');
            getline(carstream, year, ',');
            getline(carstream, mileage, ',');
            getline(carstream, available0, ',');

            Car *car = create_car_from_file(brand, model, stoi(regNo), stoi(year), stod(mileage));
            addCar(car);

            bool available = stoi(available0);
            if (!available)
            {
                rentCar(model);
            }
        }
        inFile.close();
    }
    else
    {
        cout << "Error: Unable to open the file \"" << filename << "\" for loading data.\n";
    }
}

////////////////////////////////////////////// we will use this func. to create a car and then add it to the system using add car function
Car *create_car_from_file(const string &brand, const string &model, int regNo, int year, double mileage)
{
    Car *newcar = new Car(brand, model, regNo, year, mileage, true);
    return newcar;
    delete newcar;
}

Car *create_car()
{
    string brand, model, unusedline;
    int year, regNo;
    double mileage;
    cout << "Creating a new car:\n";

    cout << "Enter brand: ";
    getline(cin, unusedline);
    getline(cin, brand);

    cout << "Enter model: ";
    getline(cin, model);

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

            else if (year > 2024 || year < 1900)
            {
                throw runtime_error("Invalid input. Please enter a proper year.");
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

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
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true)
    {
        try
        {
            cout << "Enter mileage: ";
            cin >> mileage;

            if (cin.fail())
            {
                throw runtime_error("Invalid input. Please enter a positive double mileage.");
            }
            else if (mileage < 0)
            {
                throw runtime_error("Invalid input. Please enter a positive double mileage.");
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // in case something i haven't cosidered took place
    cin.clear(); // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Car *newCar = new Car(brand, model, year, regNo, mileage, true);

    cout << "\n    Car added successfully   \n";
    return newCar;
}

///////////////////////////////////////// menu of options

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
    cout << "[5] rent a Car\n";
    cout << "[6] Return a Car\n";
    cout << "[7] Exit\n\n";

    while (true)
    {
        try
        {
            cout << "Pick an option between 1 and 7 \n";
            cin >> option;
            if (cin.fail())
            {
                throw runtime_error("Invaild input.\n Please enter a number between 1 to 7\n");
            }
            else if (option < 1 || option > 7)
            {
                throw runtime_error("Invalid input.\n Please enter a number between 1 to 7\n");
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    system("cls");
    return option;
}

////////////////////////////////////////

void carLookUp(const System &sys)
{
    cout << "\n====== Searching about a Car ======\n";
    cout << "Search about a car by : \n";
    cout << "[1] Model \n";
    cout << "[2] Manufacture Date \n";
    string Brand, unusedline;
    int year;
    int option;

    while (true)
    {
        try
        {
            cout << "Pick up an option,please.\n";
            cin >> option;
            if (cin.fail())
            {
                throw runtime_error("Invalid input.\n Please enter either 1 or 2\n");
            }
            else if (option < 1 || option > 2)
            {
                throw runtime_error("Invalid input.\n Please enter either 1 or 2\n");
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "Error : " << e.what() << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    switch (option)
    {
    case (1):
        cout << "\n what is the Brand of the car? \n( please, note that : a Brand can be something like this \" BMW \")\n";
        getline(cin, unusedline);
        getline(cin, Brand);
        system("cls");
        sys.searchBybrand(Brand);
        break;
    case (2):
        while (true)
        {
            try
            {
                cout << "\nWhat is the manufacture date of the car? \n please input just a year for example: 2014\n";
                cin >> year;
                if (cin.fail())
                {
                    throw runtime_error("\nError: please enter a proper year!\n");
                }
                else if (year < 1900 || year > 2024)
                {
                    throw runtime_error("\nError: please enter a proper year!\n");
                }
                break;
            }
            catch (const exception &e)
            {
                cout << "Error : " << e.what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        system("cls");
        sys.searchByYear(year);
        break;
    default:
        break;
    }
}
