package myFaith;

/**
 *This program demonstrates inheritance
 *@page 154
 *@author wangdch
 *@date 2015-12-17
 */

public class mysession
{
	public static void main(String [] args)
	{
		//construct a Manage object
		Manager boss =new Manager("wang", 8000, 1995, 1, 10);
		boss.setBonus(5000);
		
		Employee [] staff = new Employee[3];
		
		//fill the staff array with Manager and Employee objects
		staff[0] = new Employee("de", 5000, 1993, 10, 3);
		staff[1] = new Employee("chun", 4000, 1994, 2, 27);
		staff[2] = boss;
		
		//print out information about all Employee objects
		for(Employee e : staff)
			System.out.println("name=" +e.getName() + ", salary=" + e.getSalary());
	}
}

