package pt.isel.deetc.ls.report.layout;

import java.util.ArrayList;
import java.util.Iterator;

public abstract class ListLayout<E> implements IListLayout<E>{
	private ArrayList<Iterable<String>> 	_lines;
	
	
	public ListLayout() {
		_lines		= new ArrayList<Iterable<String>>();
	}
	public void addRow(Iterable<String> columnValues){
		ArrayList<String> line = new ArrayList<String>();
		Iterator<String> it = columnValues.iterator();
		while(it.hasNext()){
			line.add(it.next());
		}
		_lines.add(line);
	}
	
	@Override
	public Iterable<Iterable<String>> getValues() {
		return _lines;
	}
	

}
