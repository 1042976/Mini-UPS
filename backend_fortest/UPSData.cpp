//
// Created on 4/8/22.
//

#include "UPSData.h"


UPSData::UPSData() : C(make_shared<connection>("dbname = ups_db user = postgres password = postgres "
                                               "host = localhost port = 5432")), LOG("logs/database.log") {
    if (C->is_open()) {
        cout << "Successfully connect to the database: " << C->dbname() << endl;
        this->DropAllData();
        this->createTables();
        
        //this->cleanAllData();

    } else {
        throw MyException("Unable to open the database");
    }
}

UPSData::~UPSData() {
    C->disconnect();
}

void UPSData::printLog(string log) {
    cout <<"[" << log <<"]"<< endl;
    LOG << "[" << log <<"]"<< endl;
}

void UPSData::createTablePackage() {
    work W(*C);
    string sql = "CREATE TABLE IF NOT EXISTS PACKAGE("
                 "PACKAGE_ID        BIGINT    PRIMARY KEY                           NOT NULL,"
                 "USERNAME          TEXT      NULL,"
                 "ADDR_X            INT       NOT NULL,"
                 "ADDR_Y            INT       NOT NULL,"
                 "STATUS            VARCHAR   NOT NULL,"
                 "WAREHOUSE_ID      INT       REFERENCES WAREHOUSE(WAREHOUSE_ID)    NOT NULL,"
                 "TRUCK_ID          INT       REFERENCES TRUCK(TRUCK_ID)            NOT NULL,"
                 "SEQNUM            BIGINT    NOT NULL);";

    W.exec(sql);
    W.commit();
}

void UPSData::createTableWarehouse() {
    work W(*C);
    string sql = "CREATE TABLE IF NOT EXISTS WAREHOUSE("
                 "WAREHOUSE_ID      INT         PRIMARY KEY               NOT NULL,"
                 "X                 INT         NOT NULL,"
                 "Y                 INT         NOT NULL)";

    W.exec(sql);
    W.commit();
}

void UPSData::createTableItem() {
    work W(*C);
    string sql = "CREATE TABLE IF NOT EXISTS ITEM("
                 "PACKAGE_ID    BIGINT      REFERENCES PACKAGE(PACKAGE_ID)    NOT NULL,"
                 "NAME          TEXT        NOT NULL,"
                 "DESCRIPTION   TEXT        NOT NULL,"
                 "COUNT         INT         NOT NULL)";
    W.exec(sql);
    W.commit();
}

void UPSData::createTableTruck() {
    work W(*C);
    string sql = "CREATE TABLE IF NOT EXISTS TRUCK("
                 "TRUCK_ID        INT   PRIMARY KEY    NOT NULL,"
                 "TRUCK_STATUS    TEXT  NOT NULL,"
                 "TRUCK_X         INT   NOT NULL,"
                 "TRUCK_Y         INT   NOT NULL)";
    W.exec(sql);
    W.commit();
}

// void UPSData::createTableTempDelivered(){
//     work W(*C);
//     string testsql = "CREATE TABLE IF NOT EXISTS DELIVERED("
//                  "PACKAGE_ID        BIGINT    PRIMARY KEY                           NOT NULL);";
//     W.exec(testsql);
//     W.commit();
// }
//void UPSData::createTableShipment() {
//    work W(*C);
//    string testsql = "CREATE TABLE IF NOT EXISTS SHIPMENT("
//                 "ID     BIGINT   PRIMARY KEY    NOT NULL)";
//    W.exec(testsql);
//    W.commit();
//}

void UPSData::createTables() {
    createTableWarehouse();
    createTableTruck();
    createTablePackage();
    createTableItem();
    //createTableTempDelivered();    
}

void UPSData::cleanAllData() {
    work W(*C);
//    string sqlAuthUser = "DELETE FROM AUTH_USER";
    string sqlPackage = "DELETE FROM PACKAGE";
    string sqlWarehouse = "DELETE FROM WAREHOUSE";
    string sqlItem = "DELETE FROM ITEM";
    string sqlTruck = "DELETE FROM TRUCK";
    //string sqlDelivered = "DELETE FROM DELIVERED";
   // string sqlShipment = "DELETE FROM SHIPMENT";
//    W.exec(sqlAuthUser);
    W.exec(sqlPackage);
    W.exec(sqlWarehouse);
    W.exec(sqlItem);
    W.exec(sqlTruck);
    //W.exec(sqlDelivered);

    // W.exec(sqlShipment);
    W.commit();
}

void UPSData::DropAllData() {
    work W(*C);
    string sqlPackage = "DROP TABLE IF EXISTS PACKAGE CASCADE";
    string sqlWarehouse = "DROP TABLE IF EXISTS WAREHOUSE CASCADE";
    string sqlItem = "DROP TABLE IF EXISTS ITEM CASCADE";
    string sqlTruck = "DROP TABLE IF EXISTS TRUCK CASCADE";
    //string sqlDelivered = "DROP TABLE IF EXISTS DELIVERED CASCADE";
   // string sqlShipment = "DELETE FROM SHIPMENT";
    W.exec(sqlPackage);
    W.exec(sqlWarehouse);
    W.exec(sqlItem);
    W.exec(sqlTruck);
    //W.exec(sqlDelivered);

    // W.exec(sqlShipment);
    W.commit();
}

//write

void UPSData::initTruckTable(const Truck& truck) {
    
    work W(*C);
    string sql = "INSERT INTO TRUCK (TRUCK_ID,TRUCK_STATUS, TRUCK_X, TRUCK_Y) VALUES ("
                 + to_string(truck.id) + "," + addApostrophe(truck.status) + ","
                 + to_string(truck.x) + ","
                 + to_string(truck.y) + ");";
    W.exec(sql);
    W.commit();
}

int UPSData::findAvaTruck() {
    printLog("------------------findAvaTruck------------------------");
    std::lock_guard <std::mutex> lck(mtx);
    
    work W(*C);
    string sql = "SELECT TRUCK.TRUCK_ID FROM TRUCK WHERE TRUCK_STATUS = 'IDLE' OR"
                  " TRUCK_STATUS = 'DELIVERING' FOR UPDATE;";
    result R(W.exec(sql));
    
    if(R.size()==0){
        W.commit();
        return -1;
    }
    else if (R.size()==1){
        int truck_id = R[0][0].as<int>();
        string sql_update = "UPDATE TRUCK SET TRUCK_STATUS = 'TRAVELING' WHERE TRUCK_ID = "
                            + to_string(truck_id) + ";";
        W.exec(sql_update);
        W.commit();
        return truck_id;
    }
    else{
        int r = rand()%(R.size());
        int truck_id = R[r][0].as<int>();
        string sql_update = "UPDATE TRUCK SET TRUCK_STATUS = 'TRAVELING' WHERE TRUCK_ID = "
                            + to_string(truck_id) + ";";
        W.exec(sql_update);
        W.commit();
        
        return truck_id;
    }
}

void UPSData::updateTruckStatus(int truck_id, string status) {
    std::lock_guard <std::mutex> lck(mtx);
    printLog("------------------updateTruckStatus------------------------");
    printLog(to_string(truck_id)+" "+status);
    work W(*C);
    string sql = "UPDATE TRUCK SET TRUCK_STATUS = '" + status
                 +"' WHERE TRUCK_ID =" + to_string(truck_id) + ";";
    W.exec(sql);
    W.commit();
}

Truck UPSData::getTruckInfo(int truck_id) {
    nontransaction N(*C);
    string sql = "SELECT * FROM TRUCK WHERE TRUCK_ID = " + to_string(truck_id);
    pqxx::result r(N.exec(sql));
    if(r.empty()){
        return Truck(-1);
    }else{
        string status = r[0][1].as<string>();
        int x = r[0][2].as<int>();
        int y = r[0][3].as<int>();
        return Truck(truck_id, x, y, status);
    }
}


bool UPSData::checkPackageId(int64_t package_id){
    nontransaction N(*C);
    string sql = "SELECT * FROM PACKAGE WHERE PACKAGE_ID = " + to_string(package_id);
    result R(N.exec(sql));
    if(R.size()==0){
        return false;//no pacakge
    }
    else{//has package
        return true;
    }
}

void UPSData::insertPackage(const PackageInfo &packageInfo, int warehouse_id, int truck_id, int64_t seq_num) {
    std::lock_guard <std::mutex> lck(mtx);
    printLog("------------------In Insert Package------------------------");
    int64_t shipid = packageInfo.shipid();
    int32_t x = packageInfo.x();
    int32_t y = packageInfo.y();
    
    //double check
    if((checkPackageId(shipid))==true){
        return;
    }
    work W(*C);
    
    //check user_name
    if(packageInfo.has_user_name()){
        string userName=packageInfo.user_name();
        string insert_package = "INSERT INTO PACKAGE (PACKAGE_ID,USERNAME,ADDR_X,ADDR_Y,STATUS,WAREHOUSE_ID,TRUCK_ID,SEQNUM) VALUES ("
                                + to_string(shipid) + ",'" + userName + "',"+ to_string(x) + "," + to_string(y)
                                + ",'PACKING'," + to_string(warehouse_id) + "," + to_string(truck_id) + "," + to_string(seq_num) + ");";
        W.exec(insert_package);
        for(int i=0;i<packageInfo.product_size();i++){
            //check with XD for product temp
            Product temp = packageInfo.product(i);
            int count = temp.count();
            string pro_name = temp.name();
            string pro_desp = temp.description();

            string insert_item = "INSERT INTO ITEM (PACKAGE_ID,NAME,DESCRIPTION,COUNT) VALUES ("
                                 + to_string(shipid) + ",'" + pro_name + "','" + pro_desp +"'," + to_string(count) +");";
            W.exec(insert_item);
        }
    }else{
        string insert_package = "INSERT INTO PACKAGE (PACKAGE_ID,ADDR_X,ADDR_Y,STATUS,WAREHOUSE_ID,TRUCK_ID,SEQNUM) VALUES ("
                                + to_string(shipid) + ","+ to_string(x) + "," + to_string(y) + ",'PACKING',"
                                + to_string(warehouse_id) + ","
                                + to_string(truck_id) + "," + to_string(seq_num) + ");";
        W.exec(insert_package);
    }
    W.commit();
}


string UPSData::getPackageStatus(int64_t package_id) {
    work W(*C);
    string sql = "SELECT PACKAGE.STATUS FROM PACKAGE WHERE PACKAGE_ID = '"
                 + to_string(package_id) + "'";
    result R(W.exec(sql));
    W.commit();
    if(R.size()==0){
        return "NULL";
    }else{
        return R[0][0].as<string>();
    }
}

vector<int64_t> UPSData::getTargetPackageIDs(int truck_id, int warehouse_id, string status1, string status2){
    work W(*C);
    vector<int64_t> packagesIDs;
    string sql = "SELECT PACKAGE.PACKAGE_ID FROM PACKAGE WHERE TRUCK_ID = " + to_string(truck_id) 
                + " AND WAREHOUSE_ID = " + to_string(warehouse_id)
                + " AND STATUS IN ('" + status1 + "','" + status2 + "');";
    result R(W.exec(sql));
    for(size_t i=0;i<R.size();i++){
        int64_t id = R[i][0].as<int64_t>();
        packagesIDs.push_back(id);
    }
    W.commit();
    return packagesIDs;
}

pair<int,int> UPSData::singlePackageInfo(int64_t packageID){
    printLog("--------------In singlePackageInfo---------------");
    work W(*C);
    pair<int,int> packageInfo;
    string sql = "SELECT ADDR_X,ADDR_Y FROM PACKAGE WHERE PACKAGE_ID = " + to_string(packageID) + ";";
    result R(W.exec(sql));
    if(R.size()==1){
        packageInfo.first =R[0][0].as<int>();
        packageInfo.second = R[0][1].as<int>();

    }    
    W.commit();
    return packageInfo;
}

// unordered_map<int64_t,pair<int,int>> UPSData::getTargetPackageInfo(vector<int64_t> packageIDs){
//     printLog("--------------In getTargetPackageInfo---------------");
//     unordered_map<int64_t,pair<int,int>> packages;
//     string pr; 
//     for(size_t i=0;i<packageIDs.size();i++){
//         pair<int,int> temp = singlePackageInfo(packageIDs[i]);
//         packages[packageIDs[i]]=temp;
//         pr = pr + "package id = " + to_string(packageIDs[i])+ " x,y " + to_string(temp.first) + "," + to_string(temp.second) + "\n";  
//     }
//     printLog("--------------deliverd find package info---------------");
//     printLog(pr);
//     return packages;
// }

unordered_map<int64_t,pair<int,int>> UPSData::getTargetPackageInfo(int truck_id, int warehouse_id){
    printLog("--------------In getTargetPackageInfo---------------");
    unordered_map<int64_t,pair<int,int>> packages;
    work W(*C);
    string sql = "SELECT PACKAGE.PACKAGE_ID,ADDR_X,ADDR_Y FROM PACKAGE WHERE TRUCK_ID = " + to_string(truck_id)
                  + " AND WAREHOUSE_ID = " + to_string(warehouse_id) + " AND STATUS ='LOADED';";
    result R(W.exec(sql));
    string pr;
    for(size_t i=0;i<R.size();i++){
        int64_t id = R[i][0].as<int64_t>();
        int x = R[i][1].as<int>();
        int y = R[i][2].as<int>();
        pair<int,int> coor = make_pair(x,y);
        packages[id] = coor;
        pr = pr + "package id = " + to_string(id) + " x,y = " + to_string(x) + "," + to_string(y) + "\n";
    }
    W.commit();
    printLog("--------------deliverd find package info---------------");
    printLog(pr);
    return packages;
}


//  unordered_map<int64_t,pair<int,int>>  UPSData::getTargetPackagesInfo(int truck_id, string status){
//     work W(*C);
//     unordered_map<int64_t,pair<int,int>> packages;
//     string testsql = "SELECT PACKAGE.PACKAGE_ID,ADDR_X,ADDR_Y FROM PACKAGE WHERE TRUCK_ID = " + to_string(truck_id)
//                  + " AND STATUS = '" + status + "';";
//     result R(W.exec(testsql));
//     for(size_t i=0;i<R.size();i++){
//         int64_t id = R[i][0].as<int64_t>();
//         int x = R[i][1].as<int>();
//         int y = R[i][2].as<int>();
//         pair<int,int> coor = make_pair(x,y);
//         packages[id] = coor;
//     }
//     W.commit();
//     return packages;
// }

//check if all package in this truck be packed
bool UPSData::noStatus(int truck_id, string status) {
    work W(*C);
    string sql = "SELECT PACKAGE_ID FROM PACKAGE WHERE TRUCK_ID = "
                 + to_string(truck_id) + " AND PACKAGE.STATUS = '" + status +"';";
    result R(W.exec(sql));
    W.commit();
    if(R.size()==0){
        return true;
    }
    else{
        return false;
    }
}

void UPSData::updatePackageStatusID(int64_t package_id, string status) {
    printLog("--------------updatePackageStatusID--------------");
    std::lock_guard <std::mutex> lck(mtx);
    string str =  status + to_string(package_id);
    this->printLog(str);
    work W(*C);
    string sql = "UPDATE PACKAGE SET STATUS=" + addApostrophe(status) + " WHERE PACKAGE_ID =" + to_string(package_id) + ";";
    W.exec(sql);
    W.commit();
}

void UPSData::updatePackageStatus(int truck_id, string current_status, string next_status) {
    std::lock_guard <std::mutex> lck(mtx);
    work W(*C);
    string sql = "UPDATE TRUCK SET TRUCK_STATUS = '" + next_status
                 + "' WHERE TRUCK_ID = "+ to_string(truck_id) + " AND TRUCK_STATUS = "
                 + current_status + "';";
    W.exec(sql);
    W.commit();
}

void UPSData::updatePackageTruck(pair<int,int64_t> updateInfo, int64_t ori_seq){
    std::lock_guard <std::mutex> lck(mtx);
    work W(*C);
    string sql = "UPDATE PACKAGE SET TRUCK_ID = " + to_string(updateInfo.first) + " ,SEQNUM = "
                 + to_string(updateInfo.second) + " WHERE SEQNUM = "+ to_string(ori_seq) + ";";
    W.exec(sql);
    W.commit();
}

bool UPSData::checkStatus4Deliver(int truck_id, int warehouse_id){
    nontransaction N(*C);
    string sql = "SELECT * FROM PACKAGE WHERE TRUCK_ID = " + to_string(truck_id) 
                + " AND WAREHOUSE_ID = " + to_string(warehouse_id) 
                + " AND STATUS IN ('PACKING','PACKED','LOADING');";
    result R(N.exec(sql));
    if(R.size()==0){
        return true;
    }
    else{
        return false;
    }
}

int UPSData::findTruck4Package(int64_t packaged_id){
    nontransaction N(*C);
    string sql = "SELECT TRUCK_ID,STATUS FROM PACKAGE WHERE PACKAGE_ID = "
                    + to_string(packaged_id) + ";";
    result R(N.exec(sql));
    if(R.size()==0){
        return -1;
    }
    else if((R[0][1].as<string>()).compare("DELIVERED")==0){
        return -1;
    }
    else{
        return R[0][0].as<int>();
    }
}

bool UPSData::changeAddress(int64_t package_id,int x,int y){
    printLog("--------------changeAddress---------------");
    std::lock_guard <std::mutex> lck(mtx);
    work W(*C);
    string sql_select = "SELECT PACKAGE.STATUS FROM PACKAGE WHERE PACKAGE_ID = '"
                        + to_string(package_id) + "' FOR UPDATE;";
    result R(W.exec(sql_select));
    if(R.size()==0){
        W.commit();
        printLog("--------------Not change due to no package id---------------");
        return false;
    }
    else if(((R[0][0].as<string>()).compare("LOADED")==0) || ((R[0][0].as<string>()).compare("DELIVERING")==0) || ((R[0][0].as<string>()).compare("DELIVERED")==0)){
        W.commit();
        printLog("--------------Not change due to unavaliable status---------------");
        return false;
    }
    else{
        
        string sql = "UPDATE PACKAGE SET ADDR_X = " + to_string(x) + " ,ADDR_Y = "
                 + to_string(y) + " WHERE PACKAGE_ID = "+ to_string(package_id) + ";";
        W.exec(sql);
        W.commit();
        printLog("--------------Changed Address in database---------------");
        return true;
    }
}

bool UPSData::checkWarehouse(int warehouseID){
    nontransaction N(*C);
    string sql = "SELECT * FROM WAREHOUSE WHERE WAREHOUSE_ID="+ to_string(warehouseID);
    result r(N.exec(sql));
    if(r.size()){
        return true;
    }
    return false;
}

void UPSData::insertWarehouse(const Warehouse &warehouse) {
    printLog("--------------InsertWarehouse---------------");
    int id = warehouse.warehouseid();
    int x = warehouse.x();
    int y = warehouse.y();
    std::lock_guard <std::mutex> lck(mtx);
    if(checkWarehouse(id)){
        return;
    }
    printLog("--------------InsertWarehouse Start Insert---------------");
    work W(*C);
    string sql = "INSERT INTO WAREHOUSE (WAREHOUSE_ID, X, Y) VALUES (" + to_string(id) + ","
            + to_string(x) + ","
            + to_string(y) + ")";
    W.exec(sql);
    printLog("--------------InsertWarehouse Start Insert EXEC---------------");
    W.commit();
}

int UPSData::findWarehouse(int x, int y){
    nontransaction N(*C);
    string sql = "SELECT WAREHOUSE_ID FROM WAREHOUSE WHERE X ="+ to_string(x) + " AND Y = " 
                + to_string(y);
    result r(N.exec(sql));
    if(r.size()==0){
        //error status
        return -1;
    }
    int id = r[0][0].as<int>();
    return id;
}