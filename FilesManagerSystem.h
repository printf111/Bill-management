#pragma once
//FilesManagerSystem.h
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include "VectorBillStorage.h"
class FilesManagerSystem
{
public:
    FilesManagerSystem();
    std::fstream & getBillFile(); //��ȡ�ļ���
    std::fstream & getDataFile(); //��ȡ�ļ���

    int writeAllBill();//������billд��bill.data
    int addBill(const Bill);//�ڵ�ǰ��bill.data������һ��
    //int insertbill();

    bool clear();//����ļ�

private:
    std::fstream datafile;
    //std::istream datafileis;
    //std::istream datafileout;
    std::fstream billfile;
    const std::string datafilename= "data.dat";
    const std::string billfilename = "bill.dat";
};

