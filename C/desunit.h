#pragma once
//Отключает сообщения о небезопасных функциях (4996)
#pragma warning (disable: 4996)
//#define _CRT_SECURE_NO_WARNINGS
//Глобальные описания констант, типов и переменных
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>

//имена файлов проекта
#define fArTxtName "input.txt" //Имя файла исходных документов
#define fAddTxtName  "add.txt" //Имя файла добавляемых документов
#define fKodifName "kodif.txt" //Имя файла кодификатора изделий
#define fArBinName "arhiv.bin" //Имя архивного файла изделий
#define fResName     "res.txt" //Имя файла результатов контроля

//файловые переменные проекта
FILE *fArTxt;		//файл исходных документов
FILE *fArBin;		//архивный файл изделий
FILE *fAddTxt;		//файл добавляемых документов
FILE *fKodif;		//файл кодификатора изделий
FILE *fRes;			//файл результатов контроля

typedef struct ProductT  // тип компонента архива изделий 
	{			
	char ActualKod[10];	 // код изделия 
	int Amount;          // количество штук
	char Dimens[5];      // единица измерения (шт.)
	double Price;        // цена изделия
	int RecentlyArrived; // прибывшие изделия за последние 24 часа
	int Sold;            // проданные за последние 24 часа
	int Possess;         // на складе
	} ProductType;		 //синоним типа компонента архива изделий

typedef struct KodifTyp //тип компонента кодификатора изделий 
	{				
	char ActualKod[10]; // код изделия
	char Name[100];		// наименование изделия 
	int Kod;
	} KodifType;	    //синоним типа компонента кодификатора изделий

typedef struct DynProd		  //Тип элемента дека 
	{							
		ProductType  Inf;	  //информационная часть
		struct DynProd* Next; //указатель на следующий элемент
	} DynProduct;		      //синоним типа элемента дека

#define KMax 100		//макс.кол-во компонентов кодификатора 
#define PMax 200		//макс.кол-во компонентов архива изделий 

KodifType	 Kodif,     //компонент кодификатора
		Kodifs[KMax];   //массив компонентов кодификатора

unsigned char SignArchive;  //Флаг создания архива
int nk;					            //кол-во компонентов кодификатора 

//устройство вывода результатов:
// 0 - экран; 1 - экран и диск; 
int Device;		
