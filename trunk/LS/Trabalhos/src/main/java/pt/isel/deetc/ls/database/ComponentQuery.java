package pt.isel.deetc.ls.database;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.joda.time.DateTime;

import pt.isel.deetc.ls.model.LSDate;

public abstract class ComponentQuery {
	private List<String> _stm;
	private List<String> _cstm;
	private String _sep;
	private String _st;
	
	
	private String _selectCalendarByID = "select id from Calendar ";
	private String _selectComponentTypeId = "select id from ComponentType ";
	private String _updateComponentStm = "update component set ";
	
	private String _deleteCalendarComponent = "delete from Calendar_Component where componentID = ";
	private String _deleteComponentCategory = "delete from Component_Category where componentID = ";
	private String _deleteComponent			= "delete from Component where ID = ";
	private String _deleteComponentType		= "delete from ? where componentID =  ";

	public ComponentQuery(String componentName) {
		_stm = new ArrayList<String>();
		_cstm = new ArrayList<String>();
		_deleteComponentType=_deleteComponentType.replaceAll("\\?",""+componentName);
		_sep="";
		_st="";	
	}
	
	/* INSERT */
	public ComponentQuery insertComponent(int id,LSDate begin_date,LSDate end_date, int componentTypeID){
		//clearStatements();
		_stm.add("insert into Component (id,begin_date,end_date, componentTypeID) values("+id+",'"+begin_date+"','"+end_date+"',"+componentTypeID+");");
		return this;
	}
	public ComponentQuery insertComponentCategory(int componentID,int categoryID){
		//clearStatements();
		_stm.add("insert into Component_Category (componentID, categoryID) values ( "+componentID+","+categoryID+");");
		return this;
	}
	public ComponentQuery insertCalendarComponent(int calendarID,int componentID){
		//clearStatements();
		_stm.add("insert into Calendar_Component (calendarID,componentID) values("+calendarID+","+componentID+");");
		return this;
	}
	/* Delete */
	public ComponentQuery deleteComponentById(int componentId){
		clearStatements();
		_stm.add(_deleteCalendarComponent+componentId+";");
		_stm.add(_deleteComponentCategory+componentId+";");
		_stm.add(_deleteComponentType+componentId+";");
		_stm.add(_deleteComponent+componentId+";");	
		return this;
	}
	
	public ComponentQuery addStatement(String stm){
		_stm.add(stm);
		return this;		
	}
	public ComponentQuery addSetting(String cstm){
		_cstm.add(cstm);
		return this;
	}
	public ComponentQuery addCondition(String stm){
		_stm.add(stm);
		return this;	
	}
	public ComponentQuery deleteCalendarComponent(int calendarID,int componentID){
		_stm.add("delete from Calendar_Component where calendarID = "+calendarID+" and componentID = "+componentID+";");
		return this;
	}
	
	/* SELECT */
	public ComponentQuery select(String selectStm){
		clearStatements();
		_st=selectStm;
		return this;
	}
	public ComponentQuery selectComponentId(int componentID){
		newStatement("select id from Component ");
		_stm.add(" WHERE ");
		_stm.add(" id = '"+componentID+"';");
		return this;
	}
	public ComponentQuery selectComponentTypeId(String name){
		newStatement(_selectComponentTypeId);
		_stm.add(" WHERE ");
		_stm.add(" name = '"+name+"';");
		return this;
	}
	public ComponentQuery selectCalendarByName(String name){
		newStatement(_selectCalendarByID);
		_stm.add(" WHERE ");
		_stm.add(" name = '"+name+"';");
		return this;
	}
	public ComponentQuery where(){
		_stm.add(" WHERE ");
		return this;
	}
	public ComponentQuery updateComponent(){
		return updateComponent(_updateComponentStm);
	}
	public ComponentQuery updateComponent(String stm){
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
	public ComponentQuery  whereComponentIdIs(int i){
		return  addCondition("where id = "+i);
	}
	
	/*--------------------------------------------------------------------*/	
	
	public ComponentQuery componentIdIs(int i){
		_stm.add(" component_id = "+i);
		return this;
	}
	public ComponentQuery beginDateIs(DateTime date){	
		_stm.add(" begin_date = '"+date+"' ");
		return this;
	}
	public ComponentQuery endDateIs(DateTime date){	
		_stm.add(" end_date = '"+date+"' ");
		return this;
	}
	public ComponentQuery calendarNameIs(String name){
		_stm.add(" calendar_name = '"+name+"' ");
		return this;
	}	
	public ComponentQuery componentIdIsLessThanOrEqual(int i){	
		_stm.add(" component_id <= "+i);
		return this;
	}
	public ComponentQuery componentIdIsGreatherThanOrEqual(int i){
		_stm.add(" component_id >= "+i);
		return this;
	}

	public ComponentQuery beginDateBetween(LSDate beginDate,LSDate endDate){
		_stm.add(" begin_date >= '"+beginDate+"' AND begin_date <= '"+endDate+"' ");
		return this;
	}
	
	public ComponentQuery beginDateGreatherThan(DateTime date){	
		_stm.add(" begin_date >= '"+date+"' ");
		return this;
	}
	public ComponentQuery beginDateLessThan(DateTime date){	
		_stm.add(" begin_date <= '"+date+"' ");
		return this;
	}
	
	public ComponentQuery endDateBetween(LSDate beginDate,LSDate endDate){
		_stm.add(" end_date >= '"+beginDate+"' AND end_date <= '"+endDate+"' ");
		return this;
	}
	public ComponentQuery endDateGreatherThan(DateTime date){	
		_stm.add(" end_date >= '"+date+"' ");
		return this;
	}
	public ComponentQuery endDateLessThan(DateTime date){	
		_stm.add(" end_date <= '"+date+"' ");
		return this;
	}

	public ComponentQuery and(){
		_stm.add(" AND ");
		return this;
	}
	public ComponentQuery or(){
		_stm.add(" OR ");
		return this;
	}
	/* Sort */
	public ComponentQuery inAscendingOrder(String field) {
	    _stm.add(" ORDER BY "+field+" ASC");
	    return this;
	}
	
	public ComponentQuery inDescendingOrder(String field) {
	    _stm.add(" ORDER BY "+field+" DESC");
	    return this;
	}
	
	public ComponentQuery setEventId(int i){
		return addSetting(" component_id = "+i);
	}

	public ComponentQuery setBeginDate(LSDate date){	
		return addSetting(" begin_date = '"+date+"' ");
	}
	public ComponentQuery setEndDate(LSDate date){	
		return addSetting(" end_date = '"+date+"' ");
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
