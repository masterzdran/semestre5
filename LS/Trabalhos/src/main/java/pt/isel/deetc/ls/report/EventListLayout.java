package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.report.layout.ListLayout;

public class EventListLayout extends ListLayout<Event> {
	private Iterable<Event> _inputList;
	public EventListLayout(Iterable<Event> events) {
		super();
		_inputList = events;
		setRows();
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
