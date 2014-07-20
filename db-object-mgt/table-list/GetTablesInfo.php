<?php

class GetTablesInfo extends MysqlDBObject {
	
	const SHOW_TABLES = "SHOW table status like '%s'";
	const SHOW_FULL_COLUMN = "SHOW FULL COLUMNS FROM %s";
	
	public function getByPattern($pattern){
		$query = sprintf($this::SHOW_TABLES, $pattern);
		$result = $this->mysql->Execquery($query);
		if ($result != null){
			for ($i=0; $i < count($result); ++$i){
				$query = sprintf($this::SHOW_FULL_COLUMN, $result[$i]['Name']);
				$res = $this->mysql->Execquery($query);
				$result[$i]['columns'] = $res != null ? $res : $res;
			}
			return $result;
		}
		return null;
	}
}

?>