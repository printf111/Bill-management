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
        SAVE,  // 新增 SAVE 命令类型
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
                ShowError("无效命令");
                continue;
            }

            ExecuteCommand(cmd);
        }
    }

private:
    static void ShowMenu() {
        std::cout << "输入格式：命令加空格加参数，可选命令" << std::endl;
        std::cout << "显示帮助  help 命令 " << std::endl;
        std::cout << "展示账单所有内容    show（注：当条数小于50时默认不筛选显示，如果想筛选，请增加筛选参数）" << std::endl;
        std::cout << "增加账单  add" << std::endl;
        std::cout << "删除账单  remove" << std::endl;
        std::cout << "修改账单  change" << std::endl;
        std::cout << "保存账单  save" << std::endl;
        std::cout << "请输入：";
    }

    Command ParseCommand() {
        std::string input;
        std::getline(std::cin, input);

        Command cmd;
        std::istringstream iss(input);
        std::string token;

        // 解析命令类型
        if (iss >> token) {
            cmd.type = ConvertCommand(token);
        }

        // 解析参数
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
        // 参数数量检查
        if (params.size() != 6) return false;

        // 日期格式验证
        if (!std::regex_match(params[0], std::regex(R"(\d{4}-\d{2}-\d{2})"))) {
            return false;
        }

        // 金额验证
        try {
            std::stod(params[4]);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    bool ValidateChangeParams(const std::vector<std::string>& params) {
        // 这里可以添加修改命令参数验证逻辑
        return false;
    }

    bool ValidateRemoveParams(const std::vector<std::string>& params) {
        // 这里可以添加删除命令参数验证逻辑
        return false;
    }

    bool ValidateShowParams(const std::vector<std::string>& params) {
        // 这里可以添加展示命令参数验证逻辑
        return false;
    }

    bool ValidateSaveParams(const std::vector<std::string>& params) {
        // 假设 save 命令不需要参数，所以参数数量为 0 时有效
        if (params.size() == 0)
            return false;
        else
        {
            std::cout << "save没有额外参数" << std::endl;
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
            HandleSave(cmd.params);  // 新增 save 命令处理
            break;
        case INVALID:
            ShowError("无效命令类型");
            break;
        }
    }

    void HandleAdd(const std::vector<std::string>& params) {
        // 具体添加逻辑
        std::cout << "正在添加账单..." << std::endl;

    }

    void HandleShow(const std::vector<std::string>& params) {
        // 具体展示逻辑
        std::cout << "正在展示账单..." << std::endl;
    }

    void HandleRemove(const std::vector<std::string>& params) {
        // 具体删除逻辑
        std::cout << "正在删除账单..." << std::endl;
    }

    void HandleChange(const std::vector<std::string>& params) {
        // 具体修改逻辑
        std::cout << "正在修改账单..." << std::endl;
    }

    void HandleSave(const std::vector<std::string>& params) {
        // 具体保存逻辑
        std::cout << "正在保存账单..." << std::endl;
        // 这里可以添加实际的保存代码，例如将账单数据写入文件
    }

    static void ShowHelp(const std::vector<std::string>& params) {
        if (params.empty()) {
            // 显示通用帮助信息
            std::cout << "通用帮助信息：" << std::endl;
            std::cout << "参数顺序：" << std::endl;
            std::cout << "-查找指定范围的账单" << std::endl;
            std::cout << "-year-month-day -time hh:mm:ss(默认值为23:59:59)" << std::endl;
            std::cout << "-kind number指定序号" << std::endl;
            std::cout << "-id id1-id2,id3(not creat )" << std::endl;
            std::cout << "-all 显示全部，使用此参数时，不得有其他前面的选项" << std::endl;
            std::cout << "save 命令：保存当前账单数据，无参数" << std::endl;  // 新增 save 命令帮助信息
        }
        else if (params[0] == "show") {
            std::cout << "show 命令帮助信息：" << std::endl;
            std::cout << "参数顺序：" << std::endl;
            std::cout << "查找指定范围的账单" << std::endl;
            std::cout << "-data -year-month-day -time hh:mm:ss(默认值为23:59:59)" << std::endl;
            std::cout << "-kind number指定序号" << std::endl;
            std::cout << "-id id1-id2,id3(not creat )" << std::endl;
            std::cout << "-all 显示全部，使用此参数时，不得有其他前面的选项" << std::endl;
        }
        else if (params[0] == "add") {
            std::cout << "add 命令帮助信息：" << std::endl;
            std::cout << "参数顺序：" << std::endl;
            std::cout << "日期(yyyy-mm-dd) 时间(hh:mm) 描述 收入/支出(i/o) 金额(建议输入小数，比如2.00) 种类" << std::endl;
            std::cout << "注意：描述不要带空格否则会出错  添加后自动写入文件" << std::endl;
            std::cout << "例:add 2025-02-24 12:00 测试1dscripion i 2.01 2" << std::endl;
        }
        else if (params[0] == "change") {
            std::cout << "change 命令帮助信息：" << std::endl;
            std::cout << "参数顺序：ID " << std::endl;
            std::cout << "日期(yyyy-mm-dd) 时间(hh:mm) 描述 收入/支出(i/o) 金额(建议输入小数，比如2.00) 种类" << std::endl;
            std::cout << "注意：描述不要带空格否则会出错" << std::endl;
            std::cout << "例:change ID 2 2025-02-24 12:00 测试1dscripion Income 2.01 2" << std::endl;
        }
        else if (params[0] == "remove") {
            std::cout << "remove 命令帮助信息：" << std::endl;
            std::cout << "参数顺序：ID" << std::endl;
            std::cout << "例:remove 1" << std::endl;
        }
        else if (params[0] == "save") {
            std::cout << "save 命令帮助信息：" << std::endl;
            std::cout << "保存当前账单数据，无参数。" << std::endl;
        }
    }

    static void ShowError(const std::string& message) {
        std::cout << "错误: " << message << std::endl;
    }
};

