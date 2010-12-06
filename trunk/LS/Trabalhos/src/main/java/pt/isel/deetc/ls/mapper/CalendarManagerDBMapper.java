package pt.isel.deetc.ls.mapper;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class CalendarManagerDBMapper extends Mapper<CalendarManagerDB> {
	private final static String _SQLPACKAGE 	= "/pt/isel/deetc/ls/sql";
	private final static String _BUILDSCRIPT 	= "buildDB.sql";
	private final static String _DESTROYSCRIPT	= "destroyDB.sql";
	private final static String _EVENTVIEW		= "eventView.sql";
	private final static String _TODOVIEW		= "todoView.sql";
	private final static String _ALARMVIEW		= "alarmView.sql";
	
	private String _build;
	private String _destroy;
	private String _eventV;
	private String _todoV;
	private String _alarmV;
	
    private String loadScript(String script){
    	BufferedReader fileInput;
    	String scriptBuffer="";

		try {
			fileInput = new BufferedReader(new InputStreamReader(this.getClass().getResourceAsStream(_SQLPACKAGE+"/"+script)));
			String line;
			while((line=fileInput.readLine() )!= null ){
				if (!(line.trim().startsWith("--"))){
					scriptBuffer +=line+"\n";
				}
			}
			
			fileInput.close();
		} catch (Exception e) {
			scriptBuffer = null;
			System.out.println("Error while loading the scripts."+e);
		}
    	return scriptBuffer;
    }
	public CalendarManagerDBMapper() {
		super();
		_destroy 	= loadScript(_DESTROYSCRIPT);
		_build		= loadScript(_BUILDSCRIPT);
		_eventV		= loadScript(_EVENTVIEW);
		_todoV		= loadScript(_TODOVIEW);
		_alarmV		= loadScript(_ALARMVIEW);
	}
	public void createDB(boolean force) {
		if (force){
			System.out.println("Droping DB");
			execute(_destroy);
		}
		System.out.println("Building DB");
		execute(_build);
		execute(_eventV);
		execute(_todoV);
		execute(_alarmV);
	}

	@Override
	public int delete(CalendarManagerDB tObject) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public boolean exists(CalendarManagerDB Tobject) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public int insert(CalendarManagerDB tObject) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public ArrayList<CalendarManagerDB> select() {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public int update(CalendarManagerDB tObject) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

}

class CalendarManagerDB {

}
