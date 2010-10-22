package pt.isel.deetc.ls.mapper;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.joda.time.DateTime;

import pt.isel.deetc.ls.database.Criteria;
import pt.isel.deetc.ls.database.Query;
import pt.isel.deetc.ls.model.Event;



public class EventMapper extends Mapper<Event> {
	private final String _COMPONENTNAME="Event";
	
	private String _insertStm = "insert into Component (id,begin_date,end_date, componentTypeID) values( ?, ?, ?, ?) "
		+ "insert into Event (description, summary, location, componentID) values ( ?, ?, ?, ? ) "
		+ "insert into Component_Category (componentID, categoryID) values ( ?, ?) "
		+ "insert into Calendar_Component (calendarID,componentID) values(?,?)";
	
	private String _selectStm = "select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description"+
	",e.summary,e.location, e.componentID from Event e, Component c, "+
	"Calendar_Component cc, Calendar ca where e.componentID= c.id "+
	"and c.id=cc.componentID and cc.calendarID=ca.id";
	
	private String _selectStmBetweenDates = "select c.*, e.* from Component c inner join Event e on c.id = e.componentID " +
			"where c.begin_date >= ? and c.end_date <= ?";
	
	
	private String _selectSingleStm = "select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description"+
	",e.summary,e.location, e.componentID from Event e, Component c, "+
	"Calendar_Component cc, Calendar ca where e.componentID= c.id "+
	"and c.id=cc.componentID and cc.calendarID=ca.id and c.id = ?";
	
    private String _selectbyCal = "select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description"+
	",e.summary,e.location, e.componentID from Event e, Component c, "+
	"Calendar_Component cc, Calendar ca where e.componentID= c.id "+
	"and c.id=cc.componentID and cc.calendarID=ca.id and ca.name = ?";
	
    
    private String _selectComponentTypeId ="select id from ComponentType where name = ?";
    private String _selectCalendarByID="select id from Calendar where name =?";
    
    
	public EventMapper() {
		super();
	}
	@Override
	public int delete(Event event) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public boolean exists(Event event) {
		throw new UnsupportedOperationException("Not supported yet.");
	}
	private PreparedStatement getPreparedStatement(Event event) {
		PreparedStatement p=null;
		ResultSet rs = null;
		int calendarID =0;
		
		//Query calName 
		try {
			p = getConnection().prepareStatement(_selectCalendarByID);
			p.setString(1,event.get_calname());
			rs= p.executeQuery();
			rs.next();
			calendarID = rs.getInt("id");
			rs.close();
			p.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		int componentID = event.getId();
		int componentTypeID  = 1;
		int categoryID = 0;
		try{
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
			p.setString(3,  event.getEndDate().toString());
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

	
	@Override
	public int insert(Event event) {
		if (event == null) return 0;
		openConnection();
		PreparedStatement p = getPreparedStatement(event);
		int rowNbr =0;
		try {
			rowNbr = p.executeUpdate();
			p.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}finally{
		
		closeConnection();
		}
		return rowNbr;
	}

	@Override
	public ArrayList<Event> select() {
		openConnection();
		ArrayList<Event> list=new ArrayList<Event>();
		try {
			PreparedStatement p=getConnection().prepareStatement(_selectStm);
			ResultSet result = p.executeQuery();
			while( result.next()) {
				Event event = new Event(result.getString(3), (new DateTime(result.getDate(4).toString())).toLocalDateTime(), (new DateTime(result.getDate(5).toString())).toLocalDateTime());
				event.setDescription(result.getString(6));
				event.setLocation(result.getString(7));
				event.setSummary(result.getString(8));
				event.setId(result.getInt(9));
				list.add(event);
			}
			result.close();
			p.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		closeConnection();
		
		// TODO Select calendar
		return list;

	}

	private ArrayList<Event> select(String stm) {
		openConnection();
		ArrayList<Event> list=new ArrayList<Event>();
		try {
			PreparedStatement p=getConnection().prepareStatement(stm);
			ResultSet result = p.executeQuery();
			while( result.next()) {
				Event event = new Event(result.getString(3), (new DateTime(result.getDate(4).toString())).toLocalDateTime(), (new DateTime(result.getDate(5).toString())).toLocalDateTime());
				event.setDescription(result.getString(6));
				event.setLocation(result.getString(7));
				event.setSummary(result.getString(8));
				event.setId(result.getInt(9));
				list.add(event);
			}
			result.close();
			p.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		closeConnection();
		return list;

	}
	@Override
	public int update(Event event) {
		throw new UnsupportedOperationException("Not supported yet.");
	}
	
	public ArrayList<Event> selectBetweenDates(Event event){
		Query q = new Query();
		
		q.add(Criteria.greaterOrEqualThan("c.begin_date", event.getBeginDate()));
		q.add(Criteria.lessOrEqualThan("c.end_date", event.getEndDate()));
		
		StringBuffer stm = new StringBuffer();
		stm.append(_selectStm);
		stm.append(" and ");
		stm.append(q.getWhereClause());
		
		System.out.println(stm.toString());
		return(select(stm.toString()));

	}
	
	
	public ArrayList<Event> selectByID(Event event){
		Query q = new Query();
		q.add(Criteria.equal("c.id", event.getId()));
		
		StringBuffer stm = new StringBuffer();
		stm.append(_selectStm);
		stm.append(" and ");
		stm.append(q.getWhereClause());
		System.out.println(stm.toString());
		return(select(stm.toString()));
	}
	
}

