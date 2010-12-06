package pt.isel.deetc.ls.ical;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;

public abstract class VComponent {
	private Map<String, String> _vComponent;
	private LinkedList<VAlarm> _alarm;
	private String	_componentType;
	
	public VComponent(String componentType) {
		this(new LinkedList<VAlarm>(),componentType);
	}

	public VComponent(LinkedList<VAlarm> alarm,String componentType) {
		_alarm = alarm;
		_componentType = componentType;
		_vComponent = new HashMap<String, String>();
	}
	public String getcalendarName(){
		return _vComponent.get("X-WR-CALNAME");
	}
	public void addAlarms(LinkedList<VAlarm> alarms){
		_alarm.addAll(alarms);
	}
	public void setValue(String key, String value){
		_vComponent.put(key, value);
	}
	public String getValue(String key){
		return _vComponent.get(key);
	}
	
	public void addAlarm(VAlarm alarm){
		_alarm.add(alarm);
	}

	public Iterable<VAlarm> getAlarm(){
		return _alarm;
	}

	public String getComponentType(){
		return _componentType;
	}
	public boolean hasAlarms(){
		return _alarm.iterator().hasNext();
	}
	public String export(){
		StringBuffer string= new StringBuffer();
		string.append("BEGIN:"+_componentType+"\n");
		String tmpVal="";
		for(String key:_vComponent.keySet()){
			tmpVal = _vComponent.get(key);
			if (tmpVal != null && !tmpVal.trim().isEmpty() && key.compareToIgnoreCase("X-WR-CALNAME")!= 0){
				string.append(key+":"+tmpVal+"\n");
			}
		}
		Iterator<VAlarm> iterator = _alarm.iterator();
		VAlarm alarm;
		while ( iterator.hasNext()){
			alarm = iterator.next();
			string.append(alarm.export());
		}
		string.append("END:"+_componentType+"\n");
		return string.toString();
	}
	
	public void print(){
		System.out.println("------------- "+getComponentType()+" -------------");
		String tmpVal="";
		for(String key:_vComponent.keySet()){
			tmpVal = _vComponent.get(key);
			if (tmpVal != null && !tmpVal.trim().isEmpty()){
				System.out.println(key+"<:>"+tmpVal);
			}
		}
		Iterator<VAlarm> iterator = _alarm.iterator();
		VAlarm alarm;
		while ( iterator.hasNext()){
			alarm = iterator.next();
			alarm.print();
		}
		System.out.println("------------- FIM "+getComponentType()+" -------------");
	}
}
