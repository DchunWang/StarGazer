package simpleframe;

import java.awt.*;
import javax.swing.*;

/**
  *@page 257
  *@author wangdch
  *@date 2016-01-03
  */

public class SimpleFrameTest
{
	public static void main(String [] args)
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						SimpleFrame frame = new SimpleFrame();
						frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
						frame.setVisible(true);
					}
				});
		
	}
}

class SimpleFrame extends JFrame
{
	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
	
	public SimpleFrame()
	{
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}
}
