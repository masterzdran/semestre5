package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;

public class UpdateAlarm extends Command {
	
	private static final String _NAME = "update-alarm";
	private static final String _DESCRIPTION = "updates ONE Component alarm given his ID";

	public UpdateAlarm() {
		super(_NAME, _DESCRIPTION);
		Parameter p1=new Parameter("component-id", "id of the Event or Todo component to update",true);
		Parameter p2=new Parameter("trigger", "date or duration where the trigger should be trigged",true);
		Parameter p3=new Parameter("action", "type of action should be displayed");
		Parameter p4=new Parameter("alarm-id", "id of the alarm to update",true);
		
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));

		p2.addRule(ComponentRule.isOptional(p2));
		p2.addRule(ComponentRule.allowNoEmpty(p2));

		p3.addRule(ComponentRule.isOptional(p3));
		p3.addRule(ComponentRule.allowNoEmpty(p3));
		p3.addRule(ComponentRule.validValues(p3, "AUDIO","DISPLAY","EMAIL"));

		p4.addRule(ComponentRule.isRequired(p4));
		p4.addRule(ComponentRule.allowNoEmpty(p4));
		
		/* Adding the parameters*/
		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
		addParameter(p4);
	}

	@Override
	public void execute() {
		Alarm alarm = new Alarm();
		alarm.setAction(getValue("action"));
		alarm.setTrigger(new LSDate(getValue("trigger")));
		alarm.setComponentID(Integer.parseInt(getValue("component-id")));
		
    	AlarmMapper am = new AlarmMapper();
    	int i = 0;
    	System.out.println("Rows inserted: "+((i=am.update(alarm)) > 0?i:0)); 	}

}
