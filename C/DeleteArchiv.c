//Удаление компонента из архива изделий
#include "desunit.h"
#include "baseunit.h"

//----------------------------------DeleteArchive()
//Удаление компонента из архива изделий. 
//Просмотр дека слева направо
int DeleteArchive()
{											
int Kod,KodPr;
unsigned char Cond;
DynProduct *Lp,*Rp;	// левый и правый указатели дека 
DynProduct  *Del;		// указатель на удаляемый элемент из дека
DynProduct  *Run;   // текущий указатель дека архива 
int np;
char Sr[80]="";
  if ( ! SignArchive ) //архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
  ReadFileOut(&np,&Lp,&Rp);//создается архивный дек
  //ввод кода удаляемого изделия
	printf("\nУкажите код удаляемого компонента : ");
  Kod=(int)ceil(GetNumber(0,999999,1,0,6,0));
	Cond=0; KodPr=Kod;
  //поиск введенного кода в деке
	if ( Kod == Lp->Inf.Kod)
	{		//удаляется крайний левый компонент 
		Cond=1;
		Del=Lp; Lp=Lp->Next; Lp->Prev=NULL;
		free(Del);
	}
  else
	{  //поиск введенного кода в средине дека
		 //просмотр с левой стороны
		Run=Lp->Next;
    while ( Run != NULL ) 
    {
      if ( Kod == Run->Inf.Kod )
			{	//в деке найден компонент с заданным кодом
				Cond=1;
				Del=Run;
				if (Run == Rp )//удаляется крайний правый компонент
					{Rp=Run->Prev; Rp->Next=NULL;}
				else	//удаляется компонент внутри дека
					{Run->Next->Prev=Run->Prev; Run->Prev->Next=Run->Next;}
				free(Del); //освобождение памяти
				break;
			}
			Run=Run->Next;
		}
	}
  if( Cond == 1 ) //компонент найден и удален
  {  
    np--;
    WriteFileOut(Lp,Rp);	//запись дека в бинарный файл
		Lp=Rp=NULL;
    printf("\nУдаление компонента из архива закончено");
	}
  else						//компонент не найден
	{
		DisposeProduct(Lp,Rp);
		Lp=Rp=NULL;
		printf("\nВ архиве нет компонента с кодом %6d",KodPr);
	}
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}  //------DeleteArchive()
