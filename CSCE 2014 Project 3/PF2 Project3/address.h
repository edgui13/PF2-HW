#ifndef ADDRESS_H
#define ADDRESS_H

//-----------------------------------------------------------
//  Purpose:    Header file for the Address class.
//  Author:     Edgar ALcocer
//-----------------------------------------------------------
#include <iostream>

using namespace std;

//-----------------------------------------------------------
// Define the Address class interface
//-----------------------------------------------------------
class Address

{
public:
    // Constructors
    Address();
    Address(float latitude, float longitude, int houseNumber, string streetName);
    Address(const Address &node);
    ~Address();

    // Get methods
    float getLatitude() const;
    float getLongitude() const;
    float getHouseNumber() const;
    string getStreetName() const;

    // Set methods
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    void setHouseNumber(float houseNumber);
    void setStreetName(string streetName);

    // Other methods
    void print() const;

private:
    float Latitude;
    float Longitude;
    int HouseNumber;
    string StreetName;
    // vector<Address> AddressVctr;
};

#endif