package myVision;

import java.util.*;


/** 
 * This program demonstrates the ArrayList class
 * @page 185
 * @author wangdch
 * @date 2015-12-18
 */

public class myArrayListTest
{
	public static void main(String [] args)
	{
		//fill the staff array list with three Employee object;
		ArrayList<Employee> staff = new ArrayList<>();
		
		staff.add(new Employee("Wang", 75000, 1994, 12, 15));
		staff.add(new Employee("De", 85000, 1993, 10, 12));
		staff.add(new Employee("Chun", 82322, 1994, 3, 8));
		
		
		
		//raise everyone's salary by 5%
		for(Employee e : staff)
		{
			
			System.out.println(e.getName() + ", " + e.getSalary() + ", " + e.getHireDay());
			e.raiseSalary(5);
		}
		
		//print out information about all Employee objects
		for(Employee e : staff)
			System.out.println("name= " + e.getName() + ", salary= " + e.getSalary() + ", hireDay="
					+ e.getHireDay());
	}
}


class Employee
{
	private String name;
	private double salary;
	private Date hireDay;
	
	Employee(String n, double s, int year, int month , int day)
	{
		name = n;
		salary = s;
		GregorianCalendar calendar = new GregorianCalendar(year, month-1, day);
		hireDay = calendar.getTime();
	}
	
	public String  getName()
	{
		return name;
	}
	
	public double  getSalary()
	{
		
		return salary;
	}
	public void raiseSalary(double  byPercent)
	{
		double raise = salary * byPercent / 100;
		salary += raise;
	}
	
	public Date getHireDay()
	{
		return hireDay;
		
	}
	
}
