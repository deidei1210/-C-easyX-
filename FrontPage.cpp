#include"class.h"
#include"FrontPage.h"
#include<iostream>
using namespace std;

EasyTextBox txtName;
EasyTextBox Choice;
extern int ct;
//��Ҫ����ʹ����char*��delete[]�ͷ��ڴ�
char* wideCharToMultiByte(wchar_t* pWCStrKey){
	//��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	//�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	return pCStrKey;

	//�����Ҫת����string��ֱ�Ӹ�ֵ����
	//string pKey = pCStrKey;
}

//�ʼ�Ľ���
void StartPage() {
	initgraph(400, 400);
	//���ñ�����ɫΪ��ɫ
	setbkcolor(WHITE);
	cleardevice();

	// ��ô��ھ��
	HWND hWnd = GetHWnd();
	// ʹ�� Windows API �޸Ĵ�������
	SetWindowText(hWnd, _T("����������������"));

	//�����ƴ�ӡ������
	settextcolor(DarkBlue);
	settextstyle(35, 0, _T("����"));
	outtextxy(60, 130, _T("����������������"));

	//������������
	setfillcolor(DarkBlue);
	solidrectangle(0, 0, 400, 45);
	setfillcolor(NormalBlue);
	solidrectangle(0, 45, 400, 75);
	setfillcolor(LightBlue);
	solidrectangle(0, 75, 400, 90);

	//��ʼ��ť
	setlinecolor(DarkBlue);
	rectangle(150, 200, 250, 250);
	setlinecolor(DarkBlue);
	rectangle(155, 205, 245, 245);
	settextcolor(DarkBlue);
	settextstyle(20, 0, _T("����"));
	outtextxy(176, 215, _T("Start"));

	IMAGE img;
	putimage(255, 255, &img);

	MOUSEMSG mouse;//���һ������������Ϣ

	while (1) {
		mouse = GetMouseMsg();//��ù���������Ϣ
		if (mouse.x >= 155 && mouse.x <= 245 && mouse.y >= 205 && mouse.y <= 245) {
			setfillcolor(NormalBlue);
			solidrectangle(155, 205, 245, 245);
			settextcolor(LightBlue);
			settextstyle(20, 0, _T("����"));
			setbkmode(TRANSPARENT);
			outtextxy(176, 215, _T("Start"));
			//��굥������Ƭ����
			if (mouse.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else {
			setfillcolor(WHITE);
			solidrectangle(155, 205, 245, 245);
			setlinecolor(DarkBlue);
			rectangle(155, 205, 245, 245);
			settextcolor(DarkBlue);
			settextstyle(20, 0, _T("����"));
			outtextxy(176, 215, _T("Start"));
		}
	}
}
//��ѡ����Ҫ��ȡ���ļ�
string LoadFilePage() {
	//���ǵ����ļ�ҳ
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(40, 7, _T("��ӭ����������������������"));
	settextstyle(19, 0, _T("����"));
	outtextxy(50, 150, _T("��������Ҫ������ļ��ĵ�ַ��"));
	setlinecolor(DarkBlue);

	settextcolor(BLACK);
	outtextxy(10, 190, L"��ַ��");
	txtName.Create(50, 190, 380, 220, 1000);						// �����û����ı���ؼ�
	EasyButton btnOK;
	btnOK.Create(350, 225, 390, 245, L"OK");	// ������ť�ؼ�

	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (txtName.Check(msg.x, msg.y))
				txtName.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}

	outtextxy(300, 155, txtName.Text());
	string filename = wideCharToMultiByte(txtName.Text());
	return filename;
}
//��ʾ�˵�
int menu() {
	//��ʾ�˵�
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(180, 7, _T("�˵�"));

	settextstyle(18, 0, _T("����"));
	outtextxy(35, 45, _T("��ʾÿ���ַ��Ļ���������---�밴1"));
	outtextxy(35, 70, _T("��ñ����ļ�---�밴2"));
	outtextxy(35, 95, _T("��ʾ��������---�밴3"));
	outtextxy(35, 120, _T("����������---�밴4"));
	outtextxy(35, 145, _T("���¶�����Ҫ������ļ�---�밴5"));
	outtextxy(35, 170, _T("�˳�---�밴0"));
	outtextxy(35, 195, _T("��������Ҫ���еĲ�����"));
	//outtextxy(300, 155, txtName.Text());
	Choice.Create(230, 195, 260, 215, 10);
	EasyButton btnOK;
	btnOK.Create(350, 300, 390, 325, L"OK");	// ������ť�ؼ�

	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (Choice.Check(msg.x, msg.y))
				Choice.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(Choice.Text());
	if (c.length() > 1)
		return 9;
	int num = c[0] - '0';
	return num;
}
//�Ƿ����
int ToContinue() {
	closegraph();
	initgraph(400, 400);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(30, 0, L"����");
	outtextxy(50, 100, L"�Ƿ������һ��������");
	EasyButton Yes, No;
	Yes.Create(120, 210, 180, 245, L"Yes");
	No.Create(200, 210, 260, 245, L"No");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (No.Check(msg.x, msg.y)) {
				return -1;
			}
			if (Yes.Check(msg.x, msg.y)) {
				return 1;
			}
		}
	}
	return 0;
}
//�������������
void EncodePage() {
	closegraph();
	initgraph(800, 800);
	setbkcolor(WHITE);
	cleardevice();
	//����
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(330, 7, _T("�����������"));
	//�ָ���
	setlinecolor(DarkBlue);
	line(267, 40, 267, 800);
	line(534, 40, 534, 800);
	//��ͷ
	settextcolor(DarkBlue);
	settextstyle(20, 0, _T("����"));
	for (int i = 0; i < 3; i++) {
		outtextxy(5 + i * 267, 40, _T("�ַ�"));
		outtextxy(100 + i * 267, 40, L"����");
	}

}
//��������
void End() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(100, 100, _T("��л����ʹ�ã�:)"));
	Sleep(1000);
	outtextxy(160, 130, _T("�ټ���"));
	Sleep(3000);
}
//����
void ReturnButtum(int x1,int y1,int x2,int y2) {
	EasyButton Ret;
	Ret.Create(x1,y1,x2,y2, L"����");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (Ret.Check(msg.x, msg.y))
				break;
		}
	}

}
//��������������ļ��ĺ���
string MakeFilePage() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(30, 100, L"������������ļ�����");
	EasyTextBox name;
	EasyButton btnOK;
	name.Create(150, 150, 250, 180,100);
	btnOK.Create(270, 230, 320, 260,L"OK");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (name.Check(msg.x, msg.y))
				name.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(name.Text());
	return c;
}
//��������ļ��ɹ���Ľ���
void SuccessPage() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(100, 100, L"�ļ��������:)");
	Sleep(2000);
}
//���뷽ʽѡ�����
int DecodeChoice() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("����"));
	outtextxy(10, 100, L"��ѡ����Ҫ������ļ������뷽ʽ��:)");
	EasyButton Hand, Read;
	Hand.Create(60, 200, 180, 230, L"�ֶ�����");
	Read.Create(210, 200, 330, 230, L"��ȡ�ļ�");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (Hand.Check(msg.x, msg.y))
				return 1;
			if (Read.Check(msg.x, msg.y))
				return 2;
		}
	}
	return 0;
}
//�������������
string InputBox(int choice,int y ) {
	//��һ���ܴ�İ�ɫ����
	setfillcolor(WHITE);
	solidrectangle(0, y, 800, 800);
	if(choice==1)
	    outtextxy(5, y, L"������Ҫ��������ݣ�");
	else if(choice==2)
		outtextxy(5, y, L"������Ҫ������ļ���ַ��");
	else if(choice==3)
		outtextxy(5, y, L"������Ҫ�����������ļ����ƣ�");

	//���������
	EasyTextBox Put;
	EasyButton Ok;
	Put.Create(5, y+25, 795, y + 50, 1000);
	Ok.Create(650, y+75, 700, y + 100, L"OK");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// ��ȡ��Ϣ����

		if (msg.message == WM_LBUTTONDOWN) {
			// �жϿؼ�
			if (Put.Check(msg.x, msg.y))
				Put.OnMessage();
			else if (Ok.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(Put.Text());
	//��ס�����ʹ����������ֱ����ʾ����
	setfillcolor(WHITE);
	solidrectangle(5, y+25, 795, y+50);
	for (int j = 0; c[j] != '\0'; j++) {
		outtextxy(5 + j * 10 ,  y+25, c[j]);
	}

	return c;
}
//չʾ����������
void ShowContent(string content,int y) {
	outtextxy(5, y, L"����������Ϊ��");
	//int i = 0;
	for (int j = 0; content[j] != '\0'; j++) {
		outtextxy(20 + 10 * (j % 70), y + 25 + 25 *(j / 70), content[j]);
	}
}
