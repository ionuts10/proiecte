<?php

session_start();

if(!isset($_SESSION['email'])){
	$_SESSION['msg'] = "Trebuie sa fi conectat pentru a vizualiza aceasta pagina.";
	header('location: login.php');
	exit();
}

if(isset($_GET['logout'])){
	session_destroy();
	unset($_SESSION['email']);
	header('location: login.php');
	exit();
}

?>

<!DOCTYPE html>
<html>
<head>
	<title>Acasa</title>
	<link rel="stylesheet" href="index.css">
</head>
<body>
	<div class="index">
		<h1>Pagina de start</h1>

		<?php
			if(isset($_SESSION['succes'])) : ?>

			<div>
				<h3>
				<?php
					echo $_SESSION['succes'];
					unset($_SESSION['succes']);
				?>
				</h3>
			</div>
		<?php endif ?>

	<?php if(isset($_SESSION['email'])) : ?>
		<h3>Bine te-ai intors <strong><?php echo $_SESSION['email']; ?></strong></h3>
		
		<a href="employees.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista angajati</button></a>
		<a href="customers.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista clienti</button></a>
		<a href="orders.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista comenzi</button></a>
		<a href="orders_details.php"><button type="button" class="btn btn-primary btn-block btn-large">Detalii comenzi</button></a>
		<a href="couriers.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista curieri</button></a>
		<a href="suppliers.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista furnizori</button></a>
		<a href="products.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista produse</button></a>
		<a href="index.php?logout='1'"><button type="button" class="btn btn-primary btn-block btn-large">Log out</button></a>
		
	<?php endif ?>
 </div>
</body>
</html>