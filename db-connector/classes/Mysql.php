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
	public function Execquery($params=null) {
		$result = mysql_query($params, $this->clink);
		if ($result){
			return $this->getArrayValues($result);
		} else {
			return null;
		}
	}
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
	 * Ротация из query в объект массива
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