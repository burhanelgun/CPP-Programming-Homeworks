#include <iostream>   //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>

#include "Cell.h" 
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"
#include "ConnectFourDiag.h"

using namespace std;
using namespace Oyun;   // kendi namecpacesim

int ConnectFourAbstract::livingCell = 0;   // statik degiskeni ilklendirme

int main(){

	char gameMode; //degiskenler
	int rowSize;
	int columnSize;

	cout<<"Oyun Modu Seciniz =";// oyun modu alinir
	cin>>gameMode;
	cin.ignore();

	
	while(gameMode!='P' && gameMode!='P' && gameMode!='D' && gameMode!='d' && gameMode!='U' && gameMode!='u'){  //hata durumu kontrolu
		cerr<<"Hatali Giris Yapiniz"<<endl;
		cout<<"Oyun Modu Seciniz =";
		cin>>gameMode;  // oyun modu alinir
	}	

	cout<<"En giriniz = ";
	cin>>columnSize;
	cout<<"Boy giriniz = ";
	cin>>rowSize;


	if(gameMode=='P' || gameMode=='p'){  //game mode P ise ConnectFourPlus objesi oluşturulur
		gameMode='P';
		ConnectFourPlus game0(rowSize,columnSize); // rowSize Columsize a göre obje oluşturulur
		game0.initArray(rowSize,columnSize); // array olusturulur
		game0.displayBoard(); //array ekrana basilir
		game0.playGame(); // oyun ilk adim baslar(X ve O)
	}
	if(gameMode=='D' || gameMode=='d'){  //game mode D ise ConnectFourDiag objesi oluşturulur
		gameMode='D';
		ConnectFourDiag game0(rowSize,columnSize); // rowSize Columsize a göre obje oluşturulur
		game0.initArray(rowSize,columnSize); // array olusturulur
		game0.displayBoard(); //array ekrana basilir
		game0.playGame(); // oyun ilk adim baslar(X ve O)
	}
	if(gameMode=='U' || gameMode=='u'){ //game mode U ise ConnectFourPlusUndo objesi oluşturulur
	
		gameMode='U';
		ConnectFourPlusUndo game0(rowSize,columnSize); // rowSize Columsize a göre obje oluşturulur
		game0.initArray(rowSize,columnSize); // array olusturulur
		game0.displayBoard(); //array ekrana basilir
		game0.playGame(); // oyun ilk adim baslar(X ve O)
	}
	return 0;
}