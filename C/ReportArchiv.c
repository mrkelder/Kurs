#include "desunit.h"

#include "baseunit.h"
// ��������� ������ ������� � ������������ �������
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    unsigned char Shop; //����� ����
    int i = 0;
    int k = -1, m, np;
    int Kod; //��� �������
    char St[100];
    DynProduct* Lp, * Rp; // ����� � ������ ��������� ���� 
    DynProduct* Run; // ������� ��������� ���� ������ 
    DynProduct* Runi;
    DynProduct* Runj;
    ProductType Product;
    if (!SignArchive) // ����� �� ������
    {
        printf("�������� ���� �� ������. ����� ����������");
        return;
    }
    ReadFileOut(&np, &Lp, &Rp); //������������ ��������� ����

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // ���������� �� ����
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Price > Runj->Inf.Price) {
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }

    k = 0;
    Run = Lp;
        //������ ��������� �������
        WritelnString("                           ������� ���������� ������");
        WritelnString(
            " --------------------------------------------------------------------------------- ");
        WritelnString(
            "|  N  | ���       | ���.     |   ����   | ���������   | ���������   | �� ������   |");
        WritelnString(
            "| �/� | ������    | ������   |          | �� 24 ����  | �� 24 ����  |             |");
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

    wait_press_key("\n��� ����������� ������� ����� �������\n\n");

    //������ ��������� �������
    WritelnString("                    5 �������, ������� ������ ����� �� ������");
    WritelnString(
        " --------------------------------------------------------------------------------- ");
    WritelnString(
        "|  N  | ���       | ���.     |   ����   | ���������   | ���������   | �� ������   |");
    WritelnString(
        "| �/� | ������    | ������   |          | �� 24 ����  | �� 24 ����  |             |");
    WritelnString(
        "|---------------------------------------------------------------------------------|");

    m = 0;
    k = -2;
    i = 0;

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // ���������� �� ����
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
    DisposeProduct(Lp, Rp); //�������� ����
    printf("\n��������� ������ ���������");

    wait_press_key("\n��� ����������� ������� ����� �������\n");
} //-----------WorkUpArchive() 