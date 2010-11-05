package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class GetEventsCal extends GetEventsAll {

    private static final String _NAME = "get-events-cal";
    private static final String _DESCRIPTION = "show the information of ALL Events of ONE Calendar";

    public GetEventsCal() {
        super(_NAME, _DESCRIPTION);
        Parameter p1  =new Parameter("cal-name", "name of Calendar where the Event will be created",true);
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		
		addParameter(p1);
    }

    @Override
    public void execute() {
		Event event= new Event(getValue("cal-name"), "", "");
    	EventMapper e = new EventMapper();
       	setList(e.selectByCal(event));
    	sR();
    }

}
