#pragma once
//BillManagementSystem.h
#include <vector>
#include <string>
#include "BillStorage.h"
#include "FilesManagerSystem.h"
#include "VectorBillStorage.h"
// �˵�����ϵͳ��
class BillManagementSystem {
public:
    BillManagementSystem(BillStorage* storage,FilesManagerSystem* filesmanager);

    int readBill();
    int readData();

    void addBill(const Bill& bill);
    void printDiscripition() const;
    void printAllBill() const;
    void findBillsByDate(const std::string& date) const;
    int size();
    
    
    //void change(std::string commond);
    void writeWithPrint();
    // ���� << �� >> ���������
    friend std::ostream& operator<<(std::ostream& os, const BillManagementSystem& bms);
    friend std::istream& operator>>(std::istream& is, BillManagementSystem& bms);

private:
    BillStorage* storage;
    FilesManagerSystem* filesmanager;
    std::string password;//����Ա����
    int billnumber;//�˵�����
    std::vector<std::string> billkinddiscripition;//���ڱ���ÿ���˵�������
};
