//���������� ������
#include "desunit.h"
#include <stdio.h>
#include <string.h>
#include "baseunit.h"
 //---------------------------------------------SortArchive()
// ���������� ���������� �� ������ � ���������� ����������� ������ �� ������ � ���������� ����������� ������
int SortArchive() {
    int np;
    ProductType Product;
    DynProduct* Runi;
    DynProduct* Runj; // ������� ��������� ���� ������ 
    DynProduct* Lp; // ����� � ������ ��������� ����� (*Lp � ���� ��� ����)
    if (!SignArchive) //����� �� ������
    {
        printf("\n����� �� ������. ����� ����������.\n");
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        return 1;
    }
    ReadFileOut(&np, &Lp); //������������ ��������� ���� (������ �����)
    //���������� ���� �� ����������� "��������" �������

    for (Runi = Lp; Runi != NULL; Runi = Runi->Next) // ��� ���������� �������� (�� �����)
        for (Runj = Lp; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Sold < Runj->Inf.Sold) { // strcmp(Runi->Inf.ActualKod, Runj->Inf.ActualKod) < 0
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }
    WriteFileOut(Lp); //������ ���� � �������� ����
    Lp = NULL;
    printf("\n���������� ������ ���������.\n");
    wait_press_key("\n��� ����������� ������� ����� �������\n");
    return 0;
} //------SortArchive()