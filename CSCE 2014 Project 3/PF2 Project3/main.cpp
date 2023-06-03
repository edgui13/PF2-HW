//----------------------------------------------
// Purpose: Google maps test
// Author:  Edgar Alcocer
//----------------------------------------------
#include <fstream>
#include "address.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

//-----------------------------------------------------------
//  Trim white space from front and back of string
//-----------------------------------------------------------
string trim(const string str)
{
    int start = 0;
    int end = str.length() - 1;
    while ((start < int(str.length())) && (isspace(str[start])))
        start++;
    while ((end > start) && (isspace(str[end])))
        end--;
    return str.substr(start, (end - start + 1));
}

//-----------------------------------------------------------
// Read files
//-----------------------------------------------------------
void readFile(vector<Address> &AddressVctr, string fileName)
{
    // open input file
    ifstream din;
    din.open(fileName);

    if (din.fail())
    {
        cout << "Could not open unknown file" << endl;
    }

    while (!din.eof())
    {
        Address input;
        float latitude;
        float longitude;
        int houseNumber;
        string streetName;

        din >> latitude;
        din >> longitude;
        din >> houseNumber;
        getline(din, streetName);
        input.setLatitude(latitude);
        input.setLongitude(longitude);
        input.setHouseNumber(houseNumber);
        input.setStreetName(trim(streetName));

        AddressVctr.push_back(input);
    }
    din.close();
}

//-------------------------------------------------------------------
// recursive binary
//-------------------------------------------------------------------
int recursionBinarySearch(vector<Address> &AddressVctr, int searchHouseNumber, string searchStreetName, int low, int high, int lastSearched)
{
    // calculate midpoint index
    int mid = (low + high) / 2;

    int hNumber = AddressVctr[mid].getHouseNumber();
    string sName = AddressVctr[mid].getStreetName();
    string target = to_string(hNumber) + " " + sName;

    // check termination condition
    if (low > high)
    {
        cout << "Could not find it, here is the last address searched: " << endl;
        AddressVctr[lastSearched].print();
        return lastSearched;
    }
    // check if value is found
    else if (sName == searchStreetName)
    {
        if ((hNumber == searchHouseNumber) && (sName == searchStreetName))
        {
            cout << "-=-=-=-=- Found the house address! -=-=-=-=-" << endl;
            AddressVctr[mid].print();
            return mid;
        }
        // search to the left
        else if (hNumber > searchHouseNumber)
        {
            return recursionBinarySearch(AddressVctr, searchHouseNumber, sName, low, mid - 1, mid);
        }
        // search to the right
        else if (hNumber < searchHouseNumber)
        {
            return recursionBinarySearch(AddressVctr, searchHouseNumber, sName, mid + 1, high, mid);
        }
    }
    // search to the left
    else if (sName > searchStreetName)
    {
        return recursionBinarySearch(AddressVctr, searchHouseNumber, searchStreetName, low, mid - 1, mid);
    }
    // search to the right
    else
    {
        return recursionBinarySearch(AddressVctr, searchHouseNumber, searchStreetName, mid + 1, high, mid);
    }
    return mid;
}

//-------------------------------------------------------------------
// Distance finder1
//-------------------------------------------------------------------
float dist1(float lat1, float lon1, float lat2, float lon2)
{
    float delta_lat = lat1 - lat2;
    float delta_lon = lon1 - lon2;
    // cout << delta_lat << " | " << delta_lon << endl;
    return sqrt(delta_lat * delta_lat + delta_lon * delta_lon);
}
//----------------------------
float dist2(float lat1, float lon1, float lat2, float lon2)
{
    float delta_lat = fabs(lat1 - lat2);
    float delta_lon = fabs(lon1 - lon2);
    cout << delta_lat << " " << delta_lon << endl;

    if (delta_lat > delta_lon)
    {
        return delta_lat;
    }
    else
        return delta_lon;
}
//-------------------------------------------------------------------
// iterative binary search
//-------------------------------------------------------------------
int iterativeBinarySearch(vector<Address> &LocationVctr, float searchLatitude, float searchLongitude, float d, int low, int high)
{
    int count = 0;
    // int low = 0;
    int mid = (low + high) / 2;
    float latitude = searchLatitude - d;
    // int high = LocationVctr.size() - 1;
    while ((LocationVctr[mid].getLatitude() != latitude - d) && (low <= high))
    {
        // search left
        if (LocationVctr[mid].getLatitude() > latitude)
        {
            high = mid - 1;
        }
        // search right
        else // if (LocationVctr[mid].getLatitude() > latitude - d)
        {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }
    float dis = dist1(searchLatitude, searchLongitude, LocationVctr[mid].getLatitude(), LocationVctr[mid].getLongitude());

    while ((mid < LocationVctr.size()) && (LocationVctr[mid].getLatitude() >= searchLatitude - d) && LocationVctr[mid].getLatitude() <= searchLatitude + d)
    {
        // float dis = sqrt(pow(fabs(searchLatitude - LocationVctr[mid].getLatitude()), 2)) + (pow(fabs(searchLongitude - fabs(LocationVctr[mid].getLongitude())), 2));
        if (dis < d * d)
        {
            LocationVctr[mid].print();
            count++;
        }
        mid++;
    }
    cout << "There was " << count << " within the specified distance" << endl;
    return -1;
}
//----------------------------------------------
// main function
//----------------------------------------------
int main()
{
    // initalize Address Vector
    vector<Address> AddressVctr;
    readFile(AddressVctr, "address.txt");
    vector<Address> LocationVctr;
    readFile(LocationVctr, "location.txt");
    int selection;

    do
    {
        cout << "<><><><><><><><><><><><><><><><><><><>" << endl;
        cout << "Welcome to Google Maps!!!" << endl;
        cout << "The number of address' stored in the vector is: " << AddressVctr.size() << endl;
        cout << "The number of locations' stored in the vector is: " << LocationVctr.size() << endl;
        cout << "<><><><><><><><><><><><><><><><><><><>" << endl;
        cout << "1. Search for an address" << endl;
        cout << "2. Search to find nearby location" << endl;
        cout << "3. To exit the program" << endl;
        cout << "Please Select an option: ";
        cin >> selection;

        if (selection <= 0 || selection > 4)
        {
            cout << "Error!, please select an option between 1-3" << endl;
        }

        switch (selection)
        {
        case 1:
        {
            // begin the recurssive binary search process
            int searchHouseNumber;
            string searchStreetName;
            cout << "Please input an address to search: ";
            cin >> searchHouseNumber;
            getline(cin, searchStreetName);
            searchStreetName = trim(searchStreetName);
            cout << "The address to search for is: " << searchHouseNumber << " " << searchStreetName << endl;
            cout << endl;
            recursionBinarySearch(AddressVctr, searchHouseNumber, searchStreetName, 0, AddressVctr.size(), 0);
            break;
        }
        case 2:
        {
            float lat1, lat2, lon1, lon2;
            // lat1 = 36.0387;
            // lon1 = -94.187;
            // lat2 = 36.0321;
            // lon2 = -94.1839;
            cout << "Please input a location lat1 to search address': ";
            cin >> lat1;
            cout << "Please input a location lon1 to search address': ";
            cin >> lon1;
            cout << "Please input a location lat2 to search address': ";
            cin >> lat2;
            cout << "Please input a location lon2 to search address': ";
            cin >> lon2;
            // cin >> d;
            // float d = 30;
            // float d = sqrt(pow(fabs(lat1 - lon1), 2)) + (pow(fabs(lat2 - lon2), 2));
            float d = dist2(lat1, lon1, lat2, lon2);
            // cout << d;
            cout << endl;
            iterativeBinarySearch(LocationVctr, lat1, lon1, d, LocationVctr.size(), 0);
            break;
        }
        case 3:
        {
            cout << "Thank you for using Google Maps!!!" << endl;
            cout << "ending program" << endl;
            break;
        }
        }
    } while (selection != 3);
}