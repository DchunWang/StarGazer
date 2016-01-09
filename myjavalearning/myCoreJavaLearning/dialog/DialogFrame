package dialog;

import java.awt.event.*;
import javax.swing.*;

/**
 *A frame with a menu whoes File->About action shows a dialog
 *@page 404
 *@author wangdch
 *@date 2016-01-10
 */

public class DialogFrame extends JFrame
{
	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
	private AboutDialog dialog;
	
	public DialogFrame()
	{
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		
		//Constructs a File Menu
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		JMenu fileMenu = new JMenu("File");
		menuBar.add(fileMenu);
		
		//Add About and Exit menu items
		
		//The About item shows the About dialog
		JMenuItem aboutItem = new JMenuItem("About");
		aboutItem.addActionListener(new ActionListener()
				{
					public void actionPerformed(ActionEvent event)
					{
						if(dialog == null)				//first time
							dialog = new AboutDialog(DialogFrame.this);
						dialog.setVisible(true);		//pop up dialog
					}
				});
		fileMenu.add(aboutItem);
		
		//The Exit item exits the program
		
		JMenuItem exitItem = new JMenuItem("Exit");
		exitItem.addActionListener(new ActionListener()
				{
					public void actionPerformed(ActionEvent event)
					{
						System.exit(0);
					}
				});
		fileMenu.add(exitItem);
	}
}
