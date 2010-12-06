package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.model.Todo;
import pt.isel.deetc.ls.report.layout.ListLayout;

public class TodoListLayout extends ListLayout<Todo> {
	private Iterable<Todo> _inputList;
	public TodoListLayout(Iterable<Todo> events) {
		super();
		_inputList = events;
		setRows();
	}
	private void setRows(){
		Iterator<Todo> it = _inputList.iterator();
		while(it.hasNext()){
			ArrayList<String> event= new ArrayList<String>();
			Todo todo = it.next();
			event.add(todo.getCalName());
			event.add(todo.getId()+"");
			event.add(todo.getBeginDate()+"");
			event.add(todo.getEndDate()+"");
			
			event.add(todo.getPriority()+"");
			event.add(todo.getState()+"");
			event.add(todo.getDonePercent()+"");
			addRow(event);			
		}
	}
}
