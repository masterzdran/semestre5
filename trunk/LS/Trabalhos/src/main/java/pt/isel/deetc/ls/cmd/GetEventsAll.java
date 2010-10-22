package pt.isel.deetc.ls.cmd;

import java.util.Map;

import pt.isel.deetc.ls.mapper.EventMapper;

public class GetEventsAll extends Command {

    private static final String _NAME = "get-events-all";
    private static final String _DESCRIPTION = "Show the information of ALL Events";


    public GetEventsAll() {
        this(_NAME, _DESCRIPTION,true);
    }
    
    public GetEventsAll(String name, String description, boolean allowNoParameters) {
    	super(name, description,allowNoParameters);
    
    }

    @Override
    public void execute() {
//		if (!isValidParameter(parameters)){return;}
		//TODO Processar o Event
    	EventMapper e = new EventMapper();
    	showHelp();
    	e.select();
    }
}
