package pt.isel.deetc.ls.model;

import pt.isel.deetc.ls.utils.Utils;

public class Alarm {
	private String _action;
	private LSDate _trigger;
	private LSDate _baseDate;
	private int	   _componentID;
	private int    _id;
	
	public Alarm(LSDate triggerDate, String action,int componentID){
		_trigger 	 = triggerDate;		
		_action 	 = action;
		_componentID = componentID;
		_id          = Utils.getUniqueID();
	}
	
	public Alarm(){
		_trigger 	 = null;
		_action  	 = null;
		_componentID = -1;
	}

	public String getAction() {
		return _action;
	}

	public void setAction(String action) {
		_action = action;
	}

	public LSDate getTrigger() {
		return _trigger;
	}

	public void setTrigger(LSDate trigger) {
		_trigger = trigger;
	}

	public int getComponentID() {
		return _componentID;
	}

	public void setComponentID(int componentID) {
		_componentID = componentID;
	}

	public LSDate getBaseDate() {
		return _baseDate;
	}

	public void setBaseDate(LSDate baseDate) {
		_baseDate = baseDate;
	}
	public void setAlarmId(int id){
		_id = id;
	}
	public int getAlarmId(){
		return _id;
	}
		
	

}
