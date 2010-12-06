package pt.isel.deetc.ls.ical;

import java.util.LinkedList;


public class VCalendar {
	private LinkedList<VComponent> _components;
	public VCalendar() {
		_components = new LinkedList<VComponent>();
		VEvent  e = new VEvent();
		VTodo t = new VTodo();
		_components.add(e);
		_components.add(t);

	}

}
