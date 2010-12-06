package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;

public class DeleteAlarm extends Command{
	private static final String _NAME = "delete-alarm";
	private static final String _DESCRIPTION = "delete ONE Alarm given his ID";

	public DeleteAlarm() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("event-id", "Event identifier",true);
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		Parameter p2 = new Parameter("alarm-id", "Alarm identifier",true);
		p2.addRule(ComponentRule.isRequired(p2));
		p2.addRule(ComponentRule.allowNoEmpty(p2));
		
		addParameter(p1);
		addParameter(p2);
	}

	@Override
	public void execute() {
		Alarm alarm = new Alarm();
		alarm.setAction(getValue("action"));
		alarm.setTrigger(new LSDate(getValue("trigger")));
		alarm.setComponentID(Integer.parseInt(getValue("component-id")));
    	AlarmMapper am = new AlarmMapper();
    	int i = 0;
    	System.out.println("Rows inserted: "+((i=am.delete(alarm)) > 0?i:0));
 	}

}
