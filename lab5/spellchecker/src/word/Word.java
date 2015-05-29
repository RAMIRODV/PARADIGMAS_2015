package word;

/**
 * Esta clase representa una palabra sin espacios, ni tabs, ni retornos de
 * linea.
 */
public class Word {
    private String word;
    
    /**
     * Constructor.
     */
    public Word() {
        this.word = "";
    }
    
    /**
     * Constructor Word con el string especificado, este no debe contener
     * espacios en blancos.
     *
     * @param w El string sin espacios.
     */
    public Word(String w) {
        try {
            this.setWord(w);
        }
        catch (ExceptionContainsSpace e) {
            System.out.println("Error: " + e);
        }
    }

    /**
     * Este metodo modifica el Word con el string especificado.
     *
     * @param s String con el cual se modificara Word.
     * @throws ExceptionContainsSpace Si el string contiene espacios.
     */
    public void setWord(String s) throws ExceptionContainsSpace {
        if (s.contains("\\s")) {
            throw new ExceptionContainsSpace("Palabra con espacios.");
        }
        this.word = s;
    }

    /**
     * Este metodo devuelve la palabra en forma de String.
     *
     * @return El string de este word.
     */
    public String getWord() {
        return this.word;
    }

    /**
     * Este metodo rescribe el hashcode adecuandolo para word.
     *
     * @return El valor del hash code.
     */
    @Override
    public int hashCode() {
        final int prime = 31;  // Numero primo.
        int result = 1;
        result = prime * result + ((word == "") ? 0 : word.hashCode());
        return result;
    }
    
    /**
     * Este metodo compara dos clases word.
     *
     * @param obj El objeto a comparar con el actual word.
     * @return true si son iguales los word y false en caso contrario.
     */
    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof Word)) {
            return false;
        }
        Word other = (Word) obj;
        return word.equals(other.getWord());
    }
}
