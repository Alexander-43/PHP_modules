<?php

interface IDBObject {
	
	/**
	 * Создание объекта
	 */
	public function create();
	
	/**
	 * Удаление объекта
	 */
	public function delete($params);
	
	/**
	 * Обновление свойств объекта
	 */
	public function update();
	
	/**
	 * Получение свойств объекта
	 */
	public function getVars($vars);
}

?>