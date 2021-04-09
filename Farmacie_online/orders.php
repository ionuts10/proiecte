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
	<title>Comenzi</title>
	<link rel="stylesheet" href="table.css">
</head>
<body>
	<div class="container">
		<table>
			<thead>
				<tr>
					<th>ID</th>
					<th>Data comanda</th>
					<th>Data livrare</th>
					<th>Metoda plata</th>
					<th>Transport gratuit</th>
					<th>Cod voucher</th>
					<th>Operator responsabil</th>
					<th>Client</th>
					<th>Curier</th>
				</tr>
			</thead>
			<tbody>
				<?php 
					$db = mysqli_connect('localhost', 'root', '', 'farmacie_online') or die("Conectare esuata la baza de date!");
					$query = "SELECT CO.comanda_id, CO.data_comanda, CO.data_livrare, CO.metoda_plata, CO.transport_gratuit, CO.cod_voucher, A.email AS email_angajat, CL.email AS email_client, CU.nume_firma FROM tabela_comenzi CO INNER JOIN tabela_clienti CL ON CO.client_id = CL.client_id INNER JOIN tabela_curieri CU ON CO.curier_id = CU.curier_id INNER JOIN tabela_angajati A ON CO.angajat_id = A.angajat_id ORDER BY CO.data_comanda";

					if ($result = $db->query($query)) {
					    while ($row = $result->fetch_assoc()) {
					        $field1name = $row["comanda_id"];
					        $field2name = $row["data_comanda"];
					        $field3name = $row["data_livrare"];
					        $field4name = $row["metoda_plata"];
					        $field5name = $row["transport_gratuit"]; 
					        $field6name = $row["cod_voucher"]; 
					        $field7name = $row["email_angajat"];
					        $field8name = $row["email_client"]; 
					        $field9name = $row["nume_firma"]; 

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
					              </tr>';
					    }
					    $result->free();
					} 
				?>
			</tbody>
		</table>

		<a href="employees_orders.php"><button type="button" class="btn btn-primary btn-block btn-large">Numarul de comenzi prelucrate de fiecare operator</button></a>
		<a href="index.php"><button type="button" class="btn btn-primary btn-block btn-large">Pagina de start</button></a>

	</div>

</body>
</html>