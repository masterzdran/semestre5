package pt.isel.deetc.ls.model;

public class Todo extends Component {
	private String _sumary;
	private String _description;
	private String _state;
	private double _donepercent;
	private int _priority;

	public Todo(String calname, String beginDate, String endDate) {
		super(calname, beginDate, endDate);
		set_description(null);
		set_donepercent(0);
		set_priority(0);
		set_state(null);
		set_sumary(null);		
	}
	
	public Todo(){
		super(null,null,null);
		setId(-1);
		set_description(null);
		set_donepercent(0);
		set_priority(0);
		set_state(null);
		set_sumary(null);
	}
	public String get_sumary() {
		return _sumary;
	}
	public void set_sumary(String sumary) {
		_sumary = sumary;
	}
	public String get_description() {
		return _description;
	}
	public void set_description(String description) {
		_description = description;
	}
	public String get_state() {
		return _state;
	}
	public void set_state(String state) {
		_state = state;
	}
	public double get_donepercent() {
		return _donepercent;
	}
	public void set_donepercent(double donepercent) {
		_donepercent = donepercent;
	}
	public int get_priority() {
		return _priority;
	}
	public void set_priority(int priority) {
		_priority = priority;
	}

}
