<?php

class Token {
	private $id;
	private $userId;
	private $expDate;
	private $token;
	private $amount;
	private $tablename = "tokens";
	
	public function getTablename(){
		return $this->tablename;
	}
	
	public function setTablename($value){
		$this->tablename = $value;
	}
	
	public static function create(){
		$inst = new self();
		return $inst;
	}
	
	public function setId($value){
		$this->id = $value;
	}
	
	public function setUserId($value){
		$this->userId = $value;
	}
	
	public function setExpDate($value){
		if (is_array($value) && $value["amount"] != null){
			$this->expDate = time() + $value["amount"];
		} else if (is_array($value) && $value["amount"] == null){
			$this->expDate = time() + $this->amount;
		} else {
			$this->expDate = $value;
		}
	}
	
	public function setToken($value){
		if ($value != null){
			$this->token = $value;
		} else {
			$this->token = $this->getToken(true);
		}
	}
	
	public function getId(){
		return $this->id; 
	}
	
	public function getUserId(){
		return $this->userId;
	}
	
	public function getExpDate(){
		return $this->expDate;
	}
	
	public function getToken($new = false){
		if ($new === true){
			return md5(time());
		} else {
			return $this->token;
		}
	}
	
	public function getVars(){
		return get_class_vars(get_class());
	}
}

?>