#include "desunit.h"

#include "baseunit.h"
// Обработка архива изделий и формирование отчетов
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    int i = 0, j = 0;
    int np;
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

    Run = Lp;
    //печать заголовка таблицы
    WritelnString("                                          ТАБЛИЦА ПРОДАННОГО ТОВАРА");
    WritelnString(" -------------------------------------------------------------------------------------------------------- ");
    WritelnString("|  N  | Название                         | Кол.     |   Цена   | Прибывшие   | Проданные   | На складе   |");
    WritelnString("| п/п | товара                           | товара   |          | за 24 часа  | за 24 часа  |             |");
    WritelnString("|--------------------------------------------------------------------------------------------------------|");

    Run = Lp;
    while (Run != NULL) {
        char tempName[100]; // Временная переменная для хранения имен
        i++;
        for (i = 0; i < nk; i++) {
            Kodif = Kodifs[i];
            if (strcmp(Kodif.ActualKod, Run->Inf.ActualKod) == 0) {
                strcpy(tempName, Kodif.Name);
                break;
            }
        }
        printf("|%3d.  %s %4d %s     %6.2f        %6d        %6d        %6d |\n", i, tempName, Run->Inf.Amount, Run->Inf.Dimens, Run->Inf.Price, Run->Inf.RecentlyArrived, Run->Inf.Sold, Run->Inf.Possess);
        Run = Run->Next;
    }
    WritelnString("|________________________________________________________________________________________________________|\n");
    Run = NULL;

    wait_press_key("\nДля продолжения нажмите любую клавишу\n\n");

    //печать заголовка таблицы
    WritelnString("                                  5 ТОВАРОВ, КОТОРЫХ БОЛЬШЕ ВСЕГО НА СКЛАДЕ");
    WritelnString(" -------------------------------------------------------------------------------------------------------- ");
    WritelnString("|  N  | Название                         | Кол.     |   Цена   | Прибывшие   | Проданные   | На складе   |");
    WritelnString("| п/п | товара                           | товара   |          | за 24 часа  | за 24 часа  |             |");
    WritelnString("|--------------------------------------------------------------------------------------------------------|");

    i = 0;
    // Сортировка по цене
    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) 
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Possess > Runj->Inf.Possess) {
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }

    // Вывод 5 эл-тов
    Run = Lp;
    while (Run != NULL) {
        i++;
        if (i > 5) break;
        char tempName[100]; // Временная переменная для хранения имен
        for (j = 0; j < nk; j++) {
            Kodif = Kodifs[j];
            if (strcmp(Kodif.ActualKod, Run->Inf.ActualKod) == 0) {
                strcpy(tempName, Kodif.Name);
                break;
            }
        }
        printf("|%3d.  %s %4d %s     %6.2f        %6d        %6d        %6d |\n", i, tempName, Run->Inf.Amount, Run->Inf.Dimens, Run->Inf.Price, Run->Inf.RecentlyArrived, Run->Inf.Sold, Run->Inf.Possess);
        Run = Run->Next;
    }
    WritelnString("|________________________________________________________________________________________________________|\n");
    DisposeProduct(Lp, Rp); //удаление дека
    printf("\nОбработка архива закончена");

    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
} //-----------WorkUpArchive() 