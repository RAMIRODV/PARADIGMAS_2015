package document;

import java.io.*;
import word.Word;

public class Document {
	private BufferedReader input;
	private BufferedWriter output;
	
	public Document(String fname_in, String fname_out) {
		try {
			File fileIn = new File(fname_in);
			FileReader in = new FileReader(fileIn);
			this.input = new BufferedReader(in);
			File fileOut = new File(fname_out);
			FileWriter out = new FileWriter(fileOut);
			this.output = new BufferedWriter(out);
		} catch(IOException msg) {
			System.out.println("Error Document:" + msg.getMessage());
            System.exit(1);
		};
	}
	
	public void close() {
		try {
			this.input.close();
			this.output.close();
		} catch(IOException msg) {
			System.out.println("Error Document.close:" + msg.getMessage());
            System.exit(1);
		};
		
	}
	
        public Word getWord() {
            String temp_word = "";		
            try {
                int character;
                int flag = 0;
                //PrintWriter put_word = new PrintWriter(this.output); <--------------- Para eso esta el BufferedWriter
                while(true)	{
                    try {
                        character = this.input.read();
                        if (character == -1) { throw new EOFException(); }
                        if(!Character.isLetter(character)) {
                            if(flag == 0) {
                                //put_word.write(character);
                                this.output.write(character);  // <-------------------- Asi se escribe en el buffer out
                            } else {
                                this.input.reset();
                                //put_word.close();  <--------------------------------- Si cierro, se cierra todo el buffer y se queja el putWord
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
                //put_word.close();  <-------------------------------------------------- El buffer se cierra cuando llaman a doc.close() y eso lo maneja Spellc
            } catch(IOException msg) {
                System.out.println("Error Document.getWord:" + msg.getMessage());
                System.exit(1);
            };
            Word word = new Word(temp_word);
            return word;
        }
	
	public void putWord(Word word) {
		try {
            String word_write = word.getWord();
			//PrintWriter put_word = new PrintWriter(this.output); <-------+ Lo mismo de arriba tenes un buffer out
			//put_word.write(word_write);                                  \
			//put_word.close();  ------------------------------------------+
                        this.output.write(word_write);
		} catch(Exception msg) {
			System.out.println("Error Document.putWord:" + msg.getMessage());
            System.exit(1);
		};
	}
}
