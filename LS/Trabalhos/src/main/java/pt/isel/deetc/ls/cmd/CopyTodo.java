/**
 * 
 */
package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.database.TodoQuery;
import pt.isel.deetc.ls.model.Calendar;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Todo;

public class CopyTodo extends Command {
    private static final String _NAME = "copy-todo";
    private static final String _DESCRIPTION = "copies ONE Todo from one Calendar to another";

    /**
     * @param name
     * @param description
     */
    public CopyTodo() {
	super(_NAME, _DESCRIPTION);
	Parameter p1 = new Parameter("todo-id","Todo identifier", true);
	Parameter p2 = new Parameter("destination-calendar-name","Destination Calendar name", true);
	
	p1.addRule(ComponentRule.isRequired(p1));
	p1.addRule(ComponentRule.allowNoEmpty(p1));
	p2.addRule(ComponentRule.isRequired(p2));
	p2.addRule(ComponentRule.allowNoEmpty(p2));
	
	addParameter(p1);
	addParameter(p2);
    }

    @Override
    public void execute() {
	// Retrieve Todo
	Todo todo = new Todo();
	todo.setId(Integer.parseInt(getValue("todo-id")));
			
	// Retrieve Destination Calendar
	Calendar cal = new Calendar();
	cal.setName(getValue("destination-calendar-name"));
	
	// Create Todo in Destination Calendar (only Calendar_Component is affected)
	TodoQuery tQuery = new TodoQuery();
	tQuery.insertCalendarComponent(cal.getID(), todo.getId());
	
	// TODO - Treat Exceptions in case Calendar and/or Todo does not exist
    }
}
