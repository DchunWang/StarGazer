package my20151212;

/**
 * This applet displays a greeting from my core java
 * @page 27
 * @wangdch
 * 2015-12-13 01:00
 */

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import javax.swing.*;

public class NO3aberrant extends JApplet
{
	public void init()
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						//设置布局
						setLayout(new BorderLayout());
						//新建一个JLabel对象并设置显示的字符及位置
						JLabel label = new JLabel(getParameter("greeting"), SwingConstants.CENTER);
						//设置JLabel对象的字体
						label.setFont(new Font("Serif", Font.BOLD, 18));
						//将JLabel对象添加到布局中
						add(label, BorderLayout.CENTER);
						
						//新建一个JPanel对象
						JPanel panel = new JPanel();
						
						//新建一个JButton对象
						JButton myButton = new JButton("Wang Dchun");
						//添加事件监听？链接到百度吗？？
						myButton.addActionListener(makeAction("http://www.baidu.com"));
						//将JPanel对象添加到之前新建JPanel对象中
						panel.add(myButton);
						
						//新建第二个JButton对象
						JButton wangButton = new JButton("My Love");
						//添加事件监听？？
						wangButton.addActionListener(makeAction("mailto:wdczsdx2012@163.com"));
						panel.add(wangButton);
						
						//将之前的面板也添加到窗口中
						add(panel, BorderLayout.SOUTH);
					}
				});
	}
	
	private ActionListener makeAction(final String urlString)
	{
		return new ActionListener()
				{
					public void actionPerformed(ActionEvent event)
					{
						try
						{
							getAppletContext().showDocument(new URL(urlString));
						}
						catch (MalformedURLException e)
						{
							e.printStackTrace();
						}
					}
				};
	}
}
