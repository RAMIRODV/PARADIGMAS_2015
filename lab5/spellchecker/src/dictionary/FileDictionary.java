package dictionary;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.File;
import java.io.PrintWriter;
import java.util.List;

import word.Word;

    /**
	 * Esta classe representa un diccionario que se carga desde un archivo de
	 * texto. Es una subclase de Dictionary.
     * Conforma el package dictionary.
	 */
public class FileDictionary extends Dictionary {
	
    /** Atributo: Path del diccionario. */
    private String loadPath;

    /**
     * Constructor por defecto.
     * El path por defecto es el directorio actual y el nombre del archivo es
     * dict.txt.
     */
    public FileDictionary() {
        this.loadPath = "dict.txt";
    }

    /**
     * Constructor de la clase con la ruta del directorio especifico.
     * @param s: Path del archivo especificado por el usuario.
     */
    public FileDictionary(String s) {
        this.loadPath = s;
    }

     /** Metodos */

    /**
     * Metodo load: Carga un diccionario desde un archivo.
     * @param file: Nombre del archivo diccionario.
     */
    public void load(String file) {
        try {
            int i;    // Indice.
            boolean flag;    // Bandera de error.
            File f = new File(file);
            FileReader fr = new FileReader(f);
            // Lee el primer caracter y lo almacena como un int.
            int c = fr.read();
            String str;
            StringBuilder sb = new StringBuilder();
            // Recorre el archivo hasta encontrar el -1 que marca el final de
            // un archivo.
            while (c != -1) {
                if (c != '\n' && c != '\r') {
                    sb.append((char)c);
                }
                if (c == '\n') {
                    str = sb.toString();
                    i = 0;
                    flag = false;
                    if (str.length() < 30) {    // Tamaño maximo de palabra.
                        while (i < str.length()) {
                            if (!Character.isLetter(str.charAt(i))) {    // Verifica que sean caracteres alfabeticos.
                                flag = true;    // Palabra no valida.
                                break;
                            }
                            i++;
                        }
                    } else { flag = true; }    // Palabra no valida.
                    if (flag) {
                        System.out.println("Error: El diccionario no es valido.");
                        System.exit(1);    // Salida forzosa del programa por ingresar un diccionario no valido.
                    }
                    Word w = new Word(str);
                    this.add(w);
                    // Limpia el stringBuilder sb.
                    sb.delete(0, str.length());
                }
                c = fr.read();
            }
            // Cierra el archivo.
            fr.close();
        }
        catch (Exception e) {
            System.out.println("Cargando diccionario por defecto: " + this.loadPath);    // No se le pasa como argumento un diccionario.
        }
    }

    /**
     * Metodo save: Guarda el diccionario a un archivo por defecto llamado
     *               dict.txt.
     * @param void
     * @throws FileNotFoundException: Levanta una exception si no pudo abrir
     *                                el archivo.
     */
    public void save() {
        if (this.loadPath == "") {
            save(this.loadPath + "dict.txt"); // Si es el path completa al archivo.
        }
        else {
            save(this.loadPath);
        }
    }

    /**
     * Metodo save: Guarda un diccionario a un archivo especifico.
     * @param fileName: Nombre de archivo con el que se guardara el diccionario.
     * @throws FileNotFoundException: Levanta una exception si no encuentra el
     *                                archivo.
     */
    public void save(String fileName) {
        try {
            int tam;
            File newFile = new File(fileName);
            PrintWriter f = new PrintWriter(newFile);
            List <String> ls = this.toStringList();
            tam = ls.size();
            for (int i=0; i<tam; i++) {
                f.println(ls.get(i));
            }
            f.close();
        }
        catch (Exception e) {
            System.out.println("Error:" + e.getMessage());
            System.exit(1);    // Salida forzosa del programa.
        }
    }
}
