package pt.isel.deetc.ls.mapper;

import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.Test;

public class CalendarManagerDBMapperTest{
	public static void setUpBeforeClass() throws Exception {
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
	
	@Test
	public void forceDBCreationTest(){
		CalendarManagerDBMapper c = new CalendarManagerDBMapper();
		//c.createDB(true);
		Assert.assertNotNull(c);
		Assert.assertTrue(c != null);
	}

}
