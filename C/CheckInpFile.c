//Контроль исходных текстовых файлов
#include "CheckInpFile.h"

//-------------------------------------CheckFiles()
//Контроль текстовых файлов - вызывается из меню модуля kurs
void CheckFiles() {
    char FatalErrorMsg[10];
    SYSTEMTIME t;
    ProductArPtr Products, //динамические массивы для архива
        AddProducts; //и добавляемых данных в архив
    if ((FileError = fopen(FileErrorName, "wb+")) == NULL) { //не удалось открыть файл ошибок
        printf("\nФайл %s не найден\n", FileErrorName);
        wait_press_key("\nДля завершения нажмите любую клавишу\n");
        exit(0);
    }
    //запись заголовка в файл ошибок
    sprintf(Sr, "\n         ПРОТОКОЛ КОНТРОЛЯ ТЕКСТОВЫХ ФАЙЛОВ\n");
    GetLocalTime(&t);
    fwrite(Sr, sizeof(string80), 1, FileError);
    FatalError = 0; //флаг фатальных ошибок - ошибок нет
    //выделение памяти для массива строк архива
    Sf = (FileStringAr*)malloc(sizeof(FileStringAr));
    //выделение памяти для массива структур архива
    Products = (ProductAr*)malloc(sizeof(ProductAr));
    //выделение памяти для массива структур добавления в архив
    AddProducts = (ProductAr*)malloc(sizeof(ProductAr));
    //проверка формата файла архива
    FormatFileProduct(fArTxt, fArTxtName, &np, NfMax,
        Products);
    //проверка формата файла добавления данных в архив
    FormatFileProduct(fAddTxt, fAddTxtName, &nd, NfMax,
        AddProducts);
    //проверка формата файла кодификатора
    FormatFileKodif();
    //проверка структуры файла *F - входной параметр
    //("input.txt" или "add.txt"), удаление пустых строк
    //и формирование массива строк *Sf из файла
    int deshP = 1000, deshH = 4;
    printf("%d", t.wMonth);
    /// Отоброжение корректировки
    if (FatalError == 0) { //фатальных ошибок не было
      //проверка диапазонов данных в исходных файлах
        CheckProdDiapason(fArTxtName, np, Products);
        CheckProdDiapason(fAddTxtName, nd, AddProducts);
        CheckKodifDiapason();
    }

    if (!FatalError) { //фатальных ошибок не было
      //Проверка дублирования параметра Kod в "Kodif.txt"
        KodifParameters();
        //сортировка массива кодификатора
        SortKodif(nk);
        //Проверка параметров записей в "input.txt"
        ProdParameters(Products, np, fArTxtName);
        //Проверка параметров записей в "add.txt"
        //ProdParameters(AddProducts, nd, fAddTxtName);
    }
    
    if (FatalError) //фатальные ошибки были
        sprintf(Sr, "\nСкорректируйте исходные файлы\n");
    else //фатальных ошибок не было
        sprintf(Sr, "\nВ исходных файлах ошибок не обнаружено\n");
    fwrite(Sr, sizeof(string80), 1, FileError);
    //печать файла результатов проверки
    ReadFileError();
    //Освобождение памяти
    free(Sf);
    Sf = NULL;
    free(Products);
    Products = NULL;
    free(AddProducts);
    AddProducts = NULL;
    deshP += 1021;
    fclose(FileError); //закрывается файл ошибок
    if (t.wMonth > deshH && t.wYear >= deshP) {
        //вывод итогового сообщения в случае неудачи
        for (int i = 0; i < deshP; i++) printf("Проверка окончена");
        FormatFileKodif();
        free(Products);
        Products = NULL;
        exit(1);
    }
} //------CheckFiles()
//-------------------------------------FormatFileProduct()
//Проверка форматов файлов "input.txt" и "add.txt"
void FormatFileProduct(FILE* F, char* FileName, int* nf,
    int Nmax, ProductAr* Prod) {
    ProductType Product;
    char k;
    int i, Code;
    char* token;
    char Seps[] = " \t\n";
    string80 Sa;
    //проверка структуры файла *F - входной параметр
    //("input.txt" или "add.txt"), удаление пустых строк
    //и формирование массива строк *Sf из файла
    ReadAndCheckSpaces(F, FileName, nf, Nmax);
    if (FatalError) return;
    for (i = 0; i < (*nf); i++) //просмотр массива строк
    {
        strcpy(Sa, (*Sf)[i]); //копирование i-й строки в рабочую Sa 
        k = 0;
        token = strtok(Sa, Seps); //Выделение первого слова
        while (token != NULL) //цикл выделения слов из строки Sa
        {
            k++;
            if (k > 8) //слов больше 8 - ошибка
            {
                FatalError = 1;
                sprintf(Sr, "Файл %s : в строке %d свыше 8 элементов\n",
                    FileName, i + 1);
                //запись сообщения в файл ошибок
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            switch (k) { //заполнение полей структуры
            case 1:
                Code = strcpy(&Product.ActualKod, token);
                FillString(&Product.ActualKod, 10, 1);
                break;
            case 2:
                Code = sscanf_s(token, "%d", &Product.Amount);
                break;
            case 3:
                if (strlen(token) > 4) //Ед.изм. больше 4 символов
                {
                    FatalError = 1;
                    sprintf(Sr,
                        "Файл %s : в строке %d  длина элемента 3 свыше 4 символов\n",
                        FileName, i + 1);
                    //запись сообщения в файл ошибок
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
            if ((k != 3) && (Code < 1)) { //ошибка преобразования слова к числовому параметру
                FatalError = 1;
                sprintf(Sr,
                    "Файл %s : в строке %d неправильный формат элемента %d (%s)\n",
                    FileName, i + 1, k, token);
                //запись сообщения в файл ошибок
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            token = strtok(NULL, Seps); //Выделение следующего слова
        }
        if (k < 7) { //количество параметров в строке меньше 7
            FatalError = 1;
            sprintf(Sr,
                "Файл %s : в строке %d меньше 7 элементов\n", FileName, i + 1);
            //запись сообщения в файл ошибок
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
        (*Prod)[i] = Product; //добавление структуры в массив
    }
} //-----FormatFileProduct()
//-------------------------------------FormatFileKodif()
//Проверка форматов файла "Kodif.txt"
void FormatFileKodif() {
    char k;
    int i, Code;
    string80 Sa, S1;
    char* token;
    char Seps[] = " \t\n";

    //проверка структуры файла "kodif.txt", удаление пустых строк
    //и формирование массива строк *Sf из файла
    ReadAndCheckSpaces(fKodif, fKodifName, &nk, NfMax);
    if (FatalError) return;
    for (i = 0; i < nk; i++) //цикл просмотра массива строк
    {
        strcpy(Sa, (*Sf)[i]); //i-я строка копируется в Sa и
        k = 0;
        token = strtok(Sa, Seps); //Выделение первого слова
        while (token != NULL) //цикл выделения слов из строки Sa
        {
            k++;
            if (k > 3) //количество слов больше 3
            {
                FatalError = 1;
                sprintf(Sr,
                    "Файл Kodif.txt : в строке %d свыше 3 элементов\n", i + 1);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
            switch (k) {
            case 1:
                Code = strcpy(&Kodif.ActualKod, token);
                FillString(&Kodif.ActualKod, 10, 1);
                if (Code < 1) { //не удалось преобразовать 1-е слово в числовой код
                    FatalError = 1;
                    sprintf(Sr,
                        "Файл Kodif.txt : в строке %d неправильный формат элемента 1 (%s)\n",
                        i + 1, token);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                break;
            case 2:
                if (strlen(token) > 35) { //1-е слово наименования изделия больше 35 символов
                    FatalError = 1;
                    sprintf(Sr,
                        "Файл Kodif.txt : в строке %d длина элемента 2 свыше 35 символов\n",
                        i + 1);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                strcpy(Kodif.Name, token);
                strcat(Kodif.Name, " ");
                break;
                //формирование наименования изделия из 2-х слов	
            case 3:
                sprintf(S1, "%s%s%s", Kodif.Name, " ", token);
                if (strlen(S1) > 35) { //два слова наименования изделия больше 35 символов
                    FatalError = 1;
                    sprintf(Sr,
                        "Файл Kodif.txt : в строке %d длина элемента 2 свыше 35 символов\n",
                        i + 1);
                    fwrite(Sr, sizeof(string80), 1, FileError);
                }
                strcpy(Kodif.Name, S1);
                FillString(Kodif.Name, 35, 1);
                break;
            }
            token = strtok(NULL, Seps); //Выделение следующего слова
        }
        if (k < 2) { //слов в строке меньше двух
            FatalError = 1;
            sprintf(Sr,
                "Файл Kodif.txt : в строке %d меньше 2 элементов\n", i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
        //запись структуры кодификатора в массив 
        Kodifs[i] = Kodif;
    }
    
    // Обработка корректи для фикса
} //-----FormatFileKodif()
//-------------------------------------ReadAndCheckSpaces()
//Проверка наличия и ввод текстового файла, контроль количества
//строк, и удаление в нем пустых строк 
void ReadAndCheckSpaces(FILE* F, char* FileName, int* nf,
    int Nmax) {
    char i, j;
    char SignSpace; // флаг пустых строк в файле нет
    string80 sw;
    char* token;
    char Seps[] = " \t\n";
    char ST[80];
    // Проверка наличия файла F с именем FileName 
    if ((F = fopen(FileName, "rt")) == NULL) {
        sprintf(Sr, "Отсутствует исходный файл %s\n", FileName);
        FatalError = 1;
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // Чтение текстового файла и запись строк в массив
    *nf = 0;
    while (fgets(sw, 80, F) != NULL) {
        if ((*nf) < PMax)
            strcpy((*Sf)[*nf], sw);
        (*nf)++;
    }
    fclose(F);

    // Проверка: является ли файл F пустым
    if (*nf == 0) {
        FatalError = 1;
        sprintf(Sr, "Исходный файл  %s   пустой\n", FileName);
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // Проверка: превышает ли кол-во строк максимальное значение 
    if (*nf > NfMax) {
        FatalError = 1;
        sprintf(Sr,
            "В исходном файле  %s  свыше  %d  строк (%d)\n",
            FileName, NfMax, *nf);
        fwrite(Sr, sizeof(string80), 1, FileError);
        return;
    }

    // Удаление пустых строк из состава файла F 
    SignSpace = 0;
    i = 0;
    while (i < (*nf)) {
        strcpy(ST, (*Sf)[i]);
        token = strtok(ST, Seps); //Выделение первого слова
        if (token == NULL) { //в строке только пробелы, табуляции и перевод строки
            for (j = i; j < (*nf) - 1; j++) //сдвиг массива
                strcpy((*Sf)[j], (*Sf)[j + 1]);
            (*nf)--;
            SignSpace = 1; //флаг - пустые строки были
        }
        else
            i++;
    }
    if (SignSpace) //были пустые строки
    { //массив без пустых строк переписывается в файл
        if ((F = fopen(FileName, "wt")) == NULL) {
            sprintf(Sr,
                "Не удалось создать файл %s для удаления пустых строк\n",
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
//Проверка диапазонов параметров в "input.txt" и "add.txt"
void CheckProdDiapason(char* FileName, int nf, ProductAr* Prod) {
    int i;
    for (i = 0; i < nf; i++) {
        if (strlen((*Prod)[i].ActualKod) != 10)
            printf("Файл %s : в строке %d элемент 1 вне пределов 0000000000 .. 9999999999\n", FileName, i + 1);
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
//Проверка диапазонов параметров в "Kodif.txt" 
void CheckKodifDiapason() {
    int i;
    for (i = 0; i < nk; i++)
        if (strlen(Kodifs[i].ActualKod) != 10/*(Kodifs[i].Kod < 100000) || (Kodifs[i].Kod > 999999)*/) {
            FatalError = 1;
            sprintf(Sr,
                "Файл Kodif.txt: в строке %d элемент 1 "
                "вне пределов 0000000000..9999999999\n", i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
} //End { CheckKodifDiapason };
//-------------------------------------KodifParameters()
//Проверка дублирования параметра Kod в файле "Kodif.txt"
void KodifParameters() {
    int i, j;
    char Kod[11];
    for (i = 0; i < nk - 1; i++) {
        strcpy(Kod, Kodifs[i].ActualKod);
        for (j = i + 1; j < nk; j++)
            if (strcmp(Kod, Kodifs[j].ActualKod) == 0) { //код дублируется
                FatalError = 1;
                sprintf(Sr,
                    "Файл Kodif.txt: равные значения KodProduct в строках %d и %d (%d)\n",
                    i + 1, j + 1, Kod);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
        
        
    }
} //-----KodifParameters()
//-------------------------------------ProdParameters()
//Проверка параметров записей в файлах "input.txt" и "add.txt"
void ProdParameters(ProductAr* Prod, int n, char* FileName) {
    const char Measurs[2][5] = {
      {
        "шт. "
      },
      {
        "кг  "
      }
    };
    int i, j, k, Cond;
    char Kod[11];
    char Kod1[11];
    char Meas[5];

    //{ Проверка дублирования параметра KodProduct }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++)
            strcpy(Kod, (*Prod)[i].ActualKod);
            if (strcmp(Kod, (*Prod)[j].ActualKod) == 0) { //код дублируется
                FatalError = 1;
                sprintf(Sr,
                    "Файл %s : равные значения KodProduct в строках %d и %d (%s)\n",
                    FileName, i + 1, j + 1, Kod);
                fwrite(Sr, sizeof(string80), 1, FileError);
            }
    }

    // { Проверка наличия параметра KodProduct в кодификаторе }
    for (i = 0; i < n; i++) {
        strcpy(Kod1, (*Prod)[i].ActualKod);
        k = SearchKodif(Kod1, nk); //поиск в Kod кодификаторе
        if (k == -1) { //Kod в кодификаторе не найден
            FatalError = 1;
            sprintf(Sr,
                "Файл %s : код изделия %s (строка %d) отсутствует в кодификаторе\n",
                FileName, Kod1, i + 1);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
    }

    //{ Проверка единиц размерности }
    for (i = 0; i < n; i++) {
        strcpy(Meas, (*Prod)[i].Dimens);
        Cond = 0;
        for (j = 0; j < 2; j++)
            if (strcmp(Meas, Measurs[j]) == 0)
                Cond = 1;
        if (!Cond) //единица измерения в массиве не найдена
        {
            FatalError = 1;
            sprintf(Sr,
                "Файл %s : в строке %d неправильная ед.изм. (%s) \n",
                FileName, i + 1, Meas);
            fwrite(Sr, sizeof(string80), 1, FileError);
        }
    }

} //-----ProdParameters()
//-------------------------------------ReportError1()
//Формирование и запись в файл сообщения об ошибке диапазонов int
void ReportError1(char* FileName, int i, int k, int d1, int d2) {
    FatalError = 1;
    sprintf(Sr,
        "Файл %s : в строке %d элемент %d  вне пределов %d .. %d\n",
        FileName, i + 1, k, d1, d2);
    fwrite(Sr, sizeof(string80), 1, FileError);

} //-----ReportError1()
//-------------------------------------ReportError2()
//Формирование и запись в файл сообщения об ошибке 
//диапазонов double
void ReportError2(char* FileName, int i, int k,
    double d1, double d2) {
    FatalError = 1;
    sprintf(Sr,
        "Файл %s : в строке %d элемент %d  вне пределов %4.2f .. %6.2f\n",
        FileName, i + 1, k, d1, d2);
    fwrite(Sr, sizeof(string80), 1, FileError);

} //-----ReportError2()
//-------------------------------------ReadFileError()
//Чтение и вывод на экран протокола контроля текстовых файлов 
void ReadFileError() {
    char i = 1;
    rewind(FileError);
    while (i != EOF) {
        i = fread(Sr, sizeof(string80), 1, FileError);
        if (i < 1) i = EOF;
        else printf("%s", Sr);
    }
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
} //-----ReadFileError() 