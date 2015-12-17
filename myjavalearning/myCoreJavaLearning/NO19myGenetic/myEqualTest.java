package myGenetic;

/**
 *This program demonstrates the equals method
 *@page 177
 *@author wangdch
 *@date 2015-12-18
 */

public class myEqualTest
{
	public static void main(String [] args)
	{
		Employee alice1 = new Employee("wang", 75000, 1992, 12, 15);
		Employee alice2 = new Employee("wang" , 75000, 1992, 12, 15);
		Employee alice3 = new Employee("Chun", 50000, 1993, 10, 12);
		Employee alice4 =  alice1;
		Employee bob  = new  Employee("Bob", 65000, 1995, 2, 26);
		
		System.out.println("alice1 == alice4: " + (alice1 == alice4));
		System.out.println("alice1 == alice2: " + (alice1 == alice2));
		System.out.println("alice1.equals(alice2" + alice1.equals(alice2));
		System.out.println("alice1.equals(bob): " + alice1.equals(bob));
		System.out.println("bob.toString(): " + bob);
		System.out.println("alice3= " + alice3);
		
		Manager carl = new Manager("Carl", 80000, 1993, 10, 17);
		Manager boss = new Manager("Carl", 80000, 1993, 10, 17);
		
		boss.setBonus(5000);
		
		System.out.println("boss.toString();: " + boss);
		System.out.println("carl.equals(boss): " + carl.equals(boss));
		System.out.println("alice1.hashCode(): " + alice1.hashCode());
		System.out.println("alice2.hashCode(): " + alice2.hashCode());
		System.out.println("bob.hashCode(): " + bob.hashCode());
		System.out.println("carl.hashCode(): " + carl.hashCode());
		
	}
}
