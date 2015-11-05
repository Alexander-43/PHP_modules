<?php
include_once 'AbstractDBObject.inc';

class MysqlDBObject extends AbstractDBObject {
	public $props = null;
	
	function __construct($name = null, $qualifier = null, $dbParams = null, $mysql=null) {
		$this->mysql = $mysql == null ? new Mysql($dbParams): $mysql;
		if ($name != null){
			$this->setName($name);
		}
		if ($qualifier != null){
			$this->setQualifier($qualifier);
		}

	}
	
	public function __call($method_name,$arguments) {
	
		if (method_exists($this, $method_name.count($arguments)) !== true) {
			$this->$method_name($arguments);
		}
	
		$method_name = $method_name.count($arguments);
		$this->$method_name($arguments);
	}
	/**
	 * arg[0] - Условие where
	 * arg[n..n+1] - пары свойство, значение
	 * @see IDBObject::update()
	 */
	public function update() {
		if (func_num_args() > 0){
			$args = func_get_args();
			$result = true;
			$where = $args[0]!=null?sprintf($this->WHERE,$args[0]):null;
			for ($i=1;$i<func_num_args();$i=$i+2){
				$result = $result && $this->update($where, $args[$i], $args[$i+1]);
			}
			return $result;
		}
		return null;
	}
	
	public function update2($data, $key){
		$where = "";
		$set = array();
		foreach ($data as $field=>$value){
			if ($key != null && $field==$key){
				$where = sprintf($this->WHERE, $field."=".$value);
			} else {
				$set[] = $field."='".$value."'";
			}
		}
		$query = sprintf($this->UPDATE, $this->name, implode(",", $set)).$where;
		$res = $this->mysql->exec($query);
		if (mysql_affected_rows() == -1){
			return $this->makeResult(500, "Ошибка изменения - ".mysql_error());
		} else {
			return $this->makeResult(200, "Обновлено ".mysql_affected_rows()." записей.");
		}
	}
	
	public function update3($where, $propName, $value){
		$query=sprintf($this->UPDATE, $this->getName(), $propName."=".$value);
		return $this->mysql->exec($query.($where!=null?sprintf($this->WHERE,$where):""));
	}
	
	public function delete1($where){
		$query=sprintf($this->DELETE, $this->name).sprintf($this->WHERE, $where);
		return $this->mysql->exec($query);
	}
	
	public function delete($params) {
		return "Not implemented";
	}
	
	public function delete2($data, $key){
		$where = "";
		if ($key != null && $data[$key] != null){
			$where = sprintf($this->WHERE, $key."=".$data[$key]);
			$query = sprintf($this->DELETE, $this->name).$where;
		}
		if ($key == 'ALL'){
			$query = sprintf($this->DELETE, $this->name);
		}
		$res = $this->mysql->exec($query);
		if (mysql_affected_rows() == -1){
			return $this->makeResult(500, "Ошибка удаления - ".mysql_error());
		} else {
			return $this->makeResult(200, "Удалено ".mysql_affected_rows()." записей.");
		}
	}
	
	public function create($data = null, $key = null) {
		$fields = array();
		$values = array();
		foreach ($data as $field=>$value){
			$fields[] = $field;
			if (($key != null && $field==$key) || ($field == $this->ID_NAME && $key==null)){
				$values[] = null;
			} else {
				$values[] = "'".$value."'";
			}
		}
		$query = sprintf($this->CREATE, $this->name, implode(",", $fields), implode(",", $values));
		$this->mysql->exec($query);
		if (mysql_insert_id() == 0){
			return $this->makeResult(500, "Ошибка создания - ".mysql_error());
		} else {
			return $this->makeResult(200, "Создан элемент с ID=".mysql_insert_id());
		}
	}
	
	public function getVars($vars = null){
		$curVars = get_class_vars(get_class());
		if ($vars != null){
			$curVars = array_merge($vars, $curVars);
		}
		return parent::getVars($curVars);
	}
}

?>