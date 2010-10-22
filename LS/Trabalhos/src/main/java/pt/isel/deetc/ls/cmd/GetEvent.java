package pt.isel.deetc.ls.cmd;

import java.util.Map;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.Event;

public class GetEvent extends GetEventsAll {

	private static final String _NAME = "get-event";
	private static final String _DESCRIPTION = "show the information of ONE Event given his ID";

	public GetEvent() {
		super(_NAME, _DESCRIPTION,false);
		addParameter(new ParameterDescriptor("event-id", "identificador do evento", true));
	}

	@Override
	public void execute() {
//		if (!isValidParameter(parameters)){return;}
		//TODO Processar o ID
		Event event= null;
    	EventMapper e = new EventMapper();
    	showHelp();
    	e.selectByID(event);
	}
}
