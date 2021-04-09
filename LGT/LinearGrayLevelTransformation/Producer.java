package LinearGrayLevelTransformation;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

// Clasa Producer ce implementeaza interfata Runnable
public class Producer implements Runnable{
	
	// Numele fisierului ce contine imaginea
	private String inputFile;
	
	// Componenta ce memoreaza imaginea
	private BufferedImage initialImage = null;
	
	// Componenta ce memoreaza valorile fiecarui pixel din imagine
	private int[][] imageRGB;
	
	// Constructorul clasei Producer
	public Producer(String inputFile){
		this.inputFile = inputFile;
		
	}
	
	@Override
	public void run(){
		try {
			// Citirea imaginii (completa, nu pe sferturi)
			File file = new File(inputFile);
			initialImage = ImageIO.read(file);
		} catch(IOException e) {
			e.printStackTrace();
		}
		
		// Obtinerea latimii si inaltimii imaginii din componenta initialImage 
		int width = initialImage.getWidth();
		int height = initialImage.getHeight();
		
		// Crearea matricei imageRGB ce va retine valorile fiecarui pixel din imagine
		imageRGB = new int[width][height];	
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				imageRGB[i][j] = initialImage.getRGB(i, j);
			}
		}
		
		System.out.println("Citirea imaginii incheiata cu succes! Se incepe prelucrarea acesteia...\n");
		
		try {
			Thread.currentThread().sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	// Getter pt. obtinerea componentei initialImage
	public BufferedImage getImageBMP() {
		return initialImage;
	}

	// Getter pt. obtinerea componentei imageRGB
	public int[][] getImageRGB(){
		return imageRGB;
	}
}
