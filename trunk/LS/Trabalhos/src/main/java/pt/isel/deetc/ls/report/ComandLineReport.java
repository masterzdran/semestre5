package pt.isel.deetc.ls.report;

import java.util.ArrayList;

public abstract class ComandLineReport<T> extends Report<T> {
	// CommandLine Common Tags
	private final static String _beginCommandLineDocument = "##################################\n";
	private final static String _endCommandLineDocument = "##################################\n";
	// CommandLine Table Tags
	private final static String _beginTableCmdLine = "\n";
	private final static String _endTableCmdLine = "\n";
	private final static String _beginRecordCmdLine = "-->|";
	private final static String _endRecordCmdLine = "|\n";
	private final static String _beginFieldCmdLine = "|";
	private final static String _endFieldCmdLine = "|";
	
	
	// CommandLine List Tags
	private final static String _beginRecordsCmdLineList = "";
	private final static String _endRecordsCmdLineList = "";
	private final static String _beginRecordCmdLineList = "***";
	private final static String _endRecordCmdLineList = "\n";
	private final static String _beginFieldCmdLineList = " ---->";
	private final static String _endFieldCmdLineList = "\n";

	public ComandLineReport(ArrayList<T> list) {
		super(list);
	}
	
	public ComandLineReport() {
		super();
		setCmdLineTableTags();
	}
	
	public void setCmdLineTableTags() {
		setTags(_beginCommandLineDocument, _endCommandLineDocument,
				_beginTableCmdLine, _endTableCmdLine,
				_beginRecordCmdLine, _endRecordCmdLine,
				_beginFieldCmdLine, _endFieldCmdLine);
	}
	public void setCmdLineListTags() {
		setTags(_beginCommandLineDocument, _endCommandLineDocument,
				_beginRecordsCmdLineList, _endRecordsCmdLineList,
				_beginRecordCmdLineList, _endRecordCmdLineList,
				_beginFieldCmdLineList, _endFieldCmdLineList);
	}
}
