package pt.isel.deetc.ls.mapper;


import java.util.ArrayList;

import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Calendar;

public class CalendarMapperTest {

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
	public void showAllCalendarsTest(){
		CalendarMapper c = new CalendarMapper();
		ArrayList<Calendar>  list = c.select();
		
		Assert.assertNotNull(list);
		Assert.assertTrue(list.size() != 0);
		for (int i =0;i<list.size();++i){
			System.out.println(":: "+list.get(i).getID()+" :: "+list.get(i).getName());
		}
	}
	@Test
	public void createAndInserAndVerifyCalendarTest(){
		CalendarMapper c = new CalendarMapper();
		Calendar cal = new Calendar("Nuno A Cancelo");
		
		Assert.assertNotNull(cal);
		int x = c.insert(cal);
		
		System.out.println(":: "+cal.getID()+" :: "+cal.getName()+" == "+x);
	}

}
