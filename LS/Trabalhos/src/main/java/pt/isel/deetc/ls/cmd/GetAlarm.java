package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;

public class GetAlarm extends GetAlarmsAll {
	private static final String _NAME = "get-alarm";
	private static final String _DESCRIPTION = "show the information of ONE alarm given his ID";
	public GetAlarm() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("alarm-id", "alarm identifier",true);
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);
	}

	@Override
	public void execute() {
		Alarm alarm= new Alarm();
		alarm.setComponentID(Integer.parseInt(getValue("alarm-id")));
    	AlarmMapper am = new AlarmMapper();
    	Iterable<Alarm> collection = am.selectByAlarmID(alarm);
    	report(collection);
	}
}
