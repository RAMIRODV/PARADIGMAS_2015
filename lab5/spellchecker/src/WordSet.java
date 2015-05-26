public class WordSet {
    private HashSet hs;

    // Constructor
    public WordSet() {
        this.hs = new HashSet();
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

    public Iterator iterator() {
        return this.hs.iterator();
    }

    public int size() {
        return this.hs.size();
    }
}
