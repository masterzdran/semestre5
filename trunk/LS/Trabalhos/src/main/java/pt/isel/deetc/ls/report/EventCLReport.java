package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import pt.isel.deetc.ls.model.Event;

public class EventCLReport extends ComandLineReport<Event> {

	public EventCLReport(ArrayList<Event> list) {
		super(list);
	}
	public EventCLReport(){
		super();
	}

	@Override
	public void addRecord(Event event) {
		beginRecord();
		addField(String.valueOf(event.getId()));
		addField(event.getCalName());
		addField(event.getDescription());
		addField(event.getLocation());
		addField(event.getSummary());
		addField(event.getBeginDate().toString());
		addField(event.getEndDate().toString());
		endRecord();
	}
	public void show(ArrayList<Event> e){
		buildRecords(e);
		System.out.println(getDocument());		
	}
}
