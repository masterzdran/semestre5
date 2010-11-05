
package pt.isel.deetc.ls.cmd;

import java.util.ArrayList;

import pt.isel.deetc.ls.exceptions.InvalidCommandParameterException;
import pt.isel.deetc.ls.model.IRule;

public class Parameter {
    private String _name;
    private String _value;
    private String _description;
    private ArrayList<IRule> _rules;
    private boolean _isSet;
    private boolean _mandatory;

    public Parameter(String name, String description, ArrayList<IRule> rules, boolean mandatory) {
        _name = name;
        _description = description;
        _value = "";
        _rules = rules;
        _isSet= false;
    	_mandatory = mandatory;
    }
    public Parameter(String name, String description, ArrayList<IRule> rules) {
    	this(name, description, rules, false);
    }
    public Parameter(String name, String description, boolean mandatory) {
    	this(name,description,new ArrayList<IRule>(),mandatory);
    
    }

    public Parameter(String name, String description) {
    	this(name,description,new ArrayList<IRule>(),false);
    }
    
    public void addRule(IRule rule){
    	_rules.add(rule);
    }
    
    public String getName() {
        return _name;
    }

    public String getValue() {
        return _value;
    }

    public String getDescription(){
    	return _description;
    }
    
    public void setValue(String value) {
    	String backup = _value;
    	_value = value;
    	if (_rules == null) return;
    	for (IRule x : _rules){
    		if (!x.isValid()) {
    			_value = backup;
    			throw new InvalidCommandParameterException("::::"+value);
    		}
    	}
    	_isSet=true;
    }
    public void clear(){
        _value = "";
        _isSet=false;
    }

    public boolean isValid(){
    	for (IRule x : _rules){
    		if (!x.isValid()) {
    	   			return false;
    		}
    	}
    	return true;
    }
    public boolean isSet(){
    	return _isSet;
    }
    public boolean isMandatory(){
    	return _mandatory;
    }
    public void show(){
    	System.out.println("Name: "+_name);
    	System.out.println("Value: "+_value);
    	System.out.println("Description: "+_description);
    }

}
