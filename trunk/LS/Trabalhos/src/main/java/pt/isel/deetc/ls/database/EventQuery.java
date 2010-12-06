package pt.isel.deetc.ls.database;

import pt.isel.deetc.ls.model.LSDate;

public class EventQuery extends ComponentQuery {
	private String _updateEventStm 	= "update Event set ";
	private String _selectStm = "select * from EVENTS";

	public EventQuery() {
		super("EVENT");
	}

	
	public EventQuery select(){
		return(EventQuery) super.select(_selectStm);
	}
	
	/* Event Related Statement */
	public EventQuery insertEvent(int id,LSDate begin_date,LSDate end_date, int componentTypeID,String description, String summary, String location, int componentID,int categoryID,int calendarID){
		
		insertComponent(componentID, begin_date, end_date, componentTypeID);
		addStatement("insert into Event (description, summary, location, componentID) values('"+description+"','"+summary+"','"+location+"',"+componentID+");");
		insertCalendarComponent(calendarID, componentID);
		insertComponentCategory(componentID, categoryID);
		
		return (EventQuery)this;
	}


	public EventQuery updateEvent(){
		return (EventQuery)updateComponent(_updateEventStm);
	}

	/*--------------------------------------------------------------------*/

	public EventQuery setDescription(String description){
		return (EventQuery) addSetting(" description = '"+description+"' ");
	}
	public EventQuery setLocation(String location){
		return (EventQuery) addSetting(" location = '"+location+"' ");
	}
	public EventQuery setSummary(String summary){
		return (EventQuery) addSetting(" summary = '"+summary+"' ");
	}
	/*--------------------------------------------------------------------*/
	public void clear(){
		super.clearStatements();
	}
	public EventQuery deleteComponentById(int componentId){
		return (EventQuery)super.deleteComponentById(componentId);	
	}

	public EventQuery descriptionIs(String description){
		return (EventQuery) addCondition(" description = '"+description+"' ");
	}
	public EventQuery locationIs(String location){
		return (EventQuery) addCondition(" location = '"+location+"' ");
	}
	public EventQuery summaryIs(String summary){
		return (EventQuery) addCondition(" summary = '"+summary+"' ");
	}
	public EventQuery  whereEventIdIs(int i){
		return (EventQuery)  addCondition("where componentID = "+i);
	}
	
}
