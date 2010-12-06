package pt.isel.deetc.ls.output;

import java.util.ArrayList;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.Todo;

public class TodoOutput extends FormatedOutput<Todo> {

	public TodoOutput(ArrayList<Todo> list) {
		super(list);
	}

	@Override
	public void addRecord(Todo todo) {
		beginRecord();
//		addField(String.valueOf(todo.getId()));
//		addField(todo.getCalName());
//		addField(todo.getDescription());
//		addField(todo.getLocation());
//		addField(todo.getSummary());
//		addField(todo.getBeginDate().toString());
//		addField(todo.getEndDate().toString());
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
