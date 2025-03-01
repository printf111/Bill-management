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

    std::cout << "�ɹ���ȡ" << billnumber << "����Ϣ" << std::endl;
    return 0;
}
int BillManagementSystem::readData()
{
    std::fstream &file= filesmanager->getDataFile();
    file.seekg(0, std::ios::beg);
    file.seekp(0, std::ios::beg);
    file >> *this;

    //��ȡ������Ϣ

    if (file.good())
    {
        std::cout << "�ɹ���ȡ�˵�������������Ϣ" << std::endl;
    }
    else
    {
        std::cerr << "��ʼ��Ϣ��ȡ����" << std::endl;
        std::cout << "�����ļ����𻵻������ݣ��Ƿ�����ļ�����ȫ����¼������(Y?N)" << std::endl;
        char yn;
        std::cin >> yn;
        while (getchar() != '\n');//���Ļ��з�
        bool validInput = false;
        while (!validInput)
        {
            switch (yn)
            {
            case 'n':
            case 'N': {
                std::cout << "�˳�����" << std::endl;
                return -1;
            }
            case 'y':
            case 'Y': {
                std::cout << "�������" << std::endl;
                file.clear(); // ��������־
                if (!file.good()) {
                    std::cerr << "�ļ���״̬�����޷�д�����ݡ�" << std::endl;
                    return -1;
                }


                this->writeWithPrint();
                file << (*this);//��ס������ָ�룬Ҫ������

                if (file.fail()) {
                    std::cerr << "д������ʱ��������" << std::endl;
                    return -1;
                }
                std::cout << "¼�����" << std::endl;
                validInput = true;
                break;
            }
            default:
            {
                std::cout << "�����������������" << std::endl;
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
    newBill.setId(++billnumber); // �����˵���id
    
    
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
   // std::vector<std::string> billkinddiscripition;//���ڱ���ÿ���˵�������
    billkinddiscripition.resize(10);
    std::cout << "���ù���Ա���룬��֤����ǡ��Ϊ10���ַ������֣���Сд��ĸ��Ӣ���ַ���" << std::endl; 
    std::cin >> this->password;
    while (this->password.length() != 10)
    {
        std::cout<< "���Ȳ�Ϊ10 ����������" << std::endl;
        std::cin >> this->password;
    }
    this->billnumber = 0;
    for (int i = 0;i < 10;i++)
    {
        std::cout << "���" << i << " : �����������������ݲ�Ҫ����150�ַ����������ģ�" << std::endl;
        std::string input;
        std::getline(std::cin >> std::ws, input); // ��ȡ��������
        if (input.length() > 150) {
            input = input.substr(0, 150); // ��ȡǰ150���ַ�
        }
        billkinddiscripition[i] = input;
        //std::cout << "��ȡ:" << input << std::endl;

    }   
    int i = 0;
    //for (auto str : billkinddiscripition)
       // std::cout << i++ <<"  " << str << std::endl;
}

std::ostream& operator<<(std::ostream& os, const BillManagementSystem& bms) { 
    // ��������
    std::string temp = bms.password;
    for (auto& i : temp) {
        i ^= 6;
    }

    // д�����볤��
    os.seekp(0,std::ios::beg);
    size_t passwordLength = temp.length();
    os.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));   
    // д����������
    os.write(temp.c_str(), passwordLength);


    // д���˵���������
    for (const auto& str : bms.billkinddiscripition) {
        // д����������
        size_t descriptionLength = str.length();
        os.write(reinterpret_cast<const char*>(&descriptionLength), sizeof(descriptionLength));
        // д����������
        os.write(str.c_str(), descriptionLength);
    }   
    //// д���˵�����*************************����
    //os.write(reinterpret_cast<const char*>(&bms.billnumber), sizeof(bms.billnumber));


    return os;
}
// ������������������ڷ����л�
std::istream& operator>>(std::istream& is, BillManagementSystem& bms) {
    // ��ȡ���볤��
    is.seekg(0, std::ios::beg);
    size_t passwordLength;
    is.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
    if (!is.good() || passwordLength>150 || passwordLength<0) //�з�ֹ��ȡ�������������Ĺ���
    {
        is.setstate(std::ios::failbit); // ����ʧ�ܱ�־
        std::cerr << "error:1" << std::endl;
        return is;
    }


    // ��ȡ��������
    std::string encryptedPassword;
    encryptedPassword.resize(passwordLength);
    is.read(reinterpret_cast<char*>(&encryptedPassword[0]), passwordLength);
    for (auto& i : encryptedPassword) {
        i ^= 6;
    }


   // std::cerr << "����" << passwordLength << "����" << encryptedPassword <<std::endl;
    if (!is.good()) {
        is.setstate(std::ios::failbit); // ����ʧ�ܱ�־        
        std::cerr << "error:2" << std::endl;
        return is;
    }  
    // ��������

    bms.password = encryptedPassword;

    // ���ԭ�е��˵���������
    bms.billkinddiscripition.clear();

    // ��ȡ�˵���������
    for(int i=0;i<10;i++)
    {
        // ��ȡ��������
        size_t descriptionLength;
        is.read(reinterpret_cast<char*>(&descriptionLength), sizeof(descriptionLength));

        //std::cerr << descriptionLength << "::" << std::endl;
        if (!is.good()) {
            is.setstate(std::ios::failbit); // ����ʧ�ܱ�־
            std::cerr << "error:4" << std::endl;
            return is;
        }
        // ��ȡ��������
        std::string description(descriptionLength, '\0');
        is.read(&description[0], descriptionLength);
       // std::cerr << descriptionLength << std::endl;
        if (!is.good()) {
            is.setstate(std::ios::failbit); // ����ʧ�ܱ�־
            std::cerr << "error:5" << std::endl;
            return is;
        }
        // ��������ӵ�������
        bms.billkinddiscripition.push_back(description);
    }  
    // ��ȡ�˵�����*****************************����
    //is.read(reinterpret_cast<char*>(&bms.billnumber), sizeof(bms.billnumber));
    ////std::cerr << bms.billnumber << std::endl;
    //if (!is.good() || bms.billnumber > 1e7 || passwordLength < 0) 
    //{
    //    is.setstate(std::ios::failbit); // ����ʧ�ܱ�־
    //    std::cerr << "error:3" << std::endl;
    //    return is;
    //}

    return is;
}
