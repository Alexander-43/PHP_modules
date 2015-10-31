<?php

include_once 'AbstractUserService.inc';
include_once 'ILoginController.inc';

class UserServiceImpl extends AbstractUserService {
	
	public function doLogin($params){
		$res = array();
		foreach ($this->getLoginControllers() as $lc){
			if ($lc instanceof ILoginController){
				list($success, $result, $message) = $lc->login($params);
				$res[get_class($lc)] = array('status'=>$success, 'result'=>($success?$result:$message));
			} else {
				$res[get_class($lc)] = array('status'=>false, 'result'=>'Not implemented ILoginController interface');
			}
		}	
		return $res;	
	}
	
	public function doLogout($params){
		$res = array();
		foreach ($this->getLoginControllers() as $lc){
			if ($lc instanceof ILoginController){
				list($success, $result, $message) = $lc->logout($params);
				$res[get_class($lc)] = array('status'=>$success, 'result'=>($success?$result:$message));
			} else {
				$res[get_class($lc)] = array('status'=>false, 'result'=>'Not implemented ILoginController interface');
			}
		}
		return $res;
	}
	
	public function getVars($vars =NULL){
		return parent::getVars(get_class_vars(get_class()));
	}
}

?>