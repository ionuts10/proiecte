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
	<title>Curieri</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>Nume firma</th>
					<th>Email</th>
					<th>Telefon</th>
					<th>Pret transport</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT nume_firma, email, telefon, pret_transport FROM tabela_curieri";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["nume_firma"];
					        $field2name = $row["email"];
					        $field3name = $row["telefon"];
					        $field4name = $row["pret_transport"];

					        echo '<tr> 
					                  <td>'.$field1name.'</td> 
					                  <td>'.$field2name.'</td> 
					                  <td>'.$field3name.'</td> 
					                  <td>'.$field4name.'</td> 
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>