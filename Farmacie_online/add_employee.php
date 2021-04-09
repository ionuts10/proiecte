<?php include('add_employee_server.php') ?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title>Adaugare angajat</title>
	<link rel="stylesheet" href="registration.css">
</head>
<body>

	<div class="registration">

		<form action="add_employee.php" method="post">

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
				<input type="text" name="telefon" placeholder="Telefon" required>
			</div>

			<div>
				<input type="text" name="functie" placeholder="Functie" required>
			</div>

			<div>
				<input type="email" name="email" placeholder="Email" required>
			</div>

			<div>
				<input type="password" name="password_1" placeholder="Parola" required>
			</div>

			<div>
				<input type="password" name="password_2" placeholder="Confirmare parola" required>
			</div>

			<button type="submit" class="btn btn-primary btn-block btn-large" name="reg_user">Adauga</button>
			<a href="employees.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista angajati</button></a>

		</form>
	</div>

</body>
</html>