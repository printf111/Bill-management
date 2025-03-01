//main.cpp
#include <iostream>
#include "BillManagementSystem.h"
#include "FilesManagerSystem.h"
#include "Menu.h"
int main() {
    std::cerr << "��ʼ������" << std::endl;
    BillStorage* billstorage;
    VectorBillStorage storage;
    billstorage = &storage;
    FilesManagerSystem FMS;

  
    BillManagementSystem billmanagement(&storage,&FMS);
    Menu menu(&billmanagement);

    //��ȡ����
    billmanagement.readData();   
    billmanagement.readBill();


    while (1)
    {
        menu.Run();
    }
    //std::cerr << billmanagement.size() << std::endl;
    //TimePoint a = Bill::ParseDateTime("2025-2-24","12:00");
    //Bill b("����1dscripion",2.01f,1,a,2);
    //billmanagement.addBill(b);

    billmanagement.printAllBill();





    return 0;
}     
