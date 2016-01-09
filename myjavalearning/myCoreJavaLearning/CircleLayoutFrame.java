package circleLayout;

import javax.swing.*;

/**
 *A frame that shows buttons arranged along a circle
 *@page 391
 *@author wangdch
 *@date 2016-01-10
 */

public class CircleLayoutFrame extends JFrame
{
	public CircleLayoutFrame()
	{
		setLayout(new CircleLayout());
		add(new JButton("Yellow"));
		add(new JButton("Blue"));
		add(new JButton("Red"));
		add(new JButton("Green"));
		add(new JButton("Orange"));
		add(new JButton("Fuchsia"));
		add(new JButton("Indigo"));
		pack();
	}
}
