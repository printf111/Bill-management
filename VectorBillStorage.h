#pragma once
//VectorBillStorage.h
#include <vector>
#include <string>
#include "BillStorage.h"
class VectorBillStorage : public BillStorage {// 使用 std::vector 存储账单的类
public:
    void addBill(const Bill& bill) override;
    const std::vector<Bill>& getAllBills() const override;

    const std::vector<Bill>& findBillsByDate(const std::string& date) const override;
    void printAllBill() const override;
    int size() override;

private:
    std::vector<Bill> bills;
    mutable std::vector<Bill> filteredBills;   // 用于存储筛选结果的成员变量


};
