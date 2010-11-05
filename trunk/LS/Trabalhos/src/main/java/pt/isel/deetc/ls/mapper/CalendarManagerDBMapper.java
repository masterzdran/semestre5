package pt.isel.deetc.ls.mapper;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;

import pt.isel.deetc.ls.model.CalendarManagerDB;

public class CalendarManagerDBMapper extends Mapper<CalendarManagerDB> {
	// private static String _CREATEDB = "if db_id('CalendarManager') is null "+
	// "begin " + "create database CalendarManager " + "end;";

	/******************************* Drop's ************************************/
	// private static String _DROPDB =
	// " if db_id('CalendarManager') is not null " +
	// "drop database CalendarManager ";

	private static String _DROPCALENDAR = " if object_id('Calendar') is not null "
			+ "begin "
			+ "if object_id('Calendar_Component') is not null "
			+ "begin "
			+ "alter table Calendar_Component "
			+ "drop constraint fk_Calendar_Component1 "
			+ "end "
			+ "drop table Calendar " + "end ";
	private static final String _DROPEVENT = "if object_id('Event') is not null "
			+ "drop table Event; ";

	private static final String _DROPCATEGORY = "if object_id('Category') is not null "
			+ "begin "
			+ "if object_id('Component_Category') is not null "
			+ "begin "
			+ "alter table Component_Category "
			+ "drop constraint fk_Component_Category1 "
			+ "end "
			+ "drop table Category " + "end;";

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
			+ " drop table Component " + "end;";

	private static final String _DROPCOMPONENTTYPE = "if object_id('ComponentType') is not null "
			+ "begin "
			+ "if object_id('Component') is not null "
			+ "begin "
			+ "alter table Component "
			+ "drop constraint fk_Component "
			+ "end " + "drop table ComponentType " + "end;";

	private static final String _DROPCOMPONENTCATEGORY = "if object_id('Component_Category') is not null "
			+ "drop table Component_Category; ";

	private static final String _DROPCALENDARCOMPONENT = "if object_id('Calendar_Component') is not null "
			+ "drop table Calendar_Component; ";

	/*************************** Create's das Tabelas *****************************************/

	private static String _CREATECALENDAR = " create table Calendar ("
			+ "id int not null, " + "name char(50) not null unique, "
			+ "constraint pk_Calendar primary key (id) " + ");";

	private static String _CREATECATEGORY = " create table Category ( "
			+ "id int not null, " + "name char(255) not null unique, "
			+ "constraint pk_Category primary key (id) " + ");";

	private static String _CREATECOMPONENTTYPE = " create table ComponentType ( "
			+ "id int not null, "
			+ "name char(255) not null unique, "
			+ "description char(255), "
			+ "constraint pk_ComponentType primary key (id) " + ");";

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
	private static String _INITIALPOPULATE2 = "insert into ComponentType (id,name,description) values(2,'Todo',  'Todo description')";
	private static String _INITIALPOPULATE3 = "insert into Category (id, name) values(1,'Default')";

	/* End Queries */
	private ArrayList<String> _stm;
	private ArrayList<String> _drop;

	public CalendarManagerDBMapper() {
		super();
		/*_drop = new ArrayList<String>(Arrays.asList(_DROPCALENDAR,_DROPCATEGORY,
				_DROPCOMPONENTTYPE ,_DROPCOMPONENT,_DROPEVENT,_DROPCALENDARCOMPONENT,_DROPCOMPONENTCATEGORY));
		*/
		_drop =new ArrayList<String>(Arrays.asList( _DROPCALENDAR + _CREATECALENDAR,
				_DROPCATEGORY + _CREATECATEGORY,_DROPCOMPONENTTYPE + _CREATECOMPONENTTYPE,
				_DROPCOMPONENT + _CREATECOMPONENT,_DROPEVENT + _CREATEEVENT,
				_DROPCALENDARCOMPONENT + _CREATECALENDARCOMPONENT,_DROPCOMPONENTCATEGORY + _CREATECOMPONENTCATEGORY,
				_INITIALPOPULATE1, _INITIALPOPULATE2,
				_INITIALPOPULATE3));

		_stm = new ArrayList<String>(Arrays.asList(_CREATECALENDAR,
				_CREATECOMPONENTTYPE, _CREATECATEGORY, _CREATECOMPONENT,
				_CREATEEVENT, _CREATECALENDARCOMPONENT,
				_CREATECOMPONENTCATEGORY, _INITIALPOPULATE1, _INITIALPOPULATE2,
				_INITIALPOPULATE3));
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

	private void process(ArrayList<String> arr) {
		//openConnection();
		PreparedStatement p = null;
		Connection c = getConnection();
		//connection = getDataSource().getConnection();
		try {
			c.setAutoCommit(false);
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		try {
			int idx = 0, res=0;	
			for ( String query : arr ) {
				p = c.prepareStatement(query);
				res = p.executeUpdate(); 
				if (  idx < 7 && res != 0 || idx > 6 && res != 1) {
					c.rollback();
					p.close();
					closeConnection();
					System.out.println("Debug Mode: Rollback activado");
					System.out.println("Debug Mode: query = "+query);
					return;
				}
				++idx;
			}
			c.commit();
			p.close();
			closeConnection();
			System.out.println("Debug Mode: Init executado com sucesso");
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 


	}

	public void createDB(boolean force) {
		if (force)
			process(_drop);
		else
			process(_stm);
	}

}
