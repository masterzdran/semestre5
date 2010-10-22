package pt.isel.deetc.ls.model;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;


public class Date {

	final private String dateFormat = "yyyyMMdd";
	final private String dateTimeFormat = "yyyyMMddhhmm";
	private String dataFormat = dateTimeFormat;
	private java.util.Date data;

	/*
	 *  Construtor por omissao : Data corrente
	 */
	public Date(){
		data = new java.util.Date();
	}
	/*
	 *  Construtor com definição de data
	 */
	public Date(String date) throws ParseException{
		DateFormat dF = new SimpleDateFormat(dataFormat);
		data = dF.parse(date);
	}
	/*
	 *  Construtor com definição de data por duração
	 */
	public Date(String begin_date, String duration) throws ParseException {
		DateFormat dF = new SimpleDateFormat(dataFormat);
		Calendar cal = Calendar.getInstance();
		data = dF.parse(begin_date);
		cal.setTime(data);
		/*
		 * Necessário definir o formato do duration
		 * para efectuar-se a aritmética de datas.
		 * 
		 */
		cal.add(cal.HOUR_OF_DAY, Integer.parseInt(duration));
		data = cal.getTime();
	}
	/*
	 *  Redefinição de toString()
	 */
	public String toString(){
		DateFormat dF = new SimpleDateFormat(dataFormat);
		return dF.format(data).toString();		
	}
}