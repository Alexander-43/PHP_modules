<?php 
class Utils {
	public static $iniConfigObject = null;
	public static $mysqlObject = null;
	/**
	 * Возвращает объект ini-config
	 * @param String $filePath
	 * 							- путь до ini-файла
	 */
	public static function getIniConfigObject($filePath){
		if (Utils::$iniConfigObject == null || Utils::$iniConfigObject->source != $filePath) {
			if (file_exists($filePath)) {
				Utils::$iniConfigObject = new IniConfig($filePath);
			}
		}
		return Utils::$iniConfigObject;
	}
	/**
	 * Создает/Возвращает подключение к mysql
	 * @param mixed $params
	 * @param int $paramType
	 * <br>В зависимости от $paramType создается mysql объект с параметрами из $params
	 * <ol>
	 * <li>$paramType=0, $params=Array() - массив параметров для создания подключения (@see AbstractSource)</li>
	 * <li>$paramType=1, $params=Array("fileName"=>value, "sectName"=>value) - массив с путем до ini и именем секции с параметрами
	 * </ol>
	 */
	public static function getMysqlObject($params, $paramType){
		switch ($paramType){
			case 0 :
				if (Utils::$mysqlObject == null || Utils::$mysqlObject->params != $params){
					Utils::$mysqlObject = new Mysql($params);
				}
				break;
			case 1 :
				$config = new IniConfig($params["fileName"]);
				if ($config != null){
					$tempParams = $config->getValueByKey($params["sectName"]);
					if (Utils::$mysqlObject == null || Utils::$mysqlObject->params != $tempParams){
						Utils::$mysqlObject = new Mysql($tempParams);
					}
				}
				break;
			default: return "paramType is not supported";
		}
		return Utils::$mysqlObject;
	}
	
	/**
	 * Запонить атрибуты из конфига для которы есть сеттеры
	 * @param unknown $object
	 * 						- обеъект для которого происходит поиск свойств
	 * @param unknown $config
	 * 						- конфиг, из которго берутся свойства
	 */
	public static function getPropsFromIniConfig(&$object, $config){
		$vars = $object->getVars(null);
		$configSection = get_class($object);
		foreach ($vars as $name=>$value){
			$methodname = strtolower("set".$name);
			$objectMethods = get_class_methods($object);
			foreach($objectMethods as $methname){
				if (strtolower($methname) == $methodname && $config->getValueByKey($configSection.".".$name)!=null){
					$object->$methname($config->getValueByKey($configSection.".".$name));
				}
			}
		}
	}
}
?>