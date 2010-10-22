package pt.isel.deetc.lmp;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Nuno Alexandre Cancelo
 */
public class ConfigurationFile {
     /**
     * Criação do ficheiro com a Configuração da Ligação à Base de Dados
     * @param configFileOutput
     * @param path
     * @param filename
     * @param comments
     */
    public static void writeConfigFile(Properties configFileOutput, String path, String filename, String comments){
        try {
            String dbConfigFile = path+"/"+filename;
            FileOutputStream file = new FileOutputStream(dbConfigFile);
            configFileOutput.storeToXML(file,comments);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(GlobalConfigurationProprieties.class.getName()).log(Level.SEVERE, null, ex);
        }catch (IOException ex) {
                Logger.getLogger(GlobalConfigurationProprieties.class.getName()).log(Level.SEVERE, null, ex);
        }
    }


    /**
     * Função que carrega os parametros de configuração de acesso à Base de Dados.
     * Retorna null se o ficheiro não existe, se não é possivel ler o ficheiro,
     * se o ficheiro tem problemas com a descrição de alguns dos parametros ou se
     * o@param filename for null.
     *
     * @param path
     * @param filename
     * @return
     */
    public static Properties readConfigFile(String path, String filename){
        if (filename == null ) return null;
        String dbConfigFile = path+"/"+filename;
        Properties configFileInput = new Properties();
        try {
            FileInputStream file = new FileInputStream(dbConfigFile);
            configFileInput.loadFromXML(file);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(GlobalConfigurationProprieties.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }catch (IOException ex) {
                Logger.getLogger(GlobalConfigurationProprieties.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
      return configFileInput;
    }


}
