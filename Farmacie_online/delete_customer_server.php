<?php

session_start();

if(!isset($_SESSION['email'])){
	$_SESSION['msg'] = "Trebuie sa fi conectat pentru a vizualiza aceasta pagina.";
	header('location: login.php');
	exit();
}

// Initializare variabile

$email = "";

$erori = array();

// Conectare la baza de date

$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");

// Preluare email din form

if(isset($_POST['email'])){
	$email = mysqli_real_escape_string($db, $_POST['email']);
}

// Verificare daca emailul a fost preluat

if(empty($email)){
	array_push($erori, "Este necesar sa completati toate campurile!");
}

// Verificare baza de date daca exista un client cu acest email

$email_check_query = "SELECT * FROM tabela_clienti WHERE email = '$email' LIMIT 1";

$results = mysqli_query($db, $email_check_query);
$email_db = mysqli_fetch_assoc($results);

if(isset($_POST['reg_user'])){
	if($email_db){
		if($email_db['email'] === $email){
			if(count($erori) == 0){
	
				$query_inregistrare = "DELETE FROM tabela_clienti WHERE email = '$email'";
				mysqli_query($db, $query_inregistrare);
				header('location: customers.php');
				exit();
				
			}
		}
		else{
			array_push($erori, "Adresa de email nu exista!");
		}
	}
}

?>