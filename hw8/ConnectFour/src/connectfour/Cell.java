package connectfour;

/**
 * This class uses in the ConnectFour class.It keeps data about game Cells.
 * @version 1.0.1
 * @author burhan
 */
public class Cell {

    private int xPos;//data fieldler
    private int yPos;
    private int column;
    private int row;
    private char data;

/**
 * 
 * @return Cell x position
 */
    public int getterxPos(){
        return xPos;
    }	
    /**
     * 
     * @return Cell y position
     */
    public int getteryPos(){
        return yPos;
    }
    /**
     * 
     * @return Cell type
     */
    public char getterCellType(){
        return data;
    }
    /**
     * 
     * @return cell column
     */
    public int getterColumn(){
        return column;
    }
    /**
     * 
     * @return cell row
     */
    public int getterRow(){
        return row;
    }
    /**
     * 
     * @param i set to cell row
     */
    public void setterRow(int i){
        row=i;
    }	
    /**
     * 
     * @param i set to cell x position
     */
    public void setterxPos(int i){
        xPos=i;
    }	
    /**
     * 
     * @param i set the cell y position
     */
    public void setteryPos(int i){
        yPos=i;
    }
    /**
     * 
     * @param i set the cell data
     */
    public void setterData(char i){
        data=i;
    }
    /**
     * 
     * @param i set the cell column
     */
    public void setterColumn(int i){
        column=i;
    }
}