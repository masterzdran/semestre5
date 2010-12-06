package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;
import java.util.Iterator;

import pt.isel.deetc.ls.report.layout.ITableLayout;


public class TracTableLayout<E> extends TracFormat<E>{
	private ITableLayout<E> _layout;
	
	public TracTableLayout(ITableLayout<E> layout){
			super();
			_layout=layout;
		}
	
	public void renderFormat(PrintStream ps) {
		Iterator<String> h =_layout.getColumnName().iterator();
		Iterator<Iterable<String>> r = _layout.getValues().iterator();
		
		//Parsing the table header
		ps.print("||");
		while (h.hasNext()){
			ps.printf(" %s ||",h.next());
		}
		ps.println("");
		// parsing the table rows
		Iterator<String> it = null;
		while (r.hasNext()) {
			it= r.next().iterator();
			ps.print("||");
			while (it.hasNext()) {
				ps.printf(" %s ||", it.next());
			}
			ps.println("");
		}
	}
}
