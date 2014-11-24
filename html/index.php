<?php

include ".php/functions.php";

if ( isset($_GET["id"] ) {
	$id = $_GET["id"];
} else
	$id = 0;
}

switch ( $id ) {
	case 0 :
		$title = "index";
		break;
	case 1 :
		$title = "compareSrc";
		break;
	case 2 :
		$title = "stockSrc";
		break;
	case 3 :
		$title = "autre";
		break;
	default :
		$title = "error";
}

headered( $id , $title );
include "page/".$title.".html";
footered();

?>
