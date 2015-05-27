import java.io.*;
import java.util.Scanner;
import document.Document;
import dictionary.Dictionary;
import dictionary.FileDictionary;
import dictionary.MemDictionary;
import word.Word;

public class Spellchecker {

	public Spellcheker() {
		//????
	}
	
	public static Word consultUser(Word word, Dictionary main_dict, Dictionary ignored) {
		try {
			do {
				System.out.println ("Palabra no reconocida: "+word+" Aceptar (a) - Ignorar (i) - Reemplazar (r): ");
				Scanner reader = new Scanner(System.in);
				char c = reader.next(".").charAt(0);
			} while (c != 'a' && c != 'i' && c != 'r');
			String new_word;
			Scanner reader2 = new Scanner(System.in);
			switch (c) {
			case 'a':
				main_dict.add(word);
				break;
			case 'i':
				ignored.add(word);
				break;
			case 'r':
				System.out.println ("Ingrese una nueva palabra: ");
				new_word = reader2.nextLine();
				word = new_word;
				break;
			}
			return word;
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
	}

	public static void processDocument(String fname_in, String fname_out, Dictionary main_dict, Dictionary ignored) {
		try {
			Word current_word;
			Document doc = new Document(fname_in, fname_out);
			while (flag) {
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
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
			
	}

	public static void main(String[] args) {
		String dict_path;
		int i = args.length();
		if (i < 1) {
			System.out.println ("spellchecker.java: nro de argumentos erroneo. Deben ser <documento> [<diccionario>].");
			System.exit();
		}
		dict_path = (argc >=2) ? args[1] : "dict.txt";
		FileDictionary main_dict = new FileDictionary();
		main_load.load(dict_path);
		MemDictionary ignored = new MemDictionary();
		processDocument(args[0], "out.txt", main_dict, ignored);
		main_dict.save();
		main_dict.clear();
		ignored.clear();
		System.out.println ("El documento "+args[1]+ " ha sido procesado. Resultados en out.txt");
	}	
}