package pt.isel.deetc.ls.model;


public class Event extends Component{
  private String _description;
  private String _location;
  private String _summary;
 
  public Event(String calname,String beginDate, String endDate) {
    super(calname,beginDate,endDate);
    _description = null;
    _location = null;
    _summary = null;
  }
  public Event (String calname,String beginDate, String endDate, String description, String location, String summary){
	  super(calname,beginDate,endDate);
	    _description = (description == null ||description.trim().isEmpty())?null:description;
	    _location = (location == null ||location.trim().isEmpty())?null:location;
	    _summary = (summary == null ||summary.trim().isEmpty())?null:summary;
  }
  public Event (String calname,String beginDate, String endDate, String description, String location, String summary, int id){
	  super(calname,beginDate,endDate);
	    _description = (description == null ||description.trim().isEmpty())?null:description;
	    _location = (location == null ||location.trim().isEmpty())?null:location;
	    _summary = (summary == null ||summary.trim().isEmpty())?null:summary;
	    setId(id); 
  }
 public Event(){
	 this(null,null,null,null,null,null,-1);
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
    		
    		return getId()+" :: "+ getDescription()+" :: "+getBeginDate()+" :: "+getEndDate()+" :: "+getCalName()+" :: "+getSummary()+" :: "+getDescription()+" :: "+getDescription()+" :: ";
    	}
}

