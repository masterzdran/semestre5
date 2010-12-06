package pt.isel.deetc.ls.ical;

import java.util.ArrayList;
import java.util.Iterator;

import org.junit.Test;

import pt.isel.deetc.ls.domain.ComponentConverter;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;


public class ICalExporterTest {
	
	@Test
	public void testExportCalendar(){
		ArrayList<Event> collection = new ArrayList<Event>();
		ArrayList<Todo> collection2 = new ArrayList<Todo>();
		collection.add(new Event("xpt0", new LSDate(), new LSDate()));
		collection.add(new Event("xpt1", new LSDate(), new LSDate()));
		collection.add(new Event("xpt2", new LSDate(), new LSDate()));
		collection.add(new Event("xpt3", new LSDate(), new LSDate()));
		collection.add(new Event("xpt4", new LSDate(), new LSDate()));
		collection.add(new Event("xpt5", new LSDate(), new LSDate()));
		collection.add(new Event("xpt6", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt0", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt1", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt2", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt3", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt4", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt5", new LSDate(), new LSDate()));
		collection2.add(new Todo("xpt6", new LSDate(), new LSDate()));	

		ComponentConverter cc = new ComponentConverter();
		Iterable<VComponent> vcc = cc.convertToVEvent(collection);
		Iterable<VComponent> vcc2 = cc.convertToVTodo(collection2);


		ICalExporter ice = new ICalExporter("NunoCanceloExportTest2");
		ice.addCollection(vcc);
		ice.addCollection(vcc2);
		
		ice.export();
	}

}
