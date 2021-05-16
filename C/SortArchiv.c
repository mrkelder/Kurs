//Сортировка архива
#include "desunit.h"
#include <stdio.h>
#include <string.h>
#include "baseunit.h"
 //---------------------------------------------SortArchive()
// Сортировка происходит от товара с наименьшим количеством продаж до товара с наибольшим количеством продаж
int SortArchive() {
    int np;
    ProductType Product;
    DynProduct* Runi;
    DynProduct* Runj; // текущие указатели дека архива 
    DynProduct* Lp; // левый и правый указатели стека (*Lp и есть сам стек)
    if (!SignArchive) //архив не создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    ReadFileOut(&np, &Lp); //Формирование архивного дека (чтение файла)
    //Сортировка дека по возрастанию "школьным" методом

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // это сортировка школьным (не меняй)
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Sold < Runj->Inf.Sold) { // strcmp(Runi->Inf.ActualKod, Runj->Inf.ActualKod) < 0
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }
    WriteFileOut(Lp); //запись дека в архивный файл
    Lp = NULL;
    printf("\nСортировка архива закончена.\n");
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
    return 0;
} //------SortArchive()