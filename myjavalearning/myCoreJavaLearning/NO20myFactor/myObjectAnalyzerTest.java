package myFactor;

import java.util.ArrayList;

/**
 *This program uses reflection to spy on objects
 *@page 203
 *@author wangdch
 *@date 2015-12-18
 */

public class myObjectAnalyzerTest
{
	public static void main(String [] args)
	{
		ArrayList<Interger> squares = new ArrayList<>();
		for(int i = 1; i <= 5; i++)
			squares.add(i * i);
		System.out.println(new ObjectAnalyzer().toString(squares));
	}
}
