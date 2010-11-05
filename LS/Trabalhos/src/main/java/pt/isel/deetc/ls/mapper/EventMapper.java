package pt.isel.deetc.ls.mapper;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.Criteria;
import pt.isel.deetc.ls.database.Query;
import pt.isel.deetc.ls.model.Event;

public class EventMapper extends Mapper<Event> {
	private final String _COMPONENTNAME = "Event";

	private String _insertStm = "insert into Component (id,begin_date,end_date, componentTypeID) values( ?, ?, ?, ?) "
			+ "insert into Event (description, summary, location, componentID) values ( ?, ?, ?, ? ) "
			+ "insert into Component_Category (componentID, categoryID) values ( ?, ?) "
			+ "insert into Calendar_Component (calendarID,componentID) values(?,?)";

	private String _selectStm = "select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description"
			+ ",e.summary,e.location, e.componentID from Event e, Component c, "
			+ "Calendar_Component cc, Calendar ca where e.componentID=c.id "
			+ "and c.id=cc.componentID and cc.calendarID=ca.id";

	private String _selectComponentTypeId = "select id from ComponentType where name = ?";
	private String _selectCalendarByID = "select id from Calendar where name =?";

	private String _deleteStm = "delete from Calendar_Component where componentID = ?;"
			+ "delete from Component_Category where componentID = ?;"
			+ "delete from Event where componentID = ?;"
			+ "delete from Component where ID = ?;";

	
	

	public EventMapper() {
		super();
	}

	@Override
	public int delete(Event event) {
		if (event == null)
			return 0;
		Connection c = getConnection();
		try {
			c.setAutoCommit(false);
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		PreparedStatement p = getDeletePreparedStm(event);
		int rowNbr = 0;
		try {
			int idx = 0, res = 0;
			rowNbr = p.executeUpdate();
			if (idx < 7 && res != 0 || idx > 6 && res != 1) {
				c.rollback();
				p.close();
				closeConnection();
				System.out.println("Debug Mode: Rollback activado");
				return 0;
			}
			c.commit();
			p.close();
			closeConnection();

		} catch (SQLException e) {
			e.printStackTrace();
		} finally {

			closeConnection();
		}
		return rowNbr;
	}

	@Override
	public boolean exists(Event event) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public int insert(Event event) {
		if (event == null)
			return 0;
		openConnection();
		PreparedStatement p = getInsertPrepStm(event);
		int rowNbr = 0;
		try {
			rowNbr = p.executeUpdate();
			p.close();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {

			closeConnection();
		}
		return rowNbr;
	}

	@Override
	public ArrayList<Event> select() {
		Query q = new Query(_selectStm);
		PreparedStatement p = null;
		try {
			p = getConnection().prepareStatement(q.getQuery());
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (select(p));
	}

	@Override
	public int update(Event event) {
		String _updateEventStm = "update event set ";
		String _updateComponentStm = "update component set ";
		int res=0;
		try {
			/* NOTES: Used to detect if previous parameters have been used (to be implemented in a more efficient way possibly in Criteria  */
			int countParams=0;
			Connection conn = getConnection();
			Statement stm = conn.createStatement();
			// BEGIN TRANSACTION
			conn.setAutoCommit(false);

			// Updates to Event Table (if they exist)
			if (event.getSummary() != null){
				_updateEventStm += "summary='" + event.getSummary() + "'";
				++countParams;
			}
			if (event.getLocation() != null){
				if(countParams>0) _updateEventStm+=",";
				_updateEventStm += "location='" + event.getLocation() + "'";
			}
			if (event.getDescription() != null){
				if(countParams>0) _updateEventStm+=",";
				_updateEventStm += "description='" + event.getDescription() + "'";
			}
			_updateEventStm += " WHERE componentId=" + event.getId() + ";";
						
			if ( (res+=stm.executeUpdate(_updateEventStm))<1) { conn.rollback(); System.out.println("Debug Mode: rollback de Event"); }
			
			// Updates to Component Table (if they exist)
			countParams=0;
			if (event.getBeginDate() != null){
				_updateComponentStm += "begin_date='" + event.getBeginDate() + "'";
				++countParams;
			}
			if (event.getEndDate() != null){
				if(countParams==1) _updateComponentStm+=",";
				_updateComponentStm += "end_date='" + event.getEndDate() + "'";
			}
			_updateComponentStm += " WHERE id=" + event.getId()+";";
		
			if ((res+=stm.executeUpdate(_updateComponentStm))<1) { 	conn.rollback(); System.out.println("Debug Mode: rollback de Component"); 	}
			
			// END TRANSACTION
			conn.commit();
			stm.close();
			closeConnection();
		} catch (SQLException e) { e.printStackTrace(); }
		// Debug Mode
		System.out.println("Debug Mode: "+_updateEventStm);
		System.out.println("Debug Mode: "+_updateComponentStm);
		return res;
	}

	public ArrayList<Event> selectBetweenDates(Event event) {
		Query q = new Query(_selectStm);
		q.add(Criteria.greaterOrEqualThan("c.begin_date"));
		q.add(Criteria.lessOrEqualThan("c.end_date"));
		PreparedStatement p = null;
		try {
			p = getConnection().prepareStatement(q.getQuery());
			p.setString(1, event.getBeginDate().toString());
			p.setString(2, event.getEndDate().toString());
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (select(p));
	}

	public ArrayList<Event> selectByCal(Event event) {
		Query q = new Query(_selectStm);
		q.add(Criteria.equal("ca.name"));

		PreparedStatement p = null;
		try {
			p = getConnection().prepareStatement(q.getQuery());
			p.setString(1, event.getCalName());

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (select(p));
	}

	private PreparedStatement getDeletePreparedStm(Event event) {
		PreparedStatement p = null;

		try {
			p = getConnection().prepareStatement(_deleteStm);
			p.setInt(1, event.getId());
			p.setInt(2, event.getId());
			p.setInt(3, event.getId());
			p.setInt(4, event.getId());

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return p;
	}

	public ArrayList<Event> selectByID(Event event) {
		Query q = new Query(_selectStm);
		q.add(Criteria.equal("c.id"));

		PreparedStatement p = null;
		// System.out.println(q.getQuery());
		try {
			p = getConnection().prepareStatement(q.getQuery());
			p.setInt(1, event.getId());

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (select(p));
	}

	private ArrayList<Event> select(PreparedStatement stm) {
		openConnection();
		ArrayList<Event> list = new ArrayList<Event>();
		try {
			ResultSet result = stm.executeQuery();
			rsToal(result, list);
			result.close();
			stm.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		closeConnection();
		return list;

	}

	private synchronized void rsToal(ResultSet result, ArrayList<Event> list) {
		try {
			while (result.next()) {
				Event event = new Event(result.getString(3),
						result.getString(4), result.getString(5),
						result.getString(6), result.getString(7),
						result.getString(8));
				event.setId(result.getInt(9));
				list.add(event);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

	private PreparedStatement getInsertPrepStm(Event event) {
		PreparedStatement p = null;
		ResultSet rs = null;
		int calendarID = 0;

		// Query calName
		try {
			p = getConnection().prepareStatement(_selectCalendarByID);
			p.setString(1, event.getCalName());
			rs = p.executeQuery();
			rs.next();
			calendarID = rs.getInt("id");
			rs.close();
			p.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		int componentID = event.getId();
		int componentTypeID = 1;
		int categoryID = 0;
		try {
			p = getConnection().prepareStatement(_selectComponentTypeId);
			p.setString(1, _COMPONENTNAME);
			rs = p.executeQuery();
			rs.next();
			categoryID = rs.getInt("id");
			rs.close();
			p.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try {
			p = getConnection().prepareStatement(_insertStm);
			p.setInt(1, componentID);
			p.setString(2, event.getBeginDate().toString());
			p.setString(3, event.getEndDate().toString());
			p.setInt(4, componentTypeID);

			p.setString(5, event.getDescription());
			p.setString(6, event.getSummary());
			p.setString(7, event.getLocation());
			p.setInt(8, componentID);

			p.setInt(9, componentID);
			p.setInt(10, categoryID);

			p.setInt(11, calendarID);
			p.setInt(12, componentID);
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return p;
	}

}
