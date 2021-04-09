<?php include('add_customer_server.php') ?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title>Adaugare client</title>
	<link rel="stylesheet" href="registration.css">
</head>
<body>

	<div class="registration">

		<form action="add_customer.php" method="post">

			<?php 

				include('errors.php')

			?>
			<div>
				<input type="text" name="nume" placeholder="Nume" required>
			</div>

			<div>
				<input type="text" name="prenume" placeholder="Prenume" required>
			</div>

			<div>
				<input type="date" name="data_nasterii" placeholder="Data nasterii" required>
			</div>

			<div>
				<input type="text" name="sex" placeholder="Sex (M/F)" required>
			</div>

			<div>
				<input type="email" name="email" placeholder="Email" required>
			</div>

			<div>
				<input type="text" name="telefon" placeholder="Telefon" required>
			</div>

			<div>
				<input type="text" name="judet" placeholder="Judet" required>
			</div>

			<div>
				<input type="text" name="oras" placeholder="Oras" required>
			</div>

			<div>
				<input type="text" name="adresa" placeholder="Adresa" required>
			</div>

			<div>
				<input type="text" name="adresa_facturare" placeholder="Adresa facturare" required>
			</div>

			<div>
				<input type="text" name="abonat_newsletter" placeholder="Abonat newsletter (1/0)" required>
			</div>

			<button type="submit" class="btn btn-primary btn-block btn-large" name="reg_user">Adauga</button>
			<a href="customers.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista clienti</button></a>

		</form>
	</div>

</body>
</html>