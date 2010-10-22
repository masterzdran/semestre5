package pt.isel.deetc.ls.model;

import org.joda.time.LocalDateTime;



public class Task extends Component{
  // Constructors
  // Empty Constructor
  public Task (String calname,LocalDateTime beginDate, LocalDateTime endDate ) {
	super (calname,beginDate,endDate);
	
  }
}

