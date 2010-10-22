package pt.isel.deetc.ls.cmd;

import java.util.Map;

import org.joda.time.LocalDateTime;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.Event;

public class CreateEvent extends Command {

	private static final String _NAME = "create-event";
	private static final String _DESCRIPTION = "Create one new Event, in return show his event id";
	

	public CreateEvent() {
		super(_NAME, _DESCRIPTION,false);
		addParameter(new ParameterDescriptor("cal-name", "name of Calendar where the Event will be created", true));
		addParameter(new ParameterDescriptor("start", "start date of the Event", false));
		addParameter(new ParameterDescriptor("end", "end date of the Event ('end' and 'duration' are both mutually exclusive)", false));
		addParameter(new ParameterDescriptor("duration", "durantion of the Event ('end' and 'duration' are both mutually exclusive)", false));
		addParameter(new ParameterDescriptor("summary", "short description of the Event", false));
		addParameter(new ParameterDescriptor("description", "long description of the Event", false));
		addParameter(new ParameterDescriptor("location", "location of the Event", false));
	}
	
	/*
	 * Method will be moved to EventMapper
	 */
	private Event parseEvent (Map<String,String> parameters){
		String calName = parameters.get("cal-name");
		String start = parameters.get("start");
		String end = parameters.get("end");
		String duration = parameters.get("duration");
		String summary = parameters.get("summary");
		String description = parameters.get("description");
		String location = parameters.get("location");

		// Validar datas 
		DateTimeFormatter fmt = DateTimeFormat.forPattern("yyyyMMddhhmm");
		LocalDateTime startDate = null;
		if (start != null ){
			startDate = (!start.isEmpty()) ? fmt.parseDateTime(start).toLocalDateTime() : new LocalDateTime();
		}
		LocalDateTime endDate = null;
		if (end != null ){
			endDate = (!end.isEmpty()) ? fmt.parseDateTime(end).toLocalDateTime() : new LocalDateTime();
		}
		if (duration != null){
			endDate = (!duration.isEmpty()) ? fmt.parseDateTime(duration).toLocalDateTime() : new LocalDateTime() ;
		}
		
		Event e = new Event(calName,startDate, endDate);
		e.setDescription(description);
		e.setLocation(location);
		e.setSummary(summary);
		return e;		
	}



	/*
	 * DB Action will be moved to EventMapper
	 */	
	@Override
	public void execute() {
//		if (!isValidParameter(parameters)){return;}
		//TODO Processar o Event
		//Event event= parseEvent(parameters);
		Event event= null;
    	EventMapper e = new EventMapper();
    	showHelp();
    	e.insert(event);
		
	}

//	@Override
//	public boolean isValidParameter(Map<String, String> parameters) {
//		//testing if all parameters options are valid
//		if (!super.isValidParameter(parameters)) return false;
//
//		//Since end and duration are both mutually exclusive, a test must be done
//		if (parameters.containsKey("end") && parameters.containsKey("duration"))
//			return false;
//
//		//As we have valid parameters options, we check if they have valid values		
//		for (String name : getValidParameters().keySet()) {
//			String paramValue = null;
//			if ((paramValue=parameters.get(name)) == null || paramValue.trim().length() == 0 )
//				return false;
//		}
//		return true;
//	}
}
