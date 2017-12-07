#ifndef CELL_H_
#define CELL_H_

#include <iostream> //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


using namespace std;

namespace Oyun{ // kendi namespacesim

	class Cell{
	public:

		Cell(){}   // cell constructorlari
		Cell(char letter,int rowNumber,int cellType);

		bool operator==(const Cell &other);  // Cell clasi icin == operator overloadi
		bool operator!=(const Cell &other);  // Cell clasi icin != operator overloadi



		Cell& operator++ (); //pre increment operator overloading

		Cell& operator-- (); //pre decrement operator overloading
		
		Cell operator++ (const int x); //post increment operator overloading
		
		Cell operator-- (const int x); //post decrement operator overloading
		

		
		friend ostream &operator<<( ostream &output, const Cell &other ) {  // stream insertion operator overloadin
			output<<"cellType= "<<other.cellType<<endl;
			output<<"letter= "<<other.letter<<endl;
			output<<"rowNumber= "<<other.rowNumber<<endl;
			return output;
			}

	    friend istream &operator>>( istream  &input, Cell &other ) { // stream extraction operator everloading
	        input>>other.cellType;
	        input>>other.letter;
	        input>>other.rowNumber;
	        return input;
	    }
	 

		 void  setterLetter(const char &letterr);  // fonksiyonlar(setter getter)

		 char  getterLetter()const;
		
		 void  setterRowNumber(const char &rowNumberr);
		
		 int  getterRowNumber() const;

		 void  setterCellType(const int &cellTypee);

		 char  getterCellType()const;

		private:      // Cell classi icin private data memberlar
			char letter; // pozisyon(X ekseni) tutar
			int rowNumber;// pozisyon(Y ekseni) tutar
			char cellType;//hücre tipini tutar(X,O )
	};
}

#endif