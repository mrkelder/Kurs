// ��������� ���������� � ������ �������
#include "desunit.h"
#include "baseunit.h"
// ������������ ����������� ����������. 
void MakeComponent(ProductType *Product);

//-------------------------------------------ChangeArchive()
// ��������� ���������� � ������ ������� 
// �������� ���� ����� �������
// ���������� 1, ���� ����� �� ������, 0 - ������
int ChangeArchive()
{            
int Kod,Kod1,np;
unsigned char Cond=0;
ProductType Product;
DynProduct *Lp,*Rp;			// ����� � ������ ��������� ������� 
DynProduct *Run;        // ������� ��������� ������� ������ 
  if ( ! SignArchive )	// ����� �� ������
  {
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 1;
	}
	//������������ ��������� ����
	ReadFileOut(&np,&Lp,&Rp);
	//���� ���� ����������� ����������
  printf("\n������� ��� ������� ����������� ���������� :");
	Kod=(int)ceil(GetNumber(0,999999,1,0,6,0));
  Kod1=Kod; printf("Kod = %6d",Kod1);
	Run=Lp; Cond=0;
  while (Run!=NULL) //���� ������ ���������� ���� � ����
  {
		if (Kod==Run->Inf.Kod)
		{	//��������� ������
			Cond=1;
			//���������� ������� �������� 
			Product=Run->Inf;
			printf("\n          ������� ��������� ��������� :\n");
			printf("   ��.���������  ����  ����-1  ����-2  ����-1  ����-2\n");
			MakeComponent(&Product);	//���� ��������� � �����
			Run->Inf=Product;		//������ ���������� ��������� � ���
			WriteFileOut(Lp,Rp);//������ ���� � �������� ����
			Lp=Rp=NULL;
			printf("��������� ���������� � ������ ���������\n");
			break;
		} 
		Run=Run->Next;
	}
  if (! Cond )	//��������� �� ������
    printf("\n� ������ ��� ���������� � ����� %d\n",Kod1);
	wait_press_key("\n��� ����������� ������� ����� �������\n");
	return 0;
}	//-----�hangeArchive() 
//--------------------------------------------MakeComponent()
// ������������ ����������� ����������. ����� ������ �����
//�������� �� ������ ���������� ������� �������� �����.
//�������� ����� ��� ��������, ��� ����� �� ����������.
//���� ����� �������� �������� � k-�� ����, ���������� ������
//������ �������� ���� �������������� �����. ���� ��������
//�� k-�� ����� �� �������������, �� ������ �������� �������
//�� ����. ���� � ���������� ������� ������ ����� ��������,
//��������� ���� ���������� �� �����.
void MakeComponent(ProductType *Product)
{                    
	int k=0;
	char Sa[80];
	char *token;
	char Seps[]=" \t\n";

	//������ �� ����� ������� ��������
	printf("���.��. %5s  %6.2f  %6.0f  %6.0f  %6.0f  %6.0f\n",
					Product->Dimens,Product->Price,Product->Plan[0],
					Product->Plan[1],Product->Fact[0],Product->Fact[1]);
	fflush(stdin);	//������� ������ ����������
	/*
		//������� ������ ����������(���� fflush(stdin) �� ��������)
		rewind(stdin);
	*/	
	gets(Sa);				//���������� ������ � ����������
	token=strtok(Sa,Seps);	//��������� ������� �����
	while(token!=NULL)//���� ��������� ���� �� �������� ������
	{									// � ������ �������� � ���� ���������
		k++;
		switch ( k )
		{
		 case 1:strcpy(Product->Dimens,token);
								FillString(Product->Dimens,5,1);			break;
		 case 2:sscanf_s(token,"%lf",&Product->Price);		break;
		 case 3:sscanf_s(token,"%lf",&Product->Plan[0]);	break;
		 case 4:sscanf_s(token,"%lf",&Product->Plan[1]);	break;
		 case 5:sscanf_s(token,"%lf",&Product->Fact[0]);	break;
		 case 6:sscanf_s(token,"%lf",&Product->Fact[1]);	break;
		}
		token=strtok(NULL,Seps);	//��������� ���������� �����
	}
} //-----MakeComponent()
