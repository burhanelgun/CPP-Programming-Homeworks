#ifndef CONNECTFOURPLUSUNDO_H_
#define CONNECTFOURPLUSUNDO_H_

#include <iostream> //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>

#include "ConnectFourPlus.h"

using namespace std;

namespace Oyun{ // kendi namespacesim

	class ConnectFourPlusUndo:public ConnectFourPlus{  // ConnectFourPlus classından türer
	public:
		ConnectFourPlusUndo();//constructor 1(5 e 5 lik olusturan)

		ConnectFourPlusUndo(int a,int b);  // constructor 2 (gelen parametrelere gore olusturan)

		ConnectFourPlusUndo(string filenamee);  //constructor 3  (filename alarak olusturan)
		
		string getLetter(const char &mark); //(redifine)

		int playX( string letter,char gameType); // tekli modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir(redifine)

	    int playO(  string letter,const  char &gameType); // tekli modda 2. ouncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir(redifine)
		
		int setArray( string letter, const char &mark);  //(redifine)

		string writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi); //save komutu için fonksiyon(redifine)

		char readFile(string letter);//load komutu için gerekli fonksiyon (redifine)

		int undo(); // undo yapan fonksiyon

	protected:
		int *xAxis;// x ekseninde yapılan hamleleri tutar(undo yapabilmek için)
		int *yAxis;// y ekseninde yapılan hamleleri tutar(undo yapabilmek için)
		int undoCounter;// her bir undo yapılışında o undo sayısını tutar
	};

}

#endif