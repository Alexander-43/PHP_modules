<?php

include_once 'AbstractConfig.php';

class IniConfig extends AbstractConfig {
	
	public $cachedValues = null;
	
	public function getAll() {
		if ($this->checkIniFileExists($this->source)){
			if ($this->cachedValues == null){
				$this->cachedValues = parse_ini_file($this->source, true);
			}
			return $this->cachedValues;
		}
	}
	public function getValueByKey($keyString) {
		$keys = explode(".", $keyString);
		$values = $this->getAll();
		$item = null;
		foreach ($keys as $key){
			if ($item == null){
				if (!is_array($values[$key])){
					$parse = parse_ini_string($values[$key], true);
				} else {
					$parse = false;
				}
				$item = is_array($parse) && count($parse)>0 ? $parse: $values[$key];
			} else {
				if (!is_array($item[$key])){
					$parse = parse_ini_string($item[$key], true);
				} else {
					$parse = false;
				}
				$item = is_array($parse) && count($parse)>0 ? $parse: $item[$key];
			}
		}
		return $item;
	}
	
	public function checkIniFileExists($iniFile){
		if (file_exists($iniFile)){
			return true;
		} else {
			throw  new Exception("Ini-���� ".$iniFile." �� ����������");
		}
	}
}

?>