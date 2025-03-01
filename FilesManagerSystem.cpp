//FilesManagerSystem.cpp
#include "FilesManagerSystem.h"
#include <filesystem>
FilesManagerSystem::FilesManagerSystem()
{
    /***********  打开data.dat  *************/
    
    //本函数如果不额外使用std::ios::app，只能打开而无法在不存在时新建，但使用了std::ios::app又会导致文件指针始终在最后，故打开后再关闭更换权限
    namespace fs = std::filesystem;
    if (fs::exists(billfilename)) {
        std::cout << "文件 " << billfilename << " 存在" << std::endl;
    }
    else {
        // 尝试创建文件
        billfile.open(billfilename, std::ios::out | std::ios::app);
        if (billfile.is_open()) {
            std::cout << "检测文件不存在，已新建 " << billfilename << std::endl;
            billfile.close();
        }
        else {
            std::cerr << "文件不存在，且无法创建文件: " << billfilename <<"，退出程序" << std::endl;
            exit(-1);
        }
    }
    billfile.open(billfilename, std::ios::in | std::ios::out);
    if (!billfile.is_open()) {
        std::cerr << "无法打开文件: " << billfilename << "，退出程序" << std::endl;
        exit(-1);
    }
    else
    {
        std::cout << "打开文件完成" << std::endl;

    }

    /********  打开bill.dat  *******/
    //本函数如果不额外使用std::ios::app，只能打开而无法在不存在时新建，但使用了std::ios::app又会导致文件指针始终在最后，故打开后再关闭更换权限
    namespace fs = std::filesystem;
    if (fs::exists(datafilename)) {
        std::cout << "文件 " << datafilename << " 存在" << std::endl;
    }
    else {
        // 尝试创建文件
        datafile.open(datafilename, std::ios::out | std::ios::app);
        if (datafile.is_open()) {
            std::cout << "检测文件不存在，已新建 " << datafilename << std::endl;
            datafile.close();
        }
        else {
            std::cerr << "文件不存在，且无法创建文件: " << datafilename <<"，退出程序"<< std::endl;
            exit(-1);
        }
    }
    datafile.open(datafilename, std::ios::in | std::ios::out | std::ios::binary);
    if (!datafile.is_open()) {
        std::cerr << "无法打开文件: " << datafilename << "，退出程序"<<std::endl;
        exit(-1);
    }
    else
    {
        std::cout << "打开文件完成" <<std::endl;
    }
}


std::fstream& FilesManagerSystem::getBillFile()
{
    return this->billfile;
}
std::fstream& FilesManagerSystem::getDataFile()
{
    return this->datafile;
}
int FilesManagerSystem::addBill(const Bill A)
{
    if (billfile.is_open()) // 检查文件是否已经打开
    {
        billfile << A << std::endl;;
        if (billfile.fail()) // 检查写入操作是否失败
        {
            std::cerr << "写入文件失败" << std::endl;
            return -1; // 返回错误码
        }
        billfile.flush(); // 刷新缓冲区
    }
    else
    {
        std::cerr << "文件未打开，无法写入" << std::endl;
        return -1; // 返回错误码
    }  
    std::cout << "增加成功" << std::endl;
    return 0;
}
bool FilesManagerSystem::clear()
{
    if (!datafile.is_open()) {
        std::cerr << "文件指针无效或文件未打开。" << std::endl;
        return false;
    }

    // 将文件指针定位到文件开头
    datafile.seekp(0, std::ios::beg);
    // 清除流的错误状态
    datafile.clear();
    // 截断文件，将文件大小置为 0
    datafile.close();
    datafile.open(datafilename, std::ios::out | std::ios::trunc);
    if (!datafile.is_open()) {
        std::cerr << "无法重新以截断模式打开文件。" << std::endl;
        return false;
    }
    datafile.close();
    datafile.open(datafilename, std::ios::out | std::ios::out | std::ios::binary);
    return true;
}
