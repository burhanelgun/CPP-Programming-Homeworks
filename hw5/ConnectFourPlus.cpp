#include <iostream>//gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>

#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"



using namespace std;
using namespace Oyun; // kendi namespacesim

ConnectFourPlus::ConnectFourPlus(){          //constructor 1(5 e 5 lik olusturan)
		rowSize=5;
		columnSize=5;
	}

	ConnectFourPlus::ConnectFourPlus(int a,int b){   // constructor 2 (gelen parametrelere gore olusturan)
		rowSize=a;
		columnSize=b;
	}
	ConnectFourPlus::ConnectFourPlus(string filenamee){   //constructor 3  (filename alarak olusturan)

		fileName=filenamee;  // filename alir ve data member olan filename e atarim
	}

int ConnectFourPlus::controlfour( Cell **gameCells, const int &rowSize, const int &columnSize, const int &rowCounter,const int &columnCounter,const char &letter, const char &cursor) const{ //(redifine)
	int flag=0;



	/* her yeni bir tas koyuldugunda yatayda 4 fakli durum icin 4 lu durum saglanmismi diye kontrol edilir*/
	if(gameCells[rowCounter-1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')+2].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')+3].getterCellType()==cursor){
		flag=1;
		
	}
	if(gameCells[rowCounter-1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')+2].getterCellType()==cursor){
		flag=2;
			
	}
	if(gameCells[rowCounter-1][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')+1].getterCellType()==cursor){
		flag=3;
			
	}
	if(gameCells[rowCounter-1][int(letter)-int('A')-3].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1][int(letter)-int('A')-1].getterCellType()==cursor){
		flag=4;		
	}



	/*her yeni bir tas koyuldugunda duseyde 4 lu durum saglanmismi diye kontrol edilir*/

	if(rowSize-4>=rowCounter-1){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')].getterCellType()==cursor && gameCells[rowCounter-1+2][int(letter)-int('A')].getterCellType()==cursor && gameCells[rowCounter-1+3][int(letter)-int('A')].getterCellType()==cursor){
			flag=5;
				
		}
	}


	/*flag 0 ise hic bir sekilde 4 lu durum saglanmamistir*/
	if(flag==0){
		return -1;	
	}
	/*flag 1 ile 13 arasindaysa ve cursor X ise flag return edilir*/
	if(cursor=='X' && (flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
		return flag;
	}
	/*flag 1 ile 13 arasindaysa ve cursor O ise flag+13 return edilir*/

	if(cursor=='O' && (flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
		return flag+13;
	}
	
}