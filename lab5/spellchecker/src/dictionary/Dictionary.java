package dictionary;

import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

import word.Word;
import word.WordSet;

public abstract class Dictionary {
	protected WordSet dic;
	
	public Dictionary() {
		 this.dic = new WordSet();
	}
	
	public void add(Word word) {
		this.dic.add(word);
	}
	
	public boolean contains(Word word) {
		return this.dic.contains(word);
	}
	
	public void clear() {
		this.dic.clear();
	}
	
	public void fronStringList(List<String> list) {
	    int tam = list.size();
            // Word wLs[] = list.toArray();  // Lista de Word
            for (int i=0; i<tam; i++) {
                Word w = new Word(list.get(i));
                this.dic.add(w);
            }
	}
	
	public List<String> toStringList() {
		int tam = this.dic.size();
		List<String> list = new ArrayList<String>();
		Iterator<Word> q = this.dic.iterator();
		for (int i=0; i<tam; i++) {  //while (this.dic.hasNext()) {  (VER!!!!)
			Word word = q.next();
			String add_word = word.getWord();
			list.add(add_word);
		}
		return list;
	}
	
	public int size() {
		return this.dic.size();
	}
}
