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
	<title>Produse necomandate</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>Denumire produs</th>
					<th>Stoc</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT P.denumire AS denumire, P.stoc AS stoc FROM tabela_produse P WHERE P.produs_id NOT IN(SELECT DC.produs_id FROM detalii_comanda DC) ORDER BY stoc DESC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["denumire"];
					        $field2name = $row["stoc"];
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
		<a href="products.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista produse</button></a>

	</div>

</body>
</html>