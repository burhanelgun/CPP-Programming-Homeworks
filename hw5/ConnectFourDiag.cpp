#include <iostream>//gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


#include "Cell.h" 
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"

using namespace std;
using namespace Oyun;// kendi namespacesim
ConnectFourDiag::ConnectFourDiag(){          //constructor 1(5 e 5 lik olusturan)
	rowSize=5;
	columnSize=5;
}

ConnectFourDiag::ConnectFourDiag(int a,int b){   // constructor 2 (gelen parametrelere gore olusturan)
	rowSize=a;
	columnSize=b;
}

ConnectFourDiag::ConnectFourDiag(string filenamee){   //constructor 3  (filename alarak olusturan)

	fileName=filenamee;  // filename alir ve data member olan filename e atarim
}

int ConnectFourDiag::controlfour( Cell **gameCells, const int &rowSize, const int &columnSize, const int &rowCounter,const int &columnCounter,const char &letter, const char &cursor) const{
	int flag=0;

	/*her yeni bir tas koyuldugunda sol capraz sekilde 4 farkli durum icin 4 lu durum saglanmismi diye kontrol edilir*/
	if(rowCounter-1>=3 && int(letter)-int('A')>=3 && rowSize-1>=rowCounter-1 && rowSize-1>=int(letter)-int('A') ){
		if(gameCells[rowCounter-1-3][int(letter)-int('A')-3].getterCellType()==cursor && gameCells[rowCounter-1-2][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1-1][int(letter)-int('A')-1].getterCellType()==cursor){
				flag=6;
					
		}
	}

	if(rowCounter-1>=2 && int(letter)-int('A')>=2 && rowSize-2>=rowCounter-1 && rowSize-2>=int(letter)-int('A')){
		if(gameCells[rowCounter-1-2][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1-1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1+1][int(letter)-int('A')+1].getterCellType()==cursor){
			flag=7;
				
		}
	}

	if(rowCounter-1>=1 && int(letter)-int('A')>=1 && rowSize-3>=rowCounter-1 && rowSize-3>=int(letter)-int('A') ){
		if(gameCells[rowCounter-1-1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1+1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1+2][int(letter)-int('A')+2].getterCellType()==cursor){
			flag=8;
				
		}
	}


	if(rowCounter-1>=0 && int(letter)-int('A')>=0 && rowSize-4>=rowCounter-1 && rowSize-4>=int(letter)-int('A') ){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1+2][int(letter)-int('A')+2].getterCellType()==cursor && gameCells[rowCounter-1+3][int(letter)-int('A')+3].getterCellType()==cursor){
			flag=9;
				
		}
	}




	/*her yeni bir tas koyuldugunda sag capraz sekilde 4 farkli durum icin 4 lu durum saglanmismi diye kontrol edilir*/

	if(rowCounter-1>=3 && int(letter)-int('A')<=rowSize-4 && rowSize-1>=rowCounter-1 && 0<=int(letter)-int('A')){
		if(gameCells[rowCounter-1-3][int(letter)-int('A')+3].getterCellType()==cursor && gameCells[rowCounter-1-2][int(letter)-int('A')+2].getterCellType()==cursor && gameCells[rowCounter-1-1][int(letter)-int('A')+1].getterCellType()==cursor){
			flag=10;	
				
		}
	}


	if(rowCounter-1>=2 && int(letter)-int('A')<=rowSize-3 && rowSize-2>=rowCounter-1 && 1<=int(letter)-int('A')){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1-1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1-2][int(letter)-int('A')+2].getterCellType()==cursor){
			flag=11;	
				
		}
	}


	if(rowCounter-1>=1 && int(letter)-int('A')<=rowSize-2 && rowSize-3>=rowCounter-1 && 2<=int(letter)-int('A')){
		if(gameCells[rowCounter-1+2][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1-1][int(letter)-int('A')+1].getterCellType()==cursor && gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()==cursor){
			flag=12;	
				
		}
	}


	if(rowCounter-1>=0 && int(letter)-int('A')<=rowSize-1 && rowSize-4>=rowCounter-1 && 3<=int(letter)-int('A')){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()==cursor && gameCells[rowCounter-1+2][int(letter)-int('A')-2].getterCellType()==cursor && gameCells[rowCounter-1+3][int(letter)-int('A')-3].getterCellType()==cursor){
			flag=13;	
				
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


