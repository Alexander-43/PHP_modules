<?php 
	$param = array();
	if ($_GET != null){
		$param = $_GET;
	}
	if ($_POST != null){
		$param = $_POST;
	}
	if ($param['fn']){
		if (function_exists($param['fn'])){
			$param['fn']($param);
		} else {
			$error = array('status'=>500, 'message'=>'Function '.$param['fn'].' does`t exist');
		}
	} else {
		$error = array('status'=>501, 'message'=>'Function '.$param['fn'].' not set');
	}
	if (isset($error)){
		header('Content-Type: application/json');
		print json_encode($error);
	}
	function test($p){
		print_r ($p);
	}
?>