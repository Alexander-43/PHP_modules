<?php
include_once 'AbstractSource.php';

class Mysql extends AbstractSource {
	public $dblink = null;
	public $clink = null;
	public function __construct($params = null) {
		if ($params != null){
			$this->connect($params);
		}
	}
	public function connect($params=null) {
		$this->clink = mysql_connect($params[AbstractSource::HOST_NAME], 
				$params[AbstractSource::DB_USER], 
				$params[AbstractSource::DB_PASSWORD]);
		if ($this->clink){
			$this->dblink = mysql_select_db($params[AbstractSource::DB_NAME]);
		}
	}
	/**
	 * @see ISource::Execquery()
	 * @return Array 
	 * 				- результат как массив значений
	 */
	public function Execquery($params=null) {
		$result = mysql_query($params, $this->clink);
		if ($result){
			return $this->getArrayValues($result);
		} else {
			return null;
		}
	}
	/**
	 * Выполнить запрос
	 * @param String $query
	 * @return resource|NULL
	 * 						- mysql result array
	 */
	public function exec($query){
		$result = mysql_query($query, $this->clink);
		if ($result){
			return $result;
		}else{
			return null;
		}
	}
	public function close($params=null) {
		if ($this->dblink != null){
			return mysql_close ($this->dblink);
		}
	}
	/**
	 * Ротация $query в массив значений
	 * @param mysql_query_result $query
	 * @return array
	 */
	private function getArrayValues($query){
		if (!$query) return Array("res"=>"null");
		while($field=mysql_fetch_field($query)){
			$names_fields[]=$field->name;
		}
		$values = Array();
		while ($row = mysql_fetch_array($query, MYSQL_NUM)) {
			$line = Array();
			for($i = 0; $i < count($names_fields); $i++)
			{
			$line[$names_fields[$i]]=$row[$i];
			}
			$values[] = $line;
		}
		return $values;
	}
}

?>