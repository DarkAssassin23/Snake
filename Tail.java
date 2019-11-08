import java.awt.Color;
import java.awt.Graphics;

public class Tail extends Snake{
	
	private int size;
	private int xcord;
	private int ycord;
	
	public Tail(int x, int y)
	{
		size = 15;
		xcord = x;
		ycord = y;
	}
		
	public int getX()
	{
		return xcord;
	}
	
	public int getY()
	{
		return ycord;
	}
	
	
	/**
	 * sets the x coordinate
	 * @param x  the x coordinate
	 */
	public void setX(int x)
	{
		xcord = x;
	}

	/**
	 * sets the y coordinate
	 * @param y the y coordinate 
	 */
	public void setY(int y)
	{
		ycord = y;
	}
	
	public void move(int x, int y)
	{
		setX(x);
		setY(y);
	}
	public void draw(Graphics g)
	{
		g.setColor(Color.yellow);
		g.fillRect(xcord, ycord, size, size);
//		g.setColor(Color.black);
//		g.fillRect(xcord, ycord, size, size);
	}
	

}
