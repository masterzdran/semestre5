package pt.isel.deetc.ls.database;

public class Criteria {
	private String _operator;
	protected String field;
	protected Object value;
	
	private Criteria(String field,String operator, Object value){
		this.field = field;
		this._operator = operator;
		this.value = value;
	}
	public static Criteria greaterOrEqualThan(String field, Object value){
		return new Criteria(field, " >= ", value);
	}

	public static Criteria greaterOrEqualThan(String field, int value){
		return Criteria.greaterThan(field, new Integer(value));
	}	
	
	public static Criteria greaterThan(String field, Object value){
		return new Criteria(field, " > ", value);
	}

	public static Criteria greaterThan(String field, int value){
		return Criteria.greaterThan(field, new Integer(value));
	}

	public static Criteria lessOrEqualThan(String field, Object value){
		return new Criteria(field, " <= ", value);
	}
	public static Criteria lessOrEqualThan(String field, int value){
		return Criteria.lessThan(field, new Integer(value));
	}
	public static Criteria lessThan(String field, Object value){
		return new Criteria(field, " < ", value);
	}
	public static Criteria lessThan(String field, int value){
		return Criteria.lessThan(field, new Integer(value));
	}
	
	public static Criteria equal(String field, Object value){
		return new Criteria(field, " = ", value);
	}
	public static Criteria equal(String field, int value){
		return Criteria.equal(field, new Integer(value));
	}
	
	@Override
	public String toString() {
		return field+" "+_operator+" '"+value+"'";
	}
}
