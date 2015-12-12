package my20151212;

/**
 * This program displays a greeting from the core java volume I.
 * @page 19
 * @author wangdch
 *
 */

public class night20151212
{
	public static void main(String [] args)
	{
		//创建一个字符串数组
		String [] greeting = new String[3];
		//给字符串数组中各个数组元素复制
		greeting[0] = "Welcome to my Core Java";
		greeting[1] = "by wangdch";
		greeting[2] = "2015-12-12";
		
		//利用for循环遍历数组中的元素并输出
		for(String a : greeting)
		{
			System.out.println(a);
		}
	}
}
