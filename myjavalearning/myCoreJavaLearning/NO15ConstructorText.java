package  mydictum;

import java.util.*;

/**
 *This program demonstrates object construction
 *@page 132 
 *@author wangdch
 *@date 2015-12-16
 */

public class myfluid
{
	public static void main(String [] args)
	{
		//fill the staff array with three Employee objects
		
		Employee[] staff = new Employee[3];
		
		staff[0] = new Employee("wang", 250);
		staff[1] = new Employee(500);
		staff[2] = new Employee();
		
		//print out information about all Employee objects
		
		for(Employee e : staff)
			System.out.println("name=" + e.getName() + ", id=" + e.getId() + ", salary=" + e.getSalary());
	}
}

class Employee
{
	private static int nextId;
	
	private int id;
	private String name = "";			//instance field initialization
	private double salary;
	
	//static initialization block
	
	static
	{
		//a random generator object
		Random generator = new Random();
		
		//set nextId to a random number between 0 and 9999
		nextId = generator.nextInt(10000);
	}
	
	//object initialization block
	
	{
		id = nextId;
		nextId++;
	}
	
	//three oveloaded constructors
	
	public Employee(String n, double s)
	{
		name = n;
		salary = s;
	}
	
	public Employee(double s)
	{
		//calls the Emloyee(String, double) constructor
		this("Employee #" + nextId, s);
	}
	
	public Employee()
	{
		//name initialized to "" -- see above
		//salary not explicity set -- initialized to 0
		//id initialized in initialization block
	}
	
	public String getName()
	{
		return name;
	}
	
	public double getSalary()
	{
		return salary;
	}
	
	public int getId()
	{
		 return id;
	}
}


//总结

//其中的函数
//Random()
//构造一个新的随机数生成器

//int nextInt(int n)
//返回一个0~(n-1)之间的随机数

//这个程序要注意
//静态初始化块（static initialization block)和对象初始化块（object initialization block)的使用

//无论使用哪个构造器构造对象，对象的id成员变量都是在对象初始化块中被初始化的，
//也即首先运行初始化快，然后才运行构造器的主体部分

//另外，含一个参数的构造器还调用了含有两个参数的构造器
