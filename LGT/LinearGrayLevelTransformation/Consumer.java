package LinearGrayLevelTransformation;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Consumer extends Thread {
	
	// Numele fisierului primit ca argument in care va fi facuta scrierea imaginii prelucrate
	private String outputFile;
	
	// Imaginea ce va fi scrisa
	private BufferedImage processedImage;
	
	// Constructorul clasei Consumer
	public Consumer(String outputFile, BufferedImage processedImage) {
		this.outputFile = outputFile;
		this.processedImage = processedImage;
	}
	
	@Override
	public void run() {
		synchronized(Application.lock) {
			try {
				System.out.println("\nThread-ul scrierii imaginii finale a fost pornit si asteapta finalizarea prelucrarii\n");
				
				// Thread-ul este in functiune, insa asteapta apelarea notifyAll() din interiorul metodei runApplication, apelare ce semnalizeaza finalizarea prelucrarii
				Application.lock.wait();
				
				// Scrierea imaginii in fisierul outputFile
				File file = new File(outputFile);
				ImageIO.write(processedImage, "bmp", file);
				try {
					Thread.currentThread().sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println("\nScrierea noii imagini a fost efectuata cu succes!\n"); 
				
			} catch(InterruptedException | IOException e) {
				e.printStackTrace();
			}
		}
		
		
	}
}
