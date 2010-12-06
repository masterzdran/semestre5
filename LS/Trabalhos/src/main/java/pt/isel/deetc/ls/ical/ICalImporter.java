package pt.isel.deetc.ls.ical;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Iterator;
import java.util.LinkedList;

import pt.isel.deetc.ls.model.LSDate;
//TODO: Entender a ordem pela qual se vai buscar os ficheiro as Resources
public class ICalImporter {
	private String _filaname;
	private String _calendarName;

	public ICalImporter(String filename) {
		_filaname = filename;
	}
	
	public Iterable<VComponent> iCalBuilder() {
		LinkedList<VComponent> components = new LinkedList<VComponent>();

		BufferedReader fileInput;
		try {
			fileInput = new BufferedReader(new InputStreamReader(this
					.getClass().getResourceAsStream(_filaname)));
			String line;
			String property = "NOME";
			String field = "VALOR";
			int idx = -1;
			VComponent tmp;
			while ((line = fileInput.readLine()) != null) {
				idx = line.indexOf(':');

				if (idx > -1) {
					property = line.substring(0, idx);
					field = line.substring(idx + 1);

					if (property.equalsIgnoreCase("BEGIN")) {
						if (field.equalsIgnoreCase("VCALENDAR")) {
							processCalendarHeader(fileInput);
						} else if (field.equalsIgnoreCase("VEVENT")) {
							VEvent event = new VEvent();
							if ((tmp = populate(fileInput,event)) != null){
								components.add(tmp);
							}
						} else if (field.equalsIgnoreCase("VTODO")) {
							VTodo todo = new VTodo();

							if ((tmp = populate(fileInput,todo)) != null){
								components.add(tmp);
							}
						}
					}
				}
			}

			fileInput.close();
		} catch (Exception e) {
			System.err.println(e.getLocalizedMessage());
		}
		

		return components;
	}

	public void print(Iterable<VComponent> collection) { 
		Iterator<VComponent> compItera = collection.iterator();
		while(compItera.hasNext()){
			compItera.next().print();
		}	
	}

	private void processCalendarHeader(BufferedReader fileInput) throws IOException {
		String line = "";
		int idx;
		String property = "";
		String field = "";

		while ((line = fileInput.readLine()) != null) {
			idx = line.indexOf(':');
			if (idx > -1) {
				property = line.substring(0, idx);
				field = line.substring(idx + 1);
				if (property.equalsIgnoreCase("END") || (property.equalsIgnoreCase("BEGIN"))){
					if (_calendarName == null || _calendarName.trim().isEmpty() ){
						_calendarName= _filaname;
						fileInput.reset();
						return;
						
					}
				}else if((property.equalsIgnoreCase("X-WR-CALNAME"))){
					_calendarName= field;
					
					return;
				}
			}
			fileInput.mark(100);
		}
		return ;
	}
	
	private VAlarm populateAlarm(BufferedReader fileInput) throws IOException {
		VAlarm alarm = new VAlarm();
		String line = "";
		int idx;
		String property = "";
		String field = "";

		while ((line = fileInput.readLine()) != null) {
			idx = line.indexOf(':');
			if (idx > -1) {
				property = line.substring(0, idx);
				field = line.substring(idx + 1);
				if (property.equalsIgnoreCase("END")
						&& field.equalsIgnoreCase("VALARM")) {
					return alarm;
				}
				alarm.setValue(property, field);
			}
		}
		return null;
	}

	private VComponent populate(BufferedReader fileInput,VComponent component) throws IOException {
		String line = "";
		int idx;
		String property = "";
		String field = "";
		VAlarm tmp;
		component.setValue("CALENDAR_NAME", _calendarName);
		while ((line = fileInput.readLine()) != null) {
			idx = line.indexOf(':');
			if (idx > -1) {
				property = line.substring(0, idx);
				field = line.substring(idx + 1);
				if (property.equalsIgnoreCase("END")
						&& field.equalsIgnoreCase(component.getComponentType())) {
					return component;
				} else if (property.equalsIgnoreCase("BEGIN")
						&& field.equalsIgnoreCase("VALARM")) {
					if ((tmp = populateAlarm(fileInput))!= null)
						component.addAlarm(tmp);
				}else{
					if (property.startsWith("DT")){
						int idx2 = line.indexOf(';');
						if (idx2>-1 && idx2<idx ){
							int idx3= line.indexOf('=');
							String timezone = line.substring(idx3+1, idx);
							property = line.substring(0, idx2);
							LSDate x = new LSDate(field,timezone);
							field=x.toString();
						}else{
							int idx3= line.indexOf('=');
							String timezone = line.substring(idx3+1, idx);
							LSDate x = new LSDate(field,timezone);
							field=x.toString();							
						}
					}
					component.setValue(property, field);
				}
			}
		}
		return null;
	}

}
