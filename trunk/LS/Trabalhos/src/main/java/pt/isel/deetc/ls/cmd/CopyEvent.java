/**
 * 
 */
package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.database.EventQuery;
import pt.isel.deetc.ls.model.Calendar;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class CopyEvent extends Command {
    private static final String _NAME = "copy-event";
    private static final String _DESCRIPTION = "copies ONE Event from one Calendar to another";
    
    /**
     * @param name
     * @param description
     */
    public CopyEvent() {
	super(_NAME,_DESCRIPTION);
	Parameter p1 = new Parameter("event-id","Event identifier", true);
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
	// Retrieve event
	Event event = new Event();
	event.setId(Integer.parseInt(getValue("event-id")));
	
	// Retrieve Destination Calendar
	Calendar cal = new Calendar();
	cal.setName(getValue("destination-calendar-name"));
	
	// Create Event in Destination Calendar (only Calendar_Component is affected)
	EventQuery eQuery = new EventQuery();
	eQuery.insertCalendarComponent(cal.getID(), event.getId());
	
	// TODO - Treat Exceptions in case Calendar and/or Event does not exist
    }
}
