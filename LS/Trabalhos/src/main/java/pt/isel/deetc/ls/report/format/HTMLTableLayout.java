package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;
import java.util.Iterator;

import pt.isel.deetc.ls.report.layout.ITableLayout;

public class HTMLTableLayout<E> extends HTMLFormat<E> {
	private ITableLayout<E> _layout;

	public HTMLTableLayout(ITableLayout<E> layout) {
		super();
		_layout = layout;
	}

	
	public void renderFormat(PrintStream ps) {
		
		Iterator<String> h =_layout.getColumnName().iterator();
		Iterator<Iterable<String>> r = _layout.getValues().iterator();
		
		ps.println("<table border = '1'>");
		// Parsing the table header
		ps.println("<tr>");
		while (h.hasNext()) {
			ps.printf("<th> %s </th>\n", h.next());
		}
		ps.println("</tr>");
		// parsing the table rows
		Iterator<String> it = null;
		while (r.hasNext()) {
			it= r.next().iterator();
			ps.println("<tr>");
			while (it.hasNext()) {
				ps.printf("<td> %s </td>\n", it.next());
			}
			ps.println("</tr>");
		}
		ps.println("</table>");
	}

}
