package pt.isel.deetc.ls.cmd;


import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.exceptions.InvalidCommandParameterException;

public class CreateEventTest {

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
	public void CreateEventParamTest(){
		CreateEvent c = new CreateEvent();
		String string = "TESTE2010-2";
		Assert.assertNotNull(c);
		
		c.addParameter("cal-name",string);
		c.addParameter("start","20101010");
		c.addParameter("end","20101011");
		
		
		Assert.assertTrue(c.getValue("cal-name").equals(string));
		Assert.assertTrue(c.getValue("start").equals("20101010"));
		Assert.assertTrue(c.getValue("end").equals("20101011"));
		
		//c.run();
	}
	@Test(expected = InvalidCommandParameterException.class)
	public void CreateEventParamWithExceptionTest(){
		CreateEvent c = new CreateEvent();
		String string = "TESTE2010-2";
		Assert.assertNotNull(c);
		
		c.addParameter("cal-name",string);
		c.addParameter("start","20101010");
		c.addParameter("end","20101011");
		c.addParameter("duration","90");
		
		
		Assert.assertTrue(c.getValue("cal-name").equals(string));
		Assert.assertTrue(c.getValue("start").equals("20101010"));
		Assert.assertTrue(c.getValue("end").equals("20101011"));
		
		//c.run();
	}
	@Test
	public void CreateEventAndInsertParamTest(){
		CreateEvent c = new CreateEvent();
		String string = "TESTE2010-2";
		Assert.assertNotNull(c);
		
		c.addParameter("cal-name",string);
		c.addParameter("start","20101010");
		c.addParameter("end","20101011");
		
		
		Assert.assertTrue(c.getValue("cal-name").equals(string));
		Assert.assertTrue(c.getValue("start").equals("20101010"));
		Assert.assertTrue(c.getValue("end").equals("20101011"));
		
		//c.run();
	}
}
