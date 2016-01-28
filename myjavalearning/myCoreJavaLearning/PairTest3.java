package pair3;

/**
 * @page 552
 * @author wangdch
 *	@date 2016-01-28
 */

public class PairTest3
{
	public static void main(String [] args)
	{
		Manager ceo = new Manager("Gus Greedy", 800000, 2003, 12, 15);
		Manager cfo = new Manager("Sid Sneaky", 600000, 2003, 12, 15);
		Pair<Manager> buddies = new Pair<>(ceo,cfo);
		printBuddies(buddies);
		
		ceo.setBonus(100000);
		cfo.setBonus(50000);
		Manager[] managers = {ceo, cfo};
		
		Pair<Employee> result = new Pair<>();
		minmaxBonus(managers, result);
		System.out.println("first:" + result.getFirst().getName() + ",second:" + result.getSecond().getName());
		maxminBonus(managers, result);
		System.out.println("first:"+result.getFirst().getName() + ", second:" + result.getSecond.getName());
	}
	
	public static void printBuddies(Pair<? extendsEmployee> p)
	{
		Employee first = p.getFirst();
		Employee second = p.getSecond();
		System.out.println(first.getName() + "and " + second.getName() + " are buddies");
		
	}
	
	public static void minmaxBonus(Manager [] a, Pair<> super Manager> result)
	{
		if(a == null || a.length == 0)
			return;
		Manager min = a[0];
		Manager max = a[0];
		for(int i = 1; i < a.length; ++i)
		{
			if(min.getBonus() > a[i].getBonus())
				min = a[i];
			if(max.getBouns() < a[i].getBouns())
				max = a[i];
		}
		result.setFirst(min);
		result.setSecond(max);
	}
	
	public static void maxminBonus(Manager [] a, Pair<? super Manager> result)
	{
		minmaxBonus(a,result);
		PairAlg.swapHelper(result);
	}
}

class PairAlg
{
	public static boolean hasNulls(Pair<?> p)
	{
		return p.getFirst() == null || p.getSecond() == null;
	}
	
	public static void swap(Pair<?> p)
	{
		swapHelper(Pair<T> p);
	}
	
	public static <T> void swapHelper(Pair<T> p)
	{
		T = t.getFirst();
		p.setFirst(p.getSecond());
		p.setSecond(t);
	}
}


