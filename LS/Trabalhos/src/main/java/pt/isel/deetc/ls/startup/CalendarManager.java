package pt.isel.deetc.ls.startup;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Map;

import pt.isel.deetc.lmp.common.clp.CommandLineParser;
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
		if (args.length == 0) {
			System.out.println("No command or arguments");
			return;
		}
		String command = args[0];
		Map<String, String> mapArgs = null;
		CommandLineParser clp = new CommandLineParser();
		mapArgs = clp.parse(args);
		System.out.printf("Comando %s:\n", command);

		CommandLoader cmdl = null;
		cmdl = new CommandLoader();

		try {
			cmdl.execute(command, mapArgs);
		} catch (InvalidCommandException e) {
			e.printStackTrace();
		}
	}

}
