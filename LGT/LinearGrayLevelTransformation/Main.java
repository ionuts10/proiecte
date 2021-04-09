package LinearGrayLevelTransformation;

import java.io.IOException;

public class Main {
	
	public static void main(String[] args) throws IOException{
		
		try{
			// Preluarea numelor fisierelor de input si output din linia de comanda
			String inputFile = args[0];
			String outputFile = args[1];
			
			// Pornirea aplicatiei, respectand design pattern-ul singleton
			Application.setApplication(inputFile, outputFile);
			Application myApp = Application.getInstance();
			myApp.runApplication();
			
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("Numarul de argumente este insuficient!");

		}
		
	}

}

