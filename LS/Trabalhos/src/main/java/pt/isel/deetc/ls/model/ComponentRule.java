package pt.isel.deetc.ls.model;

import java.util.ArrayList;

import pt.isel.deetc.ls.cmd.Parameter;

public class ComponentRule{
	public static IRule validValues(Parameter p, String ... value ){
		class ValidValues implements IRule{
			private Parameter _parameter;
			private ArrayList<String> _validvalues;
			public ValidValues(Parameter p, String ... value){
				_parameter = p;
				_validvalues = new ArrayList<String>();
				for(String val : value){
					_validvalues.add(val);
				}
				
			}
			public boolean isValid(){
				for (String value:_validvalues){
					if (_parameter.getValue().equals(value))
						return true;

				}
				return false;				
			}
			
		}
		return new ValidValues(p, value);
	}
	public static IRule isOptional(Parameter p){
		class isOptional implements IRule{
			public isOptional(Parameter p){
			}
			public boolean isValid(){
				return true;
			}
		}
		return new isOptional(p);
	}

	public static IRule isRequired(Parameter p){
		class IsRequired implements IRule{
			private Parameter _parameter;
			public IsRequired(Parameter p){
				_parameter=p;
			}
			public boolean isValid(){
				return !_parameter.getValue().trim().isEmpty();
			}
		}
		return new IsRequired(p);
	}
	
	public static IRule allowEmpty(Parameter p){
		class AllowEmpty implements IRule{
			public AllowEmpty(Parameter p){
			}
			public boolean isValid(){
				return true;
			}
		}
		return new AllowEmpty(p);
	}
	public static IRule allowNoEmpty(Parameter p){
		class AllowEmpty implements IRule{
			private Parameter _parameter;
			public AllowEmpty(Parameter p){
				_parameter = p;
			}
			public boolean isValid(){
				return !_parameter.getValue().trim().isEmpty() ;
			}
		}
		return new AllowEmpty(p);
	}
	public static IRule mutualExclusive(Parameter p1, Parameter p2){
		class MutualExclusive implements IRule{
			private Parameter _parameter1;
			private Parameter _parameter2;
			public MutualExclusive(Parameter p1, Parameter p2){
				_parameter1 = p1;
				_parameter2 = p2;
			}
			public boolean isValid(){
					return  !(!_parameter1.getValue().trim().isEmpty() && !_parameter2.getValue().trim().isEmpty());
			}
		}
		return new MutualExclusive(p1, p2);
	}
}
