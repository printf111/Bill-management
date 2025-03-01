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

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const Bill& bill) {

    // 将时间点转换为 time_t 类型
    std::time_t tt = std::chrono::system_clock::to_time_t(
        std::chrono::time_point_cast<std::chrono::system_clock::duration>(bill.datetime));
    std::tm tm = {};
    if (localtime_s(&tm, &tt) != 0) {
        // 处理错误
        std::cerr << "Error converting time." << std::endl;
    }  
    // 输出 ID

    os << "ID:" << bill.id<<"  ";


    // 输出日期和时间
    os << std::put_time(&tm, "%Y-%m-%d %H:%M") << " ";
    // 输出描述
    os << bill.description << " ";

    // 输出类型（收入或支出）
    os << (bill.type ? "Income" : "Expense") << " "; 
    // 输出金额
    os << bill.amount << " ";
    // 输出种类
    os << bill.kind << " ";
    return os;
}

// 重载输入运算符
std::istream& operator>>(std::istream& is, Bill& bill) {
    std::string idStr;
    std::string dateTimeStr;
    std::string TimeStr;
    std::string description;
    double amount;
    std::string typeStr;
    int kind;
    int id;

    // 读取 ID
    if (!(is >> idStr)) {
        return is;
    }

    // 去掉 "ID:" 前缀
    idStr = idStr.substr(3);
    bill.id = std::stoi(idStr);

    // 读取日期和时间
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
    // 解析日期和时间
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    if (!(ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"))) {
        std::cerr << "error:7" << std::endl;
        return is;
    }
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    bill.datetime = std::chrono::time_point_cast<std::chrono::minutes>(timePoint);

    // 读取描述
    if (!(is >> description)) {
        std::cerr << "error:8" << std::endl;
        return is;
    }
    bill.description = description;

    // 读取类型
    if (!(is >> typeStr)) {
        std::cerr << "error:9" << std::endl;
        return is;
    }
    bill.type = (typeStr == "Income");

    // 读取金额
    if (!(is >> amount)) {
        std::cerr << "error:10" << std::endl;
        return is;
    }
    bill.amount = amount;

    // 读取种类
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
