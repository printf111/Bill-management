#pragma once
//Bill.h
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std::chrono; 
// ��ȷ�����ӵ�ʱ�������
using TimePoint = std::chrono::time_point<
    std::chrono::system_clock,
    std::chrono::minutes
>;
// �˵��࣬�����˵�
class Bill {
public:

    // ���ַ������� ʱ�䲿�ֿ�ѡ��Ĭ��Ϊ���� 00:00��
    static TimePoint ParseDateTime(const std::string& date, const std::string& time = "00:00") {
        std::tm tm = {};
        std::istringstream ss(date + " " + time);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        return std::chrono::time_point_cast<std::chrono::minutes>(tp);
    }
    Bill(const std::string& description, double amount, bool type, TimePoint datetime, int kind = -1);
    Bill(const Bill& other);
    Bill() { id = -1;amount = 0;kind = -1;type = true; };
    // ��ȡ�����ַ�����YYYY-MM-DD��
    std::string getDate() const; 
    // ��ȡʱ���ַ�����HH:MM��
    std::string getTime() const;

    std::string getDescription() const;
    double getAmount() const;
    void setId(int id);

    friend std::ostream& operator<<(std::ostream& os, const Bill& bill);
    friend std::istream& operator>>(std::istream& is, Bill& bill);

private:
    TimePoint datetime;
    std::string description;
    double amount;
    bool type;//����֧��
    int id;//��δ��ʼ��
    int kind;
};


