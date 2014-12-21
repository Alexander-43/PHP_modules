<?php

include_once 'IUserService.inc';

abstract class AbstractUserService implements IUserService {
	
	public $config = null;
	public $mysql = null;
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
	
	public function setTableName($tablename){
		$this->tablename = $tablename;
	}
	
	public function getTableName(){
		return $this->tablename;
	}
	
	public function setMysql($mysql){
		$this->mysql = $mysql;
	}
	
	public function setConfig($config){
		$this->config;
	}
	public function getVars(){
		$curVars = get_class_vars(get_class());
		if ($vars != null){
			$curVars = array_merge($vars, $curVars);
		}
		return $curVars;
	}
}

?>