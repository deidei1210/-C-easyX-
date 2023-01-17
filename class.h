#pragma once
#include <graphics.h>
#include<conio.h>
#include<fstream>
#include<iostream>
#include"huff.h"
#define NAME_LEN 64  //�ļ�����󳤶�
#define ENG_LEN 60   //Ŀǰ����Ϊ��Сд��ĸ+, . �Ϳո�


using namespace std;
// ʵ���ı���ؼ�
class EasyTextBox;
// ʵ�ְ�ť�ؼ�
class EasyButton;

// ʵ���ı���ؼ�
class EasyTextBox{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// �ؼ�����
	wchar_t* text = NULL;							// �ؼ�����
	size_t maxlen = 0;									// �ı���������ݳ���

public:
	void Create(int x1, int y1, int x2, int y2, int max){
		maxlen = max;
		text = new wchar_t[maxlen];
		text[0] = 0;
		left = x1, top = y1, right = x2, bottom = y2;

		// �����û�����
		Show();
	}
	~EasyTextBox()
	{
		if (text != NULL)
			delete[] text;
	}
	wchar_t* Text(){
		return text;
	}
	bool Check(int x, int y){
		return (left <= x && x <= right && top <= y && y <= bottom);
	}
	// ���ƽ���
	void Show(){
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(LIGHTGRAY);		// ���û�����ɫ
		setbkcolor(0xeeeeee);			// ���ñ�����ɫ
		setfillcolor(0xeeeeee);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}
	void OnMessage()
	{
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		int width = textwidth(text);	// �ַ����ܿ��
		int counter = 0;				// �����˸������
		bool binput = true;				// �Ƿ�������

		ExMessage msg;
		while (binput){
			while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false))	// ��ȡ��Ϣ����������Ϣ�����ó�
			{
				if (msg.message == WM_LBUTTONDOWN)	{
					// ���������ı������棬�����ı�����
					if (msg.x < left || msg.x > right || msg.y < top || msg.y > bottom){
						binput = false;
						break;
					}
				}
				else if (msg.message == WM_CHAR){
					size_t len = wcslen(text);
					switch (msg.ch){
						case '\b':				// �û����˸����ɾ��һ���ַ�
							if (len > 0){
								text[len - 1] = 0;
								width = textwidth(text);
								counter = 0;
								clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
							}
							break;
						case '\r':				// �û����س����������ı�����
						case '\n':
							binput = false;
							break;
						default:				// �û����������������ı�����
							if (len < maxlen - 1){
								text[len++] = msg.ch;
								text[len] = 0;
								clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// ������Ĺ��
								width = textwidth(text);				// ���¼����ı�����
								counter = 0;
								outtextxy(left + 10, top + 5, text);		// ����µ��ַ���
							}
					}
				}
				peekmessage(NULL, EM_MOUSE | EM_CHAR);				// ����Ϣ���������ոմ������һ����Ϣ
			}

			// ���ƹ�꣨�����˸����Ϊ 20ms * 32��
			counter = (counter + 1) % 32;
			if (counter < 16)
				line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// �����
			else
				clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// �����

			// ��ʱ 20ms
			Sleep(20);
		}

		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);

		Show();
	}
};

// ʵ�ְ�ť�ؼ�
class EasyButton{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// �ؼ�����
	wchar_t* text = NULL;							// �ؼ�����
	void (*userfunc)() = NULL;						// �ؼ���Ϣ

public:
	void Create(int x1, int y1, int x2, int y2, const wchar_t* title, void (*func)()){
		text = new wchar_t[wcslen(title) + 1];
		wcscpy_s(text, wcslen(title) + 1, title);
		left = x1, top = y1, right = x2, bottom = y2;
		userfunc = func;

		// �����û�����
		Show();
	}
	void Create(int x1, int y1, int x2, int y2, const wchar_t* title) {
		text = new wchar_t[wcslen(title) + 1];
		wcscpy_s(text, wcslen(title) + 1, title);
		left = x1, top = y1, right = x2, bottom = y2;
		userfunc = NULL;
		// �����û�����
		Show();

	}
	~EasyButton()
	{
		if (text != NULL)
			delete[] text;
	}
	bool Check(int x, int y){
		return (left <= x && x <= right && top <= y && y <= bottom);
	}
	// ���ƽ���
	void Show(){
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + (right - left - textwidth(text) + 1) / 2, top + (bottom - top - textheight(text) + 1) / 2, text);

		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}
	void OnMessage()
	{
		if (userfunc != NULL)
			userfunc();
	}
};

//�ܵ�ϵͳ��
class System{
public:
	int File_read(string filename);
	void Initial();
	void OutPut_Tree();
	void Encode();     //Ҫ�ܹ���¼�ͱ�����ʵ�ֿ��Կ�����ǰ������ķ���
	void OutPut_Code(int stop=1);  //�������
	int Make_HuffFile(string filename,string HuffFile); //����ȡ���ļ����ջ������������ʽ���
	string Decode(string ifile, string ofile,int choice);  //���ڽ���
	void Clear();
private:
	HuffmanTree Sys_Tree;         //ϵͳ�Ĺ�������
};
