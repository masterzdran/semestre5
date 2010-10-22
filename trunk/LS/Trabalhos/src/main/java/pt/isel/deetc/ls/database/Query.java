package pt.isel.deetc.ls.database;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Query {
	private List<Criteria> _criteriaList;
	
	public Query(){
		_criteriaList = new ArrayList<Criteria>();
	}

	public void add(Criteria criteria){
		_criteriaList.add(criteria);		
	}
	
	public String getWhereClause(){
		StringBuffer stm = new StringBuffer();
		for (Iterator<Criteria> i = _criteriaList.iterator(); i.hasNext();){
			Criteria criteria = i.next();
			if (stm.length() != 0 ){
				stm.append(" AND ");
			}
			stm.append(criteria.toString());
		}
		return stm.toString();
	}
	
	public String getSetClause(){
		StringBuffer stm = new StringBuffer();
		for (Iterator<Criteria> i = _criteriaList.iterator(); i.hasNext();){
			Criteria criteria = i.next();
			if (stm.length() != 0 ){
				stm.append(" , ");
			}
			stm.append(criteria.toString());
		}
		return stm.toString();
	}

}
