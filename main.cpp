#include<iostream>
#include<easyx.h>
#include <conio.h>	 
#include"class.h"
#include"FrontPage.h"
using namespace std;
int ct = 0;
int main()
{
	System sys;
	//��ʼ����
	StartPage();
	string filename = "";
	while (1) {
		//ѡ��Ҫ�򿪵��ļ�
	    filename = LoadFilePage();
		if (sys.File_read(filename))   //��ȡָ���ļ�
			break;
	}
	sys.Initial();  //�����������ɳɹ�
	sys.Encode();//��ÿһ���ַ���ʼ����
    
	int d = 1;
	while (d == 1) {
		//ѡ��Ҫ���еĲ���
		int choice = menu();

		if (choice == 1) {
			//һ��ʹ��������ܣ��ȳ�ʼ������
			EncodePage();			//����������������
			sys.OutPut_Code();   //�������
			ReturnButtum(700, 750, 780, 790);//���ذ�ť
		}
		else if (choice == 2) {   //��ָ���ļ��øոյõ����ַ��������
			string file=MakeFilePage();
			cout << file << endl;
			sys.Make_HuffFile(filename, file);
			SuccessPage();
			//ReturnButtum(300, 350, 380, 390);
		}
		else if (choice == 3) {
			sys.OutPut_Tree();
			//draw_main(root);					//����ͼ�λ�������
			ReturnButtum(5, 55, 85, 95);
		}
		else if (choice == 4) {  //ѡ���ѡ���ʾ��Ҫ����
			int c=DecodeChoice();  //��ѡ��Ľ���
			//�ֶ����������ļ�
			if (c == 1) {
				//�ȴ�ӡÿ�����ʶ�Ӧ������
				EncodePage();			//����������������
				sys.OutPut_Code(0);   //���ÿ���ַ���Ӧ�ı�������
				//�����������������
				string content=InputBox(1, 55 + (ct / 3 + 2) * 25);
				string name2 = InputBox(3, 55 + (ct / 3 + 7) * 25);//Ҫ������ļ���
				//��ʾ����������
				string result = sys.Decode(content, name2, 2);
				ShowContent(result, 55 + (ct / 3 + 11) * 25);
				ReturnButtum(700, 750, 780, 790);//���ذ�ť
			}
			//�����ļ�����
			else if (c == 2) {
				EncodePage();			//����������������
				sys.OutPut_Code(0);   //���ÿ���ַ���Ӧ�ı�������
				string address1=InputBox(2, 55 + (ct / 3 + 2) * 25);//Ҫ������ļ���ַ
				string name2= InputBox(3, 55 + (ct / 3 + 7) * 25);//Ҫ������ļ���
				//��ʾ����������
				string result=sys.Decode(address1, name2,1);
				ShowContent(result, 55 + (ct / 3 + 11) * 25);
				ReturnButtum(700, 750, 780, 790);//���ذ�ť
			}

		}
		else if (choice == 5) {//���¶����ļ�
			sys.Clear();//��֮ǰ�Ĺ��������������
			while (1) {
				//ѡ��Ҫ�򿪵��ļ�
				filename = LoadFilePage();
				if (sys.File_read(filename))   //��ȡָ���ļ�
					break;
			}
			sys.Initial();  //�����������ɳɹ�
			sys.Encode();//��ÿһ���ַ���ʼ����
		}
		else if (choice == 0) {
			break;
		}
		else {
			outtextxy(35, 330, _T("û����Ҫִ�е�ѡ����������룡"));
			Sleep(2000);
			continue;
		}
		d = ToContinue();
     }
	End();
	closegraph();
	return 0;
}

