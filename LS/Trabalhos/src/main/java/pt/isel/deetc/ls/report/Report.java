package pt.isel.deetc.ls.report;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

abstract public class Report<T> {

	private String _beginDocumentTag, _endDocumentTag;
	private String _beginRecordsTag, _endRecordsTag;
	private String _beginRecordTag, _endRecordTag;
	private String _beginFieldTag, _endFieldTag;
	public StringBuffer buffer;
	private ArrayList<T> _list;

	public Report(ArrayList<T> list) {
		this.buffer = new StringBuffer();
		this._list = list;
	}
	public Report(){
		this.buffer = new StringBuffer();
	}

	public void setTags(String beginDocumentTag, String endDocumentTag,
			String beginRecordsTag, String endRecordsTag,
			String beginRecordTag, String endRecordTag, String beginFieldTag,
			String endFieldTag) {
		this._beginDocumentTag = beginDocumentTag;
		this._endDocumentTag = endDocumentTag;
		this._beginRecordsTag = beginRecordsTag;
		this._endRecordsTag = endRecordsTag;
		this._beginRecordTag = beginRecordTag;
		this._endRecordTag = endRecordTag;
		this._beginFieldTag = beginFieldTag;
		this._endFieldTag = endFieldTag;

	}

	public void beginRecord() {
		buffer.append(_beginRecordTag);
	}

	public void endRecord() {
		buffer.append(_endRecordTag);
	}

	public void addField(String field) {
		buffer.append(_beginFieldTag);
		buffer.append(field);
		buffer.append(_endFieldTag);
	}

	public String getDocument() {
		return buffer.toString();
	}

	public boolean writeToFile(File file) {
		try {
			FileWriter fileWriter = new FileWriter(file);
			fileWriter.write(buffer.toString());
			fileWriter.close();
		} catch (IOException e) {
			// Treat Exception
		}
		return false;
	}

	public void buildRecords() {
		buffer.append(_beginDocumentTag);
		buffer.append(_beginRecordsTag);
		for (T obj : _list)
			addRecord(obj);
		buffer.append(_endRecordsTag);
		buffer.append(_endDocumentTag);
	}
	
	public void buildRecords(ArrayList<T> list) {
		buffer.append(_beginDocumentTag);
		buffer.append(_beginRecordsTag);
		for (T obj : list)
			addRecord(obj);
		buffer.append(_endRecordsTag);
		buffer.append(_endDocumentTag);
	}
	
	// Abstract methods
	abstract public void addRecord(T object);
	abstract public void show(ArrayList<T> list);

}
