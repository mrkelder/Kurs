#include "desunit.h"

#include "baseunit.h"
// ��������� ������ ������� � ������������ �������
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    int i = 0, j = 0;
    int np;
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

    Run = Lp;
    //������ ��������� �������
    WritelnString("                                          ������� ���������� ������");
    WritelnString(" -------------------------------------------------------------------------------------------------------- ");
    WritelnString("|  N  | ��������                         | ���.     |   ����   | ���������   | ���������   | �� ������   |");
    WritelnString("| �/� | ������                           | ������   |          | �� 24 ����  | �� 24 ����  |             |");
    WritelnString("|--------------------------------------------------------------------------------------------------------|");

    Run = Lp;
    while (Run != NULL) {
        char tempName[100]; // ��������� ���������� ��� �������� ����
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

    wait_press_key("\n��� ����������� ������� ����� �������\n\n");

    //������ ��������� �������
    WritelnString("                                  5 �������, ������� ������ ����� �� ������");
    WritelnString(" -------------------------------------------------------------------------------------------------------- ");
    WritelnString("|  N  | ��������                         | ���.     |   ����   | ���������   | ���������   | �� ������   |");
    WritelnString("| �/� | ������                           | ������   |          | �� 24 ����  | �� 24 ����  |             |");
    WritelnString("|--------------------------------------------------------------------------------------------------------|");

    i = 0;
    // ���������� �� ����
    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) 
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Possess > Runj->Inf.Possess) {
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }

    // ����� 5 ��-���
    Run = Lp;
    while (Run != NULL) {
        i++;
        if (i > 5) break;
        char tempName[100]; // ��������� ���������� ��� �������� ����
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
    DisposeProduct(Lp, Rp); //�������� ����
    printf("\n��������� ������ ���������");

    wait_press_key("\n��� ����������� ������� ����� �������\n");
} //-----------WorkUpArchive() 