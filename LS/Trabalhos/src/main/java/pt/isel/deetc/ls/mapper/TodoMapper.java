package pt.isel.deetc.ls.mapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.TodoQuery;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class TodoMapper extends Mapper<Todo> {
	private final String _COMPONENTNAME = "Todo";
	private final int _DEFAULT_CATEGORY = 2;
	
	public TodoMapper() {
		super();
	}
	
	@Override
	public int update(Todo todo) {
	    int result = -1;
	    TodoQuery t = new TodoQuery();
	    	    
	    // Updates to Todo Table (if they exist)
	    t.updateTodo();
	    
	    if ( todo.getSummary() != null ) t.setSummary(todo.getSummary());
	    
	    if ( todo.getDescription() != null ) t.setDescription(todo.getDescription());
	    
	    if ( todo.getState() != 0 ) t.setState(todo.getState());
	    
	    if ( todo.getDonePercent() != 0.0 ) t.setDonePercent(todo.getDonePercent());
	    
	    if ( todo.getPriority() != 0 ) t.setPriority(todo.getPriority());
	    
	    t.whereTodoIdIs(todo.getId());
	    
	    result = execute(t.getStatement());
	    
	    t.clear();
	    
	    /* Updates to Component Table (if they exist) */
	    t.updateComponent();
	    
	    if ( todo.getBeginDate() != null ) t.setBeginDate(todo.getBeginDate());
	    
	    if( todo.getEndDate() != null ) t.setEndDate(todo.getEndDate());
	    
	    t.whereComponentIdIs(todo.getId());
	    
	    result = execute(t.getStatement());
	    
		return result;
	}
	
	@Override
	public int delete(Todo todo) {
	    	TodoQuery t = new TodoQuery();
	    	t.deleteComponentById(todo.getId());
		return execute(t.getStatement());
	}

	@Override
	public int insert(Todo todo) {
	    if ( todo == null ) return 0;
		return (execute(getInsertPrepStm(todo)));
	}

	@Override
	public ArrayList<Todo> select() {
	    	TodoQuery t = new TodoQuery();
	    	t.select();
		return (select(t.getStatement()));
	}
	
	// Method for custom TodoQueries
	public Iterable<Todo> select(TodoQuery t){
	    return (select(t.getStatement()));
	}
	
	public ArrayList<Todo> selectBetweenDates(Todo todo) {
	    TodoQuery t = new TodoQuery();
	    t.select().where().beginDateBetween(todo.getBeginDate(), todo.getEndDate());
		return (select(t.getStatement()));
	}

	public ArrayList<Todo> selectByCal(Todo todo) {
	    	TodoQuery t = new TodoQuery();
	    	t.select().where().whereComponentIdIs(todo.getId());
		return (select(t.getStatement()));
	}

	public ArrayList<Todo> selectByID(Todo todo) {
	    TodoQuery t = new TodoQuery();
	    t.select().where().componentIdIs(todo.getId());
	    return (select(t.getStatement()));
	}
	
	/*-------------------------------------------- Private methods -----------------------------------------------------------*/
	
	private ArrayList<Todo> select(String stm) {
	    	ArrayList<Todo> list = new ArrayList<Todo>();
	    	ResultSet result = selectRS(stm);
	    	rsToal(result,list);
		return list;
	}
	
	private synchronized void rsToal(ResultSet result, ArrayList<Todo> list) {
		try {
			AlarmMapper alm = new AlarmMapper();
			Alarm alarm = new Alarm();
			while (result.next()) {
				Todo todo = new Todo(result.getString(3),
					new LSDate(result.getDate(4)), 
					new LSDate(result.getDate(5)),
					result.getString(6),
					result.getString(7),
					result.getInt(8),
					result.getDouble(9),
					result.getInt(10)
				); 
				todo.setId(result.getInt(9));
				alarm.setComponentID(todo.getId());
				Iterable<Alarm> alarmList=alm.selectByComponentID(alarm);
				if (alarmList.iterator().hasNext())
					todo.addAlarmList(alarmList);
				list.add(todo);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

	private String getInsertPrepStm(Todo todo) {
	    ResultSet rs = null;
	    TodoQuery t = new TodoQuery();
	    
	    t.selectCalendarByName(todo.getCalName());
	    
	    // Query calendarID
	    rs = selectRS(t.getStatement());
	    if ( rs == null ) System.out.println("....................");
	    int calendarID = 0;
	    try {
		rs.next();
		calendarID = rs.getInt("id");
		rs.clearWarnings();
	    } catch( SQLException e) {
		e.printStackTrace();
	    }
	    
	    int componentID = todo.getId();
	    int categoryID = _DEFAULT_CATEGORY;
	    
	    t.clear();
	    t.selectComponentTypeId(_COMPONENTNAME);
	    rs = selectRS(t.getStatement());
	    
	    // Query componentTypeID
	    int componentTypeID = 0;
	    try {
		rs.next();
		componentTypeID = rs.getInt("id");
		rs.close();
	    } catch (SQLException e) {
		e.printStackTrace();
	    }    
	    t.clear();
	    t.insertTodo(todo.getId(), todo.getBeginDate(), todo.getEndDate(), componentTypeID, todo.getDescription(),
		    todo.getSummary(), todo.getState(), todo.getDonePercent(), todo.getPriority(), componentID, categoryID, calendarID);
		return t.getStatement();
	}
	
	@Override
	public boolean exists(Todo todo) {
		throw new UnsupportedOperationException("Not supported yet.");
	}
}
