#pragma once
//BillManagementSystem.h
#include <vector>
#include <string>
#include "BillStorage.h"
#include "FilesManagerSystem.h"
#include "VectorBillStorage.h"
// 账单管理系统类
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
    // 重载 << 和 >> 运算符声明
    friend std::ostream& operator<<(std::ostream& os, const BillManagementSystem& bms);
    friend std::istream& operator>>(std::istream& is, BillManagementSystem& bms);

private:
    BillStorage* storage;
    FilesManagerSystem* filesmanager;
    std::string password;//管理员密码
    int billnumber;//账单数量
    std::vector<std::string> billkinddiscripition;//用于保存每种账单的描述
};
