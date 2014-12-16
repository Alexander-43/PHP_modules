<?php
include_once 'IDBObject.inc';

abstract class AbstractDBObject implements IDBObject {
	public $name = "";
	public $qualifier = "";
	
	public function setName($name){
		$this->name = $name;
	}
	
	public function getName(){
		return $this->name;
	}
	
	public function setQualifier ($qualifier) {
		$this->qualifier = $qualifier;
	}
	
	public function getQualifier(){
		return $this->qualifier;
	}
	
	public function makeResult($code, $message){
		return array("status"=>$code, "message"=>$message);
	}
	
	public function getVars($vars){
		$curVars = get_class_vars(get_class());
		if ($vars != null){
			$curVars = array_merge($vars, $curVars);
		}
		return $curVars;
	}
}

?>