package pt.isel.deetc.ls.cmd;


import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import pt.isel.deetc.ls.exceptions.InvalidCommandException;

public class CommandLoader{
    private Map<String, Command> _commandMap;

    public CommandLoader () {
        _commandMap = new HashMap<String, Command>();
        this.add(new Help());
        this.add(new CreateCalendar());
        this.add(new CreateEvent());
        this.add(new GetEvent());
        this.add(new GetEventsAll());
        this.add(new GetEventsCal());
        this.add(new GetEvents());
        this.add(new Init());
        this.add(new Exit());
    }
    
    public boolean isValidCommand(String cmd){
        return _commandMap.containsKey(cmd);
    }

    public void execute(String cmd, Map<String, String> parameter) throws InvalidCommandException{
    	Command command =getCommand(cmd);
    	parseParameters(command, parameter);
    	command.execute();
    	command.clearParameters();
    }
    
    public Command getCommand(String cmd) throws InvalidCommandException{
        if (!isValidCommand(cmd)) throw new InvalidCommandException();
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
			super("help", "mostra a syntax de cada comando", true);
		}

		@Override
		public void execute() {
	        for (String name : _commandMap.keySet()) {
	            try {
	            	System.out.println("--------------------------------------------------------------------------------");
	            	System.out.println(getCommand(name).getSyntax());
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
			super("exit", "termina a aplicação", true);
		}
		@Override
		public void execute() {
			// TODO Implementar o execute do Exit. A solução pode passar em lançar um objecto/excepção do 
			// tipo CalendarManagerExit (ou algo parecido) para que a aplicação que a chame apanhe, deforma 
			// a proceder ao fecho de aplicações ou aplicar outras funcionalidades antes de sair da aplicação.
			// Não deverá ser o Command Loader a garantir isso.
		}
    	
    }
}

