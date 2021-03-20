//������� ��������� - ���� ������ ������
#include "desunit.h"
#include "baseunit.h"
#include "CreateArchKodif.h"
#include "SortArchiv.h"
#include "AddArchiv.h"
#include "DeleteArchiv.h"
#include "EditArchiv.h"
#include "ReportArchiv.h"

extern void CheckFiles();
//------------------------------------------main()
int main()
{	
	int KeyRegime;									// ���� ������ ������ ������
	//����������� ���������
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);      
	//������ ���������� ��� ������ �������
	UsesDevice();
  if (Device==1)	//������ �� ����� � � ����
		//����������� ��������� ���� "res.txt" ��� ������ �������
		if((fRes=fopen(fResName,"wt"))==NULL)
		{	
		 printf("\n���� %s �� ������\n",fResName);
		 wait_press_key("\n��� ���������� ��������� ������� ����� �������\n");
		 exit(0);
		}
	SignArchive=0;//���� - ����� �� ������
  do
	{	//����� ���� �� �����
    printf("\n      ������� ����� ������ ���������:");
    printf("\n      0 - ����� ������;");
    printf("\n      1 - �������� ��������� ������;");
    printf("\n      2 - �������� ������ �������;");//!
    printf("\n      3 - ���������� ��������� ������;");//!
    printf("\n      4 - ������ ������ �������;");//!
    printf("\n      5 - ������ ������������ �������;");//!
    printf("\n      6 - ���������� ��������� � �����;");//!
    printf("\n      7 - �������� ���������� �� ������;");//!
    printf("\n      8 - ��������� ���������� � ������;");
    printf("\n      9 - ��������� ������ \n");
		//������� ������ ���������� � ���� ������
		fflush(stdin);
	  KeyRegime=(int)ceil(GetNumber(0,9,1,0,1,0));
		switch (KeyRegime) 
    {	//����� ������� � ������������ � ������� ���������
			case 0 : ;		              break;
			case 1 : CheckFiles();			break;
			case 2 : CreateArchive();   break;
			case 3 : SortArchive();			break;
			case 4 : PrintArchive();    break;
			case 5 : PrintKodif(nk);		break;
			case 6 : AddArchive();			break;
			case 7 : DeleteArchive();		break;
			case 8 : ChangeArchive();		break;
			case 9 : WorkUpArchive();		break;
		}
	} 
	while (KeyRegime!=0);	//����� 0 - ����� �� ���������
  if (Device==1)
    fclose(fRes);	//����������� ���� �����������

	wait_press_key("\n	�����");
	return 0;
}	//-----main()

