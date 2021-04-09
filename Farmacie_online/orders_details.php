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
	<title>Detalii comenzi</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>ID comanda</th>
					<th>Email client</th>
					<th>Denumire produs</th>
					<th>Cantitate</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT CO.comanda_id AS comanda_id, C.email AS email_client, P.denumire AS denumire, DC.cantitate AS cantitate FROM detalii_comanda DC INNER JOIN tabela_comenzi CO ON DC.comanda_id = CO.comanda_id INNER JOIN tabela_angajati A ON A.angajat_id = CO.angajat_id INNER JOIN tabela_produse P ON DC.produs_id = P.produs_id INNER JOIN tabela_clienti C ON C.client_id = CO.client_id";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["comanda_id"];
					        $field2name = $row["email_client"];
					        $field3name = $row["denumire"];
					        $field4name = $row["cantitate"];
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
		<a href="orders_value.php"><button type="button" class="btn btn-primary btn-block btn-large">Valoarea monetara a fiecarei comenzi</button></a>
		<a href="orders_over_value.php"><button type="button" class="btn btn-primary btn-block btn-large">Comenzi cu valoare totala de peste 50 unitati monetare</button></a>
		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>