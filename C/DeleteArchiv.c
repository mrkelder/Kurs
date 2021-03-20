//�������� ���������� �� ������ �������
#include "desunit.h"
#include "baseunit.h"

//----------------------------------DeleteArchive()
//�������� ���������� �� ������ �������. 
//�������� ���� ����� �������
int DeleteArchive()
{											
int Kod,KodPr;
unsigned char Cond;
DynProduct *Lp,*Rp;	// ����� � ������ ��������� ���� 
DynProduct  *Del;		// ��������� �� ��������� ������� �� ����
DynProduct  *Run;   // ������� ��������� ���� ������ 
int np;
char Sr[80]="";
  if ( ! SignArchive ) //����� �� ������
  {
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 1;
	}
  ReadFileOut(&np,&Lp,&Rp);//��������� �������� ���
  //���� ���� ���������� �������
	printf("\n������� ��� ���������� ���������� : ");
  Kod=(int)ceil(GetNumber(0,999999,1,0,6,0));
	Cond=0; KodPr=Kod;
  //����� ���������� ���� � ����
	if ( Kod == Lp->Inf.Kod)
	{		//��������� ������� ����� ��������� 
		Cond=1;
		Del=Lp; Lp=Lp->Next; Lp->Prev=NULL;
		free(Del);
	}
  else
	{  //����� ���������� ���� � ������� ����
		 //�������� � ����� �������
		Run=Lp->Next;
    while ( Run != NULL ) 
    {
      if ( Kod == Run->Inf.Kod )
			{	//� ���� ������ ��������� � �������� �����
				Cond=1;
				Del=Run;
				if (Run == Rp )//��������� ������� ������ ���������
					{Rp=Run->Prev; Rp->Next=NULL;}
				else	//��������� ��������� ������ ����
					{Run->Next->Prev=Run->Prev; Run->Prev->Next=Run->Next;}
				free(Del); //������������ ������
				break;
			}
			Run=Run->Next;
		}
	}
  if( Cond == 1 ) //��������� ������ � ������
  {  
    np--;
    WriteFileOut(Lp,Rp);	//������ ���� � �������� ����
		Lp=Rp=NULL;
    printf("\n�������� ���������� �� ������ ���������");
	}
  else						//��������� �� ������
	{
		DisposeProduct(Lp,Rp);
		Lp=Rp=NULL;
		printf("\n� ������ ��� ���������� � ����� %6d",KodPr);
	}
	wait_press_key("\n��� ����������� ������� ����� �������\n");
	return 0;
}  //------DeleteArchive()
