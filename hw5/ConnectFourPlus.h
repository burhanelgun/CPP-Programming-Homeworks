#ifndef CONNECTFOURPLUS_H_
#define CONNECTFOURPLUS_H_

#include <iostream>//gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


#include "ConnectFourAbstract.h"

using namespace std;// kendi namespacesim

namespace Oyun{ // kendi namespacesim

	class ConnectFourPlus:public ConnectFourAbstract{ // ConnectFourAbstract classından türer.
	public:
		ConnectFourPlus();        //constructor 1(5 e 5 lik olusturan)

		ConnectFourPlus(int a,int b);  // constructor 2 (gelen parametrelere gore olusturan)

		ConnectFourPlus(string filenamee);   //constructor 3  (filename alarak olusturan)

		int  controlfour( Cell** gameCells, const int &rowSize, const int &columnSize,const int &rowrowCounter,const int &columnrowCounter,const char &letter, const char &cursor)const ;  //4 lu durum olusmusmu diye kontrol eden fonksiyon(Sadece plus durumu için)(redifine)
	};
}

#endif