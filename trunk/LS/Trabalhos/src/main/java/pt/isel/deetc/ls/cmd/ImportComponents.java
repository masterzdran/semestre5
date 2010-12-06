package pt.isel.deetc.ls.cmd;

import java.util.Iterator;

import pt.isel.deetc.ls.domain.ComponentConverter;
import pt.isel.deetc.ls.ical.ICalImporter;
import pt.isel.deetc.ls.ical.VComponent;
import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.Component;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.Todo;

public class ImportComponents extends Command {
	private static final String _NAME = "import";
	private static final String _DESCRIPTION = "Import information from ONE Calendar in ICAL format";
	public ImportComponents(String name, String description) {
		super(name, description);

		Parameter p1 = new Parameter("input-file", "input file definition");

		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);

	}

	public ImportComponents() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		ICalImporter ici = new ICalImporter(getValue("input-file"));
		Iterable<VComponent> vci = ici.iCalBuilder();

		ComponentConverter cc = new ComponentConverter();

		Iterable<Component> components = cc.convertToComponent(vci);
		EventMapper em = new EventMapper();
		TodoMapper tm= new TodoMapper();
		
		Iterator<Component> itr = components.iterator();
		
		while(itr.hasNext()){
			Component component = itr.next();
			if (component.getComponentType().equals("EVENT")){
				em.insert((Event)component);
			}else if (component.getComponentType().equals("TODO")){
				tm.insert((Todo)component);
			}
		}
	}
}
