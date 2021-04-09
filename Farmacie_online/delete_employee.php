<?php include('delete_employee_server.php') ?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title>Stergere angajat</title>
	<link rel="stylesheet" href="registration.css">
</head>
<body>

	<div class="registration">

		

		<form action="delete_employee.php" method="post">

			<div class="header">
				<p>Emailul angajatului ce urmeaza a fi sters:</p>
			</div>

			<div>
				<input type="email" name="email" placeholder="Email" required>
			</div>

			<?php 

				include('errors.php')

			?>

			<button type="submit" class="btn btn-primary btn-block btn-large" name="reg_user">Sterge</button>
			<a href="employees.php"><button type="button" class="btn btn-primary btn-block btn-large">Lista angajati</button></a>

		</form>
	</div>

</body>
</html>