#include <iostream>

using namespace std;

#define maxsize 20


int getMapSize(void);
/*oyun haritasinin kenar uzunlugu bilgisini kullanicidan alir*/
/*gecersiz bir kenar uzunlugunda -1 return eder, gecerli bir size girildiginde size i return eder*/
char getGameType(void);
/*kullanicidan aldigi inputa gore user1-user2 icin P , user-computer icin C , yanlis giriste -1 return eder.*/
char initMap(char maparray[maxsize][maxsize], int size);
/* maxsize ye maxsize lik iki boyutlu arrayin icini . karakteriyle doldurur*/
char printMap(char maparray[maxsize][maxsize], int size);
/*getMapSize fonksiyonundan gelen size'i ve arrayi parametre olarak alir ardindan array i print eder*/
char getLetter(void);
/*kullanicidan oyun haritasindan bir harf(sutun) alir ve return eder*/
int controlfour(char maparray[maxsize][maxsize],int size,int sizecounter,char letter,char cursor);
/*yanyana yada capraz 4 tane ayni karakter olup olmadigini kontrol ediyor ve olusan farkli durumlara gore farkli degerler return ediyor*/
char toCapital(char letter);
/*gelen harf kucukse buyuk harfe ceviriyor ve buyuk halini return ediyor*/

int emptyMapControl(char maparray[maxsize][maxsize],int size);
/*haritada bos yer olup olmadigini kontrol ediyor eger bos yer kalmazsa -2 return ediyor*/

int lower(char maparray[maxsize][maxsize],int size,int sizecounter,char letter,char cursor, int flag);
/*kazanma durumlarinda olusan dortluyu ufaltiyor ve hangi duruma gore ufalttiysa onu return ediyor*/

int gameTypeOne(int size,char maparray[maxsize][maxsize]);
/*user1 vs. user2 nin oynanmasi icin gereken fonksiyon*/

int gameTypeTwo(int size,char maparray[maxsize][maxsize]);
/*user vs computer oynanamasi icin gereken fonksiyon*/



int main(int argc, char** argv) {
	char maparray[maxsize][maxsize]; /*oyun haritasi*/
	
	int size=getMapSize();   /*kullanicidan haritanin boyutu alinir*/

	while(size == -1){   /*harita boyutu istenilen sartlari saglamiyorsa tekrar harta boyutu istenir*/
	    cout<<"Gecersiz sayi girdiniz"<<endl;
		size=getMapSize();
	}

	char gametype = getGameType(); /*oyunun bilgisayara karsimi yoksa kullaniciya karsimi oynanacagi bilgisi alinir*/

	while(gametype==-1){  /*oyun tipi istenmeyen sartlari saglarsa kullanicidan tekrar oyun tipi istenir*/
		cout<<"Gecersiz Giris Yaptiniz"<<endl;
		gametype = getGameType();
	}


	if(gametype==1){   /*user1 vs. user2 icin oyun baslatilir*/
		gameTypeOne(size,maparray);
	}

	//G GGCDF

	if(gametype==2){    /*user vs. computer icin oyun baslatilir*/
		gameTypeTwo(size,maparray);
	}
		
	return 0;
}



int getMapSize(void){

	int size=0;
	int a = 0;


	while (a == 0){    /*haritanin size inin integer olmasi icin yapilan konrolun dongusu*/
		a = 1;

		cout<<"Haritanin Kenar Uzunlugunu Secin(4,6,8,10...20) =  ";
		cin >> size;

			if(cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "Lutfen Sayi Giriniz" << endl;
				a=0;
			}
	}

	if(size%2==0 && size>=4 && size<=maxsize){  /*  harita size inin 4 ten baslayarak maxsize dahil olacak sekilde 2 nini katlari olmali eger olursa size return edilir olmazsa -1 return edilir*/
		return size;
	}

	else{
		return -1;
	}
}

char getGameType(void){

	char flag;
	cout<<"For Player1 vs. Player2 : Press P"<<endl;
	cout<<"For Player vs. Computer : Press C"<<endl;
	cin>>flag;
	if(flag == 'P' || flag == 'p'){ /* kullanici P  yada p girerse user1 vs user2 oyunu baslar*/
		return 1;
	}
	else if(flag == 'C' || flag == 'c' ){ /* kullanici C yada c girerse user vs. computer oyunu baslar*/
		return 2;
	}
	else{   /* diger durumlarda -1 return edilir*/
		return -1;
	}
}

char initMap(char maparray[maxsize][maxsize],int size){  /* maxsize ye maxsize lik iki boyutlu arrayin icini . karakteriyle doldurur*/

	for(int j=0 ; j<size ; j++){
		for(int k=0; k<size; k++){
			maparray[j][k]='.';
		}
	}

}

char printMap(char maparray[maxsize][maxsize],int size){

	for(char c = 'a' ,i = 0; c <= 'z', i<size; ++c,i++){	/* girilen size kadar a dan baslanarak alfabe sirasiyla print edilir*/	
		if(i == 0){
			cout<<c;
		}	
		else{
			cout<<" "<<c;
		}
	}   	
	cout<<endl;

	for(int j=0 ; j<size ; j++){ /* alfabenin altina sizexsize lik bir map print edilir*/
		for(int k=0; k<size; k++){
			cout<<maparray[j][k];
			cout<<" ";
		}
		cout<<endl;
	}

}


char getLetter(void){
	char letter;  /*kullanicidan hangi sutununa kendi tasini koyacagi bilgisi alinir ve o bilgi srerun edilir*/
	cin>>letter;
	return letter;
}


char toCapital(char letter){

	if (letter >= 'a' && letter <= 'z') {  /* alinan harf bilgisi kucgkse buyultulur*/
	letter = letter -'a'+'A';
	}
	return letter;
}

int emptyMapControl(char maparray[maxsize][maxsize],int size){
	int flag =0;
	for(int j=0 ; j<size ; j++){   /*haritanin ici dolasilir ve bosluk varmi diye bakilir eger varsa flag 1 olur ve bosluk oldugu anlasilir*/
		for(int k=0; k<size; k++){
			if(maparray[j][k]=='.'){
				flag = 1;
			}
		}	
	}
	if(flag==0){
		return -2;
	}
}

int controlfour(char maparray[maxsize][maxsize],int size,int sizecounter,char letter,char cursor){
	int flag=0;

	/* her yeni bir tas koyuldugunda yatayda 4 fakli durum icin 4 lu durum saglanmismi diye kontrol edilir*/
	if(maparray[sizecounter-1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1][int(letter)-int('A')+2]==cursor && maparray[sizecounter-1][int(letter)-int('A')+3]==cursor){
		flag=1;
		
	}
	if(maparray[sizecounter-1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1][int(letter)-int('A')+2]==cursor){
		flag=2;
			
	}
	if(maparray[sizecounter-1][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1][int(letter)-int('A')+1]==cursor){
		flag=3;
			
	}
	if(maparray[sizecounter-1][int(letter)-int('A')-3]==cursor && maparray[sizecounter-1][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1][int(letter)-int('A')-1]==cursor){
		flag=4;
			
	}



	/*her yeni bir tas koyuldugunda duseyde 4 lu durum saglanmismi diye kontrol edilir*/

	if(size-4>=sizecounter-1){
		if(maparray[sizecounter-1+1][int(letter)-int('A')]==cursor && maparray[sizecounter-1+2][int(letter)-int('A')]==cursor && maparray[sizecounter-1+3][int(letter)-int('A')]==cursor){
			flag=5;
				
		}
	}




	/*her yeni bir tas koyuldugunda sol capraz sekilde 4 farkli durum icin 4 lu durum saglanmismi diye kontrol edilir*/
	if(sizecounter-1>=3 && int(letter)-int('A')>=3 && size-1>=sizecounter-1 && size-1>=int(letter)-int('A') ){
		if(maparray[sizecounter-1-3][int(letter)-int('A')-3]==cursor && maparray[sizecounter-1-2][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1-1][int(letter)-int('A')-1]==cursor){
				flag=6;
					
		}
	}

	if(sizecounter-1>=2 && int(letter)-int('A')>=2 && size-2>=sizecounter-1 && size-2>=int(letter)-int('A')){
		if(maparray[sizecounter-1-2][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1-1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1+1][int(letter)-int('A')+1]==cursor){
			flag=7;
				
		}
	}

	if(sizecounter-1>=1 && int(letter)-int('A')>=1 && size-3>=sizecounter-1 && size-3>=int(letter)-int('A') ){
		if(maparray[sizecounter-1-1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1+1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1+2][int(letter)-int('A')+2]==cursor){
			flag=8;
				
		}
	}


	if(sizecounter-1>=0 && int(letter)-int('A')>=0 && size-4>=sizecounter-1 && size-4>=int(letter)-int('A') ){
		if(maparray[sizecounter-1+1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1+2][int(letter)-int('A')+2]==cursor && maparray[sizecounter-1+3][int(letter)-int('A')+3]==cursor){
			flag=9;
				
		}
	}




	/*her yeni bir tas koyuldugunda sag capraz sekilde 4 farkli durum icin 4 lu durum saglanmismi diye kontrol edilir*/

	if(sizecounter-1>=3 && int(letter)-int('A')<=size-4 && size-1>=sizecounter-1 && 0<=int(letter)-int('A')){
		if(maparray[sizecounter-1-3][int(letter)-int('A')+3]==cursor && maparray[sizecounter-1-2][int(letter)-int('A')+2]==cursor && maparray[sizecounter-1-1][int(letter)-int('A')+1]==cursor){
			flag=10;	
				
		}
	}


	if(sizecounter-1>=2 && int(letter)-int('A')<=size-3 && size-2>=sizecounter-1 && 1<=int(letter)-int('A')){
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1-1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1-2][int(letter)-int('A')+2]==cursor){
			flag=11;	
				
		}
	}


	if(sizecounter-1>=1 && int(letter)-int('A')<=size-2 && size-3>=sizecounter-1 && 2<=int(letter)-int('A')){
		if(maparray[sizecounter-1+2][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1-1][int(letter)-int('A')+1]==cursor && maparray[sizecounter-1+1][int(letter)-int('A')-1]==cursor){
			flag=12;	
				
		}
	}


	if(sizecounter-1>=0 && int(letter)-int('A')<=size-1 && size-4>=sizecounter-1 && 3<=int(letter)-int('A')){
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]==cursor && maparray[sizecounter-1+2][int(letter)-int('A')-2]==cursor && maparray[sizecounter-1+3][int(letter)-int('A')-3]==cursor){
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

int lower(char maparray[maxsize][maxsize],int size,int sizecounter,char letter,char cursor ,int flag){

	/* controlfour fonksiyonundan gelen return degerleri her bir durum icin farkliydi , ordan gelen return degerine gore hangi lokasyonun 4 lu duruma geldigi bilgisi anlasiliyor ve bu duruma gore o 4 lu ufaltiliyor*/

	if(flag==1 || flag==14){
		if(maparray[sizecounter-1][int(letter)-int('A')+1]=='X'){
			maparray[sizecounter-1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1][int(letter)-int('A')+3]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1][int(letter)-int('A')+1]=='O'){
			maparray[sizecounter-1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1][int(letter)-int('A')+3]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}


	if(flag==2 || flag==15){
		if(maparray[sizecounter-1][int(letter)-int('A')-1]=='X'){
			maparray[sizecounter-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1][int(letter)-int('A')-1]=='O'){
			maparray[sizecounter-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}


	if(flag==3 || flag==16){
		if(maparray[sizecounter-1][int(letter)-int('A')-2]=='X'){
			maparray[sizecounter-1][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1][int(letter)-int('A')-2]=='O'){
			maparray[sizecounter-1][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==4 || flag==17){
		if(maparray[sizecounter-1][int(letter)-int('A')-3]=='X'){
			maparray[sizecounter-1][int(letter)-int('A')-3]='x';
			maparray[sizecounter-1][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1][int(letter)-int('A')-3]=='O'){
			maparray[sizecounter-1][int(letter)-int('A')-3]='o';
			maparray[sizecounter-1][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==5 || flag==18){
		if(maparray[sizecounter-1+1][int(letter)-int('A')]=='X'){
			maparray[sizecounter-1+1][int(letter)-int('A')]='x';
			maparray[sizecounter-1+2][int(letter)-int('A')]='x';
			maparray[sizecounter-1+3][int(letter)-int('A')]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1+1][int(letter)-int('A')]=='O'){
			maparray[sizecounter-1+1][int(letter)-int('A')]='o';
			maparray[sizecounter-1+2][int(letter)-int('A')]='o';
			maparray[sizecounter-1+3][int(letter)-int('A')]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==6 || flag==19){
		if(maparray[sizecounter-1-3][int(letter)-int('A')-3]=='X'){
			maparray[sizecounter-1-3][int(letter)-int('A')-3]='x';
			maparray[sizecounter-1-2][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1-3][int(letter)-int('A')-3]=='O'){
			maparray[sizecounter-1-3][int(letter)-int('A')-3]='o';
			maparray[sizecounter-1-2][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==7 || flag==maxsize){
		if(maparray[sizecounter-1-2][int(letter)-int('A')-2]=='X'){
			maparray[sizecounter-1-2][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1][int(letter)-int('A')+3]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1-2][int(letter)-int('A')-2]=='O'){
			maparray[sizecounter-1-2][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1+1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==8 || flag==21){
		if(maparray[sizecounter-1-1][int(letter)-int('A')-1]=='X'){
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1+1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1+2][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1-1][int(letter)-int('A')-1]=='O'){
			maparray[sizecounter-1-1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1+1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1+2][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==9 || flag==22){
		if(maparray[sizecounter-1+1][int(letter)-int('A')+1]=='X'){
			maparray[sizecounter-1+1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1+2][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1+3][int(letter)-int('A')+3]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1+1][int(letter)-int('A')+1]=='O'){
			maparray[sizecounter-1+1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1+2][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1+3][int(letter)-int('A')+3]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}



	if(flag==10 || flag==23){
		if(maparray[sizecounter-1-3][int(letter)-int('A')+3]=='X'){
			maparray[sizecounter-1-3][int(letter)-int('A')+3]='x';
			maparray[sizecounter-1-2][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1-1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1-3][int(letter)-int('A')+3]=='O'){
			maparray[sizecounter-1-3][int(letter)-int('A')+3]='o';
			maparray[sizecounter-1-2][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1-1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==11 || flag==24){
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]=='X'){
			maparray[sizecounter-1+1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1-1][int(letter)-int('A')+1]='x';
			maparray[sizecounter-1-2][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]=='O'){
			maparray[sizecounter-1+1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1-1][int(letter)-int('A')+1]='o';
			maparray[sizecounter-1-2][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==12 || flag==25){
		if(maparray[sizecounter-1+2][int(letter)-int('A')-2]=='X'){
			maparray[sizecounter-1+2][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1][int(letter)-int('A')+2]='x';
			maparray[sizecounter-1][int(letter)-int('A')+3]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1+2][int(letter)-int('A')-2]=='O'){
			maparray[sizecounter-1+2][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1][int(letter)-int('A')+2]='o';
			maparray[sizecounter-1][int(letter)-int('A')+3]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}

	if(flag==13 || flag==26){
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]=='X'){
			maparray[sizecounter-1+1][int(letter)-int('A')-1]='x';
			maparray[sizecounter-1+2][int(letter)-int('A')-2]='x';
			maparray[sizecounter-1+3][int(letter)-int('A')-3]='x';
			maparray[sizecounter-1][int(letter)-int('A')]='x';
		}
		if(maparray[sizecounter-1+1][int(letter)-int('A')-1]=='O'){
			maparray[sizecounter-1+1][int(letter)-int('A')-1]='o';
			maparray[sizecounter-1+2][int(letter)-int('A')-2]='o';
			maparray[sizecounter-1+3][int(letter)-int('A')-3]='o';
			maparray[sizecounter-1][int(letter)-int('A')]='o';
		}
	}
}

int gameTypeTwo(int size,char maparray[maxsize][maxsize]){

		
		char letter;
		initMap(maparray,maxsize);
		int hfourcounter=0; /* gerekli  degiskenler*/
		int vflag=0;
		int hflag=0;
		int hvflag=0;
		int vhflag=0;
		int flag=0;
		int beraberlik=0;
		int flag1=0;
		int flag2=0;
		int flag3=0;
		int counter=0;


		while(1){
			int sizecounter=size;
			if(counter==0){
				printMap(maparray,size); /* harita print edilir 1 kereligine*/
			}
			cout<<"Sutun Harfi Seciniz"<<endl; /* kullanidan sutun harfi alir*/
			letter = getLetter();
			letter=toCapital(letter);  /* kucukse buyultulur*/

			while(1){

				if(maparray[sizecounter-1][int(letter)-int('A')]=='.' && int(letter)<int('A')+size && int(letter)>=int('A')){ /* secilen sutunun sizecounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
					maparray[sizecounter-1][int(letter)-int('A')]='X'; /* eger bossa oraya X koyulur, harita print edilir, haritada bosluk kaldimi diye konrtol edilir, 4lu yanyana geldimi diye kontrol edilir ve break yapilir */
									printMap(maparray,size);


					if(emptyMapControl(maparray,size)==-2){
						beraberlik=1;
						break;

					}

					flag=controlfour(maparray,size,sizecounter,letter,'X');
					
					break;
				}
		
		
				else{    /*eger sizecounter-1 . satirda bir sey varsa */

					if(sizecounter>1){  /* sizecounter 1 den buyukse 1 ust satira bakmak icin sizecounter i 1 azaltiriz*/

						sizecounter--;
					}
					else if(int(letter)-int('A')>=size){  /* secilen sutun oyun alaninin disindayse kullanici uyarilir ve tekrar gerekli bilgiler istenir*/

							cout<<"(1.Oyuncu) Oyun Alaninin Disina Ciktiniz Tekrar Deneyiniz"<<endl;
							letter = getLetter();
							letter=toCapital(letter);

							sizecounter=size;

					}
					else if(int(letter)<int('A')+size && int(letter)>=int('A') ){ /* eger bir sutunun tamami dolmusssa ve o sutun secilmisse kullanici uyarilir ve derekli bilgiler yeniden istenir*/


							cout<<"(1.Oyuncu) Bu Sutun Bitti Tekrar Seciniz"<<endl;
							letter = getLetter();
							letter=toCapital(letter);

							sizecounter=size;

					}
					else{   /* eger i u s gibi turkce harfler kullanilirsa kullanici uyarilir ve tekrar gerekli bilgiler istenir*/

						cout<<"Turkce Karakter Kullanmayiniz"<<endl;
						letter = getLetter();
						letter=toCapital(letter);

						sizecounter=size;
					}
				}
			}

			if((flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7  || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13) || beraberlik==1){
			/*eger X icin 4 lu bir durum olusmussa flag 1 ile 13 arasindadir*/

				lower(maparray,size,sizecounter,letter,'X',controlfour(maparray,size,sizecounter,letter,'X'));
				/* o dortlu duruma gore X ler ufaltilir*/
				printMap(maparray,size);
				/*ve harita print edilir*/

				cout<<"Oyuncu Kazandi"<<endl;
				break;
			}


			if(counter==0 && maparray[size -1][size/2]=='.'){  /* oyunun baslangicinda bilgisayar haritanin ortasinin en altta kalan uygun noktasina O koyar ve bu bir kez gerceklesir*/
				maparray[size -1][size/2]='O';
				counter=1;
				printMap(maparray,size);
			}
			else if(counter==0 ){
				maparray[size -2][size/2]='O';
				counter=1;
				printMap(maparray,size);
			}



			for(int j=0 ; j<size ; j++){   /* bilgisayar kendi taslarini (O) uc tane yan yana getirmissse baska hicbir lokasyana bakmadan kendini direk dotlemesi icin gerekli for dongusu*/
				for(int k=0; k<size; k++){


					if((controlfour(maparray,size,j+1,char(int('A')+k),'O')==14 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==15 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==16 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==17 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==18 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==19 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==maxsize || controlfour(maparray,size,j+1,char(int('A')+k),'O')==21 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==22 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==23 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==24 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==25 || controlfour(maparray,size,j+1,char(int('A')+k),'O')==26) && maparray[j][k]=='.'){
						/* bir yerde uc tane yan yana O bulunuyorsa ve o uclunun yanindaki yer uygunsa(alti dolu kendisi bos ve haritanin disinda olmayan) oraya 'o' konulur*/
						if(j+1<size){  /*tabanda degilse*/

							if( maparray[j+1][k]!='.' ){

								maparray[j][k]='o';
								lower(maparray,size,j+1,char(int('A')+k),'O',controlfour(maparray,size,j+1,char(int('A')+k),'O'));
								printMap(maparray,size);
								flag2=1;
								break;
							}
						}

						else if(j==size-1){  /* en tabandayse*/



							maparray[j][k]='o';
							lower(maparray,size,j+1,char(int('A')+k),'O',controlfour(maparray,size,j+1,char(int('A')+k),'O'));
							printMap(maparray,size);
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
				cout<<"Bilgisayar Kazandi"<<endl;  /* ve bilgisayar kazandigi icin ekrana bu bilgi yazilir*/
				break;
			}	

			/* eger kullanici 3 tane tasini yan yana getirmisse bilgisayarin bunu anlamasi ve  kendisini 4 lemekten sonra baska hic bir sey yapmadan kullanicinin kendisini 4 lemesini engellemesi icin gerekli for dongusu*/
			for(int j=0 ; j<size ; j++){
				for(int k=0; k<size; k++){

					if(((controlfour(maparray,size,j+1,char(int('A')+k),'X')==1 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==2 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==3 ) && maparray[j][k]=='.' || controlfour(maparray,size,j+1,char(int('A')+k),'X')==4 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==5 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==6 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==7 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==8 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==9 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==10 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==11 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==12 || controlfour(maparray,size,j+1,char(int('A')+k),'X')==13)  && maparray[j][k]=='.'){
						
						/*eger engellencek yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve  iki for dongusundende cikilir*/
							if((maparray[j][k]=='.' && (maparray[j+1][k]!='.' || j==size-1)) ){
								maparray[j][k]='O';
								printMap(maparray,size);
								flag3=1;
								break;
							}					
						
					}
				}
				if(flag3==1){
					break;
				}			
			}
		

			if(flag3==0 && counter==2){ /* dortleme durumlari olusmadiysa yada kullanicinin 3lemesi engellenmediyse*/

				for(int k=0; k<size; k++){
					for(int j=0 ; j<size ; j++){

						if(maparray[j][k]=='O'){ /* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
							//a e e h f g e

							if((j==size-1 || maparray[j+1][k+1]=='O' || maparray[j+1][k+1]=='X' ) &&  maparray[j][k+1]=='.' ){
								/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								maparray[j][k+1]='O';

								flag2=controlfour(maparray,size,j+1,char(int('A')+k+1),'O');
								printMap(maparray,size);  /* harita print edilir*/
								flag1=1;
								break;
								
							}
							else if((j==size-1 || maparray[j+1][k-1]=='O' || maparray[j+1][k-1]=='X') &&  maparray[j][k-1]=='.' && k-1>=0 ){
									/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								maparray[j][k-1]='O';


								flag2=controlfour(maparray,size,j+1,char(int('A')+k-1),'O');
								printMap(maparray,size);  /* harita print edilir*/
								flag1=1;
								break;
							}
								
							else if((j-1==size-1 || maparray[j][k]=='O' || maparray[j][k]=='X') && maparray[j-1][k]=='.'){
								/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								maparray[j-1][k]='O';
														

								flag2=controlfour(maparray,size,j,char(int('A')+k),'O');
								printMap(maparray,size);  /* harita print edilir*/
								flag1=1;
								break;
								}


							else if(maparray[j][k+1]=='O' &&  maparray[j][k-1]=='.' ){
								/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								if(j+1<=size-1){													
									if(maparray[j+1][k-1]!='.'){
										maparray[j][k-1]='O';					

										flag2=controlfour(maparray,size,j+1,char(int('A')+k-1),'O');
										printMap(maparray,size);  /* harita print edilir*/
										flag1=1;
										break;
									}
								}	
							}
							else if(maparray[j][k-1]=='O' && maparray[j][k+1]=='.' ){
								/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								if(j+1<=size-1){													
									if(maparray[j+1][k+1]!='.'){

										maparray[j][k+1]='O';

										flag2=controlfour(maparray,size,j+1,char(int('A')+k+1),'O');
										printMap(maparray,size);   /* harita print edilir*/
										flag1=1;
										break;
									}
								}
							}

							else if(maparray[j+1][k-1]=='.'){
								/* bir yerde 'O' varsa ve yanina koyulacak yer uygunsa ( bos ve alti dolu ve haritanin icinde) oraya O koyulur ve 4 leme durumu saglanmismi diye kontrol edilir*/
								if(maparray[j+2][k-1]!='.'){

									
									maparray[j+1][k-1]='O';

									flag2=controlfour(maparray,size,j+2,char(int('A')+k-1),'O');
									printMap(maparray,size);   /* harita print edilir*/
									flag1=1;
									break;
								}	
							}
							//egehfhhdegffg
							else{ /* eger hicbir durum saglanmiyorsa haritada gorulen il bos ve uygun ( bos ve alti dolu ve haritanin icinde) yere O koyulur*/
								int k1=0;
								int j1=0;


								for(int kk=0; kk<size ; kk++){
									for(int jj=0 ; jj<size ; jj++){
										if(maparray[jj][kk]=='.'){
											if(maparray[jj+1][kk]!='.'){
												maparray[jj][kk]='O';
												printMap(maparray,size);  /* harita print edilir*/


												flag1=1;
												break;
											}
											else if(jj==size-1){
												maparray[jj][kk]='O';
												printMap(maparray,size);   /* harita print edilir*/

												flag1=1;
												break;
											}

										}

									}
									if(flag1==1){
										break;
									}
								}
								
								break;

							}
						}
					}	

					if(flag1==1){
						flag1=0;
						break;
					}
				}
			}
			else{
				flag3=0;
				counter=2;
			}	

			if((flag2==14 || flag2==15 || flag2==16 || flag2==17 || flag2==18 || flag2==19 || flag2==maxsize|| flag2==21 || flag2==22 || flag2==23 || flag2==24 || flag2==25 || flag2==26)){
				/* bilgisayar icin dortleme durumu olustuysa tum donguden cikilir*/
				break;
			}
	    }
	}		

int gameTypeOne(int size,char maparray[maxsize][maxsize]){



	char letter;
	initMap(maparray,maxsize);  /* gerekli degiskenler*/

	printMap(maparray,size);

	int hfourcounter=0;
	int vflag=0;
	int hflag=0;
	int hvflag=0;
	int vhflag=0;
	int flag=0;
	int beraberlik=0;

	while(1){
		int sizecounter=size;
		cout<<"(1.Oyuncu) Sutun Harfi Seciniz"<<endl;
		letter = getLetter();    /* kullanicidan sutun bilgisi alinir ve eger kucukse buyultulur*/
		letter=toCapital(letter);

		while(1){
			if(maparray[sizecounter-1][int(letter)-int('A')]=='.' && int(letter)<int('A')+size && int(letter)>=int('A')){ /* secilen sutunun sizecounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
				maparray[sizecounter-1][int(letter)-int('A')]='X'; /* eger bossa oraya X koyulur, harita print edilir, haritada bosluk kaldimi diye konrtol edilir, 4lu yanyana geldimi diye kontrol edilir ve break yapilir */
				if(emptyMapControl(maparray,size)==-2){
					beraberlik=1;
					break;
				}

				flag=controlfour(maparray,size,sizecounter,letter,'X');
				printMap(maparray,size);
				break;
			}

			/*eger sizecounter-1 . satirda bir sey varsa */
		
			else{  /* sizecounter 1 den buyukse 1 ust satira bakmak icin sizecounter i 1 azaltiriz*/
				if(sizecounter>1){	
					sizecounter--;
				}
				else if(int(letter)-int('A')>=size){       /* secilen sutun oyun alaninin disindayse kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
					cout<<"(1.Oyuncu) Oyun Alaninin Disina Ciktiniz Tekrar Deneyiniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;

				}
				else if(int(letter)<int('A')+size && int(letter)>=int('A') ){  /* eger bir sutunun tamami dolmusssa ve o sutun secilmisse kullanici uyarilir ve derekli bilgiler yeniden istenir*/
					cout<<"(1.Oyuncu) Bu Sutun Bitti Tekrar Seciniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;

				}
				else{  /* eger i u s gibi turkce harfler kullanilirsa kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
					cout<<"Turkce Karakter Kullanmayiniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;
				}
			}
		}

		if((flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7  || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13) || beraberlik==1){
							/*eger X icin 4 lu bir durum olusmussa flag 1 ile 13 arasindadir*/
			lower(maparray,size,sizecounter,letter,'X',controlfour(maparray,size,sizecounter,letter,'X')); /* o dortlu duruma gore X ler ufaltilir*/
			printMap(maparray,size);  /*ve harita print edilir*/

			break;
		}


		/* sira ikinci oyuncuya gecer */


		sizecounter=size;
		cout<<"(2.Oyuncu) Sutun Harfi Seciniz"<<endl;   /* kullanicidan suun bilgisi alinir ve eger kucukse buyultulur*/
		letter = getLetter();
		letter=toCapital(letter);



		while(1){
		
			if(maparray[sizecounter-1][int(letter)-int('A')]=='.' && int(letter)<int('A')+size && int(letter)>=int('A')){  /* secilen sutunun sizecounter-1. satirinin bos olup olmadigina bakilir ve uygun yer secilmismi diye bakilir*/
				maparray[sizecounter-1][int(letter)-int('A')]='O'; /* eger bossa oraya O koyulur, harita print edilir, haritada bosluk kaldimi diye konrtol edilir, 4lu yanyana geldimi diye kontrol edilir ve break yapilir */
				if(emptyMapControl(maparray,size)==-2){
					beraberlik=1;
				}
				flag=controlfour(maparray,size,sizecounter,letter,'O');
				printMap(maparray,size);

				break;
			}
				
			/*eger sizecounter-1 . satirda bir sey varsa */
			else{ /* sizecounter 1 den buyukse 1 ust satira bakmak icin sizecounter i 1 azaltiriz*/
				if(sizecounter>1){	
					sizecounter--;
				}
				else if(int(letter)-int('A')>size){ /* secilen sutun oyun alaninin disindayse kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
					cout<<"(2.Oyuncu) Oyun Alaninin Disina Ciktiniz Tekrar Deneyiniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;

				}
				else if(int(letter)<int('A')+size && int(letter)>=int('A') ){  /* eger bir sutunun tamami dolmusssa ve o sutun secilmisse kullanici uyarilir ve derekli bilgiler yeniden istenir*/
					cout<<"(2.Oyuncu) Bu Sutun Bitti Tekrar Seciniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;

				}

				else{/* eger i u s gibi turkce harfler kullanilirsa kullanici uyarilir ve tekrar gerekli bilgiler istenir*/
					cout<<"Turkce Karakter Kullanmayiniz"<<endl;
					letter = getLetter();
					letter=toCapital(letter);
					sizecounter=size;
				}
			}
		}

		if((flag==14 || flag==15 || flag==16 || flag==17 || flag==18 || flag==19 || flag==maxsize || flag==21 || flag==22 || flag==23 || flag==24 || flag==25 || flag==26) || beraberlik==1){
			/*eger X icin 4 lu bir durum olusmussa flag 1 ile 13 arasindadir*/
			lower(maparray,size,sizecounter,letter,'O',controlfour(maparray,size,sizecounter,letter,'O')); /* o dortlu duruma gore O lar ufaltilir*/
			printMap(maparray,size); /*ve harita print edilir*/
			break;
		}
	}
	/* controlfour fonksiyonundan gelen return degerlerine gore kimin kazandigi belli olur buna gore ekrana kimin kazan digi yazilir*/
	if((flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
		cout<<"1.oyuncu kazandi"<<endl;	
	}
	if((flag==14 || flag==15 || flag==16 || flag==17 || flag==18 || flag==19 || flag==maxsize || flag==21 || flag==22 || flag==23 || flag==24 || flag==25 || flag==26)){
		cout<<"2.oyuncu kazandi"<<endl;	
	}
	if(beraberlik==1){
		cout<<"Kazanan Yok"<<endl;
	}
}		




