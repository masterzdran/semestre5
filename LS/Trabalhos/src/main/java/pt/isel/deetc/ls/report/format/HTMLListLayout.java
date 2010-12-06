package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;
import java.util.Iterator;

import pt.isel.deetc.ls.report.layout.ILayout;
import pt.isel.deetc.ls.report.layout.IListLayout;

public class HTMLListLayout<E> extends HTMLFormat<E>{
	private String  _lt;
	private ILayout<E> _layout;

	public HTMLListLayout(IListLayout<E> layout){
		this(layout,false);
	}
	public HTMLListLayout(ILayout<E> layout, boolean ordered){
		super();
		_lt  = (ordered)?"ol":"ul";
		_layout=layout;
	}
	private void parse(PrintStream ps, Iterator<String> it){
		if (it.hasNext()){
			ps.print("<li>");
			ps.printf(" %s \n",it.next());
			ps.printf("<%s>",_lt);
			while (it.hasNext()){
				ps.printf("<li> %s </li>\n",it.next());
			}
			ps.printf("</%s>\n",_lt);
			ps.println("</li>");
		}
	}
	public void renderFormat(PrintStream ps){
		Iterator<Iterable<String>> c = (_layout.getValues()).iterator();
		Iterator<String> r;
		//parsing to the list rows
		ps.printf("<%s>",_lt);
		Iterable<String> e = null;
		while (c.hasNext()){
			e = c.next();
			r = e.iterator();
			parse(ps, r);
		}
		ps.printf("</%s>\n",_lt);
	}
}
