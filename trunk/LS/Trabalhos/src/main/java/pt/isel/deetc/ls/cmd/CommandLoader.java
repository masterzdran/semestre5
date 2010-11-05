package pt.isel.deetc.ls.cmd;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import pt.isel.deetc.ls.exceptions.InvalidCommandException;

public class CommandLoader{
    private Map<String, Command> _commandMap;
    private boolean _exitRequested;
    private final String _FILECOMMANDS = "commands.txt";

    public CommandLoader () {
        _commandMap = new HashMap<String, Command>();
/*      
        this.add(new CreateCalendar());
        this.add(new CreateEvent());
        this.add(new GetEvent());
        this.add(new GetEventsAll());
        this.add(new GetEventsCal());
        this.add(new GetEvents());
        this.add(new DeleteEvent());
        this.add(new Init());

*/
        _exitRequested=false;
        this.add(new Help());
        this.add(new Exit());
        this.loadCommands();
        
    }
    
    private void loadCommands(){
    	BufferedReader fileInput;
		try {
			fileInput = new BufferedReader(new InputStreamReader(CommandLoader.class.getResourceAsStream(_FILECOMMANDS)));
			String command;
			while((command=fileInput.readLine() )!= null ){
				this.add((Command) Class.forName(CommandLoader.class.getPackage().getName()+"."+command).newInstance());
			}
			
			fileInput.close();
		} catch (Exception e) {
			System.out.println("Error while loading the commands."+e);
		}
    	
    }
    public boolean isExitStatusSet(){
    	return _exitRequested;
    }
    public boolean isValidCommand(String cmd){
        return _commandMap.containsKey(cmd);
    }

    public void execute(String cmd, Map<String, String> parameter) throws InvalidCommandException{
    	Command command =getCommand(cmd);
    	parseParameters(command, parameter);
    	command.run();
    }
    
    public Command getCommand(String cmd) throws InvalidCommandException{
        if (!isValidCommand(cmd)) throw new InvalidCommandException("Command :: " + cmd);
        return _commandMap.get(cmd);
    }
    public void list(){
        for (String name : _commandMap.keySet()) {
            System.out.println("::Command Name: "+name);
        }
    }

    private void add(Command cmd){
        _commandMap.put(cmd.getCommandName(), cmd);
    }
    private void parseParameters(Command cmd, Map<String, String> parameter){
    	for(String name : parameter.keySet()){
    		cmd.addParameter(name, parameter.get(name));
    	}
    }
	/**
	 *     
	 * @author nac
	 * Classe Help
	 */
    class Help extends Command{
		public Help() {
			super("help", "mostra a syntax de cada comando");
		}

		@Override
		public void execute() {
	        for (String name : _commandMap.keySet()) {
	            try {
	            	System.out.println("--------------------------------------------------------------------------------");
	            	System.out.println(getCommand(name).help());
	            } catch (InvalidCommandException ex) {
	                Logger.getLogger(CommandLoader.class.getName()).log(Level.SEVERE, null, ex);
	            }
	        }
			
		}
    }
    /**
     * Classe Exit
     * @author nac
     *
     */
    class Exit extends Command{

		public Exit() {
			super("exit", "termina a aplicação");
		}
		@Override
		public void execute() {
			_exitRequested = true;
		}
    	
    }
}

