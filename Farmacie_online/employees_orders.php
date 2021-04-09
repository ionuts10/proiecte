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
	<title>Comenzi per operator</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>Operator</th>
					<th>Numar comenzi</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT A.email AS email_angajat, COUNT(C.comanda_id) AS nr_comenzi FROM tabela_comenzi C RIGHT JOIN tabela_angajati A ON C.angajat_id = A.angajat_id WHERE A.functie = 'Operator comenzi' GROUP BY A.email ORDER BY nr_comenzi DESC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["email_angajat"];
					        $field2name = $row["nr_comenzi"];

					        echo '<tr> 
					                  <td>'.$field1name.'</td> 
					                  <td>'.$field2name.'</td> 
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="orders.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista comenzi</button></a>

	</div>

</body>
</html>