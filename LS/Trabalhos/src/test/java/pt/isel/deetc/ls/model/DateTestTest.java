package pt.isel.deetc.ls.model;

import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.Duration;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;
import org.joda.time.format.DateTimeFormatterBuilder;
import org.junit.Test;


public class DateTestTest {
	long longWeek = 604800;
	long longDay  = 86400;
	long longHour = 3600;
	long longMinute= 60;
	
	private DateTime parse (String str,String tz){
		char[] chars = {'W','D','T','H','M','S'};
		int[] charsVal = {0,0,0,0,0,0};
		int year=-1;
		int month=-1;
		int day=-1;
		int hour=-1;
		int minute=-1;
		int second=-1;
		String timezone="";
		DateTimeFormatter dtf1 = DateTimeFormat.forPattern("yyyyMMdd'T'HHmmss'Z'");
		char signal=' ';
		DateTime d = null;
		  
		String bstr = str.toUpperCase();
		char c = bstr.toUpperCase().charAt(0);
		if ( c == '+' || c == '-' || c == 'P' ){
			int idx=0;
			int pidx=0;
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
				if ((findMatch = bstr.indexOf(chars[idx])) > -1 ){
					try{
						charsVal[idx]= Integer.parseInt(bstr.substring(pidx,findMatch));
					}catch (NumberFormatException n){
						charsVal[idx]=0;
					}
					pidx=findMatch+1;
				}
			}
			
			System.out.println("Parser Duration: "
					+ ((signal == ' ')?"":"<"+signal+">")
					+ ((charsVal[0]<0)?"":"<"+charsVal[0]+">")
					+ ((charsVal[1]<0)?"":"<"+charsVal[1]+">")
					+ ((charsVal[3]<0)?"":"<"+charsVal[3]+">")
					+ ((charsVal[4]<0)?"":"<"+charsVal[4]+">")
					+ ((charsVal[5]<0)?"":"<"+charsVal[5]+">")

			);
			
			long x = charsVal[0]*longWeek +	charsVal[1]*longDay + charsVal[3]*longHour + charsVal[4]*longMinute + charsVal[5];
			Duration duration = new Duration(x);
			 d = new DateTime();
			System.out.format("DateTime: Before>> %s (Duration: %s)\n",d.toString(), duration.toDuration());
			if (signal == '+'){
				d=d.plusWeeks(charsVal[0]).plusDays(charsVal[1]).plusHours(charsVal[3]).plusMinutes(charsVal[4]).plusSeconds(charsVal[5]);
			}else{
				d=d.minusWeeks(charsVal[0]).minusDays(charsVal[1]).minusHours(charsVal[3]).minusMinutes(charsVal[4]).minusSeconds(charsVal[5]);				
			}
			
			System.out.println("DateTime:After>>  "+d.toString());
			System.out.println("DateTime:>>  "+d.toString(dtf1));
		}else{
			int idx=0;
			if ((idx = bstr.length())<8 || idx > 16){
				
				return null;
			}
			idx=0;
			//ParseDateTime
			
			year 	= Integer.parseInt(bstr.substring(idx,idx+=4));
			month 	= Integer.parseInt(bstr.substring(idx,idx+=2));
			day		= Integer.parseInt(bstr.substring(idx,idx+=2));
			if (idx < bstr.length()){
				if (bstr.toUpperCase().charAt(idx) == 'T')
					idx++;
				
				hour	= Integer.parseInt(bstr.substring(idx,idx+=2));
				minute	= Integer.parseInt(bstr.substring(idx,idx+=2));
				second	= Integer.parseInt(bstr.substring(idx,idx+=2));
				if (idx < bstr.length()){
					if (bstr.toUpperCase().charAt(idx) == 'Z')
						timezone = "UTC";
				}
			}
			year=(year>-1)? year : 0;
			month=((month >-1)?month : 0);
			day=((day >-1)?day : 0);
			hour=((hour >-1)?hour : 0);
			minute=((minute>-1)?minute : 0);
			second=((second>-1)?second : 0);
			DateTimeZone dtz = (tz != null && !tz.trim().isEmpty())?DateTimeZone.forID(tz):DateTimeZone.UTC;
			System.out.println("DateTimeZone:>>  "+dtz.toString());
			DateTime date = new DateTime(year, month, day, hour, minute, second, 0,dtz);
			System.out.println("[LOCAL TIME]"+date.toDateTime(DateTimeZone.UTC).toString());
			d= new DateTime(date.toDateTime(DateTimeZone.UTC));
			
			System.out.println("Parser Date: "
					+ ((year<0)?"":"<"+year+">")
					+ ((month<0)?"":"<"+month+">")
					+ ((day<0)?"":"<"+day+">")
					+ ((hour<0)?"":"<"+hour+">")
					+ ((minute<0)?"":"<"+minute+">")
					+ ((second<0)?"":"<"+second+">")
					+ ((timezone.isEmpty())?"":"<"+timezone+">")					
			);

			System.out.println("DateTime:>>  "+d.toString());
			System.out.println("DateTime:>>  "+d.toString(dtf1));
		}
		return d;
	}
	@Test
	public void dateTests(){
		String[] test =
		{
				"20101010"
				,"20101011003000"
				,"20101012T004000"
				,"20101012T004000Z"
				,"+P15DT5H0M20S"
				,"-P7W"
				,"+PT123H65M0S"
				,"P7W"
		};
		

		DateTimeFormatterBuilder d1 = new DateTimeFormatterBuilder();
		d1.appendYear(4, 4).appendMonthOfYear(2).appendDayOfMonth(2);
		
		DateTimeFormatterBuilder d2 = new DateTimeFormatterBuilder();
		d2.appendYear(4, 4).appendMonthOfYear(2).appendDayOfMonth(2).
		appendHourOfDay(2).appendMinuteOfHour(2).appendSecondOfMinute(2);
		
		DateTimeFormatterBuilder d3 = new DateTimeFormatterBuilder();
		d3.appendYear(4, 4).appendMonthOfYear(2).appendDayOfMonth(2).
		appendHourOfDay(2).appendMinuteOfHour(2).appendSecondOfMinute(2).appendTimeZoneId();
		
		
//		for( int i=0;i<test.length;++i){
//			System.out.println("["+test[i]+"]");
//			//System.out.println("\t["+new LSDate(test[i]).toString()+"\t"+new LSDate(test[i])+"]");
//
//			parse(test[i]);
//		}

		DateTimeZone x = DateTimeZone.forID("US/Pacific");
		System.out.println("["+parse("20021028T150000", "US/Pacific").toString()+"]");		
			
	}

}
