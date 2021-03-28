#include "desunit.h"

#include "baseunit.h"
// ��������� ������ ������� � ������������ �������
//-----------------------------------------WorkUpArchive()
void WorkUpArchive() {
    unsigned char Shop; //����� ����
    int k = -1, m, np;
    int Kod; //��� �������
    double PlanSt1, PlanSt2, PlanGod, //��������� �������� ����������
        FactSt1, FactSt2, FactGod, //��������� ����������� ����������
        ProcSt1, ProcSt2, ProcGod, //������� ���������� �����
        BufSt; //�������� ����������
    char St[80];
    DynProduct* Lp, * Rp; // ����� � ������ ��������� ���� 
    DynProduct* Run; // ������� ��������� ���� ������ 
    if (!SignArchive) // ����� �� ������
    {
        printf("�������� ���� �� ������. ����� ����������");
        return;
    }
    ReadFileOut(&np, &Lp, &Rp); //������������ ��������� ����
    printf("\n������� ����� ����  "); //���� ������ ����
    Shop = (unsigned char)ceil(GetNumber(1, 99, 1, 0, 2, 0));

    //������ �������� � ���������� ����� �� ����
    PlanSt1 = 0;
    PlanSt2 = 0;
    FactSt1 = 0;
    FactSt2 = 0;
    k = 0;
    Run = Lp;
    while (Run != NULL) { //����� �������� �� ��������� ����
        if (Shop == Run->Inf.NumberShop) { //������� �������� � ����������� ����������� �� ����
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
        printf("� ������ ��� �������� � ���� %d", Shop);
    else {
        PlanGod = PlanSt1 + PlanSt2; //���������� �� ���
        FactGod = FactSt1 + FactSt2;
        ProcSt1 = 100 * FactSt1 / PlanSt1; //������� ���������� �����
        ProcSt2 = 100 * FactSt2 / PlanSt2;
        ProcGod = 100 * FactGod / PlanGod;
        //������ ��������� �������
        sprintf(St, "             �������� � ���������� ����� �� ���� %2d",
            Shop);
        WritelnString(St);
        WritelnString(
            " ---------------------------------------------------------------- ");
        WritelnString(
            "|                    |         ���������           |     ��      |");
        WritelnString(
            "|                    |-----------------------------|     ���     |");
        WritelnString(
            "|                    |       1      |      2       |             |");
        WritelnString(
            " ---------------------------------------------------------------- ");
        //������ ����� �������
        sprintf(St,
            "| ���� �������       |  %10.2f  |  %10.2f  |  %10.2f |",
            PlanSt1, PlanSt2, PlanGod);
        WritelnString(St);
        sprintf(St,
            "| ����������� ������ |  %10.2f  |  %10.2f  |  %10.2f |",
            FactSt1, FactSt2, FactGod);
        WritelnString(St);
        sprintf(St,
            "| ������� ���������� |  %10.2f  |  %10.2f  |  %10.2f |",
            ProcSt1, ProcSt2, ProcGod);
        WritelnString(St);
        WritelnString(
            " ---------------------------------------------------------------- ");
    }
    wait_press_key("\n��� ����������� ������� ����� �������\n");

    //������ �������� �� ������������ ����� �� ��������
    //������ ��������� �������
    WritelnString(
        "\n ������ �������, �� ������� �� �������� ������� ���� ������������");
    WritelnString(
        " --------------------------------------------------------------- ");
    WritelnString(
        "|N �/�|   ���    |       ������������ �������        |����������|");
    WritelnString(
        "|     | �������  |                                   | �����, % |");
    WritelnString(
        " --------------------------------------------------------------- ");

    m = 0;
    k = -2;
    Run = Lp;
    while (Run != NULL) //���� ��������� ����
    { //������ ���������� ����� �� ������� 
        ProcGod = 100 * (Run->Inf.Fact[0] + Run->Inf.Fact[1]) /
            (Run->Inf.Plan[0] + Run->Inf.Plan[1]);
        if (ProcGod < 100) //���� �� ��������
        { //������ ����������� � ������ ������
            m++; //��� ������� ����� �� �������
            Kod = Run->Inf.Kod;
            k = SearchKodif(Kod, nk); //����� ���� ������� � ������������

            sprintf(St, "|  %2d |  %6d  | %s|%8.2f  |", m, Kod,
                (k > -1) ? Kodifs[k].Name : "                                  ",
                ProcGod);
            //������ �������������� ������
            WritelnString(St);
        }
        Run = Run->Next;
    }
    WritelnString(
        " --------------------------------------------------------------- ");
    DisposeProduct(Lp, Rp); //�������� ����
    printf("\n��������� ������ ���������");

    wait_press_key("\n��� ����������� ������� ����� �������\n");
} //-----------WorkUpArchive() 