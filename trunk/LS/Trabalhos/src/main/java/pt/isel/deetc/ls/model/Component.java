package pt.isel.deetc.ls.model;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.utils.Utils;

abstract public class Component {
	private int _id;
	private LSDate _beginDate;
	private LSDate _endDate;
	private String _calname;
	private ArrayList<Alarm> _alarmList;
	private String _componentType;
	
	public Component(){
		_calname = "";
		_beginDate = null;
		_endDate = null;
		_id = -1;
		_alarmList = new ArrayList<Alarm>();		
	}

	public Component(String calname, LSDate beginDate, LSDate endDate) {
		_calname = calname;
		_beginDate = beginDate;
		_endDate = endDate;
		_id = Utils.getUniqueID();
		_alarmList = new ArrayList<Alarm>();
	}

	public LSDate getBeginDate() {
		return _beginDate;
	}

	public void setBeginDate(LSDate beginDate) {
		this._beginDate = beginDate;
	}

	public LSDate getEndDate() {
		return _endDate;
	}

	public void setEndDate(LSDate endDate) {
		this._endDate = endDate;
	}

	public int getId() {
		return _id;
	}

	public void setId(int id) {
		this._id = id;
	}

	public String getCalName() {
		return _calname;
	}

	public void set_calname(String calname) {
		this._calname = calname;
	}

	public Iterable<Alarm> getAlarmList() {
		return _alarmList;
	}

	public void addAlarm(Alarm alarm) {
		_alarmList.add(alarm);
	}
	
	public void addAlarmList(Iterable<Alarm> alarm) {
		Alarm a ;
		Iterator<Alarm> ai = alarm.iterator();
		while(ai.hasNext()){
			a = ai.next();
			_alarmList.add(a);
		}
	}
	public boolean hasAlarms(){
		return _alarmList.iterator().hasNext();
	}
	
	public String getComponentType(){
		return _componentType;
	}
	public void setComponetType(String componenttype){
		_componentType= componenttype;
	}
}