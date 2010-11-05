package pt.isel.deetc.ls.cmd;

import java.io.File;
import java.util.ArrayList;

import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.output.EventOutput;

public class GetTodosAll extends Command {
	private static final String _NAME = "get-events-all";
	private static final String _DESCRIPTION = "Show the information of ALL Events";
	private ArrayList<Event> _list;
	EventOutput _eOutput;

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

		// _report= new HashMap<String, Report<Event>>();
		// _report.put("commandline", new EventCLReport());
		_list = new ArrayList<Event>();
		// _eOutput = new EventOutput(_list);
	}

	public GetTodosAll() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		EventMapper e = new EventMapper();
		setList(e.select());
		sR();

	}

	public void setList(ArrayList<Event> l) {
		_list = l;
	}

	public void sR() {
		// _report.get("commandline").show(_list);
		_eOutput = new EventOutput(_list);
		if (getValue("layout").equals("table") && getValue("format").equals("html")) _eOutput.showAsHtmlTable();
		if (getValue("layout").equals("list") && getValue("format").equals("html")) _eOutput.showAsHtmlList();
		if (getValue("layout").equals("table") && getValue("format").equals("wiki")) _eOutput.showAsWikiTable();
		if (getValue("layout").equals("list") && getValue("format").equals("wiki")) _eOutput.showAsWikiList();
		_eOutput.buildDocument();
		if (getValue("output-file") != null && !getValue("output-file").trim().isEmpty()) _eOutput.writeToFile(new File(getValue("output-file")));
		System.out.println(_eOutput.getDocument());
	}
}
