package document;

import java.io.*;
import word.Word;

public class Document {
	private BufferredReader input;
	private BufferredWriter output;
	
	public Document(String fname_in, String fname_out) {
		try {
			File fileIn = new File(fname_in);
			FileReader in = new FileReader(fileIn);
			this.input = new BufferredReader(in);
			File fileOut = new File(fname_out);
			FileWriter out = new FileWriter(fileOut);
			this.output = new BufferredWriter(out);
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
	}
	
	public void close() {
		try {
			this.input.close();
			this.output.close();
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
		
	}
	
	public Word getWord() {
		try {
			char character;
			Word word = new Word();
			int flag = 0;
			PrintWriter put_word = new PrintWriter(this.output);
			while(true)	{
				try {
					character = this.input.readChar();
					if(!Character.isLetter(character)) {
						if(flag == 0) {
							put_word.write(character);
						} else {
							this.input.reset();
							return word;
						}
					} else {
						word = word.concat(character);
						flag = 1;
						this.input.mark();
					}
				} catch (EOFException msg_eof) {
					break;
				};
			}
			return word;
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
	}
	
	public void putWord(Word word) {
		try {
			PrintWriter put_word = new PrintWriter(this.output);
			put_word.write(word);
			put_word.close();
		} catch(IOException msg) {
			System.out.println("Error:"+msg.getMessage());
		};
	}
}