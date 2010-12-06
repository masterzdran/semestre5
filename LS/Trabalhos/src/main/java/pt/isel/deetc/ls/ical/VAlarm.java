package pt.isel.deetc.ls.ical;

import java.util.HashMap;
import java.util.Map;

public class VAlarm {
	
	private Map<String, String> _vAlarm;
	public VAlarm() {
		_vAlarm = new HashMap<String, String>();
		_vAlarm.put("ACTION", "");
		_vAlarm.put("TRIGGER", "");
		_vAlarm.put("DURATION", "");
		_vAlarm.put("REPEAT", "");
		_vAlarm.put("ATTACH", "");
		_vAlarm.put("X-PROP", "");
		_vAlarm.put("IANA-PROP", "");
		_vAlarm.put("DESCRIPTION", "");
		_vAlarm.put("SUMMARY", "");
		_vAlarm.put("ATTENDEE", "");
	}
	public void setAction (String action){
		setValue("ACTION", action);
	}
	public void setTrigger (String trigger){
		setValue("TRIGGER", trigger);
	}
	public void setDuration (String duration){
		setValue("DURATION", duration);
	}
	public void setRepeat (String repeat){
		setValue("REPEAT", repeat);
	}
	public void setAttach (String attach){
		setValue("ATTACH", attach);
	}
	public void setDescription (String description){
		setValue("DESCRIPTION", description);
	}
	public void setSummary (String summary){
		setValue("SUMMARY", summary);
	}
	public void setAttendee (String attendee){
		setValue("ATTENDEE", attendee);
	}
	
	public void setValue(String key, String value){
		_vAlarm.put(key, value);
	}
	
	
	public String getAction (){
		return getValue("ACTION");
	}
	public String getTrigger (){
		return getValue("TRIGGER");
	}
	public String getDuration (){
		return getValue("DURATION");
	}
	public String getRepeat (){
		return getValue("REPEAT");
	}
	public String getAttach (){
		return getValue("ATTACH");
	}
	public String getDescription (){
		return getValue("DESCRIPTION");
	}
	public String getSummary (){
		return getValue("SUMMARY");
	}
	public String getAttendee (){
		return getValue("ATTENDEE");
	}
	public String getValue(String key){
		return _vAlarm.get(key);
	}

	
	
	public String export(){
		StringBuffer string= new StringBuffer();
		string.append("BEGIN:VALARM\n");
		String tmpVal="";
		for(String key:_vAlarm.keySet()){
			tmpVal = _vAlarm.get(key);
			if (tmpVal != null && !tmpVal.trim().isEmpty()){
				string.append(key+":"+tmpVal+"\n");
			}
		}
		string.append("END:VALARM\n");
		return string.toString();
	}
	public void print(){
		System.out.println("------------- ALARM -------------");
		String tmpVal="";
		for(String key:_vAlarm.keySet()){
			tmpVal = _vAlarm.get(key);
			if (tmpVal != null && !tmpVal.trim().isEmpty()){
				System.out.println(key+"<-->"+tmpVal);
			}
		}
		System.out.println("------------ FIM ALARM -----------");

	}
}
