
package connectfour;

import java.awt.Color;  // import edilen paketler
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * This class is the main class for playing the game and it has main method.
 * @serial 1.0.0
 * @author burhan
 * @version 1.0.0
 */
public class ConnectFour extends JFrame  implements MouseListener{ // ConnectFour classı JFrame den extend olur ve MouseListener clasını implement eder
/**
 * Necessary data field
 */
    private int screenWidht; 
    private int screenHeight;
    private Dimension dim;
    private int size; 
    private Cell[][] board;
    private int playColumn;
    private int playRow;
    private char player;
    private int gameMode;
    private int win;
    private JButton jb1;
    private JButton jb2;
    private JPanel jp1;
    private JFrame a;



    /**
     * No Parameter constructor initialize necessary data fields
     */
    public ConnectFour(){

        a = new JFrame(); //Yeni bir Jframe objesi oluşturulur

        jb1= new JButton("One Player"); // buttonlar oluşturulur
        jb2= new JButton("Two Player");
        jp1=new JPanel(); //panel oluşturulur

    }
    /**
     * this method using for playing game 
     */
    public void playGame(){ 
        
        firstMenu(); //kullanıcıdan size in bilgisi alınır

        secondMenu(); // one player mi two player mi diye kullanıcıya sorulur
    }
    /**
     * takes board size from user for game board
     */
    public void firstMenu(){
        /**
         * override for button action
         */
        jb1.addActionListener(new ActionListener() // anonim inner class kullanıldı 
        {
            public void actionPerformed(ActionEvent e){ // eger birinci butona basılırsa gameMode 2 olur
            gameMode = 2;
            a.dispose();
            JPanel sizePanel = new JPanel();  // ardından size bilgisi istenir 
            JTextField sSize = new JTextField(5);

            sizePanel.add(new JLabel("size"));
            sizePanel.add(sSize);


            String input = JOptionPane.showInputDialog(null, "Please Select Board Size?");
            size = Integer.parseInt(input);  // board size ına atanır

            gameBoard();

            }	
        });
        /**
         * override for buttons action
         */
        jb2.addActionListener(new ActionListener() // anonim inner classtır
        {
            @Override
            public void actionPerformed(ActionEvent e){ 
                gameMode = 1;   // eğer ikinci button seçilirse gameMode 1 olur
                a.dispose();


                JPanel sizePanel = new JPanel();
                JTextField sSize = new JTextField(5); // ardından kullanıcıdan size bilgisini alır

                sizePanel.add(new JLabel("size"));
                sizePanel.add(sSize);


                String input = JOptionPane.showInputDialog(null,"Please Select Board Size?");
                size = Integer.parseInt(input);
                gameBoard();


            }
        });

    }
    /**
     * takes game mode user1-comp or user1-user2
     */
    public void secondMenu(){ // kullanıcıdan oyun modu hakkında bilgi alır buttonlar ile
        jp1.add(jb1);
        jp1.add(jb2);

        a.add(jp1);

        a.setTitle("Please Select A Game Mode");
        a.setSize(300,50);
        a.setVisible(true);
        a.setDefaultCloseOperation(EXIT_ON_CLOSE);
        a.setLocationRelativeTo(null);

     }
    /**
     * This method creates board and shows to user
     */
    public void gameBoard(){

        player = 'X';  // ilk kullanıcıyı X olarak seçtim
        screenWidht=(size*45);  // pencerenin nerde konumlandırılacağını size a göre ayarladım
        screenHeight=((size*45)-400);
        setTitle("ConnectFour"); // pencere başlığı ayarladığım

        setSize(((size+2)*100),(((size+2)*100)-150));  // pencerenenin sizenını ve görünürlüğünü ayarladım
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        board = new Cell[size][size];  //Cellerden oluşan iki boyutlu bir board oluşturdum

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board[i][j] = new Cell();         
            }
        }  

         for(int k= 0,l=72; k<size;k++,l=l+80){ // ve her bir cellin içine kullanılan gerekli dataları atadım
            for(int i=130,j = 0; j<size; i=i+72+6,j++){
                    board[k][j].setterxPos(i);
                    board[k][j].setteryPos(l);
                    board[k][j].setterData('.');
                    board[k][j].setterColumn(j);
                    board[k][j].setterRow(k);
            }
         }


        addMouseListener(this); // addmouselistener methodunu çağırdım


    }
    /**
     * 
     * @param g Graphics type
     * It show user which Cell is empty or not and their colors
     */
    @Override
    public void paint(Graphics g){ 
        setLocation(screenWidht, screenHeight);

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){  // iki for döngüsünde her bir cellin cell tipine göre renkleri ekrana bastırdım

                if(board[i][j].getterCellType()=='.'){ 

                        g.setColor(Color.LIGHT_GRAY);
                        g.fillOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);
                        g.setColor(Color.DARK_GRAY);
                        //g.drawOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);

                }
                if(board[i][j].getterCellType()=='X'){

                        g.setColor(Color.RED);
                        g.fillOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);

                }

                if(board[i][j].getterCellType()=='O'){

                        g.setColor(Color.BLUE);
                        g.fillOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);

                }
                if(board[i][j].getterCellType()=='o'){  // kazanma durumunda o callin celltipini kucuk harf yaptım ve ona göre ekrana daha farklı bir taş çizdirdim
                        g.setColor(Color.YELLOW);
                        g.fillOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);
                        g.setColor(Color.BLUE);
                        g.fillOval(board[i][j].getterxPos()+5,board[i][j].getteryPos()+5,63,63);

                }

                if(board[i][j].getterCellType()=='x'){
                        g.setColor(Color.YELLOW);
                        g.fillOval(board[i][j].getterxPos(),board[i][j].getteryPos(),72,72);
                        g.setColor(Color.RED);
                        g.fillOval(board[i][j].getterxPos()+5,board[i][j].getteryPos()+5,63,63);
                }
            }
        }
        if(win==3 || win==2 || win==1){  // kazanma durumunda ekranın üstüne kazanan renk bilgisini yerleştirdim ve ayrıca yeni oyun yada exit dikdörtgen tekxfieldlerını koydum
            g.setColor(Color.GRAY);   
            g.fillRect((((size+2)*100)-450),0,200,50);
            g.setColor(Color.BLACK);
            g.setFont(new Font("NEW GAME", Font.PLAIN, 30));
            g.drawString ("NEW GAME", (((size+2)*100)-450)+15, 30);
            g.setColor(Color.GRAY);
            g.fillRect((((size+2)*100)-450)+235,0,200,50);
            g.setColor(Color.BLACK);
            g.setFont(new Font("EXIT", Font.PLAIN, 30));
            g.drawString ("EXIT", (((size+2)*100)-450)+235+65, 30);
            if(win==1){  // eger win 1 lursa kırmızı taş kazanmıştır yani 1.oyuncu kazanmıştır
               g.setColor(Color.RED);
               g.setFont(new Font("TimesRoman", Font.PLAIN, 16)); 
               g.drawString ("WINNER = RED", (((size+2)*100)-450)+15, 63);                                 
            }
            if(win==2){ // eğer win 2 olursa mavi taş kazanmıştır yani 2. oyuncu yada bilgisayar kazanmıştır
               g.setColor(Color.BLUE);
               g.setFont(new Font("TimesRoman", Font.PLAIN, 16)); 
               g.drawString ("WINNER = BLUE", (((size+2)*100)-450)+15, 63);                                 
            }
            if(win==3){ // eger win 3 olursa hiç bir oyuncu yada bilgisayar kazanamamıştır , board dolmuştur.
               g.setColor(Color.BLACK);
               g.setFont(new Font("TimesRoman", Font.PLAIN, 16)); 
               g.drawString ("NO WINNER", (((size+2)*100)-450)+15, 63);                                 
            }                                
        }
    }
    // mouse listener clasından dolayı implement edilmesi gerekli olan methodlar ama ben kullanmadığım için implement etmedim
    @Override
    public void mouseEntered(MouseEvent e) {
            // TODO Auto-generated method stub

    }
    @Override
    public void mouseExited(MouseEvent e) {
            // TODO Auto-generated method stub

    }
    @Override
    public void mousePressed(MouseEvent e) {
            // TODO Auto-generated method stub

    }
    @Override
    public void mouseReleased(MouseEvent e) {
            // TODO Auto-generated method stub

    }
    /**
     * 
     * @param e Mouse event type
     * It decides what should do when press the mouse ,and it depends on mouse cursor location
     */
    @Override
    public void mouseClicked(MouseEvent e) {

        int mX = e.getX(); // mouse nin x koordinatını aldım
        int mY = e.getY(); // mousenin y koordinatını aldım
        int i=0;  
        int j=0;
        if(win ==0){   // eğer tıklanılan yer de boş yer varsa ve bir cell se oraya taş koyulması için play methodu çağrılır
            for(;i<size;i++){
                for(;j<size;j++){
                    if(board[0][j].getterCellType()=='.'){
                        if(mX > board[i][j].getterxPos() && mX < board[i][j].getterxPos()+72 ){
                            playColumn=board[i][j].getterColumn();
                            play();
                            break;
                        }
                    }

                }
                if(mX > board[i][j].getterxPos() && mX < board[i][j].getterxPos()+72 ){
                    break;
                }
            }
        }
        if(win==2 || win==1 || win==3){  // kazanma yada beraberlik durumunda mouse sadece exit ve new game tekt fieldleri uzerinde çalışabilir hale gelir
            if(mX >  (((size+2)*100)-450) && mX <  (((size+2)*100)-450)+200 && mY > 0 && mY < 50+0){
                dispose();
                ConnectFour newGame = new ConnectFour();
                newGame.playGame();
            }
            if(mX > (((size+2)*100)-450)+235 && mX < (((size+2)*100)-450)+235+200 && mY > 0 && mY < 50+0){
                System.exit(1);
            }
        }
    }
    public void mouseMoved(MouseEvent e) { 

    }
    /**
     * this method using for set red or blue to board
     */
    public void play(){
        if(gameMode==1){  // boarda taşları atmak için kullanılır

            setBoard(playColumn,player);  

            int a =controlfour(player,playRow,playColumn); // 4 leme durumu yada  tahtanın dolması durumu varsa win değişkeni değiştirilir
            int c =emptyMapControl();
             if(c==0){
                win=3;
                repaint();
                return;
            }
            if (a>0 && a<27){ // eğer 4 leme durmu varsa win değişkenine atama yapılır
                lower(player,a);
                if(player=='X'){
                    win=1;
                }
                if(player=='O'){
                    win=2;
                }
            }

            if(player=='X'){ // kullanıcı sırası değiştirilir
                player='O';
            }
            else if(player=='O'){
                player='X';
            }
            repaint();  // repaint methodu çağrılır
        }

        if(gameMode ==2){   // ikinci modda kullanıcı oynar sonra bilgisayar oynar
            setBoard(playColumn,'X');

            int a =controlfour('X',playRow,playColumn);
            int b =emptyMapControl();
            if(b==0){
                win=3;
                repaint();
                return;
            }
            if (a>0 && a<27){  // eğer  leme durmu varsa win değişkenine atama yapılır

                lower('X',a);
                if(player=='X'){
                    win=1;
                }

            }

            repaint();

            if(compSetBoard() == 2){ // bilgisayarın oynadığı method ve eğer 2 return ediyorsa bilgisayar kazanmış demektir
                    win=2;
            }
            int c =emptyMapControl();
            if(c==0){
                win=3;
                repaint();
                return;
            }
            repaint();
        }
    }
    /**
     * this method control the board full or not
     * @return 1 if board is not full , 0 if board full
     */
    public int emptyMapControl(){  //
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(board[i][j].getterCellType()=='.'){
                    return 1;
                }
            }
        }
        return 0;
    }
    /**
     * 
     * @param cursor cellType X or O
     * @param flag win location
     */
    public void lower(char cursor ,int flag){ // kazanma durumda X ise x olur O ise o olur cellType.
                                              // Bu sayede o taşlar için farklı bir graphic çizdirebliyorum ve kullanıcı hangi 4 lünün yan yana geldiğini görür.
    if(flag==1 || flag==14){

        if(board[playRow][playColumn+1].getterCellType()=='X'){
                board[playRow][playColumn+1].setterData('x');
                board[playRow][playColumn+2].setterData('x');
                board[playRow][playColumn+3].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow][playColumn+1].getterCellType()=='O'){
                board[playRow][playColumn+1].setterData('o');
                board[playRow][playColumn+2].setterData('o');
                board[playRow][playColumn+3].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==2 || flag==15){
            if(board[playRow][playColumn-1].getterCellType()=='X'){
                board[playRow][playColumn-1].setterData('x');
                board[playRow][playColumn+1].setterData('x');
                board[playRow][playColumn+2].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow][playColumn-1].getterCellType()=='O'){
                board[playRow][playColumn-1].setterData('o');
                board[playRow][playColumn+1].setterData('o');
                board[playRow][playColumn+2].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }


        if(flag==3 || flag==16){

            if(board[playRow][playColumn-2].getterCellType()=='X'){
                board[playRow][playColumn-2].setterData('x');
                board[playRow][playColumn-1].setterData('x');
                board[playRow][playColumn+1].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow][playColumn-2].getterCellType()=='O'){
                board[playRow][playColumn-2].setterData('o');
                board[playRow][playColumn-1].setterData('o');
                board[playRow][playColumn+1].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }
        if(flag==4 || flag==17){

            if(board[playRow][playColumn-3].getterCellType()=='X'){
                board[playRow][playColumn-3].setterData('x');
                board[playRow][playColumn-2].setterData('x');
                board[playRow][playColumn-1].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow][playColumn-3].getterCellType()=='O'){
                board[playRow][playColumn-3].setterData('o');
                board[playRow][playColumn-2].setterData('o');
                board[playRow][playColumn-1].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==5 || flag==18){
            if(board[playRow+1][playColumn].getterCellType()=='X'){
                board[playRow+1][playColumn].setterData('x');
                board[playRow+2][playColumn].setterData('x');
                board[playRow+3][playColumn].setterData('x');
                board[playRow][playColumn].setterData('x');
            }

            if(board[playRow+1][playColumn].getterCellType()=='O'){

                board[playRow+1][playColumn].setterData('o');
                board[playRow+2][playColumn].setterData('o');
                board[playRow+3][playColumn].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==6 || flag==19){

            if(board[playRow-3][playColumn-3].getterCellType()=='X'){
                board[playRow-3][playColumn-3].setterData('x');
                board[playRow-2][playColumn-2].setterData('x');
                board[playRow-1][playColumn-1].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow-3][playColumn-3].getterCellType()=='O'){
                board[playRow-3][playColumn-3].setterData('o');
                board[playRow-2][playColumn-2].setterData('o');
                board[playRow-1][playColumn-1].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==7 || flag==20){

            if(board[playRow-2][playColumn-2].getterCellType()=='X'){
                board[playRow-2][playColumn-2].setterData('x');
                board[playRow-1][playColumn-1].setterData('x');
                board[playRow][playColumn+3].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow-2][playColumn-2].getterCellType()=='O'){
                board[playRow-2][playColumn-2].setterData('o');
                board[playRow-1][playColumn-1].setterData('o');
                board[playRow+1][playColumn+1].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==8 || flag==21){

            if(board[playRow-1][playColumn-1].getterCellType()=='X'){
                board[playRow-1][playColumn-1].setterData('x');
                board[playRow+1][playColumn+1].setterData('x');
                board[playRow+2][playColumn+2].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow-1][playColumn-1].getterCellType()=='O'){
                board[playRow-1][playColumn-1].setterData('o');
                board[playRow+1][playColumn+1].setterData('o');
                board[playRow+2][playColumn+2].setterData('o');
                board[playRow][playColumn].setterData('o');

            }
        }

        if(flag==9 || flag==22){

            if(board[playRow+1][playColumn+1].getterCellType()=='X'){
                board[playRow+1][playColumn+1].setterData('x');
                board[playRow+2][playColumn+2].setterData('x');
                board[playRow+3][playColumn+3].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow+1][playColumn+1].getterCellType()=='O'){
                board[playRow+1][playColumn+1].setterData('o');
                board[playRow+2][playColumn+2].setterData('o');
                board[playRow+3][playColumn+3].setterData('o');
                board[playRow][playColumn].setterData('o');

            }
        }

        if(flag==10 || flag==23){

            if(board[playRow-3][playColumn+3].getterCellType()=='X'){
                board[playRow-3][playColumn+3].setterData('x');
                board[playRow-2][playColumn+2].setterData('x');
                board[playRow-1][playColumn+1].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow-3][playColumn+3].getterCellType()=='O'){
                board[playRow-3][playColumn+3].setterData('o');
                board[playRow-2][playColumn+2].setterData('o');
                board[playRow-1][playColumn+1].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==11 || flag==24){

            if(board[playRow+1][playColumn-1].getterCellType()=='X'){
                board[playRow+1][playColumn-1].setterData('x');
                board[playRow-1][playColumn+1].setterData('x');
                board[playRow-2][playColumn+2].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow+1][playColumn-1].getterCellType()=='O'){
                board[playRow+1][playColumn-1].setterData('o');
                board[playRow-1][playColumn+1].setterData('o');
                board[playRow-2][playColumn+2].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==12 || flag==25){

            if(board[playRow+2][playColumn-2].getterCellType()=='X'){
                board[playRow+2][playColumn-2].setterData('x');
                board[playRow][playColumn+2].setterData('x');
                board[playRow][playColumn+3].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow+2][playColumn-2].getterCellType()=='O'){
                board[playRow+2][playColumn-2].setterData('o');
                board[playRow][playColumn+2].setterData('o');
                board[playRow][playColumn+3].setterData('o');
                board[playRow][playColumn].setterData('o');
            }
        }

        if(flag==13 || flag==26){

            if(board[playRow+1][playColumn-1].getterCellType()=='X'){
                board[playRow+1][playColumn-1].setterData('x');
                board[playRow+2][playColumn-2].setterData('x');
                board[playRow+3][playColumn-3].setterData('x');
                board[playRow][playColumn].setterData('x');
            }
            if(board[playRow+1][playColumn-1].getterCellType()=='O'){
                board[playRow+1][playColumn-1].setterData('o');
                board[playRow+2][playColumn-2].setterData('o');
                board[playRow+3][playColumn-3].setterData('o');
                board[playRow][playColumn].setterData('o');

            }
        }
    }
    /**
     * this method set data to the cells
     * @param j setting column value
     * @param l setting row value
     */
    public void setBoard(int j,char l){ 

        for(int i = size-1;i>=0;i--){
            if(board[i][j].getterCellType()=='.'){ // eğer set edilmesi istenen yer boşssa oraya set işlemi yapılır
                playRow=board[i][j].getterRow();
                if(l=='X'){
                        board[i][j].setterData('X');
                }
                if(l=='O'){
                        board[i][j].setterData('O');
                }
                break;			
            }
        }
    }

   /**
     * in this method computer chooses a location and set data
     * @return 0 is compSet some data to board else return -1
    */ 
    public int compSetBoard(){
            

        if(board[size -1][size/2].getterCellType()=='.'){  /* oyunun baslangicinda bilgisayar haritanin ortasinin en altta kalan uygun noktasina O koyar ve bu bir kez gerceklesir*/
            board[size -1][size/2].setterData('O');
            return 0;
        }
        if( board[size -1][size/2].getterCellType()=='X' && board[size -2][size/2].getterCellType()=='.' ){
            board[size -2][size/2].setterData('O');
            return 0;
        }
        
        //4 lü durumu varmı diye kontrol etmek için

        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){

                int a =controlfour('O',i,j);

                if (a>0 && a<27 && board[i][j].getterCellType()=='.'){ // bilgisayar için 4 leme durmu varmı kontrolu

                    if(i+1<size){
                        if((board[i+1][j].getterCellType()=='X' || board[i+1][j].getterCellType()=='O') ){
                            board[i][j].setterData('O');
                            playRow = i;
                            playColumn = j;				
                            lower('O',a);
                            return 2;
                        }
                    }
                    if(i==size-1){
                        board[size-1][j].setterData('O');
                        playRow = i;
                        playColumn = j;				
                        lower('O',a);
                        return 2;
                    }
                }
            }
        }
        
        //x in 4 lemesini engelleme kontrolu

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                int b =controlfour('X',i,j);

                if (b>0 && b<27 && board[i][j].getterCellType()=='.'){ 
                    if(i+1<size){
                        if((board[i+1][j].getterCellType()=='X' || board[i+1][j].getterCellType()=='O') ){
                            board[i][j].setterData('O');
                            return 0;
                        }
                    }
                    if(i==size-1){
                        board[size-1][j].setterData('O');
                        return 0;
                    }
                }
            }
        }
        //x ikileme ve üçleme durumları
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(board[i][j].getterCellType()=='O'){
                    if(i==size-1){
                        if(j+1<size){
                            if(board[size-1][j+1].getterCellType()=='.'){
                                board[size-1][j+1].setterData('O');
                                return 0;
                            }
                        }                                                                                                                                                               
                        if(j-1>-1){
                            if(board[size-1][j-1].getterCellType()=='.'){
                                board[size-1][j-1].setterData('O');
                                return 0;
                            }
                        }                                                                                                                                                                  
                        if(j+1<size && size-2>-1){
                            if(board[size-2][j+1].getterCellType()=='.'){
                                board[size-2][j+1].setterData('O');
                                return 0;
                            }
                        }
                    }
                    if(i-1>-1){
                        if(board[i-1][j].getterCellType()=='.'){
                            board[i-1][j].setterData('O');
                            return 0;
                        }
                    }

                    if(j+1<size && i+1>size){
                        if(board[i][j+1].getterCellType()=='.' && (board[i+1][j+1].getterCellType()=='X' || board[i+1][j+1].getterCellType()=='O')){
                            board[i][j+1].setterData('O');
                            return 0;
                        }
                    }

                    if(j+1<size && i-1>-1){
                        if(board[i-1][j+1].getterCellType()=='.' && (board[i][j+1].getterCellType()=='X' || board[i][j+1].getterCellType()=='O')){
                            board[i-1][j+1].setterData('O');
                            return 0;
                        }
                    }
                    if(i-1>-1 && j-1>-1){
                        if(board[i-1][j-1].getterCellType()=='.' && (board[i][j-1].getterCellType()=='X' || board[i][j-1].getterCellType()=='O')){
                            board[i-1][j-1].setterData('O');
                            return 0;
                        }
                    }
                    if(i+1>size&& j-1>-1){
                        if(board[i][j-1].getterCellType()=='.' && (board[i+1][j-1].getterCellType()=='X' || board[i+1][j-1].getterCellType()=='O')){
                            board[i][j-1].setterData('O');
                            return 0;
                        }
                    }
                }
            }
        }
        // eğer yukardaki hiç bir durum oluşmadıysa bilgisayar bulduğu ilk boş ve uygun yere oynar
        for(int i=0;i<size;i++){ 
            for(int j=0;j<size;j++){
                if(i+1<size-1 ){
                    if(board[i][j].getterCellType()=='.' && (board[i+1][j].getterCellType()=='X' || board[i+1][j].getterCellType()=='O')) {
                        board[i][j].setterData('O');
                        return 0;
                    }
                }  
                if(i==size-1){
                    board[i][j].setterData('O');
                    return 0;                                
                }
            }
        }	
        return -1;
    }
    /**
     * 
     * @param cursor it is a cellDataType
     * @param playRo user or computer plays row
     * @param playCol user or computer plays col
     * @return depends on win location type
     */
    public int controlfour(char cursor,int playRo,int playCol) { // hangi dörtlünün 4 lendiğine göre return değeri değişir

        int flag=0;
        
        // yatay durumlar için kazanma 4 leme durumu
        if(playCol+3<size){  
            if(board[playRo][playCol+1].getterCellType()==cursor && board[playRo][playCol+2].getterCellType()==cursor && board[playRo][playCol+3].getterCellType()==cursor){
                flag=1;
            }	
        }
        if(playCol+2<size && playCol-1>-1){
            if(board[playRo][playCol-1].getterCellType()==cursor && board[playRo][playCol+1].getterCellType()==cursor && board[playRo][playCol+2].getterCellType()==cursor){
                flag=2;
            }
        }
        if(playCol+1<size && playCol-2>-1){
            if(board[playRo][playCol-2].getterCellType()==cursor && board[playRo][playCol-1].getterCellType()==cursor && board[playRo][playCol+1].getterCellType()==cursor){
                flag=3;
            }
        }
        if(playCol-3>-1){
            if(board[playRo][playCol-3].getterCellType()==cursor && board[playRo][playCol-2].getterCellType()==cursor && board[playRo][playCol-1].getterCellType()==cursor){
                flag=4;		
            }
        }
        
        
        
        //dikey durumdaki kazanma 4leme durumu
        if(size>playRo+3){ 

            if(board[playRo+1][playCol].getterCellType()==cursor && board[playRo+2][playCol].getterCellType()==cursor && board[playRo+3][playCol].getterCellType()==cursor){
                flag=5;
            } 
        }

        
        
        //çapraz kazanma durumu
        if(playRo>=3 && playCol>=3 && size-1>=playRo && size-1>=playCol ){ 
            if(board[playRo-3][playCol-3].getterCellType()==cursor && board[playRo-2][playCol-2].getterCellType()==cursor && board[playRo-1][playCol-1].getterCellType()==cursor){
                flag=6;
            }
        }

        if(playRo>=2 && playCol>=2 && size-2>=playRo && size-2>=playCol){
            if(board[playRo-2][playCol-2].getterCellType()==cursor && board[playRo-1][playCol-1].getterCellType()==cursor && board[playRo+1][playCol+1].getterCellType()==cursor){
                flag=7;
            }
        }

        if(playRo>=1 && playCol>=1 && size-3>=playRo && size-3>=playCol ){
            if(board[playRo-1][playCol-1].getterCellType()==cursor && board[playRo+1][playCol+1].getterCellType()==cursor && board[playRo+2][playCol+2].getterCellType()==cursor){
                flag=8;
            }
        }


        if(playRo>=0 && playCol>=0 && size-4>=playRo && size-4>=playCol ){
            if(board[playRo+1][playCol+1].getterCellType()==cursor && board[playRo+2][playCol+2].getterCellType()==cursor && board[playRo+3][playCol+3].getterCellType()==cursor){
                flag=9;
            }
        }




        //çapraz kazanma durumu
        if(playRo>=3 && playCol<=size-4 && size-1>=playRo && 0<=playCol){
            if(board[playRo-3][playCol+3].getterCellType()==cursor && board[playRo-2][playCol+2].getterCellType()==cursor && board[playRo-1][playCol+1].getterCellType()==cursor){
                flag=10;	
            }
        }


        if(playRo>=2 && playCol<=size-3 && size-2>=playRo && 1<=playCol){
            if(board[playRo+1][playCol-1].getterCellType()==cursor && board[playRo-1][playCol+1].getterCellType()==cursor && board[playRo-2][playCol+2].getterCellType()==cursor){
                flag=11;	
            }
        }


        if(playRo>=1 && playCol<=size-2 && size-3>=playRo && 2<=playCol){
            if(board[playRo+2][playCol-2].getterCellType()==cursor && board[playRo-1][playCol+1].getterCellType()==cursor && board[playRo+1][playCol-1].getterCellType()==cursor){
                flag=12;	
            }
        }


        if(playRo>=0 && playCol<=size-1 && size-4>=playRo && 3<=playCol){
            if(board[playRo+1][playCol-1].getterCellType()==cursor && board[playRo+2][playCol-2].getterCellType()==cursor && board[playRo+3][playCol-3].getterCellType()==cursor){
                flag=13;	
            }
        }
        // kazanma durumlarına göre farklı return değerleri oluşur
        if(flag==0){
            return -1;	
        }
        /*flag 1 ile 13 arasindaysa ve cursor X ise flag return edilir*/
        else if(cursor=='X' && (flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
            return flag;
        }
        /*flag 1 ile 13 arasindaysa ve cursor O ise flag+13 return edilir*/

        else if(cursor=='O' && (flag==1 || flag==2 || flag==3 || flag==4 || flag==5 || flag==6 || flag==7 || flag==8 || flag==9 || flag==10 || flag==11 || flag==12 || flag==13)){
            return flag+13;
        }
        else{
            return -100;
        } 
    }

    public static void main(String[] args){ // main methodunda bir tane ConnectFour objesi oluşturuyorum ve o obje üzerinde playGame methodunu çalıştırınca oyun başlıyor
            ConnectFour game = new ConnectFour();
            game.playGame();
    }

}