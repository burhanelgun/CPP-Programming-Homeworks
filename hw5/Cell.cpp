#include <iostream> //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>

#include "Cell.h"

using namespace std;
using namespace Oyun; // kendi namespacesim

Cell::Cell(char letterr,int rowNumberr,int cellTypee){
	letter=letterr;  //parametrelere ilklendirmeler yapilir
	rowNumber=rowNumberr;
	cellType=cellTypee;
}

bool Cell::operator==(const Cell &other){   // Cell clasi icin == operator overloadi
		return ((letter==other.letter) && (rowNumber==other.rowNumber) && (cellType==other.cellType)); // sutun ve satir(konum) ile cellTipi ayniysa iki cell esittir 1 return eder
	}
	bool Cell::operator!=(const Cell &other){  // Cell clasi icin != operator overloadi
		return ((letter!=other.letter) || (rowNumber!=other.rowNumber) || (cellType!=other.cellType));  // eger cell data memerlarindan biri farkliysa iki cell bir birinden farklidir ve 1 return eder
	}
	ostream &operator<<( ostream &output, const Cell &other ); // stream insertion operator overloadin

   	istream &operator>>( istream  &input, Cell &other ); // stream extraction operator everloading


Cell& Cell::operator++ (){ //pre increment operator overloading
	
	if (cellType=='*'){  // empty(*) ise user1(X) yapar
			cellType='X';
	}
	else if (cellType=='X'){  // user 1(X) ise user2(O) yapar
			cellType='O';
	}
	else if (cellType=='O'){  //user2(O) ise computer(C) yapar
			cellType='C';
	}
	else if (cellType=='C'){ // computer(C) ise empty(*)yapar
			cellType='*';
	}
	return *this;
}

Cell& Cell::operator-- (){//pre decrement operator overloading
	

	if (cellType=='*'){  // empty(*) ise user1(X) yapar
			cellType='X';
	}
	else if (cellType=='O'){ // user2(O) ise user1(X) yapar
			cellType='X';
	}
	else if (cellType=='C'){  // computer(C) ise user2(O) yapar
			cellType='O';
	}
	else if (cellType=='*'){ // emtpy(*) ise computer(C) yapar
			cellType='C';
	}
	return *this;
}

Cell Cell::operator++ (const int x){ //post increment operator overloading
	Cell c;
	c.cellType=cellType;
	if (c.cellType=='*'){ // empty(*) ise user1(X) yapar
			cellType='X';
	}
	else if (c.cellType=='X'){// user 1(X) ise user2(O) yapar
			cellType='O';
	}
	else if (c.cellType=='O'){//user2(O) ise computer(C) yapar
			cellType='C';
	}
	else if (c.cellType=='C'){// computer(C) ise empty(*)yapar
			c.cellType='*';
	}
	return c;
}

Cell Cell::operator-- (const int x){//post decrement operator overloading
	Cell c;
	c.cellType=cellType;

	if (cellType=='*'){// empty(*) ise user1(X) yapar
			cellType='X';
	}
	else if (cellType=='O'){// user2(O) ise user1(X) yapar
			cellType='X';
	}
	else if (cellType=='C'){  // computer(C) ise user2(O) yapar
			cellType='O';
	}
	else if (cellType=='*'){// emtpy(*) ise computer(C) yapar
			cellType='C';
	}
	return c;
}

void  Cell::setterLetter(const char &letterr){  // fonksiyonlar(setter getter)
	letter=letterr;
}

char  Cell::getterLetter()const {
	return letter;
}
	
void  Cell::setterRowNumber(const char &rowNumberr){
	rowNumber=rowNumberr;
}

int Cell::getterRowNumber() const {
	return rowNumber;
}

void  Cell::setterCellType(const int &cellTypee) {
	cellType=cellTypee;
}

char  Cell::getterCellType()const {
	return cellType;
}