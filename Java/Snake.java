import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

import javax.swing.Timer;

public class Snake 
{
	private int size;
	private int screenSize = 510;
	private BufferedImage myImage;
	private int xcord;
	private int ycord;
	private Color color;
	private int length;
	private int dist = 15;
	private int score = 0;
	private Timer t;
	private boolean w,a,s,d,on;
	private Snake snake;
	private Apple apple;

	/**
	 * Default constructor for the snake
	 */
	public Snake()
	{
		size = 15;
		length = 15;
		xcord = 60;
		ycord = 60;
		color = Color.yellow;
 
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

	/**
	 * returns the x coordinate
	 * @return x coordinate
	 */
	public int getX()
	{
		return xcord;
	}

	/**
	 * returns the y coordinate
	 * @return the y coordinate
	 */
	public int getY()
	{
		return ycord;
	}

	/**
	 * checks the direction and moves based on the direction
	 * @param w the up direction of movement
	 * @param s the down direction of movement
	 * @param a the left direction of movement
	 * @param d the right direction of movement
	 */
	public void move(boolean w, boolean s, boolean a, boolean d)
	{
		if(w==true)
			setY(getY()-dist);
		else if(s==true)
			setY(getY()+dist);
		else if(a==true)
			setX(getX()-dist);
		else if(d==true)
			setX(getX()+dist);
	}
	
	/**w
	 * checks if the snake is off the screen or hits itself if so returns true else its false
	 * @param s the snake
	 * @return true if it is dead else return false
	 */
	public boolean isDead(Snake s, ArrayList<Tail> tails)
	{
		if(s.getX()<=-15||s.getY()<=50)
			on = true;
		if(s.getX()>=screenSize-21||s.getY()>=screenSize-49)
			on = true;
		for(int t=tails.size()-1;t>2;t--)
		{
		int locx = (tails.get(t).getX()+15);
		int locy = (tails.get(t).getY()+15);
		int locx1 = (tails.get(t).getX()-15);
		int locy2 = (tails.get(t).getY()-15);
		if(s.getX()>=tails.get(t).getX()&&s.getX()<locx&&s.getY()>=tails.get(t).getY()&&s.getY()<locy||
				s.getX()<=tails.get(t).getX()&&s.getX()>locx1&&s.getY()<=tails.get(t).getY()&&s.getY()>locy2)
			on = true;
		if(s.getX()==255&&s.getY()==240)
			on = false;
		if(s.getX()==240&&s.getY()==255)
			on = false;
		if(s.getX()==255&&s.getY()==270)
			on = false;
		if(s.getX()==270&&s.getY()==255)
			on = false;
		}
		return on;
	}
	

	public void paintComponent(Graphics g)
	{
		g.drawImage(myImage, 0, 0, screenSize, screenSize, null); 

	}
	
	/**
	 * draws the snake
	 * @param g graphics component
	 */
	public void draw(Graphics g) 
	{
		g.setColor(color);
		g.fillRect(xcord, ycord, size, length);
	}
	
	/**
	 * Checks if the snakes coordinates are the same as the apple and eats it return true if this 
	 * happens otherwise return false
	 * @param a the apple
	 * @param s the snake
	 * @return true if apple coordinate is the same as the snakes
	 */
	public boolean eat(Apple a, Snake s)
	{
		int locx = (a.getX()+15);
		int locy = (a.getY()+15);
		int locx1 = (a.getX()-15);
		int locy2 = (a.getY()-15);
		if(s.getX()>=a.getX()&&s.getX()<locx&&s.getY()>=a.getY()&&s.getY()<locy||
				s.getX()<=a.getX()&&s.getX()>locx1&&s.getY()<=a.getY()&&s.getY()>locy2)
			return true;
		return false;
	}
}
