/**
 * 
 */
package pt.isel.deetc.ls.database;

import pt.isel.deetc.ls.model.LSDate;

public class TodoQuery extends ComponentQuery {

    private String _updateTodoStm = "update Todo set";
    private String _selectStm = "select * from TODOS";
    
    public TodoQuery() {
	super("TODO");
    }
    
    
	public TodoQuery select(){
		return(TodoQuery) super.select(_selectStm);
	}
    
    /* Todo Related Statement */
    public TodoQuery insertTodo( 
	    int id, 
	    LSDate begin_date, 
	    LSDate end_date, 
	    int componentTypeID, 
	    String description, 
	    String summary, 
	    int state,
	    double donepercent, 
	    int priority, 
	    int componentID,
	    int categoryID,
	    int calendarID )
    {
	insertComponent(componentID, begin_date, end_date, componentTypeID);
	addStatement("insert into Todo (description, summary, status, donepercent, priority, componentID) values('"
				+description+"','"+summary+"','"+state+"',"+donepercent+","+priority+","+componentID+");");
	insertCalendarComponent(calendarID, componentID);
	insertComponentCategory(componentID, categoryID);
	
	return (TodoQuery) this;
    }

    public void clear() { super.clearStatements(); }
    
    public TodoQuery updateTodo() { return (TodoQuery) updateComponent(_updateTodoStm); }
    
    public TodoQuery deleteComponentById(int componentId){ return (TodoQuery)super.deleteComponentById(componentId); }
    
    /* (Fluent Language Model) - SET Statements */
    
    public TodoQuery setTodoId(int i) { return (TodoQuery) addSetting(" id = "+i); }
    
    public TodoQuery setBeginDate(LSDate date) { return (TodoQuery) addSetting( " begin_date = "+date+" "); }
    
    public TodoQuery setEndDate(LSDate date) { return (TodoQuery) addSetting( " end_date = "+date+" "); }
    
    public TodoQuery setDescription(String description){ return (TodoQuery) addSetting(" description = '"+description+"' ");}
    
    public TodoQuery setSummary(String summary){ return (TodoQuery) addSetting(" summary = '"+summary+"' ");}

    public TodoQuery setState(int state){ return (TodoQuery) addSetting(" status = '"+state+"' ");}

    public TodoQuery setDonePercent(double donepercent){ return (TodoQuery) addSetting(" donepercent = '"+donepercent+"' ");}
    
    public TodoQuery setPriority(int priority){ return (TodoQuery) addSetting(" priority = '"+priority+"' ");}

    /* (Fluent Language Model) - SEARCH Statements */
    
    public TodoQuery whereTodoIdIs(int i) { return (TodoQuery) addCondition("where componentId = "+i); }	
    
    public TodoQuery donePercentIs(double donepercent) { return (TodoQuery) addCondition(" donepercent = "+donepercent+" "); }
    
    public TodoQuery priorityIs(int priority) { return (TodoQuery) addCondition(" priority = "+priority+" "); }
    
    public TodoQuery stateIs(int state) { return (TodoQuery) addCondition(" status = "+state+" "); } 
    
}
