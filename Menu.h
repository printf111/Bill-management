#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "BillManagementSystem.h"
class Menu {
public:

    Menu(BillManagementSystem* bms) :billmanagesystem(bms) {};
    BillManagementSystem* billmanagesystem;
    enum CommandType {
        HELP,
        ADD,
        SHOW,
        REMOVE,
        CHANGE,
        SAVE,  // ���� SAVE ��������
        INVALID
    };

    struct Command {
        CommandType type;
        std::vector<std::string> params;
    };

    void Run() {
        ShowMenu();
        while (true) {
            auto cmd = ParseCommand();
            std::cout << cmd.type << std::endl;
            for (auto i : cmd.params)
                std::cout << i << std::endl;
            if (!ValidateCommand(cmd)) {
                ShowError("��Ч����");
                continue;
            }

            ExecuteCommand(cmd);
        }
    }

private:
    static void ShowMenu() {
        std::cout << "�����ʽ������ӿո�Ӳ�������ѡ����" << std::endl;
        std::cout << "��ʾ����  help ���� " << std::endl;
        std::cout << "չʾ�˵���������    show��ע��������С��50ʱĬ�ϲ�ɸѡ��ʾ�������ɸѡ��������ɸѡ������" << std::endl;
        std::cout << "�����˵�  add" << std::endl;
        std::cout << "ɾ���˵�  remove" << std::endl;
        std::cout << "�޸��˵�  change" << std::endl;
        std::cout << "�����˵�  save" << std::endl;
        std::cout << "�����룺";
    }

    Command ParseCommand() {
        std::string input;
        std::getline(std::cin, input);

        Command cmd;
        std::istringstream iss(input);
        std::string token;

        // ������������
        if (iss >> token) {
            cmd.type = ConvertCommand(token);
        }

        // ��������
        while (iss >> token) {
            cmd.params.push_back(token);
        }

        return cmd;
    }

    CommandType ConvertCommand(const std::string& str) {
        if (str == "help") return HELP;
        if (str == "add") return ADD;
        if (str == "show") return SHOW;
        if (str == "remove") return REMOVE;
        if (str == "change") return CHANGE;
        if (str == "save") return SAVE;
        return INVALID;
    }

    bool ValidateCommand(const Command& cmd) {
        switch (cmd.type) {
        case ADD:
            return ValidateAddParams(cmd.params);
        case CHANGE:
            return ValidateChangeParams(cmd.params);
        case REMOVE:
            return ValidateRemoveParams(cmd.params);
        case SHOW:
            return ValidateShowParams(cmd.params);
        case SAVE:
            return ValidateSaveParams(cmd.params);
        default:
            return true;
        }
    }

    bool ValidateAddParams(const std::vector<std::string>& params) {
        // �����������
        if (params.size() != 6) return false;

        // ���ڸ�ʽ��֤
        if (!std::regex_match(params[0], std::regex(R"(\d{4}-\d{2}-\d{2})"))) {
            return false;
        }

        // �����֤
        try {
            std::stod(params[4]);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    bool ValidateChangeParams(const std::vector<std::string>& params) {
        // �����������޸����������֤�߼�
        return false;
    }

    bool ValidateRemoveParams(const std::vector<std::string>& params) {
        // ����������ɾ�����������֤�߼�
        return false;
    }

    bool ValidateShowParams(const std::vector<std::string>& params) {
        // ����������չʾ���������֤�߼�
        return false;
    }

    bool ValidateSaveParams(const std::vector<std::string>& params) {
        // ���� save �����Ҫ���������Բ�������Ϊ 0 ʱ��Ч
        if (params.size() == 0)
            return false;
        else
        {
            std::cout << "saveû�ж������" << std::endl;
        }
    }

    void ExecuteCommand(const Command& cmd) {
        switch (cmd.type) {
        case HELP:
            ShowHelp(cmd.params);
            break;
        case ADD:
            HandleAdd(cmd.params);
            break;
        case SHOW:
            HandleShow(cmd.params);
            break;
        case REMOVE:
            HandleRemove(cmd.params);
            break;
        case CHANGE:
            HandleChange(cmd.params);
            break;
        case SAVE:
            HandleSave(cmd.params);  // ���� save �����
            break;
        case INVALID:
            ShowError("��Ч��������");
            break;
        }
    }

    void HandleAdd(const std::vector<std::string>& params) {
        // ��������߼�
        std::cout << "��������˵�..." << std::endl;

    }

    void HandleShow(const std::vector<std::string>& params) {
        // ����չʾ�߼�
        std::cout << "����չʾ�˵�..." << std::endl;
    }

    void HandleRemove(const std::vector<std::string>& params) {
        // ����ɾ���߼�
        std::cout << "����ɾ���˵�..." << std::endl;
    }

    void HandleChange(const std::vector<std::string>& params) {
        // �����޸��߼�
        std::cout << "�����޸��˵�..." << std::endl;
    }

    void HandleSave(const std::vector<std::string>& params) {
        // ���屣���߼�
        std::cout << "���ڱ����˵�..." << std::endl;
        // ����������ʵ�ʵı�����룬���罫�˵�����д���ļ�
    }

    static void ShowHelp(const std::vector<std::string>& params) {
        if (params.empty()) {
            // ��ʾͨ�ð�����Ϣ
            std::cout << "ͨ�ð�����Ϣ��" << std::endl;
            std::cout << "����˳��" << std::endl;
            std::cout << "-����ָ����Χ���˵�" << std::endl;
            std::cout << "-year-month-day -time hh:mm:ss(Ĭ��ֵΪ23:59:59)" << std::endl;
            std::cout << "-kind numberָ�����" << std::endl;
            std::cout << "-id id1-id2,id3(not creat )" << std::endl;
            std::cout << "-all ��ʾȫ����ʹ�ô˲���ʱ������������ǰ���ѡ��" << std::endl;
            std::cout << "save ������浱ǰ�˵����ݣ��޲���" << std::endl;  // ���� save ���������Ϣ
        }
        else if (params[0] == "show") {
            std::cout << "show ���������Ϣ��" << std::endl;
            std::cout << "����˳��" << std::endl;
            std::cout << "����ָ����Χ���˵�" << std::endl;
            std::cout << "-data -year-month-day -time hh:mm:ss(Ĭ��ֵΪ23:59:59)" << std::endl;
            std::cout << "-kind numberָ�����" << std::endl;
            std::cout << "-id id1-id2,id3(not creat )" << std::endl;
            std::cout << "-all ��ʾȫ����ʹ�ô˲���ʱ������������ǰ���ѡ��" << std::endl;
        }
        else if (params[0] == "add") {
            std::cout << "add ���������Ϣ��" << std::endl;
            std::cout << "����˳��" << std::endl;
            std::cout << "����(yyyy-mm-dd) ʱ��(hh:mm) ���� ����/֧��(i/o) ���(��������С��������2.00) ����" << std::endl;
            std::cout << "ע�⣺������Ҫ���ո��������  ��Ӻ��Զ�д���ļ�" << std::endl;
            std::cout << "��:add 2025-02-24 12:00 ����1dscripion i 2.01 2" << std::endl;
        }
        else if (params[0] == "change") {
            std::cout << "change ���������Ϣ��" << std::endl;
            std::cout << "����˳��ID " << std::endl;
            std::cout << "����(yyyy-mm-dd) ʱ��(hh:mm) ���� ����/֧��(i/o) ���(��������С��������2.00) ����" << std::endl;
            std::cout << "ע�⣺������Ҫ���ո��������" << std::endl;
            std::cout << "��:change ID 2 2025-02-24 12:00 ����1dscripion Income 2.01 2" << std::endl;
        }
        else if (params[0] == "remove") {
            std::cout << "remove ���������Ϣ��" << std::endl;
            std::cout << "����˳��ID" << std::endl;
            std::cout << "��:remove 1" << std::endl;
        }
        else if (params[0] == "save") {
            std::cout << "save ���������Ϣ��" << std::endl;
            std::cout << "���浱ǰ�˵����ݣ��޲�����" << std::endl;
        }
    }

    static void ShowError(const std::string& message) {
        std::cout << "����: " << message << std::endl;
    }
};

