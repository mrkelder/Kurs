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
    DynProduct* Beg; // левый и правый указатели стека (*Beg и есть сам стек)
    if (!SignArchive) //архив не создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    ReadFileOut(&np, &Beg); //Формирование архивного дека (чтение файла)
    //Сортировка дека по возрастанию "школьным" методом

    for (Runi = Beg; Runi != NULL; Runi = Runi->Next) // это сортировка школьным (не меняй)
        for (Runj = Beg; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Sold < Runj->Inf.Sold) { // strcmp(Runi->Inf.ActualKod, Runj->Inf.ActualKod) < 0
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }
    WriteFileOut(Beg); //запись дека в архивный файл
    Beg = NULL;
    printf("\nСортировка архива закончена.\n");
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
    return 0;
} //------SortArchive()