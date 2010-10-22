package pt.isel.deetc.lmp;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;


public class GlobalConfigurationProprieties implements DBConfig{


    /**
     * Configuração dos parametros da ligação a uma Base de Dados.
     * Devolve null se alguns dos parametros fôr inválido.
     * @param host
     * @param database
     * @param port
     * @param username
     * @param password
     * @return
     */
    public static Properties createConfigProprieties (String host, String database, int port, String username, String password){
        if (host == null || database == null || port <=0 || port >= 65536)
            return null;
        Properties configFileOutput = new Properties();
        configFileOutput.setProperty(_HOST, host);
        configFileOutput.setProperty(_DB, database);
        configFileOutput.setProperty(_PORT, Integer.toString(port));
        configFileOutput.setProperty(_USER, username);
        configFileOutput.setProperty(_PW, password);
        return configFileOutput;
    }
    /**
     * Criação do ficheiro com a Configuração da Ligação à Base de Dados
     * @param configFileOutput
     */
    public static void writeConfigFile(Properties configFileOutput){
            String dbConfigFile = configFileOutput.getProperty(_HOST)+_FILENAME;
            ConfigurationFile.writeConfigFile(configFileOutput,_DB_CONFIG_PATH,dbConfigFile,_DB_CONFIG_FILE_COMMENT);
    }
    /**
     * Define uma configuração como configuração por omissão
     * @param configFileOutput
     */
    public static void setDefaultConfigFile (Properties configFileOutput){
        ConfigurationFile.writeConfigFile(configFileOutput,_DB_CONFIG_PATH, _DEFAULT_CONFIG_FILE,_DB_CONFIG_FILE_COMMENT);
    }

    /**
     * Lê o ficheiro de configuração por omissão.
     * @return
     */
    public static Properties loadDefaultConfigFile(){
        return loadConfigFile(_DEFAULT_CONFIG_FILE);
    }
    /**
     * Função que devolve um array com a lista de ficheiros de configuração da
     * ligação a Base de Dados.
     * @return
     */
    public static String[] getConfigFiles(){
        File dirPath = new File(_DB_CONFIG_PATH);
        String[] configFiles;
        FilenameFilter filter;

        filter = new FilenameFilter() { public boolean accept(File dir, String name) { return name.endsWith(_FILENAME); } };
        configFiles = dirPath.list(filter);
        return configFiles;
    }

    /**
     * Função que lista todos os ficheiros de Configuração da ligação a Base de
     * Dados.
     */
    public static void listConfigFiles(String[] configFiles){
        for (int f = 0 ; f< configFiles.length;++f){
            System.out.println("["+f+"] - " + configFiles[f] );
        }
    }
    /**
     * Escolhe de uma lista de ficheiros qual o que deve carregar
     * @return
     */
    public static String chooseConfigFile(){
        String[] configFiles = getConfigFiles();
        listConfigFiles(configFiles);

        System.out.println("Escolha um ficheiro de Configuração!");
        int choice=-1;
        try {
            choice = System.in.read() - '0';
        } catch (IOException ex) {
            Logger.getLogger(GlobalConfigurationProprieties.class.getName()).log(Level.SEVERE, null, ex);
        }

        if ( choice >= 0 && choice < configFiles.length){
            System.out.println("O ficheiro escolhido foi: "+configFiles[choice]);
            return configFiles[choice];
        } else{
            System.out.println("Opção inválida!");
        }
        return null;
    }

    /**
     * Carrega e valida as Propriedades obtidas do ficheiro de configuração.
     * Retorna null caso haja problemas.
     * @param filename
     * @return
     */
    public static Properties loadConfigFile(String filename){
        Properties configFileInput = ConfigurationFile.readConfigFile(_DB_CONFIG_PATH,filename);
        if (configFileInput == null) return null;
        String sPort =configFileInput.getProperty(_PORT);
        int port = Integer.parseInt((sPort == null)?"-1":sPort);

        if (configFileInput.getProperty(_HOST) == null ||configFileInput.getProperty(_DB) == null || port <=0 || port >= 65536 ){
            System.out.println("Paramentros de Configuração inválidos");
            return null;
        }
        return configFileInput;
    }
    


    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //System.out.println(createDefaultConfigFile().toString());
        //System.out.println(createDefaultConfigFile().toString());
        //System.out.println(loadDefaultConfigFile().toString());
        String host = chooseConfigFile();
        if(host != null)
        System.out.println(loadConfigFile(host).toString());
        //listConfigFiles();
    }
}
