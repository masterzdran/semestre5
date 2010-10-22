package pt.isel.deetc.ls.database;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.SQLException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.microsoft.sqlserver.jdbc.SQLServerException;

public class DBConfigWriter {
	private static final String CONFIG_FILE_EXTENTION = ".properties";
    private static final String DEFAULT_CONFIG_FILE = "default";
    private static final String CONFIG_FILE_COMMENT = "Configuration File";
    private static final String _HOST = "host";
    private static final String _DB = "database";
    private static final String _PORT = "port";
    private static final String _USER = "username";
    private static final String _PW = "password";

    public DBConfigWriter(String username,String password,String host,String port,String database) throws FileNotFoundException, IOException {
//    	if (username == null || password == null ||host== null || port== null||database==null)
//    		return ;
		Properties config = new Properties();
		config.put(_HOST, host);
		config.put(_DB, database);
		config.put(_PORT, port);
		config.put(_USER, username);
		config.put(_PW, password);
		writeConfigFile(host, config);
    }
    
    public DBConfigWriter(Properties config) throws FileNotFoundException, IOException {
        this(DEFAULT_CONFIG_FILE, config);
    }

    public DBConfigWriter(String host, Properties config) throws FileNotFoundException, IOException {
        if (host == null) {
            throw new NullPointerException("Invalid Configuration filename!");
        }

        writeConfigFile(host, config);
    }

    private void writeConfigFile(String fileConfig, Properties config) throws FileNotFoundException, IOException {
        FileOutputStream fileWrite = new FileOutputStream(fileConfig+CONFIG_FILE_EXTENTION);
        config.storeToXML(fileWrite, CONFIG_FILE_COMMENT);
    }

}
