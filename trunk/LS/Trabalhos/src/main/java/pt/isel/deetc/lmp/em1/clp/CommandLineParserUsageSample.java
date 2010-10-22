package pt.isel.deetc.lmp.em1.clp;

import java.util.Map;

import pt.isel.deetc.lmp.common.clp.CommandLineParser;

public class CommandLineParserUsageSample {

	/**
	 * @param args
	 */
	public static  void main(String[] args) {
		CommandLineParser clp = new  CommandLineParser("--"," ");

		if (args.length == 0){
			System.out.println("No command or arguments");
			return;
		}
		
		String command = args[0];
		if (args.length>1){
			String[] arg = new String[args.length-1];
			System.arraycopy(args, 1, arg, 0, arg.length);
		
			Map<String, String> mapArgs = clp.parse(arg);
			System.out.printf("Comando %s:\n",command);
			for (Map.Entry<String, String> entry : mapArgs.entrySet()) {
				System.out.printf("%s: %s\n", entry.getKey(), entry.getValue());
			}
		}
	}

}
