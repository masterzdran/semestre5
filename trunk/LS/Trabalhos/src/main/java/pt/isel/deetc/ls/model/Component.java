package pt.isel.deetc.ls.model;


import org.joda.time.DateTime;
import org.joda.time.LocalDateTime;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;

import pt.isel.deetc.ls.utils.Utils;

abstract  public class Component{
  private int _id;
  private LocalDateTime _beginDate;
  private LocalDateTime _endDate;
  private String _calname;
  
  public Component (String calname, String beginDate, String endDate ) {
	  _calname = calname;
	  _beginDate=formatDate(beginDate);
	  _endDate= formatDate(endDate);
      _id = Utils.getUniqueID();
  }
  
  private LocalDateTime formatDate(String date){
	  if (date == null || date.trim().isEmpty()) return null;
	  
	  DateTimeFormatter dtf1 = DateTimeFormat.forPattern("yyyyMMdd");
	  DateTimeFormatter dtf2 = DateTimeFormat.forPattern("yyyyMMddHHmmss");
	  DateTimeFormatter dtf3 = DateTimeFormat.forPattern("yyyy-MM-dd HH:mm:ss.SSS");
	  LocalDateTime newDate = null;
	  
	  try{
		  newDate = dtf1.parseDateTime(date).toLocalDateTime();
	  }catch(IllegalArgumentException a1){
		  try{
			  newDate = dtf2.parseDateTime(date).toLocalDateTime();
		  }catch(IllegalArgumentException a2){
			  try{
				  newDate = dtf3.parseDateTime(date).toLocalDateTime();
			  }catch(IllegalArgumentException a3){
				throw new IllegalArgumentException() ;
			  }
		  }
	  }
	  return newDate;
  }

    public LocalDateTime getBeginDate() {
    	
    	return _beginDate;
    }

    public void setBeginDate(String beginDate) {
        this._beginDate = new DateTime(beginDate).toLocalDateTime();
    }

//    public LocalDateTime getEndDate() {
//        return _endDate;
//    }
    public LocalDateTime getEndDate() {
        return _endDate;
    }
    public void setEndDate(String endDate) {
    	this._endDate = new DateTime(endDate).toLocalDateTime();
    }

    public int getId() {
        return _id;
    }

    public void setId(int id) {
        this._id = id;
    }

	public String getCalName() {
		return _calname;
	}

	public void set_calname(String calname) {
		this._calname = calname;
	}
    
}