//#pragma once
////Menu.h
//#include <iostream>
//#include <string>
//class Menu
//{
//	static void MENU()
//	{
//		printf("输入格式：命令加空格加参数，可选命令");
//		printf("显示帮助   help 命令 \n");
//		printf("展示账单所有内容    show（注：当条数小于50时默认不筛选显示，如果想筛选，请增加筛选参数）\n");
//		printf("增加账单  add\n");
//		printf("删除账单  remove"
//				"修改账单change "
//				"\n");
//		std::getline(std::cin,commond);
//		if (commond.substr(4) == "help")
//		{
//			commond.erase(5);
//			if (commond == "show")
//			{
//				Menu::showhelp();
//				return;
//			}
//			if (commond == "add")
//			{
//				Menu::addhelp();
//				return;
//			}
//			if (commond == "change")
//			{
//				Menu::changehelp();
//				return;
//			}
//			if (commond == "remove")
//			{
//				Menu::removehelp();
//				return;
//			}
//		}
//		else if (commond.substr(3) == "add")
//		{
//
//		}
//		else if (commond.substr(6) == "change")
//		{
//
//		}
//		else if (commond.substr(4) == "show")
//		{
//
//		}
//		else if (commond.substr(6) == "remove")
//		{
//
//		}
//		else
//		{
//			size_t spacePos = commond.find(' ');
//			if (spacePos != std::string::npos) {	
//				commond=commond.substr(0, spacePos);
//			}
//			std::cout<<"commond :"<<commond <<"无效！" << std::endl
//
//		}
//	}
//	static int addhelp(void)
//	{
//		printf("参数顺序：\n"
//			"日期(yyyy-mm-dd) 时间(hh:mm) 描述 收入/支出(i/o) 金额(建议输入小数，比如2.00) 种类"
//			"注意：描述不要带空格否则会出错\n"
//			"例:add 2025-02-24 12:00 测试1dscripion Income 2.01 2");
//	}
//	static int changehelp(void)
//	{
//		printf("参数顺序：ID \n"
//			"日期(yyyy-mm-dd) 时间(hh:mm) 描述 收入/支出(i/o) 金额(建议输入小数，比如2.00) 种类"
//			"注意：描述不要带空格否则会出错\n"
//			"例:change ID 2 2025-02-24 12:00 测试1dscripion Income 2.01 2");
//	}
//	static int removehelp(void)
//	{
//		printf("参数顺序：ID\n"
//			"例:remove 1");
//	}
//	static void showhelp(void)
//	{
//		printf("参数顺序：\n"
//			"-rest\n"
//			"查找指定范围的账单\n"
//			"-data -year-month-day -time hh:mm:ss(默认值为23:59:59)\n"
//			"-kind number指定序号\n"
//			"-id id1-id2,id3(not creat )\n"
//			"-all 显示全部，使用此参数时，不得有其他前面的选项\n");
//	}
//	static std::string commond;
//};
//static std::string commond;
//
//
//