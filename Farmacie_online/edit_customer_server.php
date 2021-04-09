<?php

session_start();

if(!isset($_SESSION['email'])){
	$_SESSION['msg'] = "Trebuie sa fi conectat pentru a vizualiza aceasta pagina.";
	header('location: login.php');
	exit();
}

// Initializare variabile

$nume = "";
$prenume = "";
$data_nasterii = "";
$sex ="";
$new_email = "";
$old_email = "";
$telefon = "";
$judet = "";
$oras ="";
$adresa = "";
$adresa_facturare = "";
$abonat_newsletter = "";

$erori = array();

// Conectare la baza de date

$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");

// Inregistrare angajati


if(isset($_POST['old_email'])){
	$old_email = mysqli_real_escape_string($db, $_POST['old_email']);
}
if(isset($_POST['nume'])){
	$nume = mysqli_real_escape_string($db, $_POST['nume']);
}
if(isset($_POST['prenume'])){
	$prenume = mysqli_real_escape_string($db, $_POST['prenume']);
}
if(isset($_POST['data_nasterii'])){
	$data_nasterii = mysqli_real_escape_string($db, $_POST['data_nasterii']);
}
if(isset($_POST['sex'])){
	$sex = mysqli_real_escape_string($db, $_POST['sex']);
}
if(isset($_POST['new_email'])){
	$new_email = mysqli_real_escape_string($db, $_POST['new_email']);
}
if(isset($_POST['telefon'])){
	$telefon = mysqli_real_escape_string($db, $_POST['telefon']);
}
if(isset($_POST['judet'])){
	$judet = mysqli_real_escape_string($db, $_POST['judet']);
}
if(isset($_POST['oras'])){
	$oras = mysqli_real_escape_string($db, $_POST['oras']);
}
if(isset($_POST['adresa'])){
	$adresa = mysqli_real_escape_string($db, $_POST['adresa']);
}
if(isset($_POST['adresa_facturare'])){
	$adresa_facturare = mysqli_real_escape_string($db, $_POST['adresa_facturare']);
}
if(isset($_POST['abonat_newsletter'])){
	$abonat_newsletter = mysqli_real_escape_string($db, $_POST['abonat_newsletter']);
}

// Validare inregistrare

if(empty($nume) || empty($prenume) || empty($telefon) || empty($abonat_newsletter) || empty($adresa_facturare) || empty($adresa) || empty($oras) || empty($judet) || empty($data_nasterii) || empty($sex) || empty($old_email) || empty($new_email)){
	array_push($erori, "Este necesar sa completati toate campurile!");
}

// Verificare baza de date daca exista un client cu acest email

$email_check_query = "SELECT * FROM tabela_clienti WHERE email = '$old_email' LIMIT 1";

$results = mysqli_query($db, $email_check_query);
$email_db = mysqli_fetch_assoc($results);

if(isset($_POST['reg_user'])){
	if($email_db){
		if($email_db['email'] === $old_email){
			if(count($erori) == 0){
	
				$query_inregistrare = "UPDATE tabela_clienti SET nume = '$nume', prenume = '$prenume', data_nasterii = '$data_nasterii', sex = '$sex', email = '$new_email', telefon = '$telefon', judet = '$judet', oras = '$oras', adresa = '$adresa', adresa_facturare = '$adresa_facturare', abonat_newsletter = '$abonat_newsletter' WHERE email = '$old_email'";
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