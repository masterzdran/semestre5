package pt.isel.deetc.ls.report;

import java.util.ArrayList;
import java.util.Iterator;

import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.report.layout.TableLayout;

public class AlarmTableLayout extends TableLayout<Alarm> {
	private Iterable<Alarm> _inputList;
	public AlarmTableLayout(Iterable<Alarm> collection) {
		super();
		_inputList = collection;
		setHeaders();
		setRows();
	}

	private void setHeaders(){
		ArrayList<String> header= new ArrayList<String>();
		header.add("Alarm ID");
		header.add("Trigger");
		header.add("Action");
		header.add("Component ID");
		addColumnsNames(header);
	}
	
	private void setRows(){
		Iterator<Alarm> it = _inputList.iterator();
		while(it.hasNext()){
			ArrayList<String> collection= new ArrayList<String>();
			Alarm element = it.next();
			collection.add(element.getAlarmId()+"");
			collection.add(element.getTrigger()+"");
			collection.add(element.getAction()+"");
			collection.add(element.getComponentID()+"");
			addRow(collection);			
		}
	}
}
