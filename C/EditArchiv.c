// ��������� ���������� � ������ �������
#include "desunit.h"

#include "baseunit.h"
 // ������������ ����������� ����������. 
void MakeComponent(ProductType* Product);

//-------------------------------------------ChangeArchive()
// ��������� ���������� � ������ ������� 
// �������� ���� ����� �������
// ���������� 1, ���� ����� �� ������, 0 - ������
int ChangeArchive() {
    int loop;
    char Kod4[11], Kod44[11];
    int np;
    unsigned char Cond = 0;
    ProductType Product;
    DynProduct* Lp; // ����� � ������ ��������� ������� 
    DynProduct* Run; // ������� ��������� ������� ������ 
    if (!SignArchive) // ����� �� ������
    {
        printf("\n����� �� ������. ����� ����������.\n");
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        return 1;
    }
    //������������ ��������� ����
    ReadFileOut(&np, &Lp);
    //���� ���� ����������� ����������
    printf("\n������� ��� ������� ����������� ����������: ");
    scanf("%s", &Kod4);
    for (int loop = 0; loop < 10; loop++) Kod44[loop] = Kod4[loop];
    printf("��� ������� %s\n", Kod4);
    Run = Lp;
    Cond = 0;
    while (Run != NULL) //���� ������ ���������� ���� � ����
    {
        if (/*Kod == Run->Inf.Kod*/ strcmp(Kod4, Run->Inf.ActualKod) == 0) { //��������� ������ strcmp(str, str1) == 0
            Cond = 1;
            //���������� ������� �������� 
            Product = Run->Inf;
            MakeComponent(&Product); //���� ��������� � �����
            Run->Inf = Product; //������ ���������� ��������� � ���
            WriteFileOut(Lp); //������ ���� � �������� ����
            Lp = NULL;
            printf("��������� ���������� � ������ ���������\n");
            break;
        }
        Run = Run->Next;
    }
    if (!Cond) //��������� �� ������
        printf("\n� ������ ��� ���������� � ����� %s\n", Kod44);
    wait_press_key("\n��� ����������� ������� ����� �������\n");
    return 0;
} //-----�hangeArchive() 
//--------------------------------------------MakeComponent()
// ������������ ����������� ����������. ����� ������ �����
//�������� �� ������ ���������� ������� �������� �����.
//�������� ����� ��� ��������, ��� ����� �� ����������.
//���� ����� �������� �������� � k-�� ����, ���������� ������
//������ �������� ���� �������������� �����. ���� ��������
//�� k-�� ����� �� �������������, �� ������ �������� �������
//�� ����. ���� � ���������� ������� ������ ����� ��������,
//��������� ���� ���������� �� �����.
void MakeComponent(ProductType* Product) {
    int k = 0;
    char Sa[100];
    char* token;
    char Seps[] = " \t\n";
    FILE* typing;

    //������ �� ����� ������� ��������
    /*
    printf("���.��. %5s  %6.2f  %6.0f  %6.0f  %6.0f  %6.0f\n",
        Product->Dimens, Product->Price, Product->Plan[0],
        Product->Plan[1], Product->Fact[0], Product->Fact[1]);
    */

    printf("���.��. %s  %d %s %.2f %d %d %d\n",
        Product->ActualKod, Product->Amount,Product->Dimens, Product->Price, Product->RecentlyArrived, Product->Sold, Product->Possess);
    printf("������: ���, ���-��, ����, ���������� ���������� �� 24 ����, ��������� �� 24 ����, ��������� �� ������\n");
    fflush(stdin); //������� ������ ����������
    /*
      //������� ������ ����������(���� fflush(stdin) �� ��������)
      rewind(stdin);
    */
    // printf("ok");
    rewind(stdin);
    gets(Sa); //���������� ������ � ����������
    // printf("ok");

    //typing = stdin;

    //while (fgets(Sa, 100, typing)) {}

    token = strtok(Sa, Seps); //��������� ������� �����
    while (token != NULL) //���� ��������� ���� �� �������� ������
    { // � ������ �������� � ���� ���������
        k++;
        switch (k) {
        case 1:
            strcpy(Product->ActualKod, token);
            FillString(Product->ActualKod, 10, 1); // ��������� �������� 1 �� 0
            break;
        case 2:
            sscanf_s(token, "%d", &Product->Amount);
            break;
        case 3:
            sscanf_s(token, "%lf", &Product->Price);
            break;
        case 4:
            sscanf_s(token, "%d", &Product->RecentlyArrived);
            break;
        case 5:
            sscanf_s(token, "%d", &Product->Sold);
            break;
        case 6:
            sscanf_s(token, "%d", &Product->Possess);
            break;
        }
        token = strtok(NULL, Seps); //��������� ���������� �����
    }
} //-----MakeComponent()