package pt.isel.deetc.ls.output;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

abstract public class Output<T> {

	private String _beginDocumentTag, _endDocumentTag;
	private String _beginRecordsTag, _endRecordsTag;
	private String _beginHeaderTag, _endHeaderTag;
	private String _beginRecordTag, _endRecordTag;
	private String _beginFieldTag, _endFieldTag;
	private StringBuffer buffer;
	private ArrayList<T> _list;
	
	// Constructor
	public Output(ArrayList<T> list) {
		this.buffer = new StringBuffer();
		this._list = list;
	}

	// Document generator methods 
	public void beginRecord() { buffer.append(_beginRecordTag); }
	public void endRecord() { buffer.append(_endRecordTag); }

	public void addField(String field) {
		buffer.append(_beginFieldTag);
		buffer.append(field);
		buffer.append(_endFieldTag);
	}
	public void addFieldsHeader(String field) {
		buffer.append(_beginHeaderTag);
		buffer.append(field);
		buffer.append(_endHeaderTag);
	}
	
	public void appendRecord(T object) { _list.add(object); }
	
	public void generateCustomDocument(String beginDocumentTag, String endDocumentTag,
			String beginRecordsTag, String endRecordsTag,
			String beginHeaderTag, String endHeaderTag,
			String beginRecordTag, String endRecordTag,
			String beginFieldTag,String endFieldTag) {
		this._beginDocumentTag = beginDocumentTag;
		this._endDocumentTag = endDocumentTag;
		this._beginRecordsTag = beginRecordsTag;
		this._beginHeaderTag = beginHeaderTag;
		this._endHeaderTag = endHeaderTag;
		this._endRecordsTag = endRecordsTag;
		this._beginRecordTag = beginRecordTag;
		this._endRecordTag = endRecordTag;
		this._beginFieldTag = beginFieldTag;
		this._endFieldTag = endFieldTag;
	}
	
	public void buildDocument(){
		buffer.append(_beginDocumentTag);
		buffer.append(_beginRecordsTag);
		buffer.append(_beginRecordsTag);
		setFieldNamesHeader();
		 concatAllRecords();
		buffer.append(_endRecordsTag);
		buffer.append(_endDocumentTag);	
	}
	
	// private methods 
	private void concatAllRecords() { for (T obj : _list) addRecord(obj); }
	
	// Data Output methods
	public boolean writeToFile(File file) {
		try {
			FileWriter fileWriter = new FileWriter(file);
			fileWriter.write(buffer.toString());
			fileWriter.close();
		} catch (IOException e) { throw new UnsupportedOperationException(); }
		return false;
	}
	
	public String getDocument() { return buffer.toString(); }

	// Abstract methods
	abstract public void addRecord(T object);
	abstract public void setFieldNamesHeader();
}
