package word;

import java.util.HashSet;
import java.util.Iterator;

    /**
     * Esta clase proporciona una coleccion de words.
     * Conforma el package word.
     */
public class WordSet {

    /** Atributo: Objeto HashSet. */
    private HashSet <Word> hs;

    /**
     * Constructor de la coleccion.
     */
    public WordSet() {
        this.hs = new HashSet <Word>();
    }

    /** Metodos */

    /**
     * NAME : Metodo add
     *
     * DESCRIPTION : Agrega un word a la coleccion.
     * @param w    El word a agregar.
     * @return void
     */
    public void add(Word w) {
        // ATENCION: hs.add(obj)  devuelve un booleano.
        this.hs.add(w);
    }

    /**
     * NAME : Metodo add
     *
     * DESCRIPTION : Verifica si el word se encuentra en la coleccion.
     * @param w    El word a verificar si se encuentra en la coleccion.
     * @return true Si el word ya existe en la coleccion, false en caso contrario.
     */
    public boolean contains(Word w) {
        return this.hs.contains(w);
    }

    /**
     * NAME : Metodo clear
     *
     * DESCRIPTION : Elimina todos los elementos de la coleccion.
     * @param void
     * @return void
     */
    public void clear() {
        this.hs.clear();
    }

    /**
     * NAME : Metodo iterator
     *
     * DESCRIPTION : Devuelve un iterator de tipo Word.
     * @param void
     * @return Iterator de la coleccion.
     */
    public Iterator<Word> iterator() {
        return this.hs.iterator();
    }

    /**
     * NAME : Metodo iterator
     *
     * DESCRIPTION : Devuelve el tamano de la coleccion.
     * @param void
     * @return Tamano entero de la coleccion.
     */
    public int size() {
        return this.hs.size();
    }
}
