<?php

function isActive($id,$page)
{
	if ( $id == $page ) {
		echo "class=\"active\"";
	}
}

function headered( $id , $title )
{	?>

<!DOCTYPE html>
<html lang="fr" >
<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<meta name="description" content="LSST LPC" />
	<meta name="author" content="Josselin Massot" />
	
	<link rel="icon" href="favicon.ico" />

	<title><?php echo $title; ?></title>

	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css" />
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap-theme.min.css" />
	<?php
		if ( $id > 0 ) { ?>
	<style>
		body { padding-top: 70px; }
	</style>
		<?php } ?>
	</head>

	<body>

	<header class="navbar navbar-inverse navbar-fixed-top" role="navigation" ><div class="container" >
		<div class="navbar-header" >
			<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar" >
				<span class="sr-only"  >Toggle navigation</span>
				<span class="icon-bar" ></span>
				<span class="icon-bar" ></span>
				<span class="icon-bar" ></span>
			</button>
			
			<a class="navbar-brand" href="index.html" >Projet LSST - ISIMA</a>

		</div>
		<nav class="collapse navbar-collapse bs-navbar-collapse" role="navigation">
			<ul class="nav navbar-nav" >
				<li <?php isActive($id,1); ?> >
					<a href="index.php?id=1" >compareSrc</a>
				</li>
				<li <?php isActive($id,2); ?> >
					<a href="index.php?id=2" >stockSrc</a>
				</li>
				<li <?php isActive($id,3); ?> >
					<a href="index.php?id=3" >Autres</a>
				</li>
			</ul>
			<ul class="nav navbar-nav navbar-right" >
				<li><a href="https://github.com/Kivvix/projet-LPC" >git</a></li>
				<li><a href="apropos.html" >À propos</a></li>
			</ul>
		</nav>
	</div></header>
<a id="top" ></a>
	<?php
}

function footered()
{ ?>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/js/bootstrap.min.js"></script>
</body>
</html>
<?php }

?>
