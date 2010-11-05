package pt.isel.deetc.ls.mapper;

import java.util.ArrayList;

import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Event;


public class EventMapperTest {
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
	public void createAndInserAndVerifyEventTest(){
		EventMapper em = new EventMapper();
		Event e = new Event("cancelo", "20101010","20101010");
		System.out.println("============== NEW EVENT =====================");
		Assert.assertNotNull(e);
		//Assert.assertTrue(em.insert(e) != 0);
		
	}
	@Test
	public void showAllEventTest(){
		EventMapper c = new EventMapper();
		ArrayList<Event>  list = c.select();
		System.out.println("============== SHOW ALL EVENTS =====================");
		Assert.assertNotNull(list);
//		Assert.assertTrue(list.size() != 0);
		
	}
	@Test
	public void showAllEventByIDTest(){
		EventMapper c = new EventMapper();
		Event e = new Event("cancelo", "20101010","20101010");
		e.setId(5790829);
		ArrayList<Event>  list = c.selectByID(e);
		System.out.println("============== BY ID =====================");
		Assert.assertNotNull(list);
	//	Assert.assertTrue(list.size() != 0);
		
	}
	@Test
	public void showAllEventBetweenDatesTest(){
		EventMapper c = new EventMapper();
		Event e = new Event("cancelo","20101010", "20101010");
		//ArrayList<Event>  list = c.selectBetweenDates(e);
		//System.out.println("============== Between Date =====================");
		//Assert.assertNotNull(list);
//		Assert.assertTrue(list.size() != 0);
		
	}

	
}
