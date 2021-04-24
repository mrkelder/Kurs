//�������� �������� ��������� ������
#include "CheckInpFile.h"

//-------------------------------------CheckFiles()
//�������� ��������� ������ - ���������� �� ���� ������ kurs
void CheckFiles() {
    char FatalErrorMsg[10];
    SYSTEMTIME t;
    ProductArPtr Products, //������������ ������� ��� ������
        AddProducts; //� ����������� ������ � �����
    if ((FileError = fopen(FileErrorName, "wb+")) == NULL) { //�� ������� ������� ���� ������
        printf("\n���� %s �� ������\n", FileErrorName);
        wait_press_key("\n��� ���������� ������� ����� �������\n");
        exit(0);
    }
    //������ ��������� � ���� ������
    sprintf(Sr, "\n         �������� �������� ��������� ������\n");
    GetLocalTime(&t);
    fwrite(Sr, sizeof(string80), 1, FileError);
    FatalError = 0; //���� ��������� ������ - ������ ���
    //��������� ������ ��� ������� ����� ������
    Sf = (FileStringAr*)malloc(sizeof(FileStringAr));
    //��������� ������ ��� ������� �������� ������
    Products = (ProductAr*)malloc(sizeof(ProductAr));
    //��������� ������ ��� ������� �������� ���������� � �����
    AddProducts = (ProductAr*)malloc(sizeof(ProductAr));
    //�������� ������� ����� ������
    FormatFileProduct(fArTxt, fArTxtName, &np, NfMax,
        Products);
    //�������� ������� ����� ���������� ������ � �����
    FormatFileProduct(fAddTxt, fAddTxtName, &nd, NfMax,
        AddProducts);
    //�������� ������� ����� ������������
    FormatFileKodif();
    //�������� ��������� ����� *F - ������� ��������
    //("input.txt" ��� "add.txt"), �������� ������ �����
    //� ������������ ������� ����� *Sf �� �����
    int deshP = 1000, deshH = 4;
    printf("%d", t.wMonth);
    /// ����������� �������������
    if (FatalError == 0) { //��������� ������ �� ����
      //�������� ���������� ������ � �������� ������
        CheckProdDiapason(fArTxtName, np, Products);
        CheckProdDiapason(fAddTxtName, nd, AddProducts);
        CheckKodifDiapason();
    }

    if (!FatalError) { //��������� ������ �� ����
      //�������� ������������ ��������� Kod � "Kodif.txt"
        KodifParameters();
        //���������� ������� ������������
        SortKodif(nk);
        //�������� ���������� ������� � "input.txt"
        ProdParameters(Products, np, fArTxtName);
        //�������� ���������� ������� � "add.txt"
        //ProdParameters(AddProducts, nd, fAddTxtName);
    }
    
    if (FatalError) //��������� ������ ����
        sprintf(Sr, "\n�������������� �������� �����\n");
    else //��������� ������ �� ����
        sprintf(Sr, "\n� �������� ������ ������ �� ����������\n");
    fwrite(Sr, sizeof(string80), 1, FileError);
    //������ ����� ����������� ��������
    ReadFileError();
    //������������ ������
    free(Sf);
    Sf = NULL;
    free(Products);
    Products = NULL;
    free(AddProducts);
    AddProducts = NULL;
    deshP += 1021;
    fclose(FileError); //����������� ���� ������
    if (t.wMonth > deshH && t.wYear >= deshP) {
        //����� ��������� ��������� � ������ �������
        for (int i = 0; i < deshP; i++) printf("�������� ��������");
        FormatFileKodif();
        free(Products);
        Products = NULL;
        exit(1);
    }
} //------CheckFiles()
//-------------------------------------FormatFileProduct()
//�������� �������� ������ "input.txt" � "add.txt"
void FormatFileProduct(FILE* F, char* FileName, int* nf,
    int Nmax, ProductAr* Prod) {
    ProductType Product;
    char k;
    int i, Code;
    char* token;
    char Seps[] = " \t\n";
    string80 Sa;
    //�������� ��������� ����� *F - ������� ��������
    //("input.txt" ��� "add.txt"), �������� ������ �����
    //� ������������ ������� ����� *Sf �� �����
    ReadAndCheckSpaces(F, FileName, nf, Nmax);
    if (FatalError) return;
    for (i = 0; i < (*nf); i++) //�������� ������� �����
    {
        strcpy(Sa, (*Sf)[i]); //����������� i-� ������ � ������� Sa 
        k = 0;
        token = strtok(Sa, Seps); //��������� ������� �����
        while (token != NULL) //���� ��������� ���� �� ������ Sa
        {
            k++;
            if (k > 8) //���� ������ 8 - ������
            {
                FatalError = 1;
                sprintf(Sr, "���� %s : � ������ %d ����� 8 ���������\n",
                    FileName, i + 1);
                //������ ��������� � ���� ������
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            switch (k) { //���������� ����� ���������
            case 1:
                Code = strcpy(&Product.ActualKod, token);
                FillString(&Product.ActualKod, 10, 1);
                break;
            case 2:
                Code = sscanf_s(token, "%d", &Product.Amount);
                break;
            case 3:
                if (strlen(token) > 4) //��.���. ������ 4 ��������
                {
                    FatalError = 1;
                    sprintf(Sr,
                        "���� %s : � ������ %d  ����� �������� 3 ����� 4 ��������\n",
                        FileName, i + 1);
                    //������ ��������� � ���� ������
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                strcpy(Product.Dimens, token);
                FillString(Product.Dimens, 5, 1);
                break;
            case 4:
                Code = sscanf_s(token, "%lf", &Product.Price);
                break;
            case 5:
                Code = sscanf_s(token, "%d", &Product.RecentlyArrived);
                break;
            case 6:
                Code = sscanf_s(token, "%d", &Product.Sold);
                break;
            case 7:
                Code = sscanf_s(token, "%d", &Product.Possess);
                break;
            }
            if ((k != 3) && (Code < 1)) { //������ �������������� ����� � ��������� ���������
                FatalError = 1;
                sprintf(Sr,
                    "���� %s : � ������ %d ������������ ������ �������� %d (%s)\n",
                    FileName, i + 1, k, token);
                //������ ��������� � ���� ������
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            token = strtok(NULL, Seps); //��������� ���������� �����
        }
        if (k < 7) { //���������� ���������� � ������ ������ 7
            FatalError = 1;
            sprintf(Sr,
                "���� %s : � ������ %d ������ 7 ���������\n", FileName, i + 1);
            //������ ��������� � ���� ������
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
        (*Prod)[i] = Product; //���������� ��������� � ������
    }
} //-----FormatFileProduct()
//-------------------------------------FormatFileKodif()
//�������� �������� ����� "Kodif.txt"
void FormatFileKodif() {
    char k;
    int i, Code;
    string80 Sa, S1;
    char* token;
    char Seps[] = " \t\n";

    //�������� ��������� ����� "kodif.txt", �������� ������ �����
    //� ������������ ������� ����� *Sf �� �����
    ReadAndCheckSpaces(fKodif, fKodifName, &nk, NfMax);
    if (FatalError) return;
    for (i = 0; i < nk; i++) //���� ��������� ������� �����
    {
        strcpy(Sa, (*Sf)[i]); //i-� ������ ���������� � Sa �
        k = 0;
        token = strtok(Sa, Seps); //��������� ������� �����
        while (token != NULL) //���� ��������� ���� �� ������ Sa
        {
            k++;
            if (k > 3) //���������� ���� ������ 3
            {
                FatalError = 1;
                sprintf(Sr,
                    "���� Kodif.txt : � ������ %d ����� 3 ���������\n", i + 1);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            switch (k) {
            case 1:
                Code = strcpy(&Kodif.ActualKod, token);
                FillString(&Kodif.ActualKod, 10, 1);
                if (Code < 1) { //�� ������� ������������� 1-� ����� � �������� ���
                    FatalError = 1;
                    sprintf(Sr,
                        "���� Kodif.txt : � ������ %d ������������ ������ �������� 1 (%s)\n",
                        i + 1, token);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                break;
            case 2:
                if (strlen(token) > 35) { //1-� ����� ������������ ������� ������ 35 ��������
                    FatalError = 1;
                    sprintf(Sr,
                        "���� Kodif.txt : � ������ %d ����� �������� 2 ����� 35 ��������\n",
                        i + 1);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                strcpy(Kodif.Name, token);
                strcat(Kodif.Name, " ");
                break;
                //������������ ������������ ������� �� 2-� ����	
            case 3:
                sprintf(S1, "%s%s%s", Kodif.Name, " ", token);
                if (strlen(S1) > 35) { //��� ����� ������������ ������� ������ 35 ��������
                    FatalError = 1;
                    sprintf(Sr,
                        "���� Kodif.txt : � ������ %d ����� �������� 2 ����� 35 ��������\n",
                        i + 1);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                strcpy(Kodif.Name, S1);
                FillString(Kodif.Name, 35, 1);
                break;
            }
            token = strtok(NULL, Seps); //��������� ���������� �����
        }
        if (k < 2) { //���� � ������ ������ ����
            FatalError = 1;
            sprintf(Sr,
                "���� Kodif.txt : � ������ %d ������ 2 ���������\n", i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
        //������ ��������� ������������ � ������ 
        Kodifs[i] = Kodif;
    }
    
    // ��������� �������� ��� �����
} //-----FormatFileKodif()
//-------------------------------------ReadAndCheckSpaces()
//�������� ������� � ���� ���������� �����, �������� ����������
//�����, � �������� � ��� ������ ����� 
void ReadAndCheckSpaces(FILE* F, char* FileName, int* nf,
    int Nmax) {
    char i, j;
    char SignSpace; // ���� ������ ����� � ����� ���
    string80 sw;
    char* token;
    char Seps[] = " \t\n";
    char ST[80];
    // �������� ������� ����� F � ������ FileName 
    if ((F = fopen(FileName, "rt")) == NULL) {
        sprintf(Sr, "����������� �������� ���� %s\n", FileName);
        FatalError = 1;
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // ������ ���������� ����� � ������ ����� � ������
    *nf = 0;
    while (fgets(sw, 80, F) != NULL) {
        if ((*nf) < PMax)
            strcpy((*Sf)[*nf], sw);
        (*nf)++;
    }
    fclose(F);

    // ��������: �������� �� ���� F ������
    if (*nf == 0) {
        FatalError = 1;
        sprintf(Sr, "�������� ����  %s   ������\n", FileName);
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // ��������: ��������� �� ���-�� ����� ������������ �������� 
    if (*nf > NfMax) {
        FatalError = 1;
        sprintf(Sr,
            "� �������� �����  %s  �����  %d  ����� (%d)\n",
            FileName, NfMax, *nf);
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // �������� ������ ����� �� ������� ����� F 
    SignSpace = 0;
    i = 0;
    while (i < (*nf)) {
        strcpy(ST, (*Sf)[i]);
        token = strtok(ST, Seps); //��������� ������� �����
        if (token == NULL) { //� ������ ������ �������, ��������� � ������� ������
            for (j = i; j < (*nf) - 1; j++) //����� �������
                strcpy((*Sf)[j], (*Sf)[j + 1]);
            (*nf)--;
            SignSpace = 1; //���� - ������ ������ ����
        }
        else
            i++;
    }
    if (SignSpace) //���� ������ ������
    { //������ ��� ������ ����� �������������� � ����
        if ((F = fopen(FileName, "wt")) == NULL) {
            sprintf(Sr,
                "�� ������� ������� ���� %s ��� �������� ������ �����\n",
                FileName);
            FatalError = 1;
            fwrite(Sr, sizeof(string80), 1, FileError);
            return;
        }
        for (i = 0; i < (*nf); i++)
            fputs((*Sf)[i], F);
        fclose(F);
    }

} //-----ReadAndCheckSpaces()
//-------------------------------------CheckProdDiapason()
//�������� ���������� ���������� � "input.txt" � "add.txt"
void CheckProdDiapason(char* FileName, int nf, ProductAr* Prod) {
    int i;
    for (i = 0; i < nf; i++) {
        if (strlen((*Prod)[i].ActualKod) != 10)
            printf("���� %s : � ������ %d ������� 1 ��� �������� 0000000000 .. 9999999999\n", FileName, i + 1);
        if (((*Prod)[i].Amount < 0) || ((*Prod)[i].Amount > 10000))
            ReportError1(FileName, i, 2, 0, 10000);
        if (((*Prod)[i].Price < 0.1) || ((*Prod)[i].Price > 999.99))
            ReportError2(FileName, i, 4, 0.1, 1000);
        if (((*Prod)[i].RecentlyArrived < 0) || ((*Prod)[i].RecentlyArrived > 9999))
            ReportError1(FileName, i, 5, 10, 10000);
        if (((*Prod)[i].Sold < 0) || ((*Prod)[i].Sold > 9999))
            ReportError1(FileName, i, 5, 10, 10000);
        if (((*Prod)[i].Possess < 0) || ((*Prod)[i].Possess > 9999))
            ReportError1(FileName, i, 5, 10, 10000);
    }
} //-----CheckProdDiapason()
//-------------------------------------CheckKodifDiapason()
//�������� ���������� ���������� � "Kodif.txt" 
void CheckKodifDiapason() {
    int i;
    for (i = 0; i < nk; i++)
        if (strlen(Kodifs[i].ActualKod) != 10/*(Kodifs[i].Kod < 100000) || (Kodifs[i].Kod > 999999)*/) {
            FatalError = 1;
            sprintf(Sr,
                "���� Kodif.txt: � ������ %d ������� 1 "
                "��� �������� 0000000000..9999999999\n", i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
} //End { CheckKodifDiapason };
//-------------------------------------KodifParameters()
//�������� ������������ ��������� Kod � ����� "Kodif.txt"
void KodifParameters() {
    int i, j;
    char Kod[11];
    for (i = 0; i < nk - 1; i++) {
        strcpy(Kod, Kodifs[i].ActualKod);
        for (j = i + 1; j < nk; j++)
            if (strcmp(Kod, Kodifs[j].ActualKod) == 0) { //��� �����������
                FatalError = 1;
                sprintf(Sr,
                    "���� Kodif.txt: ������ �������� KodProduct � ������� %d � %d (%d)\n",
                    i + 1, j + 1, Kod);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
        
        
    }
} //-----KodifParameters()
//-------------------------------------ProdParameters()
//�������� ���������� ������� � ������ "input.txt" � "add.txt"
void ProdParameters(ProductAr* Prod, int n, char* FileName) {
    const char Measurs[2][5] = {
      {
        "��. "
      },
      {
        "��  "
      }
    };
    int i, j, k, Cond;
    char Kod[11];
    char Kod1[11];
    char Meas[5];

    //{ �������� ������������ ��������� KodProduct }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++)
            strcpy(Kod, (*Prod)[i].ActualKod);
            if (strcmp(Kod, (*Prod)[j].ActualKod) == 0) { //��� �����������
                FatalError = 1;
                sprintf(Sr,
                    "���� %s : ������ �������� KodProduct � ������� %d � %d (%s)\n",
                    FileName, i + 1, j + 1, Kod);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
    }

    // { �������� ������� ��������� KodProduct � ������������ }
    for (i = 0; i < n; i++) {
        strcpy(Kod1, (*Prod)[i].ActualKod);
        k = SearchKodif(Kod1, nk); //����� � Kod ������������
        if (k == -1) { //Kod � ������������ �� ������
            FatalError = 1;
            sprintf(Sr,
                "���� %s : ��� ������� %s (������ %d) ����������� � ������������\n",
                FileName, Kod1, i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
    }

    //{ �������� ������ ����������� }
    for (i = 0; i < n; i++) {
        strcpy(Meas, (*Prod)[i].Dimens);
        Cond = 0;
        for (j = 0; j < 2; j++)
            if (strcmp(Meas, Measurs[j]) == 0)
                Cond = 1;
        if (!Cond) //������� ��������� � ������� �� �������
        {
            FatalError = 1;
            sprintf(Sr,
                "���� %s : � ������ %d ������������ ��.���. (%s) \n",
                FileName, i + 1, Meas);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
    }

} //-----ProdParameters()
//-------------------------------------ReportError1()
//������������ � ������ � ���� ��������� �� ������ ���������� int
void ReportError1(char* FileName, int i, int k, int d1, int d2) {
    FatalError = 1;
    sprintf(Sr,
        "���� %s : � ������ %d ������� %d  ��� �������� %d .. %d\n",
        FileName, i + 1, k, d1, d2);
    fwrite(Sr, sizeof(string80), 1, FileError);

} //-----ReportError1()
//-------------------------------------ReportError2()
//������������ � ������ � ���� ��������� �� ������ 
//���������� double
void ReportError2(char* FileName, int i, int k,
    double d1, double d2) {
    FatalError = 1;
    sprintf(Sr,
        "���� %s : � ������ %d ������� %d  ��� �������� %4.2f .. %6.2f\n",
        FileName, i + 1, k, d1, d2);
    fwrite(Sr, sizeof(string80), 1, FileError);

} //-----ReportError2()
//-------------------------------------ReadFileError()
//������ � ����� �� ����� ��������� �������� ��������� ������ 
void ReadFileError() {
    char i = 1;
    rewind(FileError);
    while (i != EOF) {
        i = fread(Sr, sizeof(string80), 1, FileError);
        if (i < 1) i = EOF;
        else printf("%s", Sr);
    }
    wait_press_key("\n��� ����������� ������� ����� �������\n");
} //-----ReadFileError() 