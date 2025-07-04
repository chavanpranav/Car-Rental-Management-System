#include <iostream>
#include <fstream>
using namespace std;

class Car
{
public:
    int carId;
    string model;
    float pricePerDay;
    bool isAvailable;
    int assignedDriverId;
};


struct Booking
{
    string customerName;
    int carId;
    int driverId;
    string licenseNo;
    int days;
    float totalCost;
};

class Driver
{
public:
    int driverId;
    string name;
    bool isAvailable;
    int assignedCarId;

    Car car;
    void viewAssignedCars() {
        int id;
        cout << "Enter a your driverid : " << endl;
        cin >> id;

        ifstream rd ("DriverInfo.txt");
        ifstream rc ("carInfo.txt");
        if(!rd.is_open() || !rc.is_open()) {
            cout << "Error!!" << endl;
            return;
        }

        while(rd >> driverId) {
            rd.ignore();
            getline(rd, name);
            rd >> isAvailable;
            rd >> assignedCarId;

            if(id == driverId) {
                while(rc >> car.carId) {
                    rc.ignore();
                    getline(rc, car.model);
                    rc >> car.pricePerDay;
                    rc >> car.isAvailable;
                    rc >> car.assignedDriverId;

                    if(assignedCarId == car.carId) {
                        cout << name << " you assigned a Car : " << "CarId -> " << car.carId << " model -> " << car.model << endl;
                        return;
                    }
                }
            }
        }
        cout << "Currently Not Assigned A Car " << endl;
    }

    void viewWorkHistory() {
        Booking b;
        int id;
        cout << "Enter a Your driverId : " << endl;
        cin >> id;
        cin.ignore();

        ifstream rb ("BookingHistory.txt");


        bool dfound = false;
        cout << endl;
        cout << "==========Working History==========" << endl;
        while(getline(rb, b.customerName)) {
            rb >> b.carId;
            rb >> b.driverId;
            rb.ignore();
            getline(rb, b.licenseNo);
            rb >> b.days;
            rb >> b.totalCost;
            rb.ignore();

            if(id == b.driverId) {
                cout << "Customer Name: " << b.customerName << endl;
                cout << "Car ID: " << b.carId << endl;
                cout << "Driver ID: " << b.driverId << endl;
                cout << "License No: " << b.licenseNo << endl;
                cout << "Days: " << b.days << endl;
                cout << "Total Cost: Rs. " << b.totalCost << endl;
                cout << "-----------------------------------" << endl;
                dfound = true;
            }
        }
        if(!dfound) {
            cout << "Invalid DriverId!!" << endl;
        }
        rb.close();
    }
};

class Admin
{
public:
    string userName = "admin";
    string password = "aaaa";

    Car car;
    Booking booking;
    Driver driver;

    void addCar(int id, string model, float price, bool availability)
    {
        car.carId = id;
        car.model = model;
        car.pricePerDay = price;
        car.isAvailable = availability;
        car.assignedDriverId = -1; // no driver assigned initially

        ofstream w("carInfo.txt", ios::app);
        if (!w.is_open())
        {
            cout << "Error!!" << endl;
            return;
        }
        w << car.carId << endl;
        w << car.model << endl;
        w << car.pricePerDay << endl;
        w << car.isAvailable << endl;
        w << car.assignedDriverId << endl;

        cout << "Car added!!" << endl;
        w.close();
    }

    void viewAllCars()
    {
        ifstream r("carInfo.txt");

        while (r >> car.carId)
        {
            r.ignore();
            getline(r, car.model);
            r >> car.pricePerDay;
            r >> car.isAvailable;
            r >> car.assignedDriverId;
            r.ignore();

            cout << "==========Car Information==========" << endl;
            cout << "CarId : " << car.carId << endl;
            cout << "Car Model : " << car.model << endl;
            cout << "Car pricePerDay : " << car.pricePerDay << endl;
            cout << "Car Available/Not : " << (car.isAvailable ? "Yes" : "No") << endl;
            cout << "Car AssignedDriverId" << car.assignedDriverId << endl;
        }
        r.close();
    }

    void viewAllBookings()
    {
        Booking booking;
        ifstream r("BookingInfo.txt");

        if (!r.is_open())
        {
            cout << "Unable to open BookingInfo.txt!" << endl;
            return;
        }

        while (getline(r, booking.customerName))
        {
            r >> booking.carId;
            r >> booking.driverId;
            r.ignore();
            getline(r, booking.licenseNo);
            r >> booking.days;
            r >> booking.totalCost;
            r.ignore();

            cout << "========== Booking ==========" << endl;
            cout << "Customer Name: " << booking.customerName << endl;
            cout << "Car ID: " << booking.carId << endl;
            cout << "Driver ID: " << (booking.driverId == -1 ? "No Driver" : to_string(booking.driverId)) << endl;
            cout << "License No: " << booking.licenseNo << endl;
            cout << "Days: " << booking.days << endl;
            cout << "Total Cost: Rs. " << booking.totalCost << endl;
        }
        r.close();
    }

    void addDrivers()
    {
        int n;
        cout << "How many Drivers you want to add: ";
        cin >> n;

        ofstream w("DriverInfo.txt", ios::app);
        if (!w.is_open())
        {
            cout << "Error!" << endl;
            return;
        }

        int x = 100;
        cin.ignore();
        for (int i = 1; i <= n; i++)
        {
            cout << "Enter Driver name: ";
            getline(cin, driver.name);

            driver.driverId = x++;
            driver.isAvailable = true;
            driver.assignedCarId = -1;
           // cin.ignore();

            w << driver.driverId << endl;
            w << driver.name << endl;
            w << driver.isAvailable << endl;
            w << driver.assignedCarId << endl;
        }

        w.close();
        cout << "Drivers added successfully!" << endl;
    }

    void viewAllDriverStatus() {
        ifstream rd("DriverInfo.txt");
        if(!rd.is_open()) {
            cout << "Error!!" << endl;
            return;
        }
        cout << "==========List Of Drivers==========" << endl;
        while(rd >> driver.driverId) {
            rd.ignore();
            getline(rd,driver.name);
            rd >> driver.isAvailable;
            rd >> driver.assignedCarId;

            cout << driver.driverId << endl;
            cout << driver.name << endl;
            cout << (driver.isAvailable ? "Available" : "Busy") << endl;
            cout << (driver.assignedCarId == -1 ? "Not Assigned" : "Assigned to Car") << endl;
            cout << "----------------------------------" << endl;
        }
        rd.close();
    }

    void deleteCar() {
        Car c;
        int id;
        viewAllCars();
        cout << endl;
        cout << "Enter a CarId which you want to remove :" << endl;
        cin >> id;
        ifstream rc("carInfo.txt");
        ofstream wc("tempc.txt");
        if(!rc.is_open() || !wc.is_open()) {
            cout << "Error!!" << endl;
            return;
        }
        bool CarFound = false;
        while(rc >> c.carId) {
            rc.ignore();
            getline(rc,c.model);
            rc >> c.pricePerDay;
            rc >> c.isAvailable;
            rc >> c.assignedDriverId;
            rc.ignore();
            if(id != c.carId) {
                wc << c.carId << endl;
                wc << c.model << endl;
                wc << c.pricePerDay << endl;
                wc << c.isAvailable << endl;
                wc << c.assignedDriverId << endl;
            }
            else {
                CarFound = true;
            }
        }
        rc.close();
        wc.close();

        if(CarFound) {
            remove("carInfo.txt");
            rename("tempc.txt","carInfo.txt");
            cout << "Car deleted successfully!" << endl;
        }
        else {
            remove("tempc.txt");
            cout << "Invalid Id" << endl;
        }
    }

    void deleteDriver() {
        Driver d;
        int id;
        viewAllDriverStatus();
        cout << endl;
        cout << "Enter a DriverId which you want to delete :" << endl;
        cin >> id;
        ifstream rd("DriverInfo.txt");
        ofstream wd("tempd.txt");
        if(!rd.is_open() || !wd.is_open()) {
            cout << "Error!!" << endl;
            return;
        }
        bool driverFound = false;
        while(rd >> d.driverId) {
            rd.ignore();
            getline(rd,d.name);
            rd >> d.isAvailable;
            rd >> d.assignedCarId;

            if(id != d.driverId) {
                wd << d.driverId << endl;
                wd << d.name << endl;
                wd << d.isAvailable << endl;
                wd << d.assignedCarId << endl;
            }
            else {
                driverFound = true;
            }
        }
        rd.close();
        wd.close();

        if(driverFound) {
            remove("DriverInfo.txt");
            rename("tempd.txt","DriverInfo.txt");
            cout << "Driver deleted successfully!" << endl;
        }
        else {
            remove("tempd.txt");
            cout << "Invalid Id" << endl;
        }
    }

};

class Customer
{
public:
    string name;
    string password;
    string licenseNo;
    //int bookedCarId;
    //int assignedDriverId;
    //int rentalDays;

    Car car;
    void viewAvailableCars()
    {
        ifstream r("carInfo.txt");
        bool found = false;
        while (r >> car.carId)
        {
            r.ignore();
            getline(r, car.model);
            r >> car.pricePerDay;
            r >> car.isAvailable;
            r >> car.assignedDriverId;
            r.ignore();

            if (car.isAvailable == 1)
            {
                cout << "==========Car Information==========" << endl;
                cout << "CarId : " << car.carId << endl;
                cout << "Car Model : " << car.model << endl;
                cout << "Car pricePerDay : " << car.pricePerDay << endl;
                cout << "Car AssignedDriverId" << car.assignedDriverId << endl;
                found = true;
            }
        }
        r.close();
        if (!found) {
        cout << "No cars available at the moment!" << endl;
    }
    }

    void bookCar(string uname)
    {
        Booking booking;
        int id, d;
        string name, pass, lNo, licenseNo;
        char c;
        cout << "Available cars are : " << endl;
        viewAvailableCars();
        cout << "Enter CarId: ";
        cin >> id;
        cout << "For how many days: ";
        cin >> d;
        cout << "Need a driver? (y/n): ";
        cin >> c;

        ifstream rreg("RegistrationFile.txt");// rreg readRegistration
        while(getline(rreg, name)) {
            rreg >> pass;
            rreg.ignore();
            getline(rreg, lNo);

            if(name == uname) {
                licenseNo = lNo;
            }
        }
        rreg.close();

        float pricePerDay = 0;
        bool carFound = false;

        ifstream rc("carInfo.txt");//   rc readCar
        ofstream wtc("temp.txt"); // wtc writetempcar
        Car car;
        while (rc >> car.carId)
        {
            rc.ignore();
            getline(rc, car.model);
            rc >> car.pricePerDay;
            rc >> car.isAvailable;
            rc >> car.assignedDriverId;
            rc.ignore();

            if (car.carId == id && car.isAvailable)
            {
                pricePerDay = car.pricePerDay;
                car.isAvailable = false;

                // Find an available driver
                if (c == 'y' || c == 'Y')
                {
                    ifstream rd("DriverInfo.txt");
                    ofstream wd("tempDriver.txt");
                    Driver driver;
                    bool found = false;

                    while (rd >> driver.driverId)
                    {
                        rd.ignore();
                        getline(rd, driver.name);
                        rd >> driver.isAvailable;
                        rd >> driver.assignedCarId;
                        rd.ignore();

                        if (!found && driver.isAvailable)
                        {
                            driver.isAvailable = false;
                            driver.assignedCarId = car.carId;
                            car.assignedDriverId = driver.driverId;
                            booking.driverId = driver.driverId;
                            booking.licenseNo = "N/A";
                            found = true;
                        }

                        wd << driver.driverId << endl;
                        wd << driver.name << endl;
                        wd << driver.isAvailable << endl;
                        wd << driver.assignedCarId << endl;
                    }
                    rd.close();
                    wd.close();
                    remove("DriverInfo.txt");
                    rename("tempDriver.txt", "DriverInfo.txt");
                }
                else
                {
                    booking.driverId = -1;
                    booking.licenseNo = licenseNo;
                }

                carFound = true;
            }

            wtc << car.carId << endl;
            wtc << car.model << endl;
            wtc << car.pricePerDay << endl;
            wtc << car.isAvailable << endl;
            wtc << car.assignedDriverId << endl;
        }
        rc.close();
        wtc.close();

        if (!carFound)
        {
            cout << "Car not found or already booked!" << endl;
            return;
        }

        remove("carInfo.txt");
        rename("temp.txt", "carInfo.txt");

        booking.customerName = uname;
        booking.carId = id;
        booking.days = d;
        booking.totalCost = pricePerDay * (float)d;

        ofstream wb("BookingInfo.txt", ios::app);
        ofstream wh("BookingHistory.txt", ios::app);
        if (!wb.is_open()) cout << "Failed to open BookingInfo.txt\n";
        if (!wh.is_open()) cout << "Failed to open BookingHistory.txt\n";

        wb << booking.customerName << endl;
        wb << booking.carId << endl;
        wb << booking.driverId << endl;
        wb << booking.licenseNo << endl;
        wb << booking.days << endl;
        wb << booking.totalCost << endl;

        wh << booking.customerName << endl;
        wh << booking.carId << endl;
        wh << booking.driverId << endl;
        wh << booking.licenseNo << endl;
        wh << booking.days << endl;
        wh << booking.totalCost << endl;
        wb.close();
        wh.close();

        cout << "Booking done successfully!" << endl;
        cout << "Total Cost: Rs. " << booking.totalCost << endl;
    }

    void viewBookingHistory(string uname) {
        Booking b1;
        bool bfound = false;
        ifstream rbh("BookingHistory.txt");
        while(getline(rbh, b1.customerName)) {
            rbh >> b1.carId;
            rbh >> b1.driverId;
            rbh.ignore();
            getline(rbh, b1.licenseNo);
            rbh >> b1.days;
            rbh >> b1.totalCost;
            rbh.ignore();

            if(uname == b1.customerName) {
                cout << "==========Current Booking==========" << endl;
                cout << "Customer Name: " << b1.customerName << endl;
                cout << "Car ID: " << b1.carId << endl;
                cout << "Driver ID: " << (b1.driverId == -1 ? "No Driver" : to_string(b1.driverId)) << endl;
                cout << "License No: " << b1.licenseNo << endl;
                cout << "Days: " << b1.days << endl;
                cout << "Total Cost: Rs. " << b1.totalCost << endl;
                bfound = true;
            }
        }
        if(!bfound) {
            cout << "No Booking found!" << endl;
        }
        rbh.close();
    }


    void returnCar(string uname) {
        cout << "===== Your Active Bookings =====" << endl;
        bool hasActiveBookings = false;

        ifstream rb1("BookingInfo.txt");
        Booking currentBooking;

        // Display all active bookings for this user
        while (getline(rb1, currentBooking.customerName)) {
            rb1 >> currentBooking.carId;
            rb1 >> currentBooking.driverId;
            rb1.ignore();
            getline(rb1, currentBooking.licenseNo);
            rb1 >> currentBooking.days;
            rb1 >> currentBooking.totalCost;
            rb1.ignore();

            if (currentBooking.customerName == uname) {
                cout << "Car ID: " << currentBooking.carId << endl;
                cout << "Driver ID: " << (currentBooking.driverId == -1 ? "No Driver" : to_string(currentBooking.driverId)) << endl;
                cout << "Days Rented: " << currentBooking.days << endl;
                cout << "Total Cost: Rs. " << currentBooking.totalCost << endl;
                cout << "-------------------------" << endl;
                hasActiveBookings = true;
            }
        }
        rb1.close();

        if (!hasActiveBookings) {
            cout << "You have no active bookings to return." << endl;
            return;
        }

        int id;
        //viewBookingHistory();
        cout << endl;
        cout << "Enter a your Booked carId which you want to return: " << endl;
        cin >> id;

        Car c;
        Driver d;

        ifstream rc("carInfo.txt");
        ofstream wc("temp1.txt");
        ifstream rd("DriverInfo.txt");
        ofstream wd("temp2.txt");

        bool carFound = false;
        bool driverFound = false;
        while(rc >> c.carId) {
            rc.ignore();
            getline(rc, c.model);
            rc >> c.pricePerDay;
            rc >> c.isAvailable;
            rc >> c.assignedDriverId;

            if(id == c.carId) {
                c.isAvailable = true;
                c.assignedDriverId = -1;
                carFound = true;
            }
            wc << c.carId << endl;
            wc << c.model << endl;
            wc << c.pricePerDay << endl;
            wc << c.isAvailable << endl;
            wc << c.assignedDriverId << endl;
        }
        rc.close();
        wc.close();


        if(carFound) {
            remove("carInfo.txt");
            rename("temp1.txt","carInfo.txt");
            cout << "Car Returned Successfully !!" << endl;
        }
        else {
            remove("temp1.txt");
            cout << "Invalid carId" << endl;
            return;
        }

        while(rd >> d.driverId) {
            rd.ignore();
            getline(rd, d.name);
            rd >> d.isAvailable;
            rd >> d.assignedCarId;

            if(d.assignedCarId == id) {
                d.isAvailable = true;
                d.assignedCarId = -1;
                driverFound = true;
            }
            wd << d.driverId << endl;
            wd << d.name << endl;
            wd << d.isAvailable << endl;
            wd << d.assignedCarId << endl;
        }
        rd.close();
        wd.close();
        if(driverFound) {
            remove("DriverInfo.txt");
            rename("temp2.txt","DriverInfo.txt");
        }
        else {
            remove("temp2.txt");
            //cout << "Note: No driver was assigned to this car." << endl;
        }

        ifstream rb("BookingInfo.txt");
        ofstream wb("temp3.txt");
        Booking b;

        while (getline(rb, b.customerName)) {
            rb >> b.carId;
            rb >> b.driverId;
            rb.ignore();
            getline(rb, b.licenseNo);
            rb >> b.days;
            rb >> b.totalCost;
            rb.ignore();

            if (b.carId != id) {
                wb << b.customerName << endl;
                wb << b.carId << endl;
                wb << b.driverId << endl;
                wb << b.licenseNo << endl;
                wb << b.days << endl;
                wb << b.totalCost << endl;
            }
        }
        rb.close();
        wb.close();
        remove("BookingInfo.txt");
        rename("temp3.txt", "BookingInfo.txt");


    }
};

bool isAdminLogedIn = false;
bool isCustomerLogedIn = false;

void LogIn(string uname, string pass, int AorC)
{
    if (AorC == 1)
    {
        Admin admin;
        if (uname == admin.userName && pass == admin.password)
        {
            isAdminLogedIn = true;
            cout << "Admin LogIn Successfully Done!!" << endl;
        }
        else
        {
            cout << "Incorrect UserName or PassWord\nTry Again!!" << endl;
        }
    }
    else if (AorC == 2)
    {
        Customer customer;

        ifstream r("RegistrationFile.txt");
        while (getline(r, customer.name))
        {
            getline(r, customer.password);
            getline(r, customer.licenseNo);

            if (uname == customer.name && pass == customer.password)
            {
                isCustomerLogedIn = true;
                cout << "Customer LogIn SucessFully completed!" << endl;
                return;
            }
        }
        cout << "Please first do registraton!" << endl;
    }
}

void userRegistration(string uname, string pass, string lNo)
{
    Customer customer;
    customer.name = uname;
    customer.password = pass;
    customer.licenseNo = lNo;

    ofstream w("RegistrationFile.txt", ios::app);
    if (!w.is_open())
    {
        cout << "Error!!" << endl;
    }
    w << customer.name << endl;
    w << customer.password << endl;
    w << customer.licenseNo << endl;

    cout << "Customer Registration is completed!!" << endl;
    w.close();
}

void Logout(string portal) {

    if(portal == "Admin") {
        isAdminLogedIn = false;
        cout << "Admin LogOut Done!!" << endl;
        return;
    }
    if(portal == "Customer") {
        isCustomerLogedIn = false;
        cout << "Customer LogOut Done!!" << endl;
        return;
    }
}

int main()
{
    int choise;
    Admin a;
    Customer c;
    Car car;
    int  cnt = 1;

    do
    {
        cout << endl;
        cout << "========= Welcome to Car Rental System =========" << endl;
        cout << "1. Admin Login\n2. Customer Portal\n3. Driver Portal\n0. Exit" << endl;
        cin >> choise;

        switch (choise)
        {
        case 1:
        {
            string uname, pass;
            cout << "Enter a UserName & PassWord of ADMIN: " << endl;
            cin >> uname >> pass;
            LogIn(uname, pass, 1);
            if (isAdminLogedIn)
            {
                int ch1;
                do
                {
                    cout << endl;
                    cout << "--- Admin  Menu ---" << endl;
                    cout << "1. Add Car\n2. View All Cars\n3. View All Bookings\n4. Delete Car\n5. Add Drivers\n6. Driver status\n7. Remove Driver\n8. Logout" << endl;
                    cin >> ch1;

                    switch (ch1)
                    {
                    case 1:
                    {
                        int n;
                        string model;
                        int price;
                        cout << "How many car you want to add :" << endl;
                        cin >> n;
                        cin.ignore();
                        for(int i = 0; i < n; i++) {
                            cout << "Enter a Car Model :" << endl;
                            getline(cin, model);
                            cout << "Enter a Car price per day :" << endl;
                            cin >> price;
                            cin.ignore();
                            a.addCar(cnt, model, price, true);
                            cnt++;
                        }
                        break;
                    }
                    case 2:
                    {
                        a.viewAllCars();
                        break;
                    }
                    case 3:
                    {
                        a.viewAllBookings();
                        break;
                    }
                    case 4:
                    {
                        a.deleteCar();
                        break;
                    }
                    case 5:
                    {
                        a.addDrivers();
                        break;
                    }
                    case 6:
                    {
                        a.viewAllDriverStatus();
                        break;
                    }
                    case 7:
                    {
                        a.deleteDriver();
                        break;
                    }
                    case 8:
                    {
                        Logout("Admin");
                        break;
                    }
                    }
                } while (ch1 != 8);
            }
            break;
        }
        case 2:
        {
            int ch2;
            cout << endl;
            cout << "--- Customer Menu ---" << endl;
            cout << "1. Register \n2. Login" << endl;
            cout << "Enter a choise:" << endl;
            cin >> ch2;
            switch (ch2)
            {
            case 1:
            {
                string uname, pass, lNo;
                cout << "Enter a UserName & PassWord of Customer: " << endl;
                cin >> uname >> pass;
                cout << "Enter a LisenceNo :" << endl;
                cin >> lNo;
                userRegistration(uname, pass, lNo);
                break;
            }
            case 2:
            {
                string uname, pass;
                cout << "Enter a UserName & PassWord of Customer: " << endl;
                cin >> uname >> pass;
                LogIn(uname, pass, 2);

                if (isCustomerLogedIn)
                {
                    int ch2ch;
                    do
                    {
                        cout << "--- Customer  Menu ---" << endl;
                        cout << "1. View Available Cars\n2. Book a Car\n3. Return a Car\n4. View My Bookings\n5. Logout" << endl;
                        cout << "Enter a choise:" << endl;
                        cin >> ch2ch;
                        switch (ch2ch)
                        {
                        case 1:
                        {
                            c.viewAvailableCars();
                            break;
                        }
                        case 2:
                        {
                            c.bookCar(uname);
                            break;
                        }
                        case 3:
                        {
                            c.returnCar(uname);
                            break;
                        }
                        case 4:
                        {
                            c.viewBookingHistory(uname);
                            break;
                        }
                        case 5:
                        {
                            Logout("Customer");
                            break;
                        }
                        }
                    } while (ch2ch != 5);
                }
                break;
            }
            }
            break;
        }
        case 3:
        {
            Driver d;
            int ch3;
            do{
                cout << "--- Driver Menu ---" << endl;
                cout << "1. View Assigned Car\n2. View Work History\n3. Exit" << endl;
                cout << "Enter a choice : " << endl;
                cin >> ch3;

                switch(ch3) {
                    case 1 : {
                        d.viewAssignedCars();
                        break;
                    }
                    case 2 : {
                        d.viewWorkHistory();
                        break;
                    }
                }
            }while(ch3 != 3);
            break;
        }
        default:
        {
            cout << "Invalid choise" << endl;
            cout << "Enter again Valid choise" << endl << endl;
            break;
        }
        }
    } while (choise != 0);
}
