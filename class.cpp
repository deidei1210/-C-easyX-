#include<iostream>
#include<fstream>
#include<string>
#include"class.h"
#include"huff.h"
#include"FrontPage.h"
#define ROOT_TAG '^'
const char SNAME[] = "data.txt";
using namespace std;

extern int ct;
int dis = 0;
int ch_n = 0;  //��¼�����˶��ٸ���ͬ���ַ�
//System���ڲ�����
int System::File_read(string filename)     //�ǲ��ǿ���ֱ�����öѽ��й���
{
	//cerr << "�������ļ��� : ";
	int count[ENG_LEN] = { 0 };         //����ͳ��ÿһ���ַ��������г��ֵĴ���
	//char filename[NAME_LEN];         //�ļ���
	ifstream ifs(filename, ios::in);
	ch_n = 0;
	if (!ifs.is_open()) {
		cleardevice();
		settextcolor(DarkBlue);
		settextstyle(20, 0, _T("����"));
		outtextxy(50, 100, L"�ļ������ڣ������������ļ����ƣ�:(");
		Sleep(2000);

		cerr << "�����ļ�" << filename << "��ʧ��" << endl;
		return 0;
	}
	else {                      //����ļ��򿪳ɹ�
		char ch;
		while ((ch = ifs.get()) != EOF) {             //ͳ��ÿһ���ַ�һ���ж��ٸ�
			if (ch >= 'a' && ch <= 'z')
				count[(ch - 'a')]++;
			else if (ch >= 'A' && ch <= 'Z')
				count[(ch - 'A') + 26]++;
			else if (ch == ' ')
				count[54]++;        //�ո����ĩβ���⴦��
			else if (ch == ',')
				count[52]++;
			else if (ch == '.')
				count[53]++;
			else if (ch == '?')
				count[55]++;
			else if (ch == '-')
				count[56]++;
		}
	}
	ifs.close();

	//�½�һ��data�ļ�����֮ǰ����ÿ�����ų��ֵ�Ƶ�ζ������
	ofstream ost(SNAME, ios::out);
	if (!ost.is_open()) {
		cerr << "����ļ�" << SNAME << "��ʧ��" << endl;
		return 0;
	}
	else {
		for (int i = 0; i < 26; ++i) {
			if (count[i] != 0) {//�����˾�д��data��
				ost << char('a' + i) << " " << count[i] << endl;
				ch_n++;
			}
		}
		for (int i = 0; i < 26; ++i) {
			if (count[i + 26] != 0) {
				ost << char('A' + i) << " " << count[i + 26] << endl;
				ch_n++;
			}
		}
		if (count[52] != 0) {
			ost << ',' << " " << count[52] << endl;
			ch_n++;
		}
		if (count[53] != 0) {
			ost << '.' << " " << count[53] << endl;
			ch_n++;
		}
		if (count[55] != 0) {
			ost << '?' << " " << count[55] << endl;
			ch_n++;
		}
		if (count[56] != 0) {
			ost << "-" << " " << count[56] << endl;
			ch_n++;
		}
		if (count[54] != 0) {
			ost << ' ' << " " << count[54] << endl;
			ch_n++;
		}
	}
	ost.close();
	return 1;
}
void System::Initial(){
	MinHeap M_Heap;
	M_Heap.creat_mheap(ch_n);
	HuffmanTree H1, H2, Put;      //�ֱ�ȡ��С��Ԫ��,�ϲ����Ԫ�����·ŵ�����
	while (!M_Heap.Isempty()){
		M_Heap.Delete(H1);
		M_Heap.Delete(H2);
		Put = *(Sys_Tree.Creat_Tree(H1, H2));
		if (Put.Get_root() != NULL && !M_Heap.Isempty())
			M_Heap.Insert(Put);
	}
	//�������ʱ��H_Tree��M_Heap��һ���ظ��ͷŵ�����
	H1.Reset_root();
	H2.Reset_root();
	Put.Reset_root();
	//�������û�����⣬˵���Ƕѵ��ͷų�������
	//�ѿռ��ͷŵ����˹�����������������
}
void System::OutPut_Tree(){  //��������
	//Sys_Tree.PreOrder(Sys_Tree.Get_root()); 
	//���л�ͼ���ڳ�ʼ��
	closegraph();                      //�ص�ǰ��Ļ�ͼ����
	initgraph(1920, 1080);			// ������ͼ����
	setbkcolor(WHITE);			// ���ñ��������ɫ
	cleardevice();						//�������
	setcolor(BLACK);

	dis = 0;
	//���û�������
	Sys_Tree.DrawTree(Sys_Tree.Get_root(), 600, 5);

}
void System::Encode()
{
	Sys_Tree.PreOrder(Sys_Tree.Get_root());
}
void System::OutPut_Code(int stop){
	ct = 0;
	Sys_Tree.Outputcode(Sys_Tree.Get_root(),stop);
	outtextxy(5 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, L"��ʾ��ϣ�");
}
int System::Make_HuffFile(string filename,string HuffFile) {

	ifstream ifs(filename, ios::in);
	ofstream ofs(HuffFile, ios::out);
	if (!ifs.is_open()) {
		cerr << "�����ļ�" << filename << "��ʧ��" << endl;
		return -1;
	}
	else {                      //����ļ��򿪳ɹ�
		char ch;
		while ((ch = ifs.get()) != EOF) {             
			string code="";
			Sys_Tree.SearchCode(Sys_Tree.Get_root(), ch, code);
			ofs << code;    //�����������ofs��
			//cout << code;
		 }
	}
	ifs.close();
	ofs.close();
	return 1;
}
string System::Decode(string ifile,string ofile,int choice)        //���н���
{
	string Result;
	if (choice == 1) {
		ifstream ifs(ifile, ios::in);
		if (!ifs.is_open()) {
			cerr << "�����ļ�" << ifile << "��ʧ��" << endl;
			return " ";
		}
		else {
			Node* root = Sys_Tree.Get_root();
			Node* p = root;
			char ch;
			while ((ch = ifs.get()) != EOF) {
				if (ch == '0')
					p = p->left_child;
				else
					p = p->right_child;
				if (p->left_child == NULL && p->right_child == NULL) {
					Result += p->Name;
					p = root;
				}
			}
		}
		ifs.close();
	}
	else if (choice == 2) {//��ʱ��Ӧ�ø���ifile�ַ��������ݽ��н��룬�����
		Node* root = Sys_Tree.Get_root();
		Node* p = root;
		char ch;
		for(int i=0;ifile[i]!='\0';i++){
			ch = ifile[i];
			if (ch == '0')
				p = p->left_child;
			else
				p = p->right_child;
			if (p!=NULL&&p->left_child == NULL && p->right_child == NULL) {
				Result += p->Name;
				p = root;
			}
		}
	}
	ofstream ofs(ofile, ios::out);
	if (ofs.is_open())
		ofs << Result;
	else{
		cerr << "�����ļ�" << ofile << "��ʧ��" << endl;
		return " ";
	}
	ofs.close();
	return Result;
}
void System::Clear(){
	Sys_Tree.clear();
}

//���������ڲ�����
HuffmanTree::HuffmanTree(){
	root = new Node;
};       //Ĭ�Ϲ��캯��
HuffmanTree::HuffmanTree(int data, char ch){
	root = new Node(data, ch);
}    //���ι��캯��
HuffmanTree::HuffmanTree(HuffmanTree& R){
	*this = R;
}
HuffmanTree::~HuffmanTree(){
	delete root;              //�����⣬�ظ��ͷţ�
	root = NULL;
}
Node* HuffmanTree::Get_root(){
	return this->root;
}	            //���ؽڵ�ֵ
void HuffmanTree::Reset_root(){
	this->root = NULL;
}
bool HuffmanTree::Is_Empty(){
	return root == NULL;
}
void HuffmanTree::PreOrder(Node* p, const int choice){
	static string s;
	if (p != NULL){
		s += '0';
		//if (choice != 0)
			cout << p->Name << "  " << p->Data << endl;
		PreOrder(p->left_child);
		s.pop_back();
		s += '1';
		PreOrder(p->right_child);
		s.pop_back();
		p->Code = s;
	}
}           //ǰ��ݹ��¼����
HuffmanTree& HuffmanTree::operator=(const HuffmanTree& R)
{
	this->root = R.root;
	return *this;
}
bool HuffmanTree::operator>(const HuffmanTree& R)
{
	return this->root->Data > R.root->Data;
}
bool HuffmanTree::operator<(const HuffmanTree& R)
{
	return this->root->Data < R.root->Data;
}
void HuffmanTree::Outputcode(Node* p,int stop){
	settextstyle(18, 0, _T("����"));
	if (p == NULL)
		return;
	else{
		//��Ҷ�ӽڵ�
		if (p->left_child == NULL && p->right_child == NULL){
			//��취�����������ͼ������
			outtextxy(5 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, p->Name);
			//cout << p->Name;
			if(stop)
			    Sleep(100);
			//printf("%c ", p->info);
			for (int j = 0; p->Code[j] != '\0'; j++) {
				outtextxy(100 + j * 10 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, p->Code[j]);
				if(stop)
				    Sleep(10);
			}
			ct++;
		}
		else{
			Outputcode(p->left_child,stop);
			Outputcode(p->right_child,stop);
		}
	}
}
HuffmanTree* HuffmanTree::Creat_Tree(HuffmanTree& H1, HuffmanTree& H2)  //����Huffman��
{
	if (H1.Get_root() != NULL && H2.Get_root() != NULL){
		HuffmanTree* p = new HuffmanTree(H1.Get_root()->Data + H2.Get_root()->Data, ROOT_TAG);
		this->root = p->Get_root();       //
		root->left_child = H1.Get_root();
		root->right_child = H2.Get_root();
		return p;
	}
	else    //˵��ֻ��һ��ľͷ
		return NULL;
}
void HuffmanTree::DrawTree(Node* p, int x, int y) {

	//�ȱ���������������ߵ�
	if (p->left_child != NULL) {
		//�Ȼ��ߣ����������˵����߶��������
		int x1 = x,y1=y,x2,y2;                 //�ߵ����
		if (dis != 2) {
			x2 = x - 200 + dis * 30;
			y2 = y + 50;//�ߵ��յ�
		}
		else {
			x2 = x - 140;
			y2 = y + 50;//�ߵ��յ�
		}
		setlinecolor(BLACK);
		line(x1, y1, x2 , y2);              //����  
		outtextxy((x1+x2)/2, (y1+y2)/2, '0');  //��ע��һ������'0'
		//outtextxy(x2, y2, p->Name);//��ע����ڵ������
		cout << p->Name;
		Sleep(200);
		dis++;
		DrawTree(p->left_child, x2, y2);
		dis--;
	}

	//Ȼ����������������ұߵ�
	if (p->right_child != NULL) {
		//�Ȼ��ߣ����������˵����߶��������
		int x1 = x, y1 = y, x2, y2;                 //�ߵ����
		if (dis != 2) {
			x2 = x + 200 - dis * 30;
			y2 = y + 50;//�ߵ��յ�
		}
		else {
			x2 = x + 140;
			y2 = y + 50;//�ߵ��յ�
		}	
		setlinecolor(RED);
		line(x1, y1, x2, y2);              //����  
		outtextxy((x1 + x2) / 2, (y1 + y2) / 2, '1');  //��ע��һ������'1'
		//outtextxy(x2, y2, p->Name);//��ע����ڵ������
		cout << p->Name;
		Sleep(200);
		dis++;
		DrawTree(p->right_child, x2, y2);
		dis--;
	}

	if (p->left_child == NULL && p->right_child == NULL) {
		settextstyle(18, 0, _T("����"));
		outtextxy(x, y, p->Name);//��ע����ڵ������
		cout << dis << p->Name << endl;
	}
}
void HuffmanTree::SearchCode(Node* p, char c, string& a,int flag) {  //����ָ���ַ��Ĺ���������
	Node* s[1000], * m;
	int top = 0;
	s[top] = p;

	while (top >= 0){
		// ��Ԫ�ص�ջɸ�Ƚϼ򵥣�����ֱ����������¶�
		m = s[top--];
		//cout << m->Name << "     " << c << endl;
		if (m->Name == c) {
			a = m->Code;
			break;
		}
		// ����Ҫ�ݹ��ջɸ��ջ
		if (m->right_child)
			s[++top] = m->right_child;
		if (m->left_child)
			s[++top] = m->left_child;
	}
}
void HuffmanTree::PreDelete(Node* p)  //�ݹ�������
{
	if (p == NULL)
		return;
	else{
		PreDelete(p->left_child);
		PreDelete(p->right_child);
		delete p;
		p = NULL;
	}
}
void HuffmanTree::clear()         //�������
{
	PreDelete(root);
	root = new Node;
}

//��С���㷨�ڲ�����
MinHeap::MinHeap(int sz)
{
	CurrentSize = sz;
	MaxSize = sz * 2 - 1;
	heap = new HuffmanTree[MaxSize];
}
void MinHeap::creat_mheap(int Number){
	ifstream ifs(SNAME, ios::in);
	CurrentSize = Number;
	MaxSize = Number * 2 - 1;
	heap = new HuffmanTree[MaxSize];
	if (!ifs.is_open()){
		cout << "�ļ�" << SNAME << "��ʧ�ܣ�" << endl;
		return;
	}
	else{
		int i = 0;
		//�ո��ȡ������,��Խ��
		for (; i < Number - 1; ++i)
			ifs >> heap[i].Get_root()->Name >> heap[i].Get_root()->Data;   //��ȡȨ�ع�����
		ifs.get();
		heap[Number - 1].Get_root()->Name = char(ifs.get());
		ifs.get();
		heap[Number - 1].Get_root()->Data = ifs.get();
		int Pa = (CurrentSize - 2) / 2;
		while (Pa >= 0){
			DownSift(Pa);
			Pa--;
		}
	}
	ifs.close();
}
bool MinHeap::Insert(HuffmanTree& x)
{
	if (Isfull())
		return false;
	else{
		heap[CurrentSize++] = x;
		UpSift(CurrentSize - 1);
	}
	return true;
}
bool MinHeap::Delete(HuffmanTree& N)   //Ĭ��ɾ����һ��Ԫ��
{
	if (!Isempty())
	{
		N = heap[0];
		heap[0] = heap[--CurrentSize];
		DownSift(0);
		heap[CurrentSize].Reset_root();     //ʹԭ����ָ��NULL,�����ظ��ͷ�
		return true;
	}
	return false;
}
void MinHeap::DownSift(int start)   //���µ���
{
	int i = start, child = 2 * i + 1;
	HuffmanTree temp = heap[i];
	while (child <= CurrentSize - 1)
	{
		if (child<CurrentSize - 1 && heap[child] > heap[child + 1])
			++child;
		if (temp > heap[child])
		{
			heap[i] = heap[child];
			i = child;
			child = 2 * i + 1;
		}
		else
			break;
	}
	heap[i] = temp;
	temp.Reset_root();        //����ֲ��������ͷ����⣬����temp����ʱ�����heap[i]���ڴ�
}
void MinHeap::UpSift(int start)     //���ϵ���
{
	int i = start, Parent = (i - 1) / 2;  //Insertʱ��i����Currentsize��
	HuffmanTree tmp = heap[i];             //���������������
	while (i > 0)        //parent>=0����ѭ��
	{
		if (tmp < heap[Parent])
		{
			heap[i] = heap[Parent];
			i = Parent;
			Parent = (i - 1) / 2;
		}
		else
			break;
	}
	heap[i] = tmp;
	tmp.Reset_root();        //�ֲ��������ý��������
}
void MinHeap::Print()
{
	for (int i = 0; i < this->CurrentSize; ++i)
		cout << heap[i].Get_root()->Name << "*" << heap[i].Get_root()->Data << endl;
	cout << endl;
}
