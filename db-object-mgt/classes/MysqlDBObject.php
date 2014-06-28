<?php
include_once 'AbstractDBObject.php';

class MysqlDBObject extends AbstractDBObject {
	public $mysql = null;
	public $props = null;
	const ID_NAME = "id";
	const CREATE = "INSERT INTO %s(%s) VALUES(%s)";
	const DELETE = "DELETE FROM %s";
	const UPDATE = "UPDATE %s set %s";
	const WHERE = " where %s";
	
	function __construct($name, $qualifier, $dbParams) {
		$this->mysql = new Mysql($dbParams);
		if ($name != null){
			$this->setName($name);
		}
		if ($qualifier != null){
			$this->setQualifier($qualifier);
		}
	}
	
	public function update($where, $propName, $value){
		$query=sprintf(MysqlDBObject::UPDATE, $this->getName(), $propName."=".$value);
		return $this->mysql->exec($query.($where!=null?sprintf(MysqlDBObject::WHERE,$where):""));
	}
	/**
	 * arg[0] - условие поиска
	 * arg[n..n+1] - имя и значение атрибута
	 * @see IDBObject::update()
	 */
	public function update() {
		if (func_num_args() > 0){
			$args = func_get_args();
			$result = true;
			$where = $args[0]!=null?sprintf(MysqlDBObject::WHERE,$args[0]):null;
			for ($i=1;$i<func_num_args();$i=$i+2){
				$result = $result && $this->update($where, $args[$i], $args[$i+1]);
			}
			return $result;
		}
		return null;
	}
	
	public function delete($where){
		$query=sprintf(MysqlDBObject::DELETE, $this->name).sprintf(MysqlDBObject::WHERE, $where);
		return $this->mysql->exec($query);
	}
	
	public function delete() {
		return "Not implemented";
	}
	public function create() {
		return "Not implemented";
	}
}

?>