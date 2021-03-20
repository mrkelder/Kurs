//������ �������� ��������� ����� ������� � ������� ������������,
//������ ������ �� ��������� ����� � ������������ �� �������
#include "desunit.h"
#include "baseunit.h"
//������ ����� "Kodif.txt" � ������������ ������� Kodifs 
void MakeKodifs(int *nk);
//����������� ������ �� ���������� ����� (input.txt ��� add.txt),
int ReadProduct(FILE *f,ProductType *Product);

//----------------------------------------CreateArchive()
//����������� ������ �������� �������� �� ���������� �����
//����������� �������� ���� ������. 
//�� ���������� ����� ����������� ����������� � ������������
//� ������. ������ ����������� � ����������� � ������
//�� �������� ����������. nk - ���������� ��������� � ������� 
void CreateArchive()
{
	ProductType Product;
	//����������� �������� ��������� ����
	if((fArTxt=fopen(fArTxtName,"rt"))==NULL)
		{
		 printf("\n���� %s �� ������\n",fArTxtName);
		 wait_press_key("\n��� ���������� ��������� ������� ����� �������\n");
		 exit(0);
		}
	//����������� �������� ���� ������
	if((fArBin=fopen(fArBinName,"wb"))==NULL)
		{
		 printf("\n���� %s �� ������\n",fArTxtName);
		 wait_press_key("\n��� ���������� ��������� ������� ����� �������\n");
		 exit(0);
		}
	do
	{ //������������ ��������� ������ ������� 
		if (ReadProduct(fArTxt,&Product)==0)
			//������ ��������� ������ ������� � �������� ����
			fwrite(&Product,sizeof(ProductType),1,fArBin);
	}
	while ( ! feof(fArTxt) );
	//����� �����������
	fclose(fArTxt); fArTxt=NULL;
	fclose(fArBin); fArBin=NULL;
	//������������ ������� ������������
	MakeKodifs(&nk);
	//���������� ������� ������������
	SortKodif(nk);
	//��������� ����� - ����� ������
	SignArchive=1;
	printf("\n	����� ������\n");
	wait_press_key("\n��� ����������� ������� ����� �������\n");

}	//-----CreateArchive()
//------------------------------------------ReadProduct()
//����������� ������ �� ���������� ����� (input.txt ��� add.txt),
//������������ �� ������ � ������������ ��������� Product. 
//���������� 0,���� ��������� ������������.
//���� ������ ����� ����� - ���������� 1
int ReadProduct(FILE *f,ProductType *Product)
{
	char sIn[80];		//������ �� �����
	int k;
	char *token;
	char Seps[]=" \t\n";
	if ( fgets(sIn, 80, f) != NULL )	//���������� ������
	{	
		k=0;
		token=strtok(sIn,Seps);	//��������� ������� �����
		while(token!=NULL)//���� ��������� ���� �� �������� ������
		{
			k++;                  //k-����� ���������� �����
			switch ( k )
			{	//���������� ����� ��������� �� ������ �����
				case 1:strcpy(Product->ActualKod, token); FillString(Product->ActualKod, 10, 1); break;
				case 2:sscanf_s(token,"%d",&Product->Amount); break;
				case 3:strcpy(Product->Dimens,token); FillString(Product->Dimens,5,1); break;
				case 4:sscanf_s(token,"%lf",&Product->Price); break;
				case 5:sscanf_s(token, "%d", &Product->RecentlyArrived); break;
				case 6:sscanf_s(token, "%d", &Product->Sold); break;
				case 7:sscanf_s(token, "%d", &Product->Possess); break;
			}
			token=strtok(NULL,Seps);	//��������� ���������� �����
		}
		return 0;		//Product �����������
	}
	else return 1;//������ ����� ����� 
}	//-----ReadProduct()
//---------------------------------------------PrintArchive()
//�� ��������� ����� ����������� ����� � ���������� �� ������, � ���� 
int PrintArchive()
{
	ProductType Product;
	int i;
	char s[100];
	if (SignArchive==0)//�������� ����� �������� ������
	{
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 0;
	}
	//����������� �������� �������� ����
	if((fArBin=fopen(fArBinName,"rb"))==NULL)
	{
		 printf("\n���� %s �� ������. ����� ����������.\n",fArBinName);
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 SignArchive=0;
		 return 0;
	}
	//������ ��������� ������
	WritelnString(
"\n                       ����� �������� � ������� ��������");
  WritelnString(
" --------------------------------------------------------------------------------- ");
  WritelnString(
"|  N  | ���       | ���.     |   ����   | ���������   | ���������   | �� ������   |");
  WritelnString(
"| �/� | ������    | ������   |          | �� 24 ����  | �� 24 ����  |             |");
  WritelnString(
"|---------------------------------------------------------------------------------|");

	i=0;
  while (fread(&Product,sizeof(ProductType),1,fArBin)==1)	//���� ������ �������� ��������� �����
  {	//������������ ������ s ��� ������
    i++; s[0]='|';s[1]='\0';
		sprintf(s,
			"|%3d.  %s  %4d %s     %6.2f        %6d        %6d        %6d |",
			i,Product.ActualKod,Product.Amount,Product.Dimens,
			Product.Price, Product.RecentlyArrived, Product.Sold, Product.Possess);
	  WritelnString(s);//������ ������
	}
	WritelnString(
"|_________________________________________________________________________________|\n");
 	fclose(fArBin);
	wait_press_key("\n��� ����������� ������� ����� �������\n");

	return 0;

}	//-----PrintArchive()
//-----------------------------------------------MakeKodifs()
//������ ����� "Kodif.txt" � ������������ ������� Kodifs 
//���������� ����� �������� ����� ������� nk
void MakeKodifs(int *nk)
{ 
	char Sa[80];
	int k;
	char *token;
	char Seps[]=" \t\n";
	//����������� ���� ������������ "Kodif.txt"
	if((fKodif=fopen(fKodifName,"rt"))==NULL)
	{
		 printf("\n���� %s �� ������\n",fArTxtName);
		 wait_press_key("\n��� ���������� ��������� ������� ����� �������\n");
		 exit(0);
	}
  
  *nk=0;	//����� �������
  while (fgets(Sa,80,fKodif)!=NULL) //������ "Kodif.txt"
	{
		k=0;
		token=strtok(Sa,Seps);	//��������� ������� �����
		while(token!=NULL)//���� ��������� ���� �� �������� ������
		{
			k++;
			switch ( k)
			{	//���������� ����� ��������� ������������
				case 1:strcpy(Kodif.ActualKod, token); break;
				case 2:strcpy(Kodif.Name,token); break;
				case 3:strcat(strcat(Kodif.Name," "),token); break;
			}
			token=strtok(NULL,Seps);	//��������� ���������� �����
		}
		FillString(Kodif.Name,35,1);//���������� ��������� ������
		Kodifs[*nk]=Kodif;//������ ��������� � ������
    (*nk)++;					//���������� ����� �������
	}
  fclose(fKodif);
}	//----- MakeKodifs() 
//-----------------------------------------------PrintKodif()
// ����� ������������ ������� �� �����, � ���� 
int PrintKodif(int nk)
{
	char s[80];
	unsigned char i,j=0;
  if (SignArchive==0)
	{
		 printf("\n����� �� ������. ����� ����������.\n");
		 wait_press_key("\n��� ����������� ������� ����� �������\n");
		 return 0;
	}
  WritelnString(
"\n                    ����������� �������");
  WritelnString(
" ------------------------------------------------------------- ");
  WritelnString(
"| N�/� |  ��� ������    |  ������������  ������               |");
  WritelnString(
"|-------------------------------------------------------------| ");
  j=0;
  for ( i=0; i<nk; i++ )
	{
		Kodif=Kodifs[i];
		j++; 
		sprintf(s,"|%4d.    %s      %s  |",j,Kodif.ActualKod,Kodif.Name);
		WritelnString(s);
	}
  WritelnString(
" ------------------------------------------------------------- ");
	wait_press_key("\n��� ����������� ������� ����� �������\n");
	return 0;
}	//-----PrintKodif() 
