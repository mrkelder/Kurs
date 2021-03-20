//�������� �������� ��������� ������
#include "desunit.h"
#include "baseunit.h"
//-----------------------------------------------------------
//-----------------------����������� �����
//��� string80 - 
//    ������ ���� char [80] 
typedef char string80[80];	        	//������ �� 80 ��������
//��� FileStringAr - 
//    ������ ����� ������ ���� string80 �������� PMax
typedef string80 FileStringAr[PMax];	//������ ����� ������
//��� FileStringArPtr -
//    ��������� �� ������������ ������ ����� 
//    ��� ���������� �������� ������ �� ����� fArTxt
typedef FileStringAr *FileStringArPtr;
//��� ProductAr - 
//    ������ �������� ������ ���� ProductType �������� PMax
typedef ProductType  ProductAr[PMax]; 
//��� ProductArPtr - 
//    ��������� �� ������������ ������ ProductAr �������� ������
typedef ProductAr *ProductArPtr;

//-----------------------����������� ���������� ���������� 
FILE *FileError;          // ���� ��������� ��������
char *FileErrorName="Error.dat";
int const  NfMax = PMax; // ����.���-�� ����� � ��������� ����� 
int 
	 np,              // ���-�� ����� � ����� "input.txt"
   nd,              // ���-�� ����� � ����� "add.txt"
   nk,				      // ���-�� ����� � ����� "kodif.txt"
   FatalError;      // ������� ������ � �������� ������

string80	Sr;				// ��������� �� ������
FileStringArPtr Sf; // ��������c��� ������ ����� ���������� �����
//--------------------------------------------------
//�������� ��������� ������
void CheckFiles();
//�������� �������� ������ "input.txt" � "add.txt"
void FormatFileProduct(FILE *F, char *FileName, int *nf,
												int Nmax, ProductAr *Prod);
//�������� �������� ����� "Kodif.txt"
void FormatFileKodif();
//�������� ������� ���������� �����, �������� ����������
//�����, � �������� ������ ����� 
void ReadAndCheckSpaces(FILE *F, char *FileName, int *nf,
												int Nmax);
//�������� ���������� ���������� � "input.txt" � "add.txt"
void CheckProdDiapason(char *FileName, int nf, ProductAr *Prod);
//�������� ���������� ���������� � "Kodif.txt" 
void CheckKodifDiapason();
//�������� ������������ ��������� Kod � ����� "Kodif.txt"
void KodifParameters();
//�������� ���������� ������� � ������ "input.txt" � "add.txt"
void ProdParameters(ProductAr *Prod, int n, char *FileName);
//������������ � ������ � ���� ��������� �� ������ ���������� int
void ReportError1(char *FileName, int i, int k, int d1,int d2);
//������������ � ������ � ���� ��������� �� ������ 
//���������� double
void ReportError2(char *FileName, int i, int k, 
									double d1, double d2);
//������ � ����� �� ����� ��������� �������� ��������� ������ 
void ReadFileError();
