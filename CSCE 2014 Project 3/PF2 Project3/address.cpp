//----------------------------------------------
// Purpose: Implement address class node's
// Author:  Edgar Alcocer
//----------------------------------------------

#include <fstream>
#include "address.h"

//----------------------------------------------
Address::Address()
{
    Latitude = 0;
    Longitude = 0;
    HouseNumber = 0;
    StreetName = "";
}

//----------------------------------------------
Address::Address(float latitude, float longitude, int houseNumber, string streetName)
{
    Latitude = latitude;
    Longitude = longitude;
    HouseNumber = houseNumber;
    StreetName = streetName;
}

//----------------------------------------------
Address::Address(const Address &address)
{
    Latitude = address.Latitude;
    Longitude = address.Longitude;
    HouseNumber = address.HouseNumber;
    StreetName = address.StreetName;
}

//----------------------------------------------
Address::~Address()
{
}

//----------------------------------------------
float Address::getLatitude() const
{
    return Latitude;
}

//----------------------------------------------
float Address::getLongitude() const
{
    return Longitude;
}

//----------------------------------------------
float Address::getHouseNumber() const
{
    return HouseNumber;
}

//----------------------------------------------
string Address::getStreetName() const
{
    return StreetName;
}

//----------------------------------------------
void Address::setLatitude(float latitude)
{
    Latitude = latitude;
}

//----------------------------------------------
void Address::setLongitude(float longitude)
{
    Longitude = longitude;
}

//----------------------------------------------
void Address::setHouseNumber(float houseNumber)
{
    HouseNumber = houseNumber;
}

//----------------------------------------------
void Address::setStreetName(string streetName)
{
    StreetName = streetName;
}

// //----------------------------------------------
// void Address::binarySearch(vector<Address> &AddressVctr, int searchHouseNumber, string searchStreetName, int low, int high, int lastSearched)
// {

// }

//----------------------------------------------
void Address::print() const
{
    cout << "Latitude:      " << Latitude << endl;
    cout << "Longitude:     " << Longitude << endl;
    cout << "House Number:  " << HouseNumber << endl;
    cout << "Street Name:   " << StreetName << endl;
    cout << endl;
}