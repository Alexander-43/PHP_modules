<?php
	include_once 'db-connector/index.php';
	include_once 'db-object-mgt/index.php';
	$params = array('hostname'=>'localhost', 'dbname'=>'zamaster', 'dbuser'=>'root', 'dbpassword'=>'');
	$msql = new Mysql($params);
	if ($_POST['query']!=null){
		$result = $msql->Execquery($_POST['query']);
		print_r($result);
	}
?>
<form name="f1" method="post" action="#">
	<input name="query" type="text" value="<?php print $_POST['query'];?>">
	<input type="submit">
</form>