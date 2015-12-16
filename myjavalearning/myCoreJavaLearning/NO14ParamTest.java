package mydictum;

/**
 *This program demonstrates parameter passing in Java
 *@page 124
 *@author wangdch
 *@date 2015-12-16
 */

public class myfluid
{
	public static void main(String [] args)
	{
		//Test1:Methods can't modify numeric parameters
		
		System.out.println("Testing tripleValue:");
		double percent = 10;
		System.out.println("Before: percent=" + percent);
		
		tripleValue(percent);
		
		System.out.println("After: percent=" + percent);
		
		//Test2 : Methods can change the state of object parameters
		
		System.out.println("\nTesting tripleSalary:");
		Employee harry = new Employee("Harry", 5000);
		System.out.println("Before: salary=" + harry.getSalary());
		
		tripleSalary(harry);
		
		System.out.println("After: salary=" + harry.getSalary());
		
		//Test3 : Methods can't attach new objects to object parameters
		
		System.out.println("\nTesting swap:");
		
		Employee a = new Employee("Alice", 70000);
		Employee b = new Employee("Bob", 60000);
		
		System.out.println("Before: a =" + a.getName());
		System.out.println("Before : b =" + b.getName());
		
		//doesn't work
		swap(a,b);
		
		System.out.println("After: a=" + a.getName());
		System.out.println("After: b=" + b.getName());
	}
	
	//doesn't work
	public static void tripleValue(double x)
	{
		x = 3 * x;
		System.out.println("End of method : x=" + x);
	}
	
	//works
	public static void tripleSalary(Employee x)
	{
		x.raiseSalary(300);
		System.out.println("End of method : salary= " + x.getSalary());
	}
	
	public static void swap(Employee x, Employee y)
	{
		Employee tmp = x;
		x = y;
		y = tmp;
		System.out.println("End of method : x=" + x.getName());
		System.out.println("End of method : y=" + y.getName());
	}
}

//simplified Employee class
class Employee
{
	private String name;
	private double salary;
	
	public Employee(String n, double s)
	{
		name = n;
		salary = s;
	}
	
	public String getName()
	{
		return name;
	}
	
	public double getSalary()
	{
		return salary;
	}
	
	public void raiseSalary(double byPercent)
	{
		double raise = salary * byPercent / 100;
		salary += raise;
	}
}

//总结：

//主要关注swap内外的结果是不同，参数变量x和y确实交换了，但变量a和b没有影响
//java中，对象引用是进行的值传递

/**
 *Java程序中方法参数的使用情况：
 *1:一个方法不能修改一个基本数据类型的参数（即数值型和布尔型)
 *2:一个方法可以改变一个对象参数的状态
 *3:一个方法不能让对象参数引用一个新的对象
 */
