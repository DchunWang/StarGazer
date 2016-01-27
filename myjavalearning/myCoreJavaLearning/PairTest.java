package pair;

/**
 *@page 530
 *@author wangdch
 *@date 2016-01-27
 */

public class PairTest
{
	public static void main(String[] args)
	{
		String [] words = {"Mary", "had", "a", "little", "lamb"};
		Pair<String> mm = ArrayAlg.minmax(words);
		System.out.println("min=" + mm.getFirst());
		Sysmte.out.println("max=" + mm.getSecond());
		
	}
}

class ArrayAlg
{
	/**
	 * Gets the minimum and maxium of an array of strings
	 * @param a an array of strings
	 * @return a pair with the min and max value, or null if a is null or empty
	 */
	
	public static Pair<String> minmax(String[] a)
	{
		if(a == null || a.length == 0)
			return null;
		String min = a[0];
		String max = a[1];
		for(int i = 1; i < a.length; ++i)
		{
			if(min.compareTo(a[i]) > 0)
				min = a[i];
			if(max.compareTo(a[i]) < 0)
				max = a[i];
		}
		return new Pair<>(min, max);
	}
}
