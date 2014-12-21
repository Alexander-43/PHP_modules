<?php

include_once 'AbstractUserService.inc';

class UserServiceImpl extends AbstractUserService {
	
	const GET_ALL = "SELECT * from %s ";
	const WHERE = "WHERE %s";
	
	public function getAllUsers($params) {
		$query = sprintf($this::GET_ALL, $this->getTableName());
		$result = $this->mysql->Execquery($query);
		/*for($i=0;$i<count($result);++$i){
			
		}*/
		return result;
	}
}

?>