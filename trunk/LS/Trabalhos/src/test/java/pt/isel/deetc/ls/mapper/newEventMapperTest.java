package pt.isel.deetc.ls.mapper;

import org.junit.Test;

import pt.isel.deetc.ls.model.Calendar;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class newEventMapperTest {


	@Test
	public void testInsertEvent() {
		CalendarMapper ca = new CalendarMapper();
		ca.insert(new Calendar("tester5"));
		Event e = new Event("tester5",new LSDate("20101111"),new LSDate("20101113"));
		e.setDescription("Testing0");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.insert(e);
	}

	@Test
	public void testDeleteEvent() {
		Event e = new Event("tester5",new LSDate("20101110"), new LSDate("20101113"));
		e.setDescription("Testing0");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.delete(e);
	}

	@Test
	public void testSelect() {
		Event e = new Event("tester5",new LSDate("20101109"), new LSDate("20101113"));
		e.setDescription("Testing");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.select();
	}

	@Test
	public void testSelectBetweenDates() {
		Event e = new Event("tester5",new LSDate("20101108"), new LSDate("20101113"));
		e.setDescription("Testing");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.selectBetweenDates(e);
	}

	@Test
	public void testSelectByCal() {
		Event e = new Event("tester5",new LSDate("20101107"), new LSDate("20101113"));
		e.setDescription("Testing");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.selectByCal(e);
	}

	@Test
	public void testSelectByID() {
		Event e = new Event("tester5",new LSDate("20101106"), new LSDate("20101113"));
		e.setDescription("Testing");
		e.setLocation("Loure");
		e.setSummary("ui ui");
		EventMapper em = new EventMapper();
		em.selectByID(e);
	}

	@Test
	public void testupdate() {
		Event e = new Event("tester5",new LSDate("20101105"), new LSDate("20101113"));
		e.setLocation("XPTO4EVER");
		EventMapper em = new EventMapper();
		em.update(e);
	}

}
