import java.awt.*;
import java.util.ArrayList;
public class Apple 
{
	private int xcord;
	private int ycord;
	private int size;
	private Color color;

	/**
	 * Default apple 
	 */
	public Apple()
	{

		xcord = 210;
		ycord = 210;
		size = 15;
		color = Color.red;
	}


	/**
	 * crates an apple with coordinates of x and y
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	public Apple(int x, int y)
	{
		while(x%15!=0)
			x++;
		while(y%15!=0)
			y++;
		xcord = x;
		ycord = y;
		size = 15;
		color = Color.red;
	}

	/**
	 * returns the x coordinate
	 * @return the x coordinate
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
	 * returns the color
	 * @return the color
	 */
	public Color getColor()
	{
		return color;
	}

	/**
	 * sets the x and y coordinates to somewhere randomly on the screen
	 * @param rightEdge farthest x coordinate
	 * @param bottomEdge farthest y coordinate
	 */
	public void jump(int rightEdge, int bottomEdge, ArrayList<Tail> tails)
	{
		int x,y;
		x = (int)(Math.random()*(rightEdge-65));
		y = (int)(Math.random()*(bottomEdge-65));
		while(x%15!=0)
			x++;
		while(y%15!=0)
			y++;
		if(y<50)
		{
			while(y<50)
			{
				x = (int)(Math.random()*(rightEdge-65));
				y = (int)(Math.random()*(bottomEdge-65));
				while(x%15!=0)
					x++;
				while(y%15!=0)
					y++;
			}
		}

		for(int t=0;t<tails.size()-1;t++)
		{
			if(x==tails.get(t).getX()&&y==tails.get(t).getY())
			{
				x = (int)(Math.random()*(rightEdge-65));
				y = (int)(Math.random()*(bottomEdge-65));
				while(x%15!=0)
					x++;
				while(y%15!=0)
					y++;
				t=0;
				if(y<50)
				{
					while(y<50)
					{
						x = (int)(Math.random()*(rightEdge-65));
						y = (int)(Math.random()*(bottomEdge-65));
						while(x%15!=0)
							x++;
						while(y%15!=0)
							y++;
					}
				}
			}
				
		}
		xcord = x;
		ycord = y;


	}

	/**
	 * draws the apple on the screen
	 * @param g graphics component
	 */
	public void draw(Graphics g)
	{
		g.setColor(color);
		g.fillRect(xcord, ycord, size, size);
	}
}
