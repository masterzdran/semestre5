package pt.isel.deetc.ls.startup;

import java.util.UUID;

public class testing {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		for (int x = 0; x < 10000; ++x) {
			int z = 0x7FFFFFFF;
			UUID u = UUID.randomUUID();
			int i = ((int) u.getLeastSignificantBits())&z;
			//System.out.println(x+" :U: " + u);
			System.out.println(i);
		}
	}
}
