package LinearGrayLevelTransformation;

import java.awt.image.BufferedImage;

public class Application implements Interface{
	
	// Componenta de tip Application ce ajuta la crearea pattern-ului de singleton
	private static Application instance;
	
	// Numele fisierelor de input si de output
	private String inputFile;
	private String outputFile;
	
	// Obiect ce va fi folosit pentru protectia la o eventuala interferenta intre thread-urile Runner si thread-ul Consumer
	public static Object lock;
	
	// Constructor privat al clasei Application
	private Application(String inputFile, String outputFile){
		this.inputFile = inputFile;
		this.outputFile = outputFile;
	}
	
	// Setter pentru clasa Application
	public static void setApplication(String inputFile, String outputFile) {
		// If-ul permite o singura instanta a clasei Application (singleton pattern)
		if (instance == null) {
			instance= new Application(inputFile, outputFile);
		}
	}
	
	// Getter pentru clasa Application
	public static Application getInstance() {
		return instance;
	}
	
	// Metoda ce descrie efectiv rularea aplicatiei
	public void runApplication(){
		
		// Crearea unui obiect de tip producer ce va stoca componenta de tip BufferedImage si vectorul ce contine valorile fiecarui pixel din imagine
		Producer producer = new Producer(inputFile);
		
		// Crearea unui thread si pornirea acestuia pentru producer
		Thread producerThread = new Thread(producer);
		producerThread.start();
		
		try {
			// Se asteapta finalizarea thread-ului producerThread ce se ocupa cu citirea informatiei imaginii
			producerThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		// Obtinerea componentelor stocate in obiectul producer
		BufferedImage imageBMP = producer.getImageBMP();
		int[][] imageRGB = producer.getImageRGB();
		
		// Crearea imaginii ce va stoca imaginea finala, folosind informatii din componenta obtinuta in producer
		BufferedImage processedImage = new BufferedImage(imageBMP.getWidth(), imageBMP.getHeight(), imageBMP.getType());
		
		// Numarul de nuclee ale procesorului
		int cores = Runtime.getRuntime().availableProcessors();
		
		// Crearea obiectului lock
		lock = new Object();
		
		// Crearea thread-ului ce se va ocupa de scrierea imaginii finale
		Thread consumerThread = new Consumer(outputFile, processedImage);
		
		// Crearea thread-urilor, cate unul pentru fiecare nucleu, ce vor prelucra imaginea in paralel
		Thread[] runnerThreads = new Thread[cores];
		for (int i = 0; i < cores; ++i) {
			runnerThreads[i] = new Runner(i, cores, imageRGB, processedImage);
		}
		
		// Pornirea thread-urilor ce vor prelucra imaginea in paralel, pe un numar egal de sectiuni cu cores
		for (int i = 0; i < cores; ++i) {
			runnerThreads[i].start();
		}
		
		// Pornirea thread-ului ce va scrie imaginea; conflictul cu runnerThreads este evitat cu ajutorul obiectului lock
		consumerThread.start();
		
		for (int i = 0; i < cores; ++i) {
			try {
				// Se asteapta finalizarea runnerThreads
				runnerThreads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		
		synchronized(lock) {
			// Odata finalizate runnerThreads, se semnalizeaza catre consumerThread ca isi poate relua procesul de scriere
			lock.notifyAll();
		}
		
		try {
			// Se asteapta finalizarea procesului de scriere
			consumerThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
			
	}
	
}
