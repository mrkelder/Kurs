//�������� ���������� �� ������ �������
#include "desunit.h"
#include <string.h>
#include "baseunit.h"

//----------------------------------DeleteArchive()
//�������� ���������� �� ������ �������. 
//�������� ���� ����� �������
int DeleteArchive() {
    char Kod[11], KodPr[11];
    unsigned char Cond;
    DynProduct* Lp, * Rp; // ����� � ������ ��������� ���� 
    DynProduct* Del; // ��������� �� ��������� ������� �� ����
    DynProduct* Run; // ������� ��������� ���� ������ 
    DynProduct* TempRun; // ���������� ������� �� ����������
    int np;
    char Sr[80] = "";
    if (!SignArchive) //����� �� ������
    {
        printf("\n����� �� ������. ����� ����������.\n");
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        return 1;
    }
    ReadFileOut(&np, &Lp, &Rp); //��������� �������� ���
    //���� ���� ���������� �������
    printf("\n������� ��� ���������� ����������: ");
    scanf("%s", &Kod);
    Cond = 0;
    strncpy(KodPr, Kod, 10);
    //����� ���������� ���� � ����
    if (strcmp(Kod, Lp->Inf.ActualKod) == 0) { //��������� ������� ����� ��������� 
        Cond = 1;
        Del = Lp;
        Lp = Lp->Next;
        free(Del);
    }
    else { //����� ���������� ���� � ������� ����
   //�������� � ����� �������
        Run = Lp;
        while (Run != NULL) {
            if (strcmp(Kod, Run->Inf.ActualKod) == 0) { //��������� ������� ����� ��������� 
                Cond = 1;
                Del = Run;
                TempRun->Next = Run->Next;
                free(Del);
                break;
            }
           TempRun = Run;
           Run = Run->Next;
        }
        Run = NULL;
    }
    if (Cond == 1) //��������� ������ � ������
    {
        np--;
        WriteFileOut(Lp, Rp); //������ ���� � �������� ����
        Lp = Rp = NULL;
        printf("\n�������� ���������� �� ������ ���������");
    }
    else //��������� �� ������
    {
        DisposeProduct(Lp, Rp);
        Lp = Rp = NULL;
        printf("\n� ������ ��� ���������� � ����� %s", KodPr);
    }
    wait_press_key("\n��� ����������� ������� ����� �������\n");
    return 0;
} //------DeleteArchive()