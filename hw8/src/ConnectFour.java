import javax.swing.JPanel;
import java.awt.*;
import java.awt.event.*;
import javax.swing.JOptionPane;
import java.util.*;
import javafx.scene.shape.Circle;
import java.awt.Graphics;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import java.awt.event.MouseListener;
import java.util.Random;
/**
 * CONNECT FOUR GAME WİTH JAVA
 * @author Emre KAVAK
 */
public class ConnectFour extends JFrame{  
   /**
    * Cell is inner class
    */
    public class Cell extends JLabel{
        /**
         * for hold cell type (*,x,o);
         */
        private char cellType;
        /**
         * for hold position cell (a,b,c...)
         */
        private String positionCell;
        /**
         * for hold row number
         */
        private int rowNum;
        /**
         * set cell type
         * @param value 
         */
        public void setCellType(char value){
            cellType=value;
        }
        /**
         * for set positioncell
         * @param value 
         */
        public void setPositionCell(String value){
            positionCell=value;
        }
        public void setRowNum(int value){
            rowNum=value;
        }
        public char getCellType(){
            return cellType;
        }
        public String getPositionCell(){
            return positionCell;
        }
         public int getRowNum(){
            return rowNum;
        }
    }/**
     * hold game^s data
     */
    private Cell [][] gameCells;
    private String playerChoice;
    private int boardSize;
    /**
     * for decided whick user clicked. if usercount %2==0 user 1, else user2
     */
    public static int usercount=0;
    public int newgame =0;
    /**
     * for check board for is there a winner
     */
    public int checkrow = 0;
    public int checkcolumn = 0;
    
    public ConnectFour(){
        gameCells= new Cell[2][2];           
    }
    public void setSize(int size){
        boardSize = size;   
    }
    public void setChoice(String valueChoice){
        playerChoice = valueChoice;
    }
    public String getChoice(){
        return playerChoice;
    }
    public int getBoardSize(){
        return boardSize;
    }
    /**
     * when game star,setboard filling gamecells with information  
     */
    public void setBoard(){
        gameCells=new Cell[boardSize][boardSize];
        for(int i = 0; i< boardSize; i++){
            for(int j = 0; j< boardSize; j++)
                gameCells[i][j]=new Cell();
        }
        for(int i = 0; i< boardSize; i++){
            char letters='a';
            for(int j = 0; j < boardSize; j++){
                gameCells[i][j].setCellType('*');
                gameCells[i][j].setPositionCell(String.valueOf(letters));
                gameCells[i][j].setRowNum(i);
                letters++;
            }
        }
    }
    /**
     * Game is playing in here. Creaing frame, actionPerformed methods in here.  
     */
    public void playGame(){
        JButton buttons[] = new JButton[boardSize];  // for create button
        JFrame frame = new JFrame();
    
        frame.setVisible(true);
        frame.setTitle("Connect Four Game");
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel();
        String []names = new String [boardSize]; // for hold button letters
        char letters='a';
        for(int i = 0; i< boardSize; i++){
            names[i]=String.valueOf(letters);
            letters++;
        }
        
        for (int i = 0; i < buttons.length; i++){  // Buttons are creating
            JButton buton = new JButton(names[i]);
            buttons[i]=buton;
            panel.add(buttons[i]); 
            /**
             * for click events. When user click a buttun, button letter return;
             */
        buton.addActionListener(new ActionListener(){
            Component frame2 = null;
            
            @Override
            public void actionPerformed(ActionEvent e){   
                String x=e.getActionCommand();
                usercount++;
                char b =x.charAt(0);
                
                play(x); //for change board;
                redraw(panel,frame); // draw frame 
                frame.add(panel);
                frame.setSize(51*boardSize,boardSize*55); // framesize

                 /**
                  * if user entered c, computer will play
                  */  
                if(getChoice().equals("C")) {
                    computerPlay();
                    redraw(panel,frame);
                    frame.add(panel);
                    frame.setSize(51*boardSize,boardSize*55);
                }
                /**
                 * checking board full or empty
                 */
                if(getCheckBoardFull()==1){
                    JOptionPane.showMessageDialog(frame, "!!!!! No a winner. Board is full !!!!!");
                    newgame =1; 
                    setBoard();
                    usercount=0;
                }
                /**
                 * winner control
                 */   
                if(getcheckWinner(checkrow,checkcolumn,'x')==1){
                    JOptionPane.showMessageDialog(frame2, "USER 1(RED) WİNNER.");
                    newgame =1;
                    setBoard();
                    usercount=0;
                }                  
                if(getcheckWinner(checkrow,checkcolumn,'o')==1) {
                    usercount=0;
                    if(getChoice()=="P") JOptionPane.showMessageDialog(frame, "USER 2(BLUE) WİNNER.");
                        else JOptionPane.showMessageDialog(frame, "COMPUTER (BLUE) WİNNER.");
                        newgame =1;
                        setBoard();
                }    
                /**
                 * if game end, main frame will close and new frame will open
                 */
                if(newgame==1) {
                    frame.setVisible(false);
                    newgame=0;
                    input();
                }            
            }
        });     
    }
            redraw(panel,frame);                    
    }
    /**
     * game board will change in here
     * @param letter
     * 
     */
    public void play(String letter){
        
        for(int i = boardSize-1; i>=0; i--){ 
            for(int j = 0; j<boardSize; j++){
                if(gameCells[i][j].getPositionCell().equals(letter) && gameCells[i][j].getCellType()=='*' ){
                    if(usercount %2 !=0) {
                    gameCells[i][j].setCellType('x');
                        if(getcheckWinner(i,j,'x')==1) {
                            checkrow=i;
                            checkcolumn=j;
                        }
                    }
                    if(usercount %2 ==0) {
                    gameCells[i][j].setCellType('o');
                        if(getcheckWinner(i,j,'o')==1) {
                            checkrow=i;
                            checkcolumn=j;
                        }   
                    }
                    i=-1;
                    j=boardSize-1;
                }
            }
        }
        
    }  
    /**
     * winner check method
     * @param row
     * @param column
     * @param letterUser
     * @return 
     */
    public int getcheckWinner( int row, int column, char letterUser){
        int count1 = 0, count2 = 0,count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0,
        count9 = 0, count10 = 0, count11=0,count12 =0, count13=0; // counts will count X or O according to selected row and column

        for(int i=0; i<4; i++){
            if( row+i < boardSize && gameCells[row+i][column].cellType == letterUser) count1++; 	// vertical count     
            if( column-i >= 0 && gameCells[row][column-i].cellType == letterUser) count2++;	// horizontal count xxx-                     
            if( column+i < boardSize && gameCells[row][column+i].cellType == letterUser) count3++;	// horizontal count -xxx 
            if(column+i-1 >= 0 && column+i-1 < boardSize && gameCells[row][column+i-1].cellType == letterUser) count4++; // horizontal count x-xx                      
            if(column+i-2 >= 0 && column+i-2 < boardSize && gameCells[row][column+i-2].cellType == letterUser) count5++; // horizontal count xx-x   
        }
        for(int j = 0; j<4; j++){                                                                                                    
            if(row +j < boardSize && column-j >= 0 && gameCells[row+j][column-j].cellType == letterUser) count6++; // diagonal1 count -xxx
            if(row -j >=0 && column+j < boardSize && gameCells[row-j][column+j].cellType == letterUser) count8++;  // diagonal1 count xxx-
            if(row -j >=0 && column-j >= 0 && gameCells[row-j][column-j].cellType == letterUser) count7++;    // diagonal2 count -xxx       
            if(row+j < boardSize && column+j < boardSize && gameCells[row+j][column+j].cellType == letterUser) count9++;// diagonal2 count xxx-     
        } 
        for(int m = 0; m<=4; m++){ 
            if(row + m -1 < boardSize && row + m -1 >=0 && column+m-1 >=0 && column+m-1 < boardSize && gameCells[row + m - 1][column+m-1].cellType == letterUser) 
                count10++; // diagonal2  count x-xxx   
            //if(row + m < boardSize && row + m -1 >=0 && column-m+1 >=0 && column-m-1 <boardSize && gameCells[row + m - 1][column-m+1].cellType == letterUser) 
              //  count11++; // diagonal1 count x-xxx          
            if(row + m -2 < boardSize &&  row + m -2 >=0 && column+m-2 >=0 && column+m-2 < boardSize && gameCells[row + m - 2][column+m-2].cellType == letterUser) 
                count12++; // diagonal2 count xx-x                     
            if(row + m -2 < boardSize && row + m -2 >=0 && column-m +2 >= 0 && column-m+2 < boardSize && gameCells[row + m - 2][column - m + 2].cellType == letterUser) 
                count13++; // diagonal1 count xx-x      
        }
        // after if there is a won, letters will be small according to letterUser(letterUser 'X' or 'O')
        if(count1 == 4 || count2 == 4 || count3 == 4 || count4 == 4 || count5 == 4 || count6 == 4 || count7 == 4 || count8 == 4 || count9 == 4 || 
        count10 == 4 || count11 == 4 || count12 == 4 || count13 == 4 ){

                return 1;
        }
        return 0;     
    }
    /**
     * chanhing frame according to clicked button
     * @param panel
     * @param frame 
     */
    public void redraw(JPanel panel,JFrame frame){
        
        ImageIcon image1 = null;
        for(int i = 0 ; i <boardSize; i++){ 
            for(int k = 0; k <boardSize; k++){  
             
            if(gameCells[i][k].getCellType()=='*') image1 = new ImageIcon("src\\1.png");
            if(gameCells[i][k].getCellType()=='x' ) image1= new ImageIcon("src\\2.png");
            if(gameCells[i][k].getCellType()=='o') image1 = new ImageIcon("src\\3.png");

            JLabel imagelabel1 = new JLabel();
            imagelabel1.setIcon(image1);
            imagelabel1.setBounds(k*45+boardSize*3, i*40+28, 50, 50);

            panel.add(imagelabel1);
            frame.add(imagelabel1);
            frame.add(panel);
            }     
        }
        
        frame.setBounds(500, 150, 51*boardSize+2, 55*boardSize+2);
        frame.add(panel);       
    }/**
     * first method for player choice and size
     * @return 
     */
    public int input(){
        int flag=0;
        String choice;
        
        do{ 
            choice =JOptionPane.showInputDialog(null,"Please enter PVP (P) or PVC(C)");
            if(choice.equals("P") || choice.equals("C")) flag =1;
        }while(flag==0);
        
        if(flag == 1) setChoice(choice);
        
        int fage=0;
        do{
            fage =Integer.parseInt(JOptionPane.showInputDialog(null,"Please enter Board size ( just even numbers )"));   
        }while(fage%2!=0);
        setSize(fage);
        setBoard();
        playGame();
        return 0;
    }
    
    /**
     * computer random play method
     * @return 
     */
   public void computerPlay(){ //  computer play
    
    int [] letters= new int[boardSize];
    char move;    //arr array will keep letter according to entered size. move is keeping computer select letter
    int letterNum = 97,count =0, col=0;
    
    for(int i = 0; i < boardSize ; i++){  
        letters[i] =  letterNum; //assignment letters according to entered size
        letterNum++;
        count++;
    }
    int count1 =0,count2=0,count3=0,count4=0,column=0; //counts will count how many X there are if they entered consecutive 3 times vertical or horizontal
    Random rand = new Random(); // random object
    int  random = rand.nextInt(boardSize) +97;
    move =(char)random;  // random letter hold
    
    for(int i =boardSize-1; i >= 0; i--){  // horizontal smart move select
        for(int j =0 ; j<column; j++){
            if(gameCells[i][j].getCellType() == 'x'){
                for(int k = 0; k < 4; k++){
                    if(gameCells[i][j+k].getCellType() =='x' && j+k < column ){ 
                        count1++;  
                    }
                    if(count1 ==3){
                        count2 = count1;
                        if(gameCells[i][j+k+1].getCellType() == '*' && j+k+1 < column ) col = j+k;
                        //column will keep column number if there are 3 times 'X' horizontal
                        }   
                    }
                count1=0;
                }
            }
    }
    if(count2 == 3) move = (char)(col+97);

    for(int i =boardSize-1; i >= 0; i--){  // vertical smart move select
        for(int j =boardSize-1 ; j >= 0; j--){
            if(gameCells[j][i].getCellType() == 'x'){
                for(int k = 0; k < 3; k++){
                    if(j-k >=0 && gameCells[j-k][i].getCellType() =='x' ) count3++;  
                    if(count3 ==3 ){
                        count4 = count3;
                            if(gameCells[j-k-1][i].getCellType() == '*' && j-k-1 >=0 && i-1>=0 )col = i; 
                    }       //column will keep column number if there are 3 times 'X' vertical
                }
                count3=0;
            }
        }
    }

    if(count4 == 3) move=(char) ((char)col+97); // if there are 3 times 'X' vertical, computer letter will be according to column number +97
        if(getcheckColumnFull(move) == 1){ // if selected column is full, move will change until find a '.';
            for(int i =0; i<boardSize; i++){ 
                for(int j =0 ; j<column; j++){
                    if(gameCells[i][j].getCellType() == '*'){ 
                        move =(char) ((char)j+97);
                    }
                }
            }
    }
    int minesRow = 0,rowVal=0,columnval=0;
        // according to  computer's letter, game BOARD changing
    for(int i = boardSize-1; i >= 0; i--){
        for(int j = 0; j < column; j++){
            if(gameCells[i][j].getPositionCell().equals(move)  && gameCells[i][j].getCellType() =='*'){
                rowVal = gameCells[i][j].getRowNum();
                columnval =j;
                gameCells[rowVal][j].setCellType('o');
                i=0;
                j=column;
                }
            }
    }
    usercount++;
    play(String.valueOf(move));
}
   /**
    * for check column full or not
    * @param letter
    * @return 1 or 0
    */
   public int getcheckColumnFull(char letter){
        int count = 0;
        int column =letter-97;
        // X and O are counting and count is equal heigh, return will be 1
        for(int i =boardSize-1; i >= 0; i--){
             if(gameCells[i][column].getCellType() == 'x' || gameCells[i][column].getCellType() == 'o' )
               count++;
        }  
        if(count == boardSize) return 1;
        else return 0;
   }/**
    * for check board full or not
    * @return 1 if board full,else return 0
    */
   public int getCheckBoardFull(){
    int countfull = 0;
    for( int i = 0 ; i< boardSize ; i++){  //checking game board full or not
        for(int j = 0; j< boardSize ; j++){
            if(gameCells[i][j].getCellType() !='*') countfull++;
        }
    }
    if(countfull == boardSize*boardSize) 
        return 1; //if full, returned number will be 1 
    return 0;
    }
}