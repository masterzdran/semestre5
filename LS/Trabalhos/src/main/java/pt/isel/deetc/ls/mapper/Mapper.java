package pt.isel.deetc.ls.mapper;

import java.sql.Connection;
import java.util.ArrayList;

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
  
  public Connection getConnection(){
	  return _cm.getConnection();
  }
  public void openConnection(){
	  _cm.openConnection();
  }
  public void closeConnection(){
	  _cm.closeConnection();
  }
  /**
   * 
   */
  abstract public int insert (T tObject) ;
  /**
   * 
   */
  abstract public int delete (T tObject) ;
  /**
   * 
   */
  abstract public int update (T tObject) ;
  /**
   * 
   */
  abstract public ArrayList<T> select () ;
  /**
   * 
   */
  abstract public boolean exists (T Tobject);
}

