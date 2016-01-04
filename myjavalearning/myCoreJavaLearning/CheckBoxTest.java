package checkBox;

import java.awt.*;
import javax.swing.*;

/**
 *@page 341
 *@author wangdch
 *@date 2016-01-05
 */
 
 public class CheckBoxTest
 {
	 public static void main(String [] args)
	 {
		 EventQueue.invokeLater(new Runnable()
		 {
			 public void run()
			 {
				 JFrame frame = new CheckBoxFrame();
				 frame.setTitle("CheckBoxTest");
				 frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				 frame.setVisible(true);
			 }
		 });
	 }
 }
 
