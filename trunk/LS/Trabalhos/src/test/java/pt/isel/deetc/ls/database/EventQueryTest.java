package pt.isel.deetc.ls.database;


import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class EventQueryTest {

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
	public void simpleQuery(){
		Event ev = new Event("Teste",new LSDate("20101109"),new LSDate("20101109"));
		ev.setDescription("Description Test");
		ev.setSummary("Summary Test");
		ev.setLocation("Location test");
		
		System.out.println("----------------------------------------------------------------");
		System.out.println("Event");
		System.out.println("----------------------------------------------------------------");
		System.out.println(ev.toString());
		System.out.println("----------------------------------------------------------------");
		
		int id = ev.getId();
		EventQuery event = new EventQuery();

		System.out.println("----------------------------------------------------------------");
		System.out.println("Delete");
		System.out.println("----------------------------------------------------------------");
		
		event.deleteComponentById(id);
		
		System.out.println(event.getStatement());
		
		System.out.println("----------------------------------------------------------------");
		System.out.println("Update");
		System.out.println("----------------------------------------------------------------");
		
		event.updateEvent().setLocation(ev.getLocation()).setDescription(ev.getDescription()).setSummary(ev.getSummary()).where().componentIdIs(id);
		
		System.out.println(event.getStatement());
		
		event.updateComponent().setBeginDate(ev.getBeginDate()).setEndDate(ev.getEndDate()).where().componentIdIs(id);
		
		System.out.println(event.getStatement());
		
		System.out.println("----------------------------------------------------------------");
		System.out.println("Insert");
		System.out.println("----------------------------------------------------------------");
		
		event.insertComponent(id, ev.getBeginDate(), ev.getEndDate(), 1);
		
		System.out.println(event.getStatement());
		System.out.println("----------------------------------------------------------------");
		
		
		System.out.println(event.getStatement());
		System.out.println("----------------------------------------------------------------");
		
		event.insertComponentCategory(id, 1);
		System.out.println(event.getStatement());
		System.out.println("----------------------------------------------------------------");
		
		event.insertCalendarComponent(1, id);
		System.out.println(event.getStatement());
		System.out.println("----------------------------------------------------------------");
		
		event.selectCalendarByName(ev.getCalName());
		System.out.println(event.getStatement());
		System.out.println("----------------------------------------------------------------");
		
		event.selectComponentTypeId("Event");
		System.out.println(event.getStatement());
		
		System.out.println("----------------------------------------------------------------");
		System.out.println("Select");
		System.out.println("----------------------------------------------------------------");
		
		event.select().where().calendarNameIs(ev.getCalName()).and().beginDateBetween(ev.getBeginDate(), ev.getEndDate());
		
		System.out.println(event.getStatement());
		

		
	}
	
}
