package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;

public class CreateEvent extends Command {

	private static final String _NAME = "create-event";
	private static final String _DESCRIPTION = "Create one new Event, in return show his event id";

	public CreateEvent() {
		super(_NAME, _DESCRIPTION);
		Parameter p1=new Parameter("cal-name", "name of Calendar where the Event will be created",true);
		Parameter p2=new Parameter("start", "start date of the Event",true);
		Parameter p3=new Parameter("end", "end date of the Event ('end' and 'duration' are both mutually exclusive)");
		Parameter p4=new Parameter("duration", "durantion of the Event ('end' and 'duration' are both mutually exclusive)");
		Parameter p5=new Parameter("summary", "short description of the Event");
		Parameter p6=new Parameter("description", "long description of the Event");
		Parameter p7=new Parameter("location", "location of the Event"); 
		
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));

		p2.addRule(ComponentRule.isRequired(p2));
		p2.addRule(ComponentRule.allowEmpty(p2));
		
		p3.addRule(ComponentRule.isOptional(p3));
		p3.addRule(ComponentRule.allowEmpty(p3));
		p3.addRule(ComponentRule.mutualExclusive(p3, p4));

		p4.addRule(ComponentRule.isOptional(p4));
		p4.addRule(ComponentRule.allowEmpty(p4));
		p4.addRule(ComponentRule.mutualExclusive(p3, p4));		

		p5.addRule(ComponentRule.isOptional(p5));
		p5.addRule(ComponentRule.allowEmpty(p5));
		

		p6.addRule(ComponentRule.isOptional(p6));
		p6.addRule(ComponentRule.allowEmpty(p6));
		

		p7.addRule(ComponentRule.isOptional(p7));
		p7.addRule(ComponentRule.allowEmpty(p7));	
		
		/* Adding the parameters*/
		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
		addParameter(p4);
		addParameter(p5);
		addParameter(p6);
		addParameter(p7);		
	}
	
	/*
	 * Method will be moved to EventMapper
	 */

	@Override
	public void execute() {
		Event event = new Event(getValue("cal-name"), getValue("start"), getValue("end"), getValue("description"), getValue("location"), getValue("summary"));
    	EventMapper e = new EventMapper();
    	e.insert(event);
		
	}
}
