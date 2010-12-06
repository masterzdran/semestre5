package pt.isel.deetc.ls.mapper;

import junit.framework.Assert;

import org.junit.Test;

public class CalendarManagerDBMapperTest{
	@Test
	public void forceDBCreationTest(){
		CalendarManagerDBMapper c = new CalendarManagerDBMapper();
		c.createDB(true);
		Assert.assertNotNull(c);
		Assert.assertTrue(c != null);
	}

}
