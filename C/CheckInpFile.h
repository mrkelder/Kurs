//Контроль исходных текстовых файлов
#include "desunit.h"
#include "baseunit.h"
//-----------------------------------------------------------
//-----------------------Определение типов
//Тип string80 - 
//    массив типа char [80] 
typedef char string80[80];	        	//строка на 80 символов
//Тип FileStringAr - 
//    массив строк архива типа string80 размером PMax
typedef string80 FileStringAr[PMax];	//массив строк архива
//Тип FileStringArPtr -
//    указатель на динамический массив строк 
//    для считывания архивных данных из файла fArTxt
typedef FileStringAr *FileStringArPtr;
//Тип ProductAr - 
//    массив структур архива типа ProductType размером PMax
typedef ProductType  ProductAr[PMax]; 
//Тип ProductArPtr - 
//    указатель на динамический массив ProductAr структур архива
typedef ProductAr *ProductArPtr;

//-----------------------Определение глобальных переменных 
FILE *FileError;          // файл протокола проверок
char *FileErrorName="Error.dat";
int const  NfMax = PMax; // макс.кол-во строк в текстовом файле 
int 
	 np,              // кол-во строк в файле "input.txt"
   nd,              // кол-во строк в файле "add.txt"
   nk,				      // кол-во строк в файле "kodif.txt"
   FatalError;      // наличие ошибки в исходных данных

string80	Sr;				// сообщение об ошибке
FileStringArPtr Sf; // динамичеcкий массив строк текстового файла
//--------------------------------------------------
//Контроль текстовых файлов
void CheckFiles();
//Проверка форматов файлов "input.txt" и "add.txt"
void FormatFileProduct(FILE *F, char *FileName, int *nf,
												int Nmax, ProductAr *Prod);
//Проверка форматов файла "Kodif.txt"
void FormatFileKodif();
//Проверка наличия текстового файла, контроль количества
//строк, и удаление пустых строк 
void ReadAndCheckSpaces(FILE *F, char *FileName, int *nf,
												int Nmax);
//Проверка диапазонов параметров в "input.txt" и "add.txt"
void CheckProdDiapason(char *FileName, int nf, ProductAr *Prod);
//Проверка диапазонов параметров в "Kodif.txt" 
void CheckKodifDiapason();
//Проверка дублирования параметра Kod в файле "Kodif.txt"
void KodifParameters();
//Проверка параметров записей в файлах "input.txt" и "add.txt"
void ProdParameters(ProductAr *Prod, int n, char *FileName);
//Формирование и запись в файл сообщения об ошибке диапазонов int
void ReportError1(char *FileName, int i, int k, int d1,int d2);
//Формирование и запись в файл сообщения об ошибке 
//диапазонов double
void ReportError2(char *FileName, int i, int k, 
									double d1, double d2);
//Чтение и вывод на экран протокола контроля текстовых файлов 
void ReadFileError();
