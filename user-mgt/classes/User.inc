<?php

include_once 'IUser.inc';

class User extends AbstractDbPersistableImpl implements IUser {
	
	private $id;
	private $login;
	private $password;
	private $permissions;
	private $avatar;
	private $token;
	private $tablename = "users";
	private $persistedFields = Array(
			'login'=>Array('type'=>'string', 'format'=>"'%s'", 'default'=>''),
			'password'=>Array('type'=>'string', 'format'=>"'%s'", 'default'=>''),
			'permissions'=>Array('type'=>'string', 'format'=>"'%s'", 'default'=>'')
	);
	
	public function __construct($props){
		$this->setLogin($props[IUser::PROP_LOGIN]);
		$this->id = $props[IDbPersistable::PROP_ID];
		$this->setPassword($props[IUser::PROP_PASSWORD], false);
		$this->setAvatar($props[IUser::PROP_AVATAR]);
	}
	
	public static function createInstance(){
		$inst = new self();
		return $inst;
	}
	
	public function isExists($className){
		$props = array(Utils::PROP_TABLE_NAME=>$this->getTableName(),
				Utils::PROP_UNIC_FIELD_NAME=>IDbPersistable::PROP_ID,
				Utils::PROP_UNIC_FIELD_VALUE=>$this->getId()
		);
		Utils::setMySqlObject($this->mysql);
		$res = Utils::findUnicObject($props);
		if ($res !== false && count($res) > 0){
			return $res[0][IDbPersistable::PROP_ID];
		} else {
			return false;
		}
	}
	
	public function create($props) {
	}
	
	public function isLogged() {
	}
	public function getLogin() {
		return $this->login;
	}
	function setLogin($login) {
		$this->login = $login;
	}
	public function getAvatar() {
		return $this->avatar;
	}
	public function getPassword() {
		return $this->password;
	}
	public function setAvatar($avatar) {
		$this->avatar = $avatar;
	}
	function setPassword($password, $encrypt = false) {
		if ($encrypt){
			$this->password = md5($password);
		} else {
			$this->password = $password;
		}
	}
	
	public function getId() {
		return $this->id;
	}
	
	public function setId($value) {
		$this->id = $value;
	}
	
	public function getPermission() {
	}
	
	public function setToken($value){
		$this->token = $value;
	}
	
	public function getToken(){
		return $this->token;
	}
	
	public function getTableName(){
		return $this->tablename;
	}
	
	public function setTableName($value){
		$this->tablename = $value;
	}
	
	public function getPersistedFields(){
		return $this->persistedFields;
	}
	
	public function getVars($vars =NULL){
		return parent::getVars(get_class_vars(get_class()));
	}
}

?>