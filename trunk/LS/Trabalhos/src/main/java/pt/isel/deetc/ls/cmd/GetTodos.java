package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class GetTodos extends GetEventsAll {

	private static final String _NAME = "get-events";
	private static final String _DESCRIPTION = "Show the information of a set of Event between a period of time";
	
	public GetTodos() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("start", "start date of the Event");
		Parameter p2 = new Parameter("end", "end date of the Event ('end' and 'duration' are both mutually exclusive)");
		Parameter p3 = new Parameter("duration", "durantion of the Event ('end' and 'duration' are both mutually exclusive)");
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowEmpty(p1));
		
		p2.addRule(ComponentRule.isOptional(p2));
		p2.addRule(ComponentRule.allowEmpty(p2));
		p2.addRule(ComponentRule.mutualExclusive(p2, p3));

		p3.addRule(ComponentRule.isOptional(p3));
		p3.addRule(ComponentRule.allowEmpty(p3));
		p3.addRule(ComponentRule.mutualExclusive(p2, p3));	
		
		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
	}

	@Override
	public void execute() {
		//TODO Processar as Datas
		Event event= new Event("none", getValue("start"), getValue("end"));
    	EventMapper e = new EventMapper();
       	setList(e.selectBetweenDates(event));
    	sR();
	}
}
