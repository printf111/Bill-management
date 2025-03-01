//Bill.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Bill.h"
Bill::Bill(const std::string& description, double amount, bool type,
    TimePoint datetime, int kind)
    : description(description), amount(amount), type(type),
    datetime(datetime), kind(kind), id(0) {
}

Bill::Bill(const Bill& other)
    : datetime(other.datetime),
    description(other.description),
    amount(other.amount),
    type(other.type),
    id(other.id),
    kind(other.kind) {
}
std::string Bill::getDate() const {
    
    auto days = std::chrono::floor<std::chrono::days>(datetime);
    std::time_t tt = std::chrono::system_clock::to_time_t(days);
    std::tm tm = *std::localtime(&tt);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return buffer;
    
}

std::string Bill::getDescription() const {
    return description;
}

double Bill::getAmount() const {
    return amount;
}

void Bill::setId(int id)
{
    this->id = id;
}

// ������������
std::ostream& operator<<(std::ostream& os, const Bill& bill) {

    // ��ʱ���ת��Ϊ time_t ����
    std::time_t tt = std::chrono::system_clock::to_time_t(
        std::chrono::time_point_cast<std::chrono::system_clock::duration>(bill.datetime));
    std::tm tm = {};
    if (localtime_s(&tm, &tt) != 0) {
        // �������
        std::cerr << "Error converting time." << std::endl;
    }  
    // ��� ID

    os << "ID:" << bill.id<<"  ";


    // ������ں�ʱ��
    os << std::put_time(&tm, "%Y-%m-%d %H:%M") << " ";
    // �������
    os << bill.description << " ";

    // ������ͣ������֧����
    os << (bill.type ? "Income" : "Expense") << " "; 
    // ������
    os << bill.amount << " ";
    // �������
    os << bill.kind << " ";
    return os;
}

// �������������
std::istream& operator>>(std::istream& is, Bill& bill) {
    std::string idStr;
    std::string dateTimeStr;
    std::string TimeStr;
    std::string description;
    double amount;
    std::string typeStr;
    int kind;
    int id;

    // ��ȡ ID
    if (!(is >> idStr)) {
        return is;
    }

    // ȥ�� "ID:" ǰ׺
    idStr = idStr.substr(3);
    bill.id = std::stoi(idStr);

    // ��ȡ���ں�ʱ��
    if (!(is >> dateTimeStr)) {
        std::cerr << "error:6" << std::endl;
        return is;
    }
    if (!(is >> TimeStr)) {
        std::cerr << "error:6" << std::endl;
        return is;
    }
    dateTimeStr += ' ';
    dateTimeStr += TimeStr;
    // �������ں�ʱ��
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    if (!(ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"))) {
        std::cerr << "error:7" << std::endl;
        return is;
    }
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    bill.datetime = std::chrono::time_point_cast<std::chrono::minutes>(timePoint);

    // ��ȡ����
    if (!(is >> description)) {
        std::cerr << "error:8" << std::endl;
        return is;
    }
    bill.description = description;

    // ��ȡ����
    if (!(is >> typeStr)) {
        std::cerr << "error:9" << std::endl;
        return is;
    }
    bill.type = (typeStr == "Income");

    // ��ȡ���
    if (!(is >> amount)) {
        std::cerr << "error:10" << std::endl;
        return is;
    }
    bill.amount = amount;

    // ��ȡ����
    if (!(is >> kind)) {
        std::cerr << "error:11" << std::endl;
        return is;
    }
    bill.kind = kind;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}
std::string Bill::getTime() const
{
    auto since_midnight = datetime - std::chrono::floor<std::chrono::days>(datetime);
    auto hours = std::chrono::duration_cast<std::chrono::hours>(since_midnight);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(since_midnight) % 60;
    char buffer[6];
    std::snprintf(buffer, sizeof(buffer), "%02d:%02d", hours.count(), minutes.count());
    return buffer;
}
