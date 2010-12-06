package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;

public interface IFormat {
	public abstract void render(PrintStream ps);
}
