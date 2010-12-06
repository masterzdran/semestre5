package pt.isel.deetc.ls.mapper;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import pt.isel.deetc.ls.database.ConnectionManager;

/**
 * TODO Dealing with the exceptions
 * 
 * @param <T>
 */

abstract public class Mapper<T> {
	// Variable that keep the data source to connect to the database
	private ConnectionManager _cm;

	public Mapper() {
		_cm = new ConnectionManager();
	}

	public Connection getConnection() {
		if (_cm.getConnection() == null)
			_cm.openConnection();
		return _cm.getConnection();
	}

	public void openConnection() {
		if (_cm.getConnection() == null)
			_cm.openConnection();
	}

	public void closeConnection() {
		if (_cm.getConnection() != null)
			_cm.closeConnection();
	}

	protected ResultSet selectRS(String sql) {
		Connection c = getConnection();
		ResultSet result = null;
		PreparedStatement stm = null;
		try {
			c.setAutoCommit(false);
			stm = c.prepareStatement(sql);
			result = stm.executeQuery();
			c.commit();
		} catch (SQLException e) {
			System.err.print(e.getMessage());
			if (c != null) {
				try {
					System.err
							.println("Transaction is being rolled back for: ");
					System.err.println(sql);
					c.rollback();
				} catch (SQLException excep) {
					System.err.print(excep.getMessage());
				}
			}
		} finally {
			try {
				c.setAutoCommit(true);
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return result;
	}

	protected int execute(String stm) {
		Connection c = getConnection();
		PreparedStatement p = null;
		int rowNbr = 0;
		try {
			c.setAutoCommit(false);
			p = c.prepareStatement(stm);
			rowNbr = p.executeUpdate();
			c.commit();
		} catch (SQLException e) {
			System.err.print(e.getMessage());
			if (c != null) {
				try {
					System.err.println("Transaction is being rolled back for: ");
					System.err.println(stm);
					c.rollback();
				} catch (SQLException excep) {
					System.err.print(excep.getMessage());
				}
			}
		} finally {
			try {
				p.close();
				c.setAutoCommit(true);
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}
		closeConnection();
		return rowNbr;
	}

	/**
   * 
   */
	abstract public int insert(T tObject);

	/**
   * 
   */
	abstract public int delete(T tObject);

	/**
   * 
   */
	abstract public int update(T tObject);

	/**
   * 
   */
	abstract public Iterable<T> select();

	/**
   * 
   */
	abstract public boolean exists(T Tobject);
}
