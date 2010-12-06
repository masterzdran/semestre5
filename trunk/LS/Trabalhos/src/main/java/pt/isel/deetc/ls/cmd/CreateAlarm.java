package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;

public class CreateAlarm extends Command{

	private static final String _NAME = "create-alarm";
	private static final String _DESCRIPTION = "Create one new Alarm associated to an Event or Todo";

	public CreateAlarm() {
		super(_NAME, _DESCRIPTION);
		Parameter p1=new Parameter("component-id", "id of the Event or Todo component",true);
		Parameter p2=new Parameter("trigger", "date or duration where the trigger should be trigged",true);
		Parameter p3=new Parameter("action", "type of action should be displayed");
		
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));

		p2.addRule(ComponentRule.isRequired(p2));
		p2.addRule(ComponentRule.allowNoEmpty(p2));

		p3.addRule(ComponentRule.isRequired(p3));
		p3.addRule(ComponentRule.allowNoEmpty(p3));
		p3.addRule(ComponentRule.validValues(p3, "AUDIO","DISPLAY","EMAIL"));

		/* Adding the parameters*/
		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
	}
	
	/*
	 * Method will be moved to EventMapper
	 */

	@Override
	public void execute() {
		Alarm alarm = new Alarm();
		alarm.setAction(getValue("action"));
		alarm.setTrigger(new LSDate(getValue("trigger")));
		alarm.setComponentID(Integer.parseInt(getValue("component-id")));
    	AlarmMapper am = new AlarmMapper();
    	int i = 0;
    	System.out.println("Rows inserted: "+((i=am.insert(alarm)) > 0?i:0));
	}

}
