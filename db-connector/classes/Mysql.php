<?php
include_once 'AbstractSource.php';

class Mysql extends AbstractSource {
	public $dblink = null;
	public function __construct($params = null) {
		if ($params != null){
			$this->connect($params);
		}
	}
	public function connect($params) {
		return $this->dblink = mysql_connect($params[AbstractSource::HOST_NAME], 
				$params[AbstractSource::DB_USER], 
				$params[AbstractSource::DB_PASSWORD]);
	}
	public function Execquery($params) {
		$result = mysql_query($params, $this->dblink);
		if ($result){
			return $this->getArrayValues($result);
		} else {
			return null;
		}
	}
	public function close($params) {
		if ($this->dblink != null){
			return mysql_close ($this->dblink);
		}
	}
	/**
	 * Ротация из query в объект массива
	 * @param mysql_query_result $query
	 * @return array
	 */
	public function getArrayValues($query){
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