//���������� ������
#include "desunit.h"
#include "baseunit.h"
//---------------------------------------------SortArchive()
//���������� ������ �� ����������� ���� �������. �������� ���� 
//� ����� ������� � ���������� "��������" ������� �� �����������
int SortArchive()
{							
int np;
ProductType Product;
DynProduct *Runi;
DynProduct *Runj;				// ������� ��������� ���� ������ 
DynProduct *Lp,*Rp;			// ����� � ������ ��������� ���� (������� ��� �����)
  if ( ! SignArchive )	//����� �� ������
  {
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 1;
	}
	ReadFileOut(&np,&Lp,&Rp);	//������������ ��������� ���� (������ �����)
	//���������� ���� �� ����������� "��������" �������

	for ( Runi=Lp; Runi!=NULL; Runi=Runi->Next ) // ��� ���������� �������� (�� �����)
		for ( Runj=Lp; Runj!=NULL; Runj=Runj->Next )
			if ( Runi->Inf.Kod < Runj->Inf.Kod )
			{
        Product=Runi->Inf; 
				Runi->Inf=Runj->Inf;
        Runj->Inf=Product;
			}

	WriteFileOut(Lp,Rp);	//������ ���� � �������� ����
	Lp=Rp=NULL;
	printf("\n���������� ������ ���������.\n");
	wait_press_key("\n��� ����������� ������� ����� �������\n");
	return 0;
}	//------SortArchive()
