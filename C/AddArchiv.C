
//���������� ��������� � ����� �������
#include "desunit.h"
#include "baseunit.h"
#include "CreateArchKodif.h"
//-----------------------------------AddArchive()
//���������� ��������� � ����� �������
//��� ������������ ������
int AddArchive()
{                      
ProductType Product;
DynProduct *Run;			// ������� ��������� ���� ������ 
DynProduct *Lp,*Rp;		// ����� � ������ ��������� ���� 
unsigned char Cond;		// ���� 1-��� ������ � ����
int Sr, np;
	if (SignArchive==0)	//����� �� ������
	{
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 1;
	}
	//����������� ���� "add.txt"
	if((fAddTxt=fopen(fAddTxtName,"rt"))==NULL)
	{
		 printf("\n���� %s �� ������. ����� ����������.\n",fAddTxtName);
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 SignArchive=0;
		 return 1;
	}
	if ( ReadFileOut(&np,&Lp,&Rp) == 1) //��� �� ������ 
			{ fclose(fAddTxt); return 1; }
	do
	{ //�������� ��������� ������� �� ������ ����� 
		if (ReadProduct(fAddTxt, &Product)==0)
		{	
			Sr=Product.Kod;	  //��� ������������ �������
			Run=Lp;           //������ ��������� �����
			Cond=0;	          //���� - ��� �� ������
      while (Run!=NULL) //����� ���� ������� � ����
			{
				if (Run->Inf.Kod==Sr) 
					{ Cond=1; break; }	//��� ������� � ���� ������
        Run=Run->Next;
			}
      if (Cond == 0 ) //��� ������� � ���� �� ������
			{	//��������� ������ ��� ������ �������� ����
  			Run=(DynProduct *)malloc(sizeof(DynProduct));
	      Run->Inf=Product; //������ �������������� �����        
				//��������� ���������� ��� ��������� ������ �������� � ���
				//���������� ��������� � ��� � ������ �������
				Run->Next=NULL;
				if (Lp==NULL)
					{	Lp=Run;	Run->Prev=NULL; }	
				else
					{ Rp->Next=Run; Run->Prev=Rp; }
				Rp=Run;
			}
      else  // (Cond == 1)
        printf("\n� ������ ��� ���� ������� � ����� %6d",Sr);
		}
	}
	while ( ! feof(fAddTxt) );
	fclose(fAddTxt);
	//������ ���� � �������� ����
  WriteFileOut(Lp,Rp);
	Lp=Rp=NULL;
  printf("\n���������� ������ ���������\n");
	wait_press_key("\n��� ����������� ������� ����� �������\n");
	return 0;
}	//--------------AddArchive() 