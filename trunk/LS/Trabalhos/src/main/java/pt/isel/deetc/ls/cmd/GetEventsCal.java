package pt.isel.deetc.ls.cmd;

import java.util.Map;

import pt.isel.deetc.ls.mapper.EventMapper;

public class GetEventsCal extends GetEventsAll {

    private static final String _NAME = "get-events-cal";
    private static final String _DESCRIPTION = "show the information of ALL Events of ONE Calendar";


    public GetEventsCal() {
        super(_NAME, _DESCRIPTION,false);
		addParameter(new ParameterDescriptor("cal-name", "name of Calendar where the Event will be created", true));
    }

    @Override
    public void execute() {
//		if (!isValidParameter(parameters)){return;}
		//TODO Processar Event
    	
    	EventMapper e = new EventMapper();
    	showHelp();
    	e.select();
    }

}
