//
// Created on 4/8/22.
//

#ifndef FINALPROJECT_UPSDATA_H
#define FINALPROJECT_UPSDATA_H
#include <pqxx/pqxx>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <mutex>
#include <ctime>
#include <unordered_map>
#include "Truck.h"
#include "Common.h"
#include "MyException.h"
#include "ups_amazon.pb.h"
#include "world_ups.pb.h"

using namespace std;
using namespace pqxx;

class UPSData{
private:
    shared_ptr<connection> C;
    void createTablePackage();
    void createTableWarehouse();
    void createTableItem();
    void createTableTruck();
    //void createTableTempDelivered();
    //void createTableShipment();
public:
    std::mutex mtx;
    ofstream LOG;
    UPSData();
    ~UPSData();
    void createTables();
    void cleanAllData();
    void DropAllData();
    //write data
    //truck
    void initTruckTable(const Truck& truck);
    Truck getTruckInfo(int truck_id);
    int findAvaTruck();
    void updateTruckStatus(int truck_id,string status);

    //Package
    void insertPackage(const PackageInfo &packageInfo, int warehouse_id,int truck_id, int64_t seq_num);
    bool checkPackageId(int64_t package_id);
    bool checkStatus4Deliver(int truck_id, int warehouse_id);
    int findWarehouse(int x, int y);
    string getPackageStatus(int64_t package_id);
    vector<int64_t> getTargetPackageIDs(int truck_id, int warehouse_id, string status1, string status2);
    //vector<vector<int64_t>> getTargetPackagesInfo(int truck_id, string status);
    unordered_map<int64_t,pair<int,int>> getTargetPackageInfo(int truck_id, int warehouse_id);
    //unordered_map<int64_t,pair<int,int>> UPSData::getTargetPackageInfo(vector<int64_t> packageIDs);
    pair<int,int> singlePackageInfo(int64_t packageID);
    void updatePackageStatusID(int64_t package_id,string status);
    bool noStatus(int truck_id,string status);
    void updatePackageStatus(int truck_id, string current_status, string next_status);
    void updatePackageTruck(pair<int,int64_t> updateInfo, int64_t ori_seq);
    int findTruck4Package(int64_t packaged_id);
    bool changeAddress(int64_t package_id,int x,int y);

    //Warehouse
    bool checkWarehouse(int warehouseID);
    void insertWarehouse(const Warehouse &warehouse);

   
    void printLog(string log);
};
#endif //FINALPROJECT_UPSDATA_H
