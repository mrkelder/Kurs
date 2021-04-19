#include "desunit.h"

#include "baseunit.h"
// Обработка архива изделий и формирование отчетов
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    unsigned char Shop; //номер цеха
    int i = 0;
    int k = -1, m, np;
    int Kod; //код изделия
    char St[100];
    DynProduct* Lp, * Rp; // левый и правый указатели дека 
    DynProduct* Run; // текущий указатель дека архива 
    DynProduct* Runi;
    DynProduct* Runj;
    ProductType Product;
    if (!SignArchive) // архив не создан
    {
        printf("Архивный файл не создан. Режим отменяется");
        return;
    }
    ReadFileOut(&np, &Lp, &Rp); //формирование архивного дека

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // Сортировка по цене
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Price > Runj->Inf.Price) {
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }

    k = 0;
    Run = Lp;
        //печать заголовка таблицы
        WritelnString("                           ТАБЛИЦА ПРОДАННОГО ТОВАРА");
        WritelnString(
            " --------------------------------------------------------------------------------- ");
        WritelnString(
            "|  N  | Код       | Кол.     |   Цена   | Прибывшие   | Проданные   | На складе   |");
        WritelnString(
            "| п/п | товара    | товара   |          | за 24 часа  | за 24 часа  |             |");
        WritelnString(
            "|---------------------------------------------------------------------------------|");


        Run = Lp;
        while (Run != NULL) {
            i++;
            printf("|%3d.  %s  %4d %s     %6.2f        %6d        %6d        %6d |\n", i, Run->Inf.ActualKod, Run->Inf.Amount, Run->Inf.Dimens, Run->Inf.Price, Run->Inf.RecentlyArrived, Run->Inf.Sold, Run->Inf.Possess);
            Run = Run->Next;
        }
        WritelnString("|_________________________________________________________________________________|\n");
        Run = NULL;

    wait_press_key("\nДля продолжения нажмите любую клавишу\n\n");

    //печать заголовка таблицы
    WritelnString("                    5 ТОВАРОВ, КОТОРЫХ БОЛЬШЕ ВСЕГО НА СКЛАДЕ");
    WritelnString(
        " --------------------------------------------------------------------------------- ");
    WritelnString(
        "|  N  | Код       | Кол.     |   Цена   | Прибывшие   | Проданные   | На складе   |");
    WritelnString(
        "| п/п | товара    | товара   |          | за 24 часа  | за 24 часа  |             |");
    WritelnString(
        "|---------------------------------------------------------------------------------|");

    m = 0;
    k = -2;
    i = 0;

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // Сортировка по цене
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Possess > Runj->Inf.Possess) {
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }

    Run = Lp;
    while (Run != NULL) {
        i++;
        if (i > 5) break;
        printf("|%3d.  %s  %4d %s     %6.2f        %6d        %6d        %6d |\n", i, Run->Inf.ActualKod, Run->Inf.Amount, Run->Inf.Dimens, Run->Inf.Price, Run->Inf.RecentlyArrived, Run->Inf.Sold, Run->Inf.Possess);
        Run = Run->Next;
    }
    WritelnString("|_________________________________________________________________________________|\n");
    DisposeProduct(Lp, Rp); //удаление дека
    printf("\nОбработка архива закончена");

    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
} //-----------WorkUpArchive() 