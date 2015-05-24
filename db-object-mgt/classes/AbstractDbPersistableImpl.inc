<?php

include_once 'IDbPersistable.inc';

abstract class AbstractDbPersistableImpl extends MysqlDBObject implements IDbPersistable {
	
	public $createMethodName = "createInstance"; 
	
	public function save($params = null) {
		$tObj = null;
		$obj = null;
		if ($params['id'] != null){
			$obj = $this->getById(Array('id' => $params['id']));
		} else if ($this->getId() != null){
			$obj = $this->getById(Array('id' => $this->getId(), 'setVars'=>false));
		}
		if (count($obj) > 1){
			throw new ErrorException("More then one object with this ID - ".($this->getId() || $params['id']));
		} else if (count($obj) == 0 || $obj == null){
			$exists = $this->isExists(get_class($this));
			if ($exists === false){
				$q = $this->generateInsert();
				$this->mysql->exec($q);
				$this->getById(array('id'=>mysql_insert_id()));
				return $this;
			} else {
				$this->getById(array('id'=>$exists));
				$this->save();
			}
		} else if (count($obj == 1)){
			$q = $this->generateUpdate();
			$this->mysql->exec($q);
			return mysql_affected_rows();
		} else {
			throw new ErrorException("Exeption for object by id query - ".$obj);
		}
	}
	
	public function delete($params) {
		$obj = null;
		if ($params['id'] != null){
			$obj = $this->getById(Array('id' => $params['id']));
		} else if ($this->getId() != null){
			$obj = $this->getById(Array('id' => $this->getId(), 'setVars'=>false));
		}
		if (count($obj) > 1){
			throw new ErrorException("More then one object with this ID - ".($this->getId() || $params['id']));
		} else if (count($obj) == 0 || $obj == null){
			throw new ErrorException("No rows in '".$this->getTableName()."' with id - ".$this->getId());
		} else if (count($obj == 1)){
			$q = $this->generateDelete();
			$this->mysql->exec($q);
			return mysql_affected_rows();
		} else {
			throw new ErrorException("Exeption for object by id query - ".$obj);
		}
	}
	
	public function getById($params) {
		if ($params['id'] != null && $params['id'] != ''){
			$query = sprintf(Utils::GET_ALL, $this->getTableName());
			$where = sprintf(Utils::WHERE, "id=".$params['id']);
			$query = $query.$where;
			if ($this->mysql->dblink == null && Utils::$mysqlObject != null){
				$this->setMysql(Utils::$mysqlObject);
			}
			$obj = $this->mysql->Execquery($query);
			if (count($obj) == 1 && $params['setVars'] !== false){
				$fv = $this->getValuesForFields($this->getPersistedFields());
				$merge = array_merge($obj[0], $fv);
				Utils::getClassInstance($merge, get_class($this), $this->getCreateMethodName(), $this);
			}
			return $obj;
		} else {
			throw new ErrorException("Id not set. Call method without params['id'] value");
		}
	}
	
	/**
	 * Строка вставки новой записи в БД
	 * @return string
	 * 					- команда INSERT в MySQL нотации
	 */
	public function generateInsert(){
		$fv = $this->getValuesForFields($this->getPersistedFields());
		$f = '';
		$v = '';
		foreach ($this->getPersistedFields() as $key=>$value){
			$f = $f == '' ? $key : $f.','.$key;
			$v = $v == '' ? sprintf($value['format'], $fv[$key]): $v.','.sprintf($value['format'], $fv[$key]);
		}
		return sprintf(Utils::INSERT, $this->getTableName(), $f, $v); 
	}
	
	/**
	 * Строка обновления объекта в БД
	 * @return string
	 * 					- команда UPDATE в MySQL нотации
	 */
	public function generateUpdate(){
		$fv = $this->getValuesForFields($this->getPersistedFields());
		$set = '';
		foreach ($this->getPersistedFields() as $key=>$value){
			$set = $set == '' ? $key.'='.sprintf($value['format'], $fv[$key]) : $set.','.$key.'='.sprintf($value['format'], $fv[$key]);
		}
		return sprintf(Utils::UPDATE, $this->getTableName(), $set).' '.sprintf(Utils::WHERE, 'id='.$this->getId());
	}
	
	public function generateDelete(){
		$delete = sprintf(Utils::DELETE, $this->getTableName());
		$where = sprintf(Utils::WHERE, 'id='.$this->getId());
		return $delete.$where;
	}
	
	/**
	 * Возвращает массив "поле класса"=>"значение полученное getter`ом"
	 * @param Array $fields
	 * 						- список полей
	 * @return
	 * 						- список значений для полей
	 */
	public function getValuesForFields($fields){
		$res = Array();
		$vars = array_keys($fields);
		$methods = get_class_methods($this);
		foreach ($vars as $var){
			$methodName = strtolower("get".$var);
			foreach ($methods as $method){
				if (strtolower($method) == $methodName){
					$res[$var] = $this->$method();
					continue;
				}
			}
		}
		return count($res) > 0 ? $res : null;
	}
	
	/*public function getPersistedFields() {
	}*/
	
	public function getCreateMethodName(){
		return $this->createMethodName;
	}
	
	public function isExists($className){
		throw new ErrorException('Method isExists() must be overridden in "'.$className.'" class');
	}
}

?>