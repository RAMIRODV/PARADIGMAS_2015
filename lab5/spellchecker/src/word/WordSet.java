package word;

import java.util.HashSet;
import java.util.Iterator;

public class WordSet {
    private HashSet <Word> hs;

    // Constructor
    public WordSet() {
        this.hs = new HashSet <Word>();
    }

    public void add(Word w) {
        // ATENCION: hs.add(obj)  devuelve un booleano.
        this.hs.add(w);
    }

    public boolean contains(Word w) {
        return this.hs.contains(w);
    }

    public void clear() {
        this.hs.clear();
    }

    public Iterator<Word> iterator() {
        return this.hs.iterator();
    }

    public int size() {
        return this.hs.size();
    }
}