<?php

interface UserService {
	
	/**
	 * Возвращает всех пользователей
	 */
	public function getAllUsers($params);
	
	/**
	 * Создание пользователя
	 */
	public function createUser($params);
	
	/**
	 * Установить права для пользователя
	 */
	public function setPermission($params);
}

?>