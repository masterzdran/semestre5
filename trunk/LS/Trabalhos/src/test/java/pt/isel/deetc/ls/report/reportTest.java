package pt.isel.deetc.ls.report;

import java.io.PrintStream;
import java.util.ArrayList;

import org.junit.Test;

import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;
import pt.isel.deetc.ls.report.format.HTMLFormat;
import pt.isel.deetc.ls.report.format.HTMLListLayout;
import pt.isel.deetc.ls.report.format.HTMLTableLayout;
import pt.isel.deetc.ls.report.format.TracFormat;
import pt.isel.deetc.ls.report.format.TracListLayout;
import pt.isel.deetc.ls.report.format.TracTableLayout;
import pt.isel.deetc.ls.report.layout.ListLayout;
import pt.isel.deetc.ls.report.layout.TableLayout;

public class reportTest {

	@Test
	public void testreportinHTML() {
		ArrayList<Todo> collection = new ArrayList<Todo>();
		collection.add(new Todo("xpt0", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt1", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt2", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt3", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt4", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt5", new LSDate(), new LSDate()));
		collection.add(new Todo("xpt6", new LSDate(), new LSDate()));

		TableLayout<Todo> Tlayout = new TodoTableLayout(collection);
		ListLayout<Todo> Llayout = new TodoListLayout(collection);

		HTMLFormat<Todo> HTformat = new HTMLTableLayout<Todo>(Tlayout);
		HTMLFormat<Todo> HLformat = new HTMLListLayout<Todo>(Llayout);
		HTMLFormat<Todo> HLOformat = new HTMLListLayout<Todo>(Llayout, true);
		TracFormat<Todo> TTformat = new TracTableLayout<Todo>(Tlayout);
		TracFormat<Todo> TLformat = new TracListLayout<Todo>(Llayout);
		TracFormat<Todo> TLOformat = new TracListLayout<Todo>(Llayout,true);

		
		PrintStream ps = new PrintStream(System.out);
		HTformat.render(ps);
		HLformat.render(ps);
		HLOformat.render(ps);
		TTformat.render(ps);
		TLformat.render(ps);
		TLOformat.render(ps);

	}
}
