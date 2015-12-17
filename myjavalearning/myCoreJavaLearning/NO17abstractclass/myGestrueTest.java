package myGesture;

  /**
   * This program demonstrates abstract classe
   * @page 166
   * @author wangdch
   * @date 2015-12-18
   */

public class myAbstractClass
{
	public static void main(String [] args)
	{
		Person [] people = new Person[2];
		
		//fill the people array with Student and Employee objects
		people [0] = new Employee("wang", 5000, 1992, 10, 3);
		people[1] = new Student("dechun", "computer science");
		
		//print out names and descriptions of all Person objects
		for(Person p : people)
			System.out.println(p.getName() + ", " + p.getDescription());
	}
}
