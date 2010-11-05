package pt.isel.deetc.ls.database;

public class Criteria {
	private String _operator;
	protected String field;
	protected Object value;
	
	private Criteria(String field,String operator){
		this.field = field;
		this._operator = operator;
		this.value = "?";
	}
	public static Criteria greaterOrEqualThan(String field){
		return new Criteria(field, " >= ");
	}
	public static Criteria greaterThan(String field){
		return new Criteria(field, " > ");
	}

	public static Criteria lessOrEqualThan(String field){
		return new Criteria(field, " <= ");
	}
	public static Criteria lessThan(String field){
		return new Criteria(field, " < ");
	}
	public static Criteria equal(String field){
		return new Criteria(field, " = ");
	}
	
	@Override
	public String toString() {
		return field+" "+_operator+" "+value+"";
	}
}
