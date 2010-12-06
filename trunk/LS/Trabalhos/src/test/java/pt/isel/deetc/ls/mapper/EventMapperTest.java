package pt.isel.deetc.ls.mapper;

import java.util.Iterator;

import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;


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
		Event e = new Event("XPTO", new LSDate(),new LSDate());
		System.out.println("============== NEW EVENT =====================");
		em.insert(e);
		
	}
	private void print(Iterable<Event> x){
		Iterator<Event> xi = x.iterator();
		while(xi.hasNext()){
			System.out.println(xi.next().toString());
		}
	}
	@Test
	public void showAllEventTest(){
		EventMapper c = new EventMapper();
		Iterable<Event>  list = c.select();
		System.out.println("============== SHOW ALL EVENTS =====================");
		Assert.assertNotNull(list);
		print(list);
		Event e = new Event("cancelo", new LSDate(),new LSDate());
		e.setId(1696297799);
		System.out.println("-->"+ c.delete(e));
		System.out.println("-->"+ c.delete(e));
		
	}
	@Test
	public void showAllEventByIDTest(){
		EventMapper c = new EventMapper();
		Event e = new Event("cancelo", new LSDate(),new LSDate());
		e.setId(5790829);
		Iterable<Event>  list = c.selectByID(e);
		System.out.println("============== BY ID =====================");
		Assert.assertNotNull(list);
		print(list);
		
	}
	@Test
	public void showAllEventBetweenDatesTest(){
		EventMapper c = new EventMapper();
		Event e = new Event("cancelo",new LSDate(), new LSDate());

		
	}

	
}
