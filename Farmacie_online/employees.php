<?php

session_start();

if(!isset($_SESSION['email'])){
	$_SESSION['msg'] = "Trebuie sa fi conectat pentru a vizualiza aceasta pagina.";
	header('location: login.php');
	exit();
}

?>

<!DOCTYPE html>
<html>
<head>
	<title>Angajati</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>Nume</th>
					<th>Prenume</th>
					<th>Telefon</th>
					<th>Functie</th>
					<th>Email</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT * FROM tabela_angajati ORDER BY nume ASC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["nume"];
					        $field2name = $row["prenume"];
					        $field3name = $row["telefon"];
					        $field4name = $row["functie"];
					        $field5name = $row["email"]; 

					        echo '<tr> 
					                  <td>'.$field1name.'</td> 
					                  <td>'.$field2name.'</td> 
					                  <td>'.$field3name.'</td> 
					                  <td>'.$field4name.'</td> 
					                  <td>'.$field5name.'</td> 
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="add_employee.php"><button type="button" class="btn btn-primary btn-block btn-large">Adauga anagajat</button></a>
		<a href="edit_employee.php"><button type="button" class="btn btn-primary btn-block btn-large">Modifica detalii angajat</button></a>
		<a href="delete_employee.php"><button type="button" class="btn btn-primary btn-block btn-large">Sterge angajat</button></a>
		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>