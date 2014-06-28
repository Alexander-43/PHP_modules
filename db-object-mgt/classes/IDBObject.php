<?php

interface IDBObject {
	
	/**
	 * Создание объекта
	 */
	public function create();
	
	/**
	 * Удаление объекта
	 */
	public function delete();
	
	/**
	 * Обновление объекта
	 */
	public function update();
}

?>