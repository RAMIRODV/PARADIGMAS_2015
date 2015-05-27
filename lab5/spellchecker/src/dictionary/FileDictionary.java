package dictionary;

import java.io.FileReader;
import java.io.PrintWriter;
import java.util.List;

public class FileDictionary extends Dictionary {
	/**
	 * Esta classe representa un diccionario que se carga desde un archivo de
	 * texto. Es una subclase de Dictionary.
	 * @version 0.1
	 * @author Fernando Copa.
	 * @author Ramiro Della Vedova.
	 */
	
    private String loadPath;

    /**
     * Constructor por defecto.
     * El path por defecto es el directorio actual y el nombre del archivo es
     * dict.txt.
     */
    public FileDictionary() {
        this.loadPath = "";
    }

    /**
     * Constructor de la clase con la ruta del archivo especifico.
     * @param s Path del archivo especificado por el usuario.
     */
    public FileDictionary(String s) {
        this.loadPath = s;
    }

    /**
     * Este metodo carga un diccionario desde un archivo.
     * @param file Nombre del archivo diccionario.
     */
    public void load(String file) {
        try {
            FileReader fr = new FileReader(file);
            // Leo el primer caracter y lo almaceno como un int.
            int c = fr.read();
            String str;
            StringBuilder sb = new StringBuilder();
            // Recorro el archivo hasta encontrar el -1 que marca el final de
            // un archivo.
            while (c != -1) {
                if (c != '\n' && c != '\r') {
                    sb.append((char)c);
                }
                if (c == '\n') {
                    str = sb.toString();
                    Word w = new Word(str);
                    this.add(w);
                    // Limpio el stringBuilder sb.
                    sb.delete(0, str.length()-1);
                }
                c = fr.read();
            }
            // Cierro el archivo.
            fr.close();
        }
        catch (Exception e) {
            System.out.println("Exception leyendo fichero " + file + ": " + e);
        }
    }

    /**
     * Este metodo guarda el diccionario a un archivo por defecto llamado
     * dict.txt.
     */
    public void save() {
        int tam;
        PrintWriter f = new PrintWriter(this.loadPath);

        List <String> l = this.toStringList();
        tam = l.size();
        Word wLs[] = l.toArray();  // Lista de Word
        for (int i=0; i<tam; i++) {
            String s = wLs[i].getWord();
            f.println(s);
        }
        f.close();
    }
// (VER!!!!!!! ---->>>>>> CODIGO REPETIDO!!!!!)
    /**
     * Este metodo guarda un diccionario a un archivo especifico.
     * @param fileName Nombre de archivo con el que se guardara el diccionario.
     */
    public void save(String fileName) {
        int tam;
        PrintWriter f = new PrintWriter(fileName);

        List <String> l = this.toStringList();
        tam = l.size();
        Word wLs[] = l.toArray();  // Lista de Word
        for (int i=0; i<tam; i++) {
            String s = wLs[i].getWord();
            f.println(s);
        }
        f.close();
    }
}