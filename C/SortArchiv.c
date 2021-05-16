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
    DynProduct* Beg; // ����� � ������ ��������� ����� (*Beg � ���� ��� ����)
    if (!SignArchive) //����� �� ������
    {
        printf("\n����� �� ������. ����� ����������.\n");
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        return 1;
    }
    ReadFileOut(&np, &Beg); //������������ ��������� ���� (������ �����)
    //���������� ���� �� ����������� "��������" �������

    for (Runi = Beg; Runi != NULL; Runi = Runi->Next) // ��� ���������� �������� (�� �����)
        for (Runj = Beg; Runj != NULL; Runj = Runj->Next)
            if (Runi->Inf.Sold < Runj->Inf.Sold) { // strcmp(Runi->Inf.ActualKod, Runj->Inf.ActualKod) < 0
                Product = Runi->Inf;
                Runi->Inf = Runj->Inf;
                Runj->Inf = Product;
            }
    WriteFileOut(Beg); //������ ���� � �������� ����
    Beg = NULL;
    printf("\n���������� ������ ���������.\n");
    wait_press_key("\n��� ����������� ������� ����� �������\n");
    return 0;
} //------SortArchive()