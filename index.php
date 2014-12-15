<?php
	include_once 'db-connector/index.inc';
	include_once 'db-object-mgt/index.inc';
	include_once 'config-loader/index.inc';
	include_once 'utils.inc';
	$config = new IniConfig("config.ini");
	$params = array('hostname'=>$config->getValueByKey('db-config.hostname'), 
			'dbname'=>$config->getValueByKey('db-config.dbname'), 
			'dbuser'=>$config->getValueByKey('db-config.dbuser'), 
			'dbpassword'=>$config->getValueByKey('db-config.dbpassword'));
	//print $config->getValueByKey("tree.children.1.text");
	$msql = new Mysql($params);
	if ($_POST['query']!=null){
		$result = $msql->Execquery($_POST['query']);
		print_r($result);
	}
	$tabList = new GetTablesInfo("", "", $params);
	if ($_POST['query']!=null){
		$result = $tabList->getByPattern($_POST['query']);
		print_r($result);
	}
	
	$obj = new MysqlDBObject(null, null, null);
	Utils::getPropsFromIniConfig($obj, $config);
?>
<form name="f1" method="post" action="#">
	<input name="query" type="text" value="<?php print $_POST['query'];?>">
	<input type="submit">
</form>