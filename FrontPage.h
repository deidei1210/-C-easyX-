#pragma once
#define DarkBlue RGB(54, 46, 61)
#define NormalBlue RGB(80,100,120)
#define LightBlue RGB(197,213,237)
void StartPage();                                                   //��ʼ����
char* wideCharToMultiByte(wchar_t* pWCStrKey);//���ַ�ת�����ַ���
string LoadFilePage();                                     //������Ҫ������ļ�����
int menu();                                                     //�˵�����
int ToContinue();                                            //������������
void EncodePage();                                        //�����չʾ�������ݵĽ���
void End();                                                      //������������
void ReturnButtum(int x1, int y1, int x2, int y2);//�����ء���ť���
string MakeFilePage();                                      //����������ļ�����
void SuccessPage();                                          //�ļ�����ɹ�����
int DecodeChoice();                                          //ѡ������ʱ������뷽ʽ�Ľ���
string InputBox(int choice, int y);                      //�ı��򲿼����
void ShowContent(string content, int y);          //չʾ����������