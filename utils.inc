<?php 
class Utils {
	
	const GET_ALL = "SELECT * from %s ";
	const INSERT = "INSERT INTO %s(%s) VALUES (%s) ";
	const UPDATE = "UPDATE %s set %s ";
	const DELETE = "DELETE from %s ";
	const WHERE = "WHERE %s";
	const DATE_FORMAT = "Y-m-d H:i:s";
	
	public static $iniConfigObject = null;
	public static $mysqlObject = null;
	
	public static function setMySqlObject($value){
		self::$mysqlObject = $value;
	}
	
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
	 * Заполнить атрибуты из конфига для которы есть сеттеры
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
	/**
	 * Создание объекта и заполнение его свойств из массива значений
	 * @param Array $props
	 * 						- массив значений членов класса
	 * @param String $className
	 * 						- имя класса объекта
	 * @param String $func
	 * 						- метод создания экземпляра
	 * @param Object $inst
	 * 						- экземпляр класса если объект уже создан
	 * @return mixed|NULL
	 * 						- созданный объект или ничего 
	 */
	public static function getClassInstance($props, $className, $func, &$inst = null){
		if ($inst == null){
			$inst = call_user_func(array($className, $func));
		}
		if ($inst != null && $inst !== false){
			if (is_array($props) && method_exists($inst, "getVars")){
				$vars = array_keys($inst->getVars());
				$methods = get_class_methods($inst);
				foreach ($vars as $var){
					if ($props[$var] != null || $props[$var] == 'null'){
						$methodName = strtolower("set".$var);
						foreach ($methods as $method){
							if (strtolower($method) == $methodName){
								if ($props[$var] == 'null'){
									$inst->$method(null);
								} else {
									$inst->$method($props[$var]);
								}
								continue;
							}
						}
					}
				}
			}
			return $inst;
		} else {
			return null;
		}
	}
	
	/**
	 * Установить значение переменной в сессию
	 * @param String $name
	 * 						- имя переменной
	 * @param String $value
	 * 						- зачение
	 */
	public static function setToSession($name, $value){
		$_SESSION[$name] = $value;
	}
	
	/**
	 * Получение переменной из сессии
	 * @param String $name
	 * 						- имя переменной
	 * @param Object $default
	 * 						- дефолтное значение 
	 */
	public static function getFromSession($name, $default){
		$val = $_SESSION[$name];
		if (!isset($val)){
			if (isset($default)){
				return $default;
			} else {
				return null;
			}
		} else {
			return $val;
		}
	}
	
	/**
	 * Удаление переменной из сессии
	 * @param String $name
	 * 						- имя переменной для удаления
	 */
	public static function unsetFromSession($name){
		unset($_SESSION[$name]);
	}
}
?>