//#pragma once
////Menu.h
//#include <iostream>
//#include <string>
//class Menu
//{
//	static void MENU()
//	{
//		printf("�����ʽ������ӿո�Ӳ�������ѡ����");
//		printf("��ʾ����   help ���� \n");
//		printf("չʾ�˵���������    show��ע��������С��50ʱĬ�ϲ�ɸѡ��ʾ�������ɸѡ��������ɸѡ������\n");
//		printf("�����˵�  add\n");
//		printf("ɾ���˵�  remove"
//				"�޸��˵�change "
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
//			std::cout<<"commond :"<<commond <<"��Ч��" << std::endl
//
//		}
//	}
//	static int addhelp(void)
//	{
//		printf("����˳��\n"
//			"����(yyyy-mm-dd) ʱ��(hh:mm) ���� ����/֧��(i/o) ���(��������С��������2.00) ����"
//			"ע�⣺������Ҫ���ո��������\n"
//			"��:add 2025-02-24 12:00 ����1dscripion Income 2.01 2");
//	}
//	static int changehelp(void)
//	{
//		printf("����˳��ID \n"
//			"����(yyyy-mm-dd) ʱ��(hh:mm) ���� ����/֧��(i/o) ���(��������С��������2.00) ����"
//			"ע�⣺������Ҫ���ո��������\n"
//			"��:change ID 2 2025-02-24 12:00 ����1dscripion Income 2.01 2");
//	}
//	static int removehelp(void)
//	{
//		printf("����˳��ID\n"
//			"��:remove 1");
//	}
//	static void showhelp(void)
//	{
//		printf("����˳��\n"
//			"-rest\n"
//			"����ָ����Χ���˵�\n"
//			"-data -year-month-day -time hh:mm:ss(Ĭ��ֵΪ23:59:59)\n"
//			"-kind numberָ�����\n"
//			"-id id1-id2,id3(not creat )\n"
//			"-all ��ʾȫ����ʹ�ô˲���ʱ������������ǰ���ѡ��\n");
//	}
//	static std::string commond;
//};
//static std::string commond;
//
//
//