package pt.isel.deetc.ls.model;

import org.joda.time.LocalDateTime;

public class Event extends Component{
  private String _description;
  private String _location;
  private String _summary;

  public Event(String calname,LocalDateTime beginDate, LocalDateTime endDate) {
    super(calname,beginDate,endDate);
    _description = null;
    _location = null;
    _summary = null;
  }

    public String getDescription() {
        return _description;
    }

    public void setDescription(String description) {
        this._description = description;
    }

    public String getLocation() {
        return _location;
    }

    public void setLocation(String location) {
        this._location = location;
    }

    public String getSummary() {
        return _summary;
    }

    public void setSummary(String summary) {
        this._summary = summary;
    }

    @Override
    	public String toString() {
    		
    		return getId()+" :: "+ getDescription()+" :: "+getBeginDate()+" :: "+getEndDate()+" :: "+get_calname()+" :: "+getSummary()+" :: "+getDescription()+" :: "+getDescription()+" :: ";
    	}
}

