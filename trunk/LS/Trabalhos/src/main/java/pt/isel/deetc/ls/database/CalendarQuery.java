package pt.isel.deetc.ls.database;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.joda.time.DateTime;

import pt.isel.deetc.ls.model.LSDate;

public class CalendarQuery {
	private List<String> _stm;
	private List<String> _cstm;
	private String _sep;
	private String _st;
	
	private String _selectCalendar = "select id,name from Calendar";

	public CalendarQuery() {
		_stm = new ArrayList<String>();
		_cstm = new ArrayList<String>();
		_sep="";
		_st="";	
	}
	
	/* INSERT */
	public CalendarQuery insertCalendar(int calendarId,String calendarName){
		clearStatements();
		_stm.add("insert into Calendar (id,name) values("+calendarId+",'"+calendarName+"');");
		return this;
	}

	
	/* SELECT */
	public CalendarQuery select(){
		clearStatements();
		_st=_selectCalendar;
		return this;
	}
	public CalendarQuery selectCalendarById(int calendarID){
		newStatement(_selectCalendar);
		_stm.add(" WHERE ");
		_stm.add(" id = '"+calendarID+"';");
		return this;
	}

	private void newStatement(String stm){
		clearStatements();
		_st=stm;
	}
	protected void clearStatements(){
		_stm.clear();
		_cstm.clear();	
		_sep="";
		_st="";
	}
	/*--------------------------------------------------------------------*/	

	public CalendarQuery calendarIdIs(int calendarId){
		_stm.add(" id = "+calendarId);
		return this;
	}
	public CalendarQuery calendarIdIsLessThanOrEqual(int calendarId){
		_stm.add(" id <= "+calendarId);
		return this;
	}
	public CalendarQuery calendarIdIsGreatherThanOrEqual(int calendarId){
		_stm.add(" id >= "+calendarId);
		return this;
	}
	public CalendarQuery calendarNameIs(String calendarName ){
		_stm.add(" name = "+calendarName);
		return this;
	}
	public CalendarQuery calendarNameLike(String calendarName){	
		_stm.add(" name like '%"+calendarName+"%' ");
		return this;
	}
	public CalendarQuery where(){
		_stm.add(" WHERE ");
		return this;
	}
	public CalendarQuery and(){
		_stm.add(" AND ");
		return this;
	}
	public CalendarQuery or(){
		_stm.add(" OR ");
		return this;
	}

	public String getStatement(){
		StringBuffer stm = new StringBuffer();
		Iterator<String> i = _cstm.iterator();
		Iterator<String> conditions = _stm.iterator();
		stm.append(_st);
		while( i.hasNext()){
			stm.append(i.next());
			if (i.hasNext()){
				stm.append(_sep);
			}
		}
		while(conditions.hasNext()){
			stm.append(conditions.next());
		}
		return stm.toString();
	}
}
