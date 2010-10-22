package pt.isel.deetc.ls.cmd;

import java.sql.PreparedStatement;
import java.util.Map;

import pt.isel.deetc.ls.mapper.EventMapper;

public class Init extends Command {
	private static final String _NAME = "init";
	private static final String _DESCRIPTION = "Start the Data Repository";
	

	/* Begin Queries */
	/* Versão funcional mas não final */
	private PreparedStatement preparedStatement;

	private static String _CREATEDB = "if db_id('CalendarManager') is null "
		+ "begin "
		+ "create database CalendarManager "
		+ "end;";

	/******************************* Drop's ************************************/
	private static String _DROPDB = " if db_id('CalendarManager') is not null "
		+ "drop database CalendarManager ";

	private static String _DROPCALENDAR =" if object_id('Calendar') is not null "
		+ "begin "
		+ "if object_id('Calendar_Component') is not null "
		+ "begin "
		+ "alter table Calendar_Component "
		+ "drop constraint fk_Calendar_Component1 "
		+ "end "
		+ "drop table Calendar "
		+ "end ";
	private static final String _DROPEVENT = "if object_id('Event') is not null "
		+ "drop table Event; ";

	private static final String _DROPCATEGORY = "if object_id('Category') is not null "
		+ "begin "
		+ "if object_id('Component_Category') is not null "
		+ "begin "
		+ "alter table Component_Category "
		+ "drop constraint fk_Component_Category1 "
		+ "end "
		+ "drop table Category "
		+ "end;";

	private static final String _DROPCOMPONENT = "if object_id('Component') is not null "
		+ "begin "
		+ "if object_id('Event') is not null "
		+ "begin "
		+ "alter table Event "
		+ "drop constraint fk_Event "
		+ "end "
		+ "if object_id('Calendar_Component') is not null "
		+ "begin "
		+ "alter table Calendar_Component "
		+ "drop constraint fk_Calendar_Component2 "
		+ " end "
		+ "if object_id('Component_Category') is not null "
		+ "begin "
		+ "alter table Component_Category "
		+ "drop constraint fk_Component_Category2 "
		+ "end "
		+ " drop table Component "
		+ "end;";

	private static final String _DROPCOMPONENTTYPE = "if object_id('ComponentType') is not null "
		+ "begin "
		+ "if object_id('Component') is not null "
		+ "begin "
		+ "alter table Component "
		+ "drop constraint fk_Component "
		+ "end "
		+ "drop table ComponentType "
		+ "end;";

	private static final String _DROPCOMPONENTCATEGORY = "if object_id('Component_Category') is not null "
		+ "drop table Component_Category; ";

	private static final String _DROPCALENDARCOMPONENT = "if object_id('Calendar_Component') is not null "
		+ "drop table Calendar_Component; ";

	/*************************** Create's das Tabelas *****************************************/

	private static String _CREATECALENDAR = " create table Calendar ("
		+ "id int not null, "
		+ "name char(50) not null unique, "
		+ "constraint pk_Calendar primary key (id) " 
		+ ");";

	private static String _CREATECATEGORY = " create table Category ( "
		+ "id int not null, "
		+ "name char(255) not null unique, "
		+ "constraint pk_Category primary key (id) "
		+ ");";

	private static String _CREATECOMPONENTTYPE = " create table ComponentType ( "
		+ "id int not null, "
		+ "name char(255) not null unique, "
		+ "description char(255), "
		+ "constraint pk_ComponentType primary key (id) "
		+ ");";

	private static String _CREATECOMPONENT = " create table Component ( "
		+ "id int not null, "
		+ "begin_date datetime not null, "
		+ "end_date datetime not null, "
		+ "componentTypeID int not null, "
		+ "constraint pk_Component primary key (id), "
		+ "constraint fk_Component foreign key (componentTypeID) references ComponentType(id) " 
		+ ");";

	private static String _CREATEEVENT = " create table Event ( "
		+ "description char(255), "
		+ "summary char(255), "
		+ "location char(255), "
		+ "componentID int not null, "
		+ "constraint fk_Event foreign key (componentID) references Component(id) "
		+ ");";

	private static String _CREATECALENDARCOMPONENT = " create table Calendar_Component ( "
		+ "calendarID int not null, "
		+ "componentID int not null, "
		+ "constraint fk_Calendar_Component1 foreign key (calendarID) references Calendar (id), "
		+ "constraint fk_Calendar_Component2 foreign key (componentID) references Component (id) "  
		+ ");";

	private static String _CREATECOMPONENTCATEGORY = " create table Component_Category ( "
		+ "categoryID int not null, "
		+ "componentID int not null, "
		+ "constraint fk_Component_Category1 foreign key (categoryID) references Category (id), "
		+ "constraint fk_Component_Category2 foreign key (componentID) references Component (id) "	
		+ ");";

	private static String _INITIALPOPULATE1 = "insert into ComponentType (id,name,description) values (1,'Event', 'Event description')";
	private static String _INITIALPOPULATE2 = "insert into ComponentType (id,name,description) values(2,'Task',  'Task description')";
	private static String _INITIALPOPULATE3 = "insert into Category (id, name) values(1,'Default')";
	
	/* End Queries */

	public Init(){
		super(_NAME, _DESCRIPTION,true);
		addParameter(new ParameterDescriptor("reset", "force rebuilding the repository, if it exist", false));
	}
	
	@Override
	public void execute() {
    	EventMapper e = new EventMapper();
    	showHelp();
    	e.select();
/*
		Connection connection;

		if( !parameters.isEmpty() && !parameters.containsKey("reset") ) return;

		if ( parameters.containsKey("reset")) {
			//_CREATEDB = _DROPDB + _CREATEDB;
			_CREATECALENDAR = _DROPCALENDAR + _CREATECALENDAR;
			_CREATECATEGORY = _DROPCATEGORY + _CREATECATEGORY;
			_CREATECOMPONENTTYPE = _DROPCOMPONENTTYPE + _CREATECOMPONENTTYPE;
			_CREATECOMPONENT = _DROPCOMPONENT + _CREATECOMPONENT;
			_CREATEEVENT = _DROPEVENT + _CREATEEVENT;
			_CREATECALENDARCOMPONENT = _DROPCALENDARCOMPONENT + _CREATECALENDARCOMPONENT;
			_CREATECOMPONENTCATEGORY = _DROPCOMPONENTCATEGORY + _CREATECOMPONENTCATEGORY;
		}
		try {
			//connection = getDataSource().getConnection();
			try {
				connection.setAutoCommit(false);
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			try {
				// Popular inicial da DB 
				
				
				ArrayList<String> queries =  new ArrayList<String>(Arrays.asList( _CREATECALENDAR, _CREATECOMPONENTTYPE, _CREATECATEGORY, _CREATECOMPONENT, _CREATEEVENT,
						_CREATECALENDARCOMPONENT, _CREATECOMPONENTCATEGORY, _INITIALPOPULATE1,_INITIALPOPULATE2,_INITIALPOPULATE3));
				int idx = 0, res=0;	
				for ( String query : queries ) {
					preparedStatement = connection.prepareStatement(query);
					res = preparedStatement.executeUpdate(); 
					if (  idx < 7 && res != 0 || idx > 6 && res != 1) {
						connection.rollback();
						preparedStatement.close();
						connection.close();
						System.out.println("Debug Mode: Rollback activado");
						System.out.println("Debug Mode: query = "+query);
						return;
					}
					++idx;
				}
				

				

				connection.commit();
				preparedStatement.close();
				connection.close();
				System.out.println("Debug Mode: Init executado com sucesso");
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		} catch (SQLServerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		System.out.print(getSyntax());
*/
	}

	@Override
	public boolean isValidParameter(Map<String, String> parameters) {
		//testing if all parameters options are valid
		return super.isValidParameter(parameters);
	}

}