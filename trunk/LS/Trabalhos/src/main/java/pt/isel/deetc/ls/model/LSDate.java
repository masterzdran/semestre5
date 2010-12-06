package pt.isel.deetc.ls.model;

import java.sql.Date;

import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;

public class LSDate{
	private DateTime _date;
	private final DateTimeFormatter _ICALDF = DateTimeFormat.forPattern("yyyyMMdd'T'HHmmss'Z'");
	private LSDate _baseDate;
	
	public LSDate() {
		_date = new DateTime();
	}
	
	public LSDate(String date){
		_date = parse(date);
	}
	public LSDate(String date, String timeZone){
		_date = parse(date);
	}

	public LSDate(Date date) {
		_date = new DateTime(date);
	}
	public LSDate(LSDate baseDate,String duration) {
		_baseDate=baseDate;
		_date = parseDuration(duration);

	}

	public void setDuration(LSDate baseDate,String duration) {
		_baseDate=baseDate;
		_date = parseDuration(duration);
	}
	public void setDate(String date) {
		_date = parse(date);
		_baseDate = null;
	}
	
	public String toICAL(){
		return _date.toString(_ICALDF);
	}
	@Override
	public String toString(){
		return _date.toString();
	}
	
	private DateTime parseDuration(String str){
		char[] chars = {'W','D','T','H','M','S'};
		int[] charsVal = {0,0,0,0,0,0};
		char signal=' ';
		int idx=0;
		int pidx=0;
		char c = str.toUpperCase().charAt(0);
		if (c != 'P'){
			signal = c;
			++idx;
		}
		if (idx == 0)
			signal = '+';
		++idx;
		pidx=idx;
		
		int findMatch=-1;
		for (idx = 0;idx < chars.length;++idx){
			if ((findMatch = str.indexOf(chars[idx])) > -1 ){
				try{
					charsVal[idx]= Integer.parseInt(str.substring(pidx,findMatch));
				}catch (NumberFormatException n){
					charsVal[idx]=0;
				}
				pidx=findMatch+1;
			}
		}
		DateTime d = new DateTime(_baseDate.toString());

		if (signal == '+'){
			d=d.plusWeeks(charsVal[0]).plusDays(charsVal[1]).plusHours(charsVal[3]).plusMinutes(charsVal[4]).plusSeconds(charsVal[5]);
		}else{
			d=d.minusWeeks(charsVal[0]).minusDays(charsVal[1]).minusHours(charsVal[3]).minusMinutes(charsVal[4]).minusSeconds(charsVal[5]);				
		}

		return d;
	}
	
	private DateTime parseDate(String str,String timeZone){
		int year=0, month=0,day=0, hour=0, minute=0,second=0;
		int idx=0;
		if ((idx = str.length())<8 || idx > 16)
			throw new IllegalArgumentException("Malformated Date/Time String");
		
		idx=0;
		//ParseDateTime
		year 	= Integer.parseInt(str.substring(idx,idx+=4));
		month 	= Integer.parseInt(str.substring(idx,idx+=2));
		day		= Integer.parseInt(str.substring(idx,idx+=2));
		if (idx < str.length() && (str.length() - idx )>= 7 && (str.length() - idx )<= 10 ){
			if (str.toUpperCase().charAt(idx) == 'T')
				idx++;
			hour	= Integer.parseInt(str.substring(idx,idx+=2));
			minute	= Integer.parseInt(str.substring(idx,idx+=2));
			second	= Integer.parseInt(str.substring(idx,idx+=2));
		}
		DateTimeZone dtz = (timeZone != null && !timeZone.trim().isEmpty())?DateTimeZone.forID(timeZone):DateTimeZone.UTC;
		DateTime date = new DateTime(year, month, day, hour, minute, second, 0,dtz);

		
		
		DateTime d = new DateTime(date.toDateTime(DateTimeZone.UTC));
		return d;
	}
	
	private DateTime parse (String str){
		return parse(str,"");
	}
	private DateTime parse (String str,String timezone){
		
		String bstr = str.toUpperCase();
		char c = bstr.toUpperCase().charAt(0);
		
		if ( c == '+' || c == '-' || c == 'P' ){
			return parseDuration(bstr);
		}else{
			return parseDate(bstr,timezone);
		}
	}
}