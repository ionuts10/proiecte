<?php 
include('reg_login_server.php')
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title>Conectare</title>
	<link rel="stylesheet" href="login.css">
</head>
<body>

	<div class="login">

		<div class="header">
			<h1>Conectare angajat</h1>
		</div>

		<form action="login.php" method="post">
			
			<?php 

				include('errors.php')

			?>
			
			<div>
				<input type="email" name="email" placeholder="Email" required>
			</div>

			<div>
				<input type="password" name="password" placeholder="Parola" required>
			</div>


			<button type="submit" class="btn btn-primary btn-block btn-large" name="login_user">Log in</button>

			<a href="registration.php"><button type="button" class="btn btn-primary btn-block btn-large">Nu ai cont?</button></a>

		</form>
	</div>

</body>
</html>