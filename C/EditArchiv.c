// Изменение компонента в архиве изделий
#include "desunit.h"
#include "baseunit.h"
// Формирование изменяемого компонента. 
void MakeComponent(ProductType *Product);

//-------------------------------------------ChangeArchive()
// Изменение компонента в архиве изделий 
// Просмотр дека слева направо
// Возвращает 1, если архив не создан, 0 - создан
int ChangeArchive()
{            
int Kod,Kod1,np;
unsigned char Cond=0;
ProductType Product;
DynProduct *Lp,*Rp;			// левый и правый указатели очереди 
DynProduct *Run;        // текущий указатель очереди архива 
  if ( ! SignArchive )	// архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
	//формирование архивного дека
	ReadFileOut(&np,&Lp,&Rp);
	//ввод кода изменяемого компонента
  printf("\nУкажите код изделия изменяемого компонента :");
	Kod=(int)ceil(GetNumber(0,999999,1,0,6,0));
  Kod1=Kod; printf("Kod = %6d",Kod1);
	Run=Lp; Cond=0;
  while (Run!=NULL) //цикл поиска введенного кода в деке
  {
		if (Kod==Run->Inf.Kod)
		{	//компонент найден
			Cond=1;
			//считывание текущих значений 
			Product=Run->Inf;
			printf("\n          Укажите следующие реквизиты :\n");
			printf("   ед.измерения  цена  план-1  план-2  факт-1  факт-2\n");
			MakeComponent(&Product);	//ввод изменений в полях
			Run->Inf=Product;		//запись измененной структуры в дек
			WriteFileOut(Lp,Rp);//запись дека в архивный файл
			Lp=Rp=NULL;
			printf("Изменение компонента в архиве закончено\n");
			break;
		} 
		Run=Run->Next;
	}
  if (! Cond )	//компонент не найден
    printf("\nВ архиве нет компонента с кодом %d\n",Kod1);
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}	//-----СhangeArchive() 
//--------------------------------------------MakeComponent()
// Формирование изменяемого компонента. Перед вводом новых
//значений на экране печатаются текущие значения полей.
//Изменять можно все значения, или любое их количество.
//Если нужно изменить значение в k-ом поле, необходимо ввести
//старые значения всех предшествующих полей. Если значения
//за k-ым полем не редактируются, их старые значения вводить
//не надо. Если с клавиатуры введено меньше шести значений,
//последние поля изменяться не будут.
void MakeComponent(ProductType *Product)
{                    
	int k=0;
	char Sa[80];
	char *token;
	char Seps[]=" \t\n";

	//печать на экран текущих значений
	printf("Тек.зн. %5s  %6.2f  %6.0f  %6.0f  %6.0f  %6.0f\n",
					Product->Dimens,Product->Price,Product->Plan[0],
					Product->Plan[1],Product->Fact[0],Product->Fact[1]);
	fflush(stdin);	//очистка буфера клавиатуры
	/*
		//очистка буфера клавиатуры(если fflush(stdin) не работает)
		rewind(stdin);
	*/	
	gets(Sa);				//считывание строки с клавиатуры
	token=strtok(Sa,Seps);	//Выделение первого слова
	while(token!=NULL)//цикл выделения слов из исходной строки
	{									// и запись значений в поля структуры
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
		token=strtok(NULL,Seps);	//Выделение очередного слова
	}
} //-----MakeComponent()
