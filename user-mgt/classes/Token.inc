<?php

class Token extends AbstractDbPersistableImpl {
	private $id = null;
	private $userId = null;
	private $expDate = null;
	private $created = null;
	private $token = null;
	private $amount = 1800000;
	private $tablename = "tokens";
	private $persistedFields = Array(
			'userId'=>Array('type'=>'string', 'format'=>"'%s'", 'default'=>''), 
			'expDate'=>Array('type'=>'date', 'format'=>"'%s'", 'default'=>''), 
			'token'=>Array('type'=>'string', 'format'=>"'%s'", 'default'=>'')
	);
	
	public function getTableName(){
		return $this->tablename;
	}
	
	public function setTableName($value){
		$this->tablename = $value;
	}
	
	public static function createInstance(){
		$inst = new self();
		return $inst;
	}
	
	public function setId($value){
		$this->id = $value;
	}
	
	public function setAmount($value){
		$this->amount = $value;
	}
	
	public function setUserId($value){
		$this->userId = $value;
	}
	
	public function setExpDate($value){
		if (is_array($value) && $value["amount"] != null){
			$this->expDate = time(true) + $value["amount"];
		} else if (is_array($value) && $value["amount"] == null){
			$this->expDate = time() + $this->amount;
		} else {
			$this->expDate = strtotime($value) !== false ? strtotime($value) : $value;
		}
	}
	
	public function setCreated($value){
		$this->created = $value;
	}
	
	public function getCreated(){
		return $this->created;
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
		return date(Utils::DATE_FORMAT, $this->expDate);;
	}
	
	public function getToken($new = false){
		if ($new === true){
			return md5(microtime(true));
		} else {
			return $this->token;
		}
	}
	
	public function getVars($vars =NULL){
		return parent::getVars(get_class_vars(get_class()));
	}
	
	public function getPersistedFields(){
		return $this->persistedFields;
	}
	
	public function isExists($className){
		$select = sprintf(Utils::GET_ALL, $this->getTableName());
		$where = sprintf(Utils::WHERE, 'userId='.$this->getUserId());
		$res = $this->mysql->Execquery($select.$where);
		if (count($res) == 0){
			return false;
		} else {
			return $res[0][IDbPersistable::PROP_ID];
		}
	}
}

?>