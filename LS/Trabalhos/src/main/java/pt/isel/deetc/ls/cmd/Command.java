package pt.isel.deetc.ls.cmd;

import java.util.HashMap;
import java.util.Map;

abstract public class Command {
	private Map<String, ParameterDescriptor> _validParameters;
	private String _name;
	private String _syntax = null;
	private String _description;
	private boolean _allowNoParameters;

	public Command(String name, String description, boolean allowNoParameters) {
		this._name = name;
		this._description = description;
		this._allowNoParameters = allowNoParameters;
		_validParameters = new HashMap<String, ParameterDescriptor>();
	}

	protected void addParameter(ParameterDescriptor parameterDescriptor) {
		_validParameters.put(parameterDescriptor.getName(), parameterDescriptor);
	}
	protected void addParameter(String name, String value){
		ParameterDescriptor p = null;
		if ((p = _validParameters.get(name)) == null){
			//Retorna Excepção
		}
		p.setValue(value);		
	}
	protected void clearParameters(){
		for(String name : _validParameters.keySet()){
			_validParameters.get(name).setValue(null);
		}
	}
	public void setSyntax(String syntax) {
		_syntax = syntax;
	}

	public String getCommandDescription() {
		return _description;
	}

	public String getCommandName() {
		return _name;
	}

	public String getSyntax() {
		return _syntax;
	}
	
	public String getValue(String name){
		return _validParameters.get(name).getValue();
	}
	
	private boolean isValidParameter(Map<String, String> parameters) {
		//is admissible an empty map as argument, but its not allowed null argument 
		if (parameters == null) return false;
		//if parameters map is empty but the command does not allow no parameters 
		if (parameters.isEmpty() && !_allowNoParameters) return false;

		//testing if all parameters are valid parameters names
		for (String name : parameters.keySet()) {
			if (!_validParameters.containsKey(name)){
				return false;
			}
		}
		//check is the mandatory parameter is present in the parameters input map
		/* A - The Key Exists in parameters arg
		 * B - The Parameter is mandatory
		 * 
		 * B | A || R
		 * 0 | 0 || isGood
		 * 0 | 1 || isGood
		 * 1 | 0 || isBad
		 * 1 | 1 || isGood
		 * 
		 * Result: return false as the key doesn't exists in the parameter arg, and
		 * the parameter is mandatory
		 */
		for (String name : _validParameters.keySet()) {
			if (!parameters.containsKey(name) && _validParameters.get(name).isMandatory()){
				return false;
			}
		}
		return true;
	}
	
	public String help(){
		if (_syntax == null)
			setSyntax(processSyntax());
		StringBuffer help = new StringBuffer(" -" + getCommandName() +" [options] \n");
		help.append("--------------------------------------------------------------------------------");
		help.append(getSyntax());
		return help.toString();
	}
	public void showHelp(){
		System.out.println(help());
	}

	abstract public void execute();

	private String processSyntax() {
		String syntax = "<" + getCommandName()
				+ "> <um ou mais parâmetros do comando>\n";

		for (String name : _validParameters.keySet()) {
			syntax += "\t-<" + name + "> <valor do parâmetro>:\t ("
					+ _validParameters.get(name) + ")\n";
		}
		return syntax;
	}
}
