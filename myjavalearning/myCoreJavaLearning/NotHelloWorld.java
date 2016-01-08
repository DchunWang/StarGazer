package notHelloWorld;

import java.awt.*;
import javax.swing.*;

/**
  *@page 268
  *@author wangdch
  *@date 2016-01-03
  */

public class NotHelloWorld
{
	public static void main(String [] args)
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						JFrame frame = new NotHelloWorldFrame();
						frame.setTitle("NotHelloWorld");
						frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
						frame.setVisible(true);
					}
				});
	}
}


//A frame that contains a message panel

class NotHelloWorldFrame extends JFrame
{
	public NotHelloWorldFrame()
	{
		add(new NotHelloWorldComponent());
		pack();
	}
}

//A component that displays a message

class NotHelloWorldComponent extends JComponent
{
	public static final int MESSAGE_X = 75;
	public static final int MESSAGE_Y = 100;
	
	private static final int DEFAULT_WIDTH = 600;
	private static final int DEFAULT_HEIGHT = 400;
	
	public void paintComponent(Graphics g)
	{
		g.drawString("Not a Hello, World program",  MESSAGE_X,  MESSAGE_Y);
		
	}
	
	public Dimension getPreferredSize()
	{
		return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}
}
