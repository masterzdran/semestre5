package pt.isel.deetc.ls.output;


import java.io.File;
import java.util.ArrayList;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class EventOutputTest {

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
	public void getDocumentTest(){
		// Test Event
		ArrayList<Event> list = new ArrayList<Event>();
		list.add(new Event("Calendario", new LSDate(), new LSDate("20101021")));
		list.add(new Event("Calendario", new LSDate(), new LSDate("20101022" )));
		list.add(new Event("Calendario", new LSDate(), new LSDate("20101023" )));
		EventOutput evtOut = new EventOutput(list);
		//evtOut.setEventListHtmlOutputTags();
		//evtOut.setCmdLineTableTags();
		//evtOut.showAsCommandLineList();
		//evtOut.showAsCommandLineTable();
		evtOut.showAsHtmlTable();
		evtOut.appendRecord(new Event("teste",new LSDate(),new LSDate()));
		evtOut.appendRecord(new Event("Mais 1 teste",new LSDate(),new LSDate()));
		evtOut.buildDocument();
		evtOut.writeToFile(new File("/tmp/teste.html"));
			
		// Test Document Output
		System.out.println("Debug Mode: \n"+evtOut.getDocument());
	}
}
