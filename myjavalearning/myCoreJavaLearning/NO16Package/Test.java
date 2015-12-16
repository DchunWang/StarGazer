package mydictum;

//the Employee class is defined in that package

import static java.lang.System.*;

/**
 *This program demonstrates the use of package
 *@page 138
 *@author wangdch
 *@date 2015-12-16
 */

public class myfluid
{
	public static void main(String [] args)
	{
		//because of the import statement, we don't have to use Employee here
		Employee harry = new Employee("Wangdchun", 250, 1994, 12, 25);
		
		harry.raiseSalary(5);
		
		//because of the static import statement, we don't have to use System.out  here
		out.println("name=" + harry.getName() + ", salary=" + harry.getSalary());;
	}
}
