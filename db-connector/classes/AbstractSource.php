<?php
include_once 'ISource.php';

abstract class AbstractSource implements ISource {
	const HOST_NAME = "hostname";
	const DB_NAME = "dbname";
	const DB_USER = "dbuser";
	const DB_PASSWORD = "dbpassword";
}

?>