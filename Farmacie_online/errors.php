<?php
if(count($erori) > 0) :
?>
	<div>
		
		<?php foreach($erori as $eroare) : ?>
			<p><?php echo $eroare ?></p>
		<?php endforeach ?>
	</div>

<?php endif ?>