#pragma once
//VectorBillStorage.h
#include <vector>
#include <string>
#include "BillStorage.h"
class VectorBillStorage : public BillStorage {// ʹ�� std::vector �洢�˵�����
public:
    void addBill(const Bill& bill) override;
    const std::vector<Bill>& getAllBills() const override;

    const std::vector<Bill>& findBillsByDate(const std::string& date) const override;
    void printAllBill() const override;
    int size() override;

private:
    std::vector<Bill> bills;
    mutable std::vector<Bill> filteredBills;   // ���ڴ洢ɸѡ����ĳ�Ա����


};
