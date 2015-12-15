package abberation;

import java.util.*;

/**
 *This program demonstrate console input
 *@page 55
 *@wangdch
 *@date 2015-12-15
 */

public class myabet
{
	public static void main(String [] args)
	{
		Scanner in = new Scanner(System.in);
		
		//get first input
		System.out.print("What's your name?");
		String name = in.nextLine();
		
		//get second input
		System.out.print("How old are you?");
		int age = in.nextInt();
		
		//display output on console
		System.out.println("Hello " + name + ". Next year , you will be " + (age + 1));
	}
}
