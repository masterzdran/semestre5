package pt.isel.deetc.lmp.em1.clp;

import java.util.Map;

import pt.isel.deetc.lmp.common.clp.CommandLineParser;

public class CommandLineParserUsageSample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		CommandLineParser clp = new  CommandLineParser();
                String[] arg = {"-a  "," xxxx "," -b "," xyz yzx ","c"," -----"};
		Map<String, String> mapArgs = clp.parse(arg);
		
		for (Map.Entry<String, String> entry : mapArgs.entrySet()) {
			System.out.printf("%s: %s\n", entry.getKey(), entry.getValue());
		}

	}

}
