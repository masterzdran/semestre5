package pt.isel.deetc.ls.report.layout;

import java.util.ArrayList;
import java.util.Iterator;

public abstract class TableLayout<E> implements ITableLayout<E>{
	private ArrayList<String> 			_headers;
	private ArrayList<Iterable<String>> 	_lines;
	
	
	public TableLayout() {
		_headers 	= new ArrayList<String>();
		_lines		= new ArrayList<Iterable<String>>();
	}

	protected void addColumnsNames(Iterable<String> columnName){
		_headers.clear();
		Iterator<String> it = columnName.iterator();
		while(it.hasNext()){
			_headers.add(it.next());
		}
	}
	
	protected void addRow(Iterable<String> columnValues){
		ArrayList<String> line = new ArrayList<String>();
		Iterator<String> it = columnValues.iterator();
		while(it.hasNext()){
			line.add(it.next());
		}
		_lines.add(line);
	}
	
	@Override
	public Iterable<String> getColumnName() {
		return _headers;
	}

	@Override
	public Iterable<Iterable<String>> getValues() {
		return _lines;
	}
	

}
