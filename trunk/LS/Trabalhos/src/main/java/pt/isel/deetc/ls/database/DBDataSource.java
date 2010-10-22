package pt.isel.deetc.ls.database;

import com.microsoft.sqlserver.jdbc.SQLServerDataSource;
import com.microsoft.sqlserver.jdbc.SQLServerException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.sql.Connection;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

public class DBDataSource {
    private final String _HOST = "host";
    private final String _DB = "database";
    private final String _PORT = "port";
    private final String _USER = "username";
    private final String _PW = "password";
    private Properties _configFile;
    private SQLServerDataSource _datasourse;
    private static final String DEFAULT_CONFIG_FILE = "default";
    
    public DBDataSource() throws FileNotFoundException, IOException {
    	//this(InetAddress.getLocalHost().getHostName());
    	this(DEFAULT_CONFIG_FILE);
    }

    public DBDataSource(String host) throws FileNotFoundException, IOException {
        try {
            DBConfigReader dbcr = new DBConfigReader(host);
            _configFile = dbcr.getConfigFile();
            this.setDataSource();

        } catch (UnknownHostException ex) {
            Logger.getLogger(DBDataSource.class.getName()).log(Level.SEVERE, null, ex);
            _configFile = null;
        }
    }

    private void setDataSource() {
        if (!hasValidKeyNames(_configFile)) {
            return;
        }

        _datasourse = new SQLServerDataSource();
        _datasourse.setServerName(_configFile.getProperty(_HOST));
        _datasourse.setDatabaseName(_configFile.getProperty(_DB));
        _datasourse.setPortNumber(Integer.parseInt(_configFile.getProperty(_PORT)));
        _datasourse.setUser(_configFile.getProperty(_USER));
        _datasourse.setPassword(_configFile.getProperty(_PW));

    }

    private boolean hasValidKeyNames(Properties config) {
        if (config == null || config.isEmpty()) {
            return false;
        }
        String v;
        int p;
        return !(   !(config.containsKey(_DB) && ((v=config.getProperty(_DB)) != null) && !(v.isEmpty()))
                ||  !(config.containsKey(_HOST)&& ((v=config.getProperty(_HOST)) != null) && !(v.isEmpty()))
                ||  !(config.containsKey(_PORT)&& ((v=config.getProperty(_PORT)) != null) && !(v.isEmpty()) && (p=Integer.parseInt(v))>0 && (p<65535))
                ||  !(config.containsKey(_USER)&& ((v=config.getProperty(_USER)) != null) && !(v.isEmpty()))
                ||  !(config.containsKey(_PW)  && ((v=config.getProperty(_PW)) != null) && !(v.isEmpty()))
                );
    }

    public SQLServerDataSource getDataSource() throws SQLServerException {
        if (_datasourse == null) {
            this.setDataSource();
        }
        return _datasourse;

    }
}
