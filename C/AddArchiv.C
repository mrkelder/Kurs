//Добавление компонент в архив изделий
#include "desunit.h"

#include "baseunit.h"

#include "CreateArchKodif.h"
 //-----------------------------------AddArchive()
//Добавление компонент в архив изделий
//Дек наращивается справа
int AddArchive() {
    ProductType Product;
    DynProduct* Run; // текущий указатель дека архива 
    DynProduct* Lp, * Rp; // левый и правый указатели дека 
    unsigned char Cond; // флаг 1-код найден в деке
    int Sr, np;
    if (SignArchive == 0) //архив не создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    //открывается файл "add.txt"
    if ((fAddTxt = fopen(fAddTxtName, "rt")) == NULL) {
        printf("\nФайл %s не найден. Режим отменяется.\n", fAddTxtName);
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        SignArchive = 0;
        return 1;
    }
    if (ReadFileOut(&np, &Lp, &Rp) == 1) //дек не создан 
    {
        fclose(fAddTxt);
        return 1;
    }
    do { //Создание структуры изделия из строки файла 
        if (ReadProduct(fAddTxt, &Product) == 0) {
            Sr = Product.ActualKod; //код добавляемого изделия
            Run = Lp; //начало просмотра слева
            Cond = 0; //флаг - код не найден
            while (Run != NULL) //поиск кода изделия в деке
            {
                if (Run->Inf.ActualKod == Sr) {
                    Cond = 1;
                    break;
                } //код изделия в деке найден
                Run = Run->Next;
            }
            if (Cond == 0) //код изделия в деке не найден
            { //выделение памяти для нового элемента дека
                Run = (DynProduct*)malloc(sizeof(DynProduct));
                Run->Inf = Product; //запись информационной части        
                //установка указателей для включения нового элемента в дек
                //Добавление компонент в Дек с правой стороны
                Run->Next = Lp;
                Lp = Run;
                Run = NULL;
            }
            else // (Cond == 1)
                printf("\nВ архиве уже есть изделие с кодом %6d", Sr);
        }
    } while (!feof(fAddTxt));
    fclose(fAddTxt);
    //Запись дека в архивный файл
    WriteFileOut(Lp, Rp);
    Lp = Rp = NULL;
    printf("\nДополнение архива закончено\n");
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
    return 0;
} //--------------AddArchive() 