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
	<title>Comenzi peste prag</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>ID comanda</th>
					<th>Valoare</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT comanda_id, SUM(DC.cantitate * P.pret) AS valoare FROM detalii_comanda DC INNER JOIN tabela_produse P ON DC.produs_id = P.produs_id GROUP BY comanda_id HAVING SUM(DC.cantitate * P.pret) >= 50 ORDER BY valoare DESC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["comanda_id"];
					        $field2name = $row["valoare"];
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
		<a href="orders_details.php"><button type="button" class="btn btn-primary btn-block btn-large">Detalii comenzi</button></a>

	</div>

</body>
</html>