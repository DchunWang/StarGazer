package abberation;

import java.util.*;

/**
 *This program tests the customize class
 *@page 107 
 *@author wandch
 *@date 2015-12-12
 */

public class myabet
{
	public static void main(String [] args)
	{
		//fill the staff array with theree Employee objects
		Employee [] staff = new Employee[3];
		staff[0] = new Employee("wang", 75000, 1994, 12, 15);
		staff[1] = new Employee("de", 87000, 1995, 10, 17);
		staff[2] = new Employee("chun", 92000, 1996, 9, 25);
		
		//raise everyone's salary by 5%
		for(Employee e : staff)
			e.raiseSalary(5);
		
		//print out information about all Employee objects
		for(Employee e : staff)
			System.out.println("name=" + e.getName() + ", salary= " + e.getSalary() +
					", hireDay=" + e.getHireDay());
		
	}
}

class Employee
{
	private String name;
	private double salary;
	private Date hireDay;
	
	public Employee(String n, double s, int year, int month, int day)
	{
		name = n;
		salary = s;
		GregorianCalendar calendar = new GregorianCalendar(year, month-1, day);
		
		//GregorianCalendar uses 0 for January
		hireDay = calendar.getTime();
	}
	
	public String getName()
	{
		return name;
	}
	
	public double getSalary()
	{
		return salary;
	}
	
	public Date getHireDay()
	{
		return hireDay;
	}
	
	public void raiseSalary(double byPercent)
	{
		double raise = salary * byPercent / 100;
		salary += raise;
	}
}

//这个是自定义类的使用，要理解其中时如何使用及定义自定义类的
