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
	<title>Produse</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>ID produs</th>
					<th>Tip produs</th>
					<th>Denumire produs</th>
					<th>Pret</th>
					<th>Stoc</th>
					<th>Furnizor</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT P.produs_id, P.tip_produs, P.denumire, P.pret, P.stoc, F.nume_furnizor FROM tabela_produse P INNER JOIN tabela_furnizori F ON P.furnizor_id = F.furnizor_id ORDER BY P.denumire ASC";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["produs_id"];
					        $field2name = $row["tip_produs"];
					        $field3name = $row["denumire"];
					        $field4name = $row["pret"];
					        $field5name = $row["stoc"]; 
					        $field6name = $row["nume_furnizor"]; 

					        echo '<tr> 
					                  <td>'.$field1name.'</td> 
					                  <td>'.$field2name.'</td> 
					                  <td>'.$field3name.'</td> 
					                  <td>'.$field4name.'</td> 
					                  <td>'.$field5name.'</td> 
					                  <td>'.$field6name.'</td> 
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="products_not_sold.php"><button type="button" class="btn btn-primary btn-block btn-large">Produse ce nu se afla in nicio comanda</button></a>
		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>