package pt.isel.deetc.ls.report;

import java.util.ArrayList;

public abstract class TracReport<T> extends Report<T> {
	// HTML Common Tags
	private final static String _beginHtmlDocument = "<html><body>";
	private final static String _endHtmlDocument = "</body></html>";
	// CommandLine Common Tags
	private final static String _beginCommandLineDocument = "##################################\n";
	private final static String _endCommandLineDocument = "##################################\n";
	// Wiki Common Tags
	private final static String _beginWikiDocument = "";
	private final static String _endWikiDocument = "";
	// HTML Table Tags
	private final static String _beginRecordsHtmlTable = "<table>";
	private final static String _endRecordsHtmlTable = "</table>";
	private final static String _beginRecordHtmlTable = "<tr>";
	private final static String _endRecordHtmlTable = "</tr>";
	private final static String _beginFieldHtmlTable = "<td>";
	private final static String _endFieldHtmlTable = "</td>";
	// HTML List Tags
	private final static String _beginRecordsHtmlList = "<ol>";
	private final static String _endRecordsHtmlList = "</ol>";
	private final static String _beginRecordHtmlList = "<ul>";
	private final static String _endRecordHtmlList = "</ul>";
	private final static String _beginFieldHtmlList = "<li>";
	private final static String _endFieldHtmlList = "</li>";
	// CommandLine Table Tags
	private final static String _beginRecordsCmdLineTable = "\n";
	private final static String _endRecordsCmdLineTable = "\n";
	private final static String _beginRecordCmdLineTable = "";
	private final static String _endRecordCmdLineTable = "\n";
	private final static String _beginFieldCmdLineTable = "|";
	private final static String _endFieldCmdLineTable = "|";
	// CommandLine List Tags
	private final static String _beginRecordsCmdLineList = "";
	private final static String _endRecordsCmdLineList = "";
	private final static String _beginRecordCmdLineList = "***";
	private final static String _endRecordCmdLineList = "\n";
	private final static String _beginFieldCmdLineList = " ---->";
	private final static String _endFieldCmdLineList = "\n";
	// Wiki Table Tags
	private final static String _beginRecordsWikiTable = "";
	private final static String _endRecordsWikiTable = "";
	private final static String _beginRecordWikiTable = "";
	private final static String _endRecordWikiTable = "";
	private final static String _beginFieldWikiTable = "";
	private final static String _endFieldWikiTable = "";
	// Wiki List Tags
	private final static String _beginRecordsWikiList = "";
	private final static String _endRecordsWikiList = "";
	private final static String _beginRecordWikiList = "";
	private final static String _endRecordWikiList = "";
	private final static String _beginFieldWikiList = "";
	private final static String _endFieldWikiList = "";

	public TracReport(ArrayList<T> list) {
		super(list);
	}

	public void setHtmlTableTags() {
		setTags(_beginHtmlDocument, _endHtmlDocument, _beginRecordsHtmlTable,
				_endRecordsHtmlTable, _beginRecordHtmlTable,
				_endRecordHtmlTable, _beginFieldHtmlTable, _endFieldHtmlTable);
	}

	public void setHtmlListTags() {
		setTags(_beginHtmlDocument, _endHtmlDocument, _beginRecordsHtmlList,
				_endRecordsHtmlList, _beginRecordHtmlList, _endRecordHtmlList,
				_beginFieldHtmlList, _endFieldHtmlList);
	}

	public void setCmdLineTableTags() {
		setTags(_beginCommandLineDocument, _endCommandLineDocument,
				_beginRecordsCmdLineTable, _endRecordsCmdLineTable,
				_beginRecordCmdLineTable, _endRecordCmdLineTable,
				_beginFieldCmdLineTable, _endFieldCmdLineTable);
	}

	public void setCmdLineListTags() {
		setTags(_beginCommandLineDocument, _endCommandLineDocument,
				_beginRecordsCmdLineList, _endRecordsCmdLineList,
				_beginRecordCmdLineList, _endRecordCmdLineList,
				_beginFieldCmdLineList, _endFieldCmdLineList);
	}

	public void setWikiTableTags() {
		setTags(_beginWikiDocument, _endWikiDocument, _beginRecordsWikiTable,
				_endRecordsWikiTable, _beginRecordWikiTable,
				_endRecordWikiTable, _beginFieldWikiTable, _endFieldWikiTable);
	}

	public void setWikiListTags() {
		setTags(_beginWikiDocument, _endWikiDocument, _beginRecordsWikiList,
				_endRecordsWikiList, _beginRecordWikiList, _endRecordWikiList,
				_beginFieldWikiList, _endFieldWikiList);
	}

}
