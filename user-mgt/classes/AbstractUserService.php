<?php

include_once 'IUserService.php';

abstract class AbstractUserService implements IUserService {
	
	public $config = null;
	public $connection = null;
	public $tablename = null;
	
	public function create(){
		$inst = new self();
		return $inst;
	}
	
	public function doLogout($id) {
	}
	public function createUser($params) {
	}
	public function doLogin($params) {
	}
	public function setPermission($params) {
	}
	public function getAllUsers($params) {
	}
	
	public function setConnection($connection){
		$this->connection = $connection;
	}
	
	public function setConfig($config){
		$this->config;
	}
	public function getVars(){
		return get_class_vars($this);
	}
}

?>