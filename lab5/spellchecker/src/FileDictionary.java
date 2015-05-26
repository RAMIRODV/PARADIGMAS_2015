import java.io.FileReader;
import java.io.PrintWriter;
import java.util.List;

public class FileDictionary extends Dictionary {
    private String loadPath;

    // Constructor con path por defecto.
    public FileDictionary() {
        this.loadPath = "";  // Ruta del dict.txt por defecto.
    }

    // Constructor con path en un String.
    public FileDictionary(String s) {
        this.loadPath = s;
    }

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
