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
	<title>Clienti</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>Nume</th>
					<th>Prenume</th>
					<th>Data nasterii</th>
					<th>Sex</th>
					<th>Email</th>
					<th>Telefon</th>
					<th>Judet</th>
					<th>Oras</th>
					<th>Adresa</th>
					<th>Adresa facturare</th>
					<th>Abonat newsletter</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT * FROM tabela_clienti ORDER BY nume ASC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["nume"];
					        $field2name = $row["prenume"];
					        $field3name = $row["data_nasterii"];
					        $field4name = $row["sex"];
					        $field5name = $row["email"];
					        $field6name = $row["telefon"];
					        $field7name = $row["judet"];
					        $field8name = $row["oras"];
					        $field9name = $row["adresa"];
					        $field10name = $row["adresa_facturare"];
					        $field11name = $row["abonat_newsletter"];  

					        echo '<tr> 
					                  <td>'.$field1name.'</td> 
					                  <td>'.$field2name.'</td> 
					                  <td>'.$field3name.'</td> 
					                  <td>'.$field4name.'</td> 
					                  <td>'.$field5name.'</td> 
					                  <td>'.$field6name.'</td> 
					                  <td>'.$field7name.'</td> 
					                  <td>'.$field8name.'</td> 
					                  <td>'.$field9name.'</td> 
					                  <td>'.$field10name.'</td> 
					                  <td>'.$field11name.'</td> 
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="add_customer.php"><button type="button" class="btn btn-primary btn-block btn-large">Adauga client</button></a>
		<a href="edit_customer.php"><button type="button" class="btn btn-primary btn-block btn-large">Modifica detalii client</button></a>
		<a href="delete_customer.php"><button type="button" class="btn btn-primary btn-block btn-large">Sterge client</button></a>
		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>