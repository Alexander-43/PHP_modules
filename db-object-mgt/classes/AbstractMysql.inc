<?php

class AbstractMysql {
	
	public static  final $ID_NAME = "id";
	public static  final $CREATE = "INSERT INTO %s(%s) VALUES(%s)";
	public static  final $DELETE = "DELETE FROM %s";
	public static  final $UPDATE = "UPDATE %s set %s";
	public static  final $WHERE = " where %s";
	
	protected $mysql = null;
	
	public function setMysql($value){
		$this->mysql = $value;
	}
	
	public function getMysql(){
		return $this->mysql;
	}
}

?>