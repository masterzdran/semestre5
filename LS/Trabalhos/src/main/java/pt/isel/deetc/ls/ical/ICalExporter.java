package pt.isel.deetc.ls.ical;

import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Iterator;

public class ICalExporter {
	 
	private ArrayList<VComponent> _component;
	private String _filename;
	private String _calendarName;
	
	public ICalExporter(String filename) {
		_component = new ArrayList<VComponent>();
		_filename= filename.replaceAll(" ", "")+".ics";
		//_calendarName= calendarName;
	}
	
	public void addCollection(Iterable<VComponent> component){
		Iterator<VComponent> vci = component.iterator();
		while(vci.hasNext()){
			_component.add(vci.next());
		}
	}
	
	private String icalHeader(){
		StringBuffer header = new StringBuffer();
		header.append("BEGIN:VCALENDAR\n");
		header.append("VERSION:1.0\n");
		header.append("PRODID:CalendarManager2010/2011\n");
		header.append("X-WR-CALNAME:"+_calendarName+"\n");
		return header.toString();
	}
	private String icalFooter(){
		return ("END:VCALENDAR\n");
	}
	public void export(){
		Iterator<VComponent> it = _component.iterator();
		StringBuffer buffer= new StringBuffer();
		try {
			
			VComponent vcomponent;
			while(it.hasNext()){
				vcomponent= it.next();
				if (_calendarName == null || _calendarName.trim().isEmpty()){
					System.out.println(vcomponent.getcalendarName());
					_calendarName=vcomponent.getcalendarName();
				}
				buffer.append((it.next()).export());
			}
			
			PrintStream ps = new PrintStream(_filename);
			ps.append(icalHeader());
			ps.append(buffer.toString());
			ps.append(icalFooter());
			ps.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
	}

}
