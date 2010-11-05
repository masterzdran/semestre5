package pt.isel.deetc.ls.startup;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;

import pt.isel.deetc.ls.clp.CommandLineParser;
import pt.isel.deetc.ls.cmd.CommandLoader;
import pt.isel.deetc.ls.exceptions.InvalidCommandException;

import com.microsoft.sqlserver.jdbc.SQLServerException;

public class CalendarManager {

	/**
	 * @param args
	 * @throws IOException
	 * @throws FileNotFoundException
	 * @throws SQLServerException
	 * @throws InvalidCommandException
	 */
	public static void main(String[] args) {
		Map<String, String> mapArgs = null;
		
		String command = null;
		CommandLineParser clp = new CommandLineParser();
		CommandLoader cmdl = null;
		cmdl = new CommandLoader();
		
		
		if (args.length == 0) {
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			while (!cmdl.isExitStatusSet()){
				try {
					System.out.printf("[Iterative Mode]:");
					String commandline = input.readLine();
					//getting the command name
					int idx = commandline.indexOf(' ');

					command = (idx > -1 )?commandline.substring(0, idx):commandline;
					mapArgs = clp.parse((idx > -1 )?commandline.substring(idx+1):null);

					System.out.printf("Comando %s:\n", command);
					cmdl.execute(command, mapArgs);

				} catch (InvalidCommandException e) {
					System.out.printf("Erro no comando %s: %s\n", command,e.getMessage());
				} catch (IOException e1) {
					//IOException
				}

			}
		}else{
			mapArgs = clp.parse(args);
			command = args[0];
			try {
					System.out.printf("Comando %s:\n", command);	
					cmdl.execute(command, mapArgs);
			} catch (InvalidCommandException e) {
				e.printStackTrace();
			}
			
		}
		System.out.println("The program has ended!");
	}

}
