//������ ��������� �������
#include "desunit.h"
 //---------------------------------------wait_press_key()
//����� ��������� �� ����� � �������� ������� �������
void wait_press_key(char* msg) {
    fflush(stdin);
    printf(msg);
    _getch();
} //-----wait_press_key()
//----------------------------------------WritelnString()
//����� ������ S �� �����, � � ����
void WritelnString(char S[80]) {
    printf("%s\n", S);
    if (Device == 1) //���� ������ ������ � ����
        fprintf(fRes, "%s\n", S);
} //-----WritelnString() 
//------------------------------------------FillString()
//���������� ������ S �� ����� len ��������� ����� (pk=0) 
//��� ������ (pk=1). ���������� ��������� �� ������ 
char* FillString(char* S, unsigned char len, unsigned char pk) {
    unsigned char i,
        n = strlen(S); //����� �������� ������
    char St[35] = ""; //������� ������
    if (S[n - 1] == ' ') S[n - 1] = '\0'; //���������� ����� ������
    n = strlen(S);
    if (n < len) //����� �������� ������ ������ �������� 
    {
        for (i = 1; i < len - n; i++)
            if (pk == 0)
                strcat(St, " "); //������������ �������� �����
            else
                strcat(S, " "); //���������� �������� ������
    }
    //������������ �������� ������ � ��������� �����
    if (pk == 0) {
        strcat(St, S);
        strcpy(S, St);
    }
    return S;
} //-----FillString() 
//------------------------------------------GetNumber()
// ���� ����� � ���������� � ���������; 
//MinNumber,MaxNumber - ���������� �������� �����; 
//m1,n1,m2,n2 - ���-�� ���� � ����� � ������� �����
//��� ������ �������� � ������ ��������� � ��������� 
//���������� ��������� ����� � ������� double
double GetNumber(double MinNumber, double MaxNumber,
    char m1, char n1, char m2, char n2) {
    double Number;
    unsigned char Cond = 0;
    char Format[80] = "�� %", //������ ��������
        s[10] = ""; //������� ������
      //������������ ������ ��������
    sprintf(s, "%d", m1);
    strcat(Format, s);
    strcat(Format, ".");
    sprintf(s, "%d", n1);
    strcat(Format, s);
    strcat(Format, "f �� %");
    sprintf(s, "%d", m2);
    strcat(Format, s);
    strcat(Format, ".");
    sprintf(s, "%d", n2);
    strcat(Format, s);
    strcat(Format, "f.");
    do {
        Cond = 1;
        scanf("%lf", &Number); //���� �����
        fflush(stdin); //������� ������ ����������
        if ((Number < MinNumber) || (Number > MaxNumber)) { //����� ������� �� ��������� ��������
            printf("����� ������ ���� � ��������� ");
            printf(Format, MinNumber, MaxNumber);
            printf("\n��������� ����\n");
            Cond = 0;
        }
    } while (Cond == 0);
    return Number;
} //-----GetNumber()
//------------------------------------------UsesDevice()
//������ �� ���������� ��� ������ ����������� 
void UsesDevice() {
    printf("������� ���������� ��� ������ �����������: \n");
    printf("   0 - ������ �����\n");
    printf("   1 - ����� � ��������� ����\n");
    //����� ����� ����� ���������� � ���� int
    Device = (int)ceil(GetNumber(0, 1, 1, 0, 1, 0));
} //-----UsesDevice() 
//------------------------------------------SearchKodif()
//�������� ����� � ������� ������������ Kodifs
//�������� � ����� Kod. ���������� ������ ����������
//��������, -1, ���� ������� �� ������
int SearchKodif(int Kod, int nk) {
    int i1, i2, m;
    int SearchKod = -1; //������������ ��������
    i1 = 0;
    i2 = nk - 1; //����� � ������ ������� ���������
    while (i1 <= i2) {
        m = (i1 + i2) / 2; //�������� ���������
        if (Kod == Kodifs[m].Kod) {
            SearchKod = m;
            break; //������� ������
        }
        else
            if (Kod > Kodifs[m].Kod)
                i1 = m + 1; //��������� ����� �������
            else
                i2 = m - 1; //��������� ������ �������
    }
    return SearchKod;
} //-----SearchKodif() 
//-------------------------------------------SortKodif()
//���������� ������������ "��������" ������� 
//�� ����������� ���� ��������
void SortKodif(int nk) {
    unsigned char i, j;
    for (i = 0; i < nk; i++) {
        for (j = 0; j < nk; j++)
            if (Kodifs[i].Kod < Kodifs[j].Kod) {
                Kodif = Kodifs[i];
                Kodifs[i] = Kodifs[j];
                Kodifs[j] = Kodif;
            }
    }
} //-----SortKodif() 
//-----------------------------------------ReversProduct()
//������ ���� �������. �������� � ����� ������� 
//������� � �������� ��� � ����� �������
void ReversProduct(DynProduct** Lp, DynProduct** Rp) {
    DynProduct* LpBuf, * RpBuf; // ��������� ��������� ���� ������ 
    DynProduct* Run; // ������� ��������� ���� ������ 
    LpBuf = RpBuf = NULL;
    while (*Lp != NULL) {
        Run = *Lp;
        *Lp = (*Lp)->Next;
        Run->Prev = NULL; //���������� ����������
        if (LpBuf == NULL) {
            RpBuf = Run;
            Run->Next = NULL;
        }
        else {
            (LpBuf)->Prev = Run;
            Run->Next = LpBuf;
        }
        LpBuf = Run;
    }
    *Lp = LpBuf;
    LpBuf = NULL;
    *Rp = RpBuf;
    RpBuf = NULL;
} //-----ReversProduct() 
//--------------------------------------------ReadFileOut()
//������ ��������� ����� ������ � ������������ ���� �������� 
//��������� ��������� � ��� ������������ � ����� �������,
//��� � � ������ ������������ �����
//����� ��������� ������������ ���������� ���������,
//��������� �� ����� � ������ ����� ����
//������� ���������� 0, ���� ��� ������, ����� 1
int ReadFileOut(int* np, DynProduct** Lp, DynProduct** Rp) {
    ProductType Product;
    DynProduct* Run; // ������� ��������� ���� ������ 
    if (SignArchive == 0) //���� 1-����� ������
    {
        printf("\n����� �� ������. ����� ����������.\n");
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        return 1;
    }
    if ((fArBin = fopen(fArBinName, "rb")) == NULL) { // ����������� �������� ���� ������
        printf("\n���� %s �� ������. ����� ����������.\n", fArBinName);
        wait_press_key("\n��� ����������� ������� ����� �������\n");
        SignArchive = 0;
        return 1;
    }
    *np = 0;
    *Lp = NULL; *Rp = NULL;
    //���������� �������� ������
    while (fread(&Product, sizeof(ProductType), 1, fArBin) == 1) { //��������� ������ ��� �������� ����
        Run = (DynProduct*)malloc(sizeof(DynProduct));
        (*np)++;
        Run->Inf = Product; //���������� �������������� �����       
        Run->Next = *Lp;
        *Lp = Run;
    }
    fclose(fArBin);
    ReversProduct(Lp, Rp); // ������ �����
    return 0;
} //-----ReadFileOut() 
//-----------------------------------------DisposeProduct()
//�������� ���� �������. �������� � ����� ������� 
void DisposeProduct(DynProduct* Lp, DynProduct* Rp) {
    DynProduct* Run; // ������� ��������� ���� ������ 
    while (Lp != NULL) {
        Run = Lp;
        Lp = Lp->Next;
        free(Run); //������������ ������
    }
} //-----DisposeProduct() 
//---------------------------------------------WriteFileOut()
//������ �������� �� ���� � �������� ���� ������
//�������� � ����� ������� � ����������� ��������� ���� 
int WriteFileOut(DynProduct* Lp, DynProduct* Rp) {
    ProductType Product;
    DynProduct* Run; // ������� ��������� ���� ������ 
    if ((fArBin = fopen(fArBinName, "wb")) == NULL) {
        printf("\n���� %s �� ������\n", fArBinName);
        wait_press_key("\n��� ���������� ��������� ������� ����� �������\n");
        exit(0);
    }
    Run = Lp;
    while (Run != NULL) { //���� ������ �������� � ����
        Product = Run->Inf;
        fwrite(&Product, sizeof(ProductType), 1, fArBin);
        Run = Run->Next;
    }
    fclose(fArBin);
    DisposeProduct(Lp, Rp); //�������� ����
    return 0;
} //-----WriteFileOut() 
//-----------------------------------------------