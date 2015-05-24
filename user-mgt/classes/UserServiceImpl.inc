<?php

include_once 'AbstractUserService.inc';

class UserServiceImpl extends AbstractUserService {
	
	public function getVars($vars =NULL){
		return parent::getVars(get_class_vars(get_class()));
	}
}

?>