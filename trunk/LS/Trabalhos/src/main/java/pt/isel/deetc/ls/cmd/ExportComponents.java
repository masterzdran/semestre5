package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.domain.ComponentConverter;
import pt.isel.deetc.ls.ical.ICalExporter;
import pt.isel.deetc.ls.ical.VComponent;
import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.Todo;

public class ExportComponents extends Command {
	private static final String _NAME = "export";
	private static final String _DESCRIPTION = "Export information from ONE Calendar to ICAL format";
	public ExportComponents(String name, String description) {
		super(name, description);

		Parameter p1 = new Parameter("cal-name", "name of the calendar",true);
		Parameter p2 = new Parameter("output-file", "output file definition");

		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		
		p2.addRule(ComponentRule.isRequired(p2));
		p2.addRule(ComponentRule.allowNoEmpty(p2));

		addParameter(p1);
		addParameter(p2);

	}

	public ExportComponents() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		EventMapper e = new EventMapper();
		Event event = new Event();
		event.set_calname(getValue("cal-name"));
		Iterable<Event> events = e.selectByCal(event);
		
		TodoMapper t = new TodoMapper();
		Todo todo = new Todo();
		todo.set_calname(getValue("cal-name"));
		Iterable<Todo> todos = t.selectByCal(todo);
		
		ComponentConverter cc = new ComponentConverter();
		
		Iterable<VComponent> vcc = cc.convertToVEvent(events);
		Iterable<VComponent> vcc2 = cc.convertToVTodo(todos);
	
		
		ICalExporter ice = new ICalExporter(getValue("output-file"));
		ice.addCollection(vcc);
		ice.addCollection(vcc2);
		ice.export();
		

	}
}
