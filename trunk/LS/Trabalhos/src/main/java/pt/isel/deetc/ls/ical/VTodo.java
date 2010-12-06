package pt.isel.deetc.ls.ical;

import java.util.LinkedList;

public class VTodo extends VComponent{
	public VTodo(){
		this(new LinkedList<VAlarm>());
	}
	public VTodo(LinkedList<VAlarm> alarm) {
		super(alarm,"VTODO");
		addAlarms(alarm);
		setValue("DTSTAMP", "");
		setValue("UID", "");
		setValue("CLASS", "");
		setValue("COMPLETED", "");
		setValue("CREATED", "");
		setValue("DESCRIPTION", "");
		setValue("DTSTART", "");
		setValue("GEO", "");
		setValue("LAST-MOD", "");
		setValue("LOCATION", "");
		setValue("ORGANIZER", "");
		setValue("PERCENT", "");
		setValue("PRIORITY", "");
		setValue("RECURID", "");
		setValue("SEQ", "");
		setValue("STATUS", "");
		setValue("SUMMARY", "");
		setValue("URL", "");
		setValue("RRULE", "");
		setValue("DUE", "");
		setValue("ATTACH", "");
		setValue("ATTENDEE", "");
		setValue("CATEGORIES", "");
		setValue("COMMENT", "");
		setValue("CONTACT", "");
		setValue("EXDATE", "");
		setValue("RSTATUS", "");
		setValue("RELATED", "");
		setValue("RESOURCES", "");
		setValue("RDATE", "");
		setValue("X-PROP", "");
		setValue("IANA-PROP", "");
		setValue("X-WR-CALNAME", "");
	}
	
	public void setDTStamp(String value){ setValue("DTSTAMP", value);}
	public void setUID(String value){ setValue("UID", value);}	
	public void setClass(String value){ setValue("CLASS", value);}
	public void setCompleted(String value){ setValue("COMPLETED", value);}
	public void setCreated(String value){ setValue("CREATED", value);}
	public void setDescription(String value){ setValue("DESCRIPTION", value);}
	public void setDTStart(String value){ setValue("DTSTART", value);}
	public void setGEO(String value){ setValue("GEO", value);}
	public void setLastMod(String value){ setValue("LAST-MOD", value);}
	public void setLocation(String value){ setValue("LOCATION", value);}
	public void setOrganizer(String value){ setValue("ORGANIZER", value);}
	public void setPercent(String value){ setValue("PERCENT", value);}
	public void setPriority(String value){ setValue("PRIORITY", value);}
	public void setRecurID(String value){ setValue("RECURID", value);}	
	public void setSeq(String value){ setValue("SEQ", value);}
	public void setSummary(String value){ setValue("SUMMARY", value);}
	public void setURL(String value){ setValue("URL", value);}
	public void setRRule(String value){ setValue("RRULE", value);}
	public void setDue(String value){ setValue("DUE", value);}
	public void setATTACH(String value){ setValue("ATTACH", value);}
	public void setAttendee(String value){ setValue("ATTENDEE", value);}
	public void setCategories(String value){ setValue("CATEGORIES", value);}
	public void setComment(String value){ setValue("COMMENT", value);}
	public void setContact(String value){ setValue("CONTACT", value);}
	public void setExDate(String value){ setValue("EXDATE", value);}
	public void setRStatus(String value){ setValue("RSTATUS", value);}	
	public void setRelated(String value){ setValue("RELATED", value);}
	public void setResources(String value){ setValue("RESOURCES", value);}
	public void setRDate(String value){ setValue("RDATE", value);}


	public String getDTStamp(){ return getValue("DTSTAMP");}
	public String getUID(){ return getValue("UID");}	
	public String getCLass(){ return getValue("CLASS");}
	public String getCompleted(){ return getValue("COMPLETED");}
	public String getCreated(){ return getValue("CREATED");}
	public String getDescription(){ return getValue("DESCRIPTION");}
	public String getDTStart(){ return getValue("DTSTART");}
	public String getGEO(){ return getValue("GEO");}
	public String getLastMod(){ return getValue("LAST-MOD");}
	public String getLocation(){ return getValue("LOCATION");}
	public String getOrganizer(){ return getValue("ORGANIZER");}
	public String getPercent(){ return getValue("PERCENT");}
	public String getPriority(){ return getValue("PRIORITY");}
	public String getRecurID(){ return getValue("RECURID");}	
	public String getSeq(){ return getValue("SEQ");}
	public String getSummary(){ return getValue("SUMMARY");}
	public String getURL(){ return getValue("URL");}
	public String getRRule(){ return getValue("RRULE");}
	public String getDue(){ return getValue("DUE");}
	public String getATTACH(){ return getValue("ATTACH");}
	public String getAttendee(){ return getValue("ATTENDEE");}
	public String getCategories(){ return getValue("CATEGORIES");}
	public String getComment(){ return getValue("COMMENT");}
	public String getContact(){ return getValue("CONTACT");}
	public String getExDate(){ return getValue("EXDATE");}
	public String getRStatus(){ return getValue("RSTATUS");}	
	public String getRelated(){ return getValue("RELATED");}
	public String getResources(){ return getValue("RESOURCES");}
	public String getRDate(){ return getValue("RDATE");}
	
	
	public void setCalendarName(String value){setValue("X-WR-CALNAME",value );}	

}
