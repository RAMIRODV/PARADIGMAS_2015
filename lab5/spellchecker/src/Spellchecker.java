import java.io.IOException;
import java.util.Scanner;

import document.Document;
import dictionary.Dictionary;
import dictionary.FileDictionary;
import dictionary.MemDictionary;
import word.Word;

public class Spellchecker {

	public Spellchecker() {}
	
	public static Word consultUser(Word word, Dictionary main_dict, Dictionary ignored) {
		String new_word = "";
        try {
            char c;
            //Scanner reader = new Scanner(System.in);
			do {
				System.out.println ("Palabra no reconocida: '"+word.getWord()+"'. Aceptar (a) - Ignorar (i) - Reemplazar (r): ");				
				//c = reader.next(".").charAt(0);
                //reader.reset();
                c = (char) System.in.read();
			} while ((c != 'a') && (c != 'i') && (c != 'r'));
            //reader.close();
			Scanner reader_word = new Scanner(System.in);
			switch (c) {
			case 'a':
				main_dict.add(word);
				break;
			case 'i':
				ignored.add(word);
				break;
			case 'r':
				System.out.println ("Ingrese una nueva palabra: ");
				new_word = reader_word.nextLine();
				break;
			}
            reader_word.close();
		} catch(Exception msg) {
			System.out.println("Error consultUser:" + msg.getMessage());
            System.exit(1);
		};
        Word newWord = new Word(new_word);
	    return newWord;
	}

	public static void processDocument(String fname_in, String fname_out, Dictionary main_dict, Dictionary ignored) {
		try {
			Word current_word = new Word();
			Document doc = new Document(fname_in, fname_out);
			while (true) {
				current_word = doc.getWord();
				if ((current_word.getWord()) == "") {
					break;
				}
				if (!(main_dict.contains(current_word)) && !(ignored.contains(current_word))) {
					current_word = consultUser(current_word, main_dict, ignored);
				}
				doc.putWord(current_word);
			}
			doc.close();
		} catch(Exception msg) {
			System.out.println("Error processDocument:" + msg.getMessage());
            System.exit(1);
		};
			
	}

	public static void main(String[] args) {
		String dict_path;
		int i = args.length;
		if (i < 1) {
			System.out.println ("spellchecker.java: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].");
			System.exit(1);
		}
		dict_path = (i >= 2) ? args[1] : "dict.txt";
		FileDictionary main_dict = new FileDictionary();
		main_dict.load(dict_path);
		MemDictionary ignored = new MemDictionary();
		processDocument(args[0], "out.txt", main_dict, ignored);
		main_dict.save();
		main_dict.clear();
		ignored.clear();
		System.out.println ("El documento "+args[1]+ " ha sido procesado. Resultados en out.txt");
	}	
}
