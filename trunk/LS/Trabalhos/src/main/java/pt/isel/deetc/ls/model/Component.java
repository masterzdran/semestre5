package pt.isel.deetc.ls.model;


import org.joda.time.LocalDateTime;

import pt.isel.deetc.ls.utils.Utils;

abstract  public class Component{
  private int _id;
  private LocalDateTime _beginDate;
  private LocalDateTime _endDate;
  private String _calname;
  
  public Component (String calname, LocalDateTime beginDate, LocalDateTime endDate ) {
	  _calname = calname;
      _beginDate = beginDate;
      _endDate = endDate;
      _id = Utils.getUniqueID();
  }

    public LocalDateTime getBeginDate() {
        return _beginDate;
    }

    public void setBeginDate(LocalDateTime beginDate) {
        this._beginDate = beginDate;
    }

    public LocalDateTime getEndDate() {
        return _endDate;
    }

    public void setEndDate(LocalDateTime endDate) {
        this._endDate = endDate;
    }

    public int getId() {
        return _id;
    }

    public void setId(int id) {
        this._id = id;
    }

	public String get_calname() {
		return _calname;
	}

	public void set_calname(String calname) {
		this._calname = calname;
	}
    
}