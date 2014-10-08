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
		$this->qualifier;
	}
	
	public function getQualifier(){
		return $this->qualifier;
	}
	
	public function makeResult($code, $message){
		return array("status"=>$code, "message"=>$message);
	}
}

?>