package pt.isel.deetc.ls.model;

public class Todo extends Component {
	private String _sumary;
	private String _description;
	private int  _state; // 0 : 
	private double _donepercent;
	private int _priority;

	public Todo(String calname, LSDate beginDate, LSDate endDate) {
		this(calname, beginDate,endDate,null, null,0,0,0);
	}
	
	public Todo(String calname, LSDate beginDate, LSDate endDate, 
		String description, String summary, int state, double donepercent, int priority) {
	    super(calname, beginDate, endDate);
	    setDescription(description);
	    setSummary(summary);
	    setState(state);
	    setDonePercent(donepercent);
	    setPriority(priority);
	    setComponetType("TODO");
	}
	
	public Todo(){
		this(null,null,null,null,null,0,0,0);
		setId(-1);
	}
	public String getSummary() {
		return _sumary;
	}
	public void setSummary(String sumary) {
		_sumary = sumary;
	}
	public String getDescription() {
		return _description;
	}
	public void setDescription(String description) {
		_description = description;
	}
	public int getState() {
		return _state;
	}
	public void setState(int state) {
		_state = state;
	}
	public double getDonePercent() {
		return _donepercent;
	}
	public void setDonePercent(double donepercent) {
		_donepercent = donepercent;
	}
	public int getPriority() {
		return _priority;
	}
	public void setPriority(int priority) {
		_priority = priority;
	}

}
