package pt.isel.deetc.ls.cmd;

import java.util.HashMap;
import java.util.Map;

import pt.isel.deetc.ls.exceptions.InvalidCommandParameterException;
import pt.isel.deetc.ls.exceptions.RequiredCommandParameterException;
import pt.isel.deetc.ls.model.ComponentRule;

abstract public class Command {
	private String _name;
	private String _syntax;
	private String _description;
	private Map<String, Parameter> _validArgments;

	public Command(String name, String description) {
		this._name = name;
		this._description = description;
		this._syntax = "";
		_validArgments = new HashMap<String, Parameter>();
		Parameter p = new Parameter("help", "show help");
		p.addRule(ComponentRule.isOptional(p));
		p.addRule(ComponentRule.allowEmpty(p));
		addParameter(p);
	}

	protected void addParameter(Parameter parameter) {
		_validArgments.put(parameter.getName(), parameter);
	}

	protected void addParameter(String name, String value) {
		Parameter p = null;
		if ((p = _validArgments.get(name)) == null) {
			throw new InvalidCommandParameterException("Invalid parameter: "
					+ name);
		}
		p.setValue(value);
	}

	private void clearParameters() {
		for (String name : _validArgments.keySet()) {
			_validArgments.get(name).clear();
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

	public String getValue(String name) {
		return _validArgments.get(name).getValue();
	}

	public void run() {
		if (_validArgments.get("help").isSet()) {
			showHelp();

		} else {
			evaluteArguments();
			execute();
		}
		clearParameters();
	}

	private boolean evaluteArguments() {
		// testing if all parameters are valid parameters names
		for (String name : _validArgments.keySet()) {
			if (!_validArgments.get(name).isValid()) {
				throw new RequiredCommandParameterException("The " + name
						+ " argument is required");
			}
		}
		return true;
	}

	public String help() {
		processSyntax();
		StringBuffer help = new StringBuffer(getCommandName() + " [options] \n");
		help.append("--------------------------------------------------------------------------------\n");
		help.append(getSyntax());
		return help.toString();
	}

	public void showHelp() {
		System.out.println(help());
	}

	private void processSyntax() {
		String syntax = "<" + getCommandName()
				+ "> <um ou mais parâmetros do comando>\n";

		for (String name : _validArgments.keySet()) {
			String mandatory = (_validArgments.get(name).isMandatory()) ? "(MANDATORY)": ""; 

			syntax += "\t-<" + _validArgments.get(name).getName()
					+ "> <valor do parâmetro>:\n\t\t "
					+ _validArgments.get(name).getDescription() 
					+ mandatory + "\n";
		}
		_syntax = syntax;
	}

	abstract public void execute();

}
