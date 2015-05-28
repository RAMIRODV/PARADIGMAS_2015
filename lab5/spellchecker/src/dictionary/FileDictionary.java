package dictionary;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.File;
import java.io.PrintWriter;
import java.util.List;

import word.Word;

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
     * Constructor de la clase con la ruta del directorio especifico.
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
            File f = new File(file);
            FileReader fr = new FileReader(f);  // <<<<<<<<------ El archivo esta en el path?
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
                    //System.out.println("Agregado: " + w.getWord());
                    // Limpio el stringBuilder sb.
                    sb.delete(0, str.length());
                }
                c = fr.read();
            }
            // Cierro el archivo.
            fr.close();
            // f.close();
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    /**
     * Este metodo guarda el diccionario a un archivo por defecto llamado
     * dict.txt.
     * @throws FileNotFoundException Levanta una exception si no pudo abrir
     * el archivo.
     */
    public void save() {
        if (this.loadPath == "") {
            save(this.loadPath + "dict.txt"); // Si es le path completo al archivo
        }
        else {
            save(this.loadPath);
        }
    }
// (VER!!!!!!! ---->>>>>> CODIGO REPETIDO!!!!!)
    /**
     * Este metodo guarda un diccionario a un archivo especifico.
     * @param fileName Nombre de archivo con el que se guardara el diccionario.
     * @throws FileNotFoundException levanta una exception si no encuentra el
     * archivo.
     */
    public void save(String fileName) {
        try {
            int tam;
            File newFile = new File(fileName);
            PrintWriter f = new PrintWriter(newFile);

            List <String> ls = this.toStringList();
            tam = ls.size();
            //Word wLs[] = l.toArray();  // Lista de Word
            for (int i=0; i<tam; i++) {
                //String s = wLs[i].getWord();
                f.println(ls.get(i));
            }
            f.close();
            //newFile.close();
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
