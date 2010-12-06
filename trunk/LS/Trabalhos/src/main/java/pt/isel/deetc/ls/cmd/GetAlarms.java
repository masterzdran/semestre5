package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;

public class GetAlarms extends GetAlarmsAll {

	private static final String _NAME = "get-alarms";
	private static final String _DESCRIPTION = "Show the information of a set of Alarms between a period of time";
	
	public GetAlarms() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("start", "start date of the Todo");
		Parameter p2 = new Parameter("end", "end date of the Todo ('end' and 'duration' are both mutually exclusive)");
		Parameter p3 = new Parameter("duration", "durantion of the Todo ('end' and 'duration' are both mutually exclusive)");
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
		Alarm alarm = new Alarm();
		alarm.setBaseDate(new LSDate(getValue("start")));
		alarm.setTrigger(((getValue("end") != null?new LSDate(getValue("end")):new LSDate(getValue("duration")))));
    	AlarmMapper am = new AlarmMapper();
    	Iterable<Alarm> collection = am.selectBetweenDates(alarm, alarm); 
    	report(collection);
	}
}
