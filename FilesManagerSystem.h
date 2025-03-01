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
    std::fstream & getBillFile(); //获取文件流
    std::fstream & getDataFile(); //获取文件流

    int writeAllBill();//把所有bill写入bill.data
    int addBill(const Bill);//在当前的bill.data后增加一个
    //int insertbill();

    bool clear();//清空文件

private:
    std::fstream datafile;
    //std::istream datafileis;
    //std::istream datafileout;
    std::fstream billfile;
    const std::string datafilename= "data.dat";
    const std::string billfilename = "bill.dat";
};

