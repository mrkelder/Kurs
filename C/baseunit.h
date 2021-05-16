//Модуль сервисных функций
//-----------------------Прототипы функций модуля 
//Вывод сообщения на экран и ожидание нажатия клавиши
void wait_press_key(char *msg);
//Вывод строки S на экран, и в файл
void WritelnString(char S[80]);
// Дополнение строки S до длины len пробелами  
char *FillString(char *S, unsigned char len, unsigned char pk);
// Ввод числа с клавиатуры с контролем; 
double GetNumber(double MinNumber, double MaxNumber, 
									char m1,char n1,char m2,char n2);
//Запрос об устройстве для вывода результатов 
void UsesDevice();
//Двоичный поиск в массиве кодификатора Kodifs
int SearchKodif(char* Kod, int nk);
//Сортировка кодификатора по возрастанию кода продукта
void SortKodif(int nk);
//Реверс дека изделий. Просмотр с левой стороны 
void ReversProduct(DynProduct **Lp);
//Чтение бинарного файла архива и формирование дека структур 
int ReadFileOut(int *np, DynProduct **Lp);
//Удаление дека изделий
void DisposeProduct(DynProduct *Lp);
//Запись структур из дека в бинарный файл архива
int WriteFileOut(DynProduct *Lp);
