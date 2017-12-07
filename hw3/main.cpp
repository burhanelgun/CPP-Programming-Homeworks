/*compare fonksiyonunu objelerdeki 3lü X leri saydırarak yaptım ve o an oynanan obje ile diğerlerini karşılaştırıp iyi olduğu durumlarda ekrana bastım her adımda*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class ConnectFour{


private:
	class Cell{
	public:

		Cell(){}
		Cell(char letter,int rowNumber,int cellType);

		inline void const setterLetter(const char &letterr){  //inline fonksiyonlar(setter getter)
			letter=letterr;

		}
		inline char const getterLetter() const{
				return letter;


		}
		
		inline void const setterRowNumber(const char &rowNumberr){
				rowNumber=rowNumberr;

		}
		inline int const getterRowNumber() const {
				return rowNumber;


		}

		inline void const setterCellType(const int &cellTypee){
				cellType=cellTypee;


		}
		inline char const getterCellType() const{
				return cellType;

		}

	private:      // Cell classı için private data memberlar
		char letter;
		int rowNumber;
		char cellType;   
	};
	
	vector< vector<Cell> > gameCells; //ConnectFour clası için private data memberlar
	int rowSize;
	int columnSize;
	char gameType;
	static int livingCell;    /* livingCell sayısını tutar*/
	

public:

	ConnectFour(int a,int b){   // constructor 1
		rowSize=a;
		columnSize=b;
	}
	ConnectFour(int a){       //constructor 2
		rowSize=a;
		columnSize=4;
	} 
	ConnectFour(){          //constructor 3
		rowSize=4;
		columnSize=4;
	}

	

    inline char  const GetterLetter() const{      //inline fonskiyonlar(setter getter)
    	Cell obj;
		return obj.getterLetter();

    }
    inline void  const SetterLetter(const char &letter) const{
    		
  	 	Cell obj;
		obj.setterLetter(letter);
    }

    inline void  const SetterRowNumber(const char &rowNumber) const{
    	Cell obj;
		obj.setterRowNumber(rowNumber);

    }
	inline int  const GetterRowNumber() const{
		Cell obj;
		return obj.getterRowNumber();

	}

	inline void  const SetterCellType(const int &cellType) const{
		Cell obj;
		obj.setterCellType(cellType);

	}
	inline char  const GetterCellType() const{
		Cell obj;
		return obj.getterCellType();
	}


	vector< vector<Cell> >  const getVec() const{      // iki boyutlu vektöre erişebilmek için gerekli vektör
		return gameCells;
	}
	
	void const initVector(const int &row,const int &column);    //başlangıcta vektörü initialize etmek için gerekli fonksiyon

	int const setVector(string letter,const char &mark);   //vektöre tas eklemek icin gerekli fonksiyon

	void const displayBoard() const;     /*ekranda güncel boardı gösteriri*/

	inline int GetterColumnSize() const{       //inline fonskiyonlar(setter getter)
		return columnSize;
	}
	inline void SetterColumnSize(const int &coulmnn) {
			columnSize=coulmnn;
	}

	inline int GetterRowSize() const {
		return rowSize;
	}
	inline void SetterRowSize(const int &roww){
		rowSize=roww;
	}

	

	int  const getGameType(void);      // oyun tipini kullanıcıdan alır

	inline char getterGameType() const {   //inline fonskiyonlar(setter getter)
		return gameType;
	}
	inline void setterGameType(const char &gameTypee){  
		gameType=gameTypee;
	}

	char const writeFile(const int &rowSize,const int &columnSize,string letter,const char &mark,const char &gametipi) const;   // dosyaya yazma write fonskiyonu(SAVE)

	char const readFile(string letter);   // dosyadan okuma read (LOAD) fonksiyonu

	int  const inputHeightSize();    	/*board height size ını return eder*/

	int  const inputWidhtSize();  		/*board widht size ını return eder*/

	int const playO(const string &letter,const char &gameType);  /*1. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alır)*/

	int const playX(const string &letter,const char &gameType);  /*2. oyuncu oynar 1 kez (Parametre olarak letter yani poziyon alır)*/

	int const play();  /*bilgisayar oynar 1 kez*/

	int const playGame();   //oyunu temel olarak oynatan fonksiyon 

	static int  const livingcell(){     // livingcell sayısını arrtırmak icin gerekli fonskiyon, ve current livingcell return eder
		livingCell++;
		return livingCell;
	}

	bool const compare(ConnectFour const &obje) const ;  /* ilk obje parametre olarak gönderilen objeye göre daha iyiyse  true return eder, daha kötüyse false return eder.(daha iyinin anlamı daha fazla 3 lü X sayısının olmasıdır)*/

	int const playGame(const char &gameMode);   //oyunu temel olarak oynaatan fonksiyon

	int const playO(const char &gameMode,const string &letter); // ikinci oyuncunun bir hamle yapması icin gerekli fonksiyon

	int const playX(const char &gameMode,const string &letter); // birinci oyuncunun bir hamle yapması icin gerekli fonksiyon

	int const play(const char &gameMode);  // bilgisayarın bir hamle yapması icin gerekli fonksiyon

	string const getLetter(const char &mark) const;	//kullanıcıdan sutun harfi alınan fonskiyon

	int const controlfour(const vector <vector<Cell>> &gameCells, const int &rowSize, const int &columnSize,const int &rowrowCounter,const int &columnrowCounter,const char &letter, const char &cursor) const;  //4 lü durum oluşmusmu diye kontrol eden fonksiyon

	int const emptyMapControl(const vector< vector<Cell> > &gameCells,const int &rowSize,const int &columnSize) const; //boardda bos yer varmı diye kontrol eden fonksiyon

	int const compSetVector(const int &rowSize,const int &columnSize);   //bilgisayarın boarda tas koymasını sağlayan fonskiyon

	int const lower(const int rowSize,const int rowCounter,char = 'A',char = 'O',int = 0);  //kazanma durumda kazanmayı sağlayan tasları kucultme fonksiyonu

	
};

int ConnectFour::livingCell = 0;   // statik değişkeni ilklendirme

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

	cout<<"Oyun Modu Seçiniz =";
	cin>>gameMode;
	
	while(gameMode!='S' && gameMode!='s' && gameMode!='M' && gameMode!='m'){  //hata durumu kontrolu
		cerr<<"Hatali Giris Yapiniz"<<endl;
		cout<<"Oyun Modu Seçiniz =";

		cin>>gameMode;
	}	


	if(gameMode=='S' || gameMode=='s'){  // tekli modda constructor a gönderilen parametrelerle tek obje oluşturulur*/
		gameMode='S';
		ConnectFour game0(game0.inputHeightSize(),game0.inputWidhtSize());
		game0.playGame();
	}

	if(gameMode=='M' || gameMode=='m'){  // çoklu modda constructor a gönderilen parametrelerle 5 obje oluşturulur*/
		gameMode='M';
		int objectNumber=0;

		cout<<"Obje1:"<<endl;
		ConnectFour game1(game1.inputHeightSize(),game1.inputWidhtSize());
		game1.initVector(game1.GetterRowSize(),game1.GetterColumnSize());
		game1.getGameType();


		cout<<"Obje2:"<<endl;
		ConnectFour game2(game2.inputHeightSize(),game2.inputWidhtSize());
		game2.initVector(game2.GetterRowSize(),game2.GetterColumnSize());
		game2.getGameType();


		cout<<"Obje3:"<<endl;
		ConnectFour game3(game3.inputHeightSize(),game3.inputWidhtSize());
		game3.initVector(game3.GetterRowSize(),game3.GetterColumnSize());
		game3.getGameType();

		cout<<"Obje4:"<<endl;
		ConnectFour game4(game4.inputHeightSize(),game4.inputWidhtSize());
		game4.initVector(game4.GetterRowSize(),game4.GetterColumnSize());
		game4.getGameType();

		cout<<"Obje5:"<<endl;
		ConnectFour game5(game5.inputHeightSize(),game5.inputWidhtSize());
		game5.initVector(game5.GetterRowSize(),game5.GetterColumnSize());
		game5.getGameType();

	

		while(o1==0 || o2==0 || o3==0 || o4==0 || o5==0){   /* tum objlerin oyunu bittiğinde bu döngüden çıkılır*/
	
			if(game1.compare(game2)==true){   /*har adımda eğer bir obje diğerinden daha iyiyse (3 tane X yanyana yada çapraz) ekrana print edilir*/
				cout<<"game1>game2"<<endl;
			}
		

			if(game1.compare(game3)==true){
				cout<<"game1>game3"<<endl;
			}
		
			if(game1.compare(game4)==true){
				cout<<"game1>game4"<<endl;
			}
		
			if(game1.compare(game5)==true){
				cout<<"game1>game5"<<endl;
			}
			


			if(game2.compare(game3)==true){
				cout<<"game2>game3"<<endl;
			}
	
			if(game2.compare(game4)==true){
				cout<<"game2>game4"<<endl;
			}
	
			if(game2.compare(game5)==true){
				cout<<"game2>game5"<<endl;
			}


			if(game3.compare(game4)==true){
				cout<<"game3>game4"<<endl;
			}

			if(game3.compare(game5)==true){
				cout<<"game3>game5"<<endl;
			}


			if(game4.compare(game5)==true){
				cout<<"game4>game5"<<endl;
			}



			cout<<"Obje seçiniz:"<<endl;   // her iki taş atımında obj sorulur ve o objeden devam edilir eğer bir obje bitmişsse kullanıcı uyarılır
			cin>>objectNumber;

			if(objectNumber==1){
				if( o1==0){
					o1=game1.playGame(gameMode);
				}

				if(o1!=0){
					cout<<"o1 = "<<o1<<endl;
					cout<<"1. Objenin Oyunu Bitti"<<endl;
				}
			}


			if(objectNumber==2){
				if(objectNumber==2 && o2==0){
					o2=game2.playGame(gameMode);
				}
				if(o2!=0){
					cout<<"2. Objenin Oyunu Bitti"<<endl;
				}
			}

			if(objectNumber==3){
				if(objectNumber==3 && o3==0){
					o3=game3.playGame(gameMode);
				}
				if(o3!=0){
					cout<<"3. Objenin Oyunu Bitti"<<endl;
				}
			}


			if(objectNumber==4){
				if(objectNumber==4 && o4==0){
					o4=game4.playGame(gameMode);
				}
				if(o4!=0){
					cout<<"4. Objenin Oyunu Bitti"<<endl;
				}
			}

			if(objectNumber==5){
				if(objectNumber==5 && o5==0){
					o5=game5.playGame(gameMode);
				}
				if(o5!=0){
					cout<<"5. Objenin Oyunu Bitti"<<endl;
				}
			}	

		}
		cout<<"Tüm objelerin oyunu bitti"<<endl;
			
	}

	return 0;
}


ConnectFour::Cell::Cell(char letterr,int rowNumberr,int cellTypee){
	letter=letterr;
	rowNumber=rowNumberr;
	cellType=cellTypee;
}


void const  ConnectFour::initVector(const int &columnSize,const int &rowSize){

	Cell a;
	int i= columnSize;
	int j=rowSize;

	for(int i=0;i<columnSize;i++){    //ikiboyutlu vektör initialize edilir
	    gameCells.push_back(vector<Cell>());
	    for(int j=0;j<rowSize;j++){    
	        gameCells[i].push_back(a);    
	    }
	}

	for(i=0;i<columnSize;i++){
		for(j=0;j<rowSize;j++){
			 gameCells[i][j].setterCellType('.');

		}
	}

}

void const ConnectFour::displayBoard() const{  
	for(char c = 'a' ,i = 0; c <= 'z', i<columnSize; ++c,i++){	/* girilen size kadar a dan baslanarak alfabe sirasiyla print edilir*/	
		if(i == 0){
			cout<<c;
		}	
		else{
			cout<<" "<<c;
		}
	}   	
	cout<<endl;

	for(int i=0;i<rowSize;i++){   // board ekrana basılır
	for(int j=0;j<columnSize;j++){
		cout << gameCells[i][j].getterCellType();
		cout <<" ";
	}
	cout<<endl;
}

}

int const ConnectFour::setVector(string letter,const char &mark){

	int rowCounter;       
	int beraberlik=0;
	int flag=0;
	int columnCounter=0;
	rowCounter=rowSize;
	while(1){   // seçilen sutuna göre tas koyma uygunlugu kontrol edilir ve uygunsa tas koyulur*/

		if(gameCells[rowCounter-1][int(letter[0])-int('A')].getterCellType()=='.' && int(letter[0])<int('A')+columnSize && int(letter[0])>=int('A')){ /* secilen sutunun rowCounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
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

int const ConnectFour::inputHeightSize(){   // kullanıdan height alınır
  
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

int const ConnectFour::inputWidhtSize(){   // kullanıcıdan weight alınır

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


int const ConnectFour::getGameType(void){
	string flag;
	cout<<"player | computer:"<<endl;     // kullanıcıdan oyun tipi alınır
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


string const  ConnectFour::getLetter(const char &mark) const{
	string letter;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi srerun edilir*/
	getline(cin,letter);

	if((letter[0]=='L' && letter[1]=='O' && letter[2]=='A'&& letter[3]=='D') || (letter[0]=='S' && letter[1]=='A' && letter[2]=='V'&& letter[3]=='E')){
		//cin.ignore();
	}
	while(letter.size()!=1 && letter.size()!=0 && ((letter[0]!='L' && letter[1]!='O' && letter[2]!='A'&& letter[3]!='D') && (letter[0]!='S' && letter[1]!='A' && letter[2]!='V'&& letter[3]!='E')) ){
		cerr<<"GECERLI BIR SUTUN GIRINIZ"<<endl;
		getline(cin,letter);
	}
	while(letter.size()==0 ){
		/*cerr<<"Hatali giris"<<endl;
		cerr<<"Sutun Harfi Seciniz"<<endl;*/
		getline(cin,letter);
	}
	if (letter[0] >= 'a' && letter[0] <= 'z') {  /* alinan harf bilgisi kucgkse buyultulur*/
		letter[0] = letter[0] -'a'+'A';
	}

	return letter;
}


int  const ConnectFour::controlfour(const vector<vector<Cell>> &gameCells,const int &rowSize,const int &columnSize,const int &rowCounter,const int &columnCounter,const char &letter,const char &cursor) const{
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

int const ConnectFour::emptyMapControl(const vector< vector<Cell> > &gameCells,const int &rowSize,const int &columnSize) const{
	int flag =0;


	for(int j=0 ; j<columnSize ; j++){   /*haritanin ici dolasilir ve bosluk varmi diye bakilir eger varsa flag 1 olur ve bosluk oldugu anlasilir*/
		for(int k=0; k<rowSize; k++){
			if(gameCells[k][j].getterCellType()=='.'){
				flag = 1;
			}
		}	
	}
	if(flag==0){
		return -2;
	}

}

int const ConnectFour::compSetVector(const int &rowSize,const int &columnSize){
	int flag1=0;
	int flag2=0;
	int flag3=0;
	int columnCounter=0;
	auto beraberlik=0;
	int counter=0;
	
	if(gameCells[rowSize -1][columnSize/2].getterCellType()=='.'){  /* oyunun baslangicinda bilgisayar haritanin ortasinin en altta kalan uygun noktasina O koyar ve bu bir kez gerceklesir*/
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
			if((controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==14 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==15 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==16 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==17 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==18 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==19 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==20 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==21 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==22 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==23 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==24 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==25 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'O')==26) && gameCells[j][k].getterCellType()=='.'){
				/* bir yerde uc tane yan yana O bulunuyorsa ve o uclunun yanindaki yer uygunsa(alti dolu kendisi bos ve haritanin disinda olmayan) oraya 'o' konulur*/
				if(j+1<rowSize){  /*tabanda degilse*/

					if( gameCells[j+1][k].getterCellType()!='.' ){

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
					if(((gameCells[j][k].getterCellType()=='.'  && (gameCells[j+1][k].getterCellType()!='.' ) )) ){

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

					if((j==rowSize-1 || gameCells[j+1][k+1].getterCellType()=='O' || gameCells[j+1][k+1].getterCellType()=='X' ) && gameCells[j][k+1].getterCellType()=='.' ){
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
					else if((j==rowSize-1 || gameCells[j+1][k-1].getterCellType()=='O' || gameCells[j+1][k-1].getterCellType()=='X') &&  gameCells[j][k-1].getterCellType()=='.' && k-1>=0 ){
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
						
					else if((j-1==rowSize-1 || gameCells[j][k].getterCellType()=='O' || gameCells[j][k].getterCellType()=='X') && gameCells[j-1][k].getterCellType()=='.'){
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


					else if(gameCells[j][k+1].getterCellType()=='O' &&  gameCells[j][k-1].getterCellType()=='.' ){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(j+1<=rowSize-1){													
							if(gameCells[j+1][k-1].getterCellType()!='.'){
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
					else if(gameCells[j][k-1].getterCellType()=='O' && gameCells[j][k+1].getterCellType()=='.' ){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(j+1<=rowSize-1){													
							if(gameCells[j+1][k+1].getterCellType()!='.'){

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

					else if(gameCells[j+1][k-1].getterCellType()=='.' && j+2>=0 && k-1>=0 && j+2<rowSize && k-1<columnSize){
						/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
						if(gameCells[j+2][k-1].getterCellType()!='.'){

							
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
								if(gameCells[jj][kk].getterCellType()=='.'){
									if(gameCells[jj+1][kk].getterCellType()!='.'){
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

int const ConnectFour::lower(const int rowSize,const int rowCounter,char letter,char cursor ,int flag){

		// kazanma durumda kazanma durumunu sağlayan 4 lu taslar ufaltılır
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


char const ConnectFour::writeFile(const int &rowSize,const int &columnSize,string letter,const char &mark,const char &gametipi) const{
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
			dosya<<" "<<c;
		}
	}   	
	dosya<<endl;


	for(int j=0 ; j<rowSize; j++){ /* alfabenin altina sizexsize lik bir map dosyaya print edilir*/
		for(int k=0; k<columnSize; k++){
			dosya<<gameCells[j][k].getterCellType();
			cout<<gameCells[j][k].getterCellType();
			cout<<" ";
			dosya<<" ";
		}
		dosya<<endl;
		cout<<endl;
	}	
					
	dosya.close();   /* dosya kapatilir*/
	cout<<"Sutun Harfi Seciniz"<<endl;
	letter = getLetter('X');     /* kullanicidan harf almaya devam edilir*/

}

char const  ConnectFour::readFile(string letter){
	int i=0;
	int j=0;
	string filename1;
	char sira;

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

	initVector(rowSize,columnSize);

	for(int k=0;k<rowSize;k++){    /*dosyanin icindeki tum veriyi sirasyla ikiboyutlu maparrayime attim*/
		for(int l=0;l<columnSize;l++){
			char a;
			dosya>>a;
			gameCells[k][l].setterCellType(a);
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
			if(setVector(letter,'X')==1){
				displayBoard();
				cout<<"Oyuncu kazandi"<<endl;	
				return -3 ;
			}
			//game1.displayBoard();
			cout<<endl;

			if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
				cout<<"Kazanan Yok"<<endl;	
				break;
			}

			if(compSetVector(rowSize,columnSize)==0){
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
				if(setVector(letter,'X')==1){
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
				if(setVector(letter,'O')==2){
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
				if(setVector(letter,'O')==2){
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
				if(setVector(letter,'X')==1){
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



int const ConnectFour::playGame(const char &gameMode){ 
	string letter;
	string filename;  // iki taş atımı yapılır bunun için play fonksiyonları kullanılır
	int flag=0;
	if(gameMode=='S' || gameMode=='s'){  
		initVector(rowSize,columnSize);
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



int const ConnectFour::playGame(){
	string letter;
	string filename;    // iki taş atımı yapılır bunun için play fonksiyonları kullanılır
	int flag=0;
	
	initVector(rowSize,columnSize);
	while(getGameType()==-1){
		cerr<<"Hatali Giris Yaptiniz:"<<endl;
		getGameType();
	}
	
	if(gameType=='P'){
		int counter=0;
		while(1){
			displayBoard();
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

int const ConnectFour::playX(const char &gameMode,const string &letter){    // multi modda 1. oyuncu için tek bir tas atımı ıcın gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alır
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
	int d=setVector(letter,sira);
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
int const ConnectFour::playO(const char &gameMode,const string &letter){  // multi modda 2. oyuncu için tek bir tas atımı ıcın gerekli olan fonskiyon , parametre olarak pozisyon(letter) ve gameMode alır
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
	int d=setVector(letter,sira);
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
int const ConnectFour::playX(const string &letter,const char &gameType){ // tekli modda 1. oyuncu için tek bir tas atımı ıcın gerekli olan fonskiyon , parametre olarak pozisyon(letter) alır
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
	int d=setVector(letter,sira);
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
int const ConnectFour::playO(const string &letter,const char &gameType){ // tekli modda 2. ouncu için tek bir tas atımı ıcın gerekli olan fonskiyon , parametre olarak pozisyon(letter) alır
	int a=2;
	char sira='O'; 
	if(letter[0]=='S' && letter[1]=='A' && letter[2]=='V' && letter[3]=='E'){/* eger writeFile komutu girilirse*/

		writeFile(rowSize,columnSize,letter,sira,gameType);		
	}
	if(letter[0]=='L' && letter[1]=='O' && letter[2]=='A' && letter[3]=='D'){/* eger writeFile komutu girilirse*/
		if(readFile(letter)==-3){
			return -3;
		}	
	}
	int d=setVector(letter,sira);
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

int const ConnectFour::play( const char &gameMode){  // multi modda bilgisayarın tas atımı yapması için gerekli olan fonskiyon
			
		if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
			cout<<"Kazanan Yok"<<endl;	
			return -3;
		}

		if(compSetVector(rowSize,columnSize)==0){
			return 2;
		}
		if(gameMode=='M' || gameMode=='m'){
			return 0;
		}
}

int const  ConnectFour::play(){   // tekli modda bilgisayarın tas atımı yapması için gerekli olan fonskiyon
	
	if(emptyMapControl(gameCells,rowSize,columnSize)==-2){
		cout<<"Kazanan Yok"<<endl;	
		return -3;
	}
	if(compSetVector(rowSize,columnSize)==0){
		return 2;
	}
}
			

bool const ConnectFour::compare(ConnectFour const &obje) const {
	int xCounter1=0;
	int xCounter2=0;
	int columnCounter=0;

	for(int j=0 ; j<rowSize ; j++){   /*ilk obje için üçlü durum varmı diye kontrol edlir*/
	    for(int k=0; k<columnSize; k++){
				if(((controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==1 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==2 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==3 ) && gameCells[j][k].getterCellType()=='.'  || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==4 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==5 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==6 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==7 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==8 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==9 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==10 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==11 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==12 || controlfour(gameCells,rowSize,columnSize, j+1,columnCounter, char(int('A')+k),'X')==13)  && gameCells[j][k].getterCellType()=='.'){
				xCounter1++;
			}
		}	
	}

	for(int j=0 ; j<obje.rowSize ; j++){   /*parametre olarak gelen obje için üçlü durum varmı diye kontrol edilir*/
	    for(int k=0; k<obje.columnSize; k++){
				if(((controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==1 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==2 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==3 ) && obje.gameCells[j][k].getterCellType()=='.'  || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==4 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==5 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==6 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==7 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==8 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==9 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==10 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==11 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==12 || controlfour(obje.gameCells,obje.rowSize,obje.columnSize, j+1,columnCounter, char(int('A')+k),'X')==13)  && obje.gameCells[j][k].getterCellType()=='.'){
				xCounter2++;
			}
		}	
	}

	if(xCounter1>xCounter2){
		return true;    // obje 1 , 2 den iyiyse (3 lü X durum sayısı fazlalığı)
	}
	else {
		return false;  // obje 1 , 2 den iyi değilse
	}
}