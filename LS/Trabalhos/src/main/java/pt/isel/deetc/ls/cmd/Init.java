package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.CalendarManagerDBMapper;
import pt.isel.deetc.ls.model.ComponentRule;

public class Init extends Command {
	private static final String _NAME = "init";
	private static final String _DESCRIPTION = "Start the Data Repository";

	public Init(){
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("reset", "force rebuilding the repository, if it exist");
		p1.addRule(ComponentRule.isOptional(p1));
		p1.addRule(ComponentRule.allowEmpty(p1));
				
		addParameter(p1);
	}
	
	@Override
	public void execute() {
    	CalendarManagerDBMapper c = new CalendarManagerDBMapper();
    	c.createDB(getValue("reset") != null);
	}
}