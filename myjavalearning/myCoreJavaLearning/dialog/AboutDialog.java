package dialog;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 *A sample modal dialog that displays a message and waits for the user to click the Ok button
 *@page 405
 *@author wangdch 
 *@date 2016-01-10
 */

public class AboutDialog extends JDialog
{
	public AboutDialog(JFrame owner)
	{
		super(owner, "About DialogTest", true);
		
		//add HTML label to center
		
		add(
				new JLabel(
						"<html><h1><i>Core Java</i></h1><hr>By wangdch </html>"), BorderLayout.CENTER);
		
		//Ok button closes the dialog
		
		JButton ok = new JButton("Ok");
		ok.addActionListener(new ActionListener()
				{
					public void actionPerformed(ActionEvent event)
					{
						setVisible(false);
					}
				});
		
		//add Ok button to southern border
		JPanel panel = new JPanel();
		panel.add(ok);
		add(panel, BorderLayout.SOUTH);
		pack();
	}
}
