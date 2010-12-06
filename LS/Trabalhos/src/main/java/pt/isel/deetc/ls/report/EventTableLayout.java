package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.report.layout.TableLayout;

public class EventTableLayout extends TableLayout<Event> {
	private Iterable<Event> _inputList;
	public EventTableLayout(Iterable<Event> events) {
		super();
		_inputList = events;
		setHeaders();
		setRows();
	}

	private void setHeaders(){
		ArrayList<String> header= new ArrayList<String>();
		header.add("Calendar Name");
		header.add("Event ID");
		header.add("Start Date/Time");
		header.add("End Date/Time");
		header.add("Location");
		header.add("Summary");
		header.add("Description");
		addColumnsNames(header);
	}
	
	private void setRows(){
		Iterator<Event> it = _inputList.iterator();
		while(it.hasNext()){
			ArrayList<String> event= new ArrayList<String>();
			Event ev = it.next();
			event.add(ev.getCalName());
			event.add(ev.getId()+"");
			event.add(ev.getBeginDate()+"");
			event.add(ev.getEndDate()+"");
			event.add(ev.getLocation());
			event.add(ev.getSummary());
			event.add(ev.getDescription());
			addRow(event);			
		}
	}
}
