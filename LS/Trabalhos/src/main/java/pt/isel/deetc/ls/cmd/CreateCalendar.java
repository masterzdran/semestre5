package pt.isel.deetc.ls.cmd;
import pt.isel.deetc.ls.mapper.CalendarMapper;
import pt.isel.deetc.ls.model.Calendar;
import pt.isel.deetc.ls.model.ComponentRule;

public class CreateCalendar extends Command {

	private static final String _NAME = "create-calendar";
	private static final String _DESCRIPTION = "Create one new Calendar";
	
	public CreateCalendar() {
		super(_NAME, _DESCRIPTION);
		Parameter _p1 = new Parameter("name", "name of Calendar",true);
		_p1.addRule(ComponentRule.isRequired(_p1));
		_p1.addRule(ComponentRule.allowNoEmpty(_p1));
		addParameter(_p1);
	}
	@Override
	public void execute(){
		Calendar c = new Calendar(getValue("name"));
		CalendarMapper calMap = new CalendarMapper();
		int insertLines = calMap.insert(c);
		System.out.println("Lines inserted: "+insertLines);
	}
}
