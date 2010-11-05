package pt.isel.deetc.ls.mapper;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import pt.isel.deetc.ls.database.Query;
import pt.isel.deetc.ls.model.Calendar;

public class CalendarMapper extends Mapper<Calendar> {
	private String _insertStm = "insert into Calendar (id,name) values (?,?)";
	private String _selectStm = "select id,name from Calendar";
	private String _countElem = "select count(id) as idCount from calendar where name = ?";
	
	public CalendarMapper() {
		super();
	}

	private PreparedStatement getInsertPrepStm(Calendar calendar){
		PreparedStatement p = null;
		try {
			p = getConnection().prepareStatement(_insertStm);
			p.setInt(1, calendar.getID());
			p.setString(2, calendar.getName());
		} catch (SQLException e) {
			System.err.print("An error ocorred while attemption prepare de statement.[ Error :]"+e.getMessage());
			return null;
		}
		return p;
	}
	
	@Override
	public int delete(Calendar calendar) {
		throw new UnsupportedOperationException("Not supported yet.");
	}

	@Override
	public boolean exists(Calendar calendar) {
		openConnection();
		int nbrRows = 0;
		try {
			PreparedStatement p=getConnection().prepareStatement(_countElem);
			p.setString(1, calendar.getName());
			ResultSet result = p.executeQuery();
			result.next();

			nbrRows = result.getInt(1);

			result.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			closeConnection();			
		}
		return nbrRows > 0;
	}

	@Override
	public int insert(Calendar calendar) {
		if (calendar == null) return 0;

		PreparedStatement p = getInsertPrepStm(calendar);
		if (p == null) return 0;
		int lineInserted = 0;
		
		try {
			lineInserted = getInsertPrepStm(calendar).executeUpdate();
		} catch (SQLException e) {
			System.err.println("An error ocorred while attemption execute the insert statement.\n[ Error :]"+e.getMessage());
		} finally{
			closeConnection();
		}
		return lineInserted;
	}

	@Override
	public ArrayList<Calendar> select() {
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
	public int update(Calendar calendar) {
		throw new UnsupportedOperationException("Not supported yet.");
	}
	
	
	private ArrayList<Calendar> select(PreparedStatement stm) {
		openConnection();
		ArrayList<Calendar> list = new ArrayList<Calendar>();
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
	private synchronized void rsToal(ResultSet result, ArrayList<Calendar> list) {
		try {
			while (result.next()) {
				Calendar calendar = new Calendar(result.getString(2),result.getInt(1));
				list.add(calendar);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}
}

