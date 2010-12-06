package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.model.Todo;
import pt.isel.deetc.ls.report.layout.TableLayout;

public class TodoTableLayout extends TableLayout<Todo> {
	private Iterable<Todo> _inputList;
	public TodoTableLayout(Iterable<Todo> events) {
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
		header.add("Priority");
		header.add("State");
		header.add("Percent Done");
		addColumnsNames(header);
	}
	
	private void setRows(){
		Iterator<Todo> it = _inputList.iterator();
		while(it.hasNext()){
			ArrayList<String> event= new ArrayList<String>();
			Todo ev = it.next();
			event.add(ev.getCalName());
			event.add(ev.getId()+"");
			event.add(ev.getBeginDate()+"");
			event.add(ev.getEndDate()+"");
			event.add(ev.getPriority()+"");
			event.add(ev.getState()+"");
			event.add(ev.getDonePercent()+"");
			addRow(event);			
		}
	}
}
