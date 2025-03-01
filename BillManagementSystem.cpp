//BillManagementSystem.cpp
#include "BillManagementSystem.h"
BillManagementSystem::BillManagementSystem(BillStorage* storage, FilesManagerSystem* filesmanager)
    : storage(storage), billnumber(0),filesmanager(filesmanager){
    this->billkinddiscripition.resize(10);
}
int BillManagementSystem::readBill()
{

    std::fstream& file = filesmanager->getBillFile();
    file.seekg(0, std::ios::beg);
    file.seekp(0, std::ios::beg);

    Bill t;
    while (!file.eof())
    {       
        file >> t;
        if (file.eof())
        {
            break;
       }

        billnumber++;
        storage->addBill(t);
    }

    if (file.fail())
    {     
        file.flush();
        file.clear();
    }

    std::cout << "成功读取" << billnumber << "条信息" << std::endl;
    return 0;
}
int BillManagementSystem::readData()
{
    std::fstream &file= filesmanager->getDataFile();
    file.seekg(0, std::ios::beg);
    file.seekp(0, std::ios::beg);
    file >> *this;

    //读取基础信息

    if (file.good())
    {
        std::cout << "成功读取账单数量及描述信息" << std::endl;
    }
    else
    {
        std::cerr << "初始信息读取错误" << std::endl;
        std::cout << "数据文件已损坏或无内容，是否清空文件并完全重新录入数据(Y?N)" << std::endl;
        char yn;
        std::cin >> yn;
        while (getchar() != '\n');//消耗换行符
        bool validInput = false;
        while (!validInput)
        {
            switch (yn)
            {
            case 'n':
            case 'N': {
                std::cout << "退出程序" << std::endl;
                return -1;
            }
            case 'y':
            case 'Y': {
                std::cout << "程序继续" << std::endl;
                file.clear(); // 清除错误标志
                if (!file.good()) {
                    std::cerr << "文件流状态错误，无法写入数据。" << std::endl;
                    return -1;
                }


                this->writeWithPrint();
                file << (*this);//记住这里是指针，要解引用

                if (file.fail()) {
                    std::cerr << "写入数据时发生错误。" << std::endl;
                    return -1;
                }
                std::cout << "录入完成" << std::endl;
                validInput = true;
                break;
            }
            default:
            {
                std::cout << "输入错误，请重新输入" << std::endl;
                std::cin >> yn;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            }
        }
    }
    return 0;
}
void BillManagementSystem::addBill(const Bill& bill) {
    Bill newBill = bill;
    newBill.setId(++billnumber); // 设置账单的id
    
    
    storage->addBill(newBill);

    this->filesmanager->addBill(newBill);
}

void BillManagementSystem::printDiscripition() const
{
    for (int i = 1;i <= 9;i++)
        std::cout << i << ":" <<billkinddiscripition.at(i)<< std::endl;
}

void BillManagementSystem::printAllBill() const
{
    this->storage->printAllBill();
   
}

void BillManagementSystem::findBillsByDate(const std::string& date) const {
    const auto bills = storage->findBillsByDate(date);
    if (bills.empty()) {
        std::cout << "No bills found for the date: " << date << std::endl;
    }
    else {
        for (const auto& bill : bills) {
            std::cout << "Date: " << bill.getDate() << ", Description: " << bill.getDescription()
                << ", Amount: " << bill.getAmount() << std::endl;
        }
    }
}
int BillManagementSystem::size(void)
{
    return billnumber;
}

void BillManagementSystem::writeWithPrint()
{
   // std::vector<std::string> billkinddiscripition;//用于保存每种账单的描述
    billkinddiscripition.resize(10);
    std::cout << "设置管理员密码，保证长度恰好为10个字符（数字，大小写字母，英文字符）" << std::endl; 
    std::cin >> this->password;
    while (this->password.length() != 10)
    {
        std::cout<< "长度不为10 ，重新输入" << std::endl;
        std::cin >> this->password;
    }
    this->billnumber = 0;
    for (int i = 0;i < 10;i++)
    {
        std::cout << "序号" << i << " : 输入描述，输入内容不要多于150字符，允许中文，" << std::endl;
        std::string input;
        std::getline(std::cin >> std::ws, input); // 读取整行输入
        if (input.length() > 150) {
            input = input.substr(0, 150); // 截取前150个字符
        }
        billkinddiscripition[i] = input;
        //std::cout << "获取:" << input << std::endl;

    }   
    int i = 0;
    //for (auto str : billkinddiscripition)
       // std::cout << i++ <<"  " << str << std::endl;
}

std::ostream& operator<<(std::ostream& os, const BillManagementSystem& bms) { 
    // 加密密码
    std::string temp = bms.password;
    for (auto& i : temp) {
        i ^= 6;
    }

    // 写入密码长度
    os.seekp(0,std::ios::beg);
    size_t passwordLength = temp.length();
    os.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));   
    // 写入密码内容
    os.write(temp.c_str(), passwordLength);


    // 写入账单种类描述
    for (const auto& str : bms.billkinddiscripition) {
        // 写入描述长度
        size_t descriptionLength = str.length();
        os.write(reinterpret_cast<const char*>(&descriptionLength), sizeof(descriptionLength));
        // 写入描述内容
        os.write(str.c_str(), descriptionLength);
    }   
    //// 写入账单数量*************************废弃
    //os.write(reinterpret_cast<const char*>(&bms.billnumber), sizeof(bms.billnumber));


    return os;
}
// 重载输入运算符，用于反序列化
std::istream& operator>>(std::istream& is, BillManagementSystem& bms) {
    // 读取密码长度
    is.seekg(0, std::ios::beg);
    size_t passwordLength;
    is.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
    if (!is.good() || passwordLength>150 || passwordLength<0) //有防止读取错误而程序崩溃的功能
    {
        is.setstate(std::ios::failbit); // 设置失败标志
        std::cerr << "error:1" << std::endl;
        return is;
    }


    // 读取密码内容
    std::string encryptedPassword;
    encryptedPassword.resize(passwordLength);
    is.read(reinterpret_cast<char*>(&encryptedPassword[0]), passwordLength);
    for (auto& i : encryptedPassword) {
        i ^= 6;
    }


   // std::cerr << "长度" << passwordLength << "密码" << encryptedPassword <<std::endl;
    if (!is.good()) {
        is.setstate(std::ios::failbit); // 设置失败标志        
        std::cerr << "error:2" << std::endl;
        return is;
    }  
    // 解密密码

    bms.password = encryptedPassword;

    // 清空原有的账单种类描述
    bms.billkinddiscripition.clear();

    // 读取账单种类描述
    for(int i=0;i<10;i++)
    {
        // 读取描述长度
        size_t descriptionLength;
        is.read(reinterpret_cast<char*>(&descriptionLength), sizeof(descriptionLength));

        //std::cerr << descriptionLength << "::" << std::endl;
        if (!is.good()) {
            is.setstate(std::ios::failbit); // 设置失败标志
            std::cerr << "error:4" << std::endl;
            return is;
        }
        // 读取描述内容
        std::string description(descriptionLength, '\0');
        is.read(&description[0], descriptionLength);
       // std::cerr << descriptionLength << std::endl;
        if (!is.good()) {
            is.setstate(std::ios::failbit); // 设置失败标志
            std::cerr << "error:5" << std::endl;
            return is;
        }
        // 将描述添加到数据中
        bms.billkinddiscripition.push_back(description);
    }  
    // 读取账单数量*****************************废弃
    //is.read(reinterpret_cast<char*>(&bms.billnumber), sizeof(bms.billnumber));
    ////std::cerr << bms.billnumber << std::endl;
    //if (!is.good() || bms.billnumber > 1e7 || passwordLength < 0) 
    //{
    //    is.setstate(std::ios::failbit); // 设置失败标志
    //    std::cerr << "error:3" << std::endl;
    //    return is;
    //}

    return is;
}
