package pt.isel.deetc.lmp.common.clp;

import java.util.Collection;
import java.util.Hashtable;
import java.util.Map;

/**
 * This class parses a command line arguments string given to the {@link #parse} method.
 * <p>
 * With the given command line string a {@link Map} is filled with the argument name being the key and the optional argument value 
 * being the map value. The command line arguments map is available as the return object from {@link #parse(String)} method or as the return object from 
 * {@link #getArguments()}.
 * </p>
 * <p>
 * The supported command line arguments String has the following format:
 * <code>{ARGUMENT_PREFIX&ltargument_name&gtARGUMENT_VALUE_SEPARATOR&ltargument_value&gt}*</code>.
 * Here is a sample command line string for the default argument prefix ({@link #DEFAULT_ARGUMENT_PREFIX} -> "-") and  argument value separator 
 * ({@link #DEFAULT_ARGUMENT_VALUE_SEPARATOR} -> " "):
 * <b>-argumet1 valueArgumen1 -argument2 valueArgument2</b>
 * </p>
 * <p>Each argument name and value are trimmed from leading and trailing spaces.</p>
 * 
 * @author Carlos Guedes, Luis Falcao e Pedro Felix
 * @version 1.0 - 19/02/2010
 */
public class CommandLineParser {

    public static final String DEFAULT_ARGUMENT_PREFIX = "-";
    public static final String DEFAULT_ARGUMENT_VALUE_SEPARATOR = " ";
    private final String _argumentPrefix;
    private final String _argumentValueSeparator;

    /**
     * Initializes a new instance of the {@link #CommandLineParser} class with default argument prefix ({@link #DEFAULT_ARGUMENT_PREFIX} and default
     * argument value separator {@link #DEFAULT_ARGUMENT_VALUE_SEPARATOR}.
     */
    public CommandLineParser() {

        this(DEFAULT_ARGUMENT_PREFIX, DEFAULT_ARGUMENT_VALUE_SEPARATOR);
    }

    /**
     * /**
     * Initializes a new instance of the {@link #CommandLineParser} class with the given <code>argumentPrefix</code> and <code>argumentvalueseparator</code>
     *
     * @param argumentPrefix The string that prefixes the argument name
     * @param argumentValueSeparator The string that separates the argument name from its value.
     */
    public CommandLineParser(String argumentPrefix, String argumentValueSeparator) {
        _argumentPrefix = argumentPrefix;
        _argumentValueSeparator = argumentValueSeparator;
    }

    private String getField(String field, String prefix) {
        int idx = field.indexOf(prefix);
        return field.substring(idx + prefix.length(), field.length());
    }
    private boolean byPass(String args,String argumentPrefix){
    	int x=0;
    	return ( (x = args.trim().indexOf(_argumentPrefix)) == -1 || ((x > 0) && (args.charAt(x-1) != ' ')));
    }
    /**
     * Parses the given <code>commadLine</code> string array, fills the internal arguments map and returns it.
     * @param commandLine The command line string to be parsed
     * @return The parsed arguments {@link Map}
     */
    public Map<String, String> parse(String[] args) {
        if (args == null) {
            return new Hashtable<String, String>();
        }
        Hashtable<String, String> argumentsMap = new Hashtable<String, String>();
        int i = -1;
        String name = null;
        String value = "";

        // Skip the first arguments without the prefix
        while (++i < args.length && byPass(args[i],_argumentPrefix))  ;

        for (; i < args.length;) {
            name = getField(args[i].trim(), _argumentPrefix);
            value = "";

            while (++i < args.length && byPass(args[i],_argumentPrefix)) {
                value += args[i];
            }
            argumentsMap.put(name, value.trim());
        }
        return argumentsMap;
    }

    /**
     * Parses the given <code>commadLine</code> string, fills the internal arguments map and returns it.
     * @param commandLine The command line string to be parsed
     * @return The parsed arguments {@link Map}
     */
    public Map<String, String> parse(String commandLine) {
        if (commandLine == null || (commandLine = commandLine.trim()).isEmpty()) {
            return new Hashtable<String, String>();
        }
        Hashtable<String, String> argumentsMap = new Hashtable<String, String>();
        commandLine = ' '+commandLine;
        
        String[] arguments = commandLine.split(' '+_argumentPrefix);
        //Se não tiver o separador de opção toda a string é colocada na primeira posição
        //se tiver...
        // Iterate through the split parameters.
        //Original Line: for (int i = 0; i < arguments.length; ++i) {

        String argument = "";
        int idxSeparator = 0;
        String name = null;
        String value = "";

        for (int i=1; i < arguments.length; ++i) {
            argument = arguments[i];
            idxSeparator = argument.indexOf(_argumentValueSeparator);
            name = null;
            value = "";
            if (idxSeparator == -1) {
                // Parameter with no value
                name = argument;
            } else {
                // Parameter with value
                // Parse the name removing (trimming) leading and trailing spaces
                name = argument.substring(0, idxSeparator).trim();
                // Parse the value removing (trimming) leading and trailing spaces
                value = argument.substring(idxSeparator + _argumentValueSeparator.length(), argument.length()).trim();
            }
            argumentsMap.put(name, value);
        }
        return argumentsMap;
    }

    public Map<String, Collection<String>> parseMultiple(String commandLine) {
        return null;
    }
}
