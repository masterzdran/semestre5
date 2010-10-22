package pt.isel.deetc.ls.utils;

import java.util.UUID;

public class Utils {
	public static int getUniqueID(){
		return (int) UUID.randomUUID().getLeastSignificantBits() & 0x7FFFFFFF;
	}

}
