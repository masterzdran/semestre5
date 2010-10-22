package pt.isel.deetc.ls.cmd;

import java.util.Map;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.Event;

public class GetEvents extends GetEventsAll {

	private static final String _NAME = "get-events";
	private static final String _DESCRIPTION = "Show the information of a set of Event between a period of time";
	
	public GetEvents() {
		super(_NAME, _DESCRIPTION,false);
		addParameter(new ParameterDescriptor("start", "start date of the Event", false));
		addParameter(new ParameterDescriptor("end", "end date of the Event ('end' and 'duration' are both mutually exclusive)", false));
		addParameter(new ParameterDescriptor("duration", "durantion of the Event ('end' and 'duration' are both mutually exclusive)", false));
	}

	@Override
	public void execute() {
//		if (!isValidParameter(parameters)){return;}
		//TODO Processar as Datas
		Event event= null;
    	EventMapper e = new EventMapper();
    	showHelp(); // delete this line
    	e.selectBetweenDates(event);
	}

//	@Override
//	public boolean isValidParameter(Map<String, String> parameters) {
//		if (!super.isValidParameter(parameters)) return false;
//		
//		if (parameters.containsKey("end") && parameters.containsKey("duration")){
//			System.err.println("The option 'end' and ' 'duration' are mutal exclusive. You can only use one at the time!");
//			return false;
//		}
//		return true;
//	}

}
