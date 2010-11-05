package pt.isel.deetc.ls.output;

import java.util.ArrayList;
import pt.isel.deetc.ls.model.Event;

public class EventOutput extends FormatedOutput<Event> {

	public EventOutput(ArrayList<Event> list) {
		super(list);
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

	@Override
	public void setFieldNamesHeader() {
		beginRecord();
		addFieldsHeader("ID");
		addFieldsHeader("Calendar Name");
		addFieldsHeader("Description");
		addFieldsHeader("Location");
		addFieldsHeader("Summary");
		addFieldsHeader("Begin Date");
		addFieldsHeader("End Date");
		endRecord();
	}
}
