package pt.isel.deetc.ls.database;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.joda.time.DateTime;

import pt.isel.deetc.ls.model.LSDate;

public class AlarmQuery {
	private List<String> _stm;
	private List<String> _cstm;
	private String _sep;
	private String _st;
	
	private String _selectAlarm = "select id,atrigger,anaction,componentID from Alarm";
	private String _updateComponentStm = "update alarm set ";
	private String _deleteAlarm			= "delete from Alarm";


	public AlarmQuery() {
		_stm = new ArrayList<String>();
		_cstm = new ArrayList<String>();
		_sep="";
		_st="";	
	}
	
	/* INSERT */
	public AlarmQuery insertAlarm(int alarmId, LSDate triggerDate, String anaction,int componentID){
		clearStatements();
		_stm.add("insert into Alarm (id,atrigger,componentID, anaction) values("+alarmId+",'"+triggerDate+"','"+anaction+"',"+componentID+");");
		return this;
	}

	/* Delete */
	public AlarmQuery deleteAlarmById(int alarmId){
		clearStatements();
		_stm.add(_deleteAlarm +" where id = "+alarmId+";");
		return this;
	}
	
	public AlarmQuery deleteAlarmsByComponentId(int componentId){
		_stm.add(_deleteAlarm + " where componentID = "+componentId+";");
		return this;		
	}
	
	public AlarmQuery addSetting(String cstm){
		_cstm.add(cstm);
		return this;
	}

	public AlarmQuery addCondition(String stm){
		_stm.add(stm);
		return this;	
	}

	
	/* SELECT */
	public AlarmQuery select(){
		clearStatements();
		_st=_selectAlarm;
		return this;
	}
	public AlarmQuery selectAlarmById(int alarmID){
		newStatement(_selectAlarm);
		_stm.add(" WHERE ");
		_stm.add(" id = '"+alarmID+"';");
		return this;
	}
	public AlarmQuery selectAlarmByComponentID(int componentID){
		newStatement(_selectAlarm);
		_stm.add(" WHERE ");
		_stm.add(" componentID = '"+componentID+"';");
		return this;
	}
	public AlarmQuery where(){
		_stm.add(" WHERE ");
		return this;
	}
	public AlarmQuery updateAlarm(){
		return updateAlarm(_updateComponentStm);
	}
	
	public AlarmQuery updateAlarm(String stm){
		clearStatements();
		_sep = ",";
		_st= stm;
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

	public AlarmQuery alarmIdIs(int alarmId){
		_stm.add(" id = "+alarmId);
		return this;
	}
	public AlarmQuery alarmIdIsLessThanOrEqual(int alarmId){
		_stm.add(" id <= "+alarmId);
		return this;
	}
	public AlarmQuery alarmIdIsGreatherThanOrEqual(int alarmId){
		_stm.add(" id >= "+alarmId);
		return this;
	}
	
	
	
	public AlarmQuery componentIdIs(int i){
		_stm.add(" component_id = "+i);
		return this;
	}
	public AlarmQuery triggerIs(LSDate date){	
		_stm.add(" atrigger = '"+date+"' ");
		return this;
	}

	public AlarmQuery componentIdIsLessThanOrEqual(int i){	
		_stm.add(" componentID <= "+i);
		return this;
	}
	public AlarmQuery componentIdIsGreatherThanOrEqual(int i){
		_stm.add(" componentID >= "+i);
		return this;
	}

	public AlarmQuery triggerteBetween(LSDate beginDate,LSDate endDate){
		_stm.add(" atrigger >= '"+beginDate+"' AND atrigger <= '"+endDate+"' ");
		return this;
	}
	
	public AlarmQuery triggerGreatherThan(DateTime date){	
		_stm.add(" atrigger >= '"+date+"' ");
		return this;
	}
	public AlarmQuery triggerLessThan(DateTime date){	
		_stm.add(" atrigger <= '"+date+"' ");
		return this;
	}
	
	public AlarmQuery and(){
		_stm.add(" AND ");
		return this;
	}
	public AlarmQuery or(){
		_stm.add(" OR ");
		return this;
	}
	public AlarmQuery setComponentId(int id){
		return addSetting(" componentID = "+id);
	}

	public AlarmQuery setTrigger(LSDate trigger){	
		return addSetting(" atrigger = '"+trigger+"' ");
	}

	public AlarmQuery setanaction(String anaction){	
		return addSetting(" anaction = '"+anaction+"' ");
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
