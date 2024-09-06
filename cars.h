#pragma once

#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

class Car
{
private:
    string brand;
    string model;
    int year;
    int regNO;
    double mileage;
    bool available;

public:
    Car(string brand, string model, int year, int regNO, double mileage,bool available);

    ~Car();

    string get_brand() const;

    string get_model() const;

    int get_year() const;

    int get_regNO() const;

    double get_mileage() const;

    bool isAvailable() const;

    void rentCar();

    void returnCar();
    
};

/////////////////////////////////////////////////////////////////////

class Customer
{
private:
    string name;
    string idNo;
    string licenseNo;
    string address;
    string email;
    bool license_status;
    bool membership;

public:
    Customer(string name, string idNo, string licenseNo, string address, string email);

    string get_name() const;

    string get_idNo() const;

    string get_licenseNo() const;

    string get_address() const;

    string get_email() const;

    bool isValid() const;

    void becomeCustomer();

    void cancelMembership();
};

/////////////////////////////////////////////////////////////////////

class System
{
private:
    vector<Car*> cars;

public:
    map<string, time_point<high_resolution_clock>> rental_start_times;

    ~System();
    
    void addCar(Car* car);  // ownership --> System

    void displaycars() const;

    void deleteCar(const string &model); // BMW I3

    void searchBybrand(string &brand) const;

    void searchByYear(int &year) const;

    void rentCar(const string &model);

    void returnCar(const string &model);

    void savecars(const string& filename) const;

    void getFileCars(const string& filename);

};

Car* create_car_from_file(const string& brand, const string& model, int regNo, int year, double mileage);
Car* create_car();
void carLookUp(const System &sys);
int Menu();

#endif
