#include <iostream>
#include <string>
#include <fstream>
#include <new>

using namespace std;

class ConnectFour{


private:
	class Cell{
	public:

		Cell(){}   // cell constructorlari
		Cell(char letter,int rowNumber,int cellType);

		bool operator==(const Cell &other){   // Cell clasi icin == operator overloadi

			return ((letter==other.letter) && (rowNumber==other.rowNumber) && (cellType==other.cellType)); // sutun ve satir(konum) ile cellTipi ayniysa iki cell esittir 1 return eder
		}
		bool operator!=(const Cell &other){  // Cell clasi icin != operator overloadi
			
			return ((letter!=other.letter) || (rowNumber!=other.rowNumber) || (cellType!=other.cellType));  // eger cell data memerlarindan biri farkliysa iki cell bir birinden farklidir ve 1 return eder
		}


		Cell& operator++ () //pre increment operator overloading
{
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
Cell& operator-- () //pre decrement operator overloading
{

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

Cell operator++ (const int x) //post increment operator overloading
{
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

Cell operator-- (const int x) //post decrement operator overloading
{
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

		inline void  setterLetter(const char &letterr){  //inline fonksiyonlar(setter getter)
			letter=letterr;

		}
		inline char  getterLetter()const {
				return letter;


		}
		
		inline void  setterRowNumber(const char &rowNumberr){
				rowNumber=rowNumberr;

		}
		inline int  getterRowNumber() const {
				return rowNumber;


		}

		inline void  setterCellType(const int &cellTypee) {
				cellType=cellTypee;


		}
		inline char  getterCellType()const {
				return cellType;

		}

	private:      // Cell classi icin private data memberlar
		char letter;
		int rowNumber;
		char cellType;
	};
	
	Cell** gameCells; //ConnectFour clasi icin private data memberlar
	int rowSize;
	int columnSize;
	char gameType;
	string fileName;
	static int livingCell;    /* livingCell sayisini tutar*/
	

public:

	ConnectFour(){          //constructor 1(5 e 5 lik olusturan)
		rowSize=5;
		columnSize=5;
	}

	ConnectFour(int a,int b){   // constructor 2 (gelen parametrelere gore olusturan)
		rowSize=a;
		columnSize=b;
	}
	ConnectFour(string filenamee){   //constructor 3  (filename alarak olusturan)

		fileName=filenamee;  // filename alir ve data member olan filename e atarim

	}

	ConnectFour(const ConnectFour & D){ // copy constructor
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
	~ConnectFour(){         // destructor
		 for(int i = 0; i < rowSize; ++i) {  // olusturulan objenin icinde pointer data member olan gameCells vardi ve obje oldiginde bunu delete etmeliyiz
	delete[] gameCells[i];
		 }
	 delete[] gameCells;
	}

	bool operator==(const ConnectFour &other){  // == operatoru overloading(ConnectFour classi icin)

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
		return ((rowSize==other.rowSize) && (columnSize==other.columnSize) && (gameType==other.gameType) && flag);// iki connectfour objesinin esit olmasi icin row colum sizelari,gameTypelari ve gameCellsleri(flag) ayni olmali
	}

	bool operator!=(const ConnectFour &other){ // != operatoru overloading(ConnectFour classi icin)
		int flag=0;
		
		for(int i=0;i<rowSize;i++){  // board icini tarar ve boardda 1 tane farklilik gordugu anda flag 1 olur ve 1 return eder
			for(int j=0;j<columnSize;j++){
				if(gameCells[i][j].getterCellType()!=other.gameCells[i][j].getterCellType()){
					flag=1;
					return 1;
				}
			}
		}

		return ((rowSize!=other.rowSize) || (columnSize!=other.columnSize) || (gameType!=other.gameType) || flag);// iki connectfour objesinin farkli olmasi icin rowsize columsize gametype yada gameCellslerinden birisinin farkli olmasi yeterlidir
	}


	ConnectFour& operator = (const ConnectFour &D ) {   //overloaded assigment operator

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


inline char   GetterLetter()const {      //inline fonskiyonlar(setter getter)
	Cell obj;
		return obj.getterLetter();
}
inline void   SetterLetter(const char &letter)const {
		
	 	Cell obj;
		obj.setterLetter(letter);
}

inline void   SetterRowNumber(const char &rowNumber)const {
	Cell obj;
		obj.setterRowNumber(rowNumber);

}
	inline int   GetterRowNumber()const {
		Cell obj;
		return obj.getterRowNumber();

	}

	inline void   SetterCellType(const int &cellType)const {
		Cell obj;
		obj.setterCellType(cellType);

	}
	inline char GetterCellType()const {
		Cell obj;
		return obj.getterCellType();
	}


	Cell** getVec() const {      // iki boyutlu vektore erisebilmek icin gerekli vektor
		return gameCells;
	}
	
	void  initArray(const int &row, const int &column);    //baslangicta vektoru initialize etmek icin gerekli fonksiyon

	void initArray();  // filename alan constructor kullanildiginda cagrilan fonksiyon

	int  setArray(string letter,const char &mark);   //vektore tas eklemek icin gerekli fonksiyon

	void  displayBoard()const ;     /*ekranda guncel boardi gosteriri*/

	inline int GetterColumnSize()const {       //inline fonskiyonlar(setter getter)
		return columnSize;
	}
	inline void SetterColumnSize(const int coulmnn) {
			columnSize=coulmnn;
	}

	inline int GetterRowSize() const {
		return rowSize;
	}
	inline void SetterRowSize(const int roww){
		rowSize=roww;
	}
	inline string getterFileName()const {       //inline fonskiyonlar(setter getter)
		return fileName;
	}
	

	int   getGameType(void);      // oyun tipini kullanicidan alir

	inline char getterGameType()  {   //inline fonskiyonlar(setter getter)
		return gameType;
	}
	inline void setterGameType( char gameTypee){
		gameType=gameTypee;
	}

	string  writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi) ;   // dosyaya yazma write fonskiyonu(SAVE)

	char  readFile(string letter);   // dosyadan okuma read (LOAD) fonksiyonu

	int   inputHeightSize();    	/*board height size ini return eder*/

	int   inputWidhtSize();  		/*board widht size ini return eder*/

	string inputFileName();   //kullanicidan dosya adini alan fonksiyon

	int  playO(string letter, const char &gameType);  /*1. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alir)*/

	int  playX( string letter, char gameType);  /*2. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alir)*/

	int  play();  /*bilgisayar oynar 1 kez*/

	int  playGame();   //oyunu temel olarak oynatan fonksiyon

	static int   livingcell(){     // livingcell sayisini arrtirmak icin gerekli fonskiyon, ve current livingcell return eder
		livingCell++;
		return livingCell;
	}

	bool  compare(const ConnectFour &obje)  ;  /* ilk obje parametre olarak gonderilen objeye gore daha iyiyse  true return eder, daha kotuyse false return eder.(daha iyinin anlami daha fazla 3 lu X sayisinin olmasidir)*/

	int  playGame(const char &gameMode);   //oyunu temel olarak oynaatan fonksiyon

	int  playO(const char &gameMode, const string &letter); // ikinci oyuncunun bir hamle yapmasi icin gerekli fonksiyon

	int  playX(const char &gameMode, const string &letter); // birinci oyuncunun bir hamle yapmasi icin gerekli fonksiyon

	int  play(const char &gameMode);  // bilgisayarin bir hamle yapmasi icin gerekli fonksiyon

	string  getLetter( const char &mark);	//kullanicidan sutun harfi alinan fonskiyon

	int  controlfour( Cell** gameCells, const int &rowSize, const int &columnSize,const int &rowrowCounter,const int &columnrowCounter,const char &letter, const char &cursor)const ;  //4 lu durum olusmusmu diye kontrol eden fonksiyon

	int  emptyMapControl(Cell** gameCells, const int &rowSize, const int &columnSize)const ; //boardda bos yer varmi diye kontrol eden fonksiyon

	int  compSetArray(const int &rowSize, const int &columnSize)const;   //bilgisayarin boarda tas koymasini saglayan fonskiyon

	int  lower(const int &rowSize,const int &rowCounter,char = 'A',char = 'O',int = 0)const;  //kazanma durumda kazanmayi saglayan taslari kucultme fonksiyonu

	
};

int ConnectFour::livingCell = 0;   // statik degiskeni ilklendirme

int main(){

	char gameMode; //degiskenler
	string letter;
	string filename;
	int flag=0;
	int o1=0;
	int o2=0;
	int o3=0;
	int o4=0;
	int o5=0;

	cout<<"Oyun Modu Seciniz =";// oyun modu alinir
	cin>>gameMode;
	cin.ignore();

	
	while(gameMode!='S' && gameMode!='s' && gameMode!='M' && gameMode!='m'){  //hata durumu kontrolu
		cerr<<"Hatali Giris Yapiniz"<<endl;
		cout<<"Oyun Modu Seciniz =";
		cin>>gameMode;  // oyun modu alinir
	}	


	if(gameMode=='S' || gameMode=='s'){  // tekli modda constructor a gonderilen filename parametresiyle tek obje olusturulur
		gameMode='S';
		ConnectFour game0(game0.inputFileName()); // inputFilename string dondurur o string ile ConnectFour constructoru cagrilir
		game0.initArray(); // array olusturulur
		game0.displayBoard(); //array ekrana basilir
		game0.playGame(); // oyun ilk adim baslar(X ve O)
	}
	if(gameMode=='M' || gameMode=='m'){  // coklu modda constructor a gonderilen filenanameler ile 5 obje olusturulur
		gameMode='M';
		int objectNumber=0;

		cout<<"Obje1:"<<endl;
		ConnectFour game1(game1.inputFileName());// array olusturulur
		game1.initArray();  // array olusturulur
		game1.getGameType();// oyun tipi alinir



		cout<<"Obje2:"<<endl;
		ConnectFour game2(game2.inputFileName());// array olusturulur
		game2.initArray();  // array olusturulur
		game2.getGameType();// oyun tipi alinir



		cout<<"Obje3:"<<endl;
		ConnectFour game3(game3.inputFileName());// array olusturulur
		game3.initArray();  // array olusturulur
		game3.getGameType();// oyun tipi alinir


		cout<<"Obje4:"<<endl;
		ConnectFour game4(game4.inputFileName());// array olusturulur
		game4.initArray();  // array olusturulur
		game4.getGameType();// oyun tipi alinir


		cout<<"Obje5:"<<endl;
		ConnectFour game5(game5.inputFileName());// array olusturulur
		game5.initArray();  // array olusturulur
		game5.getGameType();// oyun tipi alinir

		if(game1==game2){  // game1 ile game2 esitse ekrana bu bildirilir(connectfour icin == overload kullanilir)
			cout<<"game1 ile game2 esittir"<<endl;
		}

		if(game1!=game2){// game1 ile game2 esit degilse ekrana bu bildirilir(connectfour icin != overload kullanilir)
			cout<<"game1 ile game2 esit degildir"<<endl;
		}

		while(o1==0 || o2==0 || o3==0 || o4==0 || o5==0){   /* tum objlerin oyunu bittiginde bu donguden cikilir*/

			cout<<"Obje seciniz:"<<endl;   // her iki tas atiminda obj sorulur ve o objeden devam edilir eger bir obje bitmissse kullanici uyarilir
			cin>>objectNumber;

			if(objectNumber==1){
				if( o1==0){
					o1=game1.playGame(gameMode);//  oyun 2 adim devam eder(X ve O)
				}

				if(o1!=0){
					cout<<"o1 = "<<o1<<endl;
					cout<<"1. Objenin Oyunu Bitti"<<endl;
				}
			}


			if(objectNumber==2){
				if(objectNumber==2 && o2==0){
					o2=game2.playGame(gameMode);// oyun 2 adim devam eder(X ve O)
				}
				if(o2!=0){
					cout<<"2. Objenin Oyunu Bitti"<<endl;
				}
			}

			if(objectNumber==3){
				if(objectNumber==3 && o3==0){
					o3=game3.playGame(gameMode);//  oyun 2 adim devam eder(X ve O)
				}
				if(o3!=0){
					cout<<"3. Objenin Oyunu Bitti"<<endl;
				}
			}


			if(objectNumber==4){
				if(objectNumber==4 && o4==0){
					o4=game4.playGame(gameMode);//  oyun 2 adim devam eder(X ve O)
				}
				if(o4!=0){
					cout<<"4. Objenin Oyunu Bitti"<<endl;
				}
			}

			if(objectNumber==5){
				if(objectNumber==5 && o5==0){
					o5=game5.playGame(gameMode);// oyun 2 adim devam eder(X ve O)
				}
				if(o5!=0){
					cout<<"5. Objenin Oyunu Bitti"<<endl;
				}
			}	

			if(game1==game2){
			cout<<"game1 ile game2 esittir"<<endl;
			}

			if(game1!=game2){
				cout<<"game1 ile game2 esit degildir"<<endl;
			}


		}
		cout<<"Tum objelerin oyunu bitti"<<endl;
			
	}

	return 0;

}

ConnectFour::Cell::Cell(char letterr,int rowNumberr,int cellTypee){
	letter=letterr;  //parametrelere ilklendirmeler yapilir
	rowNumber=rowNumberr;
	cellType=cellTypee;
}


void ConnectFour::initArray(const int &columnSize, const int &rowSize){

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

void ConnectFour::initArray(){

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

void ConnectFour::displayBoard()const{

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

int ConnectFour::setArray( string letter, const char &mark){

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

string ConnectFour::inputFileName(){
	string a;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi srerun edilir*/
	cout<<"Dosya Adini Giriniz"<<endl;
	getline(cin,a);
	cout<<"a="<<a<<endl;
	return a;
	
}

int ConnectFour::inputHeightSize(){   // kullanidan height alinir

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

int ConnectFour::inputWidhtSize(){   // kullanicidan weight alinir

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


int ConnectFour::getGameType(void){
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

/***********************************************************************************************/
string ConnectFour::getLetter(const char &mark) {
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

int ConnectFour::controlfour( Cell **gameCells, const int &rowSize, const int &columnSize, const int &rowCounter,const int &columnCounter,const char &letter, const char &cursor) const{
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
int  ConnectFour::emptyMapControl(Cell** gameCells, const int &rowSize,const int &columnSize)const {
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

int ConnectFour::compSetArray(const int &rowSize, const int &columnSize)const{
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
		cout<<"livingCell= "<<livingCell<<endl;
		return -2;

	}
	else if( gameCells[rowSize -2][columnSize/2].getterCellType()!='O' && gameCells[rowSize -2][columnSize/2].getterCellType()!='X' ){
		gameCells[rowSize -2][columnSize/2].setterCellType('O');
		livingcell();
		displayBoard();
		cout<<"livingCell= "<<livingCell<<endl;
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
						cout<<"livingCell= "<<livingCell<<endl;

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
					cout<<"livingCell= "<<livingCell<<endl;

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
						cout<<"livingCell= "<<livingCell<<endl;


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
						cout<<"livingCell= "<<livingCell<<endl;


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
						cout<<"livingCell= "<<livingCell<<endl;

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
						cout<<"livingCell= "<<livingCell<<endl;

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
						cout<<"livingCell= "<<livingCell<<endl;

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
								cout<<"livingCell= "<<livingCell<<endl;

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
								cout<<"livingCell= "<<livingCell<<endl;

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
							cout<<"livingCell= "<<livingCell<<endl;
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
										cout<<"livingCell= "<<livingCell<<endl;
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
										cout<<"livingCell= "<<livingCell<<endl;
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

int ConnectFour::lower(const int &rowSize,const int &rowCounter,char letter,char cursor ,int flag)const{

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

string ConnectFour::writeFile( int rowSize, int columnSize,string letter, char mark, char gametipi) {
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

	cout<<"letter2="<<letter<<endl;

	letter = getLetter('X');     /* kullanicidan harf almaya devam edilir*/
	cout<<"letter3="<<letter<<endl;
	return letter;



}

char ConnectFour::readFile(string letter) {
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

	rowSize++;

	for(int i=0; i<rowSize ; i++){
		gameCells[i] = new Cell[columnSize];
	}

	for(int j=0 ; j<rowSize ; j++){
			for(int k=0; !(dosya.eof()) ; k++){
				dosya.get(a);
				if(a=='\n'){
					break;
				}
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
								cout<<"heyheyeyey"<<endl;
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

int ConnectFour::playGame(const char &gameMode){
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

int ConnectFour::playGame(){
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
			//displayBoard();
			cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;

			letter = getLetter('X');    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/

			int b=playX(letter,gameType);

			if(b==1 || b==0 || b==-3){
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
		
			if(m==1 || m==-3 ){
				return 1;
			}

				
			if(play()==2){
				return 2;
			}	


		}
		return 0;	
	}

}

int ConnectFour::playX( const char &gameMode, const string &letter){    // multi modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alir
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

int ConnectFour::playO(const char &gameMode,const string &letter){  // multi modda 2. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alir
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

int ConnectFour::playX( string letter,char gameType){ // tekli modda 1. oyuncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir
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

int  ConnectFour::playO(  string letter,const  char &gameType){ // tekli modda 2. ouncu icin tek bir tas atimi icin gerekli olan fonskiyon , parametre olarak pozisyon(letter) alir
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

	cout<<"letter1="<<letter<<endl;
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

int  ConnectFour::play( const char &gameMode){  // multi modda bilgisayarin tas atimi yapmasi icin gerekli olan fonskiyon
			
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

int   ConnectFour::play(){   // tekli modda bilgisayarin tas atimi yapmasi icin gerekli olan fonskiyon
	
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return -3;
	}
	if(compSetArray(rowSize,columnSize)==0){
		return 2;
	}
}
			

bool  ConnectFour::compare(const ConnectFour  &obje)  {
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

