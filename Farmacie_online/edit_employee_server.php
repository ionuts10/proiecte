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
$telefon = "";
$functie ="";
$new_email = "";
$old_email = "";
$password_1 = "";
$password_2 = "";

$erori = array();

// Conectare la baza de date

$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");

// Verificare introducere date

if(isset($_POST['old_email'])){
	$old_email = mysqli_real_escape_string($db, $_POST['old_email']);
}
if(isset($_POST['nume'])){
	$nume = mysqli_real_escape_string($db, $_POST['nume']);
}
if(isset($_POST['prenume'])){
	$prenume = mysqli_real_escape_string($db, $_POST['prenume']);
}
if(isset($_POST['telefon'])){
	$telefon = mysqli_real_escape_string($db, $_POST['telefon']);
}
if(isset($_POST['functie'])){
	$functie = mysqli_real_escape_string($db, $_POST['functie']);
}
if(isset($_POST['new_email'])){
	$new_email = mysqli_real_escape_string($db, $_POST['new_email']);
}
if(isset($_POST['password_1'])){
	$password_1 = mysqli_real_escape_string($db, $_POST['password_1']);
}
if(isset($_POST['password_2'])){
	$password_2 = mysqli_real_escape_string($db, $_POST['password_2']);
}

// Validare introducere date

if(empty($old_email) || empty($nume) || empty($prenume) || empty($telefon) || empty($functie) || empty($new_email) || empty($password_1)){
	array_push($erori, "Este necesar sa completati toate campurile!");
}

if($password_1 != $password_2){
	array_push($erori, "Parolele nu sunt identice!");
}

// Verificare baza de date daca exista un angajat cu acest email

$email_check_query = "SELECT * FROM tabela_angajati WHERE email = '$old_email' LIMIT 1";

$results = mysqli_query($db, $email_check_query);
$email_db = mysqli_fetch_assoc($results);

if(isset($_POST['reg_user'])){
	if($email_db){
		if($email_db['email'] === $old_email){
			if(count($erori) == 0){
	
				$password = password_hash($password_1, PASSWORD_DEFAULT); // Criptare parola
				$query_inregistrare = "UPDATE tabela_angajati SET nume = '$nume', prenume = '$prenume', telefon = '$telefon', functie = '$functie', email = '$new_email', parola = '$password' WHERE email = '$old_email'";
				mysqli_query($db, $query_inregistrare);
				header('location: employees.php');
				exit();
				
			}
		}
		else{
			array_push($erori, "Adresa de email nu exista!");
		}
	}
}

?>