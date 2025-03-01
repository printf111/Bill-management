//VectorBillStorage.cpp
#include "VectorBillStorage.h"
void VectorBillStorage::addBill(const Bill& bill) {
    bills.push_back(bill);
}

const std::vector<Bill>& VectorBillStorage::getAllBills() const {
    return bills;
}

const std::vector<Bill>& VectorBillStorage::findBillsByDate(const std::string& date) const {
    // 清空之前的筛选结果
    filteredBills.clear();
    for (const auto& bill : bills) {
        if (bill.getDate() == date) {
            filteredBills.push_back(bill);
        }
    }
    return filteredBills;
}

void VectorBillStorage::printAllBill() const 
{
    int number = bills.size();
    for (int i = 0;i < number;i++)
    {
        std::cout << bills.at(i) << std::endl;
    }
}

int VectorBillStorage::size()
{
    return this->bills.size();
}

