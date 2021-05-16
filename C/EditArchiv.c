// Изменение компонента в архиве изделий
#include "desunit.h"

#include "baseunit.h"
 // Формирование изменяемого компонента. 
void MakeComponent(ProductType* Product);

//-------------------------------------------ChangeArchive()
// Изменение компонента в архиве изделий 
// Просмотр дека слева направо
// Возвращает 1, если архив не создан, 0 - создан
int ChangeArchive() {
    int loop;
    char Kod4[11], Kod44[11];
    int np;
    unsigned char Cond = 0;
    ProductType Product;
    DynProduct* Lp; // левый и правый указатели очереди 
    DynProduct* Run; // текущий указатель очереди архива 
    if (!SignArchive) // архив не создан
    {
        printf("\nАрхив не создан. Режим отменяется.\n");
        wait_press_key("\nДля продолжения нажмите любую клавишу\n");
        return 1;
    }
    //формирование архивного дека
    ReadFileOut(&np, &Lp);
    //ввод кода изменяемого компонента
    printf("\nУкажите код изделия изменяемого компонента: ");
    scanf("%s", &Kod4);
    for (int loop = 0; loop < 10; loop++) Kod44[loop] = Kod4[loop];
    printf("Код изделия %s\n", Kod4);
    Run = Lp;
    Cond = 0;
    while (Run != NULL) //цикл поиска введенного кода в деке
    {
        if (/*Kod == Run->Inf.Kod*/ strcmp(Kod4, Run->Inf.ActualKod) == 0) { //компонент найден strcmp(str, str1) == 0
            Cond = 1;
            //считывание текущих значений 
            Product = Run->Inf;
            MakeComponent(&Product); //ввод изменений в полях
            Run->Inf = Product; //запись измененной структуры в дек
            WriteFileOut(Lp); //запись дека в архивный файл
            Lp = NULL;
            printf("Изменение компонента в архиве закончено\n");
            break;
        }
        Run = Run->Next;
    }
    if (!Cond) //компонент не найден
        printf("\nВ архиве нет компонента с кодом %s\n", Kod44);
    wait_press_key("\nДля продолжения нажмите любую клавишу\n");
    return 0;
} //-----СhangeArchive() 
//--------------------------------------------MakeComponent()
// Формирование изменяемого компонента. Перед вводом новых
//значений на экране печатаются текущие значения полей.
//Изменять можно все значения, или любое их количество.
//Если нужно изменить значение в k-ом поле, необходимо ввести
//старые значения всех предшествующих полей. Если значения
//за k-ым полем не редактируются, их старые значения вводить
//не надо. Если с клавиатуры введено меньше шести значений,
//последние поля изменяться не будут.
void MakeComponent(ProductType* Product) {
    int k = 0;
    char Sa[100];
    char* token;
    char Seps[] = " \t\n";
    FILE* typing;

    //печать на экран текущих значений
    /*
    printf("Тек.зн. %5s  %6.2f  %6.0f  %6.0f  %6.0f  %6.0f\n",
        Product->Dimens, Product->Price, Product->Plan[0],
        Product->Plan[1], Product->Fact[0], Product->Fact[1]);
    */

    printf("Тек.зн. %s  %d %s %.2f %d %d %d\n",
        Product->ActualKod, Product->Amount,Product->Dimens, Product->Price, Product->RecentlyArrived, Product->Sold, Product->Possess);
    printf("Ввести: код, кол-во, цену, количество полученных за 24 часа, проданных за 24 часа, имеющихся на складе\n");
    fflush(stdin); //очистка буфера клавиатуры
    /*
      //очистка буфера клавиатуры(если fflush(stdin) не работает)
      rewind(stdin);
    */
    // printf("ok");
    rewind(stdin);
    gets(Sa); //считывание строки с клавиатуры
    // printf("ok");

    //typing = stdin;

    //while (fgets(Sa, 100, typing)) {}

    token = strtok(Sa, Seps); //Выделение первого слова
    while (token != NULL) //цикл выделения слов из исходной строки
    { // и запись значений в поля структуры
        k++;
        switch (k) {
        case 1:
            strcpy(Product->ActualKod, token);
            FillString(Product->ActualKod, 10, 1); // пропробуй поменять 1 на 0
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
        token = strtok(NULL, Seps); //Выделение очередного слова
    }
} //-----MakeComponent()