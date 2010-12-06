package pt.isel.deetc.ls.cmd;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Todo;
import pt.isel.deetc.ls.report.TodoListLayout;
import pt.isel.deetc.ls.report.TodoTableLayout;
import pt.isel.deetc.ls.report.format.HTMLListLayout;
import pt.isel.deetc.ls.report.format.HTMLTableLayout;
import pt.isel.deetc.ls.report.format.IFormat;
import pt.isel.deetc.ls.report.format.TracListLayout;
import pt.isel.deetc.ls.report.format.TracTableLayout;
import pt.isel.deetc.ls.report.layout.ILayout;
import pt.isel.deetc.ls.report.layout.IListLayout;
import pt.isel.deetc.ls.report.layout.ITableLayout;

public class GetTodosAll extends Command {
	private static final String _NAME = "get-todos-all";
	private static final String _DESCRIPTION = "Show the information of ALL Todos";

	public GetTodosAll(String name, String description) {
		super(name, description);

		Parameter p1 = new Parameter("layout", "layout definition");
		Parameter p2 = new Parameter("format", "format definition");
		Parameter p3 = new Parameter("output-file", "output file definition");

		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		p1.addRule(ComponentRule.validValues(p1, "table","list"));
		
		p2.addRule(ComponentRule.isRequired(p2));
		p2.addRule(ComponentRule.allowNoEmpty(p2));
		p2.addRule(ComponentRule.validValues(p2, "html","wiki"));
		

		p3.addRule(ComponentRule.isOptional(p3));
		p3.addRule(ComponentRule.allowEmpty(p3));

		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
	}

	public GetTodosAll() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		TodoMapper e = new TodoMapper();
		Iterable<Todo> collection = e.select();
		report(collection);
	}
	protected void report(Iterable<Todo> collection){
		ILayout<Todo> layout 	= null;
		IFormat format 			= null;

		if (getValue("format").equals("html")){
			if (getValue("layout").equals("table")){
				layout = new TodoTableLayout(collection);
				format = new HTMLTableLayout<Todo>((ITableLayout<Todo>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new TodoListLayout(collection);
				format = new HTMLListLayout<Todo>((IListLayout<Todo>)layout);
			}
		}else if (getValue("format").equals("wiki")){
			if (getValue("layout").equals("table")){
				layout = new TodoTableLayout(collection);
				format = new TracTableLayout<Todo>((ITableLayout<Todo>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new TodoListLayout(collection);
				format = new TracListLayout<Todo>((IListLayout<Todo>)layout);
			}
		}
		
		PrintStream ps = null;
		String filename = null;
		if ((filename=getValue("output-file")) != null && !filename.trim().isEmpty()){
			try {
				ps = new PrintStream(new FileOutputStream(filename));
			} catch (FileNotFoundException e1) {
				System.err.println("Unable to create "+filename+" file.");
			}
		}else{
			ps = new PrintStream(System.out);
		}
		format.render(ps);		
	}
}
