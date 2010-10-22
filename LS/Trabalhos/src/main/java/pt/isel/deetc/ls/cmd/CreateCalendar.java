package pt.isel.deetc.ls.cmd;
import java.util.Map;

import pt.isel.deetc.ls.mapper.CalendarMapper;
import pt.isel.deetc.ls.model.Calendar;

public class CreateCalendar extends Command {

	private static final String _NAME = "create-calendar";
	private static final String _DESCRIPTION = "Create one new Calendar";

	public CreateCalendar() {
		super(_NAME, _DESCRIPTION,false);
		addParameter(new ParameterDescriptor("name", "name of Calendar", true));
	}

	@Override
	public void execute(){
//		if (!isValidParameter(parameters)){
//			System.err.println("Was found an invalid usage of an parameter option while parsing.");
//			showHelp();
//			return;
//		}
		
		Calendar c = new Calendar(getValue("name"));
		CalendarMapper calMap = new CalendarMapper();
		int insertLines = calMap.insert(c);
		System.out.println("Lines inserted: "+insertLines);
	}

//	@Override
//	public boolean isValidParameter(Map<String, String> parameters) {
//		//testing if all parameters options are valid
//		if (!super.isValidParameter(parameters)) return false;
//		
//		/*As we have valid parameters options, we check if they have valid values*/
//		for (String name : getValidParameters().keySet()) {
//			String paramValue = null;
//			if ((paramValue=parameters.get(name)) == null || paramValue.trim().length() == 0 )
//				return false;
//		}
//		return true;
//	}

}
