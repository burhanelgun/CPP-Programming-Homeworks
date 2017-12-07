#include <iostream> //gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>

#include "ConnectFourPlusUndo.h"
#include "ConnectFourPlus.h"


using namespace std;
using namespace Oyun; // kendi namespacesim

ConnectFourPlusUndo::ConnectFourPlusUndo(){          //constructor 1(5 e 5 lik olusturan)
	rowSize=5;
	columnSize=5;
}

ConnectFourPlusUndo::ConnectFourPlusUndo(int a,int b){   // constructor 2 (gelen parametrelere gore olusturan)
	rowSize=a;
	columnSize=b;
	xAxis=new int[columnSize*rowSize];
	yAxis=new int[rowSize*columnSize];
	undoCounter=0;
}

ConnectFourPlusUndo::ConnectFourPlusUndo(string filenamee){   //constructor 3  (filename alarak olusturan)
	fileName=filenamee;  // filename alir ve data member olan filename e atarim
}	
int ConnectFourPlusUndo::undo(){ //undo yapma fonksiyonu
	if(livingCell>0){
		livingCell--;  // her yapılan undo da livingcell 1 azalır
		gameCells[yAxis[livingCell]][xAxis[livingCell]].setterCellType('*'); // ve hamle arraylerinin(xAxis, yAxis) en son elemanını kullanarak o hücrenin gameType ı * a geri çevrilir.
		yAxis[livingCell]=0; // en son hamle yok edildiği için o hamlelere 0 atadım.
		xAxis[livingCell]=0;
		displayBoard(); // boardı ekrana bastırdım.
	}
	else{ //eger hep undo yapılırsa ve en son hamleye gelinirse yani livingcell 0 olursa kullanıcı uyarılır
		cout<<"En Başa Döndünüz"<<endl;
		return 	-2;
	}

}


int ConnectFourPlusUndo::setArray( string letter, const char &mark){

	int rowCounter;
	int beraberlik=0;
	int flag=0;
	int columnCounter=0;
	rowCounter=rowSize;
	while(1){   // secilen sutuna gore tas koyma uygunlugu kontrol edilir ve uygunsa tas koyulur*/

		if(gameCells[rowCounter-1][int(letter[0])-int('A')].getterCellType()=='*' && int(letter[0])<int('A')+columnSize && int(letter[0])>=int('A')){ /* secilen sutunun rowCounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
			gameCells[rowCounter-1][int(letter[0])-int('A')].setterCellType(mark);
		
			if(gameType=='P'){   // her hamlede o hamlenin x ve  y pozisyonu sırasıyla xAxis ve yAxis arraylerine kaydedilir
				xAxis[livingCell]=int(letter[0])-int('A');
				yAxis[livingCell]=rowCounter-1;
			}
		
			livingcell(); // her hamlede livingcell arttırılır
			displayBoard();

			if(mark=='O'){
				cout<<"livingCell= "<<livingCell<<endl;
			}
			flag=controlfour(gameCells,rowSize,columnSize,rowCounter,columnCounter,letter[0],mark);
			break;
		}
		else{

			if(rowCounter>1){
	
				rowCounter--; // en alltan baslarak ilk bos olan yere tas koyulur.
			}
			else if(int(letter[0])<int('A')+rowSize && int(letter[0])>=int('A') ){  /* eger bir sutunun tamami dolmusssa ve o sutun secilmisse kullanici uyarilir ve derekli bilgiler yeniden istenir*/
				cerr<<"(1.Oyuncu) Bu Sutun Bitti Tekrar Seciniz"<<endl;
				letter = getLetter('X');
				rowCounter=rowSize;

			}

			else if(int(letter[0])-int('A')>=columnSize){       /* secilen sutun oyun alaninin disindayse kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
				cerr<<"(1.Oyuncu) Oyun Alaninin Disina Ciktiniz Tekrar Deneyiniz"<<endl;
				letter = getLetter('X');
				rowCounter=rowSize;
			}

			else{
				if(gameType!='C'){
				 /* eger i u s gibi turkce harfler kullanilirsa kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
					cerr<<"Hatali Giris Tekrar Deneyiniz"<<endl;
					letter = getLetter('X');
					rowCounter=rowSize;
				}
			}

		}
	}
	
	if((flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){ // farklı flag türlerine göre hangi durumda 4 lemenin olduğu belirlenir ve ona göre lower(kucultme) fonksiyonu cagrilir
		lower(rowSize,rowCounter,letter[0],'X',flag);
		return 1;
	}
	if((flag==14 || flag==15 || flag==16 || flag==17 || flag==18 || flag==19 || flag==20 || flag==21 || flag==22 || flag==23 || flag==24 || flag==25 || flag==26)){
		lower(rowSize,rowCounter,letter[0],'O',flag);
		return 2;
	}
	
	}
	string ConnectFourPlusUndo::getLetter(const char &mark) {
	string letter;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi return edilir*/
	getline(cin,letter);
	if(cin.eof() ){
		cout<<"Test Dosyasi Bitti"<<endl;
		exit(-1);
	}

	if((letter[0]=='L' && letter[1]=='O' && letter[2]=='A'&& letter[3]=='D') || (letter[0]=='S' && letter[1]=='A' && letter[2]=='V'&& letter[3]=='E') || (letter[0]=='U' && letter[1]=='N' && letter[2]=='D'&& letter[3]=='O')){
		//cin.ignore (1000, 'B');
	}
	while(letter.size()!=1 && letter.size()!=0 && ((letter[0]!='L' && letter[1]!='O' && letter[2]!='A'&& letter[3]!='D') && (letter[0]!='S' && letter[1]!='A' && letter[2]!='V'&& letter[3]!='E') && (letter[0]!='U' && letter[1]!='N' && letter[2]!='D'&& letter[3]!='O')) ){
		cerr<<"GECERLI BIR SUTUN GIRINIZ"<<endl;
		getline(cin,letter);
	}
	while(letter.size()==0 ){
		cerr<<"Hatali giris"<<endl;
		cerr<<"Sutun Harfi Seciniz"<<endl;
		getline(cin,letter);
	}
	if (letter[0] >= 'a' && letter[0] <= 'z') {  /* alinan harf bilgisi kucgkse buyultulur*/
		letter[0] = letter[0] -'a'+'A';
	}
	return letter;
}

string ConnectFourPlusUndo::writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi) {
	int i=0;
	int j=0;
	string filename;

	ofstream dosya;

	for(i=5, j=0; letter[i]!='.'; i++,j++){   /* writeFile komutundan sonra . olana kadar yada null karaktere kadar kontrol edilir ve filename string ine atilir*/
		if(letter[i]=='\0'){
			break;
		}
		filename[j]=letter[i];
	}
	filename[j]='.';    /* stringin sonuna .txt uzantisi eklenir*/
	filename[j+1]='T';
	filename[j+2]='X';
	filename[j+3]='T';
	filename[j+4]='\0';

	dosya.open(filename);    /* dosya acilir*/


	dosya<<columnSize<<endl;   /* dosyaya size bilgisi girilir*/
	dosya<<rowSize<<endl;   /* dosyaya size bilgisi girilir*/

	dosya<<gametipi<<endl;;   /* dosyaya hangi oyunnun oynandigi bilgisi girilir*/

	dosya<<mark<<endl;   /*dosyaya siranin kacinci oyuncuda oldugu bilgisi girilir*/
	dosya<<livingCell<<endl;;   /* livingcell bilgisi girilir*/



	for(char c = 'a' ,i = 0; c <= 'z', i<columnSize; ++c,i++){	/* girilen size kadar a dan baslanarak alfabe sirasiyla dosyaya print edilir*/	
		if(i == 0){
			dosya<<c;
		}	
		else{
			dosya<<c;
		}
	}   	
	dosya<<endl;


	for(int j=0 ; j<rowSize; j++){ /* alfabenin altina sizexsize lik bir map dosyaya print edilir*/
		for(int k=0; k<columnSize; k++){
			dosya<<gameCells[j][k].getterCellType();
			cout<<gameCells[j][k].getterCellType();
			//cout<<" ";
		}
		dosya<<endl;
		cout<<endl;
	}	
	for(int i=0;i<rowSize*columnSize;i++){ // dosyaya o oyunun x hamleleri kaydedilir
		dosya<<xAxis[i]<<endl;
	}		
	for(int i=0;i<rowSize*columnSize;i++){ // dosyaya o oyunun y hamleleri kaydedilir
		dosya<<yAxis[i]<<endl;
	}				
	dosya<<undoCounter; // dosyaya o oyunun kaç defa undo yapıldığı yazılır
	dosya.close();   /* dosya kapatilir*/
	cout<<"Sutun Harfi Seciniz"<<endl;
	cin.clear();


	letter = getLetter('X');     /* kullanicidan harf almaya devam edilir*/
	return letter;

}
char ConnectFourPlusUndo::readFile(string letter) {
	int i=0;
	int j=0;
	string filename1;
	char sira;
	char a;

	char temp[1000];   /* temp arrayi */

	ifstream dosya;   /* okumak icin dosya*/

	for(i=5, j=0; letter[i]!='.'; i++,j++){   /* readFile dan sonra gelen kelimeden sonra noktaya kadar yada keliemninin sonuna kadar kontrol edilir*/
		if(letter[i]=='\0'){
			break;
		}
		filename1[j]=letter[i];

	}

	filename1[j]='.';     /* dosya adinin sonuna .txt uzantisi koyulur*/
	filename1[j+1]='T';
	filename1[j+2]='X';
	filename1[j+3]='T';
	filename1[j+4]='\0';

	dosya.open(filename1);

	
	dosya>>columnSize;    /* dosyadan size bilgisi okunur*/
	dosya>>rowSize;
	dosya>>gameType;    /*dosyadan oyun tipi bilgisi okunur*/
	dosya>>sira;       // hangi kullanıcıdayken kayıt edildiyse ondan başlamak için sıra bilgisi okunur
	dosya>>livingCell;  // livingcell okunur dosyadan

	
	for(int l=0;l<columnSize;l++){   /* dosyanin icindeki a b c d gibi harfleri temp arrayine attim*/
			dosya>>temp[l];
	}

	//rowSize++;


	gameCells = new Cell*[rowSize]; // yeni yer alınır yeni rowSize ve columSize a göre

	for(int i=0; i<rowSize ; i++){
		gameCells[i] = new Cell[columnSize];
	}

	for(int j=0 ; j<rowSize ; j++){ // doaydan okunan hücre bilgilerine göre gameCells doldurulur
			for(int k=0; k<columnSize; k++){
				dosya>>a;
				gameCells[j][k].setterCellType(a);
			}
	}	

	for(int i=0;i<columnSize*rowSize;i++){ // xAxis arrayine x ekseninin hamleleri yazılır
		dosya>>xAxis[i];
	}

	for(int i=0;i<columnSize*rowSize;i++){ // yAxis arrayine y ekseninin hamleleri yazılır
		dosya>>yAxis[i];
	}
	dosya>>undoCounter;  // undoCounter dosyadan okunur

	displayBoard();

	if(gameType=='C'){
		int counter=0;
		while(1){

			displayBoard();

			cout<<"Sutun Harfi Seciniz"<<endl;
			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
			if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
				
				writeFile(rowSize,columnSize,letter,'X','C');
					
			}
			if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
				
				if(readFile(letter)==-3){
						return -3;
					}
					
			}

			if(setArray(letter,'X')==1){ //hamle map e set edilir
				displayBoard();
				cout<<"Oyuncu kazandi"<<endl;	
				return -3 ;
			}
			cout<<endl;

			if(emptyMapControl(gameCells,rowSize,columnSize)==-2){ // map boşmu diye kontrol edilir
				cout<<"Kazanan Yok"<<endl;	
				break;
			}

			if(compSetArray(rowSize,columnSize)==0){  // bilgisayar oynar
				break;
			}

		}	
		return -3;
	}
	else if(gameType=='P'){ // oyun tipi P ise
		if(sira=='X'){  // sıra X te ise
			while(1){
				cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;
				letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
				
				if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger SAVE komutu girilirse*/
					
					writeFile(rowSize,columnSize,letter,'X','P');
						
				}
				if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger LOAD komutu girilirse*/

					if(readFile(letter)==-3){
						return -3;
					}	
				}
				if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger UNDO komutu girilirse*/
					if(undo()==-2){ // undo fonksiiyonu çağrılır

						return -3;
					}

				}
				if(letter!="UNDO"){ // undo cagrılmadıysa kazanma durumlarına bakılır ve setyapılır
				if(setArray(letter,'X')==1){
					displayBoard();
					cout<<"1.oyuncu kazandi"<<endl;	
					return -3;
				}}

				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){ // map doluluğu kontrol edilir
					cout<<"Kazanan Yok"<<endl;	
					break;
				}

				cout<<"(2.Oyuncu) Sutun Harfi Seciniz"<<endl;
				letter = getLetter('O');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
				if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger SAVE komutu girilirse*/
					
					writeFile(rowSize,columnSize,letter,'O','P');
						
				}
				if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger LOAD komutu girilirse*/
					
					if(readFile(letter)==-3){
						return -3;
					}	
						
				}
				if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger UNDO komutu girilirse*/
					if(undo()==-2){ // undo fonksiyonu cagrılır
						return -3;
					}
				}
				if(letter!="UNDO"){// undo komutu girilmediyse kazanma durumlarına bakılır ve setyapılır
					if(setArray(letter,'O')==2){
						displayBoard();

						cout<<"2.oyuncu kazandi"<<endl;	
						return -3;
					}
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){ // map doluluğu kontrol edilir
					cout<<"Kazanan Yok"<<endl;	
					break;
				}


			}
			return -3;
		}
		if(sira=='O'){ // sıra O ise
			while(1){
				cout<<"(2.Oyuncu) Sutun Harfi Seciniz"<<endl;
				letter = getLetter('O');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
				if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
					
					writeFile(rowSize,columnSize,letter,'O','P');
						
				}
				if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
					
					if(readFile(letter)==-3){
						return -3;
					}	
						
				}
				if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger writeFile komutu girilirse*/
					if(undo()==-2){
						return -3;
					}
					return 99;
				}
				if(letter!="UNDO"){// undo komutu girilmediyse kazanma durumlarına bakılır ve setyapılır
					if(setArray(letter,'O')==2){
						displayBoard();
						cout<<"2.oyuncu kazandi"<<endl;	
						break;
					}
				}

				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){ // map doluluğu kontrol edilir
					cout<<"Kazanan Yok"<<endl;	
					break;
				}


				cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;
				letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
				
				if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
					
					writeFile(rowSize,columnSize,letter,'X','P');
						
				}
				if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/

					if(readFile(letter)==-3){
						return -3;
					}	
				}
				if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger writeFile komutu girilirse*/
					if(undo()==-2){
						return -3;
					}
					return 99;
				}
				if(letter!="UNDO"){ // undo komutu girilmediyse kazanma durumlarına bakılır ve setyapılır

					if(setArray(letter,'X')==1){
						displayBoard();
						cout<<"1.oyuncu kazandi"<<endl;	
						return -3;
					}
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){// map doluluğu kontrol edilir
					cout<<"Kazanan Yok"<<endl;	
					break;
				}

			}
			return -3;
		}

	}

	return gameType;		/* oyun tipi return edilir*/
}
int ConnectFourPlusUndo::playX( string letter,char gameType){ // tekli modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir

	int a=1;
	char sira='X';
		
	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger SAVE komutu girilirse*/
		writeFile(rowSize,columnSize,letter,sira,gameType);
			
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger LOAD komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}
	if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger UNDO komutu girilirse*/
		if(gameType=='P'){ // oyun tipi P ise undo çağrılır
			if(undo()==-2){
				return -3;
			}
			return 99;
		}

		return -98;


	}
	int d=setArray(letter,sira); // hamle map e set edilir
	if(d==1){
		displayBoard();
		cout<<"1.oyuncu kazandi"<<endl;	
		return a;
	}
	else if(d==2){
		displayBoard();
		cout<<"2.oyuncu kazandi"<<endl;	
		return a;
	}


	//game1.displayBoard();
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return 1;
	}
	return -5;
	
}
int  ConnectFourPlusUndo::playO(  string letter,const  char &gameType){ // tekli modda 2. ouncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir

	int a=2;
	char sira='O';
	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger SAVE komutu girilirse*/

		letter =writeFile(rowSize,columnSize,letter,sira,gameType);	
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger LOAD komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}

	if(letter[0]=='U' && letter[1]=='N' && letter[2]=='D' && letter[3]=='O'){/* eger UNDO komutu girilirse*/
		if(undo()==-2){
			return -99;
		}
		return 99;

	}

	int d=setArray(letter,sira); // hamle map e set edilir
	if(d==1){
		displayBoard();
		cout<<"1.oyuncu kazandi"<<endl;	
		return a;
	}
	else if(d==2){
		displayBoard();
		cout<<"2.oyuncu kazandi"<<endl;	
		return a;
	}
	//game1.displayBoard();
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){ //map doluluğu kontrol edilir
		cout<<"Kazanan Yok"<<endl;	
		return 1;
	}
	return -5;
}
