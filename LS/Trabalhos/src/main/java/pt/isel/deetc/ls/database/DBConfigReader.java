package pt.isel.deetc.ls.database;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class DBConfigReader {
  private static final String DEFAULT_CONFIG_FILE = "default";
  private static final String CONFIG_FILE_EXTENTION = ".properties";
  private Properties _configFile;

  public DBConfigReader () throws FileNotFoundException, IOException {
      this(DEFAULT_CONFIG_FILE);
  }

  public DBConfigReader (String fileConfig ) throws FileNotFoundException, IOException {
    if (fileConfig == null) throw new NullPointerException("Invalid Configuration filename!");
    readConfFile(fileConfig+CONFIG_FILE_EXTENTION);
  }

  private void readConfFile (String fileConfig) throws FileNotFoundException, IOException {
    File inputFile = new File(fileConfig);
    Properties p  = new Properties();
    if (!inputFile.exists()){
    	System.out.println(inputFile.toString() + " not found!!");
        if (fileConfig.compareTo(DEFAULT_CONFIG_FILE+CONFIG_FILE_EXTENTION) == 0){
            throw new FileNotFoundException("The configuration file was not found!");
        }else{
            inputFile = new File(DEFAULT_CONFIG_FILE+CONFIG_FILE_EXTENTION);
        }
    }
    FileInputStream readFile = new FileInputStream(fileConfig);
    p.loadFromXML(readFile);
    _configFile= p;
  }

  public Properties getConfigFile(){
      return _configFile;
  }
}

