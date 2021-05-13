//Удаление компонента из архива изделий
#include "desunit.h"
#include <string.h>
#include "baseunit.h"

//----------------------------------DeleteArchive()
//Удаление компонента из архива изделий. 
//Просмотр дека слева направо
int DeleteArchive() {
    char Kod[11], KodPr[11];
    unsigned char Cond;
    DynProduct* Lp, * Rp; // левый и правый указатели дека 
    DynProduct* Del; // указатель на удаляемый элемент из дека
    DynProduct* Run; // текущий указатель дека архива 
    DynProduct* TempRun; // предыдущий элемент до удоляемого
    int np;
    char Sr[80] = "";
    if (!SignArchive) //архив не создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    ReadFileOut(&np, &Lp, &Rp); //создается архивный дек
    //ввод кода удаляемого изделия
    printf("\nУкажите код удаляемого компонента: ");
    scanf("%s", &Kod);
    Cond = 0;
    strncpy(KodPr, Kod, 10);
    //поиск введенного кода в деке
    if (strcmp(Kod, Lp->Inf.ActualKod) == 0) { //удаляется крайний левый компонент 
        Cond = 1;
        Del = Lp;
        Lp = Lp->Next;
        free(Del);
    }
    else { //поиск введенного кода в средине дека
   //просмотр с левой стороны
        Run = Lp;
        while (Run != NULL) {
            if (strcmp(Kod, Run->Inf.ActualKod) == 0) { //удаляется крайний левый компонент 
                Cond = 1;
                Del = Run;
                TempRun->Next = Run->Next;
                free(Del);
                break;
            }
           TempRun = Run;
           Run = Run->Next;
        }
        Run = NULL;
    }
    if (Cond == 1) //компонент найден и удален
    {
        np--;
        WriteFileOut(Lp, Rp); //запись дека в бинарный файл
        Lp = Rp = NULL;
        printf("\nУдаление компонента из архива закончено");
    }
    else //компонент не найден
    {
        DisposeProduct(Lp, Rp);
        Lp = Rp = NULL;
        printf("\nВ архиве нет компонента с кодом %s", KodPr);
    }
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
    return 0;
} //------DeleteArchive()