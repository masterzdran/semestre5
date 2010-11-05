package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class DeleteEvent extends Command{
	private static final String _NAME = "delete-event";
	private static final String _DESCRIPTION = "delete ONE Event given his ID";

	public DeleteEvent() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("event-id", "identificador do evento",true);
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);
	}

	@Override
	public void execute() {
		Event event= new Event("none", "20101010", "20101010");
		event.setId(Integer.parseInt(getValue("event-id")));
    	EventMapper e = new EventMapper();
    	if (e.delete(event)> 0){
    		System.out.println("Event deleted.");
    	}else{
    		System.out.println("No record was deleted.");
    	}
 	}
}
