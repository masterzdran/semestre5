package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;
import java.util.Iterator;

import pt.isel.deetc.ls.report.layout.ILayout;
import pt.isel.deetc.ls.report.layout.IListLayout;


public class TracListLayout<E> extends TracFormat<E>{
	private String  _lt;
	private ILayout<E> _layout;
	
	public TracListLayout(IListLayout<E> layout){
		this(layout, false);
	}
	public TracListLayout(IListLayout<E> layout, boolean ordered){
		super();
		_lt  = (ordered)?" i. ":" *";
		_layout=layout;
	}
	private void parse(PrintStream ps, Iterator<String> it){
		if (it.hasNext()){
			ps.printf("%s %s\n",_lt,it.next());
			while (it.hasNext()){
				ps.printf("  %s %s\n",_lt,it.next());
			}
		}
	}
	public void renderFormat(PrintStream ps){
		Iterator<Iterable<String>> c = (_layout.getValues()).iterator();
		Iterator<String> r;
		//parsing to the list rows
		Iterable<String> e = null;
		while (c.hasNext()){
			e = c.next();
			r = e.iterator();
			parse(ps, r);
		}
	}
}
