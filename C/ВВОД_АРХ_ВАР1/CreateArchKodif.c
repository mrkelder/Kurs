#include "CreateArchKodif.h"
//---------------------------------------------
//Считывается строка из указанного файла, производится ее разбор
//и формирование структуры Product. Возвращает 0
//Если найден конец файла - возвращает 1
int ReadProduct(FILE *f,ProductType *Product)
{
	char sIn[80];  double rr;
	char slovo[30];
	unsigned char Cond=0;
	int k1,k2,k,i,n;
	if ( fgets(sIn, 80, f) != NULL )
	{	
		k=strlen(sIn);
		if (sIn[k-1]==10) sIn[k-1]='\0';
		i=0; k=0; Cond=1; k2=-1;
//for (i=0;i<14;i++) sIn[i]=' ';
sscanf_s(sIn,"%d%d%4s%lf",&i,&k,slovo,4,&rr);
sscanf_s(sIn,"%d%d%4s%lf",&i,&k,Product->Dimens,4,&rr);
/*sscanf_s(sIn,"%d",&i);
sscanf_s(sIn,"%4s",slovo,4);
sscanf_s(sIn,"%4s",Product->Dimens,4);
*/
sscanf_s(sIn,"%d%d%4s%lf%lf%lf%lf%lf",
	&Product->NumberShop,&Product->Kod,
	Product->Dimens,4,&Product->Price,
	&Product->Plan[0],&Product->Plan[1],		
	&Product->Fact[0],&Product->Fact[1]);		
FillString(Product->Dimens,5,1);					
	
		return 0;
	}
	else return 1;
}
//-----------------------------------------------
//Считываются строки описания продукта из текстового файла
//Формируется бинарный файл архива. Из текстового файла считывается
//кодификатор и записывается в массив. Массив сортируется и сохраняется
//до закрытия приложения. nk - количество элементов в массиве 
void CreateArchive()
{
	ProductType Product;

	if((fArTxt=fopen(fArTxtName,"rt"))==NULL)
		{
		 printf("\nФаил %s не найден\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
		}
	if((fArBin=fopen(fArBinName,"wb"))==NULL)
		{
		 printf("\nФаил %s не создан\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
		}
	do
	{  
		if (ReadProduct(fArTxt,&Product)==0)
			fwrite(&Product,sizeof(ProductType),1,fArBin);
	}
	while ( ! feof(fArTxt) );
	fclose(fArTxt);
	fclose(fArBin);
	MakeKodifs(&nk);
	SortKodif(nk);

	SignArchive=1;
	printf("\n	Архив создан\n");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");

}
//-----------------------------------------------
//Из бинарного файла считывается архив и печатается на экране, в файл 
int PrintArchive()
{
	ProductType Product;
	int i,p=1;
	char s[80];
	char slovo[80]="";
	if (SignArchive==0)
	{
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 0;
	}
	if((fArBin=fopen(fArBinName,"rb"))==NULL)
	{
		 printf("\nФаил %s не найден. Режим отменяется.\n",fArBinName);
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 SignArchive=0;
		 return 0;
	}

	WritelnString("\n              АРХИВ СВЕДЕНИЙ О ВЫПУСКАЕМОЙ ПРОДУКЦИИ");
  WritelnString(" --------------------------------------------------------------- ");
  WritelnString("| N  | N  |  Код  | Ед. |       |  План выпуска |  Факт.выпуск  |");
  WritelnString("|п/п |цеха|изделия| изм.| Цена  |---------------|---------------|");
  WritelnString("|    |    |       |     |       |   1   |   2   |   1   |   2   |");
  WritelnString("|---------------------------------------------------------------|");

	i=0;
	if( p=fread(&Product,sizeof(ProductType),1,fArBin)<1) p=EOF;
  while (p!=EOF)
    {
      i++; s[0]='|';s[1]='\0';
			sprintf(slovo,"%3d",i);strcat(s,slovo);strcat(s,". ");

			sprintf(slovo,"%3d",Product.NumberShop);strcat(s,slovo);strcat(s,"   ");	
			sprintf(slovo,"%6d",Product.Kod);strcat(s,slovo);strcat(s," ");	
			strcat(s,Product.Dimens);strcat(s,"   ");	
			sprintf(slovo,"%6.2f",Product.Price);strcat(s,slovo);strcat(s,  "  ");	
			sprintf(slovo,"%6.0f",Product.Plan[0]);strcat(s,slovo);strcat(s,"  ");	
			sprintf(slovo,"%6.0f",Product.Plan[1]);strcat(s,slovo);strcat(s,"  ");	
			sprintf(slovo,"%6.0f",Product.Fact[0]);strcat(s,slovo);strcat(s,"  ");	
			sprintf(slovo,"%6.0f",Product.Fact[1]);strcat(s,slovo);strcat(s,"|");	
		  WritelnString(s);
			if( p=fread(&Product,sizeof(ProductType),1,fArBin)<1) p=EOF;
		}
		WritelnString("|_______________________________________________________________|\n");
  	fclose(fArBin);
		wait_press_key("\nДля продолжения нажмите любую клавишу\n");

	return 0;

}
//-----------------------------------------------
// Чтение файла "Kodif.txt" и формирование массива Kodifs 
void MakeKodifs(int *nk)
{ 
	char Sa[80],Sb[80];
	unsigned char  n,k,Cond;
	int k1,k2;

	if((fKodif=fopen(fKodifName,"rt"))==NULL)
		{
		 printf("\nФаил %s не найден\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
		}
  
  *nk=0;
  while (fgets(Sa,80,fKodif)!=NULL) 
	{
		n=strlen(Sa);
		if (Sa[n-1]==10) 	Sa[n-1]='\0'; 
		Cond=1; k2=-1; k=0;
    while (Cond) 
			{
				k1=NotSpace(Sa,k2+1);
				if (k1==-1) Cond=0;
				else
				{
					k2=Space(Sa,k1+1);
					if (k2==-1) { k2=strlen(Sa); Cond=0; }
					k++;
					n=k2-k1;
					strncpy(Sb,&Sa[k1],n);//копируем текущее слово в Sb
					Sb[n]='\0';            //и добавляем символ '\0'.
					switch ( k)
					{
						case 1:sscanf_s(Sb,"%d",&Kodif.Kod);	break;
						case 2:strncpy(Kodif.Name,&Sb[0],n);  
									Kodif.Name[n]=' '; Kodif.Name[n+1]='\0'; break;
						case 3:strcat(Kodif.Name,Sb); break;
					}
				}
			}
			k=strlen(Kodif.Name);
			if ( Kodif.Name[k-1]==10 ) Kodif.Name[k-1]='\0';
			FillString(Kodif.Name,35,1);
			Kodifs[*nk]=Kodif;
      (*nk)++;
	}
  fclose(fKodif);
}								// MakeKodifs 
//-----------------------------------------------
// Вывод кодификатора изделий на экран, в файл 
int PrintKodif(int nk)
{
	char s[80];
	char slovo[80]="";
	unsigned char i,j=0;
  if (SignArchive==0)
	{
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 0;
	}
  WritelnString("\n                КОДИФИКАТОР ВЫПУСКАЕМОЙ ПРОДУКЦИИ");
  WritelnString(" ---------------------------------------------------------------- ");
  WritelnString("| Nп/п |   Код изделия  |    Наименование  изделия               |");
  WritelnString(" ---------------------------------------------------------------- ");
  j=0;
  for ( i=0; i<nk; i++ )
	{
		Kodif=Kodifs[i];
      j++; s[0]='|';s[1]='\0';
			sprintf(slovo,"%4d",j);strcat(s,slovo);strcat(s,".       ");
			sprintf(slovo,"%6d",Kodif.Kod);strcat(s,slovo);strcat(s,"          ");	
			strcat(s,Kodif.Name);
			strcat(s,"  |");	
		  WritelnString(s);
	}
  WritelnString(" ---------------------------------------------------------------- ");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}     //PrintKodif 
//-----------------------------------------------
