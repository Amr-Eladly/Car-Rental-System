# car-rental-system
# Car Rental Management System

A console-based car rental management system written in C++ that allows users to manage a fleet of cars, handle rentals, and track rental durations with automatic pricing calculations.

## Features

### Core Functionality
- **Car Management**: Add, delete, and display cars in the system
- **Search Capabilities**: Search cars by brand or manufacturing year
- **Rental System**: Rent and return cars with availability tracking
- **Time-based Pricing**: Automatic rental fee calculation based on rental duration
- **Data Persistence**: Save and load car data from file storage
- **Input Validation**: Robust error handling and input validation

### Classes Overview

#### `Car` Class
Represents individual vehicles with properties:
- Brand, model, year, registration number
- Mileage and availability status
- Methods for renting and returning cars

#### `Customer` Class
Manages customer information:
- Personal details (name, ID, license, address, email)
- License validation and membership status
- Customer registration and membership management

#### `System` Class
Core management system that handles:
- Car fleet management (add, delete, display)
- Search functionality by brand and year
- Rental and return operations
- File I/O operations for data persistence
- Rental time tracking and pricing

## Getting Started

### Prerequisites
- C++ compiler with C++11 support or higher
- Standard C++ libraries

### Compilation
```bash
g++ -std=c++11 main.cpp cars.cpp -o car_rental_system
```

### Running the Application
```bash
./car_rental_system
```

## Usage

### Menu Options
The system provides a user-friendly menu with the following options:

1. **Add a Car** - Register a new vehicle in the system
2. **Delete a Car** - Remove a car from the fleet
3. **View All Cars** - Display all registered vehicles
4. **Search for a Car** - Find cars by brand or manufacturing year
5. **Rent a Car** - Rent an available vehicle
6. **Return a Car** - Return a rented vehicle and calculate fees
7. **Exit** - Close the application

### Adding a Car
When adding a car, you'll be prompted to enter:
- Brand (e.g., "BMW", "Toyota")
- Model (e.g., "BMW I3", "Camry")
- Manufacturing year (1900-2024)
- Registration number (positive integer)
- Mileage (positive decimal number)

### Renting a Car
- Enter the car model exactly as registered
- System will check availability and start rental timer
- Unavailable cars will display appropriate error messages

### Returning a Car
- Enter the car model to return
- System calculates rental fees at 0.85 HUF per second
- Rental timer stops and fees are displayed

### Searching Cars
Two search options available:
- **By Brand**: Find all cars from a specific manufacturer
- **By Year**: Find all cars manufactured in a specific year

## File Structure

```
car-rental-system/
├── cars.h          # Header file with class declarations
├── cars.cpp        # Implementation of classes and functions
├── main.cpp        # Main application entry point
├── cars_data.txt   # Data storage file (auto-generated)
└── README.md       # This file
```

## Data Storage

The system uses a simple CSV format in `cars_data.txt`:
```
Brand,Model,RegistrationNumber,Year,Mileage,Availability
BMW,BMW I3,12345,2020,15000.5,1
Toyota,Camry,67890,2019,25000.0,0
```

## Error Handling

The system includes comprehensive error handling for:
- Invalid input types and ranges
- File I/O operations
- Car not found scenarios
- Already rented/returned car operations
- Memory management with proper cleanup

## Pricing System

- **Rate**: 0.85 HUF per second of rental time
- **Timer**: Starts when car is rented, stops when returned
- **Calculation**: Based on high-resolution clock for accuracy

## Technical Details

### Memory Management
- Dynamic memory allocation for Car objects
- Proper cleanup in System destructor
- RAII principles followed

### Time Tracking
- Uses `std::chrono::high_resolution_clock` for precise timing
- Rental start times stored in map for each rented vehicle
- Duration calculated in seconds for fee computation

## Known Limitations

1. Fixed pricing rate for all vehicles (no categorization by car type/year)
2. No customer rental history tracking
3. Simple file-based storage (no database integration)
4. Console-only interface
5. Single-user system (no concurrent access handling)

## Future Enhancements

- Variable pricing based on car category/year
- Customer management integration
- Database support
- GUI implementation
- Multi-user support with authentication
- Rental history and reporting
- Advanced search filters

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is open source and available under the MIT License.

## Contact

For questions or suggestions regarding this car rental management system, please create an issue in the repository.
