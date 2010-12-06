package pt.isel.deetc.ls.mapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.CalendarQuery;
import pt.isel.deetc.ls.model.Calendar;

public class CalendarMapper extends Mapper<Calendar> {

	
	public CalendarMapper() {
		super();
	}

	@Override
	public boolean exists(Calendar calendar) {
		return (select(new CalendarQuery().select().where().calendarNameIs(calendar.getName()).getStatement()) != null);
	}

	@Override
	public int insert(Calendar calendar) {
		CalendarQuery a = new CalendarQuery();
		a.insertCalendar(calendar.getID(), calendar.getName());
		return (execute(a.getStatement()));
	}

	@Override
	public Iterable<Calendar> select() {
		CalendarQuery calendar = new CalendarQuery();
		calendar.select();
		return (select(calendar.getStatement()));	
	}
	
	
	private Iterable<Calendar> select(String stm) {
		ArrayList<Calendar> list = new ArrayList<Calendar>();
		ResultSet result = selectRS(stm);
		rsToal(result, list);
		return list;
	}
	
	private synchronized void rsToal(ResultSet result, ArrayList<Calendar> list) {
		try {
			while (result.next()) {
				Calendar calendar = new Calendar(result.getString(2),result.getInt(1));
				list.add(calendar);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}
	
	@Override
	public int delete(Calendar calendar) {
		throw new UnsupportedOperationException("Not supported operation.");
	}
	@Override
	public int update(Calendar calendar) {
		throw new UnsupportedOperationException("Not supported operation.");
	}

}

