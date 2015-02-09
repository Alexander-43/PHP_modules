<?php

include_once 'AbstractUserService.inc';

class UserServiceImpl extends AbstractUserService {
	
	public function getAllUsers($params) {
		$query = sprintf(Utils::GET_ALL, $this->getTableName());
		$result = $this->mysql->Execquery($query);
		$obj = array();
		foreach($result as $index=>$props){
			$obj[] = new User($props);
		}
		return $obj;
	}
	
	public function getVars($vars =NULL){
		return parent::getVars(get_class_vars(get_class()));
	}
}

?>