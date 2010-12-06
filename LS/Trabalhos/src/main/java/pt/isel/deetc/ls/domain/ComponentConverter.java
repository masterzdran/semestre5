package pt.isel.deetc.ls.domain;

import java.util.Iterator;
import java.util.LinkedList;

import pt.isel.deetc.ls.ical.VAlarm;
import pt.isel.deetc.ls.ical.VComponent;
import pt.isel.deetc.ls.ical.VEvent;
import pt.isel.deetc.ls.ical.VTodo;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.Component;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class ComponentConverter {
	
	public Iterable<VComponent> convertToVEvent(Iterable<Event> event){
		LinkedList<VComponent> vcomponent = new LinkedList<VComponent>();
		
		Iterator<Event> eit= event.iterator();
		
		Event evnt;
		while(eit.hasNext()){
			VEvent ve = new VEvent();
			
			evnt = eit.next();
			ve.setCalendarName(evnt.getCalName());
			ve.setDTStart(evnt.getBeginDate().toICAL());
			ve.setDescription(evnt.getDescription());
			ve.setDTSEnd(evnt.getEndDate().toICAL());
			ve.setUID(""+evnt.getId());
			ve.setLocation(evnt.getLocation());
			ve.setSummary(evnt.getSummary());
			if (evnt.hasAlarms()){
				Iterator<Alarm> aIterator = evnt.getAlarmList().iterator();
				Alarm alarm;
				while(aIterator.hasNext()){
					alarm = aIterator.next();
					VAlarm valarm = new VAlarm();
					valarm.setAction(alarm.getAction());
					valarm.setTrigger(alarm.getTrigger().toICAL());
					ve.addAlarm(valarm);
				}
			}			
			vcomponent.add(ve);
		}
		return vcomponent;
	}
	public Iterable<VComponent> convertToVTodo(Iterable<Todo> todo){
		LinkedList<VComponent> vcomponent = new LinkedList<VComponent>();
		
		Iterator<Todo> eit= todo.iterator();
		
		Todo td;
		while(eit.hasNext()){
			VTodo to = new VTodo();
			td = eit.next();
			to.setCalendarName(td.getCalName());
			to.setDTStart(td.getBeginDate().toICAL());
			to.setPercent(td.getDonePercent()+"");
			to.setDescription(td.getDescription());
			to.setExDate(td.getEndDate().toICAL());
			to.setUID(td.getId()+"");
			to.setPriority(td.getPriority()+"");
			to.setRStatus(td.getState()+"");
			to.setSummary(td.getSummary());
			if (td.hasAlarms()){
				Iterator<Alarm> aIterator = td.getAlarmList().iterator();
				Alarm alarm;
				while(aIterator.hasNext()){
					alarm = aIterator.next();
					VAlarm valarm = new VAlarm();
					valarm.setAction(alarm.getAction());
					valarm.setTrigger(alarm.getTrigger().toICAL());
					to.addAlarm(valarm);
				}
			}
			vcomponent.add(to);
		}
		return vcomponent;
	}	
	
	public Iterable<Component> convertToComponent(Iterable<VComponent> vComponents){
		LinkedList<Component> component = new LinkedList<Component>();
		
		Iterator<VComponent> vci = vComponents.iterator();
		
		while(vci.hasNext()){
			VComponent vc = vci.next();
			if (vc.getComponentType().equals("VEVENT")){
				VEvent vE = (VEvent)vc;
				Event e = castToEvent(vE);
				component.add(e);
			}else if (vc.getComponentType().equals("TODO")){
				VTodo vT = (VTodo)vc;
				Todo t = castToTodo(vT);
				component.add(t);
			}
		}
		
		return null;
	}
	
	private Event castToEvent(VEvent vEvent){
		Event event = new Event();
		event.set_calname(vEvent.getcalendarName());
		event.setBeginDate(new LSDate(vEvent.getDTStart()));
		event.setDescription(vEvent.getDescription());
		event.setEndDate(new LSDate(vEvent.getDTSEnd()));
		event.setId(Integer.parseInt(vEvent.getUID()));
		event.setLocation(vEvent.getLocation());
		event.setSummary(vEvent.getSummary());
		if (vEvent.hasAlarms()){
			Iterator<VAlarm> vaIterator = vEvent.getAlarm().iterator();
			VAlarm valarm;
			while(vaIterator.hasNext()){
				valarm = vaIterator.next();
				Alarm alarm = new Alarm();
				alarm.setAction(valarm.getAction());
				alarm.setTrigger(new LSDate(valarm.getTrigger()));
				event.addAlarm(alarm);
			}
		}
		return event;
	}
	
	private Todo castToTodo(VTodo vtodo){
		Todo todo = new Todo();
		todo.set_calname(vtodo.getcalendarName());
		todo.setBeginDate(new LSDate(vtodo.getDTStart()));
		todo.setDonePercent(Integer.parseInt(vtodo.getPercent()));
		todo.setDescription(vtodo.getDescription());
		todo.setEndDate(new LSDate(vtodo.getExDate()));
		todo.setId(Integer.parseInt(vtodo.getUID()));
		todo.setPriority(Integer.parseInt(vtodo.getPriority()));
		todo.setState(Integer.parseInt(vtodo.getRStatus()));
		todo.setSummary(vtodo.getSummary());
		if (vtodo.hasAlarms()){
			Iterator<VAlarm> vaIterator = vtodo.getAlarm().iterator();
			VAlarm valarm;
			while(vaIterator.hasNext()){
				valarm = vaIterator.next();
				Alarm alarm = new Alarm();
				alarm.setAction(valarm.getAction());
				alarm.setTrigger(new LSDate(valarm.getTrigger()));
				todo.addAlarm(alarm);
			}
		}

		return todo;
	}
	
	/*																						*/
	public Iterable<Component> convertToEvent(Iterable<VEvent> vEvent, String calendarName){
		LinkedList<Component> component = new LinkedList<Component>();
		
		Iterator<VEvent> eit= vEvent.iterator();
		
		VEvent vE;
		while(eit.hasNext()){
			Event event = new Event();
			vE = eit.next();
			event.set_calname(vE.getcalendarName());
			event.setBeginDate(new LSDate(vE.getDTStart()));
			event.setDescription(vE.getDescription());
			event.setEndDate(new LSDate(vE.getDTSEnd()));
			event.setId(Integer.parseInt(vE.getUID()));
			event.setLocation(vE.getLocation());
			event.setSummary(vE.getSummary());
			if (vE.hasAlarms()){
				Iterator<VAlarm> vaIterator = vE.getAlarm().iterator();
				VAlarm valarm;
				while(vaIterator.hasNext()){
					valarm = vaIterator.next();
					Alarm alarm = new Alarm();
					alarm.setAction(valarm.getAction());
					alarm.setTrigger(new LSDate(valarm.getTrigger()));
					event.addAlarm(alarm);
				}
			}
			component.add(event);
		}
		return component;
	}
	
	
	public Iterable<Component> convertToTodo(Iterable<VTodo> vTodo, String calendarName){
		LinkedList<Component> component = new LinkedList<Component>();
		
		Iterator<VTodo> eit= vTodo.iterator();
		
		VTodo componentType;
		while(eit.hasNext()){
			Todo todo = new Todo();
			componentType = eit.next();
			todo.set_calname(componentType.getcalendarName());
			todo.setBeginDate(new LSDate(componentType.getDTStart()));
			todo.setDonePercent(Integer.parseInt(componentType.getPercent()));
			todo.setDescription(componentType.getDescription());
			todo.setEndDate(new LSDate(componentType.getExDate()));
			todo.setId(Integer.parseInt(componentType.getUID()));
			todo.setPriority(Integer.parseInt(componentType.getPriority()));
			todo.setState(Integer.parseInt(componentType.getRStatus()));
			todo.setSummary(componentType.getSummary());
			if (componentType.hasAlarms()){
				Iterator<VAlarm> vaIterator = componentType.getAlarm().iterator();
				VAlarm valarm;
				while(vaIterator.hasNext()){
					valarm = vaIterator.next();
					Alarm alarm = new Alarm();
					alarm.setAction(valarm.getAction());
					alarm.setTrigger(new LSDate(valarm.getTrigger()));
					todo.addAlarm(alarm);
				}
			}
			component.add(todo);
		}
		return component;
	}
	
}
