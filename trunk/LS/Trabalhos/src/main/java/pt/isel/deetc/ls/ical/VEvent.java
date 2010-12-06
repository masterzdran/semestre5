package pt.isel.deetc.ls.ical;

import java.util.LinkedList;

public class VEvent extends VComponent{
	public VEvent() {
		this(new LinkedList<VAlarm>());
	}

	public VEvent(LinkedList<VAlarm> alarm){
		super("VEVENT");
		addAlarms(alarm);
		setValue("DTSTAMP", "");
		setValue("UID", "");
		setValue("DTSTART", "");
		setValue("DESCRIPTION", "");
		setValue("LOCATION", "");
		setValue("SUMMARY", "");
		setValue("DTEND", "");
		setValue("RECURID", "");
		setValue("RRULE", "");
		setValue("CLASS", "");
		setValue("CREATED", "");
		setValue("GEO", "");
		setValue("LAST_MOD", "");
		setValue("ORIGANIZER", "");
		setValue("PRIORITY", "");
		setValue("SEQ", "");
		setValue("STATUS", "");
		setValue("TRANSP", "");
		setValue("URL", "");
		setValue("X-WR-CALNAME", "");
	}

	public String getRecurID(){ return getValue("RECURID");}
	public String getRRule(){ return getValue("RRULE");}
	public String getCLass(){ return getValue("CLASS");}	
	public String getCreated(){ return getValue("CREATED");}
	public String getGEO(){ return getValue("GEO");}
	public String getLastMod(){ return getValue("LAST_MOD");}
	public String getOrganizer(){ return getValue("ORGANIZER");}
	public String getPriority(){ return getValue("PRIORITY");}
	public String getSeq(){ return getValue("SEQ");}
	public String getStatus(){ return getValue("STATUS");}
	public String getTransp(){ return getValue("TRANSP");}
	public String getURL(){ return getValue("URL");}
	
	
	public String getDTStamp(){ return getValue("DTSTAMP");}
	public String getUID(){ return getValue("UID");}
	public String getDTStart(){ return getValue("DTSTART");}
	public String getDescription(){ return getValue("DESCRIPTION");}
	public String getLocation(){ return getValue("LOCATION");}
	public String getSummary(){ return getValue("SUMMARY");}
	public String getDTSEnd(){ return getValue("DTEND");}

	public void setDTStamp(String value){ setValue("DTSTAMP",value );}
	public void setUID(String value){ setValue("UID",value );}
	public void setDTStart(String value){ setValue("DTSTART",value );}
	public void setDescription(String value){ setValue("DESCRIPTION",value );}
	public void setLocation(String value){ setValue("LOCATION",value );}
	public void setSummary(String value){ setValue("SUMMARY",value );}
	public void setDTSEnd(String value){ setValue("DTEND",value );}

	public void setRecurID(String value){ setValue("RECURID",value );}
	public void setRRule(String value){ setValue("RRULE",value );}
	public void setCLass(String value){ setValue("CLASS",value );}	
	public void setCreated(String value){ setValue("CREATED",value );}
	public void setGEO(String value){ setValue("GEO",value );}
	public void setLastMod(String value){ setValue("LAST_MOD",value );}
	public void setOrganizer(String value){ setValue("ORGANIZER",value );}
	public void setPriority(String value){ setValue("PRIORITY",value );}
	public void setSeq(String value){ setValue("SEQ",value );}
	public void setStatus(String value){ setValue("STATUS",value );}
	public void setTransp(String value){ setValue("TRANSP",value );}
	public void setURL(String value){ setValue("URL",value );}
	
	public void setCalendarName(String value){setValue("X-WR-CALNAME",value );}	
	

}
