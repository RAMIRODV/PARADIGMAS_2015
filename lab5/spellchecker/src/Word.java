public class Word {
    private String word;
    
    // Constructor Word sin parametros.
    public Word() {
        word = "";
    }
    
    // Constructor Word con parametro String.
    public Word(String w) {
        this.word = w;
    }
    public void setWord(String s) {
        this.word = s;
    }

    public String getWord() {
        return this.word;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof(Word)) {
            return false;
        }
        Word other = (Word) obj;
        return word.equals(obj.getWord());
    }

    @Override
    public int hashCode() {
        final int prime = 31;  // Numero primo.
        int result = 1;
        result = prime * result + ((word == "") ? 0 : word.hashCode());
        return result;
    }
}
