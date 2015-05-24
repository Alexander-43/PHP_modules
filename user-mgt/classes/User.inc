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
	
	public function __construct($props){
		$this->setLogin($props['login']);
		$this->id = $props['id'];
		$this->setPassword($props['password'], false);
		$this->setAvatar($props['avatar']);
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
	function setPassword($password, $encrypt) {
		if ($encrypt){
			$this->password = md5($password);
		} else {
			$this->password = $password;
		}
	}
	public function getId() {
		return $this->id;
	}
	public function getPermission() {
	}
	public function setToken($value){
		$this->token = $value;
	}
	public function getToken(){
		return $this->token;
	}
}

?>