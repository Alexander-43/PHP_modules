<?php

include_once 'User.inc';
include_once 'Token.inc';

class BaseLoginController extends AbstractMysql implements ILoginController {
	
	const USER_PARAM = 'user';
	const TOKEN_PARAM = 'token';
	
	public static function createInstance(){
		$inst = new self();
		return $inst;
	}
	
	public function login($props){
		$user = $props[BaseLoginController::USER_PARAM];
		$token = $props[BaseLoginController::TOKEN_PARAM];
		$check = $user != null && $user instanceof User; 
		$check = $check && $token != null && $token instanceof Token;
		if ($check){
			$token->setUserId($user->getId());
			$token->save();
			$user->setToken($token->getToken());
			$user->save();
			return array(true, $token);
		} else {
			return array(false, null, "User or token not set");
		}
	}
	
	public function logout($props){
		$user = $props[BaseLoginController::USER_PARAM];
		$token = $props[BaseLoginController::TOKEN_PARAM];
		$check = $user != null && $user instanceof User;
		$check = $check && $token != null && $token instanceof Token;
		if ($check){
			if ($token->delete() > 0){
				$user->setToken("");
				$user->save();
				return array(true, null);
			} else {
				return array(false, $token, $user->getLogin()." does not logged in");
			}
		}
	}
	
	public function createToken($props){
		throw new Exception("Not implemented for " + get_class());
	}
	
	public function getVars($vars = null){
		$curVars = get_class_vars(get_class());
		if ($vars != null){
			$curVars = array_merge($vars, $curVars);
		}
		return $curVars;
	}
	
}

?>