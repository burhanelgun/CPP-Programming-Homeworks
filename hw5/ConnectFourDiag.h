#ifndef CONNECTFOURDIAG_H_
#define CONNECTFOURDIAG_H_

#include <iostream> //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


#include "ConnectFourAbstract.h"



using namespace std;

namespace Oyun{ // kendi namespacesim

	class ConnectFourDiag:public ConnectFourAbstract{ 
	public:
		
		ConnectFourDiag();         //constructor 1(5 e 5 lik olusturan)

		ConnectFourDiag(int a,int b);   // constructor 2 (gelen parametrelere gore olusturan)

		ConnectFourDiag(string filenamee);  //constructor 3  (filename alarak olusturan)

		int  controlfour( Cell** gameCells, const int &rowSize, const int &columnSize,const int &rowrowCounter,const int &columnrowCounter,const char &letter, const char &cursor)const ;  //4 lu durum olusmusmu diye kontrol eden fonksiyon

	};
}

#endif