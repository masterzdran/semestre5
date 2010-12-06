package pt.isel.deetc.ls.cmd;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import pt.isel.deetc.ls.mapper.AlarmMapper;
import pt.isel.deetc.ls.model.Alarm;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.report.AlarmListLayout;
import pt.isel.deetc.ls.report.AlarmTableLayout;
import pt.isel.deetc.ls.report.format.HTMLListLayout;
import pt.isel.deetc.ls.report.format.HTMLTableLayout;
import pt.isel.deetc.ls.report.format.IFormat;
import pt.isel.deetc.ls.report.format.TracListLayout;
import pt.isel.deetc.ls.report.format.TracTableLayout;
import pt.isel.deetc.ls.report.layout.ILayout;
import pt.isel.deetc.ls.report.layout.IListLayout;
import pt.isel.deetc.ls.report.layout.ITableLayout;

public class GetAlarmsAll extends Command{
	private static final String _NAME = "get-alarms-all";
	private static final String _DESCRIPTION = "Show the information of ALL Alarms";

	public GetAlarmsAll(String name, String description) {
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

	public GetAlarmsAll() {
		this(_NAME, _DESCRIPTION);
	}

	@Override
	public void execute() {
		AlarmMapper al = new AlarmMapper();
		Iterable<Alarm> alarms = al.select(); 
		report(alarms);
	}
	protected void report(Iterable<Alarm> collection){
		ILayout<Alarm> layout 	= null;
		IFormat format 			= null;

		if (getValue("format").equals("html")){
			if (getValue("layout").equals("table")){
				layout = new AlarmTableLayout(collection);
				format = new HTMLTableLayout<Alarm>((ITableLayout<Alarm>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new AlarmListLayout(collection);
				format = new HTMLListLayout<Alarm>((IListLayout<Alarm>)layout);
			}
		}else if (getValue("format").equals("wiki")){
			if (getValue("layout").equals("table")){
				layout = new AlarmTableLayout(collection);
				format = new TracTableLayout<Alarm>((ITableLayout<Alarm>)layout);
			}else if (getValue("layout").equals("list")){
				layout = new AlarmListLayout(collection);
				format = new TracListLayout<Alarm>((IListLayout<Alarm>)layout);
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
