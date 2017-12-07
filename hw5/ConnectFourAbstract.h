#ifndef CONNECTFOURABSTRACT_H_
#define CONNECTFOURABSTRACT_H_

#include <iostream>//gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


#include "Cell.h"


using namespace std;

namespace Oyun {// kendi namespacesim
	class ConnectFourAbstract{
	protected:
		
		Cell** gameCells; //ConnectFourAbstract clasi icin private data memberlar
		int rowSize;
		int columnSize;
		char gameType;
		string fileName;
		static int livingCell;    /* livingCell sayisini tutar*/

		int  compSetArray(const int &rowSize, const int &columnSize)const;   //bilgisayarin boarda tas koymasini saglayan fonskiyon


	public:

		ConnectFourAbstract();        //constructor 1(5 e 5 lik olusturan)
		

		ConnectFourAbstract(int a,int b);   // constructor 2 (gelen parametrelere gore olusturan)

		ConnectFourAbstract(string filenamee);   //constructor 3  (filename alarak olusturan)

		ConnectFourAbstract(const ConnectFourAbstract & D); // copy constructor
		~ConnectFourAbstract();       // destructor
		ConnectFourAbstract& operator = (const ConnectFourAbstract &D );  //overloaded assigment operator


		int  playGame();   //oyunu temel olarak oynatan fonksiyon

		int  play();  /*bilgisayar oynar 1 kez*/

		void  initArray(const int &row, const int &column);    //baslangicta vektoru initialize etmek icin gerekli fonksiyon

		void initArray();  // filename alan constructor kullanildiginda cagrilan fonksiyon

		void  displayBoard()const ;     /*ekranda guncel boardi gosteriri*/


		virtual string  getLetter( const char &mark);	//kullanicidan sutun harfi alinan fonskiyon (redifine edildiği için virtual yaptım)

		virtual int  controlfour( Cell** gameCells, const int &rowSize, const int &columnSize,const int &rowrowCounter,const int &columnrowCounter,const char &letter, const char &cursor)const ;  //4 lu durum olusmusmu diye kontrol eden fonksiyon(redifine edildiği için virtual yaptım)

		virtual string  writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi) ;   // dosyaya yazma write fonskiyonu(SAVE)(redifine edildiği için virtual yaptım)

		virtual char  readFile(string letter);   // dosyadan okuma read (LOAD) fonksiyonu(redifine edildiği için virtual yaptım)

		virtual int  playO(string letter, const char &gameType);  /*1. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alir)*/ //(redifine edildiği için virtual yaptım)

		virtual int  playX( string letter, char gameType);  /*2. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alir)*/ //(redifine edildiği için virtual yaptım)

		virtual int  setArray(string letter,const char &mark);   //vektore tas eklemek icin gerekli fonksiyon (redifine edildiği için virtual yaptım)


		inline char   GetterLetter()const;      //inline fonskiyonlar(setter getter)
		
		inline void   SetterLetter(const char &letter)const;
			
		inline void   SetterRowNumber(const char &rowNumber)const;
		
		inline int   GetterRowNumber()const;
		
		inline void   SetterCellType(const int &cellType)const;
			
		inline char GetterCellType()const;
		
		inline int GetterColumnSize()const ;      //inline fonskiyonlar(setter getter)
			
		inline void SetterColumnSize(const int coulmnn);

		inline int GetterRowSize() const;

		inline void SetterRowSize(const int roww);

		inline string getterFileName()const;       //inline fonskiyonlar(setter getter)
		

		int   getGameType(void);      // oyun tipini kullanicidan alir

		inline char getterGameType() ;   //inline fonskiyonlar(setter getter)
		
		inline void setterGameType( char gameTypee);

		int   inputHeightSize();    	/*board height size ini return eder*/

		int   inputWidhtSize();  		/*board widht size ini return eder*/

		string inputFileName();   //kullanicidan dosya adini alan fonksiyon

		static int   livingcell();     // livingcell sayisini arrtirmak icin gerekli fonskiyon, ve current livingcell return eder

		bool  compare(const ConnectFourAbstract &obje)  ;  /* ilk obje parametre olarak gonderilen objeye gore daha iyiyse  true return eder, daha kotuyse false return eder.(daha iyinin anlami daha fazla 3 lu X sayisinin olmasidir)*/

		int  playGame(const char &gameMode);   //oyunu temel olarak oynaatan fonksiyon

		int  playO(const char &gameMode, const string &letter); // ikinci oyuncunun bir hamle yapmasi icin gerekli fonksiyon

		int  playX(const char &gameMode, const string &letter); // birinci oyuncunun bir hamle yapmasi icin gerekli fonksiyon

		int  play(const char &gameMode);  // bilgisayarin bir hamle yapmasi icin gerekli fonksiyon

		int  emptyMapControl(Cell** gameCells, const int &rowSize, const int &columnSize)const ; //boardda bos yer varmi diye kontrol eden fonksiyon

		int  lower(const int &rowSize,const int &rowCounter,char = 'A',char = 'O',int = 0)const;  //kazanma durumda kazanmayi saglayan taslari kucultme fonksiyonu

		bool operator==(const ConnectFourAbstract &other);  // == operatoru overloading(ConnectFourAbstract classi icin)

		Cell** getVec() const;      // iki boyutlu vektore erisebilmek icin gerekli vektor

		bool operator!=(const ConnectFourAbstract &other); // != operatoru overloading(ConnectFourAbstract classi icin)
		

		
	};
}


#endif