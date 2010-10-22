package pt.isel.deetc.ls.cmd;

public class ParameterDescriptor {
    private String _name;
    private String _description;
    private boolean _isMandatory;
    private String _value;

    public ParameterDescriptor(String name, String description, boolean isMandatory) {
        this._name = name;
        this._description = description;
        this._isMandatory = isMandatory;
        this._value = "";
    }

    public String getDescription() {
        return _description;
    }
    public String getName() {
        return _name;
    }
    public boolean isMandatory(){
    	return _isMandatory;
    }
    public String getValue(){
    	return _value;
    }
    public void setValue(String value){
    	_value=value;
    }

}
