//Модуль сервисных функций
#include "desunit.h"
 //---------------------------------------wait_press_key()
//Вывод сообщения на экран и ожидание нажатия клавиши
void wait_press_key(char* msg) {
    fflush(stdin);
    printf(msg);
    _getch();
} //-----wait_press_key()
//----------------------------------------WritelnString()
//Вывод строки S на экран, и в файл
void WritelnString(char S[80]) {
    printf("%s\n", S);
    if (Device == 1) //Флаг записи строки в файл
        fprintf(fRes, "%s\n", S);
} //-----WritelnString() 
//------------------------------------------FillString()
//Дополнение строки S до длины len пробелами слева (pk=0) 
//или справа (pk=1). Возвращает указатель на строку 
char* FillString(char* S, unsigned char len, unsigned char pk) {
    unsigned char i,
        n = strlen(S); //длина исходной строки
    char St[35] = ""; //рабочая строка
    if (S[n - 1] == ' ') S[n - 1] = '\0'; //добавление конца строки
    n = strlen(S);
    if (n < len) //длина исходной строки меньше заданной 
    {
        for (i = 1; i < len - n; i++)
            if (pk == 0)
                strcat(St, " "); //формирование пробелов слева
            else
                strcat(S, " "); //добавление пробелов справа
    }
    //формирование итоговой строки с пробелами слева
    if (pk == 0) {
        strcat(St, S);
        strcpy(S, St);
    }
    return S;
} //-----FillString() 
//------------------------------------------GetNumber()
// Ввод числа с клавиатуры с контролем; 
//MinNumber,MaxNumber - допустимый диапазон чисел; 
//m1,n1,m2,n2 - кол-во цифр в числе и дробной части
//для строки форматов в печати сообщения о диапазоне 
//Возвращает введенное число в формате double
double GetNumber(double MinNumber, double MaxNumber,
    char m1, char n1, char m2, char n2) {
    double Number;
    unsigned char Cond = 0;
    char Format[80] = "от %", //строка форматов
        s[10] = ""; //рабочая строка
      //формирование строки форматов
    sprintf(s, "%d", m1);
    strcat(Format, s);
    strcat(Format, ".");
    sprintf(s, "%d", n1);
    strcat(Format, s);
    strcat(Format, "f до %");
    sprintf(s, "%d", m2);
    strcat(Format, s);
    strcat(Format, ".");
    sprintf(s, "%d", n2);
    strcat(Format, s);
    strcat(Format, "f.");
    do {
        Cond = 1;
        scanf("%lf", &Number); //ввод числа
        fflush(stdin); //очистка буфера клавиатуры
        if ((Number < MinNumber) || (Number > MaxNumber)) { //число выходит за указанный диапазон
            printf("Число должно быть в диапазоне ");
            printf(Format, MinNumber, MaxNumber);
            printf("\nПовторите ввод\n");
            Cond = 0;
        }
    } while (Cond == 0);
    return Number;
} //-----GetNumber()
//------------------------------------------UsesDevice()
//Запрос об устройстве для вывода результатов 
void UsesDevice() {
    printf("Укажите устройство для вывода результатов: \n");
    printf("   0 - только экран\n");
    printf("   1 - экран и текстовый файл\n");
    //целая часть числа приводится к типу int
    Device = (int)ceil(GetNumber(0, 1, 1, 0, 1, 0));
} //-----UsesDevice() 
//------------------------------------------SearchKodif()
//Двоичный поиск в массиве кодификатора Kodifs
//элемента с кодом Kod. Возвращает индекс найденного
//элемента, -1, если элемент не найден
int SearchKodif(int Kod, int nk) {
    int i1, i2, m;
    int SearchKod = -1; //возвращаемое значение
    i1 = 0;
    i2 = nk - 1; //левая и правая границы диапазона
    while (i1 <= i2) {
        m = (i1 + i2) / 2; //середина диапазона
        if (Kod == Kodifs[m].Kod) {
            SearchKod = m;
            break; //Элемент найден
        }
        else
            if (Kod > Kodifs[m].Kod)
                i1 = m + 1; //Изменение левой границы
            else
                i2 = m - 1; //Изменение правой границы
    }
    return SearchKod;
} //-----SearchKodif() 
//-------------------------------------------SortKodif()
//Сортировка кодификатора "школьным" методом 
//по возрастанию кода продукта
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
//Реверс дека изделий. Просмотр с левой стороны 
//Вставка в буферный дек с левой стороны
void ReversProduct(DynProduct** Lp, DynProduct** Rp) {
    DynProduct* LpBuf, * RpBuf; // указатели буферного дека архива 
    DynProduct* Run; // текущий указатель дека архива 
    LpBuf = RpBuf = NULL;
    while (*Lp != NULL) {
        Run = *Lp;
        *Lp = (*Lp)->Next;
        Run->Prev = NULL; //связывание указателей
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
//Чтение бинарного файла архива и формирование дека структур 
//Включение элементов в дек производится с левой стороны,
//как и в случае формирования стека
//Через параметры возвращаются количество элементов,
//указатели на левый и правый концы дека
//Функция возвращает 0, если дек создан, иначе 1
int ReadFileOut(int* np, DynProduct** Lp, DynProduct** Rp) {
    ProductType Product;
    DynProduct* Run; // текущий указатель дека архива 
    if (SignArchive == 0) //флаг 1-архив создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    if ((fArBin = fopen(fArBinName, "rb")) == NULL) { // открывается бинарный файл архива
        printf("\nФайл %s не найден. Режим отменяется.\n", fArBinName);
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        SignArchive = 0;
        return 1;
    }
    *np = 0;
    *Lp = NULL; *Rp = NULL;
    //считывание структур архива
    while (fread(&Product, sizeof(ProductType), 1, fArBin) == 1) { //выделение памяти для элемента дека
        Run = (DynProduct*)malloc(sizeof(DynProduct));
        (*np)++;
        Run->Inf = Product; //заполнение информационной части       
        Run->Next = *Lp;
        *Lp = Run;
    }
    fclose(fArBin);
    ReversProduct(Lp, Rp); // реверс стека
    return 0;
} //-----ReadFileOut() 
//-----------------------------------------DisposeProduct()
//Удаление дека изделий. Просмотр с левой стороны 
void DisposeProduct(DynProduct* Lp, DynProduct* Rp) {
    DynProduct* Run; // текущий указатель дека архива 
    while (Lp != NULL) {
        Run = Lp;
        Lp = Lp->Next;
        free(Run); //освобождение памяти
    }
} //-----DisposeProduct() 
//---------------------------------------------WriteFileOut()
//Запись структур из дека в бинарный файл архива
//Просмотр с левой стороны с последующим удалением дека 
int WriteFileOut(DynProduct* Lp, DynProduct* Rp) {
    ProductType Product;
    DynProduct* Run; // текущий указатель дека архива 
    if ((fArBin = fopen(fArBinName, "wb")) == NULL) {
        printf("\nФайл %s не создан\n", fArBinName);
        wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
        exit(0);
    }
    Run = Lp;
    while (Run != NULL) { //цикл записи структур в файл
        Product = Run->Inf;
        fwrite(&Product, sizeof(ProductType), 1, fArBin);
        Run = Run->Next;
    }
    fclose(fArBin);
    DisposeProduct(Lp, Rp); //удаление дека
    return 0;
} //-----WriteFileOut() 
//-----------------------------------------------