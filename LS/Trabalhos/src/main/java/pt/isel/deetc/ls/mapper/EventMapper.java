package pt.isel.deetc.ls.mapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.EventQuery;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class EventMapper extends Mapper<Event> {
	private final String _COMPONENTNAME = "Event";
	private final int _DEFAULT_CATEGORY = 1;

	public EventMapper() {
		super();
	}

	@Override
	public int update(Event event) {
		int result = -1;
		EventQuery e = new EventQuery();
		e.updateEvent();

		// Updates to Event Table (if they exist)
		if (event.getSummary() != null)
			e.setSummary(event.getSummary());

		if (event.getLocation() != null)
			e.setLocation(event.getLocation());

		if (event.getDescription() != null)
			e.setDescription(event.getDescription());

		e.whereEventIdIs(event.getId());

		result = execute(e.getStatement());

		e.clear();
		e.updateComponent();
		if (event.getBeginDate() != null)
			e.setBeginDate(event.getBeginDate());

		if (event.getEndDate() != null)
			e.setEndDate(event.getEndDate());

		e.whereComponentIdIs(event.getId());

		result = execute(e.getStatement());
		return result;
	}

	@Override
	public int insert(Event event) {
		if (event == null)
			return 0;
		return (execute(getInsertPrepStm(event)));
	}

	@Override
	public int delete(Event event) {
		EventQuery e = new EventQuery();
		e.deleteComponentById(event.getId());
		return execute(e.getStatement());
	}

	@Override
	public Iterable<Event> select() {
		EventQuery e = new EventQuery();
		e.select();
		return (select(e.getStatement()));
	}
	
	// Method for custom EventQueries
	public Iterable<Event> select(EventQuery e){
	    return (select(e.getStatement()));
	}

	public Iterable<Event> selectBetweenDates(Event event) {
		EventQuery e = new EventQuery();
		e.select().where().beginDateBetween(event.getBeginDate(),
				event.getEndDate());
		return (select(e.getStatement()));
	}

	public Iterable<Event> selectByCal(Event event) {
		EventQuery e = new EventQuery();
		e.select().where().calendarNameIs(event.getCalName());
		return (select(e.getStatement()));
	}

	public Iterable<Event> selectByID(Event event) {
		EventQuery e = new EventQuery();
		e.select().where().componentIdIs(event.getId());
		return (select(e.getStatement()));
	}

	/*-----------------------------------------------------------------------------*/
	/*-----------------------PRIVATE---------------------------------------*/
	/*-----------------------------------------------------------------------------*/
	private Iterable<Event> select(String stm) {
		ArrayList<Event> list = new ArrayList<Event>();
		ResultSet result = selectRS(stm);
		rsToal(result, list);
		closeConnection();
		return list;
	}

	private synchronized void rsToal(ResultSet result, ArrayList<Event> list) {
		try {
			AlarmMapper alm = new AlarmMapper();
			Alarm alarm = new Alarm();
			while (result.next()) {
				Event event = new Event(
						result.getString(3), 
						new LSDate(result.getDate(4)), 
						new LSDate(result.getDate(5)), 
						result.getString(6), 
						result.getString(7), 
						result.getString(8),
						result.getInt(9));
				alarm.setComponentID(event.getId());
				Iterable<Alarm> alarmList=alm.selectByComponentID(alarm);
				if (alarmList.iterator().hasNext())
					event.addAlarmList(alarmList);
				list.add(event);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

	private String getInsertPrepStm(Event event) {
		ResultSet rs = null;
		EventQuery e = new EventQuery();

		e.selectCalendarByName(event.getCalName());

		// Query calName
		rs = selectRS(e.getStatement());
		if (rs == null)
			System.out.println("...........");
		int calendarID = 0;
		try {
			rs.next();
			calendarID = rs.getInt("id");
			rs.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}

		int componentID = event.getId();
		int categoryID = _DEFAULT_CATEGORY;
		e.clear();
		e.selectComponentTypeId(_COMPONENTNAME);
		rs = selectRS(e.getStatement());
		int componentTypeID = 0;
		try {
			rs.next();
			componentTypeID = rs.getInt("id");
			rs.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		e.clear();
		e.insertEvent(event.getId(), event.getBeginDate(), event.getEndDate(),
				componentTypeID, event.getDescription(), event.getSummary(),
				event.getLocation(), componentID, categoryID, calendarID);

		return e.getStatement();
	}

	@Override
	public boolean exists(Event event) {
		return new EventQuery().selectComponentId(event.getId()).getStatement() != null;
	}

}
