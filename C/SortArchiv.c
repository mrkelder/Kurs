//Сортировка архива
#include "desunit.h"
#include "baseunit.h"
//---------------------------------------------SortArchive()
//Сортировка архива по возрастанию кода изделия. Просмотр дека 
//с левой стороны и сортировка "школьным" методом по возрастанию
int SortArchive()
{							
int np;
ProductType Product;
DynProduct *Runi;
DynProduct *Runj;				// текущие указатели дека архива 
DynProduct *Lp,*Rp;			// левый и правый указатели дека (очереди или стека)
  if ( ! SignArchive )	//архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
	ReadFileOut(&np,&Lp,&Rp);	//Формирование архивного дека (чтение файла)
	//Сортировка дека по возрастанию "школьным" методом

	for ( Runi=Lp; Runi!=NULL; Runi=Runi->Next ) // это сортировка школьным (не меняй)
		for ( Runj=Lp; Runj!=NULL; Runj=Runj->Next )
			if ( Runi->Inf.Kod < Runj->Inf.Kod )
			{
        Product=Runi->Inf; 
				Runi->Inf=Runj->Inf;
        Runj->Inf=Product;
			}

	WriteFileOut(Lp,Rp);	//запись дека в архивный файл
	Lp=Rp=NULL;
	printf("\nСортировка архива закончена.\n");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}	//------SortArchive()
