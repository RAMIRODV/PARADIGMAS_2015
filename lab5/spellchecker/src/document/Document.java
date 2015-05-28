package document;

import java.io.*;
import word.Word;

    /**
	 * Esta clase representa el documento que se va a procesar. 
     * Conforma el package document.
     */

public class Document {

    /** Atributos */

	private BufferedReader input;    // Documento de entrada.
	private BufferedWriter output;   // Documento de salida.

    /** Constructor */
	
	public Document(String fname_in, String fname_out) {
		try {
			File fileIn = new File(fname_in);    // Objeto file input.
			FileReader in = new FileReader(fileIn);    // Objeto lectura file.
			this.input = new BufferedReader(in);    // Lee un texto de una corriente de caracteres de entrada.
			File fileOut = new File(fname_out);    // Objeto file output.
			FileWriter out = new FileWriter(fileOut);    // Objeto escritura file.
			this.output = new BufferedWriter(out);    // Escribe un texto.
		} catch(IOException msg) {
			System.out.println("Error Document:" + msg.getMessage());
            System.exit(1);    // Salida forzosa del programa.
		};
	}
	
    /** Metodos */

    /**
	 * El metodo close, cierra el documento luego de procesarlo.
     */

	public void close() {
		try {
			this.input.close();    // Cierra el documento de entrada.
			this.output.close();    // Cierra el documento de salida.
		} catch(IOException msg) {
			System.out.println("Error Document.close:" + msg.getMessage());
            System.exit(1);    // Salida forzosa del programa.
		};
		
	}
    /**
     * NAME : Metodo getWord
     *
     * DESCRIPTION : Lee una palabra del archivo de entrada, copiando 
     *               todo caracter de puntuacion precedente al archivo
     *               de salida.
     * @param void
     * @return Word Palabra que se lee desde el archivo.
     * @throws EOFException levanta una excepcion al llegar al EOF.
     * @throws IOException si se produce un error al leer el documento.
     */

    /**
	 * El metodo getWord, lee una palabra del archivo de entrada, copiando 
     * todo caracter de puntuacion precedente al archivo de salida.
     */

	
    public Word getWord() {
        String temp_word = "";		
        try {
            int character;
            int flag = 0;
            while(true)	{
                try {
                    character = this.input.read();
                    if (character == -1) { throw new EOFException(); }    // Al llegar al EOF, se lo señaliza con una excepción.
                    if(!Character.isLetter(character)) {
                        if(flag == 0) {
                            this.output.write(character);
                        } else {
                            this.input.reset();
                            break;
                        }
                    } else {
                        temp_word += (char) character;
                        flag = 1;
                        this.input.mark(30);
                    }
                } catch (EOFException msg_eof) {
                    break;
                };
            }
        } catch(IOException msg) {
            System.out.println("Error Document.getWord:" + msg.getMessage());
            System.exit(1);    // Salida forzosa del programa.
        };
        Word word = new Word(temp_word);
        return word;
    }
	
	public void putWord(Word word) {
		try {
            String word_write = word.getWord();
            this.output.write(word_write);
		} catch(Exception msg) {
			System.out.println("Error Document.putWord:" + msg.getMessage());
            System.exit(1);    // Salida forzosa del programa.
		};
	}
}
