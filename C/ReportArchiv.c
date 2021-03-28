#include "desunit.h"

#include "baseunit.h"
// Обработка архива изделий и формирование отчетов
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    unsigned char Shop; //номер цеха
    int k = -1, m, np;
    int Kod; //код изделия
    double PlanSt1, PlanSt2, PlanGod, //суммарные плановые показатели
        FactSt1, FactSt2, FactGod, //суммарные фактические показатели
        ProcSt1, ProcSt2, ProcGod, //процент выполнения плана
        BufSt; //буферная переменная
    char St[80];
    DynProduct* Lp, * Rp; // левый и правый указатели дека 
    DynProduct* Run; // текущий указатель дека архива 
    if (!SignArchive) // архив не создан
    {
        printf("Архивный файл не создан. Режим отменяется");
        return;
    }
    ReadFileOut(&np, &Lp, &Rp); //формирование архивного дека
    printf("\nУкажите номер цеха  "); //ввод номера цеха
    Shop = (unsigned char)ceil(GetNumber(1, 99, 1, 0, 2, 0));

    //ПЕЧАТЬ СВЕДЕНИй О ВЫПОЛНЕНИИ ПЛАНА ПО ЦЕХУ
    PlanSt1 = 0;
    PlanSt2 = 0;
    FactSt1 = 0;
    FactSt2 = 0;
    k = 0;
    Run = Lp;
    while (Run != NULL) { //поиск сведений по заданному цеху
        if (Shop == Run->Inf.NumberShop) { //Подсчет плановых и фактических показателей по цеху
            k++;
            BufSt = Run->Inf.Plan[0] * Run->Inf.Price;
            PlanSt1 += BufSt;
            BufSt = Run->Inf.Plan[1] * Run->Inf.Price;
            PlanSt2 += BufSt;
            BufSt = Run->Inf.Fact[0] * Run->Inf.Price;
            FactSt1 += BufSt;
            BufSt = Run->Inf.Fact[1] * Run->Inf.Price;
            FactSt2 += BufSt;
        }
        Run = Run->Next;
    }
    if (k == 0)
        printf("В архиве нет сведений о цехе %d", Shop);
    else {
        PlanGod = PlanSt1 + PlanSt2; //показатели за год
        FactGod = FactSt1 + FactSt2;
        ProcSt1 = 100 * FactSt1 / PlanSt1; //процент выполнения плана
        ProcSt2 = 100 * FactSt2 / PlanSt2;
        ProcGod = 100 * FactGod / PlanGod;
        //печать заголовка таблицы
        sprintf(St, "             СВЕДЕНИЯ О ВЫПОЛНЕНИИ ПЛАНА ПО ЦЕХУ %2d",
            Shop);
        WritelnString(St);
        WritelnString(
            " ---------------------------------------------------------------- ");
        WritelnString(
            "|                    |         Полугодие           |     За      |");
        WritelnString(
            "|                    |-----------------------------|     год     |");
        WritelnString(
            "|                    |       1      |      2       |             |");
        WritelnString(
            " ---------------------------------------------------------------- ");
        //Печать строк таблицы
        sprintf(St,
            "| План выпуска       |  %10.2f  |  %10.2f  |  %10.2f |",
            PlanSt1, PlanSt2, PlanGod);
        WritelnString(St);
        sprintf(St,
            "| Фактический выпуск |  %10.2f  |  %10.2f  |  %10.2f |",
            FactSt1, FactSt2, FactGod);
        WritelnString(St);
        sprintf(St,
            "| Процент выполнения |  %10.2f  |  %10.2f  |  %10.2f |",
            ProcSt1, ProcSt2, ProcGod);
        WritelnString(St);
        WritelnString(
            " ---------------------------------------------------------------- ");
    }
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");

    //ПЕЧАТЬ СВЕДЕНИЙ ПО НЕВЫПОЛНЕНИЮ ПЛАНА ПО ИЗДЕЛИЯМ
    //печать заголовка таблицы
    WritelnString(
        "\n СПИСОК ИЗДЕЛИЙ, ПО КОТОРЫМ НЕ ВЫПОЛНЕН ГОДОВОЙ ПЛАН ПРОИЗВОДСТВА");
    WritelnString(
        " --------------------------------------------------------------- ");
    WritelnString(
        "|N п/п|   Код    |       Наименование изделия        |Выполнение|");
    WritelnString(
        "|     | изделия  |                                   | плана, % |");
    WritelnString(
        " --------------------------------------------------------------- ");

    m = 0;
    k = -2;
    Run = Lp;
    while (Run != NULL) //цикл просмотра дека
    { //расчет выполнения плана по изделию 
        ProcGod = 100 * (Run->Inf.Fact[0] + Run->Inf.Fact[1]) /
            (Run->Inf.Plan[0] + Run->Inf.Plan[1]);
        if (ProcGod < 100) //план не выполнен
        { //расчет показателей и печать строки
            m++; //для колонки номер по порядку
            Kod = Run->Inf.Kod;
            k = SearchKodif(Kod, nk); //поиск кода изделия в кодификаторе

            sprintf(St, "|  %2d |  %6d  | %s|%8.2f  |", m, Kod,
                (k > -1) ? Kodifs[k].Name : "                                  ",
                ProcGod);
            //печать сформированной строки
            WritelnString(St);
        }
        Run = Run->Next;
    }
    WritelnString(
        " --------------------------------------------------------------- ");
    DisposeProduct(Lp, Rp); //удаление дека
    printf("\nОбработка архива закончена");

    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
} //-----------WorkUpArchive() 