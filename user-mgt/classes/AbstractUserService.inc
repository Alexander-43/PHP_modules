<?php

include_once 'IUserService.inc';

abstract class AbstractUserService implements IUserService {
	
	public $config = null;
	public $mysql = null;
	public $loginControllers;
	
	public function create(){
		$inst = new self();
		return $inst;
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
	public function getVars($vars = NULL){
		$curVars = get_class_vars(get_class());
		if ($vars != null){
			$curVars = array_merge($vars, $curVars);
		}
		return $curVars;
	}
	
	public function getAllUsers($params) {
		$query = sprintf(Utils::GET_ALL, $this->getTableName());
		$result = $this->mysql->Execquery($query);
		$obj = array();
		foreach($result as $index=>$props){
			$obj[] = new User($props);
		}
		return $obj;
	}
	
	public function doLogout($params){
		throw new ErrorException("Must be overrided.");
	}
	
	public function doLogin($params){
		throw new ErrorException("Must be overrided.");
	}
	
	public function setPermission($params){
	
	}
	
	public function createUser($params){
		$newUser = new User($params);
		$newUser->setMysql($this->mysql);
		$newUser->save();
		return $newUser;
	}
	
	public function setLoginControllers($value){
		$this->loginControllers = $value;
	}
	
	public function getLoginControllers(){
		return $this->loginControllers;
	}
}

?>