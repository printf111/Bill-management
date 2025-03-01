#pragma once
//BillStorage.h
#include <vector>
#include <string>
#include "Bill.h"

class BillStorage {// ³éÏó´æ´¢²ã
public:
    virtual void addBill(const Bill& bill) = 0;
    virtual const std::vector<Bill>& getAllBills() const = 0;
    virtual const std::vector<Bill>& findBillsByDate(const std::string& date) const = 0;
    virtual int size() = 0;
    virtual void printAllBill() const =0;
    virtual ~BillStorage() {}
};
