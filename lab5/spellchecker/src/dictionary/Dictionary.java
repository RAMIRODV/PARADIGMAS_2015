package dictionary;

import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

import word.Word;
import word.WordSet;

    /**
	 * Esta clase representa al diccionario de palabras.
     * Es una clase abstracta.
     * Conforma el package dictionary.
     */
public abstract class Dictionary {

    /** Atributo: Establece un objeto WordSet. */
	protected WordSet dic;

    /**
     * Constructor de la clase.
     * Genera un objeto WorSet.
     */
	public Dictionary() {
		 this.dic = new WordSet();
	}

    /** Metodos */

    /**
     * NAME : Metodo add
     *
     * DESCRIPTION : Agrega una palabra al diccionario.
     * @param word    Palabra a ser agregada.
     * @return void
     */
	public void add(Word word) {
		this.dic.add(word);
	}

    /**
     * NAME : Metodo contains
     *
     * DESCRIPTION : Devuelve el tamaño del diccionario.
     * @param word    Palabra a verificar.
     * @return boolean    Si la palabra es conocida en el diccionario true. Si no, false.
     */
	public boolean contains(Word word) {
		return this.dic.contains(word);
	}

    /**
     * NAME : Metodo clear
     *
     * DESCRIPTION : Borra el diccionario.
     * @param void
     * @return void
     */
	public void clear() {
		this.dic.clear();
	}

    /**
     * NAME : Metodo fronStringList
     *
     * DESCRIPTION : Inserta en el diccionario, todos los elementos
     *               pertenecientes a una lista de strings, pasada
     *               como argumento.
     * @param list    Lista de strings.
     * @return void
     */	
	public void fronStringList(List<String> list) {
	    int tam = list.size();    // Tamaño de la lista.
        for (int i=0; i<tam; i++) {
            Word w = new Word(list.get(i));    // Crea un Word por cada elemento de la lista.
            this.dic.add(w);    // Lo agrega al diccionario.
        }
	}

    /**
     * NAME : Metodo toString
     *
     * DESCRIPTION : Retorna una lista de string,
     *               de todas las palabras que pertenecen al diccionario.
     * @param void
     * @return List<String>    Lista de strings: Palabras que posee el diccionario.
     */
	public List<String> toStringList() {
		int tam = this.dic.size();    // Tamaño del diccionario.
		List<String> list = new ArrayList<String>();   // Objeto lista.
		Iterator<Word> q = this.dic.iterator();    // Objeto iterador.
		for (int i=0; i<tam; i++) {
			Word word = q.next();    // Devuelve el proximo objeto Word.
			String add_word = word.getWord();    // Lo transforma en String.
			list.add(add_word);    // Lo agrega a la lista.
		}
		return list;
	}

    /**
     * NAME : Metodo size
     *
     * DESCRIPTION : Devuelve el tamaño del diccionario.
     * @param void
     * @return int    Cantidad de palabras que posee el diccionario.
     */
	public int size() {
		return this.dic.size();
	}
}
