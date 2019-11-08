import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.awt.event.*;
import javax.swing.*;
@SuppressWarnings("serial")
public class Game extends JPanel {

	private Snake snake;
	ArrayList<Tail> tails = new ArrayList<>();
	private int screenSize = 510;
	private static final Color BACKGROUND = new Color(0,0,0);
	private BufferedImage myImage;
	ArrayList<Snake> snakes = new ArrayList<>();
	private Graphics myBuffer;
	private Apple apple;
	private Timer t;
	ArrayList<Tail> z = new ArrayList<>();
	private int x = 250;
	private int y = 250;
	private int score = 0,xloc = 0, yloc = 0;
	private int highscore;
	private boolean w,a,s,d,on;
	//creates and sets up the game
	public Game()
	{
		myImage = new BufferedImage(screenSize,screenSize,BufferedImage.TYPE_INT_RGB);
		myBuffer = myImage.getGraphics();
		myBuffer.setColor(BACKGROUND);
		myBuffer.fillRect(0, 0, screenSize, screenSize);
		apple = new Apple(x,y);
		snakes.add(snake = new Snake());
		//ArrayList<Tail> tails = new ArrayList<>();
		Tail tail = new Tail(snake.getX(),snake.getY());
		tails.add(tail);
		t = new Timer(100, new Listener());
		t.start();
		addKeyListener(new Key());
		setFocusable(true); 
	}

	public class Key extends KeyAdapter
	{
		public void keyPressed(KeyEvent e)
		{
			if(e.getKeyCode()==KeyEvent.VK_W&&s==false)//sets w to true to move the snake up
			{										//everything else is false
				w=true;
				s=false;
				a=false;
				d=false;
			}
			if(e.getKeyCode()==KeyEvent.VK_S&&w==false)//sets s to true to move the snake down 
			{										//everything else is false
				w=false;
				s=true;
				a=false;
				d=false;
			}
			if(e.getKeyCode()==KeyEvent.VK_A&&d==false)//sets a to true to move the snake right 
			{										//everything else is false
				w=false;
				s=false;
				a=true;
				d=false;
			}
			if(e.getKeyCode()==KeyEvent.VK_D&&a==false)//sets d to true to move the snake left
			{										//everything else is false
				w=false;
				s=false;
				a=false;
				d=true;
			}
		}
	}

	public void paintComponent(Graphics g)
	{
		g.drawImage(myImage, 0, 0, screenSize, screenSize, null); 

	}
	public class Listener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			myBuffer.setColor(BACKGROUND); //creates the back ground
			myBuffer.fillRect(0, 0, screenSize, screenSize);

			try 
			{
				Scanner hScore = new Scanner(new File("highscore.txt"));
				highscore = hScore.nextInt();
				hScore.close();
			} 
			catch (FileNotFoundException e1) 
			{
				e1.printStackTrace();
			}
			
			
			
			apple.draw(myBuffer);//creates the apple
			for(Snake x : snakes)//creates the snake
			{
				x.draw(myBuffer);
				x.move(w,s,a,d);
			}

			myBuffer.setColor(BACKGROUND);
			myBuffer.fillRect(0, 0, screenSize, screenSize);
			if(snake.eat(apple, snake))//checks if the apple is eaten
			{
				apple.jump(screenSize, screenSize, tails);//makes the apple jump
				score+=5;//adds 5 to the score
				if(highscore<score)
					highscore=score;
				try
				{
					PrintWriter write = new PrintWriter(new FileWriter("highscore.txt"));
					write.print(highscore);
					write.close();
				}
				catch(Exception e2)
				{
					System.out.println(e2.getMessage());
				}
				if(tails.size()<6)
				{
					if(w)
					{
						xloc += 255;
						yloc += 270;
					}
					if(s==true)
					{
						xloc += 255;
						yloc += 240;
					}
					if(a)
					{
						xloc += 270;
						yloc += 255;
					}
					if(d)
					{
						xloc += 240;
						yloc += 255;
					}
				}
				for(int x=0;x<10;x++)//adds tails to the end of the snake
				{
					Tail tail = new Tail(tails.get(tails.size()-1).getX(),tails.get(tails.size()-1).getY());
					tails.add(tail);
				}

			}

			//moves the the tails to follow the snake
			tails.get(0).move(snake.getX(),snake.getY());
			for(int t=tails.size()-1;t>1;t--)
			{
				tails.get(t).move(tails.get(t-2).getX(),tails.get(t-2).getY());

			}

			snake.draw(myBuffer);
			for(Tail t : tails)
				t.draw(myBuffer);
			apple.draw(myBuffer);

			myBuffer.setColor(BACKGROUND);
			myBuffer.fillRect(xloc, yloc, 15, 15);
			//prints the score on the screen
			myBuffer.setColor(Color.white);
			myBuffer.setFont(new Font("Monospaced", Font.BOLD, 24));
			myBuffer.drawString("Score: "+ score, screenSize-200,25);
			myBuffer.drawString("High Score: "+highscore, screenSize-500, 25);
			myBuffer.fillRect(0, 40, screenSize, 5);
			if(snake.isDead(snake,tails))//checks if the snake is dead
			{
				//prints "game over" and ends the game
				myBuffer.setColor(Color.white);
				myBuffer.setFont(new Font("Monospaced", Font.BOLD, 50));
				myBuffer.drawString("GAME OVER", 100,200);
				t.stop();

				//System.exit(0);

			}
			repaint();

		}
	}

	//runs the game
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("Snake");
		frame.setSize(510,510);
		frame.setLocation(0, 0);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Game g = new Game();
		frame.setContentPane(g);
		g.requestFocus();
		frame.setVisible(true);
	}

}
