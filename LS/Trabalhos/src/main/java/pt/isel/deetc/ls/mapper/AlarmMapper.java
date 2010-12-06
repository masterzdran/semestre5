package pt.isel.deetc.ls.mapper;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.AlarmQuery;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.LSDate;

public class AlarmMapper extends Mapper<Alarm> {
	public AlarmMapper() {
		super();
	}
	public Iterable<Alarm> selectBetweenDates(Alarm triggerBegin,Alarm triggerEnd) {
		AlarmQuery alarm = new AlarmQuery();
		alarm.select().where().triggerteBetween(triggerBegin.getTrigger(),triggerEnd.getTrigger());
		return (select(alarm.getStatement()));	
	}

	public Iterable<Alarm> selectByAlarmID(Alarm alarm) {
		AlarmQuery a = new AlarmQuery();
		a.selectAlarmById(alarm.getAlarmId());
		return (select(a.getStatement()));	
	}
	public Iterable<Alarm> selectByComponentID(Alarm alarm) {
		AlarmQuery a = new AlarmQuery();
		a.selectAlarmByComponentID(alarm.getComponentID());
		return (select(a.getStatement()));	
	}
	@Override
	public Iterable<Alarm> select() {
		AlarmQuery alarm = new AlarmQuery();
		alarm.select();
		return (select(alarm.getStatement()));	
	}
	
	
	@Override
	public int insert(Alarm alarm){
		AlarmQuery a = new AlarmQuery();
		a.insertAlarm(alarm.getAlarmId(), alarm.getTrigger(), alarm.getAction(), alarm.getComponentID());
		return (execute(a.getStatement()));
	}
	@Override
	public int update(Alarm tObject) {
		AlarmQuery a = new AlarmQuery();
		a.updateAlarm();
		if (tObject.getTrigger() != null)
			a.setTrigger(tObject.getTrigger());
		if (tObject.getAction() != null)
			a.setanaction(tObject.getAction());
		if (tObject.getComponentID() != 0)
			a.setComponentId(tObject.getComponentID());
		
		a.where().alarmIdIs(tObject.getAlarmId());
		return (execute(a.getStatement()));
	}
	@Override
	public int delete(Alarm tObject) {
		AlarmQuery alarm = new AlarmQuery();
		alarm.deleteAlarmById(tObject.getAlarmId());
		return execute(alarm.getStatement());
	}
	private Iterable<Alarm> select(String stm) {
		ArrayList<Alarm> list = new ArrayList<Alarm>();
		ResultSet result = selectRS(stm);
		rsToal(result, list);
		return list;
	}
	private synchronized void rsToal(ResultSet result, ArrayList<Alarm> list) {
		try {
			while (result.next()) {
				Alarm alarm = new Alarm();
				alarm.setAlarmId(result.getInt(0));
				alarm.setTrigger(new LSDate(result.getDate(1)));
				alarm.setAction(result.getString(2));
				alarm.setComponentID(result.getInt(3));
				
				list.add(alarm);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}
	@Override
	public boolean exists(Alarm alarme) {
		return (select(new AlarmQuery().selectAlarmById(alarme.getAlarmId()).getStatement()) != null);
	}
}
