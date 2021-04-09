package LinearGrayLevelTransformation;

import java.awt.image.BufferedImage;

public class Runner extends Thread {
	
	private int threadId; // Id-ul curent al thread-ului
	private int cores; // Numarul total de nuclee ale procesorului
	private int[][] imageRGB; // Imaginea salvata sub forma unei matrice
	private BufferedImage imageToProcess; // Obiectul de tip BufferedImage ce reprezinta imaginea ce va fi creata in urma transformarii greyscale
	
	// Constructorul clasei Runner
	public Runner(int threadId, int cores, int[][] image, BufferedImage imageToProcess) {
		this.threadId = threadId;
		this.cores = cores;
		this.imageRGB = image;
		this.imageToProcess = imageToProcess;
	}
	
	@Override
	public void run() {
		
		System.out.println("Thread-ul " + threadId + " a inceput prelucrarea");
		
		// Obtinerea inaltimii si a latimii unei imagini
		int height = imageToProcess.getHeight();
		int width = imageToProcess.getWidth();
		
		// Calcularea portiunii de imagine ce va fi procesata in functie de threadId-ul curent
		int range = (int)Math.ceil((double)width / cores);
		int start = threadId * range;
		int stop = Math.min(width - 1, start + range - 1);
		
		// Prelucrarea portiunii de imagine alocata fiecarui thread
		for (int i = start; i <= stop; ++i) {
			for (int j = 0; j < height; ++j) {
				// Obtinerea valorii pixelului de pe pozitia (i, j) din matricea imageRGB
				int pixel = imageRGB[i][j];
				
				// Aplicarea transformarii liniare grey level
				pixel = 16777215 - pixel;
                
                // Setarea pixelului transformat
                imageToProcess.setRGB(i, j, pixel);
			}
		}
		
		try {
			Thread.currentThread().sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Thread-ul " + threadId + " a terminat prelucrarea");
		
	}
	

}
