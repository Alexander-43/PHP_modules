<?php

class AbstractMysql {
	
	public static $ID_NAME = "id";
	public static $CREATE = "INSERT INTO %s(%s) VALUES(%s)";
	public static $DELETE = "DELETE FROM %s";
	public static $UPDATE = "UPDATE %s set %s";
	public static $WHERE = " where %s";
	
	protected $mysql = null;
	
	public function setMysql($value){
		$this->mysql = $value;
	}
	
	public function getMysql(){
		return $this->mysql;
	}
}

?>