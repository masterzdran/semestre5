package pt.isel.deetc.ls.report.layout;

public interface ITableLayout<E> extends ILayout<E> {
	public Iterable<String> getColumnName();
}
