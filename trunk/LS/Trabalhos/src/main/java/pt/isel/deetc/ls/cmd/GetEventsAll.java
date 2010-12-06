package pt.isel.deetc.ls.cmd;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.report.EventListLayout;
import pt.isel.deetc.ls.report.EventTableLayout;
import pt.isel.deetc.ls.report.format.HTMLListLayout;
import pt.isel.deetc.ls.report.format.HTMLTableLayout;
import pt.isel.deetc.ls.report.format.IFormat;
import pt.isel.deetc.ls.report.format.TracListLayout;
import pt.isel.deetc.ls.report.format.TracTableLayout;
import pt.isel.deetc.ls.report.layout.ILayout;
import pt.isel.deetc.ls.report.layout.IListLayout;
import pt.isel.deetc.ls.report.layout.ITableLayout;

public class GetEventsAll extends Command {
	private static final String _NAME = "get-events-all";
	private static final String _DESCRIPTION = "Show the information of ALL Events";
	public GetEventsAll(String name, String description) {
		super(name, description);

		Parameter p1 = new Parameter("layout", "layout definition",true);
		Parameter p2 = new Parameter("format", "format definition",true);
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

	public GetEventsAll() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		EventMapper e = new EventMapper();
		Iterable<Event> events = e.select();
		report(events);
	}

	protected void report(Iterable<Event> collection){
		ILayout<Event> layout 	= null;
		IFormat format 			= null;

		if (getValue("format").equals("html")){
			if (getValue("layout").equals("table")){
				layout = new EventTableLayout(collection);
				format = new HTMLTableLayout<Event>((ITableLayout<Event>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new EventListLayout(collection);
				format = new HTMLListLayout<Event>((IListLayout<Event>)layout);
			}
		}else if (getValue("format").equals("wiki")){
			if (getValue("layout").equals("table")){
				layout = new EventTableLayout(collection);
				format = new TracTableLayout<Event>((ITableLayout<Event>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new EventListLayout(collection);
				format = new TracListLayout<Event>((IListLayout<Event>)layout);
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
