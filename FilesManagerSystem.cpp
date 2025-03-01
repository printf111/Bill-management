//FilesManagerSystem.cpp
#include "FilesManagerSystem.h"
#include <filesystem>
FilesManagerSystem::FilesManagerSystem()
{
    /***********  ��data.dat  *************/
    
    //���������������ʹ��std::ios::app��ֻ�ܴ򿪶��޷��ڲ�����ʱ�½�����ʹ����std::ios::app�ֻᵼ���ļ�ָ��ʼ������󣬹ʴ򿪺��ٹرո���Ȩ��
    namespace fs = std::filesystem;
    if (fs::exists(billfilename)) {
        std::cout << "�ļ� " << billfilename << " ����" << std::endl;
    }
    else {
        // ���Դ����ļ�
        billfile.open(billfilename, std::ios::out | std::ios::app);
        if (billfile.is_open()) {
            std::cout << "����ļ������ڣ����½� " << billfilename << std::endl;
            billfile.close();
        }
        else {
            std::cerr << "�ļ������ڣ����޷������ļ�: " << billfilename <<"���˳�����" << std::endl;
            exit(-1);
        }
    }
    billfile.open(billfilename, std::ios::in | std::ios::out);
    if (!billfile.is_open()) {
        std::cerr << "�޷����ļ�: " << billfilename << "���˳�����" << std::endl;
        exit(-1);
    }
    else
    {
        std::cout << "���ļ����" << std::endl;

    }

    /********  ��bill.dat  *******/
    //���������������ʹ��std::ios::app��ֻ�ܴ򿪶��޷��ڲ�����ʱ�½�����ʹ����std::ios::app�ֻᵼ���ļ�ָ��ʼ������󣬹ʴ򿪺��ٹرո���Ȩ��
    namespace fs = std::filesystem;
    if (fs::exists(datafilename)) {
        std::cout << "�ļ� " << datafilename << " ����" << std::endl;
    }
    else {
        // ���Դ����ļ�
        datafile.open(datafilename, std::ios::out | std::ios::app);
        if (datafile.is_open()) {
            std::cout << "����ļ������ڣ����½� " << datafilename << std::endl;
            datafile.close();
        }
        else {
            std::cerr << "�ļ������ڣ����޷������ļ�: " << datafilename <<"���˳�����"<< std::endl;
            exit(-1);
        }
    }
    datafile.open(datafilename, std::ios::in | std::ios::out | std::ios::binary);
    if (!datafile.is_open()) {
        std::cerr << "�޷����ļ�: " << datafilename << "���˳�����"<<std::endl;
        exit(-1);
    }
    else
    {
        std::cout << "���ļ����" <<std::endl;
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
    if (billfile.is_open()) // ����ļ��Ƿ��Ѿ���
    {
        billfile << A << std::endl;;
        if (billfile.fail()) // ���д������Ƿ�ʧ��
        {
            std::cerr << "д���ļ�ʧ��" << std::endl;
            return -1; // ���ش�����
        }
        billfile.flush(); // ˢ�»�����
    }
    else
    {
        std::cerr << "�ļ�δ�򿪣��޷�д��" << std::endl;
        return -1; // ���ش�����
    }  
    std::cout << "���ӳɹ�" << std::endl;
    return 0;
}
bool FilesManagerSystem::clear()
{
    if (!datafile.is_open()) {
        std::cerr << "�ļ�ָ����Ч���ļ�δ�򿪡�" << std::endl;
        return false;
    }

    // ���ļ�ָ�붨λ���ļ���ͷ
    datafile.seekp(0, std::ios::beg);
    // ������Ĵ���״̬
    datafile.clear();
    // �ض��ļ������ļ���С��Ϊ 0
    datafile.close();
    datafile.open(datafilename, std::ios::out | std::ios::trunc);
    if (!datafile.is_open()) {
        std::cerr << "�޷������Խض�ģʽ���ļ���" << std::endl;
        return false;
    }
    datafile.close();
    datafile.open(datafilename, std::ios::out | std::ios::out | std::ios::binary);
    return true;
}
