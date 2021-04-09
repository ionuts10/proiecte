<?php

session_start();

// Initializare variabile

$nume = "";
$prenume = "";
$telefon = "";
$functie ="";
$email = "";
$password_1 = "";
$password_2 = "";

$erori = array();

// Conectare la baza de date

$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");

// Verificare completare date



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
if(isset($_POST['email'])){
	$email = mysqli_real_escape_string($db, $_POST['email']);
}
if(isset($_POST['password_1'])){
	$password_1 = mysqli_real_escape_string($db, $_POST['password_1']);
}
if(isset($_POST['password_2'])){
	$password_2 = mysqli_real_escape_string($db, $_POST['password_2']);
}

// Validare date

if(empty($nume) || empty($prenume) || empty($telefon) || empty($functie) || empty($email) || empty($password_1)){
	array_push($erori, "Este necesar sa completati toate campurile!");
}

if($password_1 != $password_2){
	array_push($erori, "Parolele nu sunt identice!");
}

// Verificare baza de date daca exista un angajat cu acest email

$email_check_query = "SELECT * FROM tabela_angajati WHERE email = '$email' LIMIT 1";

$results = mysqli_query($db, $email_check_query);
$email_db = mysqli_fetch_assoc($results);

if(isset($_POST['reg_user'])){
	if($email_db){
		if($email_db['email'] === $email){
			array_push($erori, "Adresa de email este deja inregistrata!");
		}
	}
}

// Inregistrare angajat

if(count($erori) == 0){
	
	$password = password_hash($password_1, PASSWORD_DEFAULT); // Criptare parola
	$query_inregistrare = "INSERT INTO tabela_angajati (nume, prenume, telefon, functie, email, parola) VALUES ('$nume', '$prenume', '$telefon', '$functie', '$email', '$password')";
	mysqli_query($db, $query_inregistrare);
	$_SESSION['email'] = $email;
	$_SESSION['succes'] = "Conectare efectuata cu succes!";
	header('location: index.php');
	exit();
}

// Login

if(isset($_POST['login_user'])){
	if(isset($_POST['email'])){
		$email = mysqli_real_escape_string($db, $_POST['email']);
	}

	if(isset($_POST['password'])){
		$password = mysqli_real_escape_string($db, $_POST['password']);
	}

	$query_verify_password = "SELECT parola FROM tabela_angajati WHERE email = '$email'";
	$results_verify_password = mysqli_query($db, $query_verify_password);

	$row = mysqli_fetch_assoc($results_verify_password);
	if(!empty($row)){

		$hash = $row['parola'];
		$ok = password_verify($password, $hash);
		if($ok){
		$_SESSION['email'] = $email;
		$_SESSION['succes'] = "Conectare efectuata cu succes.";
		header('location: index.php');
		exit();
		}
		else{
		array_push($erori, "Combinatia email/parola gresita.");
		}

	}
	
	else{
		array_push($erori, "Combinatia email/parola gresita.");
	}
}
?>