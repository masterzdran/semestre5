package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class GetEvent extends GetEventsAll {
	private static final String _NAME = "get-event";
	private static final String _DESCRIPTION = "show the information of ONE Event given his ID";
	public GetEvent() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("event-id", "event identifier",true);
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);
	}

	@Override
	public void execute() {
		Event event= new Event();
		event.setId(Integer.parseInt(getValue("event-id")));
    	EventMapper e = new EventMapper();
    	Iterable<Event> events = e.selectByID(event);
    	report(events);
	}
}
