package pt.isel.deetc.ls.database;

import java.sql.Connection;
import java.sql.SQLException;

import com.microsoft.sqlserver.jdbc.SQLServerDataSource;
import com.microsoft.sqlserver.jdbc.SQLServerException;

public class ConnectionManager {
	private SQLServerDataSource _ds;
	private Connection _con;
	 
	public ConnectionManager() {
		start();
	}
	private void start(){
		try {
			_ds  = DBDataSource.getInstace().getDataSource();
			_con = _ds.getConnection(); 
		} catch (SQLServerException e) {
			// TODO IOException treatment
		}
	}
	public Connection getConnection(){
		if (_con == null) start();
		return _con;
	}

	public boolean closeConnection(){
		if (_con != null){
			try {
				_con.close();
				_con=null;
			} catch (SQLException e) {
				System.err.print("A error ocorred while attemption to close the connection.[ Error :]"+e.getErrorCode());
				return false;
			}
		}
		return true;
	}
	public boolean openConnection(){
		try {		
			if (_con != null){
				try {
					if (!_con.isValid(1000)){
						return false;
					}
				} catch (SQLException e) {
					System.err.print("A error ocorred while attemption to evaluate the connection.[ Error :]"+e.getErrorCode());
					return false;
				}
			}else{
				_con = _ds.getConnection();
			}
		} catch (SQLException e) {
			System.err.print("A error ocorred while attemption to open the connection.[ Error :]"+e.getErrorCode());
			return false;
		}
			
		return true;
	}

}
