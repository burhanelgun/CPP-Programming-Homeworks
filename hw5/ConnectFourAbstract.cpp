#include <iostream>//gerekli kütüphaneleri include ettim
#include <string>
#include <fstream>
#include <new>


#include "ConnectFourAbstract.h"

using namespace std;
using namespace Oyun;// kendi namespacesim

ConnectFourAbstract::ConnectFourAbstract(){          //constructor 1(5 e 5 lik olusturan)
		rowSize=5;
		columnSize=5;
}
ConnectFourAbstract::ConnectFourAbstract(int a,int b){   // constructor 2 (gelen parametrelere gore olusturan)
		rowSize=a;
		columnSize=b;
}
ConnectFourAbstract::ConnectFourAbstract(string filenamee){   //constructor 3  (filename alarak olusturan)

		fileName=filenamee;  // filename alir ve data member olan filename e atarim
}
ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract & D){ // copy constructor
	rowSize = D.rowSize; //gelen objenin data memberlari objenin kendisinin data memberlarina atanir
	columnSize = D.columnSize;
	gameType=D.gameType;
	fileName=D.fileName;
	livingCell=D.livingCell;

	gameCells = new Cell*[rowSize];  // pointer oldugu icin gameCell icin dinamik yer alinir

	for(int i=0; i<rowSize ; i++){
		gameCells[i] = new Cell[columnSize];
	}

	for(int i=0;i<rowSize;i++){    // ve ondan sonra atama islemi yapilir
		for(int j=0;j<columnSize;j++){
			gameCells[i][j]=D.gameCells[i][j];
		}
	}

}
ConnectFourAbstract::~ConnectFourAbstract(){         // destructor
    for(int i = 0; i < rowSize; ++i) {  // olusturulan objenin icinde pointer data member olan gameCells vardi ve obje oldiginde bunu delete etmeliyiz
		delete[] gameCells[i];
    }
	delete[] gameCells;
}
bool ConnectFourAbstract::operator==(const ConnectFourAbstract &other){  // == operatoru overloading(ConnectFourAbstract classi icin)

	int flag=0;

	for(int i=0;i<rowSize;i++){    // board icini tarar ve eger tum board elamanlarinin yeri ve cellTipi ayniysa flag 1 olur, bir tane bile farkli olursa flag 0 olur ve 0 return eder
		for(int j=0;j<columnSize;j++){
			if(gameCells[i][j].getterCellType()==other.gameCells[i][j].getterCellType()){
				flag=1;
			}
			else{
				flag=0;
				return 0;				}
		}
	}
	return ((rowSize==other.rowSize) && (columnSize==other.columnSize) && (gameType==other.gameType) && flag);// iki connectfourAbstract objesinin esit olmasi icin row colum sizelari,gameTypelari ve gameCellsleri(flag) ayni olmali
}
bool ConnectFourAbstract::operator!=(const ConnectFourAbstract &other){ // != operatoru overloading(ConnectFourAbstract classi icin)
	int flag=0;
	
	for(int i=0;i<rowSize;i++){  // board icini tarar ve boardda 1 tane farklilik gordugu anda flag 1 olur ve 1 return eder
		for(int j=0;j<columnSize;j++){
			if(gameCells[i][j].getterCellType()!=other.gameCells[i][j].getterCellType()){
				flag=1;
				return 1;
			}
		}
	}

	return ((rowSize!=other.rowSize) || (columnSize!=other.columnSize) || (gameType!=other.gameType) || flag);// iki connectfourAbstract objesinin farkli olmasi icin rowsize columsize gametype yada gameCellslerinden birisinin farkli olmasi yeterlidir
}
ConnectFourAbstract& ConnectFourAbstract::operator = (const ConnectFourAbstract &D ) {   //overloaded assigment operator

	if(this==&D){  // eger atanan obje kendisiyse direk kendini return eder
		return *this;
	}
	rowSize = D.rowSize;   // pointer olmayan data memberlar normal bir sekilde gelen objeden kendi objesine atanir
	columnSize = D.columnSize;
	gameType=D.gameType;
	fileName=D.fileName;
	livingCell=D.livingCell;

	for(int i = 0; i < rowSize; ++i) {  // gameCells atanmadan once kendimizin gameCelli ni delete etmeliyiz cunku artik ona ihtiyacimiz yok (memory leak olmasin diye), disaridan gelen objenin gameCellini alacagiz
		delete[] gameCells[i];
	}
	delete[] gameCells;
	gameCells = new Cell*[rowSize];  // delete ettikten sonra tekrar yeni rowSie ve columSize a gore yer aliyouz

		for(int i=0; i<rowSize ; i++){
			gameCells[i] = new Cell[columnSize];
	}

	for(int i=0;i<rowSize;i++){
		for(int j=0;j<columnSize;j++){  // ardindan sirasiyla kendi gameCellimizin ici disaridan gelen objenin gameCellsi ile dolduruyoruz
			gameCells[i][j]=D.gameCells[i][j];
		}
	}
	return *this; // kendi objemi return ederim

}

char   ConnectFourAbstract::GetterLetter()const {      // fonskiyonlar(setter getter)
	Cell obj;
	return obj.getterLetter();
}
void   ConnectFourAbstract::SetterLetter(const char &letter)const {
 	Cell obj;
	obj.setterLetter(letter);
}

void   ConnectFourAbstract::SetterRowNumber(const char &rowNumber)const {
	Cell obj;
	obj.setterRowNumber(rowNumber);

}
int   ConnectFourAbstract::GetterRowNumber()const {
		Cell obj;
		return obj.getterRowNumber();
}

void   ConnectFourAbstract::SetterCellType(const int &cellType)const {
	Cell obj;
	obj.setterCellType(cellType);
}
 char ConnectFourAbstract::GetterCellType()const {
	Cell obj;
	return obj.getterCellType();
}
Cell** ConnectFourAbstract::getVec() const {      // iki boyutlu vektore erisebilmek icin gerekli vektor
	return gameCells;
}
int ConnectFourAbstract::GetterColumnSize()const {       // fonskiyonlar(setter getter)
	return columnSize;
}
 void ConnectFourAbstract::SetterColumnSize(const int coulmnn) {
		columnSize=coulmnn;
}

 int ConnectFourAbstract::GetterRowSize() const {
	return rowSize;
}
 void ConnectFourAbstract::SetterRowSize(const int roww){
	rowSize=roww;
}
 string ConnectFourAbstract::getterFileName()const {       // fonskiyonlar(setter getter)
	return fileName;
}

 char ConnectFourAbstract::getterGameType()  {   // fonskiyonlar(setter getter)
	return gameType;
}
 void ConnectFourAbstract::setterGameType( char gameTypee){
	gameType=gameTypee;
}
int   ConnectFourAbstract::livingcell(){     // livingcell sayisini arrtirmak icin gerekli fonskiyon, ve current livingcell return eder
	livingCell++;
	return livingCell;
}

void ConnectFourAbstract::initArray(const int &columnSize, const int &rowSize){
	gameCells = new Cell*[columnSize];

	for(int i=0; i<columnSize ; i++){
		gameCells[i] = new Cell[rowSize];
	}


	for(int j=0 ; j<columnSize ; j++){
		for(int k=0; k<rowSize; k++){
			gameCells[j][k].setterCellType('*');
		}
	}
}
void ConnectFourAbstract::initArray(){

	char a;
	int satirSayisi=0;
	int enUzunSutunSayisi=0;
	int c=0;
	ifstream dosya;   /* okumak icin dosya*/
	dosya.open(fileName); // dosya acilir

	
	for(int k=0; !(dosya.eof()); k++){ // dosyanin sonuna kadar okuma yapilir
		dosya.get(a);  // dosya char char okunur
		c++;
		if(a=='\n'){   // her satirda en uzun satir sayisi na bakilir eger en uzun satir sayisindan buyukse en uzun satir sayisi guncellenir ve diger satira gecilir(\n gordukce)
			if(enUzunSutunSayisi<c){
				enUzunSutunSayisi=c;
			}
			c=0;
			satirSayisi++;  // her satirda satir sayisi arttirilir
		}
	}
	satirSayisi--;  // satir ve en uzun satir sayisi array [0] dan basladigi icin bir eksiltmem gerekti ikisinide
	enUzunSutunSayisi--;

	rowSize=satirSayisi;  // satir sayisi rowSize olur
	columnSize=enUzunSutunSayisi; // en uzun satir sayisi colum size olur
	dosya.close();	//dosya kapatilir
	
	dosya.open(fileName); // dosya tekrar acilir


	gameCells = new Cell*[rowSize];  // rowSIze ve columSize a gore dinamik olarak yer alinir.

	for(int i=0; i<rowSize ; i++){
		gameCells[i] = new Cell[columnSize];
	}

	for(int j=0 ; j<rowSize ; j++){  // dosyadan okunan boardin her bir elemani ile gameCells doldurulur
		for(int k=0; !(dosya.eof()) ; k++){ // dosya sonu gelince cikilir
			dosya.get(a);
			if(a=='\n'){ // her bir satirda diger satira gecmesi icin break yapilir.
				break;
			}
			gameCells[j][k].setterCellType(a); // dosyadan okunan her bir eleman set edilir gameCellin cellType ina.

		}
	}

	dosya.close(); // dosya kapatilir

}
void ConnectFourAbstract::displayBoard()const{

	for(char c = 'a' ,i = 0; c <= 'z', i<columnSize; ++c,i++){	/* girilen size kadar a dan baslanarak alfabe sirasiyla print edilir*/	
		if(i == 0){
			cout<<c;
		}	
		else{
			cout<<c;
		}
	}
	cout<<endl;

	for(int i=0;i<rowSize;i++){   // board ekrana basilir
		for(int j=0;j<columnSize;j++){
			cout << gameCells[i][j].getterCellType();
		}
		cout<<endl;
	}

}
int ConnectFourAbstract::setArray( string letter, const char &mark){

	int rowCounter;
	int beraberlik=0;
	int flag=0;
	int columnCounter=0;
	rowCounter=rowSize;
	while(1){   // secilen sutuna gore tas koyma uygunlugu kontrol edilir ve uygunsa tas koyulur*/

		if(gameCells[rowCounter-1][int(letter[0])-int('A')].getterCellType()=='*' && int(letter[0])<int('A')+columnSize && int(letter[0])>=int('A')){ /* secilen sutunun rowCounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
			gameCells[rowCounter-1][int(letter[0])-int('A')].setterCellType(mark);
			livingcell();
			displayBoard();

			if(mark=='O'){
				cout<<"livingCell= "<<livingCell<<endl;
			}
		
			flag=controlfour(gameCells,rowSize,columnSize,rowCounter,columnCounter,letter[0],mark);
			break;

		}
		else{

			if(rowCounter>1){
	
				rowCounter--;
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
	
	if((flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
		lower(rowSize,rowCounter,letter[0],'X',flag);
		return 1;
	}
	if((flag==14 || flag==15 || flag==16 || flag==17 || flag==18 || flag==19 || flag==20 || flag==21 || flag==22 || flag==23 || flag==24 || flag==25 || flag==26)){
		lower(rowSize,rowCounter,letter[0],'O',flag);
		return 2;
	}
	
}
string ConnectFourAbstract::inputFileName(){
	string a;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi srerun edilir*/
	cout<<"Dosya Adini Giriniz"<<endl;
	getline(cin,a);
	cout<<"a="<<a<<endl;
	return a;
	
}

int ConnectFourAbstract::inputHeightSize(){   // kullanidan height alinir

	int a = 0;
	while (a == 0 ){    /*haritanin size inin integer olmasi icin yapilan konrolun dongusu*/
		a = 1;

		cout<<"Boy Giriniz: ";
		cin >> rowSize;
		if(cin.fail()) {
			cin.clear();
			cin.ignore();
			cerr << "Lutfen Sayi Giriniz" << endl;
			a=0;
		}
		else{
			while(rowSize<4){
			cerr<<"Boy en az 4 olabilir.Tekrar Deneyin= ";
			cin >> rowSize;
			}	
		}

	}
	return rowSize;
}

int ConnectFourAbstract::inputWidhtSize(){   // kullanicidan weight alinir

	int a = 0;

	while (a == 0){    /*haritanin size inin integer olmasi icin yapilan konrolun dongusu*/
		a = 1;
		cout<<"En Giriniz: ";
		cin >> columnSize;

		if(cin.fail()) {
			cin.clear();
			cin.ignore();
			cerr << "Lutfen Sayi Giriniz" << endl;
			a=0;
		}
		else{
			while(columnSize<4){
			cerr<<"En en az 4 olabilir.Tekrar Deneyin= ";
			cin >> columnSize;
			}	
		}
	}
	return columnSize;
}


int ConnectFourAbstract::getGameType(void){
	string flag;
	cout<<"player | computer:"<<endl;     // kullanicidan oyun tipi alinir
	getline(cin,flag);

	while(flag.size()==0 ){
		getline(cin,flag);
	}
	while(flag.size()!=1 ){
		cerr<<"Gecersiz Giris Yaptiniz"<<endl;
		getline(cin,flag);
	}
	if(flag[0] == 'P' || flag[0] == 'p'){ /* kullanici P  yada p girerse user1 vs user2 oyunu baslar*/
		gameType='P';
		return 1;
	}
	else if(flag[0] == 'C' || flag[0] == 'c' ){ /* kullanici C yada c girerse user vs. computer oyunu baslar*/
		gameType='C';
		return 2;
	}
	else{   /* diger durumlarda -1 return edilir*/
		return -1;
	}
}


string ConnectFourAbstract::getLetter(const char &mark) {
	string letter;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi srerun edilir*/
	getline(cin,letter);

	if(cin.eof() ){
		cout<<"Test Dosyasi Bitti"<<endl;
		exit(-1);
	}

	if((letter[0]=='L' && letter[1]=='O' && letter[2]=='A'&& letter[3]=='D') || (letter[0]=='S' && letter[1]=='A' && letter[2]=='V'&& letter[3]=='E')){
		//cin.ignore (1000, 'B');

	}
	while(letter.size()!=1 && letter.size()!=0 && ((letter[0]!='L' && letter[1]!='O' && letter[2]!='A'&& letter[3]!='D') && (letter[0]!='S' && letter[1]!='A' && letter[2]!='V'&& letter[3]!='E')) ){
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


int ConnectFourAbstract::controlfour( Cell **gameCells, const int &rowSize, const int &columnSize, const int &rowCounter,const int &columnCounter,const char &letter, const char &cursor) const{
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
int  ConnectFourAbstract::emptyMapControl(Cell** gameCells, const int &rowSize,const int &columnSize)const {
	int flag =0;


	for(int j=0 ; j<columnSize ; j++){   /*haritanin ici dolasilir ve bosluk varmi diye bakilir eger varsa flag 1 olur ve bosluk oldugu anlasilir*/
		for(int k=0; k<rowSize; k++){
			if(gameCells[k][j].getterCellType()=='*'){
				flag = 1;
			}
		}	
	}
	if(flag==0){
		return -2;
	}

}

int ConnectFourAbstract::compSetArray(const int &rowSize, const int &columnSize)const{
	int flag1=0;
	int flag2=0;
	int flag3=0;
	int columnCounter=0;
	auto beraberlik=0;
	int counter=0;
	
	
	if(gameCells[rowSize -1][columnSize/2].getterCellType()=='*'){  /* oyunun baslangicinda bilgisayar haritanin ortasinin en altta kalan uygun noktasina O koyar ve bu bir kez gerceklesir*/
		gameCells[rowSize -1][columnSize/2].setterCellType('O');
		displayBoard();
		livingcell();
		return -2;

	}
	else if( gameCells[rowSize -2][columnSize/2].getterCellType()!='O' && gameCells[rowSize -2][columnSize/2].getterCellType()!='X' ){
		gameCells[rowSize -2][columnSize/2].setterCellType('O');
		livingcell();
		displayBoard();
		return -2;
	}
	
	int j=0;
	int k=0;

	for(j=0 ; j<rowSize ; j++){   /* bilgisayar kendi taslarini (O) uc tane yan yana getirmissse baska hicbir lokasyana bakmadan kendini direk dotlemesi icin gerekli for dongusu*/
		for(k=0; k<columnSize; k++){
			if((controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==14 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==15 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==16 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==17 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==18 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==19 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==20 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==21 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==22 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==23 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==24 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==25 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==26) && gameCells[j][k].getterCellType()=='*'){
				/* bir yerde uc tane yan yana O bulunuyorsa ve o uclunun yanindaki yer uygunsa(alti dolu kendisi bos ve haritanin disinda olmayan) oraya 'o' konulur*/
				if(j+1<rowSize){  /*tabanda degilse*/

					if( gameCells[j+1][k].getterCellType()!='*' ){

						gameCells[j][k].setterCellType('O');
						livingcell();
						displayBoard();

						//lower(maparray,size,j+1,char(int('A')+k),'O',controlfour(maparray,size,j+1,char(int('A')+k),'O'));
						displayBoard();
						flag2=1;

						break;
					}
				}

				else if(j==rowSize-1){  /* en tabandayse*/
					gameCells[j][k].setterCellType('O');
					livingcell();
					displayBoard();

					//lower(maparray,size,j+1,char(int('A')+k),'O',controlfour(maparray,size,j+1,char(int('A')+k),'O'));
					displayBoard();
					flag2=1;

					break;
				}		
			}

		}
		if(flag2==1){ /* 4 lu durum olusursa flag 2 olur ve bu yuzden ilk for dungusunden cikilir*/
			break;
		}			
	}
	if(flag2==1){/* 4 lu durum olusursa flag 2 olur ve bu yuzden ikinci for dungusunden cikilir*/

		lower(rowSize,j+1,char(int('A')+k),'O',controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O'));
		displayBoard();
		cout<<"Bilgisayar Kazandi"<<endl;  /* ve bilgisayar kazandigi icin ekrana bu bilgi yazilir*/

		return 0;
	}


	for(int j=0 ; j<rowSize ; j++){
		for(int k=0; k<columnSize; k++){
			if(((controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==1 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==2 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==3 ) || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==4 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==5 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==6 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==7 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==8 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==9 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==10 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==11 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==12 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==13) ){
				/*eger engellencek yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve  iki for dongusundende cikilir*/
				if(j+1<10){
					if(((gameCells[j][k].getterCellType()=='*'  && (gameCells[j+1][k].getterCellType()!='*' ) )) ){

						gameCells[j][k].setterCellType('O');
						livingcell();
						displayBoard();


						if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
							displayBoard();
							cout<<"Kazanan Yok"<<endl;
							break;
						}
						displayBoard();
						flag3=1;
						break;
					}				

				}
				else if(j==rowSize-1){
					gameCells[j][k].setterCellType('O');
						livingcell();
						displayBoard();


						if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
							displayBoard();
							cout<<"Kazanan Yok"<<endl;
							break;
						}
						displayBoard();
						flag3=1;
						break;
				}
			}
		}
		if(flag3==1){
			break;
		}			
	}	


	if(flag3==0){ /* dortleme durumlari olusmadiysa yada kullanicinin 3lemesi engellenmediyse*/
		for(int k=0; k<columnSize; k++){
			for(int j=0 ; j<rowSize ; j++){
				if(gameCells[j][k].getterCellType()=='O'){ /* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/

					if((j==rowSize-1 || gameCells[j+1][k+1].getterCellType()=='O' || gameCells[j+1][k+1].getterCellType()=='X' ) && gameCells[j][k+1].getterCellType()=='*' ){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						gameCells[j][k+1].setterCellType('O');
						livingcell();
						displayBoard();

						if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
							beraberlik=1;
							displayBoard();
							cout<<"Kazanan Yok"<<endl;
							break;
						}

						flag2=controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k+1),'O');

						flag1=1;
						break;
						
					}
					else if((j==rowSize-1 || gameCells[j+1][k-1].getterCellType()=='O' || gameCells[j+1][k-1].getterCellType()=='X') &&  gameCells[j][k-1].getterCellType()=='*' && k-1>=0 ){
							/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						gameCells[j][k-1].setterCellType('O');
						livingcell();
						displayBoard();

						if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
							beraberlik=1;
							displayBoard();
							cout<<"Kazanan Yok"<<endl;
							break;
						}


						flag2=controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k-1),'O');

						flag1=1;
						break;
					}
						
					else if((j-1==rowSize-1 || gameCells[j][k].getterCellType()=='O' || gameCells[j][k].getterCellType()=='X') && gameCells[j-1][k].getterCellType()=='*'){
						/* bir yerde 'O' varsa ve yanina koyulac
						ak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						gameCells[j-1][k].setterCellType('O');
						livingcell();
						displayBoard();

						if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
							beraberlik=1;
							displayBoard();
							cout<<"Kazanan Yok"<<endl;
							break;
						}
												

						flag2=controlfour(gameCells,rowSize,columnSize, j,columnCounter, char(int('A')+k),'O');

						flag1=1;
						break;
					}


					else if(gameCells[j][k+1].getterCellType()=='O' &&  gameCells[j][k-1].getterCellType()=='*' ){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(j+1<=rowSize-1){													
							if(gameCells[j+1][k-1].getterCellType()!='*'){
								gameCells[j][k-1].setterCellType('O');
								livingcell();
								displayBoard();

								if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
									beraberlik=1;
									displayBoard();
									cout<<"Kazanan Yok"<<endl;
									break;
								}
								flag2=controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k-1),'O');
								flag1=1;
								break;
							}
						}	
					}
					else if(gameCells[j][k-1].getterCellType()=='O' && gameCells[j][k+1].getterCellType()=='*' ){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(j+1<=rowSize-1){													
							if(gameCells[j+1][k+1].getterCellType()!='*'){

								gameCells[j][k+1].setterCellType('O');
								livingcell();
								displayBoard();

								if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
									beraberlik=1;
									displayBoard();
									cout<<"Kazanan Yok"<<endl;
									break;
								}

								flag2=controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k+1),'O');

								flag1=1;
								break;
							}
						}
					}

					else if(gameCells[j+1][k-1].getterCellType()=='*' && j+2>=0 && k-1>=0 && j+2<rowSize && k-1<columnSize){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(gameCells[j+2][k-1].getterCellType()!='*'){

							
							gameCells[j+1][k-1].setterCellType('O');
							livingcell();
							displayBoard();
							if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
								beraberlik=1;
								displayBoard();
								cout<<"Kazanan Yok"<<endl;
								break;
							}
							flag2=controlfour(gameCells,rowSize,columnSize, j+2,columnCounter, char(int('A')+k-1),'O');


							flag1=1;
							break;
						}	
					}
					//egehfhhdegffg
					else{ /* eger hicbir durum saglanmiyorsa haritada gorulen il bos ve uygun ( bos ve alti dolu ve haritanin icinde) yere O koyulur*/
						int k1=0;
						int j1=0;
						for(int kk=0; kk<columnSize ; kk++){
							for(int jj=0 ; jj<rowSize ; jj++){
								if(gameCells[jj][kk].getterCellType()=='*'){
									if(gameCells[jj+1][kk].getterCellType()!='*'){
										gameCells[jj][kk].setterCellType('O');
										livingcell();
										displayBoard();
										if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
											displayBoard();
											beraberlik=1;
											cout<<"Kazanan Yok"<<endl;
											break;
										}

										flag1=1;
										break;
									}
									else if(jj==rowSize-1){
										gameCells[jj][kk].setterCellType('O');
										livingcell();
										displayBoard();
										if(emptyMapControl(getVec(),GetterRowSize(),GetterColumnSize())==-2){
											displayBoard();
											beraberlik=1;
											cout<<"Kazanan Yok"<<endl;
											break;
										}


										flag1=1;
										break;
									}
								}
							}
							if(flag1==1 || beraberlik==1){
								break;
							}
						}
						break;
					}
				}
			}	
			if(flag1==1 || beraberlik==1){
				flag1=0;
				break;
			}
		}
	}
	else{
		flag3=0;
		counter=2;

	}	

	if((flag2==14 || flag2==15 || flag2==16 || flag2==17 || flag2==18 || flag2==19 || flag2==20|| flag2==21 || flag2==22 || flag2==23 || flag2==24 || flag2==25 || flag2==26 || beraberlik==1)){
		/* bilgisayar icin dortleme durumu olustuysa tum donguden cikilir*/
		return -1;
		
	}
}

int ConnectFourAbstract::lower(const int &rowSize,const int &rowCounter,char letter,char cursor ,int flag)const{

		// kazanma durumda kazanma durumunu saglayan 4 lu taslar ufaltilir
	if(flag==1 || flag==14){
		if(gameCells[rowCounter-1][int(letter)-int('A')+1].getterCellType()=='X'){
			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1][int(letter)-int('A')+1].getterCellType()=='O'){
			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+3].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==2 || flag==15){
		if(gameCells[rowCounter-1][int(letter)-int('A')-1].getterCellType()=='X'){
			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1][int(letter)-int('A')-1].getterCellType()=='O'){
			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}


	if(flag==3 || flag==16){
		if(gameCells[rowCounter-1][int(letter)-int('A')-2].getterCellType()=='X'){
			gameCells[rowCounter-1][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1][int(letter)-int('A')-2].getterCellType()=='O'){
			gameCells[rowCounter-1][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}
	if(flag==4 || flag==17){


		if(gameCells[rowCounter-1][int(letter)-int('A')-3].getterCellType()=='X'){
			gameCells[rowCounter-1][int(letter)-int('A')-3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1][int(letter)-int('A')-3].getterCellType()=='O'){
			gameCells[rowCounter-1][int(letter)-int('A')-3].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==5 || flag==18){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')].getterCellType()=='X'){
			gameCells[rowCounter-1+1][int(letter)-int('A')].setterCellType('x');
			gameCells[rowCounter-1+2][int(letter)-int('A')].setterCellType('x');
			gameCells[rowCounter-1+3][int(letter)-int('A')].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}

		if(gameCells[rowCounter-1+1][int(letter)-int('A')].getterCellType()=='O'){

			gameCells[rowCounter-1+1][int(letter)-int('A')].setterCellType('o');

			gameCells[rowCounter-1+2][int(letter)-int('A')].setterCellType('o');

			gameCells[rowCounter-1+3][int(letter)-int('A')].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==6 || flag==19){
		if(gameCells[rowCounter-1-3][int(letter)-int('A')-3].getterCellType()=='X'){
			gameCells[rowCounter-1-3][int(letter)-int('A')-3].setterCellType('x');
			gameCells[rowCounter-1-2][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1-3][int(letter)-int('A')-3].getterCellType()=='O'){
			gameCells[rowCounter-1-3][int(letter)-int('A')-3].setterCellType('o');

			gameCells[rowCounter-1-2][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==7 || flag==20){
		if(gameCells[rowCounter-1-2][int(letter)-int('A')-2].getterCellType()=='X'){
			gameCells[rowCounter-1-2][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1-2][int(letter)-int('A')-2].getterCellType()=='O'){
			gameCells[rowCounter-1-2][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1+1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==8 || flag==21){
		if(gameCells[rowCounter-1-1][int(letter)-int('A')-1].getterCellType()=='X'){
			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1+1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1+2][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1-1][int(letter)-int('A')-1].getterCellType()=='O'){
			gameCells[rowCounter-1-1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1+1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1+2][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==9 || flag==22){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')+1].getterCellType()=='X'){
			gameCells[rowCounter-1+1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1+2][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1+3][int(letter)-int('A')+3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1+1][int(letter)-int('A')+1].getterCellType()=='O'){
			gameCells[rowCounter-1+1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1+2][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1+3][int(letter)-int('A')+3].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}



	if(flag==10 || flag==23){
		if(gameCells[rowCounter-1-3][int(letter)-int('A')+3].getterCellType()=='X'){
			gameCells[rowCounter-1-3][int(letter)-int('A')+3].setterCellType('x');
			gameCells[rowCounter-1-2][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1-1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1-3][int(letter)-int('A')+3].getterCellType()=='O'){
			gameCells[rowCounter-1-3][int(letter)-int('A')+3].setterCellType('o');

			gameCells[rowCounter-1-2][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1-1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==11 || flag==24){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()=='X'){
			gameCells[rowCounter-1+1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1-1][int(letter)-int('A')+1].setterCellType('x');
			gameCells[rowCounter-1-2][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()=='O'){
			gameCells[rowCounter-1+1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1-1][int(letter)-int('A')+1].setterCellType('o');

			gameCells[rowCounter-1-2][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==12 || flag==25){
		if(gameCells[rowCounter-1+2][int(letter)-int('A')-2].getterCellType()=='X'){
			gameCells[rowCounter-1+2][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')+3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1+2][int(letter)-int('A')-2].getterCellType()=='O'){
			gameCells[rowCounter-1+2][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+2].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')+3].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}

	if(flag==13 || flag==26){
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()=='X'){
			gameCells[rowCounter-1+1][int(letter)-int('A')-1].setterCellType('x');
			gameCells[rowCounter-1+2][int(letter)-int('A')-2].setterCellType('x');
			gameCells[rowCounter-1+3][int(letter)-int('A')-3].setterCellType('x');
			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('x');
		}
		if(gameCells[rowCounter-1+1][int(letter)-int('A')-1].getterCellType()=='O'){
			gameCells[rowCounter-1+1][int(letter)-int('A')-1].setterCellType('o');

			gameCells[rowCounter-1+2][int(letter)-int('A')-2].setterCellType('o');

			gameCells[rowCounter-1+3][int(letter)-int('A')-3].setterCellType('o');

			gameCells[rowCounter-1][int(letter)-int('A')].setterCellType('o');

		}
	}
}

string ConnectFourAbstract::writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi) {
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
					
	dosya.close();   /* dosya kapatilir*/
	cout<<"Sutun Harfi Seciniz"<<endl;
	cin.clear();


	letter = getLetter('X');     /* kullanicidan harf almaya devam edilir*/
	return letter;



}
char ConnectFourAbstract::readFile(string letter) {
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
	dosya>>sira;
	dosya>>livingCell;

	
	for(int l=0;l<columnSize;l++){   /* dosyanin icindeki a b c d gibi harfleri temp arrayine attim*/
			dosya>>temp[l];
	}

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
			if(setArray(letter,'X')==1){
				displayBoard();
				cout<<"Oyuncu kazandi"<<endl;	
				return -3 ;
			}
			cout<<endl;

			if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
				cout<<"Kazanan Yok"<<endl;	
				break;
			}

			if(compSetArray(rowSize,columnSize)==0){
				break;
			}

		}	
		return -3;
	}
	else if(gameType=='P'){
		if(sira=='X'){
			while(1){
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
				if(setArray(letter,'X')==1){
					displayBoard();
					cout<<"1.oyuncu kazandi"<<endl;	
					return -3;
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){
					cout<<"Kazanan Yok"<<endl;	
					break;
				}

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
				if(setArray(letter,'O')==2){
					displayBoard();

					cout<<"2.oyuncu kazandi"<<endl;	
					return -3;
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){
					cout<<"Kazanan Yok"<<endl;	
					break;
				}


			}
			return -3;
		}
		if(sira=='O'){
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
				if(setArray(letter,'O')==2){
					displayBoard();

					cout<<"2.oyuncu kazandi"<<endl;	
					break;
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){
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
				if(setArray(letter,'X')==1){
					displayBoard();
					cout<<"1.oyuncu kazandi"<<endl;	
					return -3;
				}
				//game1.displayBoard();
				if(emptyMapControl(getVec(),rowSize,columnSize)==-2){
					cout<<"Kazanan Yok"<<endl;	
					break;
				}

			}
			return -3;
		}

	}

	return gameType;		/* oyun tipi return edilir*/	
}
int ConnectFourAbstract::playGame(const char &gameMode){
	string letter;
	string filename;  // iki tas atimi yapilir bunun icin play fonksiyonlari kullanilir
	int flag=0;
	if(gameMode=='S' || gameMode=='s'){
		//initArray(rowSize,columnSize);
		while(getGameType()==-1){
			cerr<<"Hatali Giris Yaptiniz:"<<endl;

			getGameType();

		}
	}
	if(gameType=='P'){
		int counter=0;
		while(1){
			displayBoard();
			cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;

			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/

			int b=playX(gameMode,letter);

			if(b==-3 || b==0){
				return b;
			}

			cout<<"(2.Oyuncu) Sutun Harfi Seciniz"<<endl;

			letter = getLetter('O');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/

			int c=playO(gameMode,letter);	

			if(c==-3 || c==0){
				return c;
			}
		}
		return 0;
	}
	if(gameType=='C'){
		int counter=0;
		while(1){
			displayBoard();

			cout<<"Sutun Harfi Seciniz"<<endl;

			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
			int m=playX(letter,gameType);
		
			if(m==1 || m==-3 ){
				return 1;
			}
				
			if(play(gameMode)==2){
				return 2;
			}
			break;

		}
		
		return 0;	
	}

}

int ConnectFourAbstract::playGame(){
	string letter;
	string filename;    // iki tas atimi yapilir bunun icin play fonksiyonlari kullanilir
	int flag=0;
	
	//initArray(rowSize,columnSize);
	while(getGameType()==-1){
		cerr<<"Hatali Giris Yaptiniz:"<<endl;
		getGameType();
	}
	
	if(gameType=='P'){
		int counter=0;
		while(1){

			cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;

			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/

			int b=playX(letter,gameType);

			if(b==1 || b==0 || b==-3 || b==-99){
				return 0;
			}

			cout<<"(2.Oyuncu) Sutun Harfi Seciniz"<<endl;

			letter = getLetter('O');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/

			int c=playO(letter,gameType);	


			if(c==2 || c==0 || c==-3){
				return 0;
			}
		}
		return 0;
	}
	if(gameType=='C'){
		int counter=0;
		while(1){

			displayBoard();

			cout<<"Sutun Harfi Seciniz"<<endl;

			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
			
			int m=playX(letter,gameType);
		
			if(m==1 || m==-3 || m==-99 ){
				return 1;
			}

			if(m!=-98)	{
			if(play()==2){
				return 2;
			}	
			}
			else{
				displayBoard();
			}

		}
		return 0;	
	}

}

int ConnectFourAbstract::playX( const char &gameMode, const string &letter){    // multi modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alir
	int a=1;
	char sira='X';

	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
		
		writeFile(rowSize,columnSize,letter,sira,'P');
			
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}
	int d=setArray(letter,sira);
	if(d==1){
		displayBoard();
		cout<<"1.oyuncu kazandi"<<endl;	
		return -3;
	}
	else if(d==2){
		displayBoard();
		cout<<"2.oyuncu kazandi"<<endl;	
		return -3;

	}

	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return -3;
	}
	if(sira=='O'){
		if(gameMode=='M' || gameMode=='m'){
			return 0;
		}
	}

	
}

int ConnectFourAbstract::playO(const char &gameMode,const string &letter){  // multi modda 2. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alir
	int a=2;
	char sira='O';

	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
		
		writeFile(rowSize,columnSize,letter,sira,'P');
			
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}
	int d=setArray(letter,sira);
	if(d==1){
		displayBoard();
		cout<<"1.oyuncu kazandi"<<endl;	
		return -3;
	}
	else if(d==2){
		displayBoard();
		cout<<"2.oyuncu kazandi"<<endl;	
		return -3;

	}

	//game1.displayBoard();
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return -3;
	}
	if(sira=='O'){
		if(gameMode=='M' || gameMode=='m'){
			return 0;
		}
	}

	
}

int ConnectFourAbstract::playX( string letter,char gameType){ // tekli modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir
	int a=1;
	char sira='X';
		
	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/
		writeFile(rowSize,columnSize,letter,sira,gameType);
			
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}
	int d=setArray(letter,sira);
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
int  ConnectFourAbstract::playO(  string letter,const  char &gameType){ // tekli modda 2. ouncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir
	int a=2;
	char sira='O';
	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/

		letter =writeFile(rowSize,columnSize,letter,sira,gameType);	
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}


	int d=setArray(letter,sira);
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

int  ConnectFourAbstract::play( const char &gameMode){  // multi modda bilgisayarin tas atimi yapmasi icin gerekli olan fonskiyon
			
		if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
			cout<<"Kazanan Yok"<<endl;	
			return -3;
		}

		if(compSetArray(rowSize,columnSize)==0){
			return 2;
		}
		if(gameMode=='M' || gameMode=='m'){
			return 0;
		}
}

int   ConnectFourAbstract::play(){   // tekli modda bilgisayarin tas atimi yapmasi icin gerekli olan fonskiyon
	
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return -3;
	}
	if(compSetArray(rowSize,columnSize)==0){
		return 2;
	}
}
			

bool  ConnectFourAbstract::compare(const ConnectFourAbstract  &obje)  {
	int xCounter1=0;
	int xCounter2=0;
	int columnCounter=0;

	for(int j=0 ; j<rowSize ; j++){   /*ilk obje icin uclu durum varmi diye kontrol edlir*/
	    for(int k=0; k<columnSize; k++){
				if(((controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==1 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==2 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==3 ) && gameCells[j][k].getterCellType()=='*'  || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==4 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==5 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==6 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==7 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==8 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==9 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==10 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==11 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==12 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==13)  && gameCells[j][k].getterCellType()=='*'){
				xCounter1++;
			}
		}	
	}

	for(int j=0 ; j<obje.rowSize ; j++){   /*parametre olarak gelen obje icin uclu durum varmi diye kontrol edilir*/
	    for(int k=0; k<obje.columnSize; k++){
				if(((controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==1 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==2 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==3 ) && obje.gameCells[j][k].getterCellType()=='*'  || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==4 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==5 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==6 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==7 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==8 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==9 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==10 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==11 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==12 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==13)  && obje.gameCells[j][k].getterCellType()=='*'){
				xCounter2++;
			}
		}	
	}

	if(xCounter1>xCounter2){
		return true;    // obje 1 , 2 den iyiyse (3 lu X durum sayisi fazlaligi)
	}
	else {
		return false;  // obje 1 , 2 den iyi degilse
	}
}

