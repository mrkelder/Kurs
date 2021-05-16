#pragma once
//��������� ��������� � ������������ �������� (4996)
#pragma warning (disable: 4996)
//#define _CRT_SECURE_NO_WARNINGS
//���������� �������� ��������, ����� � ����������
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>

//����� ������ �������
#define fArTxtName "input.txt" //��� ����� �������� ����������
#define fAddTxtName  "add.txt" //��� ����� ����������� ����������
#define fKodifName "kodif.txt" //��� ����� ������������ �������
#define fArBinName "arhiv.bin" //��� ��������� ����� �������
#define fResName     "res.txt" //��� ����� ����������� ��������

//�������� ���������� �������
FILE *fArTxt;		//���� �������� ����������
FILE *fArBin;		//�������� ���� �������
FILE *fAddTxt;		//���� ����������� ����������
FILE *fKodif;		//���� ������������ �������
FILE *fRes;			//���� ����������� ��������

typedef struct ProductT  // ��� ���������� ������ ������� 
	{			
	char ActualKod[10];	 // ��� ������� 
	int Amount;          // ���������� ����
	char Dimens[5];      // ������� ��������� (��.)
	double Price;        // ���� �������
	int RecentlyArrived; // ��������� ������� �� ��������� 24 ����
	int Sold;            // ��������� �� ��������� 24 ����
	int Possess;         // �� ������
	} ProductType;		 //������� ���� ���������� ������ �������

typedef struct KodifTyp //��� ���������� ������������ ������� 
	{				
	char ActualKod[10]; // ��� �������
	char Name[100];		// ������������ ������� 
	int Kod;
	} KodifType;	    //������� ���� ���������� ������������ �������

typedef struct DynProd		  //��� �������� ���� 
	{							
		ProductType  Inf;	  //�������������� �����
		struct DynProd* Next; //��������� �� ��������� �������
	} DynProduct;		      //������� ���� �������� ����

#define KMax 100		//����.���-�� ����������� ������������ 
#define PMax 200		//����.���-�� ����������� ������ ������� 

KodifType	 Kodif,     //��������� ������������
		Kodifs[KMax];   //������ ����������� ������������

unsigned char SignArchive;  //���� �������� ������
int nk;					            //���-�� ����������� ������������ 

//���������� ������ �����������:
// 0 - �����; 1 - ����� � ����; 
int Device;		
