package pt.isel.deetc.ls.cmd;


import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.exceptions.InvalidCommandParameterException;

public class CreateCalendarTest {

	@BeforeClass
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
	public void CreateCalendarDynamicArgmentTest(){
		CreateCalendar c = new CreateCalendar();
		Assert.assertNotNull(c);
		
		c.addParameter("name","teste");
		
		Assert.assertTrue(c.getValue("name").equals("teste"));
	}

	@Test(expected = InvalidCommandParameterException.class)
	public void CreateCalendarDynamicArgmentWithExceptionTest(){
		CreateCalendar c = new CreateCalendar();
		Assert.assertNotNull(c);
		
		c.addParameter("name","teste");
		
		Assert.assertTrue(c.getValue("name").equals("teste"));
		c.addParameter("xname","teste");
		
	}
	
	@Test
	public void CreateCalendarInDBTest(){
		CreateCalendar c = new CreateCalendar();
		String string = "TESTE2010-2";
		Assert.assertNotNull(c);
		
		c.addParameter("name",string);
		
		Assert.assertTrue(c.getValue("name").equals(string));
		//c.run();

	}	
	
}
