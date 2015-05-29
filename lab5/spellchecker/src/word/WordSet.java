package word;

import java.util.HashSet;
import java.util.Iterator;

/**
 * Esta clase proporciona una coleccion de words.
 */
public class WordSet {
    private HashSet <Word> hs;

    /**
     * Constructor de la coleccion.
     */
    public WordSet() {
        this.hs = new HashSet <Word>();
    }

    /**
     * Este metodo agrega un word a la coleccion.
     *
     * @param w El word a agregar.
     */
    public void add(Word w) {
        // ATENCION: hs.add(obj)  devuelve un booleano.
        this.hs.add(w);
    }

    /**
     * Este metodo verifica si el word se encuentra en la coleccion.
     *
     * @param w El word a verificar si se encuentra en la coleccion.
     * @return true Si el word ya existe en la coleccion, false en caso contrario.
     */
    public boolean contains(Word w) {
        return this.hs.contains(w);
    }

    /**
     * Este metodo elimina todos los lementos de la coleccion.
     */
    public void clear() {
        this.hs.clear();
    }

    /**
     * Este metodo devuelve un iterator de tipo Word.
     *
     * @return Iterator de la coleccion.
     */
    public Iterator<Word> iterator() {
        return this.hs.iterator();
    }

    /**
     * Este metodo devuelve el tamano de la coleccion.
     *
     * @return Tamano entero de la coleccion.
     */
    public int size() {
        return this.hs.size();
    }
}
