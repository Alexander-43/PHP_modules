<?php

interface IDbPersistable {
	/**
	 * Получить таблицу в которой сохранятся объект
	 */
	public function getTableName();
	
	/**
	 * Имя метода который создаёт экземпляр класса
	 */
	public function getCreateMethodName();
	
	/**
	 * Получить Id объекта
	 */
	public function getId();
	
	/**
	 * Получить список полей объекта для сохранения в БД
	 */
	public function getPersistedFields();
	
	/**
	 * Сохранение объекта в БД
	 * @param Object $params
	 * 						- массив/объект параметров
	 */
	public function save($params = null);
	
	/**
	 * Удаление из БД
	 * @param Object $params
	 * 						- массив/объект параметров
	 */
	public function delete($params);
	
	/**
	 * Получение объекта по Id
	 * @param Object $params
	 * 						- массив/объект параметров
	 */
	public function getById($params);
	
	/**
	 * Получить список переменных объекта
	 * @param Object $vars
	 * 						- переменные из родительского класса
	 */
	public function getVars($vars = NULL);
	
	/**
	 * Прверка существования записи для объекта
	 * @param string $className
	 * 						- имя класса
	 * @return int
	 * 						- id записи в БД
	 */
	public function isExists($className);
}

?>