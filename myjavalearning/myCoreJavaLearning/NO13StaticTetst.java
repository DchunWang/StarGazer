package mydictum;

/**This program demonstrates static methods
 *@page 119
 *@author wangdch
 *@date 2015-12-16
 */

public class myfluid
{
	public static void main(String [] args)
	{
		//fill the staff array with three Employee objects
		Employee[] staff = new Employee[3];
		
		staff[0] = new Employee("wang", 40000);
		staff[1] = new Employee("de", 60000);
		staff[2] = new Employee("chun", 65000);
		
		//print out information about all Employee objects
		for(Employee e : staff)
		{
			e.setId();
			System.out.println("name=" + e.getName() + ", id=" + e.getId() + ", salary=" + e.getSalary());
			
		}
		
		//calls static method 
		int n = Employee.getNextId();
		
		System.out.println("Nexxt available id = " + n);
	}
}

class Employee
{
	//defines a private static variable
	private static int nextId = 1;
	
	private String name;
	private double salary;
	private int id;
	
	public Employee(String n, double s)
	{
		name = n;
		salary = s;
		id = 0;
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
	public void setId()
	{
		//set id to next available id
		id = nextId;
		nextId++;
	}
	
	//defines static method
	public static int getNextId()
	{
		//returns static field
		return nextId;
	}
	
	//unit test
	/*
	public static void main(String [] args)
	{
		Employee e = new Employee("Harry", 50000);
		System.out.print(e.getName() + " " + e.getSalary());
	}
	*/
}

//这个程序中主要学习到静态变量及静态方法的调用
//其中也有单元测试的部分，可以根据需要利用不同命令执行不同的main方法
//java Employee
//java myfluid
